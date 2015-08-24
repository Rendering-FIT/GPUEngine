#pragma once

#include<geUtil/ArgumentManager.h>
#include"NamespaceWithUsers.h"

namespace ge{
  namespace util{
    namespace sim{
      void copyArgumentManager2Namespace(
          ge::util::sim::Namespace* ns          ,
          ge::util::ArgumentManager*argm        ,
          std::shared_ptr<ge::core::TypeRegister>&typeRegister);
    }
  }
}
