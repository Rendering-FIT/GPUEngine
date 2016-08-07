#pragma once

#include<cstddef>
#include<cassert>
#include<geDE/Export.h>
#include<geCore/CallStackPrinter.h>

namespace ge{
  namespace de{
    class GEDE_EXPORT ObjectFactory{
      public:
        using Uses = size_t;
      protected:
        Uses _maxUses = 0   ;
        Uses _uses    = 0   ;
        bool _first   = true;
      public:
        inline ObjectFactory(Uses const&maxUses = 0);
        inline virtual ~ObjectFactory();
        inline Uses getUses()const;
        inline void setUses(Uses uses);
    };

    inline ObjectFactory::ObjectFactory(Uses const&maxUses){
      PRINT_CALL_STACK(maxUses);
      assert(this!=nullptr);
      this->_maxUses = maxUses;
      this->_uses    = 0      ;
      this->_first   = true   ;
    }

    inline ObjectFactory::~ObjectFactory(){
      PRINT_CALL_STACK();
    }

    inline ObjectFactory::Uses ObjectFactory::getUses()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_maxUses;
    }

    inline void ObjectFactory::setUses(Uses uses){
      PRINT_CALL_STACK(uses);
      assert(this!=nullptr);
      this->_maxUses = uses;
    }

  }
}

