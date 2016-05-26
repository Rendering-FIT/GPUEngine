#pragma once

#include<geDE/ObjectFactory.h>
#include<geDE/TypeRegister.h>

namespace ge{
  namespace de{
    class Resource;
    class FunctionRegister;
    class GEDE_EXPORT ResourceFactory: public ObjectFactory{
      protected:
        TypeRegister::TypeId     _type   = TypeRegister::UNREGISTERED;
        std::shared_ptr<Resource>_result = nullptr                   ;
      public:
        inline ResourceFactory(TypeRegister::TypeId const&type,Uses const&maxUses=1);
        inline virtual ~ResourceFactory();
        inline void reset();
        inline bool firstConstruction()const;
        std::shared_ptr<Resource>operator()(std::shared_ptr<FunctionRegister>const&tr);
    };

    inline ResourceFactory::ResourceFactory(
        TypeRegister::TypeId const&type   ,
        Uses                 const&maxUses){
      this->_type    = type   ;
      this->_maxUses = maxUses;
      this->reset();
    }

    inline ResourceFactory::~ResourceFactory(){
    }

    inline void ResourceFactory::reset(){
      this->_uses   = 0      ;
      this->_result = nullptr;
      this->_first  = true   ;
    }

    inline bool ResourceFactory::firstConstruction()const{
      return this->_first;
    }
  }
}
