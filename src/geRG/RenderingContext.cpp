#include <algorithm>
#include <cstring>
#include <iostream> // for cerr
#include <geRG/RenderingContext.h>
#include <geRG/Mesh.h>
#include <geRG/AttribStorage.h>
#include <geRG/StateSet.h>
#include <geRG/MatrixList.h>
#include <geRG/Transformation.h>
#include <geGL/BufferObject.h>

using namespace ge::rg;
using namespace ge::gl;
using namespace std;

thread_local RenderingContext::AutoInitRenderingContext RenderingContext::NoExport::_currentContext;

const unsigned initialPrimitiveBufferCapacity = 512; // 512*12 = 6 KiB
const unsigned intialDrawCommandBufferCapacity = 1024; // 1024*12 = 12 KiB
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



void RenderingContext::init()
{
   // init _currentContext.data.value
   // (use placement new on shared_ptr, memory is statically preallocated)
   NoExport::_currentContext.usingNiftyCounter=true; // this will write into local thread storage (lts)
                                                     // and may trigger all the constructors in lts
   if(NoExport::_currentContext.initialized==false) {
      ::new(&NoExport::_currentContext.ptr[0])shared_ptr<RenderingContext>();
      NoExport::_currentContext.initialized=true;
   }
}


void RenderingContext::finalize()
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
   ::new(&ptr[0])shared_ptr<RenderingContext>();
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
   : _numAttribStorages(0)
   , _useARBShaderDrawParameters(false)
   , _primitiveStorage(initialPrimitiveBufferCapacity,1,GL_DYNAMIC_DRAW) // block-based
   , _drawCommandStorage(intialDrawCommandBufferCapacity,1,GL_DYNAMIC_DRAW) // item-based
   , _matrixStorage(initialMatrixListBufferCapacity,1,GL_DYNAMIC_COPY) // block-based, 1 null item (one identity matrix)
   , _matrixListControlStorage(initialMatrixAllocationBufferCapacity,1,GL_DYNAMIC_DRAW) // item-based, 1 null item (one identity matrix)
   , _stateSetStorage(initialStateSetBufferCapacity,1,GL_DYNAMIC_DRAW) // item-based
   , _transformationAllocationManager(initialTransformationBufferCapacity,1) // item-based
{
   // create draw commands buffer
   _drawIndirectBuffer=new BufferObject(initialDrawIndirectBufferSize,nullptr,GL_DYNAMIC_COPY);
   //_transformationBuffer=new BufferObject(_initialTransformationBufferSize,nullptr,GL_DYNAMIC_DRAW);
   _cpuTransformationBuffer=new float[initialTransformationBufferCapacity*64/sizeof(float)];

   // create Null objects (Null object design pattern)

   // primitiveStorage: null object has count set to zero
   PrimitiveGpuData *psData=static_cast<PrimitiveGpuData*>(
         _primitiveStorage.bufferObject()->map(0,sizeof(PrimitiveGpuData),GL_MAP_WRITE_BIT));
   psData->countAndIndexedFlag=0;
   psData->first=0;
   psData->vertexOffset=0;
   _primitiveStorage.bufferObject()->unmap();

   // drawCommandStorage: null object has assigned empty matrix list
   DrawCommandGpuData *dcData=static_cast<DrawCommandGpuData*>(
         _drawCommandStorage.bufferObject()->map(0,sizeof(DrawCommandGpuData),GL_MAP_WRITE_BIT));
   dcData->primitiveSetOffset4=0;
   dcData->matrixListControlOffset4=0;
   dcData->stateSetOffset4=0;
   _drawCommandStorage.bufferObject()->unmap();

   // matrixListStorage: null object is identity matrix
   float *p1=static_cast<float*>(_matrixStorage.bufferObject()->map(0,sizeof(float)*16,GL_MAP_WRITE_BIT));
   memcpy(p1,identityMatrix,sizeof(float)*16);
   _matrixStorage.bufferObject()->unmap();

   // _matrixListControlStorage: null object points to the null identity matrix in _matrixStorage
   // and its number of matrices is set to zero
   ListControlGpuData *maData=static_cast<ListControlGpuData*>(_matrixListControlStorage.bufferObject()->map(0,sizeof(ListControlGpuData),GL_MAP_WRITE_BIT));
   maData->startIndex=0;
   maData->numItems=0;
   _matrixListControlStorage.bufferObject()->unmap();

   // stateSetStorage: null object points to the zero index in _drawIndirectBuffer
   StateSetGpuData *ssData=static_cast<StateSetGpuData*>(_stateSetStorage.bufferObject()->map(0,sizeof(StateSetGpuData),GL_MAP_WRITE_BIT));
   ssData->drawIndirectBufferOffset=0;
   _stateSetStorage.bufferObject()->unmap();

   // _cpuTransformationBuffer: null object is identity matrix
   memcpy(&_cpuTransformationBuffer[0],identityMatrix,sizeof(float)*16);
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
   // Warn if attribStorage is not already assigned
   if(mesh.attribStorage()==nullptr)
   {
      cerr<<"Error: calling RenderingContext::allocPrimitiveSets() on Mesh\n"
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
                                     int numPrimitives,unsigned startIndex,
                                     bool truncate)
{
   if(mesh.attribStorage()==nullptr)
      return;

   // resize if needed
   int minSizeRequired=numPrimitives+startIndex;
   int currentSize=int(mesh.primitiveList().size());
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
void RenderingContext::setAndUploadPrimitives(Mesh& mesh,PrimitiveGpuData* nonConstBufferData,const Primitive *primitiveList,int numPrimitives)
{
   clearPrimitives(mesh);
   updateVertexOffsets(mesh,nonConstBufferData,primitiveList,numPrimitives);
   uploadPrimitives(mesh,nonConstBufferData,numPrimitives);
   setPrimitives(mesh,primitiveList,numPrimitives);
}


void RenderingContext::updateVertexOffsets(Mesh &mesh,void *primitiveBuffer,
                                           const Primitive *primitiveList,int numPrimitives)
{
   // get index of allocated block
   unsigned vertexOffset;
   if(mesh.indicesDataId()==0)
      vertexOffset=mesh.attribStorage()->vertexAllocationBlock(mesh.verticesDataId()).startIndex;
   else
      vertexOffset=mesh.attribStorage()->indexAllocationBlock(mesh.indicesDataId()).startIndex;

   // update vertexOffset of all primitive sets
   for(int i=0; i<numPrimitives; i++)
   {
      // set PrimitiveSetGpuData::vertexOffset
      unsigned index=primitiveList[i].offset4();
      static_cast<unsigned*>(primitiveBuffer)[index+2]=vertexOffset;
   }
}


vector<Primitive>
RenderingContext::generatePrimitiveList(const unsigned *modesAndOffsets4,int numPrimitives)
{
   vector<Primitive> r;
   r.reserve(numPrimitives);
   for(int i=0,c=numPrimitives*2; i<c; i+=2)
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


ObjectId RenderingContext::createObject(
      Mesh &mesh,
      const unsigned *primitiveIndices,const int primitiveCount,
      MatrixList *ml,StateSet *stateSet)
{
   // numDrawCommands to be created
   unsigned numDrawCommands=primitiveCount!=-1 ? unsigned(primitiveCount)
                                               : unsigned(mesh.primitiveList().size());

   // allocate Object
   Object *obj=Object::alloc(numDrawCommands);
   obj->stateSet=stateSet;
   obj->matrixList=ml;
   obj->numItems=numDrawCommands;

   // reference MatrixList (to prevent it to be released from memory as long as Object exists)
   ml->incrementInstanceRefCounter();

   // allocate draw commands
   _drawCommandStorage.alloc(numDrawCommands,obj->items());

   // iterate through instances
   auto storageDataIterator=stateSet->getOrCreateAttribStorageData(mesh.attribStorage());
   StateSet::AttribStorageData &storageData=storageDataIterator->second;
   auto listControlOffset4=ml->listControlOffset4();
   DrawCommandGpuData* drawCommandBufferPtr=_drawCommandStorage.map(BufferStorageAccess::WRITE);
   for(unsigned i=0; i<numDrawCommands; i++)
   {
      // update DrawCommandGpuData
      DrawCommandGpuData &dcData=drawCommandBufferPtr[obj->item(i).index()];
      unsigned psIndex=primitiveCount==-1 ? i : primitiveIndices[i];
      Primitive pl=mesh.primitiveList()[psIndex];
      dcData.primitiveSetOffset4=_primitiveStorage[mesh.primitivesDataId()].startIndex*
                                 unsigned(sizeof(PrimitiveGpuData)/4) + pl.offset4();
      dcData.matrixListControlOffset4=listControlOffset4;

      // update instance's mode and StateSet counter
      unsigned mode=pl.mode();
      obj->item(i).setMode(mode);
      stateSet->incrementDrawCommandModeCounter(1,mode,storageData);

      // update DrawCommandGpuData::stateSetOffset4 (must be done after incrementing StateSet counter)
      dcData.stateSetOffset4=stateSet->getStateSetBufferOffset4(mode,storageData);
   }
   stateSet->releaseAttribStorageDataIfEmpty(storageDataIterator);

   // insert InstanceGroup into the list of instances
   // and return iterator to it
   mesh.objects().push_front(obj);
   return mesh.objects().begin();
}


void RenderingContext::deleteObject(Mesh &mesh,ObjectId id)
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

   // unreference matrix collection
   id->matrixList->decrementInstanceRefCounter();

   // remove from lists, execute destructors and free memory
   _drawCommandStorage.free(id->items(),id->numItems);
   id->free();
   mesh.objects().erase(id);
}


void RenderingContext::appendTransformationGraph(shared_ptr<Transformation>& transformation)
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
   // and zero all Object::items)
   for(auto it=_primitiveStorage.begin(); it!=_primitiveStorage.end(); it++) {
      Mesh *m=it->owner;
      if(m) {
         m->setAttribStorage(nullptr);
         ObjectList &ol=m->objects();
         for(auto olit=ol.begin(); olit!=ol.end(); olit++) {
            unsigned num=olit->numItems;
            for(unsigned i=0; i<num; i++)
               olit->item(i).data=0;
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
}


void RenderingContext::handleContextLost()
{
   cancelAllAllocations();
}


static void countMatrices(Transformation *t)
{
   MatrixList *ml=t->matrixList().get();
   if(ml) {
      if(ml->restartFlag()) {
         ml->setNumMatrices(1);
         ml->setRestartFlag(false);
      } else {
         ml->setNumMatrices(ml->numMatrices()+1);
      }
   }
   for(auto it=t->childList().begin(); it!=t->childList().end(); it++)
      countMatrices(*it);
}


static void processTransformation(Transformation *t,const glm::mat4& parentMV)
{
   // compute new matrix
   glm::mat4 mv=parentMV*(*reinterpret_cast<glm::mat4*>(t->getMatrixPtr()));

   // update number of matrices and allocated space for them
   MatrixList *ml=t->matrixList().get();
   if(ml)
   {
      if(ml->restartFlag()==false)
      {
         if(ml->numMatrices()!=ml->capacity())
            ml->setCapacity(ml->numMatrices());
         ml->setRestartFlag(true);
         ml->setNumMatrices(0);
      }
      ml->upload(reinterpret_cast<float*>(&mv),1,ml->numMatrices());
      ml->setNumMatrices(ml->numMatrices()+1);
   }

   // process child transformations
   for(auto it=t->childList().begin(); it!=t->childList().end(); it++)
      processTransformation(*it,mv);
}


void RenderingContext::evaluateTransformationGraph()
{
   for(auto it=_transformationGraphs.begin(); it!=_transformationGraphs.end(); it++)
      countMatrices(it->get());

   glm::mat4 mv{}; // identity matrix
   for(auto it=_transformationGraphs.begin(); it!=_transformationGraphs.end(); it++)
      processTransformation(it->get(),mv);
}


void RenderingContext::setupRendering()
{
   _indirectBufferAllocatedSpace4=0;
}


void RenderingContext::render()
{
}


void RenderingContext::setCurrent(const shared_ptr<RenderingContext>& ptr)
{
   NoExport::_currentContext.get()=ptr;
}
