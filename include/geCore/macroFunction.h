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
        virtual inline void operator()();
        virtual bool bindInput (InputIndex i,std::shared_ptr<Function>function = nullptr);
        virtual bool bindOutput(             std::shared_ptr<Accessor>data     = nullptr);
        virtual bool hasInput (InputIndex i)const;
        virtual bool hasOutput(            )const;
        virtual std::shared_ptr<Accessor>const&getInputData (InputIndex i)const;
        virtual std::shared_ptr<Accessor>const&getOutputData(            )const;
        virtual Ticks getUpdateTicks()const;
        virtual Ticks getCheckTicks ()const;
        virtual void  setUpdateTicks(Ticks ticks);
        virtual void  setCheckTicks (Ticks ticks);
        virtual std::shared_ptr<Function>const&getInputFunction(InputIndex i)const;
        virtual inline std::string doc()const{return "";}
    };

    inline void MacroFunction::operator()(){
      (*this->_outputMapping)();
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
        void reset();
        virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister>const&fr);
    };

    class GECORE_EXPORT MacroFunctionFactory: public FunctionFactory{
      protected:
        std::shared_ptr<FunctionFactory>_factory = nullptr;
        using FactoryInput = std::tuple<std::shared_ptr<FunctionFactory>,FunctionRegister::InputIndex>;
        enum FceInputParts{
          FUNCTION = 0,
          INPUT    = 1,
        };
        using FactoryInputList = std::vector<FactoryInput>;
        std::vector<FactoryInputList> _inputs;
        //void _recBuildInput(MacroFunction::FactoryInputList const&factoryInputList)
      public:
        MacroFunctionFactory(std::string name = "",Uses maxUses = 1);
        virtual ~MacroFunctionFactory();
        void setFactory(std::shared_ptr<StatementFactory>const&fac);
        void setInputFactories(std::vector<FactoryInputList> const&inputs);
        virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister>const&fr);
    };


  }
}
