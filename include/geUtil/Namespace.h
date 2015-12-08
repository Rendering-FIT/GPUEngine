#pragma once

#include<iostream>
#include<vector>
#include<map>

#include<geUtil/Export.h>
#include<geCore/TypeRegister.h>

namespace ge{
  namespace util{
    namespace sim{
      class GEUTIL_EXPORT Namespace{
        protected:
          std::string _name   = ""     ;
          Namespace*  _parent = nullptr;
          std::map<std::string,Namespace*>_name2Namespace   ;
          std::map<std::string,std::shared_ptr<ge::core::Accessor>> _name2Variable;
          std::string _toUpper(std::string str);
        public:
          Namespace(std::string name,Namespace*parent=NULL);
          virtual ~Namespace();
          bool empty()const;
          void setParent(Namespace*parent=NULL);
          void insertNamespace(std::string name,Namespace*nmspace);
          void insert(std::string name,std::shared_ptr<ge::core::Accessor>const&variable);
          void erase(std::string name);
          std::string toStr(unsigned indentation)const;
          Namespace*getNamespace(std::string name)const;
          std::shared_ptr<ge::core::Accessor>getVariable(std::string name)const;
          bool contain(std::string name)const;
          template<typename TYPE>
            TYPE&get(std::string name)const{
              return (TYPE&)(*this->getVariable(name));
            }
          template<typename TYPE>
            TYPE const&get(std::string name,TYPE const& def)const{
              if(!this->contain(name))return def;
              return (TYPE&)(*this->getVariable(name));
            }
          template<typename TYPE>
            TYPE &get(std::string name,TYPE &def)const{
              if(!this->contain(name))return def;
              return (TYPE&)(*this->getVariable(name));
            }
          typedef std::map<std::string,Namespace*>::const_iterator CNSIter;
          typedef std::map<std::string,std::shared_ptr<ge::core::Accessor>>::const_iterator CVarIter;
          CNSIter  namespacesBegin()const;
          CNSIter  namespacesEnd  ()const;
          CVarIter varsBegin()const;
          CVarIter varsEnd  ()const;
      };
    }
  }
}
