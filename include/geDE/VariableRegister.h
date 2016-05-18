#pragma once

#include<geDE/Export.h>
#include<iostream>
#include<map>
#include<memory>

namespace ge{
  namespace de{
    class TypeRegister;
    class Nullary;
    class GEDE_EXPORT VariableRegister{
      public:
        using SharedVariableRegister = std::shared_ptr<VariableRegister>;
        using SharedVariable = std::shared_ptr<Nullary>;
        VariableRegister(std::string name,VariableRegister*parent = nullptr);
        virtual ~VariableRegister();
        bool empty()const;
        void setParent(VariableRegister*parent = nullptr);
        void insertVariableRegister(std::string name,SharedVariableRegister const&vr);
        bool insert(std::string name,SharedVariable const&variable);
        void erase(std::string name);
        std::string toStr(unsigned indentation,std::shared_ptr<TypeRegister>const&tr)const;
        bool hasVariableRegister(std::string name)const;
        bool hasVariable(std::string name)const;
        SharedVariableRegister const&getVariableRegister(std::string name)const;
        SharedVariable         const&getVariable (std::string name)const;
        bool contain(std::string name)const;
      protected:
        std::string _name = "";
        VariableRegister*_parent = nullptr;
        std::map<std::string,SharedVariableRegister>_name2Register;
        std::map<std::string,SharedVariable>_name2Variable;
    };
  }
}

