#pragma once

#include<geDE/Function.h>
#include<map>

namespace ge{
  namespace de{
    class GEDE_EXPORT AtomicFunctionInput{
      public:
        bool                     changed     = false  ;
        Function::Ticks          updateTicks = 0      ;
        std::shared_ptr<Function>function    = nullptr;
        AtomicFunctionInput(
            std::shared_ptr<Function>const&fce         = nullptr,
            Function::Ticks                updateTicks = 0      ,
            bool                           changed     = false  );
        virtual ~AtomicFunctionInput();
    };

    class StatementFactory;

    class GEDE_EXPORT AtomicFunction: public Function{
      public:
        using SharedFunction = std::shared_ptr<Function>;
        using SharedAtomicFunctionInput = std::shared_ptr<AtomicFunctionInput>;
        using Fce2FceInput = std::map<SharedFunction,SharedAtomicFunctionInput>;
        using InputList  = std::vector<SharedAtomicFunctionInput>;
      protected:
        InputList                _inputs               ;
        std::map<SharedFunction,std::set<size_t>>_fce2Indices;
        Fce2FceInput             _fce2FceInput        ;
        Function::Ticks          _updateTicks = 1      ;
        std::shared_ptr<Resource>_outputData  = nullptr;
      public:
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr,
            FunctionId                             id);
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr               ,
            TypeId                                 type             ,
            std::string                      const&name             ,
            std::shared_ptr<StatementFactory>const&factory = nullptr);
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr    ,
            FunctionId                             id    ,
            std::shared_ptr<Resource>        const&output);
        virtual ~AtomicFunction();
        virtual void operator()()override;
        virtual bool bindInput (
            std::shared_ptr<FunctionRegister>const&fr                ,
            size_t                                 i                 ,
            std::shared_ptr<Function>        const&function = nullptr)override;
        virtual bool bindOutput(
            std::shared_ptr<FunctionRegister>const&fr            ,
            std::shared_ptr<Resource>        const&data = nullptr)override;
        virtual bool bindOutput(
            std::shared_ptr<FunctionRegister>const&fr     ,
            std::shared_ptr<Nullary>         const&nullary)override;
        virtual bool hasInput(size_t i)const override;
        virtual bool hasOutput()const override;
        virtual std::shared_ptr<Resource>const&getInputData(size_t i)const override;
        virtual std::shared_ptr<Resource>const&getOutputData()const override;
        virtual Ticks getUpdateTicks()const override;
        virtual void setUpdateTicks(Ticks ticks)override;
        virtual std::shared_ptr<Function>const&getInputFunction(size_t i)const override;
      protected:
        bool _processInputs();
        virtual bool _do();
        inline bool _inputChanged(size_t i)const;
    };

    inline std::shared_ptr<Resource>const&AtomicFunction::getOutputData()const{
      assert(this!=nullptr);
      return this->_outputData;
    }

    inline bool AtomicFunction::hasInput(size_t i)const{
      assert(this!=nullptr);
      assert(i<this->_inputs.size());
      assert(this->_inputs.at(i)!=nullptr);
      return this->_inputs.at(i)->function!=nullptr;
    }

    inline Function::Ticks AtomicFunction::getUpdateTicks()const{
      assert(this!=nullptr);
      return this->_updateTicks;
    }

    inline void AtomicFunction::setUpdateTicks(Function::Ticks ticks){
      assert(this!=nullptr);
      this->_updateTicks = ticks;
    }

    inline std::shared_ptr<Function>const&AtomicFunction::getInputFunction(size_t i)const{
      assert(this!=nullptr);
      assert(i<this->_inputs.size());
      assert(this->_inputs.at(i)!=nullptr);
      return this->_inputs.at(i)->function;
    }

    inline bool AtomicFunction::hasOutput()const{
      assert(this!=nullptr);
      return this->_outputData!=nullptr;
    }

    inline std::shared_ptr<Resource>const&AtomicFunction::getInputData(size_t i)const{
      assert(this!=nullptr);
      assert(i<this->_inputs.size());
      assert(this->_inputs.at(i)!=nullptr);
      assert(this->_inputs.at(i)->function!=nullptr);
      return this->_inputs.at(i)->function->getOutputData();
    }

    inline bool AtomicFunction::_inputChanged(size_t i)const{
      assert(this!=nullptr);
      assert(i<this->_inputs.size());
      assert(this->_inputs.at(i)!=nullptr);
      return this->_inputs.at(i)->changed;
    }

  }
}
