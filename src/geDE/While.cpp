#include<geDE/While.h>
#include<geDE/Resource.h>
#include<geDE/Function.h>

using namespace ge::de;

void While::operator()(){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  assert(this->_condition!=nullptr);
  assert(this->_body!=nullptr);
  if(!this->_dirtyFlag)return;
  this->_dirtyFlag = false;
  bool changed = false;
  //unsigned counter = 0;
  for(;;){
    //std::cout<<"condition before: "<<this->_condition->isDirty()<<std::endl;
    (*this->_condition)();
    if(this->_conditionUpdateTicks!=this->_condition->getUpdateTicks())changed = true;
    this->_conditionUpdateTicks = this->_condition->getUpdateTicks();
    //std::cout<<"condition after: "<<this->_condition->isDirty()<<std::endl;
    if(!(bool)*this->_condition->getOutputData())return;
    //std::cout<<"body before: "<<this->_body->isDirty()<<std::endl;
    (*this->_body)();
    if(this->_bodyUpdateTicks!=this->_body->getUpdateTicks())changed = true;
    this->_bodyUpdateTicks = this->_body->getUpdateTicks();
    //std::cout<<"body after: "<<this->_body->isDirty()<<std::endl;
    //counter++;
    //if(counter>20)break;
  }
  if(!changed)return;
  this->_updateTicks++;
  this->setSignalingDirty();
}


