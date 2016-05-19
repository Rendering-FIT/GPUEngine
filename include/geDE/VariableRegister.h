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
        using Name2Register = std::map<std::string,SharedVariableRegister>;
        using Name2Variable = std::map<std::string,SharedVariable>;
        using VariableIterator = Name2Variable::iterator;
        using RegisterIterator = Name2Register::iterator;
        VariableRegister(std::string name,VariableRegister*parent = nullptr);
        virtual ~VariableRegister();
        bool empty()const;
        void setParent(VariableRegister*parent = nullptr);
        void insertVariableRegister(std::string name,SharedVariableRegister const&vr);
        bool insert(std::string name,SharedVariable const&variable);
        void erase(std::string name);
        std::string toStr(unsigned indentation,std::shared_ptr<TypeRegister>const&tr)const;
        std::string getName()const;
        std::string getFullName()const;
        bool hasVariableRegister(std::string name)const;
        bool hasVariable(std::string name)const;
        SharedVariableRegister const&getVariableRegister(std::string name)const;
        SharedVariable         const&getVariable (std::string name)const;
        bool contain(std::string name)const;
        VariableIterator varsBegin();
        VariableIterator varsEnd();
        RegisterIterator registersBegin();
        RegisterIterator registersEnd();
      protected:
        std::string _name = "";
        VariableRegister*_parent = nullptr;
        Name2Register _name2Register;
        Name2Variable _name2Variable;
    };
  }
}

