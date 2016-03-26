#include<geCore/if.h>
#include<geCore/Accessor.h>

using namespace ge::core;

If::If(
    std::shared_ptr<AtomicFunction> const&condition,
    std::shared_ptr<Statement>const&trueBody ,
    std::shared_ptr<Statement>const&falseBody):Statement(IF){
  this->_condition = condition;
  this->_trueBody  = trueBody ;
  this->_falseBody = falseBody;
}

If::~If(){

}

void If::setCondition(std::shared_ptr<AtomicFunction> const&condition){
  this->_condition = condition;
}

void If::setTrueBody (std::shared_ptr<Statement>const&trueBody ){
  this->_trueBody = trueBody;
}

void If::setFalseBody(std::shared_ptr<Statement>const&falseBody){
  this->_falseBody = falseBody;
}

std::shared_ptr<AtomicFunction> const&If::getCondition()const{
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
  if((bool)*this->_condition->getOutputData())
    (*this->_trueBody)();
  else{
    if(this->_falseBody)(*this->_falseBody)();
  }
}


IfFactory::~IfFactory(){
}

std::shared_ptr<Statement>IfFactory::operator()(std::shared_ptr<FunctionRegister> const&fr){
  auto result = std::make_shared<If>();
  result->setTrueBody ((*this->trueFactory     )(fr));
  result->setFalseBody((*this->falseFactory    )(fr));
  result->setCondition(std::dynamic_pointer_cast<AtomicFunction>((*this->conditionFactory)(fr)));
  return result;
}


