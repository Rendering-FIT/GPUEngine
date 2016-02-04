#include<geCore/while.h>

using namespace ge::core;

While::While(
    std::shared_ptr<Function >const&condition,
    std::shared_ptr<Statement>const&body     ):Statement(WHILE){
  this->_condition = condition;
  this->_body      = body;
}

While::~While(){

}

void While::setBody(std::shared_ptr<Statement>const&body){
  this->_body = body;
}

void While::setCondition(std::shared_ptr<Function>const&condition){
  this->_condition = condition;
}

std::shared_ptr<Function>const&While::getCondition()const{
  return this->_condition;
}

std::shared_ptr<Statement>const&While::getBody()const{
  return this->_body;
}

void While::operator()(){
  for(;;){
    (*this->_condition)();
    if(!(bool)*(this->_condition->getOutput()))return;
    (*this->_body)();
  }
}



std::shared_ptr<Statement>WhileFactory::operator()(SharedTypeRegister const&tr){
  auto result = std::make_shared<While>();
  result->setCondition(std::dynamic_pointer_cast<Function>((*this->conditionFactory)(tr)));
  result->setBody     ((*this->bodyFactory     )(tr));
  return result;
}


