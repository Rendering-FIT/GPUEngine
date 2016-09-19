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
#include<geDE/RegisterBasicFunction.h>

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
        template<typename...ARGS>
          std::shared_ptr<Function>createFce(
              std::string const&name,
              ARGS... args);
        template<typename...ARGS>
          std::shared_ptr<Function>createAlwaysExecFce(
              std::string const&name,
              ARGS... args);



        std::shared_ptr<Resource>const&variable(std::string const&name)const;
        template<typename T>
          bool addVariable(std::string const&name,T const&val);
        template<typename OUTPUT,typename...ARGS>
          FunctionId addFunction(
              std::string const&fceName,
              std::vector<std::string>const&names,
              OUTPUT(*fce)(ARGS...),
              bool(*sig)(ARGS...) = nullptr);
        template<typename OUTPUT,typename CLASS,typename...ARGS>
          FunctionId addFunction(
              std::string const&fceName,
              std::vector<std::string>const&names,
              OUTPUT(CLASS::*fce)(ARGS...),
              bool(*sig)(ARGS...) = nullptr);
        template<typename OUTPUT,typename CLASS,typename...ARGS>
          FunctionId addFunction(
              std::string const&fceName,
              std::vector<std::string>const&names,
              OUTPUT(CLASS::*fce)(ARGS...)const,
              bool(*sig)(ARGS...) = nullptr);
        FunctionId addCompositeFunction(
            std::string const&fceName,
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
        TypeId addEnumType(
            std::string const&name,
            std::vector<EnumElementType>const&elements,
            std::vector<std::string>const&names);
        std::shared_ptr<FunctionNodeFactory>createFunctionNodeFactory(
            std::string functionName,
            std::vector<std::shared_ptr<StatementFactory>>const&inputFunctionFactories = {});
        std::shared_ptr<CompositeFunctionFactory>createCompositeFunctionFactory(
            std::shared_ptr<FunctionNodeFactory>const&root,
            std::vector<std::vector<std::shared_ptr<FunctionNodeFactory>>>const&inputs,
            std::vector<std::vector<size_t>>const&inputIndices);
        std::shared_ptr<ResourceFactory>createResourceFactory(
            std::string name);
        template<typename CLASS>
          TypeId addAtomicClass(std::string const&name = keyword<CLASS>());
        void nameFunctionInterface(TypeId id,std::vector<std::string>const&names);
      protected:
        inline std::shared_ptr<Resource>_getOutputFromArgs(){return nullptr;}
        inline std::shared_ptr<Resource>_getOutputFromArgs(std::shared_ptr<Resource>const&r){
          return r;
        }
        template<typename T,typename std::enable_if<!std::is_same<std::shared_ptr<Resource>,T>::value,unsigned>::type = 0>
          inline std::shared_ptr<Resource>_getOutputFromArgs(T const&){
            return nullptr;
          }
        inline std::shared_ptr<Resource>_getOutputFromArgs(std::string const&s){
          if(this->variableRegister->hasVariable(s))
            return this->variable(s);
          return this->createResource(s);
        }
        inline std::shared_ptr<Resource>_getOutputFromArgs(const char*s){
          if(this->variableRegister->hasVariable(s))
            return this->variable(s);
          return this->createResource(s);
        }
        template<typename HEAD,typename...TAIL,typename std::enable_if<sizeof...(TAIL)!=0,unsigned>::type = 0>
          inline std::shared_ptr<Resource>_getOutputFromArgs(HEAD const&,TAIL...args){
            return this->_getOutputFromArgs(args...);
          }

        template<typename LAST>
          inline void _getInputsFromArgsWithoutLast(std::vector<RFN>&,LAST const&){}
        inline void _getInputsFromArgsWithoutLast(std::vector<RFN>&){}
        inline void _addArgToInputs(std::vector<RFN>&inputs,std::string const&s){
          inputs.emplace_back(s);
        }
        inline void _addArgToInputs(std::vector<RFN>&inputs,const char*s){
          inputs.emplace_back(std::string(s));
        }
        inline void _addArgToInputs(std::vector<RFN>&inputs,std::shared_ptr<Function>const&f){
          inputs.emplace_back(f);
        }
        inline void _addArgToInputs(std::vector<RFN>&inputs,std::shared_ptr<Resource>const&r){
          inputs.emplace_back(r);
        }
        template<typename HEAD,typename...TAIL,typename std::enable_if<sizeof...(TAIL)!=0,unsigned>::type = 0>
          inline void _getInputsFromArgsWithoutLast(std::vector<RFN>&inputs,HEAD const&h,TAIL...args){
            this->_addArgToInputs(inputs,h);
            this->_getInputsFromArgsWithoutLast(inputs,args...);
          }

        inline void _getInputsFromArgs(std::vector<RFN>&){}
        template<typename HEAD>
          inline void _getInputsFromArgs(std::vector<RFN>&inputs,HEAD const&h){
            this->_addArgToInputs(inputs,h);
          }
        template<typename HEAD,typename...TAIL,typename std::enable_if<sizeof...(TAIL)!=0,unsigned>::type = 0>
          inline void _getInputsFromArgs(std::vector<RFN>&inputs,HEAD const&h,TAIL...args){
            this->_addArgToInputs(inputs,h);
            this->_getInputsFromArgs(inputs,args...);
          }

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
          std::string const&fceName,
          std::vector<std::string>const&names,
          OUTPUT(*fce)(ARGS...),
          bool(*sig)(ARGS...)){
        assert(this!=nullptr);
        assert(this->functionRegister!=nullptr);
        assert(this->nameRegister!=nullptr);
        auto ret = registerBasicFunction(this->functionRegister,fceName,fce,sig);
        this->nameFunctionInterface(ret,names);
        return ret;
      }
    template<typename OUTPUT,typename CLASS,typename...ARGS>
      FunctionId Kernel::addFunction(
          std::string const&fceName,
          std::vector<std::string>const&names,
          OUTPUT(CLASS::*fce)(ARGS...),
          bool(*sig)(ARGS...)){
        assert(this!=nullptr);
        assert(this->functionRegister!=nullptr);
        assert(this->nameRegister!=nullptr);
        auto ret = registerClassFunction(this->functionRegister,fceName,fce,sig);
        this->nameFunctionInterface(ret,names);
        return ret;
      }
    template<typename OUTPUT,typename CLASS,typename...ARGS>
      FunctionId Kernel::addFunction(
          std::string const&fceName,
          std::vector<std::string>const&names,
          OUTPUT(CLASS::*fce)(ARGS...)const,
          bool(*sig)(ARGS...)){
        assert(this!=nullptr);
        assert(this->functionRegister!=nullptr);
        assert(this->nameRegister!=nullptr);
        auto ret = registerClassFunction(this->functionRegister,fceName,fce,sig);
        this->nameFunctionInterface(ret,names);
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

    template<typename...ARGS>
      std::shared_ptr<Function>Kernel::createFce(
          std::string const&name,
          ARGS... args){
        assert(this!=nullptr);
        auto fr = this->functionRegister;
        assert(fr!=nullptr);
        auto tr = fr->getTypeRegister();
        assert(tr!=nullptr);
        auto result = fr->sharedFunction(name);
        std::vector<RFN>inputs;
        std::shared_ptr<Resource>output;
        if(sizeof...(ARGS)==1+fr->getNofInputs(result->getId())){
          this->_getInputsFromArgsWithoutLast(inputs,args...);
          output = this->_getOutputFromArgs(args...);
        }else{
          this->_getInputsFromArgs(inputs,args...);
          auto type = tr->getFceReturnTypeId(fr->getType(result->getId()));
          if(tr->getTypeIdType(type)==TypeRegister::VOID)
            output = nullptr;
          else
            output = tr->sharedResource(type);
        }
        this->bindInput(result,inputs);
        this->bindOutput(result,output);
        return result;
      }
    template<typename...ARGS>
      inline std::shared_ptr<Function>Kernel::createAlwaysExecFce(
          std::string const&name,
          ARGS... args){
        auto res = this->createFce(name,args...);
        res->setIgnoreDirty(true);
        res->setIgnoreInputChanges(true);
        return res;
      }



  }
}
