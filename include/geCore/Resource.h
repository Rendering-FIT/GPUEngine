#pragma once

#include<geCore/Export.h>
#include<geCore/Dtemplates.h>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<typeinfo>
#include<functional>
#include<memory>
#include<geCore/TypeRegister.h>

namespace ge{
  namespace core{
    class AtomicResource;
    class TypeRegister;

    class GECORE_EXPORT Resource{
      protected:
        std::shared_ptr<TypeRegister>_manager = nullptr;
        TypeRegister::TypeID _id = TypeRegister::UNREGISTERED;
      public:
        inline Resource(
            std::shared_ptr<TypeRegister>const&manager = nullptr                   ,
            TypeRegister::TypeID               id      = TypeRegister::UNREGISTERED){
          //std::cerr<<"Resource::Resource() - "<<this<<std::endl;
          //std::cout<<"Resource::Resource()-tr: "<<manager<<std::endl;
          this->_manager = manager;
          //std::cout<<"this: "<<this<<" Resource::Resource()->_manager: "<<this->_manager<<std::endl;
          this->_id = id;
        }
        inline virtual ~Resource(){}//std::cerr<<"Resource::~Resource() - "<<this<<std::endl;}
        inline std::shared_ptr<TypeRegister>const&getManager()const{return this->_manager;}
        virtual void*getData()const = 0;
        virtual void const*getDataAddress()const = 0;
        inline TypeRegister::TypeID getId()const{return this->_id;}
        virtual std::shared_ptr<Resource> operator[](TypeRegister::DescriptionIndex elem)const=0;
        virtual TypeRegister::DescriptionElement getNofElements()const=0;
        virtual std::string data2Str()const=0;
        template<typename T>
          Resource& operator=(const T&data);
        template<typename T>
          operator T&()const;
        template<typename T>
          operator T*()const;
        template<typename T>
          operator T**()const;
    };

    template<typename T>
      Resource& Resource::operator=(const T&data){
        *((T*)this->getData()) = data;
        return *this;
      }
    template<typename T>
      Resource::operator T&()const{
        return *((T*)this->getData());
      }
    template<typename T>
      Resource::operator T*()const{
        return (T*)this->getData();
      }
    template<typename T>
      Resource::operator T**()const{
        return (T**)this->getDataAddress();
      }

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

    class GECORE_EXPORT CompositeResource: public Resource{
      protected:
        std::vector<std::shared_ptr<Resource>>_components;
        TypeRegister::DescriptionElement _nofElements;
      public:
        CompositeResource(
            std::shared_ptr<TypeRegister>const&         manager   = nullptr                   ,
            TypeRegister::TypeID                        id        = TypeRegister::UNREGISTERED,
            std::vector<std::shared_ptr<Resource>>const&accessors = {}                        );
        virtual void*getData()const = 0;
        virtual void const*getDataAddress()const = 0;
        virtual std::shared_ptr<Resource> operator[](TypeRegister::DescriptionIndex elem)const=0;
        virtual TypeRegister::DescriptionElement getNofElements()const=0;
        virtual std::string data2Str()const=0;
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
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResource(std::string name,ARGS... args)const{
        TypeID id=this->getTypeId(name);
        return this->sharedResourceTypeID<CLASS>(id,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResource(const char* name,ARGS... args)const{
        TypeID id=this->getTypeId(std::string(name));
        return this->sharedResourceTypeID<CLASS>(id,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResource(ARGS... args)const{
        TypeID id=this->getTypeId(this->getTypeKeyword<CLASS>());
        return this->sharedResourceTypeID<CLASS>(id,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResourceAddCD(std::string name,ARGS... args){
        this->addClassCD<CLASS>(name);
        return this->sharedResource<CLASS>(name,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResourceAddC(std::string name,ARGS... args){
        this->addClassC<CLASS>(name);
        return this->sharedResource<CLASS>(name,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResourceAddD(std::string name,ARGS... args){
        this->addClassD<CLASS>(name);
        return this->sharedResource<CLASS>(name,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResourceAdd(std::string name,ARGS... args){
        this->addClass<CLASS>(name);
        return this->sharedResource<CLASS>(name,args...);
      }
  }
}
