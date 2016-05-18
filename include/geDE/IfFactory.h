#pragma once

#include<geCore/StatementFactory.h>

namespace ge{
  namespace{
    class GECORE_EXPORT IfFactory: public StatementFactory{
      public:
        IfFactory(std::string name = "",unsigned maxUses = 1);
        virtual ~IfFactory();
        std::shared_ptr<StatementFactory>trueFactory      = nullptr;
        std::shared_ptr<StatementFactory>falseFactory     = nullptr;
        std::shared_ptr<FunctionFactory >conditionFactory = nullptr;
        virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister>const&)override;
    };

    inline IfFactory::IfFactory(std::string name,unsigned maxUses):StatementFactory(name,maxUses){
    }

    inline IfFactory::~IfFactory(){
    }

    inline std::shared_ptr<Statement>IfFactory::_do(std::shared_ptr<FunctionRegister> const&fr){
      auto result = std::make_shared<If>();
      result->setTrueBody ((*this->trueFactory     )(fr));
      result->setFalseBody((*this->falseFactory    )(fr));
      result->setCondition(std::dynamic_pointer_cast<AtomicFunction>((*this->conditionFactory)(fr)));
      return result;
    }


  }
}
