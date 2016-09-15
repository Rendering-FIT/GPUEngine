#pragma once

#include<geDE/Resource.h>

namespace ge{
  namespace de{
    class GEDE_EXPORT AtomicResource: public Resource{
      protected:
        std::shared_ptr<uint8_t>_data   = nullptr;
        size_t                  _offset = 0u     ;
        static void _callDestructors(
            uint8_t*                                 ptr    ,
            TypeId                                   id     ,
            std::shared_ptr<const TypeRegister>const&manager);
      public:
        AtomicResource(AtomicResource const& ac);
        AtomicResource(
            std::shared_ptr<TypeRegister>const&manager = nullptr                   ,
            const void*                        data    = nullptr                   ,
            TypeId                             id      = TypeRegister::UNREGISTERED,
            size_t                             offset  = 0                         );
        AtomicResource(
            std::shared_ptr<TypeRegister>const&manager                             ,
            std::shared_ptr<uint8_t>const&     data                                ,
            TypeId                             id      = TypeRegister::UNREGISTERED,
            size_t                             offset  = 0                         );
        AtomicResource(
            std::shared_ptr<TypeRegister>const&manager,
            TypeId                             id     );
        template<typename TYPE>
          AtomicResource(TYPE val,std::shared_ptr<TypeRegister>const&manager);
        virtual ~AtomicResource();
        virtual void*getData()const override;
        virtual void const*getDataAddress()const override;
        virtual uint8_t getByte(size_t offset)const override;
        virtual void setByte(size_t offset,uint8_t byte)override;
        virtual std::shared_ptr<Resource> operator[](size_t elem)override;
        virtual size_t getNofElements()const override;
        const void*getPointer()const;
        virtual std::string data2Str()const override;
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
/*
    template<typename TYPE>
      AtomicResource::AtomicResource(TYPE val,std::shared_ptr<TypeRegister>const&manager){
        this->_id      = manager->getTypeId(TypeRegister::getTypeKeyword<TYPE>());
        this->_manager = manager;
        ge::de::TypeId id=this->_id;
        this->_data    = std::shared_ptr<char>((char*)manager->alloc(this->_id),[id,manager](char*ptr){AtomicResource::_callDestructors(ptr,id,manager);delete[]ptr;});
        this->_offset  = 0;
        (*this)=val;
      }
*/
    template<typename T>
      AtomicResource& AtomicResource::operator=(const T&data){
        assert(this!=nullptr);
        assert(this->getData()!=nullptr);
        *((T*)this->getData()) = data;
        return *this;
      }
    template<typename T>
      AtomicResource::operator T&()const{
        assert(this!=nullptr);
        assert(this->getData()!=nullptr);
        return *((T*)this->getData());
      }
    template<typename T>
      AtomicResource::operator T*()const{
        assert(this!=nullptr);
        assert(this->getData()!=nullptr);
        return *(T**)this->getData();
      }
    template<typename T>
      AtomicResource::operator T**()const{
        assert(this!=nullptr);
        return (T**)this->getDataAddress();
      }

    template<typename CLASS,typename... ARGS>
      void AtomicResource::callConstructor(ARGS... args){
        assert(this!=nullptr);
        new(this->getData())CLASS(args...);
      }
/*
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResourceTypeId(TypeId id,ARGS... args)const{
        auto ptr=std::make_shared<AtomicResource>(std::const_pointer_cast<TypeRegister>(this->shared_from_this()),this->alloc(id),id);
        ptr->callConstructor<CLASS>(args...);
        return ptr;
      }
*/


  }
}
