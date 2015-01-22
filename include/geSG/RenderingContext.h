// some includes need to be placed before GE_SG_ATTRIBS_MANAGER_H define
// to prevent problems of circular includes
#include <geSG/AttribConfig.h>
#include <geGL/AsynchronousQueryObject.h>

#ifndef GE_SG_ATTRIBS_MANAGER_H
#define GE_SG_ATTRIBS_MANAGER_H

#include <memory>
#include <set>
#include <geSG/Export.h>
#include <geSG/AllocationManagers.h>

namespace ge
{
   namespace gl
   {
      class BufferObject;
   }
   namespace sg
   {
      class Array;
      class AttribReference;
      class AttribStorage;


      class GE_EXPORT RenderingContext { //: public GraphicsContext,GLContext,...
      public:

         typedef AttribConfig::AttribConfigList AttribConfigList;

      protected:

         AttribConfigList _attribConfigList;
         //StateSetList
         ge::gl::BufferObject *_stateSetBuffer;
         ge::gl::BufferObject *_drawCommandBuffer;
         ge::gl::BufferObject *_instanceBuffer;
         ge::gl::BufferObject *_indirectCommandBuffer;
         AllocationBlockManager _drawCommandAllocationManager;  ///< Allocation manager of blocks of draw commands.
         unsigned _instanceBufferElementsCount;
         unsigned _instanceBufferFreeListFirst;
         unsigned _instanceBufferFreeListLast;
         int _initialDrawCommandBufferSize = 10000; // 10'000 bytes

      public:

         RenderingContext();
         virtual ~RenderingContext();

         inline  const AttribConfigList& getAttribConfigList();
         virtual AttribConfigRef getAttribConfig(const AttribConfig::ConfigData &config);
         inline  AttribConfigRef getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo);
         inline  AttribConfigRef getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,
                                                AttribConfigId id);
         void removeAttribConfig(AttribConfigList::iterator it);

         inline const AllocationBlock& getDrawCommandsAllocationBlock(unsigned id) const;
         inline AllocationBlockManager& getDrawCommandsAllocationManager();
         inline const AllocationBlockManager& getDrawCommandsAllocationManager() const;

         inline unsigned getNumDrawCommandsTotal() const;
         inline unsigned getNumDrawCommandsAvailable() const;
         inline unsigned getNumDrawCommandsAvailableAtTheEnd() const;
         inline unsigned getFirstDrawCommandAvailableAtTheEnd() const;
         inline unsigned getIdOfDrawCommandBlockAtTheEnd() const;

         virtual bool allocDrawCommands(AttribReference &r,unsigned size);
         virtual bool reallocDrawCommands(AttribReference &r,int newSize,
                                          bool preserveContent=true);
         virtual void freeDrawCommands(AttribReference &r);

         void uploadDrawCommands(AttribReference &r,const void *drawCommandBuffer,
                                 unsigned drawCommandBufferSize,
                                 const unsigned *offsetsAndSizes,int numDrawCommands);
         virtual void uploadDrawCommands(AttribReference &r,const void *drawCommandBuffer,
                                         unsigned dstOffset,unsigned size);
         virtual void updateDrawCommandOffsets(AttribReference &r,
                                               const unsigned *offsetsAndSizes,int numDrawCommands,
                                               unsigned startIndex=0,bool truncate=true);
         inline  void clearDrawCommands(AttribReference &r);
         virtual void setNumDrawCommands(AttribReference &r,unsigned num);

         //virtual InstanceID createInstance(AttribReference &r,drawCommandOrAll,MatrixOffset,StateSetOffset);
         //virtual void deleteInstance(AttribReference &r, InstanceID);

         virtual void cancelAllAllocations();
         virtual void handleContextLost();

         static inline std::shared_ptr<RenderingContext>& current();
         static void setCurrent(const std::shared_ptr<RenderingContext>& ptr);

      protected:
         static thread_local std::shared_ptr<RenderingContext> _currentContext;
      };

   }
}



// inline methods
//
// note: they need their own includes that can not be placed on the beginning of this file
//       as there is a circular include reference and the classes need to be defined before
//       inline methods to avoid incomplete type compiler error

#include <geSG/AttribReference.h>

namespace ge
{
   namespace sg
   {
      inline const RenderingContext::AttribConfigList& RenderingContext::getAttribConfigList()  { return _attribConfigList; }
      inline AttribConfigRef RenderingContext::getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo)
      { return getAttribConfig(attribTypes,ebo,AttribConfig::getId(attribTypes,ebo)); }
      inline AttribConfigRef RenderingContext::getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,AttribConfigId id)
      { return getAttribConfig(AttribConfig::ConfigData(attribTypes,ebo,id)); }
      inline const AllocationBlock& RenderingContext::getDrawCommandsAllocationBlock(unsigned id) const  { return _drawCommandAllocationManager[id]; }
      inline AllocationBlockManager& RenderingContext::getDrawCommandsAllocationManager()  { return _drawCommandAllocationManager; }
      inline const AllocationBlockManager& RenderingContext::getDrawCommandsAllocationManager() const  { return _drawCommandAllocationManager; }
      inline unsigned RenderingContext::getNumDrawCommandsTotal() const  { return _drawCommandAllocationManager._numBytesTotal; }
      inline unsigned RenderingContext::getNumDrawCommandsAvailable() const  { return _drawCommandAllocationManager._numBytesAvailable; }
      inline unsigned RenderingContext::getNumDrawCommandsAvailableAtTheEnd() const  { return _drawCommandAllocationManager._numBytesAvailableAtTheEnd; }
      inline unsigned RenderingContext::getFirstDrawCommandAvailableAtTheEnd() const  { return _drawCommandAllocationManager._firstByteAvailableAtTheEnd; }
      inline unsigned RenderingContext::getIdOfDrawCommandBlockAtTheEnd() const  { return _drawCommandAllocationManager._idOfBlockAtTheEnd; }
      inline void RenderingContext::clearDrawCommands(AttribReference &r)  { setNumDrawCommands(r,0); }
      inline std::shared_ptr<RenderingContext>& RenderingContext::current()
      { return _currentContext; }

   }
}

#endif // GE_SG_ATTRIBS_MANAGER_H
