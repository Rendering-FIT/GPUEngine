#pragma once

#include<geUtil/Export.h>
#include<geUtil/ArgumentManager/ArgumentManager.h>
#include<geUtil/NamespaceWithUsers.h>

namespace ge{
  namespace util{
    namespace sim{
      GEUTIL_EXPORT void copyArgumentManager2Namespace(
          std::shared_ptr<ge::util::sim::Namespace> const&ns,
          ge::util::ArgumentManager*argm   ,
          std::shared_ptr<ge::core::TypeRegister>&typeRegister);
    }
  }
}
