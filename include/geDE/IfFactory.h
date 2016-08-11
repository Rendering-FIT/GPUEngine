#pragma once

#include<geDE/StatementFactory.h>
#include<geDE/AtomicFunction.h>
#include<geDE/FunctionFactory.h>
#include<geDE/If.h>

namespace ge{
  namespace de{
    class GEDE_EXPORT IfFactory: public StatementFactory{
      public:
        IfFactory(/*std::string name = "",*/unsigned maxUses = 0);
        virtual ~IfFactory();
        std::shared_ptr<StatementFactory>trueFactory      = nullptr;
        std::shared_ptr<StatementFactory>falseFactory     = nullptr;
        std::shared_ptr<FunctionFactory >conditionFactory = nullptr;
        virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister>const&)override;
    };

    inline IfFactory::IfFactory(/*std::string name,*/unsigned maxUses):StatementFactory(/*name,*/maxUses){
      PRINT_CALL_STACK(/*name,*/maxUses);
    }

    inline IfFactory::~IfFactory(){
      PRINT_CALL_STACK();
    }

    inline std::shared_ptr<Statement>IfFactory::_do(std::shared_ptr<FunctionRegister> const&fr){
      PRINT_CALL_STACK(fr);
      assert(this!=nullptr);
      auto result = std::make_shared<If>();
      assert(result!=nullptr);
      assert(this->trueFactory!=nullptr);
      assert(this->falseFactory!=nullptr);
      assert(this->conditionFactory!=nullptr);
      result->setTrueBody ((*this->trueFactory     )(fr));
      result->setFalseBody((*this->falseFactory    )(fr));
      result->setCondition(std::dynamic_pointer_cast<AtomicFunction>((*this->conditionFactory)(fr)));
      return result;
    }


  }
}
