#pragma once

#include<geDE/StatementFactory.h>

namespace ge{
  namespace de{
    class FunctionFactory;
    class GEDE_EXPORT WhileFactory: public StatementFactory{
      public:
        inline WhileFactory(/*std::string const&name = "",*/Uses maxUses = 0);
        inline virtual ~WhileFactory();
        std::shared_ptr<StatementFactory>bodyFactory      = nullptr;
        std::shared_ptr<FunctionFactory >conditionFactory = nullptr;
        virtual std::shared_ptr<Statement>_do(
            std::shared_ptr<FunctionRegister>const&)override;
    };

    inline WhileFactory::WhileFactory(
        //std::string const&name   ,
        Uses              maxUses):StatementFactory(/*name,*/maxUses){
      PRINT_CALL_STACK(name,maxUses);
    }

    inline WhileFactory::~WhileFactory(){
      PRINT_CALL_STACK();
    }
  }
}
