#pragma once

#include<iostream>
#include<vector>
#include<map>

#include<geDE/Export.h>
#include<geDE/TypeRegister.h>
#include<geDE/Resource.h>

namespace ge{
  namespace de{
      class GEDE_EXPORT Namespace: public std::enable_shared_from_this<Namespace>{
        public:
          using SharedNamespace = std::shared_ptr<Namespace>;
          using SharedResource  = std::shared_ptr<Resource >;
        protected:
          std::string                          _name   = ""     ;
          std::weak_ptr<Namespace>             _parent          ;
          std::map<std::string,SharedNamespace>_name2Namespace  ;
          std::map<std::string,SharedResource >_name2Variable   ;
          std::string _toUpper(std::string str);
        public:
          Namespace(std::string name,SharedNamespace const&parent = nullptr);
          virtual ~Namespace();
          bool empty()const;
          void setParent(SharedNamespace const&parent = nullptr);
          void insertNamespace(std::string name,SharedNamespace const&nmspace);
          void insert(std::string name,SharedResource const&variable);
          void erase(std::string name);
          std::string toStr(unsigned indentation)const;
          SharedNamespace getNamespace(std::string name)const;
          SharedResource  getVariable (std::string name)const;
          bool contain(std::string name)const;
          template<typename TYPE>
            TYPE&get(std::string name)const;
          template<typename TYPE>
            TYPE const&get(std::string name,TYPE const& def)const;
          template<typename TYPE>
            TYPE&get(std::string name,TYPE &def)const;
          using CNSIter  = decltype(_name2Namespace)::const_iterator;
          using CVarIter = decltype(_name2Variable )::const_iterator;
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
