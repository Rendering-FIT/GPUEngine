#pragma once

#include<iostream>
#include<vector>
#include<map>

#include<geUtil/Export.h>
#include<geCore/TypeRegister.h>
#include<geCore/Namespace.h>

namespace ge{
  namespace util{
    namespace sim{
      class User;

      class GEUTIL_EXPORT NamespaceWithUsers: public ge::core::sim::Namespace{
        protected:
          std::set<User*>                      _allUsers      ;
          std::map<std::string,std::set<User*>>_variableUser  ;
          std::map<std::string,bool>           _changed       ;
          std::map<User*,bool>                 _sendUpdate    ;
          std::map<User*,std::set<std::string>>_user2Variables;
        public:
          NamespaceWithUsers(std::string name);
          void registerUser  (User*user,std::string variable);
          void unregisterUser(User*user,std::string variable="");
          void setAsChanged(std::string variable);
          void sendUpdate();
      };
    }
  }
}
