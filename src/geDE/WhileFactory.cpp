#include<geDE/FunctionFactory.h>
#include<geDE/WhileFactory.h>
#include<geDE/While.h>
#include<geDE/AtomicFunction.h>

using namespace ge::de;

std::shared_ptr<Statement>WhileFactory::_do(
    std::shared_ptr<FunctionRegister>const&fr){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  auto result = std::make_shared<While>();
  assert(result!=nullptr);
  result->setCondition(std::dynamic_pointer_cast<AtomicFunction>((*this->conditionFactory)(fr)));
  result->setBody     ((*this->bodyFactory     )(fr));
  return result;
}


