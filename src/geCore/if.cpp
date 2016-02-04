#include<geCore/if.h>

using namespace ge::core;

If::If(
    std::shared_ptr<Function> const&condition,
    std::shared_ptr<Statement>const&trueBody ,
    std::shared_ptr<Statement>const&falseBody):Statement(IF){
  this->_condition = condition;
  this->_trueBody  = trueBody ;
  this->_falseBody = falseBody;
}

If::~If(){

}

void If::setCondition(std::shared_ptr<Function> const&condition){
  this->_condition = condition;
}

void If::setTrueBody (std::shared_ptr<Statement>const&trueBody ){
  this->_trueBody = trueBody;
}

void If::setFalseBody(std::shared_ptr<Statement>const&falseBody){
  this->_falseBody = falseBody;
}

std::shared_ptr<Function> const&If::getCondition()const{
  return this->_condition;
}

std::shared_ptr<Statement>const&If::getTrueBody()const{
  return this->_trueBody;
}

std::shared_ptr<Statement>const&If::getFalseBody()const{
  return this->_falseBody;
}

void If::operator()(){
  (*this->_condition)();
  if((bool)*(this->_condition->getOutput()))
    (*this->_trueBody)();
  else{
    if(this->_falseBody)(*this->_falseBody)();
  }
}



std::shared_ptr<Statement>IfFactory::operator()(SharedTypeRegister const&tr){
  auto result = std::make_shared<If>();
  result->setTrueBody ((*this->trueFactory     )(tr));
  result->setFalseBody((*this->falseFactory    )(tr));
  result->setCondition(std::dynamic_pointer_cast<Function>((*this->conditionFactory)(tr)));
  return result;
}


