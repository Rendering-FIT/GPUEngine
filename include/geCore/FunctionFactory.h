#pragma once

#include<geCore/statement.h>

namespace ge{
  namespace core{
    class FunctionRegister;
    class GECORE_EXPORT FunctionFactory: public StatementFactory{
      public:
        FunctionFactory(std::string const&name = "",Uses maxUses = 1);
        virtual ~FunctionFactory();
        virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister> const&)=0;
    };
  }
}

