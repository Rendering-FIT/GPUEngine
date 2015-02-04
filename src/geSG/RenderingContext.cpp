#include <iostream> // for cerr
#include <cstring>
#include <geSG/RenderingContext.h>
#include <geSG/AttribReference.h>
#include <geSG/AttribStorage.h>
#include <geGL/BufferObject.h>

using namespace ge::sg;
using namespace ge::gl;
using namespace std;


thread_local shared_ptr<RenderingContext> RenderingContext::_currentContext;

int RenderingContext::_initialDrawCommandBufferSize = 8000; // 8'000 bytes
int RenderingContext::_initialInstanceBufferSize = 8000; // 8'000 bytes
int RenderingContext::_initialIndirectCommandBufferSize = 8000; // 8'000 bytes



RenderingContext::RenderingContext()
   : _drawCommandAllocationManager(_initialDrawCommandBufferSize)
   , _instanceAllocationManager(_initialInstanceBufferSize)
{
   // create draw commands buffer
   _drawCommandBuffer=new BufferObject(_drawCommandAllocationManager._numBytesTotal,nullptr,GL_DYNAMIC_DRAW);
   _instanceBuffer=new BufferObject(_initialInstanceBufferSize,nullptr,GL_DYNAMIC_DRAW);
   _indirectCommandBuffer=new BufferObject(_initialIndirectCommandBufferSize,nullptr,GL_DYNAMIC_COPY);
}


RenderingContext::~RenderingContext()
{
   cancelAllAllocations();
   for(AttribConfigList::iterator it=_attribConfigList.begin(),nextIt; it!=_attribConfigList.end(); it=nextIt)
   {
      nextIt=it;
      nextIt++;
      if(it->second)
         it->second->deleteAllAttribStorages();
   }
   delete _drawCommandBuffer;
   delete _instanceBuffer;
   delete _indirectCommandBuffer;
}


AttribConfigRef RenderingContext::getAttribConfig(const AttribConfig::ConfigData &config)
{
   // find AttribConfig in _attribConfigList (std::map)
   auto r=_attribConfigList.emplace(config,nullptr);

   // if found, return reference to it
   if(r.second==false)
      return r.first->second->createReference();

   // otherwise create new AttribConfig, put it in _attribConfigList and return reference
   AttribConfig *ac=AttribConfig::getFactory()->create(config,this,r.first);
   r.first->second=ac;
   return ac->createReference();
}


void RenderingContext::removeAttribConfig(AttribConfigList::iterator it)
{
   if(it->second!=NULL)
      it->second->detachFromRenderingContext();
   _attribConfigList.erase(it);
}


/** Allocates the memory for draw commands.
 *
 *  Returns true on success. False on failure, usually caused by absence of
 *  large enough free memory block.
 *
 *  The method does not require active graphics context.
 *
 *  @param r AttribReference that will hold reference to the allocated draw command memory
 *  @param size number of bytes to be allocated
 */
bool RenderingContext::allocDrawCommands(AttribReference &r,unsigned size)
{
   // Warn if attribStorage is not already assigned
   if(r.attribStorage==NULL)
   {
      cerr<<"Error: calling RenderingContext::allocDrawCommands() on AttribReference\n"
            "   that is empty (no vertices and indices allocated)." << endl;
      return false;
   }

   // Warn if already allocated
   if(r.drawCommandBlockId!=0)
   {
      cerr<<"Warning: calling RenderingContext::allocDrawCommands() on AttribReference\n"
            "   that has already allocated draw commands." << endl;
      freeDrawCommands(r);
   }

   if(!_drawCommandAllocationManager.canAllocate(size))
      return false;

   // allocate memory for draw commands (inside AttribStorage's preallocated memory or buffers)
   r.drawCommandBlockId=_drawCommandAllocationManager.alloc(size,r);

   return true;
}


bool RenderingContext::reallocDrawCommands(AttribReference &r,int newSize,bool preserveContent)
{
   // not implemented yet
}


void RenderingContext::freeDrawCommands(AttribReference &r)
{
   // Warn if attribStorage is assigned
   if(r.attribStorage==NULL)
   {
      cerr<<"Error: calling RenderingContext::freeDrawCommands() on AttribReference\n"
            "   that is empty (no vertices and indices allocated)." << endl;
      return;
   }

   // release the memory block
   _drawCommandAllocationManager.free(r.drawCommandBlockId);
   r.drawCommandBlockId=0;
}


/** Sets draw commands for the given AttribReference.
 *
 * The method uploads all draw commands to GPU
 * while updating startIndex of each draw command.
 * Draw commands are given by drawCommandBuffer memory pointer.
 * Each draw command is stored as four unsigned integers followed
 * by arbitrary user data. The first integer specifies GL mode
 * (GL_TRIANGLES, GL_LINE_STRIP, GL_POINT, GL_PATCH, etc.).
 * The second integer gives count - the number of vertices sent for rendering.
 * The third gives the start index within AttribReference allocated block of
 * vertices or indices while the fourth gives the index-offset of the start of
 * the allocated block of vertices or indices within AttribStorage. Thus,
 * the real start index is sum of these two indexes.*/
void RenderingContext::setDrawCommands(AttribReference &r,
                                       const void *drawCommandBuffer,unsigned bytesToCopy,
                                       const unsigned *offsets,int numDrawCommands)
{
   void *p=malloc(bytesToCopy);
   memcpy(p,drawCommandBuffer,bytesToCopy);
   setDrawCommandsOptimized(r,p,bytesToCopy,offsets,numDrawCommands);
   free(p);
}


void RenderingContext::setDrawCommandsOptimized(AttribReference &r,
                                                void *drawCommandBuffer,unsigned bytesToCopy,
                                                const unsigned *offsets,int numDrawCommands)
{
   clearDrawCommands(r);
   updateDrawCommandsBufferData(r,drawCommandBuffer,offsets,numDrawCommands);
   uploadDrawCommands(r,drawCommandBuffer,bytesToCopy);
   updateDrawCommandOffsets(r,offsets,numDrawCommands);
}


void RenderingContext::updateDrawCommandsBufferData(AttribReference &r,
                                                    void *drawCommandBuffer,
                                                    const unsigned *offsets,int numDrawCommands)
{
   // get index of allocated block
   unsigned index;
   if(r.indicesDataId==0)
      index=r.attribStorage->getVertexAllocationBlock(r.verticesDataId).startIndex;
   else
      index=r.attribStorage->getIndexAllocationBlock(r.indicesDataId).startIndex;

   // update start index of all draw commands
   for(int i=0; i<numDrawCommands; i++)
   {
      unsigned pos=offsets[i];
      static_cast<unsigned*>(drawCommandBuffer)[pos+3]=index;
   }
}


void RenderingContext::uploadDrawCommands(AttribReference &r,const void *drawCommandBuffer,
                                          unsigned bytesToCopy,unsigned dstOffset)
{
   if(r.attribStorage==NULL || r.drawCommandBlockId==0)
      return;

   int bufferOffset=dstOffset+_drawCommandAllocationManager[r.drawCommandBlockId].offset;
   _drawCommandBuffer->setData((uint8_t*)drawCommandBuffer,bytesToCopy,bufferOffset);
}


void RenderingContext::updateDrawCommandOffsets(AttribReference &r,
                                                const unsigned *offsets,int numDrawCommands,
                                                unsigned startIndex,bool truncate)
{
   if(r.attribStorage==NULL)
      return;

   // resize if needed
   int minSizeRequired=numDrawCommands+startIndex;
   int currentSize=r.drawCommandOffsets.size();
   if((truncate && currentSize!=minSizeRequired) || minSizeRequired>currentSize)
      r.drawCommandOffsets.resize(minSizeRequired);

   // copy memory
   memmove(r.drawCommandOffsets.data()+startIndex,offsets,numDrawCommands*sizeof(unsigned));
}


void RenderingContext::setNumDrawCommands(AttribReference &r,unsigned num)
{
   if(r.attribStorage==NULL)
      return;

   r.drawCommandOffsets.resize(num);
}


/*InstanceBlockID RenderingContext::createInstances(AttribReference &r,
                                                  const unsigned *drawCommandIndices,
                                                  const unsigned drawCommandsCount,
                                                  unsigned matrixOffset,unsigned stateSetOffset)
{
   FlexibleArray<unsigned,ListItemBase> *instanceBlock;
   unsigned numInstances=drawCommandsCount==-1 ? r.drawCommandOffsets.size() : drawCommandsCount;
   instanceBlock=FlexibleArray<unsigned,ListItemBase>.alloc(numInstances);
   instanceBlock->count=numInstances;
   if(drawCommandsCount==-1)
   {
      
   r.instances
}*/


void RenderingContext::cancelAllAllocations()
{
   // break references from AttribReferences
   for(auto it=_drawCommandAllocationManager.begin(); it!=_drawCommandAllocationManager.end(); it++)
      if(it->owner)
         it->owner->attribStorage=nullptr;

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


void RenderingContext::setCurrent(const std::shared_ptr<RenderingContext>& ptr)
{
   _currentContext=ptr;
}
