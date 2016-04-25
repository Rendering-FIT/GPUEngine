#pragma once

#include<geCore/ObjectFactory.h>
#include<geCore/TypeRegister.h>

namespace ge{
  namespace core{
    class Accessor;
    class FunctionRegister;
    class GECORE_EXPORT ResourceFactory: public ObjectFactory{
      protected:
        TypeRegister::TypeID     _type   = TypeRegister::UNREGISTERED;
        std::shared_ptr<Accessor>_result = nullptr                   ;
      public:
        inline ResourceFactory(TypeRegister::TypeID const&type,Uses const&maxUses=1);
        inline virtual ~ResourceFactory();
        inline void reset();
        inline bool firstConstruction()const;
        std::shared_ptr<Accessor>operator()(std::shared_ptr<FunctionRegister>const&tr);
    };

    inline ResourceFactory::ResourceFactory(
        TypeRegister::TypeID const&type   ,
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
