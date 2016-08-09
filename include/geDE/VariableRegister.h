#pragma once

#include<geDE/Export.h>
#include<iostream>
#include<map>
#include<memory>

namespace ge{
  namespace de{
    class TypeRegister;
    class Resource;
    class GEDE_EXPORT VariableRegister{
      public:
        using SharedVariableRegister = std::shared_ptr<VariableRegister>;
        using SharedVariable = std::shared_ptr<Resource>;
        using Name2Register = std::map<std::string,SharedVariableRegister>;
        using Name2Variable = std::map<std::string,SharedVariable>;
        using VariableIterator = Name2Variable::iterator;
        using RegisterIterator = Name2Register::iterator;
        VariableRegister(std::string const&name,VariableRegister*parent = nullptr);
        virtual ~VariableRegister();
        bool empty()const;
        void setParent(VariableRegister*parent = nullptr);
        void insertVariableRegister(std::string const&name,SharedVariableRegister const&vr);
        bool insert(std::string const&name,SharedVariable const&variable);
        void erase(std::string const&name);
        void eraseVariableRegister(std::string const&name);
        std::string toStr(unsigned indentation,std::shared_ptr<TypeRegister>const&tr)const;
        std::string getName()const;
        std::string getFullName()const;
        bool hasVariableRegister(std::string const&name)const;
        bool hasVariable(std::string const&name)const;
        SharedVariableRegister const&getVariableRegister(std::string const&name)const;
        SharedVariable         const&getVariable (std::string const&name)const;
        bool contain(std::string const&name)const;
        VariableIterator varsBegin();
        VariableIterator varsEnd();
        RegisterIterator registersBegin();
        RegisterIterator registersEnd();
      protected:
        bool _checkPath(std::string const&path)const;
        std::string _name = "";
        VariableRegister*_parent = nullptr;
        Name2Register _name2Register;
        Name2Variable _name2Variable;
    };
  }
}

