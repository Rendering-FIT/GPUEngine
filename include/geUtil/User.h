#pragma once

#include<geUtil/Namespace.h>

namespace ge{
  namespace util{
    namespace sim{
      class User{
        protected:
          Namespace*_sData;
        public:
          User(Namespace*ns){this->_sData=ns;}
          virtual void update(){}
      };
    }
  }
}
