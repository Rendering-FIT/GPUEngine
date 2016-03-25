#pragma once

#include<geCore/function.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT If: public Statement{
      protected:
        std::shared_ptr<AtomicFunction >_condition = nullptr;
        std::shared_ptr<Statement>_trueBody  = nullptr;
        std::shared_ptr<Statement>_falseBody = nullptr;
      public:
        If(
            std::shared_ptr<AtomicFunction >const&condition = nullptr,
            std::shared_ptr<Statement>const&trueBody  = nullptr,
            std::shared_ptr<Statement>const&falseBody = nullptr);
        virtual ~If();
        void setCondition(std::shared_ptr<AtomicFunction >const&condition = nullptr);
        void setTrueBody (std::shared_ptr<Statement>const&trueBody  = nullptr);
        void setFalseBody(std::shared_ptr<Statement>const&falseBody = nullptr);
        std::shared_ptr<AtomicFunction >const&getCondition()const;
        std::shared_ptr<Statement>const&getTrueBody ()const;
        std::shared_ptr<Statement>const&getFalseBody()const;
        virtual void operator()();
    };

    class GECORE_EXPORT IfFactory: public StatementFactory{
      public:
        virtual ~IfFactory();
        std::shared_ptr<StatementFactory>trueFactory      = nullptr;
        std::shared_ptr<StatementFactory>falseFactory     = nullptr;
        std::shared_ptr<FunctionFactory >conditionFactory = nullptr;
        virtual std::shared_ptr<Statement>operator()(SharedTypeRegister const&);
    };

  }
}
