#include<geCore/while.h>
#include<geCore/Accessor.h>

using namespace ge::core;

While::While(
    std::shared_ptr<AtomicFunction >const&condition,
    std::shared_ptr<Statement>const&body     ):Statement(WHILE){
  this->_condition = condition;
  this->_body      = body;
}

While::~While(){

}

void While::setBody(std::shared_ptr<Statement>const&body){
  this->_body = body;
}

void While::setCondition(std::shared_ptr<AtomicFunction>const&condition){
  this->_condition = condition;
}

std::shared_ptr<AtomicFunction>const&While::getCondition()const{
  return this->_condition;
}

std::shared_ptr<Statement>const&While::getBody()const{
  return this->_body;
}

void While::operator()(){
  for(;;){
    (*this->_condition)();
    if(!(bool)*this->_condition->getOutputData())return;
    (*this->_body)();
  }
}

WhileFactory::WhileFactory(std::string name,unsigned maxUses):StatementFactory(name,maxUses){
}

WhileFactory::~WhileFactory(){
}

std::shared_ptr<Statement>WhileFactory::operator()(std::shared_ptr<FunctionRegister> const&fr){
  auto result = std::make_shared<While>();
  result->setCondition(std::dynamic_pointer_cast<AtomicFunction>((*this->conditionFactory)(fr)));
  result->setBody     ((*this->bodyFactory     )(fr));
  return result;
}


