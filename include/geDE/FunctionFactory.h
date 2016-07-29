#pragma once

#include<geDE/StatementFactory.h>
#include<geDE/Types.h>
#include<tuple>

namespace ge{
  namespace de{
    class Statement;
    class FunctionRegister;
    class GEDE_EXPORT FunctionFactory: public StatementFactory{
      public:
        FunctionFactory(std::string const&name = "",Uses maxUses = 0);
        virtual ~FunctionFactory();
        virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister> const&)=0;
        virtual TypeId getOutputType(std::shared_ptr<FunctionRegister>const&)const = 0;
        virtual size_t getNofInputs(std::shared_ptr<FunctionRegister> const&)const=0;
        virtual TypeId getInputType(std::shared_ptr<FunctionRegister> const&,size_t)const=0;
    };
  }
}

