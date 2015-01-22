#include <iostream> // for cerr
#include <geSG/RenderingContext.h>
#include <geSG/AttribReference.h>
#include <geSG/AttribStorage.h>
#include <geGL/BufferObject.h>

using namespace ge::sg;
using namespace ge::gl;
using namespace std;


thread_local shared_ptr<RenderingContext> RenderingContext::_currentContext;



RenderingContext::RenderingContext()
   : _drawCommandAllocationManager(_initialDrawCommandBufferSize)
{
   // create draw commands buffer
   _drawCommandBuffer=new BufferObject(_drawCommandAllocationManager._numBytesTotal,NULL,GL_DYNAMIC_DRAW);
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


void RenderingContext::uploadDrawCommands(AttribReference &r,const void *drawCommandBuffer,
                                       unsigned drawCommandBufferSize,
                                       const unsigned *offsetsAndSizes,int numDrawCommands)
{
   clearDrawCommands(r);
   uploadDrawCommands(r,drawCommandBuffer,0,drawCommandBufferSize);
   updateDrawCommandOffsets(r,offsetsAndSizes,numDrawCommands);
}


void RenderingContext::uploadDrawCommands(AttribReference &r,const void *drawCommandBuffer,
                                       unsigned dstOffset,unsigned size)
{
   if(r.attribStorage==NULL)
      return;

   //...
   //int srcOffset=fromIndex*sizeof(DrawCommandData);
   //int dstOffset=(_drawCommandsAllocationMap[r.drawCommandsId].startIndex+fromIndex)*sizeof(DrawCommandData);
   //_drawCommands->setData(((uint8_t*)drawCommands)+srcOffset,numDrawCommands,dstOffset);
}


void RenderingContext::updateDrawCommandOffsets(AttribReference &r,
                                             const unsigned *offsetsAndSizes,int numDrawCommands,
                                             unsigned startIndex,bool truncate)
{
   if(r.attribStorage==NULL)
      return;

   //...
}


void RenderingContext::setNumDrawCommands(AttribReference &r,unsigned num)
{
   if(r.attribStorage==NULL)
      return;

   //...
}


void RenderingContext::cancelAllAllocations()
{
   // break references from AttribReferences
   for(auto it=_drawCommandAllocationManager.begin(); it!=_drawCommandAllocationManager.end(); it++)
      if(it->owner)
         it->owner->attribStorage=nullptr;

   // empty allocation map
   _drawCommandAllocationManager.clear();

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
