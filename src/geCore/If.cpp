#include<geCore/If.h>
#include<geCore/Resource.h>
#include<geCore/AtomicFunction.h>

using namespace ge::core;

void If::operator()(){
  (*this->_condition)();
  if((bool)*this->_condition->getOutputData())
    (*this->_trueBody)();
  else{
    if(this->_falseBody)(*this->_falseBody)();
  }
}

