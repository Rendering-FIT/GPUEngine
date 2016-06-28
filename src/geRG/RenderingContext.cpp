#include <algorithm>
#include <cstring>
#include <iostream> // for cerr
#include <sstream>
#include <geRG/RenderingContext.h>
#include <geRG/AttribStorage.h>
#include <geRG/FlexibleUniform.h>
#include <geRG/MatrixList.h>
#include <geRG/Mesh.h>
#include <geRG/StateSet.h>
#include <geRG/StateSetManager.h>
#include <geRG/Transformation.h>
#include <geGL/BufferObject.h>
#include <geGL/ProgramObject.h>

using namespace ge::rg;
using namespace ge::gl;
using namespace std;

thread_local RenderingContext::AutoInitRenderingContext RenderingContext::NoExport::_currentContext;

const unsigned initialPrimitiveBufferCapacity = 512; // 512*12 = 6 KiB
const unsigned initialDrawCommandBufferCapacity = 1024; // 1024*12 = 12 KiB
const unsigned initialMatrixListBufferCapacity = 32; // 32 matrices, 32*64=2'048 bytes
const unsigned initialMatrixAllocationBufferCapacity = 16; // 16*8=128 bytes
const unsigned initialStateSetBufferCapacity = 32; // 32*8=256 bytes
const unsigned initialDrawIndirectBufferSize = 24*1024; // 24 KiB
const unsigned initialTransformationBufferCapacity = 16; // 16*64=1 KiB

const float RenderingContext::identityMatrix[16] = {
   1.f, 0.f, 0.f, 0.f,
   0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 1.f, 0.f,
   0.f, 0.f, 0.f, 1.f,
};



void RenderingContext::global_init()
{
   // init _currentContext.data.value
   // (use placement new on shared_ptr, memory is statically preallocated)
   NoExport::_currentContext.usingNiftyCounter=true; // this will write into local thread storage (lts)
                                                     // and may trigger all the constructors in lts
   if(NoExport::_currentContext.initialized==false) {
      ::new(&NoExport::_currentContext.ptr)shared_ptr<RenderingContext>();
      NoExport::_currentContext.initialized=true;
   }
}


void RenderingContext::global_finalize()
{
   // call in-place shared_ptr destructor
   // (do not free static memory)
   NoExport::_currentContext.get().~shared_ptr();
}


RenderingContext::AutoInitRenderingContext::AutoInitRenderingContext()
{
   if(usingNiftyCounter||initialized)
      return;

   // placement new on shared_ptr
   // (memory is statically preallocated)
   ::new(&ptr)shared_ptr<RenderingContext>();
   initialized=true;
}


RenderingContext::AutoInitRenderingContext::~AutoInitRenderingContext()
{
   if(usingNiftyCounter)
      return;

   // call in-place shared_ptr destructor
   // (do not free static memory)
   get().~shared_ptr();
}


RenderingContext::RenderingContext()
   : _primitiveStorage(initialPrimitiveBufferCapacity,GL_DYNAMIC_DRAW) // array-based
   , _drawCommandStorage(initialDrawCommandBufferCapacity,GL_DYNAMIC_DRAW) // item-based
   , _matrixStorage(initialMatrixListBufferCapacity,1,GL_DYNAMIC_COPY) // array-based, 1 null item (one identity matrix)
   , _matrixListControlStorage(initialMatrixAllocationBufferCapacity,1,GL_DYNAMIC_DRAW) // item-based, 1 null item (one identity matrix)
   , _stateSetStorage(initialStateSetBufferCapacity,GL_DYNAMIC_DRAW) // item-based
   , _transformationAllocationManager(initialTransformationBufferCapacity) // item-based
   , _numAttribStorages(0)
   , _stateSetManager(make_shared<StateSetDefaultManager>())
   , _useARBShaderDrawParameters(false)
{
   // primitiveStorage - array-based
   // null objects:
   // - id 0 - numItems set to zero (no buffer space)
#if 1
   // - id 1 - numItems set to 1, index to 0 (single allocation on the beginning of buffer)
   _primitiveStorage.alloc(1,*static_cast<Mesh*>(nullptr));
   PrimitiveGpuData *psData=static_cast<PrimitiveGpuData*>(
         _primitiveStorage.bufferObject()->map(0,sizeof(PrimitiveGpuData),GL_MAP_WRITE_BIT));
   psData->countAndIndexedFlag=0;
   psData->first=0;
   psData->vertexOffset=0;
   _primitiveStorage.bufferObject()->unmap();
#endif

   // drawCommandStorage - item-based
   // null object on id 0: all members points to zero objects
   DrawCommandGpuData *dcData=static_cast<DrawCommandGpuData*>(
         _drawCommandStorage.bufferObject()->map(0,sizeof(DrawCommandGpuData),GL_MAP_WRITE_BIT));
   dcData->primitiveSetOffset4=0;
   dcData->matrixListControlOffset4=0;
   dcData->stateSetOffset4=0;
   _drawCommandStorage.bufferObject()->unmap();

   // matrixStorage - array-based
   // null objects:
   // - id 0 - numItems set to 1 (one identity matrix)
   float *p1=static_cast<float*>(_matrixStorage.bufferObject()->map(0,sizeof(float)*16,GL_MAP_WRITE_BIT));
   memcpy(p1,identityMatrix,sizeof(float)*16);
   _matrixStorage.bufferObject()->unmap();
#if 0
   // - id 0 - numItems set to zero (no buffer space)
   // - id 1 - numItems set to 1, index to 0 pointing to identity matrix
   _matrixStorage.alloc(1,*static_cast<MatrixList*>(nullptr));
#endif

   // matrixListControlStorage - item-based
   // null object on id 0: startIndex set to 0 (points to identity matrix),
   // numItems to zero (e.g. empty list)
   ListControlGpuData *maData=static_cast<ListControlGpuData*>(
         _matrixListControlStorage.bufferObject()->map(0,sizeof(ListControlGpuData),GL_MAP_WRITE_BIT));
   maData->startIndex=0;
   maData->numItems=0;
   _matrixListControlStorage.bufferObject()->unmap();

   // stateSetStorage - item-based
   // null object, id 0: points to the zero index in _drawIndirectBuffer
   StateSetGpuData *ssData=static_cast<StateSetGpuData*>(
         _stateSetStorage.bufferObject()->map(0,sizeof(StateSetGpuData),GL_MAP_WRITE_BIT));
   ssData->drawIndirectBufferOffset=0;
   _stateSetStorage.bufferObject()->unmap();

   // cpuTransformationBuffer + transformationAllocationManager - item-based
   // null object, id 0: points to identity matrix
   _cpuTransformationBuffer=new float[initialTransformationBufferCapacity*16];
   memcpy(&_cpuTransformationBuffer[0],identityMatrix,sizeof(float)*16);

   // drawIndirectBuffer
   // written by compute shader by processing drawCommandBuffer
   _drawIndirectBuffer=new BufferObject(initialDrawIndirectBufferSize,nullptr,GL_DYNAMIC_COPY);
}


RenderingContext::~RenderingContext()
{
   // break all scene graph references for this context
   cancelAllAllocations();

   // delete all AttribStorages attached to this RenderingContext
   for(AttribConfigList::iterator it=_attribConfigList.begin(),nextIt; it!=_attribConfigList.end(); it=nextIt)
   {
      nextIt=it;
      nextIt++;
      if(it->second)
         it->second->deleteAllAttribStorages();
   }

   // remove references to all Transformations
   _transformationGraphs.clear();

   // check AllocationManagers to be empty
   //_stateSetBufferAllocationManager.assertEmpty();
   //_drawCommandAllocationManager.assertEmpty();
   //_instanceAllocationManager.assertEmpty();
   //_transformationsAllocationManager.assertEmpty();
   //_instancingMatrixCollectionAllocationManager.assertEmpty();
   //_instancingMatrixAllocationManager.assertEmpty();

   // delete buffers
   delete _drawIndirectBuffer;
   //delete _transformationBuffer;
   delete[] _cpuTransformationBuffer;
}


AttribConfigRef RenderingContext::getAttribConfig(const AttribConfig::ConfigData &config)
{
   // find AttribConfig in _attribConfigList (std::map)
   auto r=_attribConfigList.emplace(config,nullptr);

   // if found, return reference to it
   if(r.second==false)
      return r.first->second->createReference();

   // otherwise create new AttribConfig, put it in _attribConfigList and return reference
   AttribConfig *ac=AttribConfig::factory()->create(config,this,r.first);
   r.first->second=ac;
   return ac->createReference();
}


void RenderingContext::removeAttribConfig(AttribConfigList::iterator it)
{
   if(it->second!=NULL)
      it->second->detachFromRenderingContext();
   _attribConfigList.erase(it);
}


void RenderingContext::setUseARBShaderDrawParameters(bool value)
{
   if(_numAttribStorages==0)
      _useARBShaderDrawParameters=value;
   else
      cerr<<"RenderingContext::setUseARBShaderDrawParameters(): The method can be used\n"
            "   only until the first AttribStorage is created for the rendering context."<<endl;
}


void RenderingContext::onAttribStorageInit(AttribStorage*)
{
   _numAttribStorages++;
}


void RenderingContext::onAttribStorageRelease(AttribStorage*)
{
   _numAttribStorages--;
}


void* RenderingContext::mapBuffer(BufferObject *buffer,
                                  MappedBufferAccess requestedAccess,
                                  void* &mappedBufferPtr,
                                  MappedBufferAccess &grantedAccess)
{
   if(grantedAccess==MappedBufferAccess::READ_WRITE ||
      grantedAccess==requestedAccess ||
      requestedAccess==MappedBufferAccess::NO_ACCESS)
      return mappedBufferPtr;

   if(grantedAccess!=MappedBufferAccess::NO_ACCESS)
      buffer->unmap();

   grantedAccess|=requestedAccess;
   mappedBufferPtr=buffer->map(static_cast<GLbitfield>(grantedAccess));
   return mappedBufferPtr;
}


void RenderingContext::unmapBuffer(ge::gl::BufferObject *buffer,
                                   void* &mappedBufferPtr,
                                   MappedBufferAccess &currentAccess)
{
   if(currentAccess==MappedBufferAccess::NO_ACCESS)
      return;

   buffer->unmap();
   mappedBufferPtr=nullptr;
   currentAccess=MappedBufferAccess::NO_ACCESS;
}


void RenderingContext::unmapBuffers()
{
   _primitiveStorage.unmap();
   _drawCommandStorage.unmap();
   _matrixStorage.unmap();
   _matrixListControlStorage.unmap();
   _stateSetStorage.unmap();
}


void RenderingContext::setCpuTransformationBufferCapacity(unsigned numMatrices)
{
   // set new capacity
   unsigned capacity=_transformationAllocationManager.capacity();
   if(capacity==numMatrices)
      return;
   _transformationAllocationManager.setCapacity(numMatrices);

   // realloc buffer
   float *newBuffer=new float[numMatrices*16];
   unsigned copyNumBytes=((capacity<numMatrices)?capacity:numMatrices)*16*sizeof(float);
   memcpy(newBuffer,_cpuTransformationBuffer,copyNumBytes);
   delete[] _cpuTransformationBuffer;
   _cpuTransformationBuffer=newBuffer;
}


/** Allocates the memory for primitives.
 *
 *  Returns true on success. False on failure, usually caused by absence of
 *  large enough free memory block.
 *
 *  The method does not require active graphics context.
 *
 *  @param mesh Mesh that will hold the reference to the allocated memory
 *  @param numPrimitives number of primitives to be allocated
 */
bool RenderingContext::allocPrimitives(Mesh &mesh,unsigned numPrimitives)
{
   // Warn if attribStorage is not assigned
   if(mesh.attribStorage()==nullptr)
   {
      cerr<<"Error: calling RenderingContext::allocPrimitives() on Mesh\n"
            "   that is empty (no vertices and indices allocated)." << endl;
      return false;
   }

   // Warn if already allocated
   if(mesh.primitivesDataId()!=0)
   {
      cerr<<"Warning: calling RenderingContext::allocPrimitiveSets() on Mesh\n"
            "   that has already allocated primitives." << endl;
      freePrimitives(mesh);
   }

   // allocate memory for primitives
   // (assign space in already pre-allocated buffer)
   unsigned id=_primitiveStorage.alloc(numPrimitives,mesh);
   mesh.setPrimitivesDataId(id);

   return true;
}


bool RenderingContext::reallocPrimitives(Mesh& /*mesh*/,unsigned /*numPrimitives*/,bool /*preserveContent*/)
{
   // not implemented yet
   return false;
}


void RenderingContext::freePrimitives(Mesh &mesh)
{
   // Warn if attribStorage is assigned
   if(mesh.attribStorage()==nullptr)
   {
      cerr<<"Error: calling RenderingContext::freePrimitiveSets() on Mesh\n"
            "   that is empty (no vertices and indices allocated)." << endl;
      return;
   }

   // release the memory block
   _primitiveStorage.free(mesh.primitivesDataId());
   mesh.setPrimitivesDataId(0);
}


/** Uploads raw primitive data to GPU buffers.
 *  Note that buffer must contain correct values
 *  in PrimitiveGpuData::vertexOffset.
 *  The method maps gpu-buffers to cpu address space.
 *  Call RenderingContext::unmapBuffers() when all buffer updates are completed.
 */
void RenderingContext::uploadPrimitives(Mesh &r,const PrimitiveGpuData *bufferData,
                                        unsigned numPrimitives,unsigned dstIndex)
{
   if(r.attribStorage()==nullptr || r.primitivesDataId()==0)
      return;

   unsigned index=dstIndex+_primitiveStorage[r.primitivesDataId()].startIndex;
   PrimitiveGpuData *ptr=_primitiveStorage.map(BufferStorageAccess::WRITE);
   memcpy(ptr+index,bufferData,numPrimitives*sizeof(PrimitiveGpuData));
}


/* Sets draw command control data (the data that are kept on CPU memory). */
void RenderingContext::setPrimitives(Mesh &mesh,const Primitive *primitiveList,
                                     unsigned numPrimitives,unsigned startIndex,
                                     bool truncate)
{
   if(mesh.attribStorage()==nullptr)
      return;

   // resize if needed
   unsigned minSizeRequired=numPrimitives+startIndex;
   unsigned currentSize=unsigned(mesh.primitiveList().size());
   if((truncate && currentSize!=minSizeRequired) || minSizeRequired>currentSize)
      mesh.primitiveList().resize(minSizeRequired);

   // copy memory
   memmove(mesh.primitiveList().data()+startIndex,primitiveList,
           numPrimitives*sizeof(Primitive));
}


/** Updates primitive data structures in both - cpu memory and gpu buffers for a given Mesh.
 *
 *  The method updates cpu memory data (see Primitive class)
 *  and uploads the data to gpu buffers (see PrimitiveGpuData).
 *
 *  Each primitive is stored in nonConstBufferData
 *  as PrimitiveGpuData unsigned integers followed
 * by arbitrary user data.
 *
 * Before uploading all draw commands to GPU,
 * the buffer have to be preprocessed to update
 * startIndex of each draw command. As a performance optimization,
 * the preprocessing is performed directly in nonConstDrawCommandBuffer,
 * thus if you do not want the data to be modified,
 * create temporary copy and pass it to the method instead.
 *
 * DrawCommandControlData carries the offset of each
 * draw command inside draw command buffer and mode of each draw command.
 * The mode tells OpenGL rendering mode (GL_TRIANGLES, GL_LINE_STRIP, etc.)
 * and whether indexing is in use (glDrawArrays vs. glDrawElements).
 */
void RenderingContext::setAndUploadPrimitives(Mesh& mesh,PrimitiveGpuData* nonConstBufferData,const Primitive* primitiveList,unsigned numPrimitives)
{
   clearPrimitives(mesh);
   updateVertexOffsets(mesh,nonConstBufferData,primitiveList,numPrimitives);
   uploadPrimitives(mesh,nonConstBufferData,numPrimitives);
   setPrimitives(mesh,primitiveList,numPrimitives);
}


void RenderingContext::updateVertexOffsets(Mesh &mesh,void *primitiveBuffer,
                                           const Primitive *primitiveList,unsigned numPrimitives)
{
   // get index of allocated block
   unsigned vertexOffset;
   if(mesh.indicesDataId()==0)
      vertexOffset=mesh.attribStorage()->vertexArrayAllocation(mesh.verticesDataId()).startIndex;
   else
      vertexOffset=mesh.attribStorage()->indexArrayAllocation(mesh.indicesDataId()).startIndex;

   // update vertexOffset of all primitive sets
   for(unsigned i=0; i<numPrimitives; i++)
   {
      // set PrimitiveSetGpuData::vertexOffset
      unsigned index=primitiveList[i].offset4();
      static_cast<unsigned*>(primitiveBuffer)[index+2]=vertexOffset;
   }
}


vector<Primitive>
RenderingContext::generatePrimitiveList(const unsigned *modesAndOffsets4,unsigned numPrimitives)
{
   vector<Primitive> r;
   r.reserve(numPrimitives);
   for(unsigned i=0,c=numPrimitives*2; i<c; i+=2)
   {
      r.emplace_back(modesAndOffsets4[i+1],modesAndOffsets4[i+0]);
   }
   return r;
}


void RenderingContext::setNumPrimitives(Mesh &mesh,unsigned num)
{
   if(mesh.attribStorage()==nullptr)
      return;

   mesh.primitiveList().resize(num);
}


DrawableId RenderingContext::createDrawable(
      Mesh &mesh,
      const unsigned *primitiveIndices,const unsigned primitiveCount,
      MatrixList *matrixList,StateSet *stateSet)
{
   // numDrawCommands to be created
   unsigned numDrawCommands=primitiveCount!=0 ? primitiveCount
                                              : unsigned(mesh.primitiveList().size());

   // allocate Drawable
   Drawable *drawable=Drawable::alloc(numDrawCommands);
   drawable->stateSet=stateSet;
   drawable->matrixList=matrixList;
   drawable->numItems=numDrawCommands;

   // reference stateSet and matrixList
   // (to indicate that they should not be released from memory as long as this drawable exists)
   stateSet->incrementDrawableCount();
   matrixList->incrementReferenceCounter();

   // allocate draw commands
   _drawCommandStorage.alloc(numDrawCommands,drawable->items());

   // iterate through instances
   auto storageDataIterator=stateSet->getOrCreateAttribStorageData(mesh.attribStorage());
   StateSet::AttribStorageData &storageData=storageDataIterator->second;
   auto listControlOffset4=matrixList->listControlOffset4();
   DrawCommandGpuData* drawCommandBufferPtr=_drawCommandStorage.map(BufferStorageAccess::WRITE);
   for(unsigned i=0; i<numDrawCommands; i++)
   {
      // update DrawCommandGpuData
      DrawCommandGpuData &dcData=drawCommandBufferPtr[drawable->item(i).index()];
      unsigned psIndex=primitiveCount==0 ? i : primitiveIndices[i];
      Primitive pl=mesh.primitiveList()[psIndex];
      dcData.primitiveSetOffset4=_primitiveStorage[mesh.primitivesDataId()].startIndex*
                                 unsigned(sizeof(PrimitiveGpuData)/4) + pl.offset4();
      dcData.matrixListControlOffset4=listControlOffset4;

      // update instance's mode and StateSet counter
      unsigned mode=pl.mode();
      drawable->item(i).setMode(mode);
      stateSet->incrementDrawCommandModeCounter(1,mode,storageData);

      // update DrawCommandGpuData::stateSetOffset4 (must be done after incrementing StateSet counter)
      dcData.stateSetOffset4=stateSet->getStateSetBufferOffset4(mode,storageData);
   }
   stateSet->releaseAttribStorageDataIfEmpty(storageDataIterator);

   // insert Drawable into the list of drawables
   // and return iterator to it
   mesh.drawables().push_front(drawable);
   return mesh.drawables().begin();
}


void RenderingContext::deleteDrawable(Mesh &mesh,DrawableId id)
{
   // iterate through instances
   StateSet *stateSet=id->stateSet;
   auto storageDataIterator=stateSet->getOrCreateAttribStorageData(mesh.attribStorage());
   StateSet::AttribStorageData &storageData=storageDataIterator->second;
   for(unsigned i=0,c=id->numItems; i<c; i++)
   {
      // update StateSet counter
      stateSet->decrementDrawCommandModeCounter(1,id->item(i).mode(),storageData);
   }
   stateSet->releaseAttribStorageDataIfEmpty(storageDataIterator);

   // unreference matrixList and stateSet
   id->matrixList->decrementReferenceCounter();
   stateSet->decrementDrawableCount();

   // remove from lists, execute destructors and free memory
   _drawCommandStorage.free(id->items(),id->numItems);
   id->free();
   mesh.drawables().erase(id);
}


void RenderingContext::addTransformationGraph(shared_ptr<Transformation>& transformation)
{
   _transformationGraphs.emplace_back(transformation);
}


void RenderingContext::removeTransformationGraph(shared_ptr<Transformation>& transformation)
{
   auto it=std::find(_transformationGraphs.begin(),_transformationGraphs.end(),transformation);
   if(it!=_transformationGraphs.end())
      _transformationGraphs.erase(it);
}


void RenderingContext::cancelAllAllocations()
{
   // break Mesh references to Primitives
   // (set all Mesh::_attribStorage to nullptr
   // and zero all Drawable::items)
   for(auto it=_primitiveStorage.begin(), // begin() skips all null items
       e=_primitiveStorage.end(); // end() points just after the last allocated item
       it!=e; it++)
   {
      Mesh *m=it->owner;
      if(m) {
         m->setAttribStorage(nullptr);
         DrawableList &dl=m->drawables();
         for(auto dlit=dl.begin(); dlit!=dl.end(); dlit++) {
            unsigned num=dlit->numItems;
            for(unsigned i=0; i<num; i++)
               dlit->item(i).data=0;
         }
      }
   }

   // empty allocation maps
   _primitiveStorage.clear();
   _drawCommandStorage.clear();

   // break references in all AttribStorages
   // (call AttribStorage::cancelAllAllocations() for all AttribStorages,
   // this will cause to set all dependent Mesh::_attribStorage to nullptr)
   for(auto acIt=_attribConfigList.begin(); acIt!=_attribConfigList.end(); acIt++)
   {
      const AttribConfig::AttribStorageList &list=acIt->second->getAttribStorageList();
      for(auto asIt=list.begin(); asIt!=list.end(); asIt++)
         (*asIt)->cancelAllAllocations();
   }

   // break Transformation references into the transformation matrix buffer
   {
      unsigned id=_transformationAllocationManager.firstId();
      unsigned last=_transformationAllocationManager.lastId();
      for(; id<=last; id++)
      {
         unsigned *p=_transformationAllocationManager[id];
         if(p!=nullptr) {
            _transformationAllocationManager.free(id);
            *p=0;
         }
      }
   }
}


void RenderingContext::handleContextLost()
{
   cancelAllAllocations();
}


const shared_ptr<ProgramObject>& RenderingContext::getProcessDrawCommandsProgram() const
{
   if(!_processDrawCommandsProgram)
      const_cast<RenderingContext*>(this)->_processDrawCommandsProgram=make_shared<ProgramObject>(
         GL_COMPUTE_SHADER,
         "#version 430\n"
         "\n"
         "layout(local_size_x=64,local_size_y=1,local_size_z=1) in;\n"
         "\n"
         "layout(std430,binding=0) restrict readonly buffer PrimitiveBuffer {\n"
         "   uint primitiveBuffer[];\n"
         "};\n"
         "layout(std430,binding=1) restrict readonly buffer DrawCommandBuffer {\n"
         "   uint drawCommandBuffer[];\n"
         "};\n"
         "layout(std430,binding=2) restrict readonly buffer MatrixListControlBuffer {\n"
         "   uint matrixListControlBuffer[];\n"
         "};\n"
         "layout(std430,binding=3) restrict writeonly buffer DrawIndirectBuffer {\n"
         "   uint drawIndirectBuffer[];\n"
         "};\n"
         "layout(std430,binding=4) restrict buffer StateSetBuffer {\n"
         "   uint stateSetBuffer[];\n"
         "};\n"
         "\n"
         "uniform uint numToProcess;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   if(gl_GlobalInvocationID.x>=numToProcess)\n"
         "      return;\n"
         "\n"
         "   // draw command buffer data\n"
         "   uint drawCommandOffset4=gl_GlobalInvocationID.x*3;\n"
         "   uint primitiveOffset4=drawCommandBuffer[drawCommandOffset4+0];\n"
         "   uint matrixControlOffset4=drawCommandBuffer[drawCommandOffset4+1];\n"
         "   uint stateSetDataOffset4=drawCommandBuffer[drawCommandOffset4+2];\n"
         "\n"
         "   // matrix control data\n"
         "   uint matrixListOffset64=matrixListControlBuffer[matrixControlOffset4+0];\n"
         "   uint numMatrices=matrixListControlBuffer[matrixControlOffset4+1];\n"
         "\n"
         "   // compute increment and get indirectBufferOffset\n"
         "   uint countAndIndexedFlag=primitiveBuffer[primitiveOffset4+0];\n"
         "   uint indirectBufferIncrement=4+bitfieldExtract(countAndIndexedFlag,31,1); // make increment 4 or 5\n"
         "   uint indirectBufferOffset4=atomicAdd(stateSetBuffer[stateSetDataOffset4],indirectBufferIncrement);\n"
         "\n"
         "   // write indirect buffer data\n"
         "   drawIndirectBuffer[indirectBufferOffset4]=countAndIndexedFlag&0x7fffffff; // indexCount or vertexCount\n"
         "   indirectBufferOffset4++;\n"
         "   drawIndirectBuffer[indirectBufferOffset4]=numMatrices; // instanceCount\n"
         "   indirectBufferOffset4++;\n"
         "   uint first=primitiveBuffer[primitiveOffset4+1]; // firstIndex or firstVertex\n"
         "   uint vertexOffset=primitiveBuffer[primitiveOffset4+2]; // vertexOffset\n"
         "   if(countAndIndexedFlag>=0x80000000) {\n"
         "      drawIndirectBuffer[indirectBufferOffset4]=first; // firstIndex\n"
         "      indirectBufferOffset4++;\n"
         "      drawIndirectBuffer[indirectBufferOffset4]=vertexOffset; // vertexOffset\n"
         "      indirectBufferOffset4++;\n"
         "   } else {\n"
         "      drawIndirectBuffer[indirectBufferOffset4]=first+vertexOffset; // firstVertex\n"
         "      indirectBufferOffset4++;\n"
         "   }\n"
         "   drawIndirectBuffer[indirectBufferOffset4]=matrixListOffset64; // base instance\n"
         "}\n");
   return _processDrawCommandsProgram;
}


const shared_ptr<ProgramObject>& RenderingContext::getAmbientProgram() const
{
   if(!_ambientProgram) {
      const_cast<RenderingContext*>(this)->_ambientProgram=make_shared<ProgramObject>(
         GL_VERTEX_SHADER,
         static_cast<std::stringstream&>(stringstream()<<
         "#version 430\n"
         <<(_useARBShaderDrawParameters
         ? "#extension GL_ARB_shader_draw_parameters : enable\n"
           "\n"
           "layout(std430,binding=0) restrict readonly buffer InstancingMatrix {\n"
           "   mat4 instancingMatrixBuffer[];\n"
           "};\n"
         : ""
         )<<
         "\n"
         "layout(location=0) in vec4 position;\n"
         "layout(location=2) in vec4 color;\n"
         "layout(location=3) in vec2 texCoord;\n"
         <<(_useARBShaderDrawParameters
         ? ""
         : "layout(location=12) in mat4 instancingMatrix;\n"
         )<<
         "\n"
         "out VertexData {\n" // interfaces are supported since GLSL 1.5 (OpenGL 3.2)
         "   vec4 color;\n"
         "   vec2 texCoord;\n"
         "} o;\n"
         "\n"
         "uniform vec4 globalAmbientLight; // alpha must be 1\n"
         "uniform mat4 projection;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   // ambient lighting\n"
         "   o.color=globalAmbientLight*color;\n"
         "   o.texCoord=texCoord;\n"
         "\n"
         "   // vertex position\n"
         <<(_useARBShaderDrawParameters
         ? "   uint matrixOffset64=gl_BaseInstanceARB+gl_InstanceID;\n"
           "   gl_Position=projection*(instancingMatrixBuffer[matrixOffset64]*position);\n"
         : "   gl_Position=projection*(instancingMatrix*position);\n" // ( and ) are used to perform the same computation and produce exactly the same results in ambient and phong render pass
         )<<
         "}\n").str(),
         GL_FRAGMENT_SHADER,
         "#version 330\n"
         "\n"
         "in VertexData {\n"
         "   vec4 color;\n"
         "   vec2 texCoord;\n"
         "};\n"
         "\n"
         "layout(location=0) out vec4 fragColor;\n"
         "\n"
         "uniform int colorTexturingMode; // 0 - no texturing, 1 - modulate, 2 - replace\n"
         "uniform sampler2D colorTexture;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   // texturing and final color\n"
         "   if(colorTexturingMode==0) // no texturing\n"
         "      fragColor=color;\n"
         "   else if(colorTexturingMode==1) // modulate\n"
         "      fragColor=color*texture(colorTexture,texCoord);\n"
         "   else // replace\n"
         "      fragColor=texture(colorTexture,texCoord);\n"
         "}\n");
   }
   return _ambientProgram;
}


const shared_ptr<ProgramObject>& RenderingContext::getAmbientUniformColorProgram() const
{
   if(!_ambientUniformColorProgram) {
      const_cast<RenderingContext*>(this)->_ambientUniformColorProgram=make_shared<ProgramObject>(
         GL_VERTEX_SHADER,
         static_cast<std::stringstream&>(stringstream()<<
         "#version 430\n"
         <<(_useARBShaderDrawParameters
         ? "#extension GL_ARB_shader_draw_parameters : enable\n"
           "\n"
           "layout(std430,binding=0) restrict readonly buffer InstancingMatrix {\n"
           "   mat4 instancingMatrixBuffer[];\n"
           "};\n"
         : ""
         )<<
         "\n"
         "layout(location=0) in vec4 position;\n"
         "layout(location=3) in vec2 texCoord;\n"
         <<(_useARBShaderDrawParameters
         ? ""
         : "layout(location=12) in mat4 instancingMatrix;\n"
         )<<
         "\n"
         "out VertexData {\n" // interfaces are supported since GLSL 1.5 (OpenGL 3.2)
         "   flat vec4 color;\n"
         "   vec2 texCoord;\n"
         "} o;\n"
         "\n"
         "uniform vec4 color;\n"
         "uniform vec4 globalAmbientLight; // alpha must be 1\n"
         "uniform mat4 projection;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   // ambient lighting\n"
         "   o.color=globalAmbientLight*color;\n"
         "   o.texCoord=texCoord;\n"
         "\n"
         "   // vertex position\n"
         <<(_useARBShaderDrawParameters
         ? "   uint matrixOffset64=gl_BaseInstanceARB+gl_InstanceID;\n"
           "   gl_Position=projection*(instancingMatrixBuffer[matrixOffset64]*position);\n"
         : "   gl_Position=projection*(instancingMatrix*position);\n" // ( and ) are used to perform the same computation and produce exactly the same results in ambient and phong render pass
         )<<
         "}\n").str(),
         GL_FRAGMENT_SHADER,
         "#version 330\n"
         "\n"
         "in VertexData {\n"
         "   flat vec4 color;\n"
         "   vec2 texCoord;\n"
         "};\n"
         "\n"
         "layout(location=0) out vec4 fragColor;\n"
         "\n"
         "uniform int colorTexturingMode; // 0 - no texturing, 1 - modulate, 2 - replace\n"
         "uniform sampler2D colorTexture;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   // texturing and final color\n"
         "   if(colorTexturingMode==0) // no texturing\n"
         "      fragColor=color;\n"
         "   else if(colorTexturingMode==1) // modulate\n"
         "      fragColor=color*texture(colorTexture,texCoord);\n"
         "   else // replace\n"
         "      fragColor=texture(colorTexture,texCoord);\n"
         "}\n");
   }
   return _ambientUniformColorProgram;
}


const shared_ptr<ProgramObject>& RenderingContext::getPhongProgram() const
{
   if(!_phongProgram) {
      const_cast<RenderingContext*>(this)->_phongProgram=make_shared<ProgramObject>(
         GL_VERTEX_SHADER,
         static_cast<std::stringstream&>(stringstream()
         <<(_useARBShaderDrawParameters
         ? "#version 430\n"
           "#extension GL_ARB_shader_draw_parameters : enable\n"
           "\n"
           "layout(std430,binding=0) restrict readonly buffer InstancingMatrix {\n"
           "   mat4 instancingMatrixBuffer[];\n"
           "};\n"
         : "#version 330\n"
         )<<
         "\n"
         "layout(location=0) in vec4 position;\n"
         "layout(location=1) in vec3 normal;\n"
         "layout(location=2) in vec4 color;\n"
         "layout(location=3) in vec2 texCoord;\n"
         <<(_useARBShaderDrawParameters
         ? ""
         : "layout(location=12) in mat4 instancingMatrix;\n"
         )<<
         "\n"
         "out VertexData {\n" // interfaces are supported since GLSL 1.5 (OpenGL 3.2)
         "   vec3 eyePosition;\n"
         "   vec3 eyeNormal;\n"
         "   vec4 color;\n"
         "   vec2 texCoord;\n"
         "} o;\n"
         "\n"
         "uniform mat4 projection;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   o.color=color;\n"
         "   o.texCoord=texCoord;\n"
         <<(_useARBShaderDrawParameters
         ? "   uint matrixOffset64=gl_BaseInstanceARB+gl_InstanceID;\n"
           "   mat4 instancingMatrix=instancingMatrixBuffer[matrixOffset64];\n"
           "   vec4 v=instancingMatrix*position;\n"
         : "   vec4 v=instancingMatrix*position;\n"
         )<<
         "   o.eyePosition=v.xyz;\n"
         "   o.eyeNormal=transpose(inverse(mat3(instancingMatrix)))*normal;\n"
         "   gl_Position=projection*v;\n"
         "}\n").str(),
         GL_FRAGMENT_SHADER,
         "#version 330\n"
         "\n"
         "in VertexData {\n"
         "   vec3 eyePosition;\n"
         "   vec3 eyeNormal;\n"
         "   vec4 color;\n"
         "   vec2 texCoord;\n"
         "};\n"
         "\n"
         "layout(location=0) out vec4 fragColor;\n"
         "\n"
         "uniform vec4 specularAndShininess; // shininess in alpha\n"
         "uniform int colorTexturingMode; // 0 - no texturing, 1 - modulate, 2 - replace\n"
         "uniform sampler2D colorTexture;\n"
         "uniform vec4 lightPosition; // in eye coordinates, w must be 0 or 1\n"
         "uniform vec3 lightColor;\n"
         "uniform vec3 lightAttenuation;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   // compute VL - vertex to light vector, in eye coordinates\n"
         "   vec3 VL=lightPosition.xyz;\n"
         "   if(lightPosition.w!=0.)\n"
         "      VL-=eyePosition;\n"
         "   float VLlen=length(VL);\n"
         "   vec3 VLdir=VL/VLlen;\n"
         "\n"
         "   // invert normals on back facing triangles\n"
         "   vec3 N=gl_FrontFacing?eyeNormal:-eyeNormal;\n"
         "\n"
         "   // Lambert's diffuse reflection\n"
         "   float NdotL=dot(N,VLdir);\n"
         "\n"
         "   // fragments facing the light get all the lighting\n"
         "   // while those not facing the light get only ambient lighting\n"
         "   if(NdotL<=0.)\n"
         "   {\n"
         "      // final sum for light-not-facing fragments\n"
         "      // (This can be computed as fragColor=vec4(0,0,0,diffuse.a)\n"
         "      // or we can simply drop the fragment.)\n"
         "      discard;\n"
         "   }\n"
         "   else\n"
         "   {\n"
         "      // specular effect\n"
         "      float specularEffect;\n"
         "      vec3 R=reflect(-VLdir,N);\n"
         "      vec3 Vdir=normalize(eyePosition.xyz);\n"
         "      float RdotV=dot(R,-Vdir);\n"
         "      if(RdotV>0.)\n"
         "         specularEffect=pow(RdotV,specularAndShininess.a);\n"
         "      else\n"
         "         specularEffect = 0.;\n"
         "\n"
         "      // attenuation\n"
         "      float attenuation=lightAttenuation[0]+\n"
         "                        lightAttenuation[1]*VLlen+\n"
         "                        lightAttenuation[2]*VLlen*VLlen;\n"
         "\n"
         "      // texturing\n"
         "      vec4 c;\n;"
         "      if(colorTexturingMode==0) // no texturing\n"
         "         c=color;\n"
         "      else if(colorTexturingMode==1) // modulate\n"
         "         c=texture(colorTexture,texCoord)*color;\n"
         "      else // replace\n"
         "         c=texture(colorTexture,texCoord);\n"
         "\n"
         "      // final sum for light-facing fragments\n"
         "      fragColor=vec4((c.rgb*lightColor*NdotL+\n"
         "                      specularAndShininess.rgb*lightColor*specularEffect)/\n"
         "                      attenuation,\n"
         "                     c.a);\n"
         "   }\n"
         "}\n");
   }
   return _phongProgram;
}


const shared_ptr<ProgramObject>& RenderingContext::getPhongUniformColorProgram() const
{
   if(!_phongUniformColorProgram) {
      const_cast<RenderingContext*>(this)->_phongUniformColorProgram=make_shared<ProgramObject>(
         GL_VERTEX_SHADER,
         static_cast<std::stringstream&>(stringstream()
         <<(_useARBShaderDrawParameters
         ? "#version 430\n"
           "#extension GL_ARB_shader_draw_parameters : enable\n"
           "\n"
           "layout(std430,binding=0) restrict readonly buffer InstancingMatrix {\n"
           "   mat4 instancingMatrixBuffer[];\n"
           "};\n"
         : "#version 330\n"
         )<<
         "\n"
         "layout(location=0) in vec4 position;\n"
         "layout(location=1) in vec3 normal;\n"
         "layout(location=3) in vec2 texCoord;\n"
         <<(_useARBShaderDrawParameters
         ? ""
         : "layout(location=12) in mat4 instancingMatrix;\n"
         )<<
         "\n"
         "out VertexData {\n" // interfaces are supported since GLSL 1.5 (OpenGL 3.2)
         "   vec3 eyePosition;\n"
         "   vec3 eyeNormal;\n"
         "   vec2 texCoord;\n"
         "} o;\n"
         "\n"
         "uniform mat4 projection;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   o.texCoord=texCoord;\n"
         <<(_useARBShaderDrawParameters
         ? "   uint matrixOffset64=gl_BaseInstanceARB+gl_InstanceID;\n"
           "   mat4 instancingMatrix=instancingMatrixBuffer[matrixOffset64];\n"
           "   vec4 v=instancingMatrix*position;\n"
         : "   vec4 v=instancingMatrix*position;\n"
         )<<
         "   o.eyePosition=v.xyz;\n"
         "   o.eyeNormal=transpose(inverse(mat3(instancingMatrix)))*normal;\n"
         "   gl_Position=projection*v;\n"
         "}\n").str(),
         GL_FRAGMENT_SHADER,
         "#version 330\n"
         "\n"
         "in VertexData {\n"
         "   vec3 eyePosition;\n"
         "   vec3 eyeNormal;\n"
         "   vec2 texCoord;\n"
         "};\n"
         "\n"
         "layout(location=0) out vec4 fragColor;\n"
         "\n"
         "uniform vec4 color;\n"
         "uniform vec4 specularAndShininess; // shininess in alpha\n"
         "uniform int colorTexturingMode; // 0 - no texturing, 1 - modulate, 2 - replace\n"
         "uniform sampler2D colorTexture;\n"
         "uniform vec4 lightPosition; // in eye coordinates, w must be 0 or 1\n"
         "uniform vec3 lightColor;\n"
         "uniform vec3 lightAttenuation;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   // compute VL - vertex to light vector, in eye coordinates\n"
         "   vec3 VL=lightPosition.xyz;\n"
         "   if(lightPosition.w!=0.)\n"
         "      VL-=eyePosition;\n"
         "   float VLlen=length(VL);\n"
         "   vec3 VLdir=VL/VLlen;\n"
         "\n"
         "   // invert normals on back facing triangles\n"
         "   vec3 N=gl_FrontFacing?eyeNormal:-eyeNormal;\n"
         "\n"
         "   // Lambert's diffuse reflection\n"
         "   float NdotL=dot(N,VLdir);\n"
         "\n"
         "   // fragments facing the light get all the lighting\n"
         "   // while those not facing the light get only ambient lighting\n"
         "   if(NdotL<=0.)\n"
         "   {\n"
         "      // final sum for light-not-facing fragments\n"
         "      // (This can be computed as fragColor=vec4(0,0,0,diffuse.a)\n"
         "      // or we can simply drop the fragment.)\n"
         "      discard;\n"
         "   }\n"
         "   else\n"
         "   {\n"
         "      // specular effect\n"
         "      float specularEffect;\n"
         "      vec3 R=reflect(-VLdir,N);\n"
         "      vec3 Vdir=normalize(eyePosition.xyz);\n"
         "      float RdotV=dot(R,-Vdir);\n"
         "      if(RdotV>0.)\n"
         "         specularEffect=pow(RdotV,specularAndShininess.a);\n"
         "      else\n"
         "         specularEffect = 0.;\n"
         "\n"
         "      // attenuation\n"
         "      float attenuation=lightAttenuation[0]+\n"
         "                        lightAttenuation[1]*VLlen+\n"
         "                        lightAttenuation[2]*VLlen*VLlen;\n"
         "\n"
         "      // texturing\n"
         "      vec4 c;\n;"
         "      if(colorTexturingMode==0) // no texturing\n"
         "         c=color;\n"
         "      else if(colorTexturingMode==1) // modulate\n"
         "         c=texture(colorTexture,texCoord)*color;\n"
         "      else // replace\n"
         "         c=texture(colorTexture,texCoord);\n"
         "\n"
         "      // final sum for light-facing fragments\n"
         "      fragColor=vec4(1.f,0.f,0.f,1.f);/*(c.rgb*lightColor*NdotL+\n"
         "                      specularAndShininess.rgb*lightColor*specularEffect)/\n"
         "                      attenuation,\n"
         "                     c.a)*/;\n"
         "   }\n"
         "}\n");
   }
   return _phongUniformColorProgram;
}


#if 0 // uncomment for debugging purposes (it is commented out to kill warning of unused function)
static void printIntBufferContent(ge::gl::BufferObject *bo,unsigned numInts)
{
   cout<<"Buffer contains "<<numInts<<" int values:"<<endl;
   unsigned *p=(unsigned*)bo->map(GL_MAP_READ_BIT);
   if(p==nullptr) return;
   unsigned i;
   for(i=0; i<numInts; i++)
   {
      cout<<*(p+i)<<"  ";
      if(i%4==3)
         cout<<endl;
   }
   bo->unmap();
   if(i%4!=0)
      cout<<endl;
   cout<<endl;
}


static void printFloatBufferContent(ge::gl::BufferObject *bo,unsigned numFloats)
{
   cout<<"Buffer contains "<<numFloats<<" float values:"<<endl;
   float *p=(float*)bo->map(GL_MAP_READ_BIT);
   if(p==nullptr) return;
   unsigned i;
   for(i=0; i<numFloats; i++)
   {
      cout<<*(p+i)<<"  ";
      if(i%4==3)
         cout<<endl;
   }
   bo->unmap();
   if(i%4!=0)
      cout<<endl;
   cout<<endl;
}
#endif


static void countMatrices(Transformation *t,unsigned &totalMatrices)
{
   MatrixList *ml=t->matrixList().get();
   if(ml) {
      if(ml->restartFlag()) {
         ml->setNumMatrices(1);
         ml->setRestartFlag(false);
      } else {
         ml->setNumMatrices(ml->numMatrices()+1);
      }
      totalMatrices++;
   }
   for(auto it=t->childList().begin(); it!=t->childList().end(); it++)
      countMatrices(it->get(),totalMatrices);
}


static void processTransformation(Transformation *t,const glm::mat4& parentMV,RenderingContext *rc)
{
   // compute new matrix
   glm::mat4 mv=parentMV*(*reinterpret_cast<glm::mat4*>(t->getMatrixPtr()));

   // update number of matrices and allocated space for them
   MatrixList *ml=t->matrixList().get();
   if(ml)
   {
      if(ml->restartFlag()==false)
      {
         ml->setRestartFlag(true);
         unsigned matrixOffset64=rc->bufferPosition();
         ml->setStartIndex(matrixOffset64);
         rc->setBufferPosition(matrixOffset64+ml->numMatrices());
         ml->uploadListControlData(); // upload startIndex and numMatrices
         ml->setNumMatrices(0);
      }
      ml->uploadMatrixData(&mv,ml->numMatrices(),1);
      ml->setNumMatrices(ml->numMatrices()+1);
   }

   // process child transformations
   for(auto it=t->childList().begin(); it!=t->childList().end(); it++)
      processTransformation(it->get(),mv,rc);
}


void RenderingContext::evaluateTransformationGraph()
{
   // count matrices
   unsigned totalMatrices=_matrixStorage.numNullItems(); // skip null items
   for(auto it=_transformationGraphs.begin(); it!=_transformationGraphs.end(); it++)
      countMatrices(it->get(),totalMatrices);

   if(totalMatrices>_matrixStorage.capacity()) {

      // resize matrix buffer
      unsigned newSize=unsigned(totalMatrices*1.2f);
      _matrixStorage.setCapacity(newSize);
      _matrixStorage.bufferObject()->realloc(newSize*sizeof(float)*16,ge::gl::BufferObject::KEEP_ID);

      // initialize identity matrix on the beginning of the buffer
      float *p=static_cast<float*>(_matrixStorage.bufferObject()->map(0,sizeof(float)*16,GL_MAP_WRITE_BIT));
      memcpy(p,identityMatrix,sizeof(float)*16);
      _matrixStorage.bufferObject()->unmap();
   }

   // reset buffer position
   // here, we use it as index to matrix4 buffer that is stored in MatrixStorage
   setBufferPosition(_matrixStorage.numNullItems()); // skip null items

   glm::mat4 mv{}; // identity matrix
   matrixStorage()->map(BufferStorageAccess::WRITE);
   memcpy(matrixStorage()->ptr(),identityMatrix,sizeof(float)*16);
   matrixListControlStorage()->map(BufferStorageAccess::WRITE);
   for(auto it=_transformationGraphs.begin(); it!=_transformationGraphs.end(); it++)
      processTransformation(it->get(),mv,this);
   matrixStorage()->unmap();
   matrixListControlStorage()->unmap();
}


void RenderingContext::setupRendering()
{
   // reset buffer position
   // here, we use buffer position as index to uint array that is stored in indirect buffer
   setBufferPosition(4); // 4xuint is reserved for null item, it will be never drawn,
                         // but it will be written on the beginning of the buffer

   // set null StateSet position to zero
   // (other StateSets will use non-zero values)
   unsigned *stateSetBufferPtr=reinterpret_cast<unsigned*>(_stateSetStorage.ptr());
   stateSetBufferPtr[0]=0;

   // setup rendering on StateSets
   StateSet* root=_stateSetManager->root().get();
   if(root)
      root->setupRendering();

   // resize drawIndirectBuffer if necessary
   if(_drawIndirectBuffer->getSize()<bufferPosition()*4)
      _drawIndirectBuffer->realloc(static_cast<decltype(_bufferPosition)>(
            bufferPosition()*1.2f)*4, // multiply by 1.2 to avoid possibly many reallocations by very small amount
            BufferObject::NEW_BUFFER);
}


void RenderingContext::processDrawCommands()
{
   // process draw commands and generate content of draw indirect buffer using compute shader
   auto processDrawCommandsProgram=getProcessDrawCommandsProgram();
   processDrawCommandsProgram->use();
   unsigned numInstances=drawCommandStorage()->firstItemAvailableAtTheEnd();
   processDrawCommandsProgram->set("numToProcess",numInstances);
   primitiveStorage()->bufferObject()->bindBase(GL_SHADER_STORAGE_BUFFER,0);
   drawCommandStorage()->bufferObject()->bindBase(GL_SHADER_STORAGE_BUFFER,1);
   matrixListControlStorage()->bufferObject()->bindBase(GL_SHADER_STORAGE_BUFFER,2);
   drawIndirectBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,3);
   stateSetStorage()->bufferObject()->bindBase(GL_SHADER_STORAGE_BUFFER,4);
   glDispatchCompute((numInstances+63)/64,1,1);
}


void RenderingContext::fenceSyncGpuComputation()
{
   // finish all current commands in GPU queue
   GLsync syncObj=glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE,0);
#if 0 // glWaitSync does not work on my Quadro K1000M (Keppler architecture), drivers 352.21
      // (this would be faster as it does not involve CPU)
   //glFlush();
   //glWaitSync(syncObj,0,GL_TIMEOUT_IGNORED);
#else
   // synchronization involving CPU
   glClientWaitSync(syncObj,GL_SYNC_FLUSH_COMMANDS_BIT,(GLuint64)1e9);
#endif
   glDeleteSync(syncObj);
}


void RenderingContext::render()
{
   // bind buffers for rendering
   drawIndirectBuffer()->bind(GL_DRAW_INDIRECT_BUFFER);
   if(_useARBShaderDrawParameters)
      matrixStorage()->bufferObject()->bindBase(GL_SHADER_STORAGE_BUFFER,0);

#if 0
   cout<<_primitiveStorage.bufferObject()->getSize()<<endl;
   cout<<_drawCommandStorage.bufferObject()->getSize()<<endl;
   cout<<_matrixStorage.bufferObject()->getSize()<<endl;
   cout<<_matrixListControlStorage.bufferObject()->getSize()<<endl;
   cout<<_stateSetStorage.bufferObject()->getSize()<<endl;
   cout<<_transformationAllocationManager.capacity()<<endl;
   cout<<_drawIndirectBuffer->getSize()<<endl;
#endif
#if 0
   printIntBufferContent(RenderingContext::current()->primitiveStorage()->bufferObject(),
                         RenderingContext::current()->primitiveStorage()->firstItemAvailableAtTheEnd()*3);
   printIntBufferContent(RenderingContext::current()->drawCommandStorage()->bufferObject(),
                         RenderingContext::current()->drawCommandStorage()->firstItemAvailableAtTheEnd()*3);
   printIntBufferContent(RenderingContext::current()->stateSetStorage()->bufferObject(),
                         RenderingContext::current()->stateSetStorage()->firstItemAvailableAtTheEnd());
   printIntBufferContent(RenderingContext::current()->drawIndirectBuffer(),
                         RenderingContext::current()->drawCommandStorage()->firstItemAvailableAtTheEnd()*5);
#endif

   // render all StateSets
   _stateSetManager->render();
}


void RenderingContext::frame()
{
   // update progressStamp (monotonically increasing number wrapping on overflow)
   incrementProgressStamp();

   // clear screen
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   // compute transformation matrices
   evaluateTransformationGraph();

   // prepare internal structures for rendering
   stateSetStorage()->map(BufferStorageAccess::WRITE);
   setupRendering();
   stateSetStorage()->unmap();

   // fill indirect buffer with draw commands
   processDrawCommands();
   fenceSyncGpuComputation();

   // render scene
   render();

   // check for OpenGL errors
   unsigned e=glGetError();
   if(e!=GL_NO_ERROR)
      cout<<"OpenGL error "<<e<<" detected after the frame rendering"<<endl;
}


std::shared_ptr<ge::gl::TextureObject> RenderingContext::cachedTextureObject(const std::string& path) const
{
   auto it=_textureCache.find(path);
   if(it==_textureCache.end())
      return std::shared_ptr<ge::gl::TextureObject>();
   auto r=it->second.lock();
   if(!r)
      const_cast<RenderingContext*>(this)->_textureCache.erase(it);
   return r;
}


void RenderingContext::setCurrent(const shared_ptr<RenderingContext>& ptr)
{
   NoExport::_currentContext.get()=ptr;
}
