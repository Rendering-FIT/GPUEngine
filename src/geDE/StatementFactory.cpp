#include<geDE/StatementFactory.h>
#include<geCore/CallStackPrinter.h>

using namespace ge::de;


std::shared_ptr<Statement>StatementFactory::operator()(
    std::shared_ptr<FunctionRegister>const&tr){
  PRINT_CALL_STACK(tr);
  assert(this!=nullptr);
  this->_first = this->_uses == 0;
  if(!this->_result)this->_result = this->_do(tr);
  auto res = this->_result;
  this->_uses++;
  if(this->_uses>=this->_maxUses){
    this->_uses = 0;
    this->_result = nullptr;
  }
  return res;
}
