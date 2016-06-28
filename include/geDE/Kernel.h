#pragma once

#include<geDE/Export.h>
#include<memory>
#include<vector>
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
        Kernel();
        ~Kernel();
        bool addEmptyVariable(std::string const&type,std::string const&name);
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
        std::shared_ptr<Nullary>createVariable(T const&val);
        std::shared_ptr<Resource>createResource(std::string const&name);
        std::shared_ptr<Function>createFunction(std::string const&name,
            std::vector<std::shared_ptr<Function>>const&inputs = {},
            std::shared_ptr<Resource>const&output = nullptr);
        std::shared_ptr<Function>createFunction(std::string const&name,
            std::vector<std::shared_ptr<Function>>const&inputs,
            std::string const&outputType);
        std::shared_ptr<Function>createFunction(std::string const&name,
            std::vector<std::string>const&inputNames,
            std::string             const&outputType);

        std::shared_ptr<Nullary>const&variable(std::string const&name)const;
        template<typename T>
          bool addVariable(std::string const&name,T const&val);
        template<typename OUTPUT,typename...ARGS>
          FunctionRegister::FunctionID addFunction(
              std::vector<std::string>const&names,
              OUTPUT(*FCE)(ARGS...));

        FunctionRegister::FunctionID addCompositeFunction(
            std::vector<std::string>const&names,
            std::shared_ptr<CompositeFunctionFactory>const&factory);
        void bindInput(
            std::shared_ptr<Function>const&fce,
            std::vector<std::shared_ptr<Function>>const&inputs);
        void bindOutput(
            std::shared_ptr<Function>const&fce,
            std::shared_ptr<Resource>const&output);
        TypeRegister::TypeId addAtomicType(
            std::string               const&name                 ,
            size_t                    const&size                 ,
            TypeRegister::Constructor const&constructor = nullptr,
            TypeRegister::Destructor  const&destructor  = nullptr);
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
          TypeRegister::TypeId addAtomicClass(std::string const&name);
    };

    template<typename T>
      std::shared_ptr<Nullary>Kernel::createVariable(T const&val){
        auto fce = this->functionRegister->sharedFunction("Nullary");
        fce->bindOutput(this->functionRegister,this->typeRegister->sharedResource(TypeRegister::getTypeKeyword<T>()));
        *(T*)(*fce->getOutputData()) = val;
        return std::dynamic_pointer_cast<Nullary>(fce);
      }
    template<typename T>
      bool Kernel::addVariable(std::string const&name,T const&val){
        return this->variableRegister->insert(name,this->createVariable(val));
      }
    template<typename OUTPUT,typename...ARGS>
      FunctionRegister::FunctionID Kernel::addFunction(
          std::vector<std::string>const&names,
          OUTPUT(*FCE)(ARGS...)){
        if(names.size()==0){
          std::cerr<<"ERROR: Kernel::addFunction() - at least function name has to be specified"<<std::endl;
          return 0;
        }
        auto ret = registerBasicFunction(this->functionRegister,names[0],FCE);
        if(names.size()>1)
          this->nameRegister->setFceOutputName(ret,names[1]);
        for(size_t i=2;i<names.size();++i)
          this->nameRegister->setFceInputName(ret,i-2,names[i]);
        return ret;
      }

    template<typename CLASS>
      TypeRegister::TypeId Kernel::addAtomicClass(std::string const&name){
        auto result = this->typeRegister->addAtomicType(name,sizeof(CLASS));
        this->typeRegister->addConstructor(result,[](void*ptr){new(ptr)CLASS;});
        this->typeRegister->addDestructor(result,[](void*ptr){((CLASS*)ptr)->~CLASS();});
        return result;
      }


  }
}
