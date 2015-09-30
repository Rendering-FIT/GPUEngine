#ifndef GE_RG_BUFFER_STORAGE_H
#define GE_RG_BUFFER_STORAGE_H

#include <geRG/Export.h>

#include <iostream>
#include <typeinfo>
#include <typeindex>

namespace ge
{
   namespace gl
   {
      class BufferObject;
   }
   namespace rg
   {
      struct NoAllocationManager {};


      template<typename AllocationManagerT=NoAllocationManager,unsigned AllocationItemSize=1>
      class BufferStorage : public AllocationManagerT {
      public:

         enum MappedBufferAccess { READ=0x1, WRITE=0x2, READ_WRITE=0x3, NO_ACCESS=0x0 };

      protected:

         ge::gl::BufferObject* _bufferObject;
         void* _mappedBufferPtr;
         MappedBufferAccess _mappedBufferAccess;

         //template<typename T> static auto test_allocWithPointer(int) -> decltype(std::declval<T>().alloc((unsigned*)nullptr) == 1,std::true_type());
         //template<typename T> static std::false_type test_allocWithPointer(...);

         //template<typename T> static auto test_allocWithPointer(int) -> decltype(std::true_type());
         //template<typename T> static char test_allocWithPointer(int);
         //template<typename T> static std::false_type test_allocWithPointer(...);
         //template<typename T> static int test_allocWithPointer(int);
         //template<typename T> static char test_allocWithPointer(...);
         /*template<typename T> static auto test_allocWithNumAndPointer(int) -> decltype(std::declval<T>().alloc(0u,(unsigned*)nullptr) == 1,std::true_type());
         template<typename T> static std::false_type test_allocWithNumAndPointer(...);
         template<typename T> static auto test_allocWithNumAndOwner(int) -> decltype(std::declval<T>().alloc(0u,*((typename T::AllocationOwner*)nullptr)) == 1,std::true_type());
         template<typename T> static std::false_type test_allocWithNumAndOwner(...);*/
         //static const bool has_allocWithPointer = true;// std::is_same<decltype(test_allocWithPointer<AllocationManagerT>(0)), std::true_type>::value;
         //static const bool has_allocWithNumAndPointer=std::is_same<decltype(test_allocWithNumAndPointer<AllocationManagerT>(0)),std::true_type>::value;
         //static const bool has_allocWithNumAndOwner=std::is_same<decltype(test_allocWithNumAndOwner<AllocationManagerT>(0)),std::true_type>::value;

      public:
         // MSVC 2013 requires following templated structures to be public
         // (other compilers such as g++ and MSVC 2015 does not require this)
         template<typename T,typename P=decltype(std::declval<T>().alloc((unsigned*)nullptr))>
         struct test_allocWithPointer : std::true_type {};
         template<typename T,typename P=decltype(std::declval<T>().alloc(0u,(unsigned*)nullptr))>
         struct test_allocWithNumAndPointer : std::true_type {};
         template<typename T,typename P=decltype(std::declval<T>().alloc(0u,*((typename T::AllocationOwner*)nullptr)))>
         struct test_allocWithNumAndOwner : std::true_type {};

      public:

         BufferStorage(unsigned /*bufferSize*/=0)  {}
         BufferStorage(unsigned capacity,unsigned numNullElements=0)  {}
         BufferStorage(unsigned bufferSize,unsigned allocManagerCapacity,unsigned nullObjectSize=0)  {}

         inline void* map(MappedBufferAccess access=MappedBufferAccess::READ_WRITE);
         inline void* mappedBufferPtr() const;
         inline void unmap();

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

         //template<bool B = std::is_same<ge::rg::BufferStorage<AllocationManagerT>::test_allocWithPointer<AllocationManagerT>(0), std::true_type>::value,
         //template<bool B = std::is_same<test_allocWithPointer<AllocationManagerT>(0), std::true_type>::value,
         //template<typename T=AllocationManagerT,typename=std::enable_if<std::is_function<decltype(int())>::value>::type>
         //template<typename T=AllocationManagerT,typename=std::enable_if<std::is_member_function_pointer<typeof(&T::alloc)>::value>::type>

         /*template<bool B=has_allocWithNumAndPointer,typename std::enable_if<B,int>::type=0>
         void alloc(unsigned numItems,unsigned* ids);
         template<bool B=has_allocWithNumAndOwner,typename std::enable_if<B,int>::type=0,typename A=AllocationManagerT>
         unsigned alloc(unsigned num,typename A::AllocationOwner &owner);*/

      };
   }
}



// inline and template methods

#include <geGL/BufferObject.h>

namespace ge
{
   namespace rg
   {

      template<typename AllocationManagerT,unsigned AllocationItemSize>
      //template<bool B, typename std::enable_if<B, int>::type>
      template<typename,typename>
      void BufferStorage<AllocationManagerT, AllocationItemSize>::alloc(unsigned *id)
      {
         bool r=AllocationManagerT::alloc(id);
         if(r)
            return;

         unsigned c=AllocationManagerT::capacity();
         unsigned newCapacity=(c==0)?4:c*2;
         AllocationManagerT::setCapacity(newCapacity);
         unsigned s=unsigned(_bufferObject->getSize());
         unsigned newSize=newCapacity*AllocationItemSize;
         if(newSize>s)
            _bufferObject->realloc(newSize,ge::gl::BufferObject::KEEP_DATA);
         AllocationManagerT::alloc(id);
      }
      template<typename AllocationManagerT,unsigned AllocationItemSize>
      //template<bool B,typename std::enable_if<B,int>::type>
      template<typename,typename>
      void BufferStorage<AllocationManagerT,AllocationItemSize>::alloc(unsigned numItems,unsigned* ids)
      {
         bool r=AllocationManagerT::alloc(numItems,ids);
         if(r)
            return;

         unsigned c=AllocationManagerT::capacity();
         unsigned newCapacity=(c==0)?4:c*2;
         AllocationManagerT::setCapacity(newCapacity);
         unsigned s=unsigned(_bufferObject->getSize());
         unsigned newSize=newCapacity*AllocationItemSize;
         if(newSize>s)
            _bufferObject->realloc(newSize,ge::gl::BufferObject::KEEP_DATA);
         AllocationManagerT::alloc(numItems,ids);
      }
      template<typename AllocationManagerT,unsigned AllocationItemSize>
      //template<bool B,typename std::enable_if<B,int>::type,typename A>
      template<typename T,typename>
      unsigned BufferStorage<AllocationManagerT,AllocationItemSize>::alloc(unsigned num,typename T::AllocationOwner &owner)
      {
         unsigned id=AllocationManagerT::alloc(num,owner);
         if(id!=0)
            return id;

         unsigned c=AllocationManagerT::capacity();
         unsigned newCapacity=(c==0)?4:c*2;
         AllocationManagerT::setCapacity(newCapacity);
         unsigned s=unsigned(_bufferObject->getSize());
         unsigned newSize=newCapacity*AllocationItemSize;
         if(newSize>s)
            _bufferObject->realloc(newSize,ge::gl::BufferObject::KEEP_DATA);
         return AllocationManagerT::alloc(num,owner);
      }

   }
}

#endif /* GE_RG_BUFFER_STORAGE_H */
