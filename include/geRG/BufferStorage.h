#ifndef GE_RG_BUFFER_STORAGE_H
#define GE_RG_BUFFER_STORAGE_H

#include <geRG/Export.h>

namespace ge
{
   namespace gl
   {
      class Buffer;
   }
   namespace rg
   {
      /** Helper structure allowing BufferStorage to have no allocation manager.
       */
      struct NoAllocationManager {
         inline NoAllocationManager(unsigned=0)  {}
         inline NoAllocationManager(unsigned,unsigned)  {}
      };


      enum class BufferStorageAccess { READ=0x1, WRITE=0x2, READ_WRITE=0x3, NO_ACCESS=0x0 };
      inline BufferStorageAccess operator|(const BufferStorageAccess a, const BufferStorageAccess b)
      { return BufferStorageAccess(uint8_t(a) | uint8_t(b)); }


      /** BufferStorage template combines the functionality of ge::gl::Buffer
       *  and allocation manager functionality (such as ItemMemoryManager, BlockMemoryManager,
       *  ChunkMemoryManager) into the single class.
       *
       *  BufferStorage maintains buffer (using ge::gl::Buffer) and allows to
       *  allocate data inside it using one of allocation managers. When the buffer
       *  free space is exhausted or gets low, it allows for buffer reallocation.
       */
      template<typename AllocationManagerT=NoAllocationManager,typename Type=char,unsigned AllocationItemSize=sizeof(Type)>
      class BufferStorage : public AllocationManagerT {
      protected:

         std::shared_ptr<ge::gl::Buffer> _buffer;
         Type* _mappedBufferPtr;
         BufferStorageAccess _mappedBufferAccess;

      public:
         // MSVC 2013 requires following templated structures to be public
         // (other compilers such as g++ and MSVC 2015 does not require it)
         template<typename T,typename P=decltype(std::declval<T>().alloc((unsigned*)nullptr))>
         struct test_allocWithPointer : std::true_type {};
         template<typename T,typename P=decltype(std::declval<T>().alloc(0u,(unsigned*)nullptr))>
         struct test_allocWithNumAndPointer : std::true_type {};
         template<typename T,typename P=decltype(std::declval<T>().alloc(0u,*((typename T::AllocationOwner*)nullptr)))>
         struct test_allocWithNumAndOwner : std::true_type {};

      public:

         BufferStorage(unsigned capacity=0,
                       unsigned flags=0x88E8/*GL_DYNAMIC_DRAW*/,void *data=nullptr);
         BufferStorage(unsigned capacity,unsigned nullObjectElements,
                       unsigned flags,void *data=nullptr);
         BufferStorage(unsigned bufferSize,unsigned allocManagerCapacity,unsigned nullObjectElements,
                       unsigned flags,void *data=nullptr);
         virtual ~BufferStorage();

         inline const std::shared_ptr<ge::gl::Buffer>& buffer() const;

         inline Type* ptr() const;
         Type* map(BufferStorageAccess access=BufferStorageAccess::READ_WRITE);
         void unmap();

#if !defined(_MSC_VER)
         // g++ and similar compilers
         template<typename T=AllocationManagerT,typename=typename std::enable_if<test_allocWithPointer<T>::value>::type>
         void alloc(unsigned *id);
         template<typename T=AllocationManagerT,typename=typename std::enable_if<test_allocWithNumAndPointer<T>::value>::type>
         void alloc(unsigned numItems,unsigned* ids);
         template<typename T=AllocationManagerT,typename=typename std::enable_if<test_allocWithNumAndOwner<T>::value>::type>
         unsigned alloc(unsigned num,typename T::AllocationOwner &owner);
#else
         // MSVC-based compilers
         template<typename T=AllocationManagerT,typename=typename std::enable_if<test_allocWithPointer<AllocationManagerT>::value>::type>
         void alloc(unsigned *id);
         template<typename T=AllocationManagerT,typename=typename std::enable_if<test_allocWithNumAndPointer<AllocationManagerT>::value>::type>
         void alloc(unsigned numItems,unsigned* ids);
         template<typename T=AllocationManagerT,typename=typename std::enable_if<test_allocWithNumAndOwner<AllocationManagerT>::value>::type>
         unsigned alloc(unsigned num,typename T::AllocationOwner &owner);
#endif
         virtual void grow(unsigned freeBlockSizeRequest);

      };
   }
}



// inline and template methods

#include <geGL/Buffer.h>
#include <assert.h>

namespace ge
{
   namespace rg
   {

      template<typename AllocationManagerT,typename Type,unsigned AllocationItemSize>
      BufferStorage<AllocationManagerT,Type,AllocationItemSize>::BufferStorage(unsigned capacity,unsigned flags,void *data)
         : AllocationManagerT(capacity)
         , _buffer(std::make_shared<ge::gl::Buffer>(capacity*AllocationItemSize,data,flags))
         , _mappedBufferPtr(nullptr)
         , _mappedBufferAccess(BufferStorageAccess::NO_ACCESS)
      {}

      template<typename AllocationManagerT,typename Type,unsigned AllocationItemSize>
      BufferStorage<AllocationManagerT,Type,AllocationItemSize>::BufferStorage(unsigned capacity,unsigned nullObjectElements,unsigned flags,void *data)
         : AllocationManagerT(capacity,nullObjectElements)
         , _buffer(std::make_shared<ge::gl::Buffer>(capacity*AllocationItemSize,data,flags))
         , _mappedBufferPtr(nullptr)
         , _mappedBufferAccess(BufferStorageAccess::NO_ACCESS)
      {}

      template<typename AllocationManagerT,typename Type,unsigned AllocationItemSize>
      BufferStorage<AllocationManagerT,Type,AllocationItemSize>::BufferStorage(
            unsigned bufferSize,unsigned allocManagerCapacity,unsigned nullObjectElements,unsigned flags,void *data)
         : AllocationManagerT(allocManagerCapacity,nullObjectElements)
         , _buffer(std::make_shared<ge::gl::Buffer>(bufferSize,data,flags))
         , _mappedBufferPtr(nullptr)
         , _mappedBufferAccess(BufferStorageAccess::NO_ACCESS)
      {
         assert(bufferSize>=allocManagerCapacity*AllocationItemSize &&
                "BufferStorage error: Buffer is not large enough to hold all items of AllocationManager.");
      }

      template<typename AllocationManagerT,typename Type,unsigned AllocationItemSize>
      BufferStorage<AllocationManagerT,Type,AllocationItemSize>::~BufferStorage()
      {
      }

      template<typename AllocationManagerT,typename Type,unsigned AllocationItemSize>
      inline const std::shared_ptr<ge::gl::Buffer>& BufferStorage<AllocationManagerT,Type,AllocationItemSize>::buffer() const
      { return _buffer; }

      template<typename AllocationManagerT,typename Type,unsigned AllocationItemSize>
      inline Type* BufferStorage<AllocationManagerT,Type,AllocationItemSize>::ptr() const
      { return _mappedBufferPtr; }

      template<typename AllocationManagerT,typename Type,unsigned AllocationItemSize>
      Type* BufferStorage<AllocationManagerT,Type,AllocationItemSize>::map(BufferStorageAccess requestedAccess)
      {
         if(_mappedBufferAccess==BufferStorageAccess::READ_WRITE ||
            _mappedBufferAccess==requestedAccess ||
            requestedAccess==BufferStorageAccess::NO_ACCESS)
            return _mappedBufferPtr;

         if(_mappedBufferAccess!=BufferStorageAccess::NO_ACCESS)
            _buffer->unmap();

         _mappedBufferAccess=_mappedBufferAccess|requestedAccess;
         _mappedBufferPtr=static_cast<Type*>(_buffer->map(static_cast<GLbitfield>(_mappedBufferAccess)));
         return _mappedBufferPtr;
      }

      template<typename AllocationManagerT,typename Type,unsigned AllocationItemSize>
      void BufferStorage<AllocationManagerT,Type,AllocationItemSize>::unmap()
      {
         if(_mappedBufferAccess==BufferStorageAccess::NO_ACCESS)
            return;

         _buffer->unmap();
         _mappedBufferPtr=nullptr;
         _mappedBufferAccess=BufferStorageAccess::NO_ACCESS;
      }

      template<typename AllocationManagerT,typename Type,unsigned AllocationItemSize>
      template<typename,typename>
      void BufferStorage<AllocationManagerT,Type,AllocationItemSize>::alloc(unsigned *id)
      {
         bool r=AllocationManagerT::alloc(id);
         if(!r) {
            grow(1);
            AllocationManagerT::alloc(id);
         }
      }

      template<typename AllocationManagerT,typename Type,unsigned AllocationItemSize>
      template<typename,typename>
      void BufferStorage<AllocationManagerT,Type,AllocationItemSize>::alloc(unsigned numItems,unsigned* ids)
      {
         bool r=AllocationManagerT::alloc(numItems,ids);
         if(!r) {
            grow(numItems);
            AllocationManagerT::alloc(numItems,ids);
         }
      }

      template<typename AllocationManagerT,typename Type,unsigned AllocationItemSize>
      template<typename T,typename>
      unsigned BufferStorage<AllocationManagerT,Type,AllocationItemSize>::alloc(unsigned num,typename T::AllocationOwner &owner)
      {
         unsigned id=AllocationManagerT::alloc(num,owner);
         if(id==0) {
            grow(num);
            id=AllocationManagerT::alloc(num,owner);
         }
         return id;
      }

      template<typename AllocationManagerT,typename Type,unsigned AllocationItemSize>
      void BufferStorage<AllocationManagerT,Type,AllocationItemSize>::grow(unsigned freeBlockSizeRequest)
      {
         // do we have enough space?
         unsigned largest=AllocationManagerT::largestAvailable();
         if(largest>=freeBlockSizeRequest)
            return;

         // set new capacity
         unsigned capacity=AllocationManagerT::capacity();
         unsigned delta=(capacity==0)?4:capacity; // double the capacity, only if empty set initial size to 4
         if(delta+AllocationManagerT::numItemsAvailableAtTheEnd() < freeBlockSizeRequest)
            delta=freeBlockSizeRequest-AllocationManagerT::numItemsAvailableAtTheEnd();
         unsigned newCapacity=capacity+delta;
         AllocationManagerT::setCapacity(newCapacity);

         // realloc Buffer
         unsigned bufferSize=unsigned(_buffer->getSize());
         unsigned newBufferSize=newCapacity*AllocationItemSize;
         if(newBufferSize>bufferSize) {
            if(_mappedBufferAccess!=BufferStorageAccess::NO_ACCESS)
               _buffer->unmap();
            _buffer->realloc(newBufferSize,ge::gl::Buffer::KEEP_DATA);
            if(_mappedBufferAccess!=BufferStorageAccess::NO_ACCESS)
               _mappedBufferPtr=static_cast<Type*>(_buffer->map(static_cast<GLbitfield>(_mappedBufferAccess)));
         }
      }

   }
}

#endif /* GE_RG_BUFFER_STORAGE_H */
