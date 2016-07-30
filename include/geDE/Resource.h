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

    class /*GEDE_EXPORT*/ Resource{
      public:
        inline Resource(
            std::shared_ptr<TypeRegister>const&manager = nullptr                   ,
            TypeId               id      = TypeRegister::UNREGISTERED);
        inline virtual ~Resource();
        inline std::shared_ptr<TypeRegister>const&getManager()const;
        virtual void*getData()const = 0;
        virtual void const*getDataAddress()const = 0;
        inline TypeId getId()const;
        virtual std::shared_ptr<Resource> operator[](size_t elem) = 0;
        virtual size_t getNofElements()const=0;
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
        TypeId _id = TypeRegister::UNREGISTERED;
    };

    inline Resource::Resource(
        std::shared_ptr<TypeRegister>const&manager,
        TypeId               id     ){
      PRINT_CALL_STACK(manager,id);
      assert(this!=nullptr);
      this->_manager = manager;
      this->_id = id;
    }

    inline Resource::~Resource(){
      PRINT_CALL_STACK();
    }

    inline std::shared_ptr<TypeRegister>const&Resource::getManager()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_manager;
    }

    inline TypeId Resource::getId()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_id;
    }

    template<typename T>
      Resource& Resource::operator=(const T&data){
        PRINT_CALL_STACK(data);
        assert(this!=nullptr);
        assert(this->getData()!=nullptr);
        *((T*)this->getData()) = data;
        return *this;
      }

    template<typename T>
      Resource::operator T&()const{
        PRINT_CALL_STACK();
        assert(this!=nullptr);
        assert(this->getData()!=nullptr);
        return *((T*)this->getData());
      }

    template<typename T>
      Resource::operator T*()const{
        PRINT_CALL_STACK();
        assert(this!=nullptr);
        assert(this->getData()!=nullptr);
        return *(T**)this->getData();
      }

    
    template<typename T>
      Resource::operator T**()const{
        PRINT_CALL_STACK();
        assert(this!=nullptr);
        return (T**)this->getData();//this->getDataAddress();
      }
  }
}
