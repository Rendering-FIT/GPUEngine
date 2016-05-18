#include<geDE/While.h>
#include<geDE/Resource.h>
#include<geDE/Function.h>

using namespace ge::de;

void While::operator()(){
  for(;;){
    (*this->_condition)();
    if(!(bool)*this->_condition->getOutputData())return;
    (*this->_body)();
  }
}


