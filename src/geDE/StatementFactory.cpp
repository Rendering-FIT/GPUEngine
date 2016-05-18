#include<geDE/StatementFactory.h>

using namespace ge::de;


std::shared_ptr<Statement>StatementFactory::operator()(
    std::shared_ptr<FunctionRegister>const&tr){
  this->_first = this->_uses == 0;
  std::shared_ptr<Statement>res;
  if(!this->_result)this->_result = this->_do(tr);
  res = this->_result;
  this->_uses++;
  if(this->_uses==this->_maxUses){
    this->_uses = 0;
    this->_result = nullptr;
  }
  return res;
}
