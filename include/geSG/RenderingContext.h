// some includes need to be placed before GE_SG_ATTRIBS_MANAGER_H define
// to prevent problems of circular includes
#include <geSG/AttribConfig.h>
#include <geSG/AttribReference.h>

#ifndef GE_SG_ATTRIBS_MANAGER_H
#define GE_SG_ATTRIBS_MANAGER_H

#include <memory>
#include <geSG/Export.h>
#include <geSG/AllocationManagers.h>
#include <geSG/InstanceGroup.h>

namespace ge
{
   namespace gl
   {
      class BufferObject;
   }
   namespace sg
   {
      class AttribReference;
      class AttribStorage;
      class StateSet;


      class GESG_EXPORT RenderingContext {
      public:

         typedef AttribConfig::AttribConfigList AttribConfigList;
         enum class MappedBufferAccess : uint8_t { READ=0x1, WRITE=0x2, READ_WRITE=0x3, NO_ACCESS=0x0 };

         struct DrawCommandBufferData {
            unsigned mode;
            unsigned count;
            unsigned first;
            unsigned blockOffset;
         };

         struct Instance {
            unsigned drawCommandOffset4;
            unsigned matrixIndex;
            unsigned stateSetDataIndex;
         };

      protected:

         AttribConfigList _attribConfigList;
         //StateSetList
         ge::gl::BufferObject *_stateSetBuffer;
         ge::gl::BufferObject *_drawCommandBuffer;
         ge::gl::BufferObject *_instanceBuffer;
         ge::gl::BufferObject *_indirectCommandBuffer;
         ItemAllocationManager _stateSetBufferAllocationManager;
         ChunkAllocationManager _drawCommandAllocationManager;  ///< Allocation manager of blocks of draw commands.
         InstanceAllocationManager _instanceAllocationManager;  ///< Allocation manager of instances.
         void* _mappedDrawCommandBufferPtr;
         MappedBufferAccess _drawCommandBufferMappedAccess;
         void* _mappedInstanceBufferPtr;
         MappedBufferAccess _instanceBufferMappedAccess;

         static int _initialStateSetBufferNumElements;
         static int _initialDrawCommandBufferSize;
         static int _initialInstanceBufferNumElements;
         static int _initialIndirectCommandBufferSize;

         static void* mapBuffer(void* &_mappedBufferPtr,
                                MappedBufferAccess &currentAccess,
                                ge::gl::BufferObject *buffer,
                                MappedBufferAccess requestedAccess);
         static void unmapBuffer(ge::gl::BufferObject *buffer,
                                 void* &mappedBufferPtr,
                                 MappedBufferAccess &currentAccess);

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

         inline void* mapDrawCommandBuffer(MappedBufferAccess access=MappedBufferAccess::READ_WRITE);
         inline void unmapDrawCommandBuffer();
         inline void* mapInstanceBuffer(MappedBufferAccess access=MappedBufferAccess::READ_WRITE);
         inline void unmapInstanceBuffer();

         inline unsigned* getStateSetBufferAllocation(unsigned id) const;
         inline ItemAllocationManager& getStateSetBufferAllocationManager();
         inline const ItemAllocationManager& getStateSetBufferAllocationManager() const;

         unsigned allocStateSetBufferItem();
         void freeStateSetBufferItem(unsigned id);
         inline unsigned getNumStateSetBufferItemsTotal() const;
         inline unsigned getNumStateSetBufferItemsAvailable() const;
         inline unsigned getNumStateSetBufferItemsAvailableAtTheEnd() const;
         inline unsigned getFirstStateSetBufferItemAvailableAtTheEnd() const;

         inline const ChunkAllocation& getDrawCommandsAllocationBlock(unsigned id) const;
         inline ChunkAllocationManager& getDrawCommandsAllocationManager();
         inline const ChunkAllocationManager& getDrawCommandsAllocationManager() const;

         inline unsigned getNumDrawCommandBytesTotal() const;
         inline unsigned getNumDrawCommandBytesAvailable() const;
         inline unsigned getNumDrawCommandBytesAvailableAtTheEnd() const;
         inline unsigned getFirstDrawCommandAvailableAtTheEnd() const;
         inline unsigned getIdOfDrawCommandBlockAtTheEnd() const;

         inline InstanceData* getInstanceAllocation(unsigned id) const;
         inline ItemAllocationManager& getInstanceAllocationManager();
         inline const ItemAllocationManager& getInstanceAllocationManager() const;

         inline unsigned getNumInstancesTotal() const;
         inline unsigned getNumInstancesAvailable() const;
         inline unsigned getNumInstancesAvailableAtTheEnd() const;
         inline unsigned getFirstInstanceAvailableAtTheEnd() const;

         virtual bool allocDrawCommands(AttribReference &r,unsigned size);
         virtual bool reallocDrawCommands(AttribReference &r,int newSize,
                                          bool preserveContent=true);
         virtual void freeDrawCommands(AttribReference &r);

         virtual void uploadPreprocessedDrawCommands(AttribReference &r,
                                                     const void *drawCommandBuffer,
                                                     unsigned bytesToCopy,unsigned dstOffset=0);
         virtual void setDrawCommandControlData(AttribReference &r,
                                                const AttribReference::DrawCommandControlData *data,
                                                int numDrawCommands,unsigned startIndex=0,
                                                bool truncate=true);
         static void preprocessDrawCommands(AttribReference &r,
                                            void *drawCommandBuffer,
                                            const AttribReference::DrawCommandControlData *data,
                                            int numDrawCommands);
         static std::vector<AttribReference::DrawCommandControlData> generateDrawCommandControlData(
                                            const void *drawCommandBuffer,
                                            const unsigned *offsets4,int numDrawCommands);

         void uploadDrawCommands(AttribReference &r,
                                 void *nonConstDrawCommandBuffer,unsigned bytesToCopy,
                                 const AttribReference::DrawCommandControlData *data,
                                 int numDrawCommands);
         inline void uploadDrawCommands(AttribReference &r,
                                        void *nonConstDrawCommandBuffer,unsigned bytesToCopy,
                                        const unsigned *offsets4,int numDrawCommands);

         inline  void clearDrawCommands(AttribReference &r);
         virtual void setNumDrawCommands(AttribReference &r,unsigned num);

         inline InstanceGroupId createInstances(AttribReference &r,
                                                unsigned matrixIndex,StateSet *stateSet);
         virtual InstanceGroupId createInstances(AttribReference &r,
                                                 const unsigned *drawCommandIndices,
                                                 const int drawCommandsCount,
                                                 unsigned matrixIndex,StateSet *stateSet);
         virtual void deleteInstances(AttribReference &r,InstanceGroupId id);

         virtual void cancelAllAllocations();
         virtual void handleContextLost();

         static inline void setInitialStateSetBufferNumElements(int value);
         static inline int getInitialStateSetBufferNumElements();
         static inline void setInitialDrawCommandBufferSize(int value);
         static inline int getInitialDrawCommandBufferSize();
         static inline void setInitialInstanceBufferNumElements(int value);
         static inline int getInitialInstanceBufferNumElements();
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
      inline void* RenderingContext::mapDrawCommandBuffer(MappedBufferAccess access)
      { return mapBuffer(_mappedDrawCommandBufferPtr,_drawCommandBufferMappedAccess,_drawCommandBuffer,access); }
      inline void RenderingContext::unmapDrawCommandBuffer()
      { unmapBuffer(_drawCommandBuffer,_mappedDrawCommandBufferPtr,_drawCommandBufferMappedAccess); }
      inline void* RenderingContext::mapInstanceBuffer(MappedBufferAccess access)
      { return mapBuffer(_mappedInstanceBufferPtr,_instanceBufferMappedAccess,_instanceBuffer,access); }
      inline void RenderingContext::unmapInstanceBuffer()
      { unmapBuffer(_instanceBuffer,_mappedInstanceBufferPtr,_instanceBufferMappedAccess); }
      inline unsigned* RenderingContext::getStateSetBufferAllocation(unsigned id) const  { return _stateSetBufferAllocationManager[id]; }
      inline ItemAllocationManager& RenderingContext::getStateSetBufferAllocationManager()  { return _stateSetBufferAllocationManager; }
      inline const ItemAllocationManager& RenderingContext::getStateSetBufferAllocationManager() const  { return _stateSetBufferAllocationManager; }
      inline unsigned RenderingContext::getNumStateSetBufferItemsTotal() const  { return _stateSetBufferAllocationManager._numItemsTotal; }
      inline unsigned RenderingContext::getNumStateSetBufferItemsAvailable() const  { return _stateSetBufferAllocationManager._numItemsAvailable; }
      inline unsigned RenderingContext::getNumStateSetBufferItemsAvailableAtTheEnd() const  { return _stateSetBufferAllocationManager._numItemsAvailableAtTheEnd; }
      inline unsigned RenderingContext::getFirstStateSetBufferItemAvailableAtTheEnd() const  { return _stateSetBufferAllocationManager._firstItemAvailableAtTheEnd; }
      inline const ChunkAllocation& RenderingContext::getDrawCommandsAllocationBlock(unsigned id) const  { return _drawCommandAllocationManager[id]; }
      inline ChunkAllocationManager& RenderingContext::getDrawCommandsAllocationManager()  { return _drawCommandAllocationManager; }
      inline const ChunkAllocationManager& RenderingContext::getDrawCommandsAllocationManager() const  { return _drawCommandAllocationManager; }
      inline unsigned RenderingContext::getNumDrawCommandBytesTotal() const  { return _drawCommandAllocationManager._numBytesTotal; }
      inline unsigned RenderingContext::getNumDrawCommandBytesAvailable() const  { return _drawCommandAllocationManager._numBytesAvailable; }
      inline unsigned RenderingContext::getNumDrawCommandBytesAvailableAtTheEnd() const  { return _drawCommandAllocationManager._numBytesAvailableAtTheEnd; }
      inline unsigned RenderingContext::getFirstDrawCommandAvailableAtTheEnd() const  { return _drawCommandAllocationManager._firstByteAvailableAtTheEnd; }
      inline unsigned RenderingContext::getIdOfDrawCommandBlockAtTheEnd() const  { return _drawCommandAllocationManager._idOfBlockAtTheEnd; }
      inline InstanceData* RenderingContext::getInstanceAllocation(unsigned id) const  { return _instanceAllocationManager[id]; }
      inline ItemAllocationManager& RenderingContext::getInstanceAllocationManager()  { return _instanceAllocationManager; }
      inline const ItemAllocationManager& RenderingContext::getInstanceAllocationManager() const  { return _instanceAllocationManager; }
      inline unsigned RenderingContext::getNumInstancesTotal() const  { return _instanceAllocationManager._numItemsTotal; }
      inline unsigned RenderingContext::getNumInstancesAvailable() const  { return _instanceAllocationManager._numItemsAvailable; }
      inline unsigned RenderingContext::getNumInstancesAvailableAtTheEnd() const  { return _instanceAllocationManager._numItemsAvailableAtTheEnd; }
      inline unsigned RenderingContext::getFirstInstanceAvailableAtTheEnd() const  { return _instanceAllocationManager._firstItemAvailableAtTheEnd; }
      inline void RenderingContext::uploadDrawCommands(AttribReference &r,void *nonConstDrawCommandBuffer,unsigned bytesToCopy,const unsigned *offsets4,int numDrawCommands)
      { uploadDrawCommands(r,nonConstDrawCommandBuffer,bytesToCopy,generateDrawCommandControlData(nonConstDrawCommandBuffer,offsets4,numDrawCommands).data(),numDrawCommands); }
      inline void RenderingContext::clearDrawCommands(AttribReference &r)  { setNumDrawCommands(r,0); }
      inline InstanceGroupId RenderingContext::createInstances(AttribReference &r,unsigned matrixIndex,StateSet *stateSet)
      { return createInstances(r,nullptr,-1,matrixIndex,stateSet); }
      inline void RenderingContext::setInitialStateSetBufferNumElements(int value)  { _initialStateSetBufferNumElements=value; }
      inline int RenderingContext::getInitialStateSetBufferNumElements()  { return _initialStateSetBufferNumElements; }
      inline void RenderingContext::setInitialDrawCommandBufferSize(int value)  { _initialDrawCommandBufferSize=value; }
      inline int RenderingContext::getInitialDrawCommandBufferSize()  { return _initialDrawCommandBufferSize; }
      inline void RenderingContext::setInitialInstanceBufferNumElements(int value)  { _initialInstanceBufferNumElements=value; }
      inline int RenderingContext::getInitialInstanceBufferNumElements()  { return _initialInstanceBufferNumElements; }
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
