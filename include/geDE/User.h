#pragma once

#include<geDE/Namespace.h>
#include<geDE/Export.h>

namespace ge{
  namespace de{
    class GEDE_EXPORT User{
      protected:
        std::shared_ptr<Namespace>_sData;
      public:
        User(std::shared_ptr<Namespace>const&ns){this->_sData=ns;}
        virtual void update(){}
    };
  }
}
