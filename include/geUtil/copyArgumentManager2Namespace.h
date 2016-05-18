#pragma once

#include<geUtil/Export.h>
#include<geUtil/ArgumentManager/ArgumentManager.h>
#include<geDE/NamespaceWithUsers.h>

namespace ge{
  namespace util{
    namespace sim{
      GEUTIL_EXPORT void copyArgumentManager2Namespace(
          std::shared_ptr<de::Namespace> const&ns,
          ge::util::ArgumentManager*argm   ,
          std::shared_ptr<de::TypeRegister>&typeRegister);
    }
  }
}
