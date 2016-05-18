#include<geDE/If.h>
#include<geDE/Resource.h>
#include<geDE/Function.h>

using namespace ge::de;

void If::operator()(){
  (*this->_condition)();
  if((bool)*this->_condition->getOutputData())
    (*this->_trueBody)();
  else{
    if(this->_falseBody)(*this->_falseBody)();
  }
}

