#pragma once

#include<cstddef>
#include<cassert>
#include<geDE/Export.h>

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
      this->_maxUses = maxUses;
      this->_uses    = 0      ;
      this->_first   = true   ;
    }

    inline ObjectFactory::~ObjectFactory(){
    }

    inline ObjectFactory::Uses ObjectFactory::getUses()const{
      assert(this!=nullptr);
      return this->_maxUses;
    }

    inline void ObjectFactory::setUses(Uses uses){
      assert(this!=nullptr);
      this->_maxUses = uses;
    }

  }
}

