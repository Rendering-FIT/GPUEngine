#include<geCore/WhileFactory.h>
#include<geCore/While.h>
#include<geCore/AtomicFunction.h>

using namespace ge::core;

std::shared_ptr<Statement>WhileFactory::_do(
    std::shared_ptr<FunctionRegister>const&fr){
  auto result = std::make_shared<While>();
  result->setCondition(std::dynamic_pointer_cast<AtomicFunction>((*this->conditionFactory)(fr)));
  result->setBody     ((*this->bodyFactory     )(fr));
  return result;
}


