#pragma once

#include<geDE/Function.h>

namespace ge{
  namespace de{
    class CompositeFunctionFactory;
    class GEDE_EXPORT CompositeFunction: public Function{
      friend class CompositeFunctionFactory;
      public:
        using FceInput = std::tuple<std::shared_ptr<Function>,InputIndex>;
        enum FceInputParts{
          FUNCTION = 0,
          INPUT    = 1,
        };
        using FceInputList = std::vector<FceInput>;
        CompositeFunction(
            std::shared_ptr<FunctionRegister>const&fr    ,
            FunctionId                             id    ,
            std::shared_ptr<Function>        const&output,
            std::vector<FceInputList>        const&inputs);
        ~CompositeFunction();
        virtual inline void operator()()override;
        virtual bool bindInput (
            std::shared_ptr<FunctionRegister>const&fr          ,
            InputIndex                             i           ,
            std::shared_ptr<Resource>        const&r  = nullptr)override;
        virtual bool bindOutput(
            std::shared_ptr<FunctionRegister>const&fr          ,
            std::shared_ptr<Resource>        const&r  = nullptr)override;
        virtual bool bindOutputAsVariable(
            std::shared_ptr<FunctionRegister>const&fr,
            std::shared_ptr<Resource>        const&r )override;
        virtual bool hasInput (InputIndex i)const override;
        virtual bool hasOutput(            )const override;
        virtual std::shared_ptr<Resource>const&getInputData (InputIndex i)const override;
        virtual Resource*getOutputData()const override;
      protected:
        std::vector<FceInputList>_inputMapping;
        std::shared_ptr<Function>_outputMapping;
        virtual void _addSignalingTarget(Statement*statement)override;
        virtual void _removeSignalingTarget(Statement*statement)override;
        virtual void _addTargetResource(Resource*resource)override;
        virtual void _removeTargetResource(Resource*resource)override;
    };

    inline void CompositeFunction::operator()(){
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      assert(this->_outputMapping!=nullptr);
      (*this->_outputMapping)();
    }
  }
}
