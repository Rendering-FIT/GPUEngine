#include <algorithm>
#include <cstring>
#include <iostream> // for cerr
#include <geSG/RenderingContext.h>
#include <geSG/Mesh.h>
#include <geSG/AttribStorage.h>
#include <geSG/StateSet.h>
#include <geSG/InstancingMatrices.h>
#include <geSG/Transformation.h>
#include <geGL/BufferObject.h>

using namespace ge::sg;
using namespace ge::gl;
using namespace std;

thread_local shared_ptr<RenderingContext> RenderingContext::_currentContext;

int RenderingContext::_initialStateSetBufferNumElements = 100; // 800 bytes
int RenderingContext::_initialDrawCommandBufferSize = 8000; // 8'000 bytes
int RenderingContext::_initialInstanceBufferNumElements = 1000; // 12'000 bytes
int RenderingContext::_initialIndirectCommandBufferSize = 20000; // 20'000 bytes
int RenderingContext::_initialTransformationBufferSize = 1280; // 20 matrices (including one reserved
                                                               // matrix for identity), 64*20=1'280 bytes
int RenderingContext::_initialInstancingMatricesControlBufferNumElements = 20; // 20*8=160 bytes
int RenderingContext::_initialInstancingMatricesBufferSize = 1280; // 20 matrices, 64*20=1'280 bytes

const float RenderingContext::identityMatrix[16] = {
   1.f, 0.f, 0.f, 0.f,
   0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 1.f, 0.f,
   0.f, 0.f, 0.f, 1.f,
};



RenderingContext::RenderingContext()
   : _stateSetBufferAllocationManager(_initialStateSetBufferNumElements)
   , _drawCommandAllocationManager(_initialDrawCommandBufferSize)
   , _instanceAllocationManager(_initialInstanceBufferNumElements)
   , _transformationAllocationManager(_initialTransformationBufferSize/64,1)
   , _instancingMatricesControlAllocationManager(_initialInstancingMatricesControlBufferNumElements,1)
   , _instancingMatrixAllocationManager(_initialInstancingMatricesBufferSize/64,1)
   , _stateSetBufferMappedAccess(MappedBufferAccess::NO_ACCESS)
   , _drawCommandBufferMappedAccess(MappedBufferAccess::NO_ACCESS)
   , _instanceBufferMappedAccess(MappedBufferAccess::NO_ACCESS)
   , _instancingMatricesControlBufferMappedAccess(MappedBufferAccess::NO_ACCESS)
   , _instancingMatrixBufferMappedAccess(MappedBufferAccess::NO_ACCESS)
{
   // create draw commands buffer
   _stateSetBuffer=new BufferObject(_initialStateSetBufferNumElements*8,nullptr,GL_DYNAMIC_DRAW);
   _drawCommandBuffer=new BufferObject(_initialDrawCommandBufferSize,nullptr,GL_DYNAMIC_DRAW);
   _instanceBuffer=new BufferObject(_initialInstanceBufferNumElements*12,nullptr,GL_DYNAMIC_DRAW);
   _indirectCommandBuffer=new BufferObject(_initialIndirectCommandBufferSize,nullptr,GL_DYNAMIC_COPY);
   //_transformationBuffer=new BufferObject(_initialTransformationBufferSize,nullptr,GL_DYNAMIC_DRAW);
   _cpuTransformationBuffer=new float[_initialTransformationBufferSize/sizeof(float)];
   _instancingMatricesControlBuffer=new BufferObject(_initialInstancingMatricesControlBufferNumElements*
          sizeof(InstancingMatricesControlGpuData),nullptr,GL_DYNAMIC_DRAW);
   _instancingMatrixBuffer=new BufferObject(_initialInstancingMatricesBufferSize,nullptr,GL_DYNAMIC_COPY);

   // create Null objects (Null object design pattern)
   // _cpuTransformationBuffer: null object is identity matrix
   memcpy(&_cpuTransformationBuffer[0],identityMatrix,sizeof(float)*16);
   // _instancingMatrixBuffer: null object is identity matrix
   float *p1=static_cast<float*>(_instancingMatrixBuffer->map(0,sizeof(float)*16,GL_MAP_WRITE_BIT));
   memcpy(p1,identityMatrix,sizeof(float)*16);
   _instancingMatrixBuffer->unmap();
   // _instancingMatrixControlBuffer: null object points to the null identity matrix in _instancingMatrixBuffer
   unsigned *p2=static_cast<unsigned*>(_instancingMatricesControlBuffer->map(0,sizeof(unsigned)*2,GL_MAP_WRITE_BIT));
   p2[0]=0; // matrixCollectionOffset64
   p2[1]=1; // numMatrices
   _instancingMatricesControlBuffer->unmap();
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
   delete _stateSetBuffer;
   delete _drawCommandBuffer;
   delete _instanceBuffer;
   delete _indirectCommandBuffer;
   //delete _transformationBuffer;
   delete[] _cpuTransformationBuffer;
   delete _instancingMatricesControlBuffer;
   delete _instancingMatrixBuffer;
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


unsigned RenderingContext::allocStateSetBufferItem()
{
   unsigned id;
   if(!_stateSetBufferAllocationManager.alloc(&id))
   {
      // resize buffer here
   }
   return id;
}


void RenderingContext::freeStateSetBufferItem(unsigned id)
{
   _stateSetBufferAllocationManager.free(id);
}


/** Allocates the memory for draw commands.
 *
 *  Returns true on success. False on failure, usually caused by absence of
 *  large enough free memory block.
 *
 *  The method does not require active graphics context.
 *
 *  @param mesh Mesh that will hold reference to the allocated draw command memory
 *  @param size number of bytes to be allocated
 */
bool RenderingContext::allocDrawCommands(Mesh &mesh,unsigned size)
{
   // Warn if attribStorage is not already assigned
   if(mesh.attribStorage()==nullptr)
   {
      cerr<<"Error: calling RenderingContext::allocDrawCommands() on Mesh\n"
            "   that is empty (no vertices and indices allocated)." << endl;
      return false;
   }

   // Warn if already allocated
   if(mesh.drawCommandBlockId()!=0)
   {
      cerr<<"Warning: calling RenderingContext::allocDrawCommands() on Mesh\n"
            "   that has already allocated draw commands." << endl;
      freeDrawCommands(mesh);
   }

   if(!_drawCommandAllocationManager.canAllocate(size))
      return false;

   // allocate memory for draw commands (inside AttribStorage's preallocated memory or buffers)
   unsigned id=_drawCommandAllocationManager.alloc(size,mesh);
   mesh.setDrawCommandBlockId(id);

   return true;
}


bool RenderingContext::reallocDrawCommands(Mesh &mesh,int newSize,bool preserveContent)
{
   // not implemented yet
   return false;
}


void RenderingContext::freeDrawCommands(Mesh &mesh)
{
   // Warn if attribStorage is assigned
   if(mesh.attribStorage()==nullptr)
   {
      cerr<<"Error: calling RenderingContext::freeDrawCommands() on Mesh\n"
            "   that is empty (no vertices and indices allocated)." << endl;
      return;
   }

   // release the memory block
   _drawCommandAllocationManager.free(mesh.drawCommandBlockId());
   mesh.setDrawCommandBlockId(0);
}


/** Uploads raw draw commands data to GPU buffers. */
void RenderingContext::uploadPreprocessedDrawCommands(Mesh &r,
                                                      const void *drawCommandBuffer,
                                                      unsigned bytesToCopy,unsigned dstOffset)
{
   if(r.attribStorage()==nullptr || r.drawCommandBlockId()==0)
      return;

   int bufferOffset=dstOffset+_drawCommandAllocationManager[r.drawCommandBlockId()].offset;
   _drawCommandBuffer->setData((uint8_t*)drawCommandBuffer,bytesToCopy,bufferOffset);
}


/* Sets draw command control data (the data that are kept on CPU memory). */
void RenderingContext::setDrawCommandControlData(Mesh &mesh,
                                                 const Mesh::DrawCommandControlData *data,
                                                 int numDrawCommands,unsigned startIndex,
                                                 bool truncate)
{
   if(mesh.attribStorage()==nullptr)
      return;

   // resize if needed
   int minSizeRequired=numDrawCommands+startIndex;
   int currentSize=int(mesh.drawCommandControlData().size());
   if((truncate && currentSize!=minSizeRequired) || minSizeRequired>currentSize)
      mesh.drawCommandControlData().resize(minSizeRequired);

   // copy memory
   memmove(mesh.drawCommandControlData().data()+startIndex,data,
           numDrawCommands*sizeof(Mesh::DrawCommandControlData));
}


void RenderingContext::preprocessDrawCommands(Mesh &mesh,
                                              void *drawCommandBuffer,
                                              const Mesh::DrawCommandControlData *data,
                                              int numDrawCommands)
{
   // get index of allocated block
   unsigned blockOffset;
   if(mesh.indicesDataId()==0)
      blockOffset=mesh.attribStorage()->vertexAllocationBlock(mesh.verticesDataId()).startIndex;
   else
      blockOffset=mesh.attribStorage()->indexAllocationBlock(mesh.indicesDataId()).startIndex;

   // update blockOffset of all draw commands
   for(int i=0; i<numDrawCommands; i++)
   {
      // set DrawCommandBufferData::blockOffset
      unsigned index=data[i].offset4();
      static_cast<unsigned*>(drawCommandBuffer)[index+2]=blockOffset;
   }
}


vector<Mesh::DrawCommandControlData>
RenderingContext::generateDrawCommandControlData(const void *drawCommandBuffer,
                                                 const unsigned *modesAndOffsets4,int numDrawCommands)
{
   vector<Mesh::DrawCommandControlData> r;
   r.reserve(numDrawCommands);
   for(int i=0,c=numDrawCommands*2; i<c; i+=2)
   {
      r.emplace_back(modesAndOffsets4[i+1],modesAndOffsets4[i+0]);
   }
   return r;
}


/** Uploads draw commands and sets their control data.
 *
 * The method uploads all draw commands to GPU
 * and sets the control data of each draw command.
 *
 * Each draw command is stored in nonConstDrawCommandBuffer
 * as four unsigned integers followed
 * by arbitrary user data. The first integer specifies GL mode
 * (GL_TRIANGLES, GL_LINE_STRIP, GL_POINT, GL_PATCH, etc.).
 * The second integer gives count - the number of vertices sent for rendering.
 * The third gives the start index within Mesh allocated block of
 * vertices or indices while the fourth gives the index-offset of the start of
 * the allocated block of vertices or indices within AttribStorage. Thus,
 * the real start index is sum of these two indexes.
 * Arbitrary amount of user defined data may follow, that might be used
 * for GPU-based frustum culling, automatic LOD, etc.
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
void RenderingContext::uploadDrawCommands(Mesh &mesh,
                                          void *nonConstDrawCommandBuffer,unsigned bytesToCopy,
                                          const Mesh::DrawCommandControlData *data,
                                          int numDrawCommands)
{
   clearDrawCommands(mesh);
   preprocessDrawCommands(mesh,nonConstDrawCommandBuffer,data,numDrawCommands);
   uploadPreprocessedDrawCommands(mesh,nonConstDrawCommandBuffer,bytesToCopy);
   setDrawCommandControlData(mesh,data,numDrawCommands);
}


void RenderingContext::setNumDrawCommands(Mesh &mesh,unsigned num)
{
   if(mesh.attribStorage()==nullptr)
      return;

   mesh.drawCommandControlData().resize(num);
}


InstanceGroupId RenderingContext::createInstances(
      Mesh &mesh,
      const unsigned *drawCommandIndices,const int drawCommandsCount,
      InstancingMatrices *im,StateSet *stateSet)
{
   // numInstances to be created
   unsigned numInstances=drawCommandsCount!=-1 ? unsigned(drawCommandsCount)
                                               : unsigned(mesh.drawCommandControlData().size());

   // make sure we have enough space
   if(!_instanceAllocationManager.canAllocate(numInstances))
      return mesh.instances().end();

   // allocate InstanceGroup
   InstanceGroup *ig=InstanceGroup::alloc(numInstances);
   ig->stateSet=stateSet;
   ig->instancingMatrices=im;
   ig->count=numInstances;

   // reference matrix collection (to prevent it to be released from memory)
   im->incrementInstanceRefCounter();

   // allocate items in allocation manager
   _instanceAllocationManager.alloc(numInstances,ig->items);

   // iterate through instances
   auto storageDataIterator=stateSet->getOrCreateAttribStorageData(mesh.attribStorage());
   StateSet::AttribStorageData &storageData=storageDataIterator->second;
   auto instancingMatricesControlOffset4=im->controlDataOffset4();
   mapInstanceBuffer(MappedBufferAccess::WRITE);
   for(unsigned i=0; i<numInstances; i++)
   {
      // update instanceBuffer
      Instance &instance=static_cast<Instance*>(_mappedInstanceBufferPtr)[ig->items[i].index()];
      unsigned dcIndex=drawCommandsCount==-1 ? i : drawCommandIndices[i];
      Mesh::DrawCommandControlData dccd=mesh.drawCommandControlData()[dcIndex];
      instance.drawCommandOffset4=_drawCommandAllocationManager[mesh.drawCommandBlockId()].offset/4+
                                  dccd.offset4();
      instance.instancingMatricesControlOffset4=instancingMatricesControlOffset4;

      // update instance's mode and StateSet counter
      unsigned mode=dccd.mode();
      ig->items[i].setMode(mode);
      stateSet->incrementDrawCommandModeCounter(1,mode,storageData);

      // set stateSet offset (must be done after incrementing StateSet counter)
      instance.stateSetDataOffset4=stateSet->getStateSetBufferOffset4(mode,storageData);
   }
   stateSet->releaseAttribStorageDataIfEmpty(storageDataIterator);

   // insert InstanceGroup into the list of instances
   // and return iterator to it
   mesh.instances().push_front(ig);
   return mesh.instances().begin();
}


void RenderingContext::deleteInstances(Mesh &r,InstanceGroupId id)
{
   // iterate through instances
   StateSet *stateSet=id->stateSet;
   auto storageDataIterator=stateSet->getOrCreateAttribStorageData(r.attribStorage());
   StateSet::AttribStorageData &storageData=storageDataIterator->second;
   for(unsigned i=0,c=id->count; i<c; i++)
   {
      // update StateSet counter
      stateSet->decrementDrawCommandModeCounter(1,id->items[i].mode(),storageData);
   }
   stateSet->releaseAttribStorageDataIfEmpty(storageDataIterator);

   // unreference matrix collection
   id->instancingMatrices->decrementInstanceRefCounter();

   // remove from lists, execute destructors and free memory
   _instanceAllocationManager.free(id->items,id->count);
   id->free();
   r.instances().erase(id);
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
   // break Mesh references to DrawCommands
   for(auto it=_drawCommandAllocationManager.begin(); it!=_drawCommandAllocationManager.end(); it++)
      if(it->owner)
         it->owner->setAttribStorage(nullptr);

   // empty allocation maps
   _drawCommandAllocationManager.clear();
   _instanceAllocationManager.clear();

   // break references in all AttribStorages
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
   InstancingMatrices *im=t->instancingMatrices().get();
   if(im) {
      if(im->matrixCounterResetFlag()) {
         im->setMatrixCounter(1);
         im->setMatrixCounterResetFlag(false);
      } else {
         im->setMatrixCounter(im->matrixCounter()+1);
      }
   }
   for(auto it=t->getChildList().begin(); it!=t->getChildList().end(); it++)
   {
      countMatrices(it->get());
   }
}


static void processTransformation(Transformation *t,glm::mat4 parentMV)
{
   // compute new matrix
   glm::mat4 mv=parentMV*(*reinterpret_cast<glm::mat4*>(t->getMatrixPtr()));

   // update number of matrices and allocated space for them
   InstancingMatrices *im=t->instancingMatrices().get();
   if(im)
   {
      if(im->matrixCounterResetFlag()==false)
      {
         if(im->matrixCounter()!=im->numMatricesAllocated()) {
            im->updateGpuControlData(im->matrixCounter());
            im->setNumMatricesAllocated(im->matrixCounter());
         }
         im->setMatrixCounterResetFlag(true);
         im->setMatrixCounter(0);
      }
      im->uploadMatrices(reinterpret_cast<float*>(&mv),1,im->matrixCounter());
      im->setMatrixCounter(im->matrixCounter()+1);
   }

   // process child transformations
   for(auto it=t->getChildList().begin(); it!=t->getChildList().end(); it++)
   {
      processTransformation(it->get(),mv);
   }
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
   _currentContext=ptr;
}
