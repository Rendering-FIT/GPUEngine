#pragma once

#include<geDE/Statement.h>
#include<geDE/Types.h>

namespace ge{
  namespace de{

    // function: Resource compositor
    // function: selector of element of Resource

    class Resource;
    class AtomicFunction;
    class CompositeFunction;
    class Nullary;
    class FunctionRegister;
    class GEDE_EXPORT Function: public Statement{
      friend class AtomicFunction;
      friend class CompositeFunction;
      public:
        using Ticks = uint64_t;
        Function(
            std::shared_ptr<FunctionRegister>const&fr,
            FunctionId                             id);
        virtual ~Function();
        FunctionId getId()const;
        virtual bool bindInput (
            std::shared_ptr<FunctionRegister>const&fr                ,
            size_t                                 i                 ,
            std::shared_ptr<Function>        const&function = nullptr) = 0;
        virtual bool bindOutput(
            std::shared_ptr<FunctionRegister>const&fr            ,
            std::shared_ptr<Resource>        const&data = nullptr) = 0;
        virtual bool bindOutput(
            std::shared_ptr<FunctionRegister>const&fr     ,
            std::shared_ptr<Nullary>         const&nullary) = 0;
        virtual bool hasInput(size_t i)const = 0;
        virtual bool hasOutput()const = 0; 
        virtual std::shared_ptr<Resource>const&getInputData(size_t i)const = 0;
        virtual std::shared_ptr<Resource>const&getOutputData()const = 0;
        virtual std::shared_ptr<Function>const&getInputFunction(size_t i)const = 0;
        virtual std::shared_ptr<Function>toFunction()const override;
      protected:
        Statement* _outputNullary = nullptr;
        FunctionId _id;
        bool _inputBindingCheck (
            std::shared_ptr<FunctionRegister>const&fr      ,
            size_t                                 i       ,
            std::shared_ptr<Function>        const&function)const;
        bool _outputBindingCheck(
            std::shared_ptr<FunctionRegister>const&fr      ,
            std::shared_ptr<Resource>        const&resource)const;
    };

    inline Function::Function(
        std::shared_ptr<FunctionRegister>const&,
        FunctionId id):Statement(FUNCTION){
      assert(this!=nullptr);
      this->_id = id;
    }

    inline Function::~Function(){
    }

    inline FunctionId Function::getId()const{
      return this->_id;
    }

    inline std::shared_ptr<Function>Function::toFunction()const{
      assert(this!=nullptr);
      return std::dynamic_pointer_cast<Function>(std::const_pointer_cast<Statement>(this->shared_from_this()));
    }
  }
}

