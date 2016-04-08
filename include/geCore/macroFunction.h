#pragma once

#include<geCore/function.h>

namespace ge{
  namespace core{
    class MacroFunctionFactory;
    class GECORE_EXPORT MacroFunction: public Function{
      friend class MacroFunctionFactory;
      public:
        using FceInput = std::tuple<std::shared_ptr<Function>,FunctionRegister::InputIndex>;
        enum FceInputParts{
          FUNCTION = 0,
          INPUT    = 1,
        };
        using FceInputList = std::vector<FceInput>;
      protected:
        std::vector<FceInputList>_inputMapping;
        std::shared_ptr<Function>_outputMapping;
      public:
        MacroFunction(
            std::shared_ptr<FunctionRegister>const&fr,
            FunctionRegister::FunctionID id,
            std::shared_ptr<Function>const&output,
            std::vector<FceInputList>const&inputs);
        ~MacroFunction();
        virtual inline void operator()()override;
        virtual bool bindInput (InputIndex i,std::shared_ptr<Function>function = nullptr)override;
        virtual bool bindOutput(             std::shared_ptr<Accessor>data     = nullptr)override;
        virtual bool hasInput (InputIndex i)const override;
        virtual bool hasOutput(            )const override;
        virtual std::shared_ptr<Accessor>const&getInputData (InputIndex i)const override;
        virtual std::shared_ptr<Accessor>const&getOutputData(            )const override;
        virtual Ticks getUpdateTicks()const override;
        virtual Ticks getCheckTicks ()const override;
        virtual void  setUpdateTicks(Ticks ticks)override;
        virtual void  setCheckTicks (Ticks ticks)override;
        virtual std::shared_ptr<Function>const&getInputFunction(InputIndex i)const override;
        virtual inline std::string doc()const override;
    };

    inline void MacroFunction::operator()(){
      assert(this!=nullptr);
      (*this->_outputMapping)();
    }

    inline std::string MacroFunction::doc()const{
      return "";
    }

    class GECORE_EXPORT FunctionNodeFactory: public FunctionFactory{
      protected:
        std::shared_ptr<FunctionFactory>functionFactory = nullptr;
        std::vector<std::shared_ptr<ResourceFactory>>resourceFactories;
        std::vector<std::shared_ptr<FunctionFactory>>inputFactories;
      public:
        FunctionNodeFactory(std::string name = "",Uses maxUses = 1);
        void setFactory(std::shared_ptr<StatementFactory>const&fac);
        void addResourceFactory(std::shared_ptr<ResourceFactory>const&factory);
        void addInputFactory(std::shared_ptr<StatementFactory>const&factory);
        virtual ~FunctionNodeFactory();
        std::shared_ptr<FunctionFactory>getInputFactory(size_t input);
        void reset();
        virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister>const&fr);
    };

    class GECORE_EXPORT MacroFunctionFactory: public FunctionFactory{
      public:
        using FactoryInput = std::tuple<std::shared_ptr<FunctionFactory>,FunctionRegister::InputIndex>;
        enum FceInputParts{
          FACTORY = 0,
          INPUT   = 1,
        };
        using FactoryInputList = std::vector<FactoryInput>;
      protected:
        std::shared_ptr<FunctionFactory>_factory = nullptr;
        std::vector<FactoryInputList> _inputs;
        void _recBuildInput(
            MacroFunction::FceInputList&output,
            std::shared_ptr<Function>const&fce,
            std::shared_ptr<FunctionFactory>const&fac,
            MacroFunctionFactory::FactoryInputList const&factoryInputList);
      public:
        MacroFunctionFactory(std::string name = "",Uses maxUses = 1);
        virtual ~MacroFunctionFactory();
        std::shared_ptr<FunctionFactory>getInputFactory(size_t input);
        void setFactory(std::shared_ptr<StatementFactory>const&fac);
        void setInputFactories(std::vector<FactoryInputList> const&inputs);
        virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister>const&fr);
    };


  }
}
