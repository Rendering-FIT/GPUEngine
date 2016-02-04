#pragma once

#include<geCore/function.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT While: public Statement{
      protected:
        std::shared_ptr<Function >_condition = nullptr;
        std::shared_ptr<Statement>_body      = nullptr;
      public:
        While(std::shared_ptr<Function> const&condition = nullptr,
              std::shared_ptr<Statement>const&body      = nullptr);
        virtual ~While();
        void setBody     (std::shared_ptr<Statement>const&body      = nullptr);
        void setCondition(std::shared_ptr<Function >const&condition = nullptr);
        std::shared_ptr<Function >const&getCondition()const;
        std::shared_ptr<Statement>const&getBody     ()const;
        virtual void operator()();
    };

    class GECORE_EXPORT WhileFactory: public StatementFactory{
      public:
        virtual ~WhileFactory();
        std::shared_ptr<StatementFactory>bodyFactory      = nullptr;
        std::shared_ptr<FunctionFactory >conditionFactory = nullptr;
        virtual std::shared_ptr<Statement>operator()(SharedTypeRegister const&);
    };
  }
}
