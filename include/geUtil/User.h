#pragma once

#include<geCore/Namespace.h>

namespace ge{
  namespace util{
    namespace sim{
      class GEUTIL_EXPORT User{
        protected:
          std::shared_ptr<ge::core::sim::Namespace>_sData;
        public:
          User(std::shared_ptr<ge::core::sim::Namespace>const&ns){this->_sData=ns;}
          virtual void update(){}
      };
    }
  }
}
