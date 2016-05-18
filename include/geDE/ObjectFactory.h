#pragma once

#include<cstddef>
#include<geDE/Export.h>

namespace ge{
  namespace de{
    class GEDE_EXPORT ObjectFactory{
      public:
        using Uses = size_t;
      protected:
        Uses _maxUses = 1   ;
        Uses _uses    = 0   ;
        bool _first   = true;
      public:
        inline ObjectFactory(Uses const&maxUses = 1);
        inline virtual ~ObjectFactory();
    };

    inline ObjectFactory::ObjectFactory(Uses const&maxUses){
      this->_maxUses = maxUses;
      this->_uses    = 0      ;
      this->_first   = true   ;
    }

    inline ObjectFactory::~ObjectFactory(){
    }
  }
}

