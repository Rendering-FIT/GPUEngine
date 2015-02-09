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
#include <geSG/FlexibleArrayList.h>

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
         typedef FlexibleArray<unsigned,ListItemBase> InstanceGroup;
         typedef FlexibleArrayList<InstanceGroup> InstanceGroupList;
         typedef InstanceGroupList::iterator InstanceGroupId;
         enum class MappedBufferAccess : uint8_t { READ=0x1, WRITE=0x2, READ_WRITE=0x3, NO_ACCESS=0x0 };

         struct Instance {
            unsigned drawCommandOffset;
            unsigned matrixOffset;
            unsigned stateSetOffset;
         };

      protected:

         AttribConfigList _attribConfigList;
         //StateSetList
         ge::gl::BufferObject *_stateSetBuffer;
         ge::gl::BufferObject *_drawCommandBuffer;
         ge::gl::BufferObject *_instanceBuffer;
         ge::gl::BufferObject *_indirectCommandBuffer;
         ChunkAllocationManager _drawCommandAllocationManager;  ///< Allocation manager of blocks of draw commands.
         ItemAllocationManager _instanceAllocationManager;  ///< Allocation manager of instances.
         void* _mappedInstanceBufferPtr;
         MappedBufferAccess _instanceBufferMappedAccess;

         static int _initialDrawCommandBufferSize;
         static int _initialInstanceBufferSize;
         static int _initialIndirectCommandBufferSize;

      public:

         RenderingContext();
         virtual ~RenderingContext();

         inline  const AttribConfigList& getAttribConfigList();
         virtual AttribConfigRef getAttribConfig(const AttribConfig::ConfigData &config);
         inline  AttribConfigRef getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo);
         inline  AttribConfigRef getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,
                                                AttribConfigId id);
         void removeAttribConfig(AttribConfigList::iterator it);

         inline ge::gl::BufferObject* getDrawCommandBuffer();      ///< Returns the buffer containing draw commands of this graphics context. Any modification to the buffer must be done carefully to not break internal data consistency.
         inline ge::gl::BufferObject* getInstanceBuffer();         ///< Returns the buffer containing instances. Any modification to the buffer must be done carefully to not break internal data consistency.
         inline ge::gl::BufferObject* getIndirectCommandBuffer();  ///< Returns indirect command buffer used for indirect rendering.

         void* mapInstanceBuffer(MappedBufferAccess access=MappedBufferAccess::READ_WRITE);
         void unmapInstanceBuffer();

         inline const ChunkAllocation& getDrawCommandsAllocationBlock(unsigned id) const;
         inline ChunkAllocationManager& getDrawCommandsAllocationManager();
         inline const ChunkAllocationManager& getDrawCommandsAllocationManager() const;

         inline unsigned getNumDrawCommandsTotal() const;
         inline unsigned getNumDrawCommandsAvailable() const;
         inline unsigned getNumDrawCommandsAvailableAtTheEnd() const;
         inline unsigned getFirstDrawCommandAvailableAtTheEnd() const;
         inline unsigned getIdOfDrawCommandBlockAtTheEnd() const;

         virtual bool allocDrawCommands(AttribReference &r,unsigned size);
         virtual bool reallocDrawCommands(AttribReference &r,int newSize,
                                          bool preserveContent=true);
         virtual void freeDrawCommands(AttribReference &r);

         void setDrawCommands(AttribReference &r,
                              const void *drawCommandBuffer,unsigned bytesToCopy,
                              const unsigned *offsets,int numDrawCommands);
         void setDrawCommandsOptimized(AttribReference &r,
                                       void *drawCommandBuffer,unsigned bytesToCopy,
                                       const unsigned *offsets,int numDrawCommands);
         virtual void updateDrawCommandsBufferData(AttribReference &r,
                                                   void *drawCommandBuffer,
                                                   const unsigned *offsets,int numDrawCommands);
         virtual void uploadDrawCommands(AttribReference &r,const void *drawCommandBuffer,
                                         unsigned bytesToCopy,unsigned dstOffset=0);
         virtual void updateDrawCommandOffsets(AttribReference &r,
                                               const unsigned *offsets,int numDrawCommands,
                                               unsigned startIndex=0,bool truncate=true);
         inline  void clearDrawCommands(AttribReference &r);
         virtual void setNumDrawCommands(AttribReference &r,unsigned num);

         inline InstanceGroupId createInstances(AttribReference &r,
                                                unsigned matrixOffset,unsigned stateSetOffset);
         virtual InstanceGroupId createInstances(AttribReference &r,
                                                 const unsigned *drawCommandIndices,
                                                 const unsigned drawCommandsCount,
                                                 unsigned matrixOffset,unsigned stateSetOffset);
         virtual void deleteInstances(AttribReference &r,InstanceGroupId id);

         virtual void cancelAllAllocations();
         virtual void handleContextLost();

         static inline void setInitialDrawCommandBufferSize(int value);
         static inline int getInitialDrawCommandBufferSize();
         static inline void setInitialInstanceBufferSize(int value);
         static inline int getInitialInstanceBufferSize();
         static inline void setInitialIndirectCommandBufferSize(int value);
         static inline int getInitialIndirectCommandBufferSize();

         static inline std::shared_ptr<RenderingContext>& current();
         static void setCurrent(const std::shared_ptr<RenderingContext>& ptr);

      protected:
         static thread_local std::shared_ptr<RenderingContext> _currentContext;
      };


      inline RenderingContext::MappedBufferAccess& operator|=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b);
      inline RenderingContext::MappedBufferAccess& operator&=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b);
      inline RenderingContext::MappedBufferAccess& operator+=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b);
      inline RenderingContext::MappedBufferAccess& operator-=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b);
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
      inline ge::gl::BufferObject* RenderingContext::getDrawCommandBuffer()  { return _drawCommandBuffer; }
      inline ge::gl::BufferObject* RenderingContext::getInstanceBuffer()  { return _instanceBuffer; }
      inline ge::gl::BufferObject* RenderingContext::getIndirectCommandBuffer()  { return _indirectCommandBuffer; }
      inline const ChunkAllocation& RenderingContext::getDrawCommandsAllocationBlock(unsigned id) const  { return _drawCommandAllocationManager[id]; }
      inline ChunkAllocationManager& RenderingContext::getDrawCommandsAllocationManager()  { return _drawCommandAllocationManager; }
      inline const ChunkAllocationManager& RenderingContext::getDrawCommandsAllocationManager() const  { return _drawCommandAllocationManager; }
      inline unsigned RenderingContext::getNumDrawCommandsTotal() const  { return _drawCommandAllocationManager._numBytesTotal; }
      inline unsigned RenderingContext::getNumDrawCommandsAvailable() const  { return _drawCommandAllocationManager._numBytesAvailable; }
      inline unsigned RenderingContext::getNumDrawCommandsAvailableAtTheEnd() const  { return _drawCommandAllocationManager._numBytesAvailableAtTheEnd; }
      inline unsigned RenderingContext::getFirstDrawCommandAvailableAtTheEnd() const  { return _drawCommandAllocationManager._firstByteAvailableAtTheEnd; }
      inline unsigned RenderingContext::getIdOfDrawCommandBlockAtTheEnd() const  { return _drawCommandAllocationManager._idOfBlockAtTheEnd; }
      inline void RenderingContext::clearDrawCommands(AttribReference &r)  { setNumDrawCommands(r,0); }
      inline RenderingContext::InstanceGroupId RenderingContext::createInstances(AttribReference &r,unsigned matrixOffset,unsigned stateSetOffset)
      { return createInstances(r,nullptr,-1,matrixOffset,stateSetOffset); }
      inline void RenderingContext::setInitialDrawCommandBufferSize(int value)  { _initialDrawCommandBufferSize=value; }
      inline int RenderingContext::getInitialDrawCommandBufferSize()  { return _initialDrawCommandBufferSize; }
      inline void RenderingContext::setInitialInstanceBufferSize(int value)  { _initialInstanceBufferSize=value; }
      inline int RenderingContext::getInitialInstanceBufferSize()  { return _initialInstanceBufferSize; }
      inline void RenderingContext::setInitialIndirectCommandBufferSize(int value)  { _initialIndirectCommandBufferSize=value; }
      inline int RenderingContext::getInitialIndirectCommandBufferSize()  { return _initialIndirectCommandBufferSize; }
      inline std::shared_ptr<RenderingContext>& RenderingContext::current()
      { return _currentContext; }

      inline RenderingContext::MappedBufferAccess& operator|=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b)
      { (uint8_t&)a|=(uint8_t)b; return a; }
      inline RenderingContext::MappedBufferAccess& operator&=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b)
      { (uint8_t&)a&=(uint8_t)b; return a; }
      inline RenderingContext::MappedBufferAccess& operator+=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b)
      { (uint8_t&)a|=(uint8_t)b; return a; }
      inline RenderingContext::MappedBufferAccess& operator-=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b)
      { (uint8_t&)a&=(uint8_t)b; return a; }

   }
}

#endif // GE_SG_ATTRIBS_MANAGER_H
