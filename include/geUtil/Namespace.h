#pragma once

#include<iostream>
#include<vector>
#include<map>

#include<geUtil/Export.h>
#include<geCore/TypeRegister.h>

namespace ge{
  namespace util{
    namespace sim{
      class GEUTIL_EXPORT Namespace: public std::enable_shared_from_this<Namespace>{
        protected:
          std::string _name   = ""     ;
          std::weak_ptr<Namespace>  _parent;
          std::map<std::string,std::shared_ptr<Namespace>>_name2Namespace   ;
          std::map<std::string,std::shared_ptr<ge::core::Accessor>> _name2Variable;
          std::string _toUpper(std::string str);
        public:
          Namespace(std::string name,std::shared_ptr<Namespace>const&parent = nullptr);
          virtual ~Namespace();
          bool empty()const;
          void setParent(std::shared_ptr<Namespace>const&parent = nullptr);
          void insertNamespace(std::string name,std::shared_ptr<Namespace>const&nmspace);
          void insert(std::string name,std::shared_ptr<ge::core::Accessor>const&variable);
          void erase(std::string name);
          std::string toStr(unsigned indentation)const;
          std::shared_ptr<Namespace>getNamespace(std::string name)const;
          std::shared_ptr<ge::core::Accessor>getVariable(std::string name)const;
          bool contain(std::string name)const;
          template<typename TYPE>
            TYPE&get(std::string name)const;
          template<typename TYPE>
            TYPE const&get(std::string name,TYPE const& def)const;
          template<typename TYPE>
            TYPE& get(std::string name,TYPE &def)const;
          typedef std::map<std::string,std::shared_ptr<Namespace>>::const_iterator CNSIter;
          typedef std::map<std::string,std::shared_ptr<ge::core::Accessor>>::const_iterator CVarIter;
          CNSIter  namespacesBegin()const;
          CNSIter  namespacesEnd  ()const;
          CVarIter varsBegin()const;
          CVarIter varsEnd  ()const;
      };



      template<typename TYPE>
        TYPE&Namespace::get(std::string name)const{
          return (TYPE&)(*this->getVariable(name));
        }

      template<typename TYPE>
        TYPE const&Namespace::get(std::string name,TYPE const& def)const{
          if(!this->contain(name))return def;
          return (TYPE&)(*this->getVariable(name));
        }

      template<typename TYPE>
        TYPE& Namespace::get(std::string name,TYPE &def)const{
          if(!this->contain(name))return def;
          return (TYPE&)(*this->getVariable(name));
        }
    }
  }
}
