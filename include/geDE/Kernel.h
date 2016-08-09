#pragma once

#include<geDE/Export.h>
#include<memory>
#include<vector>
#include<geCore/ErrorPrinter.h>
#include<geDE/TypeRegister.h>
#include<geDE/FunctionRegister.h>
#include<geDE/NameRegister.h>
#include<geDE/VariableRegister.h>
#include<geDE/StdFunctions.h>
#include<geDE/FunctionNodeFactory.h>
#include<geDE/CompositeFunctionFactory.h>
#include<geDE/CompositeFunction.h>
#include<geDE/ResourceFactory.h>

namespace ge{
  namespace de{
    class GEDE_EXPORT Kernel{
      public:
        using RFNT = std::tuple<std::shared_ptr<Resource>,std::shared_ptr<Function>,std::string>;
        class RFN: public RFNT{
          public:
            RFN(std::shared_ptr<Resource>const&res):RFNT(res,nullptr,""){}
            RFN(std::shared_ptr<Function>const&fce):RFNT(nullptr,fce,""){}
            RFN(std::string const&name):RFNT(nullptr,nullptr,name){}
        };
        enum{
          RESOURCE = 0,
          FUNCTION = 1,
          NAME     = 2,
        };
        Kernel();
        ~Kernel();
        bool addEmptyVariable(std::string const&name,std::string const&type);
        void removeVariable(std::string const&name);
        void addCommand(std::shared_ptr<Statement>const&command);
        void run();
        void restart();
        std::shared_ptr<TypeRegister    >typeRegister    ;
        std::shared_ptr<FunctionRegister>functionRegister;
        std::shared_ptr<NameRegister    >nameRegister    ;
        std::shared_ptr<VariableRegister>variableRegister;
        std::vector<std::shared_ptr<Statement>>commands;
        size_t currentCommand = 0;
        template<typename T>
        std::shared_ptr<Resource>createVariable(T const&val);
        std::shared_ptr<Resource>createResource(std::string const&name);
        std::shared_ptr<Function>createFunction2(
            std::string              const&name  ,
            std::vector<RFN>         const&inputs,
            std::shared_ptr<Resource>const&output);
        std::shared_ptr<Function>createFunction2(
            std::string     const&name        ,
            std::vector<RFN>const&inputs      ,
            std::string     const&variableName);
        std::shared_ptr<Function>createFunction2(
            std::string     const&name  ,
            std::vector<RFN>const&inputs);
        std::shared_ptr<Function>createFunction(
            std::string             const&name        ,
            std::vector<std::string>const&inputNames  ,
            std::string             const&variableName);
        std::shared_ptr<Function>createFunction(
            std::string              const&name      ,
            std::vector<std::string> const&inputNames,
            std::shared_ptr<Resource>const&output    );
        std::shared_ptr<Function>createFunction(
            std::string              const&name      ,
            std::vector<std::string> const&inputNames);

        std::shared_ptr<Resource>const&variable(std::string const&name)const;
        template<typename T>
          bool addVariable(std::string const&name,T const&val);
        template<typename OUTPUT,typename...ARGS>
          FunctionId addFunction(
              std::vector<std::string>const&names,
              OUTPUT(*fce)(ARGS...),
              bool(*sig)(ARGS...) = nullptr);
        template<typename OUTPUT,typename CLASS,typename...ARGS>
          FunctionId addFunction(
              std::vector<std::string>const&names,
              OUTPUT(CLASS::*fce)(ARGS...),
              bool(*sig)(ARGS...) = nullptr);
        FunctionId addCompositeFunction(
            std::vector<std::string>const&names,
            std::shared_ptr<CompositeFunctionFactory>const&factory);
        void bindInput(
            std::shared_ptr<Function>const&fce,
            std::vector<RFN>         const&inputs);
        void bindOutput(
            std::shared_ptr<Function>const&fce,
            std::shared_ptr<Resource>const&output);
        TypeId addAtomicType(
            std::string               const&name                 ,
            size_t                    const&size                 ,
            CDPtr const&constructor = nullptr,
            CDPtr const&destructor  = nullptr);
        TypeId addCompositeType(
            std::string           const&name       ,
            TypeDescriptionVector const&description);
        TypeId addStructType(
            std::string           const&name,
            TypeDescriptionVector const&typeids);
        TypeId addStructType(
            std::string             const&name     ,
            std::vector<std::string>const&typeNames);
        TypeId addArrayType(
            std::string const&name     ,
            size_t            size     ,
            TypeId            innerType);
        TypeId addArrayType(
            std::string const&name     ,
            size_t            size     ,
            std::string const&innerType);
        std::shared_ptr<FunctionNodeFactory>createFunctionNodeFactory(
            std::string name,
            std::string functionName,
            std::vector<std::shared_ptr<StatementFactory>>const&inputFunctionFactories = {});/*,
            std::vector<std::shared_ptr<ResourceFactory>>const&inputResourceFactories = {});*/
        /*
        std::shared_ptr<FunctionNodeFactory>createFunctionNodeFactory(
            std::string name,
            std::string functionName,
            std::vector<std::shared_ptr<StatementFactory>>const&inputFunctionFactories,
            std::vector<std::string>const&inputResourceFactoryNames);
            */
        std::shared_ptr<CompositeFunctionFactory>createCompositeFunctionFactory(
            std::string const&name,
            std::shared_ptr<FunctionNodeFactory>const&root,
            std::vector<std::vector<std::shared_ptr<FunctionNodeFactory>>>const&inputs,
            std::vector<std::vector<size_t>>const&inputIndices);
           

        std::shared_ptr<ResourceFactory>createResourceFactory(
            std::string name);
        template<typename CLASS>
          TypeId addAtomicClass(std::string const&name);
    };

    template<typename T>
      std::shared_ptr<Resource>Kernel::createVariable(T const&val){
        assert(this!=nullptr);
        assert(this->functionRegister!=nullptr);
        assert(this->typeRegister!=nullptr);
        auto result = this->typeRegister->sharedResource(keyword<T>());
        *result = val;
        return result;
      }
    template<typename T>
      bool Kernel::addVariable(std::string const&name,T const&val){
        assert(this!=nullptr);
        assert(this->variableRegister!=nullptr);
        return this->variableRegister->insert(name,this->createVariable(val));
      }
    template<typename OUTPUT,typename...ARGS>
      FunctionId Kernel::addFunction(
          std::vector<std::string>const&names,
          OUTPUT(*fce)(ARGS...),
          bool(*sig)(ARGS...)){
        assert(this!=nullptr);
        assert(this->functionRegister!=nullptr);
        assert(this->nameRegister!=nullptr);
        if(names.size()==0){
          ge::core::printError(GE_CORE_FCENAME,"at least function name has to be specified",names,fce,sig);
          return 0;
        }
        auto ret = registerBasicFunction(this->functionRegister,names[0],fce,sig);
        if(names.size()>1)
          this->nameRegister->setFceOutputName(ret,names[1]);
        for(size_t i=2;i<names.size();++i)
          this->nameRegister->setFceInputName(ret,i-2,names[i]);
        return ret;
      }
    template<typename OUTPUT,typename CLASS,typename...ARGS>
      FunctionId Kernel::addFunction(
          std::vector<std::string>const&names,
          OUTPUT(CLASS::*fce)(ARGS...),
          bool(*sig)(ARGS...)){
        assert(this!=nullptr);
        assert(this->functionRegister!=nullptr);
        assert(this->nameRegister!=nullptr);
        if(names.size()==0){
          ge::core::printError(GE_CORE_FCENAME,"at least function name has to be specified",names,fce,sig);
          return 0;
        }
        auto ret = registerClassFunction(this->functionRegister,names[0],fce,sig);
        if(names.size()>1)
          this->nameRegister->setFceOutputName(ret,names[1]);
        for(size_t i=2;i<names.size();++i)
          this->nameRegister->setFceInputName(ret,i-2,names[i]);
        return ret;
      }


    template<typename CLASS>
      TypeId Kernel::addAtomicClass(std::string const&name){
        assert(this!=nullptr);
        assert(this->typeRegister!=nullptr);
        auto result = this->typeRegister->addAtomicType(name,sizeof(CLASS));
        this->typeRegister->addConstructor(result,[](void*ptr){new(ptr)CLASS;});
        this->typeRegister->addDestructor(result,[](void*ptr){((CLASS*)ptr)->~CLASS();});
        return result;
      }


  }
}
