#pragma once

#include<geCore/StatementFactory.h>

namespace ge{
  namespace core{
    class FunctionFactory;
    class GECORE_EXPORT WhileFactory: public StatementFactory{
      public:
        inline WhileFactory(std::string const&name = "",Uses maxUses = 1);
        inline virtual ~WhileFactory();
        std::shared_ptr<StatementFactory>bodyFactory      = nullptr;
        std::shared_ptr<FunctionFactory >conditionFactory = nullptr;
        virtual std::shared_ptr<Statement>_do(
            std::shared_ptr<FunctionRegister>const&)override;
    };

    inline WhileFactory::WhileFactory(
        std::string const&name   ,
        Uses              maxUses):StatementFactory(name,maxUses){
    }

    inline WhileFactory::~WhileFactory(){
    }
  }
}
