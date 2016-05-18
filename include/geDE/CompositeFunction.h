#pragma once

#include<geDE/Function.h>

namespace ge{
  namespace de{
    class CompositeFunctionFactory;
    class GEDE_EXPORT CompositeFunction: public Function{
      friend class CompositeFunctionFactory;
      public:
        using FceInput = std::tuple<std::shared_ptr<Function>,FunctionRegister::InputIndex>;
        enum FceInputParts{
          FUNCTION = 0,
          INPUT    = 1,
        };
        using FceInputList = std::vector<FceInput>;
        CompositeFunction(
            std::shared_ptr<FunctionRegister>const&fr    ,
            FunctionRegister::FunctionID           id    ,
            std::shared_ptr<Function>        const&output,
            std::vector<FceInputList>        const&inputs);
        ~CompositeFunction();
        virtual inline void operator()()override;
        virtual bool bindInput (
            std::shared_ptr<FunctionRegister>const&fr                ,
            InputIndex                             i                 ,
            std::shared_ptr<Function>        const&function = nullptr)override;
        virtual bool bindOutput(
            std::shared_ptr<FunctionRegister>const&fr            ,
            std::shared_ptr<Resource>        const&data = nullptr)override;
        virtual bool hasInput (InputIndex i)const override;
        virtual bool hasOutput(            )const override;
        virtual std::shared_ptr<Resource>const&getInputData (InputIndex i)const override;
        virtual std::shared_ptr<Resource>const&getOutputData(            )const override;
        virtual Ticks getUpdateTicks()const override;
        virtual Ticks getCheckTicks ()const override;
        virtual void  setUpdateTicks(Ticks ticks)override;
        virtual void  setCheckTicks (Ticks ticks)override;
        virtual std::shared_ptr<Function>const&getInputFunction(InputIndex i)const override;
        virtual inline std::string doc()const override;
      protected:
        std::vector<FceInputList>_inputMapping;
        std::shared_ptr<Function>_outputMapping;
    };

    inline void CompositeFunction::operator()(){
      assert(this!=nullptr);
      (*this->_outputMapping)();
    }

    inline std::string CompositeFunction::doc()const{
      return "";
    }
  }
}
