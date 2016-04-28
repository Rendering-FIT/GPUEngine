#include<geCore/While.h>
#include<geCore/Resource.h>
#include<geCore/Function.h>

using namespace ge::core;

void While::operator()(){
  for(;;){
    (*this->_condition)();
    if(!(bool)*this->_condition->getOutputData())return;
    (*this->_body)();
  }
}


