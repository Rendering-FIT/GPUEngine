#pragma once

#include<geDE/Function.h>
#include<map>

namespace ge{
  namespace de{
    class GEDE_EXPORT AtomicFunctionInput{
      public:
        bool                     changed     = false  ;
        Ticks                    updateTicks = 0      ;
        std::shared_ptr<Resource>resource    = nullptr;
        std::shared_ptr<Function>function    = nullptr;
        AtomicFunctionInput(
            std::shared_ptr<Resource>const&resource    = nullptr,
            Function::Ticks                updateTicks = 0      ,
            bool                           changed     = false  );
        AtomicFunctionInput(
            std::shared_ptr<Function>const&function             ,
            Function::Ticks                updateTicks = 0      ,
            bool                           changed     = false  );
        virtual ~AtomicFunctionInput();
    };

    class StatementFactory;

    class GEDE_EXPORT AtomicFunction: public Function{
      public:
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr               ,
            FunctionId                             id               ,
            bool                                   ignore    = false);
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr               ,
            TypeId                                 type             ,
            std::string                      const&name             ,
            std::shared_ptr<StatementFactory>const&factory = nullptr,
            bool                                   ignore    = false);
        virtual ~AtomicFunction();
        virtual void operator()()override;
        virtual bool bindInput (
            std::shared_ptr<FunctionRegister>const&fr          ,
            size_t                                 i           ,
            std::shared_ptr<Function>        const&f  = nullptr)override;
        virtual bool bindInputAsVariable (
            std::shared_ptr<FunctionRegister>const&fr,
            size_t                                 i ,
            std::shared_ptr<Resource>        const&r )override;
        virtual bool bindOutput(
            std::shared_ptr<FunctionRegister>const&fr            ,
            std::shared_ptr<Resource>        const&data = nullptr)override;
        virtual void unbindInput(size_t i)override;
        virtual void unbindOutput()override;
        virtual bool hasInput(size_t i)const override;
        virtual bool hasOutput()const override;
        virtual size_t getNofInputs()const override;
        virtual std::shared_ptr<Resource>const&getInputData(size_t i)const override;
        virtual std::shared_ptr<Resource>const&getOutputData()const override;
        virtual std::shared_ptr<Function>const&getInputFunction(size_t i)const override;
        virtual bool isIgnoringInputChanges()const override;
        virtual void setIgnoreInputChanges(bool ignore = false)override;
      protected:
        bool _ignoreInputChanges = false;
        std::vector<AtomicFunctionInput>_inputs;
        std::map<std::shared_ptr<Function>,size_t>_fces;
        std::shared_ptr<Resource>_outputData  = nullptr;
        bool _processInputs();
        virtual bool _do();
        inline bool _inputChanged(size_t i)const;
    };

    inline std::shared_ptr<Resource>const&AtomicFunction::getOutputData()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_outputData;
    }

    inline bool AtomicFunction::hasInput(size_t i)const{
      PRINT_CALL_STACK(i);
      assert(this!=nullptr);
      assert(i<this->_inputs.size());
      return this->_inputs.at(i).resource!=nullptr || this->_inputs.at(i).function!=nullptr;
    }

    inline bool AtomicFunction::hasOutput()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_outputData!=nullptr;
    }

    inline size_t AtomicFunction::getNofInputs()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_inputs.size();
    }

    inline std::shared_ptr<Resource>const&AtomicFunction::getInputData(size_t i)const{
      PRINT_CALL_STACK(i);
      assert(this!=nullptr);
      assert(i<this->_inputs.size());
      if(this->_inputs.at(i).function)
        return this->_inputs.at(i).function->getOutputData();
      return this->_inputs.at(i).resource;
    }

    inline bool AtomicFunction::_inputChanged(size_t i)const{
      PRINT_CALL_STACK(i);
      assert(this!=nullptr);
      assert(i<this->_inputs.size());
      return this->_inputs.at(i).changed;
    }
    inline bool AtomicFunction::isIgnoringInputChanges()const{
      PRINT_CALL_STACK(i);
      assert(this!=nullptr);
      return this->_ignoreInputChanges;
    }

    inline void AtomicFunction::setIgnoreInputChanges(bool ignore){
      PRINT_CALL_STACK(i);
      assert(this!=nullptr);
      this->_ignoreInputChanges = ignore;
    }

  }
}
