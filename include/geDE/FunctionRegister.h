#pragma once

#include<utility>
#include<tuple>
#include<geDE/Export.h>
#include<geDE/TypeRegister.h>
#include<geDE/StatementFactory.h>
#include<geDE/Statement.h>
#include<geDE/NameRegister.h>

namespace ge{
  namespace de{
    class Statement;
    class Function;

    /**
     * @brief FunctionRegister can register functions' factories
     * It can create new shared instances of registered functions
     * A function that is registered is described using 3 values
     * type of the function
     * name of the function
     * factory of the function
     * every triplet is associated with unique id - FunctionId.
     * FunctionRegister can also register precompiled function from
     * 3rd party libraries.
     * Every 3rd party function's pointer can be stored
     */
    class Empty;
    class GEDE_EXPORT FunctionRegister: public std::enable_shared_from_this<FunctionRegister>{
      public:
        typedef void(*Implementation)();
        typedef bool(*SignalingDecider)();
        class CLSImpl{};
        using InputIndex = size_t;
        inline FunctionRegister(
            std::shared_ptr<TypeRegister>const&typeRegister,
            std::shared_ptr<NameRegister>const&namer       );
        inline ~FunctionRegister();
        FunctionId addFunction(
            TypeId                           const&type   ,
            std::string                      const&name   ,
            std::shared_ptr<StatementFactory>const&factory);
        TypeId                           getType   (FunctionId id)const;
        std::string                      getName   (FunctionId id)const;
        std::shared_ptr<StatementFactory>getFactory(FunctionId id)const;
        FunctionId getFunctionId(std::string const&name)const;
        InputIndex  getNofInputs (FunctionId id)const;
        std::string getOutputName(FunctionId id)const;
        std::string getInputName (FunctionId id,InputIndex input)const;
        TypeId     getInputType (FunctionId id,InputIndex input)const;
        TypeId     getOutputType(FunctionId id)const;
        InputIndex getInputIndex(FunctionId id,std::string const&name)const;
        std::shared_ptr<TypeRegister>const&getTypeRegister()const;
        std::shared_ptr<NameRegister>const&getNameRegister()const;
        void addImplementation(FunctionId  id  ,Implementation impl);
        void addImplementation(std::string const&name,Implementation impl);
        Implementation getImplementation(FunctionId  id  )const;
        Implementation getImplementation(std::string const&name)const;
        void addSignalingDecider(FunctionId id,SignalingDecider sig);
        void addSignalingDecider(std::string const&name,SignalingDecider sig);
        SignalingDecider getSignalingDecider(FunctionId id)const;
        SignalingDecider getSignalingDecider(std::string const&name)const;
        void addClassImplementation(FunctionId id,CLSImpl* impl);
        void addClassImplementation(std::string const&name,CLSImpl* impl);
        CLSImpl* getClassImplementation(FunctionId id)const;
        CLSImpl* getClassImplementation(std::string const&name)const;
        std::shared_ptr<Function>sharedFunction(FunctionId  id  )const;
        std::shared_ptr<Function>sharedFunction(std::string const&name)const;
        std::shared_ptr<Statement>sharedStatement(FunctionId  id  )const;
        std::shared_ptr<Statement>sharedStatement(std::string const&name)const;
        std::shared_ptr<StatementFactory>sharedFactory(FunctionId  id  ,StatementFactory::Uses maxUses = 0)const;
        std::shared_ptr<StatementFactory>sharedFactory(std::string const&name,StatementFactory::Uses maxUses = 0)const;
        std::string str()const;
      protected:
        using FunctionDefinition = std::tuple<
          TypeId,
          std::string,
          std::shared_ptr<StatementFactory>>;
        enum FunctionDefinitionParts{
          TYPE    = 0,
          NAME    = 1,
          FACTORY = 2,
        };
        std::shared_ptr<NameRegister>       _namer;
        std::shared_ptr<TypeRegister>_typeRegister;
        std::map<FunctionId,FunctionDefinition>_functions;
        std::map<FunctionId,Implementation>_implementations;
        std::map<FunctionId,SignalingDecider>_signalingDeciders;
        std::map<FunctionId,CLSImpl*>_classImplementations;
        std::map<std::string,FunctionId>_name2Function;
        inline FunctionDefinition      & _getDefinition(FunctionId id);
        inline FunctionDefinition const& _getDefinition(FunctionId id)const;
        std::string _genDefaultName(InputIndex i)const;

    };

    inline FunctionRegister::FunctionRegister(
        std::shared_ptr<TypeRegister>const&typeRegister,
        std::shared_ptr<NameRegister>const&namer){
      PRINT_CALL_STACK(typeRegister,namer);
      assert(this!=nullptr);
      assert(typeRegister!=nullptr);
      this->_typeRegister = typeRegister;
      this->_functions[0]=FunctionDefinition(
          TypeRegister::UNREGISTERED,
          "unregistered",
          nullptr);
      this->_namer = namer;
    }


    inline FunctionRegister::~FunctionRegister(){
      PRINT_CALL_STACK();
      for(auto const&x:this->_classImplementations)
         delete x.second;
    }

    inline FunctionRegister::FunctionDefinition &FunctionRegister::_getDefinition(FunctionId id){
      PRINT_CALL_STACK(id);
      assert(this!=nullptr);
      auto ii=this->_functions.find(id);
      if(ii==this->_functions.end()){
        ge::core::printError("FunctionRegister::_getDefinition","there is no such function id",id);
        return this->_functions.find(0)->second;
      }
      return ii->second;
    }

    
    inline FunctionRegister::FunctionDefinition const&FunctionRegister::_getDefinition(FunctionId id)const{
      PRINT_CALL_STACK(id);
      assert(this!=nullptr);
      auto ii=this->_functions.find(id);
      if(ii==this->_functions.end()){
        ge::core::printError("FunctionRegister::_getDefinition","there is no such function id",id);
        return this->_functions.find(0)->second;
      }
      return ii->second;
    }

    inline TypeId FunctionRegister::getType(FunctionId id)const{
      PRINT_CALL_STACK(id);
      assert(this!=nullptr);
      return std::get<TYPE>(this->_getDefinition(id));
    }

    inline std::string FunctionRegister::getName(FunctionId id)const{
      PRINT_CALL_STACK(id);
      assert(this!=nullptr);
      return std::get<NAME>(this->_getDefinition(id));
    }

    inline std::shared_ptr<StatementFactory>FunctionRegister::getFactory(FunctionId id)const{
      PRINT_CALL_STACK(id);
      assert(this!=nullptr);
      return std::get<FACTORY>(this->_getDefinition(id));
    }

    inline FunctionId FunctionRegister::getFunctionId(std::string const&name)const{
      PRINT_CALL_STACK(name);
      assert(this!=nullptr);
      auto ii=this->_name2Function.find(name);
      if(ii==this->_name2Function.end()){
        ge::core::printError("FunctionRegister::getFunctionId","there is no such function name",name);
        return 0;
      }
      return ii->second;
    }

    inline FunctionRegister::InputIndex FunctionRegister::getNofInputs(FunctionId id)const{
      PRINT_CALL_STACK(id);
      assert(this!=nullptr);
      assert(this->_typeRegister!=nullptr);
      auto t=this->getType(id);
      if(t==TypeRegister::UNREGISTERED){
        ge::core::printError("FunctionRegister::getNofInputs","there is no such function",id);
        return 0;
      }
      return this->_typeRegister->getNofFceArgs(t);
    }

    inline std::string FunctionRegister::getOutputName(FunctionId id)const{
      PRINT_CALL_STACK(id);
      assert(this!=nullptr);
      assert(this->_namer!=nullptr);
      return this->_namer->getFceOutputName(id);
    }

    inline std::string FunctionRegister::getInputName(FunctionId id,InputIndex input)const{
      PRINT_CALL_STACK(id,input);
      assert(this!=nullptr);
      assert(this->_namer!=nullptr);
      return this->_namer->getFceInputName(id,input);
    }

    inline TypeId FunctionRegister::getInputType(FunctionId id,InputIndex input)const{
      PRINT_CALL_STACK(id,input);
      assert(this!=nullptr);
      assert(this->_typeRegister!=nullptr);
      auto type = this->getType(id);
      return this->_typeRegister->getFceArgTypeId(type,input);
    }

    inline TypeId FunctionRegister::getOutputType(FunctionId id)const{
      PRINT_CALL_STACK(id);
      assert(this!=nullptr);
      assert(this->_typeRegister!=nullptr);
      auto type = this->getType(id);
      return this->_typeRegister->getFceReturnTypeId(type);
    }


    inline FunctionRegister::InputIndex FunctionRegister::getInputIndex(FunctionId id,std::string const&name)const{
      PRINT_CALL_STACK(id,name);
      assert(this!=nullptr);
      assert(this->_namer!=nullptr);
      return this->_namer->getFceInput(id,name);
    }

    inline std::shared_ptr<TypeRegister>const&FunctionRegister::getTypeRegister()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_typeRegister;
    }

    inline std::shared_ptr<NameRegister>const&FunctionRegister::getNameRegister()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_namer;
    }

    inline void FunctionRegister::addImplementation(FunctionId id,Implementation impl){
      PRINT_CALL_STACK(id,impl);
      assert(this!=nullptr);
      this->_implementations[id]=impl;
    }
    
    inline void FunctionRegister::addImplementation(std::string const&name,Implementation impl){
      PRINT_CALL_STACK(name,impl);
      assert(this!=nullptr);
      this->addImplementation(this->getFunctionId(name),impl);
    }

    inline FunctionRegister::Implementation FunctionRegister::getImplementation(FunctionId id)const{
      PRINT_CALL_STACK(id);
      assert(this!=nullptr);
      assert(this->_implementations.count(id)!=0);
      return this->_implementations.find(id)->second;
    }

    inline FunctionRegister::Implementation FunctionRegister::getImplementation(std::string const&name)const{
      PRINT_CALL_STACK(name);
      assert(this!=nullptr);
      return this->getImplementation(this->getFunctionId(name));
    }

    inline void FunctionRegister::addSignalingDecider(FunctionId id,SignalingDecider sig){
      PRINT_CALL_STACK(id,sig);
      assert(this!=nullptr);
      this->_signalingDeciders[id]=sig;
    }

    inline void FunctionRegister::addSignalingDecider(std::string const&name,SignalingDecider sig){
      PRINT_CALL_STACK(name,sig);
      assert(this!=nullptr);
      this->addSignalingDecider(this->getFunctionId(name),sig);
    }

    inline FunctionRegister::SignalingDecider FunctionRegister::getSignalingDecider(FunctionId id)const{
      PRINT_CALL_STACK(id);
      assert(this!=nullptr);
      assert(this->_signalingDeciders.count(id)!=0);
      return this->_signalingDeciders.find(id)->second;
    }

    inline FunctionRegister::SignalingDecider FunctionRegister::getSignalingDecider(std::string const&name)const{
      PRINT_CALL_STACK(name);
      assert(this!=nullptr);
      return this->getSignalingDecider(this->getFunctionId(name));
    }

    inline void FunctionRegister::addClassImplementation(FunctionId id,CLSImpl* impl){
      PRINT_CALL_STACK(id,sig);
      assert(this!=nullptr);
      this->_classImplementations[id] = impl;
    }

    inline void FunctionRegister::addClassImplementation(std::string const&name,CLSImpl* impl){
      PRINT_CALL_STACK(name,impl);
      assert(this!=nullptr);
      this->addClassImplementation(this->getFunctionId(name),impl);
    }

    inline FunctionRegister::CLSImpl* FunctionRegister::getClassImplementation(FunctionId id)const{
      PRINT_CALL_STACK(id);
      assert(this!=nullptr);
      assert(this->_classImplementations.count(id)!=0);
      return this->_classImplementations.find(id)->second;
    }

    inline FunctionRegister::CLSImpl* FunctionRegister::getClassImplementation(std::string const&name)const{
      PRINT_CALL_STACK(name);
      assert(this!=nullptr);
      return this->getClassImplementation(this->getFunctionId(name));
    }
  }
}

