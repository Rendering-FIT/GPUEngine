#pragma once

#include<iostream>
#include<cassert>
#include<tuple>
#include<map>
#include<geDE/Export.h>
#include<geCore/ErrorPrinter.h>
#include<geCore/CallStackPrinter.h>
#include<geCore/Dtemplates.h>

namespace ge{
  namespace de{

    class GEDE_EXPORT NameRegister{
      public:
        using ElementIndex = size_t;
        using Id = size_t;
        NameRegister();
        ~NameRegister();
        std::string const&getFceInputName(Id id,ElementIndex input)const;
        std::string const&getFceOutputName(Id id)const;
        void setFceInputName (Id id,ElementIndex input,std::string const&name);
        void setFceOutputName(Id id,std::string const&name);
        std::string const&getStructElementName(Id id,ElementIndex e)const;
        void setStructElementName(Id id,ElementIndex e,std::string const&name);
        std::string const&getEnumElementName(Id id,ElementIndex e)const;
        void setEnumElementName(Id id,ElementIndex e,std::string const&name);
        ElementIndex getFceInput     (Id id,std::string const&name)const;
        ElementIndex getStructElement(Id id,std::string const&name)const;
        ElementIndex getEnumElement  (Id id,std::string const&name)const;
        bool hasFceInput     (Id id,std::string const&name)const;
        bool hasStructElement(Id id,std::string const&name)const;
        bool hasEnumElement  (Id id,std::string const&name)const;
        void addFceNaming(Id id,ElementIndex nofInputs);
        void addStructNaming(Id id,ElementIndex nofElements);
        void addEnumNaming  (Id id,ElementIndex nofElements);
        void removeFceNaming   (Id id);
        void removeStructNaming(Id id);
        void removeEnumNaming  (Id id);
      protected:
        using FunctionNaming = std::tuple<
          std::vector<std::string>,
          std::map<std::string,ElementIndex>,
          std::string>;
        enum FunctionNamingParts{
          INPUT_NAME   = 0,
          NAME_2_INPUT = 1,
          OUTPUT       = 2,
        };
        using StructureNaming = std::tuple<
          std::vector<std::string>,
          std::map<std::string,ElementIndex>>;
        enum StructureNameingParts{
          ELEMENT_NAME   = 0,
          NAME_2_ELEMENT = 1,
        };
        using EnumNaming = std::tuple<
          std::vector<std::string>,
          std::map<std::string,ElementIndex>>;
        using FunctionMap  = std::map<Id,FunctionNaming >;
        using StructureMap = std::map<Id,StructureNaming>; 
        using EnumMap      = std::map<Id,EnumNaming>     ;
        FunctionMap  _functionNaming;
        StructureMap _structureNaming;
        EnumMap      _enumNaming;
    };

    inline NameRegister::NameRegister(){
      PRINT_CALL_STACK();
    }

    inline NameRegister::~NameRegister(){
      PRINT_CALL_STACK();
    }

    inline std::string const&NameRegister::getFceInputName(Id id,ElementIndex input)const{
      PRINT_CALL_STACK(id,input);
      assert(this!=nullptr);
      assert(this->_functionNaming.count(id)!=0);
      assert(input<std::get<INPUT_NAME>(this->_functionNaming.find(id)->second).size());
      return std::get<INPUT_NAME>(this->_functionNaming.find(id)->second)[input];
    }

    inline std::string const&NameRegister::getFceOutputName(Id id)const{
      PRINT_CALL_STACK(id);
      assert(this!=nullptr);
      assert(this->_functionNaming.count(id)!=0);
      return std::get<OUTPUT>(this->_functionNaming.find(id)->second);
    }

    inline void NameRegister::setFceInputName(Id id,ElementIndex input,std::string const&name){
      PRINT_CALL_STACK(id,input,name);
      assert(this!=nullptr);
      assert(this->_functionNaming.count(id)!=0);
      assert(input<std::get<INPUT_NAME>(this->_functionNaming[id]).size());
      if(this->hasFceInput(id,name)&&this->getFceInput(id,name)!=input){
        ge::core::printError("NameRegister::setFceInputName","there is other input with that name",id,input,name);
        return;
      }
      std::get<NAME_2_INPUT>(this->_functionNaming[id]).erase(std::get<INPUT_NAME>(this->_functionNaming[id])[input]);
      std::get<INPUT_NAME>(this->_functionNaming[id])[input] = name;
      std::get<NAME_2_INPUT>(this->_functionNaming[id])[name] = input;
    }

    inline void NameRegister::setFceOutputName(Id id,std::string const&name){
      PRINT_CALL_STACK(id,name);
      assert(this!=nullptr);
      assert(this->_functionNaming.count(id)!=0);
      std::get<OUTPUT>(this->_functionNaming[id]) = name;
    }

    inline std::string const&NameRegister::getStructElementName(Id id,ElementIndex element)const{
      PRINT_CALL_STACK(id,element);
      assert(this!=nullptr);
      assert(this->_structureNaming.count(id)!=0);
      assert(element<std::get<ELEMENT_NAME>(this->_structureNaming.find(id)->second).size());
      return std::get<ELEMENT_NAME>(this->_structureNaming.find(id)->second)[element];
    }

    inline void NameRegister::setStructElementName(Id id,ElementIndex element,std::string const&name){
      PRINT_CALL_STACK(id,element,name);
      assert(this!=nullptr);
      assert(this->_structureNaming.count(id)!=0);
      assert(element<std::get<ELEMENT_NAME>(this->_structureNaming.at(id)).size());
      std::get<NAME_2_ELEMENT>(this->_structureNaming.at(id)).erase(std::get<ELEMENT_NAME>(this->_structureNaming.at(id)).at(element));
      std::get<ELEMENT_NAME>(this->_structureNaming.at(id)).at(element) = name;
      std::get<NAME_2_ELEMENT>(this->_structureNaming.at(id))[name] = element;
    }

    inline std::string const&NameRegister::getEnumElementName(Id id,ElementIndex element)const{
      PRINT_CALL_STACK(id,element);
      assert(this!=nullptr);
      assert(this->_enumNaming.count(id)!=0);
      assert(element<std::get<ELEMENT_NAME>(this->_enumNaming.at(id)).size());
      return std::get<ELEMENT_NAME>(this->_enumNaming.at(id)).at(element);
    }

    inline void NameRegister::setEnumElementName(Id id,ElementIndex element,std::string const&name){
      PRINT_CALL_STACK(id,element,name);
      assert(this!=nullptr);
      assert(this->_enumNaming.count(id)!=0);
      assert(element<std::get<ELEMENT_NAME>(this->_enumNaming.at(id)).size());
      std::get<NAME_2_ELEMENT>(this->_enumNaming.at(id)).erase(std::get<ELEMENT_NAME>(this->_enumNaming.at(id)).at(element));
      std::get<ELEMENT_NAME>(this->_enumNaming.at(id)).at(element) = name;
      std::get<NAME_2_ELEMENT>(this->_enumNaming.at(id))[name] = element;
    }

    inline NameRegister::ElementIndex NameRegister::getFceInput(Id id,std::string const&name)const{
      PRINT_CALL_STACK(id,name);
      assert(this!=nullptr);
      assert(this->_functionNaming.count(id)!=0);
      auto fi = this->_functionNaming.find(id);
      auto ii = std::get<NAME_2_INPUT>(fi->second).find(name);
      if(ii==std::get<NAME_2_INPUT>(fi->second).end()){
        ge::core::printError(GE_CORE_FCENAME,"no such function input",id,name);
        return 0;
      }
      return ii->second;
    }

    inline NameRegister::ElementIndex NameRegister::getStructElement(Id id,std::string const&name)const{
      PRINT_CALL_STACK(id,name);
      assert(this!=nullptr);
      assert(this->_structureNaming.count(id)!=0);
      auto si = this->_structureNaming.find(id);
      auto ii = std::get<NAME_2_ELEMENT>(si->second).find(name);
      if(ii==std::get<NAME_2_ELEMENT>(si->second).end()){
        ge::core::printError(GE_CORE_FCENAME,"no such structure element",id,name);
        return 0;
      }
      return ii->second;
    }

    inline NameRegister::ElementIndex NameRegister::getEnumElement(Id id,std::string const&name)const{
      PRINT_CALL_STACK(id,name);
      assert(this!=nullptr);
      assert(this->_enumNaming.count(id)!=0);
      auto si = this->_enumNaming.find(id);
      auto ii = std::get<NAME_2_ELEMENT>(si->second).find(name);
      if(ii==std::get<NAME_2_ELEMENT>(si->second).end()){
        ge::core::printError(GE_CORE_FCENAME,"no such enum element",id,name);
        return 0;
      }
      return ii->second;
    }

    inline bool NameRegister::hasFceInput(Id id,std::string const&name)const{
      PRINT_CALL_STACK(id,name);
      assert(this!=nullptr);
      assert(this->_functionNaming.count(id)!=0);
      return std::get<NAME_2_INPUT>(this->_functionNaming.at(id)).count(name)>0;
    }

    inline bool NameRegister::hasStructElement(Id id,std::string const&name)const{
      PRINT_CALL_STACK(id,name);
      assert(this!=nullptr);
      assert(this->_structureNaming.count(id)!=0);
      return std::get<NAME_2_ELEMENT>(this->_structureNaming.at(id)).count(name)>0;
    }

    inline bool NameRegister::hasEnumElement(Id id,std::string const&name)const{
      PRINT_CALL_STACK(id,name);
      assert(this!=nullptr);
      assert(this->_enumNaming.count(id)!=0);
      return std::get<NAME_2_ELEMENT>(this->_enumNaming.at(id)).count(name)>0;
    }

  }
}
