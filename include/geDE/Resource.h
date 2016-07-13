#pragma once

#include<geDE/Export.h>
#include<geCore/Dtemplates.h>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<typeinfo>
#include<functional>
#include<memory>
#include<geDE/TypeRegister.h>

namespace ge{
  namespace de{
    class TypeRegister;

    class GEDE_EXPORT Resource{
      public:
        inline Resource(
            std::shared_ptr<TypeRegister>const&manager = nullptr                   ,
            TypeRegister::TypeId               id      = TypeRegister::UNREGISTERED);
        inline virtual ~Resource();
        inline std::shared_ptr<TypeRegister>const&getManager()const;
        virtual void*getData()const = 0;
        virtual void const*getDataAddress()const = 0;
        inline TypeRegister::TypeId getId()const;
        virtual std::shared_ptr<Resource> operator[](size_t elem) = 0;
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
      protected:
        std::shared_ptr<TypeRegister>_manager = nullptr;
        TypeRegister::TypeId _id = TypeRegister::UNREGISTERED;
    };

    inline Resource::Resource(
        std::shared_ptr<TypeRegister>const&manager,
        TypeRegister::TypeId               id     ){
      this->_manager = manager;
      this->_id = id;
    }

    inline Resource::~Resource(){

    }

    inline std::shared_ptr<TypeRegister>const&Resource::getManager()const{
      return this->_manager;
    }

    inline TypeRegister::TypeId Resource::getId()const{
      return this->_id;
    }

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
        return (T**)this->getData();//this->getDataAddress();
      }


/*
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResource(std::string const&name,ARGS... args)const{
        TypeId id=this->getTypeId(name);
        return this->sharedResourceTypeId<CLASS>(id,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResource(const char* name,ARGS... args)const{
        TypeId id=this->getTypeId(std::string(name));
        return this->sharedResourceTypeId<CLASS>(id,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResource(ARGS... args)const{
        TypeId id=this->getTypeId(this->getTypeKeyword<CLASS>());
        return this->sharedResourceTypeId<CLASS>(id,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResourceAddCD(std::string const&name,ARGS... args){
        this->addClassCD<CLASS>(name);
        return this->sharedResource<CLASS>(name,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResourceAddC(std::string const&name,ARGS... args){
        this->addClassC<CLASS>(name);
        return this->sharedResource<CLASS>(name,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResourceAddD(std::string const&name,ARGS... args){
        this->addClassD<CLASS>(name);
        return this->sharedResource<CLASS>(name,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Resource>TypeRegister::sharedResourceAdd(std::string const&name,ARGS... args){
        this->addClass<CLASS>(name);
        return this->sharedResource<CLASS>(name,args...);
      }
      */
  }
}
