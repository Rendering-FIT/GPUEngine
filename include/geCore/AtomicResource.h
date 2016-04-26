#pragma once

#include<geCore/Resource.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT AtomicResource: public Resource{
      protected:
        std::shared_ptr<char>_data   = nullptr;
        size_t               _offset = 0u     ;
        static void _callDestructors(
            char*                                    ptr    ,
            TypeRegister::TypeID                     id     ,
            std::shared_ptr<const TypeRegister>const&manager);
      public:
        AtomicResource(AtomicResource const& ac);
        AtomicResource(
            std::shared_ptr<TypeRegister>const&manager = nullptr                   ,
            const void*                        data    = nullptr                   ,
            TypeRegister::TypeID               id      = TypeRegister::UNREGISTERED,
            size_t                             offset  = 0                         );
        AtomicResource(
            std::shared_ptr<TypeRegister>const&manager                             ,
            std::shared_ptr<char>const&        data                                ,
            TypeRegister::TypeID               id      = TypeRegister::UNREGISTERED,
            size_t                             offset  = 0                         );
        AtomicResource(
            std::shared_ptr<TypeRegister>const&manager,
            TypeRegister::TypeID               id     );
        template<typename TYPE>
          AtomicResource(TYPE val,std::shared_ptr<TypeRegister>const&manager);
        virtual ~AtomicResource();
        virtual void*getData()const;
        virtual void const*getDataAddress()const;
        virtual std::shared_ptr<Resource> operator[](TypeRegister::DescriptionIndex elem)const;
        virtual TypeRegister::DescriptionElement getNofElements()const;
        const void*getPointer()const;
        virtual std::string data2Str()const;
        template<typename T>
          AtomicResource& operator=(const T&data);
        template<typename T>
          operator T&()const;
        template<typename T>
          operator T*()const;
        template<typename T>
          operator T**()const;
        template<typename CLASS,typename... ARGS>
          void callConstructor(ARGS... args);
        void callDestructor();
    };

    template<typename TYPE>
      AtomicResource::AtomicResource(TYPE val,std::shared_ptr<TypeRegister>const&manager){
        this->_id      = manager->getTypeId(TypeRegister::getTypeKeyword<TYPE>());
        this->_manager = manager;
        ge::core::TypeRegister::TypeID id=this->_id;
        this->_data    = std::shared_ptr<char>((char*)manager->alloc(this->_id),[id,manager](char*ptr){AtomicResource::_callDestructors(ptr,id,manager);delete[]ptr;});
        this->_offset  = 0;
        (*this)=val;
      }

    template<typename T>
      AtomicResource& AtomicResource::operator=(const T&data){
        *((T*)this->getData()) = data;
        return *this;
      }
    template<typename T>
      AtomicResource::operator T&()const{
        return *((T*)this->getData());
      }
    template<typename T>
      AtomicResource::operator T*()const{
        return (T*)this->getData();
      }
    template<typename T>
      AtomicResource::operator T**()const{
        return (T**)this->getDataAddress();
      }

    template<typename CLASS,typename... ARGS>
      void AtomicResource::callConstructor(ARGS... args){
        new(this->getData())CLASS(args...);
      }

    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResourceTypeID(TypeID id,ARGS... args)const{
        auto ptr=std::make_shared<AtomicResource>(std::const_pointer_cast<TypeRegister>(this->shared_from_this()),this->alloc(id),id);
        ptr->callConstructor<CLASS>(args...);
        return ptr;
      }



  }
}
