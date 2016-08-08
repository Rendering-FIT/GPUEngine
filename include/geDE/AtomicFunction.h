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
        AtomicFunctionInput(
            std::shared_ptr<Resource>const&resource    = nullptr,
            Function::Ticks                updateTicks = 0      ,
            bool                           changed     = false  );
        virtual ~AtomicFunctionInput();
    };

    class StatementFactory;

    class GEDE_EXPORT AtomicFunction: public Function{
      public:
        using SharedResource = std::shared_ptr<Resource>;
        using SharedAtomicFunctionInput = std::shared_ptr<AtomicFunctionInput>;
        using Res2FceInput = std::map<SharedResource,SharedAtomicFunctionInput>;
        using InputList  = std::vector<SharedAtomicFunctionInput>;
      protected:
        InputList                _inputs               ;
        std::map<SharedResource,std::set<size_t>>_res2Indices;
        Res2FceInput             _res2FceInput        ;
        Resource*_outputData  = nullptr;
      public:
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr,
            FunctionId                             id);
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr               ,
            TypeId                                 type             ,
            std::string                      const&name             ,
            std::shared_ptr<StatementFactory>const&factory = nullptr);
        virtual ~AtomicFunction();
        virtual void operator()()override;
        virtual bool bindInput (
            std::shared_ptr<FunctionRegister>const&fr          ,
            size_t                                 i           ,
            std::shared_ptr<Resource>        const&r  = nullptr)override;
        virtual bool bindOutput(
            std::shared_ptr<FunctionRegister>const&fr            ,
            std::shared_ptr<Resource>        const&data = nullptr)override;
        virtual bool bindOutputAsVariable(
            std::shared_ptr<FunctionRegister>const&fr,
            std::shared_ptr<Resource>        const&r )override;
        virtual bool hasInput(size_t i)const override;
        virtual bool hasOutput()const override;
        virtual std::shared_ptr<Resource>const&getInputData(size_t i)const override;
        virtual Resource*getOutputData()const override;
      protected:
        bool _processInputs();
        virtual bool _do();
        inline bool _inputChanged(size_t i)const;
    };

    inline Resource*AtomicFunction::getOutputData()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_outputData;
    }

    inline bool AtomicFunction::hasInput(size_t i)const{
      PRINT_CALL_STACK(i);
      assert(this!=nullptr);
      assert(i<this->_inputs.size());
      assert(this->_inputs.at(i)!=nullptr);
      return this->_inputs.at(i)->resource!=nullptr;
    }

    inline bool AtomicFunction::hasOutput()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_outputData!=nullptr;
    }

    inline std::shared_ptr<Resource>const&AtomicFunction::getInputData(size_t i)const{
      PRINT_CALL_STACK(i);
      assert(this!=nullptr);
      assert(i<this->_inputs.size());
      assert(this->_inputs.at(i)!=nullptr);
      return this->_inputs.at(i)->resource;
    }

    inline bool AtomicFunction::_inputChanged(size_t i)const{
      PRINT_CALL_STACK(i);
      assert(this!=nullptr);
      assert(i<this->_inputs.size());
      assert(this->_inputs.at(i)!=nullptr);
      return this->_inputs.at(i)->changed;
    }

  }
}
