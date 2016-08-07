#pragma once

#include<memory>
#include<geDE/ObjectFactory.h>
#include<geDE/Types.h>

namespace ge{
  namespace de{
    class Resource;
    class FunctionRegister;
    class GEDE_EXPORT ResourceFactory: public ObjectFactory{
      protected:
        TypeId                   _type;
        std::shared_ptr<Resource>_result = nullptr                   ;
      public:
        inline ResourceFactory(TypeId const&type,Uses const&maxUses=0);
        inline virtual ~ResourceFactory();
        inline void reset();
        inline bool firstConstruction()const;
        std::shared_ptr<Resource>operator()(std::shared_ptr<FunctionRegister>const&tr);
    };

    inline ResourceFactory::ResourceFactory(
        TypeId const&type   ,
        Uses   const&maxUses){
      PRINT_CALL_STACK(type,maxUses);
      assert(this!=nullptr);
      this->_type    = type   ;
      this->_maxUses = maxUses;
      this->reset();
    }

    inline ResourceFactory::~ResourceFactory(){
      PRINT_CALL_STACK();
    }

    inline void ResourceFactory::reset(){
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      this->_uses   = 0      ;
      this->_result = nullptr;
      this->_first  = true   ;
    }

    inline bool ResourceFactory::firstConstruction()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_first;
    }
  }
}
