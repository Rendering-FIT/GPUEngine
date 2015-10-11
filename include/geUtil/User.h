#pragma once

#include<geUtil/Namespace.h>

namespace ge{
  namespace util{
    namespace sim{
      class User{
        protected:
          std::shared_ptr<Namespace>_sData;
        public:
          User(std::shared_ptr<Namespace>const&ns){this->_sData=ns;}
          virtual void update(){}
      };
    }
  }
}
