#pragma once

#include<utility>
#include<tuple>
#include<geCore/Export.h>
#include<geCore/TypeRegister.h>
#include<geCore/statement.h>

namespace ge{
  namespace core{
    class StatementFactory;
    class Statement;
    class Function;

    class GECORE_EXPORT FunctionRegister: public std::enable_shared_from_this<FunctionRegister>{
      public:
        typedef void(*Implementation)();
        using InputIndex = size_t;
        using FunctionID = size_t;
        using FunctionDefinition = std::tuple<
          TypeRegister::TypeID,
          std::string,
          std::shared_ptr<StatementFactory>,
          std::map<InputIndex,std::string>,
          std::map<std::string,InputIndex>,
          std::string>;
        enum FunctionDefinitionParts{
          TYPE       = 0,
          NAME       = 1,
          FACTORY    = 2,
          INDEX2NAME = 3,
          NAME2INDEX = 4,
          OUTPUTNAME = 5,
        };
      protected:
        std::shared_ptr<TypeRegister>_typeRegister;
        std::map<FunctionID,FunctionDefinition>_functions;
        std::map<FunctionID,Implementation>_implementations;
        std::map<std::string,FunctionID>_name2Function;
        inline FunctionDefinition      & _getDefinition(FunctionID id);
        inline FunctionDefinition const& _getDefinition(FunctionID id)const;
        std::string _genDefaultName(InputIndex i)const;
      public:
        inline FunctionRegister(std::shared_ptr<TypeRegister>const&typeRegister);
        inline ~FunctionRegister();
        FunctionID addFunction(
            TypeRegister::TypeID type,
            std::string          name,
            std::shared_ptr<StatementFactory>const&factory);
        inline TypeRegister::TypeID             getType   (FunctionID id)const;
        inline std::string                      getName   (FunctionID id)const;
        inline std::shared_ptr<StatementFactory>getFactory(FunctionID id)const;
        inline FunctionID getFunctionId(std::string name)const;
        inline InputIndex getNofInputs(FunctionID id)const;
        inline std::string getOutputName(FunctionID id)const;
        inline std::string getInputName(FunctionID id,InputIndex input)const;
        inline TypeRegister::TypeID getInputType(FunctionID id,InputIndex input)const;
        inline TypeRegister::TypeID getOutputType(FunctionID id)const;
        inline InputIndex getInputIndex(FunctionID id,std::string name)const;
        inline void setInputName(FunctionID id,InputIndex input,std::string name);
        inline void setOutputName(FunctionID id,std::string name);
        inline std::shared_ptr<TypeRegister>const&getTypeRegister()const;
        inline void addImplementation(FunctionID id,Implementation impl);
        inline void addImplementation(std::string name,Implementation impl);
        inline Implementation getImplementation(FunctionID id)const;
        inline Implementation getImplementation(std::string name)const;
        std::shared_ptr<Statement>sharedFunction(FunctionID id)const;
        std::shared_ptr<Statement>sharedFunction(std::string name)const;
        std::shared_ptr<StatementFactory>sharedFactory(FunctionID id,StatementFactory::Uses maxUses = 1)const;
        std::shared_ptr<StatementFactory>sharedFactory(std::string name,StatementFactory::Uses maxUses = 1)const;
        std::string str()const;
    };

    inline FunctionRegister::FunctionRegister(std::shared_ptr<TypeRegister>const&typeRegister){
      assert(typeRegister!=nullptr);
      this->_typeRegister = typeRegister;
      this->_functions[0]=FunctionDefinition(
          TypeRegister::getTypeTypeId<TypeRegister::Unregistered>(),
          "unregistered",
          nullptr,
          std::map<InputIndex,std::string>(),
          std::map<std::string,InputIndex>(),
          "");
    }


    inline FunctionRegister::~FunctionRegister(){
    }

    inline FunctionRegister::FunctionDefinition &FunctionRegister::_getDefinition(FunctionID id){
      assert(this!=nullptr);
      auto ii=this->_functions.find(id);
      if(ii==this->_functions.end()){
        std::cerr<<"ERROR - FunctionRegister::_getDefinition("<<id<<") - ";
        std::cerr<<"there is no such function id"<<std::endl;
        return this->_functions.find(0)->second;
      }
      return ii->second;
    }

    
    inline FunctionRegister::FunctionDefinition const&FunctionRegister::_getDefinition(FunctionID id)const{
      assert(this!=nullptr);
      auto ii=this->_functions.find(id);
      if(ii==this->_functions.end()){
        std::cerr<<"ERROR - FunctionRegister::_getDefinition("<<id<<") - ";
        std::cerr<<"there is no such function id"<<std::endl;
        return this->_functions.find(0)->second;
      }
      return ii->second;
    }

    inline TypeRegister::TypeID FunctionRegister::getType(FunctionID id)const{
      assert(this!=nullptr);
      return std::get<TYPE>(this->_getDefinition(id));
    }

    inline std::string FunctionRegister::getName(FunctionID id)const{
      assert(this!=nullptr);
      return std::get<NAME>(this->_getDefinition(id));
    }

    inline std::shared_ptr<StatementFactory>FunctionRegister::getFactory(FunctionID id)const{
      assert(this!=nullptr);
      return std::get<FACTORY>(this->_getDefinition(id));
    }

    inline FunctionRegister::FunctionID FunctionRegister::getFunctionId(std::string name)const{
      assert(this!=nullptr);
      auto ii=this->_name2Function.find(name);
      if(ii==this->_name2Function.end()){
        std::cerr<<"ERROR - FunctionRegister::getFunctionId("<<name<<") - ";
        std::cerr<<"there is no such function name"<<std::endl;
        return 0;
      }
      return ii->second;
    }

    inline FunctionRegister::InputIndex FunctionRegister::getNofInputs(FunctionID id)const{
      assert(this!=nullptr);
      assert(this->_typeRegister!=nullptr);
      auto t=this->getType(id);
      if(t==TypeRegister::getTypeTypeId<TypeRegister::Unregistered>()){
        std::cerr<<"ERROR - FunctionRegister::getNofInputs("<<id<<") - ";
        std::cerr<<"there is no such function"<<std::endl;
        return 0;
      }
      return this->_typeRegister->getNofFceArgs(t);
    }

    inline std::string FunctionRegister::getOutputName(FunctionID id)const{
      assert(this!=nullptr);
      return std::get<OUTPUTNAME>(this->_getDefinition(id));
    }

    inline std::string FunctionRegister::getInputName(FunctionID id,InputIndex input)const{
      assert(this!=nullptr);
      auto ii=std::get<INDEX2NAME>(this->_getDefinition(id)).find(input);
      if(ii==std::get<INDEX2NAME>(this->_getDefinition(id)).end()){
        std::cerr<<"ERROR - FunctionRegister::getInputName("<<id<<","<<input<<") - ";
        std::cerr<<"there is no such input"<<std::endl;
        return "";
      }
      return ii->second;
    }

    inline TypeRegister::TypeID FunctionRegister::getInputType(FunctionID id,InputIndex input)const{
      assert(this!=nullptr);
      assert(this->_typeRegister!=nullptr);
      auto type = this->getType(id);
      return this->_typeRegister->getFceArgTypeId(type,input);
    }

    inline TypeRegister::TypeID FunctionRegister::getOutputType(FunctionID id)const{
      assert(this!=nullptr);
      assert(this->_typeRegister!=nullptr);
      auto type = this->getType(id);
      return this->_typeRegister->getFceReturnTypeId(type);
    }


    inline FunctionRegister::InputIndex FunctionRegister::getInputIndex(FunctionID id,std::string name)const{
      assert(this!=nullptr);
      auto def = this->_getDefinition(id);
      if(std::get<TYPE>(def)==TypeRegister::getTypeTypeId<TypeRegister::Unregistered>()){
        std::cerr<<"ERROR - FunctionRegister::getInputIndex("<<id<<","<<name<<") - ";
        std::cerr<<"there is no such function"<<std::endl;
        return 0;
      }
      auto ii=std::get<NAME2INDEX>(this->_getDefinition(id)).find(name);
      if(ii==std::get<NAME2INDEX>(this->_getDefinition(id)).end()){
        std::cerr<<"ERROR - FunctionRegister::getInputIndex("<<id<<","<<name<<") - ";
        std::cerr<<"there is no such input"<<std::endl;
        return 0;
      }
      return ii->second;
    }

    inline void FunctionRegister::setInputName(FunctionID id,InputIndex input,std::string name){
      assert(this!=nullptr);
      FunctionDefinition& def = this->_getDefinition(id);
      if(std::get<TYPE>(def)==TypeRegister::getTypeTypeId<TypeRegister::Unregistered>()){
        std::cerr<<"ERROR - FunctionRegister::setInputName("<<id<<","<<input<<","<<name<<") - ";
        std::cerr<<"there is no such function"<<std::endl;
        return;
      }

      if(name=="")name=this->_genDefaultName(input);

      auto jj=std::get<NAME2INDEX>(def).find(name);
      if(jj!=std::get<NAME2INDEX>(def).end()&&jj->second!=input){
        std::cerr<<"ERROR: "<<std::get<NAME>(def)<<"::setInputName("<<input<<","
          <<name<<")";
        std::cerr<<" - name "<<name<<" is already used for input number: ";
        std::cerr<<jj->second<<std::endl;
        return;
      }
      auto ii=std::get<INDEX2NAME>(def).find(input);
      if(ii!=std::get<INDEX2NAME>(def).end()){
        if(std::get<NAME2INDEX>(def).find(ii->second)!=std::get<NAME2INDEX>(def).end())
          std::get<NAME2INDEX>(def).erase(ii->second);
        std::get<INDEX2NAME>(def).erase(input);
      }
      std::get<NAME2INDEX>(def)[name ] = input;
      std::get<INDEX2NAME>(def)[input] = name ;
    }

    inline void FunctionRegister::setOutputName(FunctionID id,std::string name){
      assert(this!=nullptr);
      FunctionDefinition &def = this->_getDefinition(id);
      if(std::get<TYPE>(def)==TypeRegister::getTypeTypeId<TypeRegister::Unregistered>()){
        std::cerr<<"ERROR - FunctionRegister::setOutputName("<<id<<","<<name<<") - ";
        std::cerr<<"there is no such function"<<std::endl;
        return;
      }
      std::get<OUTPUTNAME>(def)=name;
    }

    inline std::shared_ptr<TypeRegister>const&FunctionRegister::getTypeRegister()const{
      assert(this!=nullptr);
      return this->_typeRegister;
    }

    inline void FunctionRegister::addImplementation(FunctionID id,Implementation impl){
      assert(this!=nullptr);
      this->_implementations[id]=impl;
    }
    
    inline void FunctionRegister::addImplementation(std::string name,Implementation impl){
      assert(this!=nullptr);
      this->addImplementation(this->getFunctionId(name),impl);
    }

    inline FunctionRegister::Implementation FunctionRegister::getImplementation(FunctionID id)const{
      assert(this!=nullptr);
      assert(this->_implementations.count(id)!=0);
      return this->_implementations.find(id)->second;
    }

    inline FunctionRegister::Implementation FunctionRegister::getImplementation(std::string name)const{
      assert(this!=nullptr);
      return this->getImplementation(this->getFunctionId(name));
    }



  }
}
