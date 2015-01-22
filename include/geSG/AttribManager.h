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


      class GE_EXPORT AttribManager { // RenderingContext //: public GraphicsContext GLContext
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

      public:

         AttribManager();
         virtual ~AttribManager();

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

         static inline std::shared_ptr<AttribManager>& instance();
         static void setInstance(std::shared_ptr<AttribManager>& ptr);

      protected:
         static std::shared_ptr<AttribManager> _instance;
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
      inline const AttribManager::AttribConfigList& AttribManager::getAttribConfigList()  { return _attribConfigList; }
      inline AttribConfigRef AttribManager::getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo)
      { return getAttribConfig(attribTypes,ebo,AttribConfig::getId(attribTypes,ebo)); }
      inline AttribConfigRef AttribManager::getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,AttribConfigId id)
      { return getAttribConfig(AttribConfig::ConfigData(attribTypes,ebo,id)); }
      inline const AllocationBlock& AttribManager::getDrawCommandsAllocationBlock(unsigned id) const  { return _drawCommandAllocationManager[id]; }
      inline AllocationBlockManager& AttribManager::getDrawCommandsAllocationManager()  { return _drawCommandAllocationManager; }
      inline const AllocationBlockManager& AttribManager::getDrawCommandsAllocationManager() const  { return _drawCommandAllocationManager; }
      inline unsigned AttribManager::getNumDrawCommandsTotal() const  { return _drawCommandAllocationManager._numBytesTotal; }
      inline unsigned AttribManager::getNumDrawCommandsAvailable() const  { return _drawCommandAllocationManager._numBytesAvailable; }
      inline unsigned AttribManager::getNumDrawCommandsAvailableAtTheEnd() const  { return _drawCommandAllocationManager._numBytesAvailableAtTheEnd; }
      inline unsigned AttribManager::getFirstDrawCommandAvailableAtTheEnd() const  { return _drawCommandAllocationManager._firstByteAvailableAtTheEnd; }
      inline unsigned AttribManager::getIdOfDrawCommandBlockAtTheEnd() const  { return _drawCommandAllocationManager._idOfBlockAtTheEnd; }
      inline void AttribManager::clearDrawCommands(AttribReference &r)  { setNumDrawCommands(r,0); }
      inline std::shared_ptr<AttribManager>& AttribManager::instance()
      { return _instance; }

   }
}

#endif // GE_SG_ATTRIBS_MANAGER_H
