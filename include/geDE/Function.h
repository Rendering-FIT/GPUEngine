#pragma once

#include<geCore/CallStackPrinter.h>
#include<geDE/Statement.h>
#include<geDE/Types.h>

namespace ge{
  namespace de{

    // function: Resource compositor
    // function: selector of element of Resource

    class Resource;
    class AtomicFunction;
    class CompositeFunction;
    class FunctionRegister;
    class GEDE_EXPORT Function: public Statement{
      friend class Resource;
      friend class AtomicFunction;
      friend class CompositeFunction;
      public:
        Function(
            std::shared_ptr<FunctionRegister>const&fr               ,
            FunctionId                             id               ,
            bool                                   ignore    = false);
        virtual ~Function();
        FunctionId getId()const;
        virtual bool bindInput (
            std::shared_ptr<FunctionRegister>const&fr          ,
            size_t                                 i           ,
            std::shared_ptr<Function>        const&f  = nullptr) = 0;
        virtual bool bindInputAsVariable(
            std::shared_ptr<FunctionRegister>const&fr,
            size_t                                 i ,
            std::shared_ptr<Resource>        const&r ) = 0;
        virtual bool bindOutput(
            std::shared_ptr<FunctionRegister>const&fr            ,
            std::shared_ptr<Resource>        const&data = nullptr) = 0;
        virtual void unbindInput(size_t i) = 0;
        virtual void unbindOutput() = 0;
        virtual bool hasInput(size_t i)const = 0;
        virtual bool hasOutput()const = 0; 
        virtual size_t getNofInputs()const = 0;
        virtual std::shared_ptr<Resource>const&getInputData(size_t i)const = 0;
        virtual std::shared_ptr<Resource>const&getOutputData()const = 0;
        virtual std::shared_ptr<Function>toFunction()const override;
        virtual void setSignalingDirty()override;
        virtual std::shared_ptr<Function>const&getInputFunction(size_t i)const = 0;
        bool hasTargetResource(Resource*r)const;
        bool hasSourceResource(Resource*r)const;
        size_t nofTargetResources()const;
        size_t nofSourceResources()const;
        virtual bool isIgnoringInputChanges()const = 0;
        virtual void setIgnoreInputChanges(bool ignore = false) = 0;
      protected:
        FunctionId _id;
        bool _inputBindingCheck (
            std::shared_ptr<FunctionRegister>const&fr      ,
            size_t                                 i       ,
            std::shared_ptr<Function>        const&function)const;
        bool _inputBindingCheck (
            std::shared_ptr<FunctionRegister>const&fr      ,
            size_t                                 i       ,
            std::shared_ptr<Resource>        const&resource)const;
        bool _outputBindingCheck(
            std::shared_ptr<FunctionRegister>const&fr      ,
            std::shared_ptr<Resource>        const&resource)const;

        bool _outputBindingCircularCheck(
            std::shared_ptr<FunctionRegister>const&fr      ,
            std::shared_ptr<Resource>        const&resource)const;
        bool _inputBindingCircularCheck(
            std::shared_ptr<FunctionRegister>const&fr      ,
            std::shared_ptr<Function>        const&function)const;

        bool _recOutputBindingCircularCheck(
            std::shared_ptr<FunctionRegister>const&fr      ,
            std::set<Function const*>             &visited ,
            std::shared_ptr<Resource>        const&resource)const;
        std::set<Resource*>_targetResources;
        std::set<Resource*>_sourceResources;
        virtual void _addTargetResource(Resource*r);
        virtual void _removeTargetResource(Resource*r);
        virtual void _addSourceResource(Resource*r);
        virtual void _removeSourceResource(Resource*r);
    };

    inline Function::Function(
        std::shared_ptr<FunctionRegister>const&,
        FunctionId id,
        bool ignore):Statement(FUNCTION,ignore){
      assert(this!=nullptr);
      this->_id = id;
    }

    inline FunctionId Function::getId()const{
      assert(this!=nullptr);
      return this->_id;
    }

    inline std::shared_ptr<Function>Function::toFunction()const{
      assert(this!=nullptr);
      return std::dynamic_pointer_cast<Function>(std::const_pointer_cast<Statement>(this->shared_from_this()));
    }
    
    inline void Function::_addTargetResource(Resource*r){
      PRINT_CALL_STACK(r);
      assert(this!=nullptr);
      this->_targetResources.insert(r);
    }

    inline void Function::_removeTargetResource(Resource*r){
      PRINT_CALL_STACK(r);
      assert(this!=nullptr);
      this->_targetResources.erase(r);
    }

    inline void Function::_addSourceResource(Resource*r){
      PRINT_CALL_STACK(r);
      assert(this!=nullptr);
      this->_sourceResources.insert(r);
    }

    inline void Function::_removeSourceResource(Resource*r){
      PRINT_CALL_STACK(r);
      assert(this!=nullptr);
      this->_sourceResources.erase(r);
    }

    inline bool Function::hasTargetResource(Resource*r)const{
      PRINT_CALL_STACK(r);
      assert(this!=nullptr);
      return this->_targetResources.count(r)!=0;
    }

    inline bool Function::hasSourceResource(Resource*r)const{
      PRINT_CALL_STACK(r);
      assert(this!=nullptr);
      return this->_sourceResources.count(r)!=0;
    }

    inline size_t Function::nofTargetResources()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_targetResources.size();
    }

    inline size_t Function::nofSourceResources()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_sourceResources.size();
    }


  }
}

