#include<geDE/If.h>
#include<geDE/Resource.h>
#include<geDE/Function.h>

using namespace ge::de;

void If::operator()(){
  assert(this!=nullptr);
  assert(this->_condition!=nullptr);
  assert(this->_trueBody!=nullptr);
  if(!this->_dirtyFlag)return;
  (*this->_condition)();
  bool changed = false;
  if(this->_conditionUpdateTicks!=this->_condition->getUpdateTicks())changed = true;
  this->_conditionUpdateTicks = this->_condition->getUpdateTicks();
  if((bool)*this->_condition->getOutputData()){
    (*this->_trueBody)();
    if(this->_trueBodyUpdateTicks!=this->_trueBody->getUpdateTicks())changed = true;
    this->_trueBodyUpdateTicks = this->_trueBody->getUpdateTicks();
  }else{
    if(this->_falseBody){
      (*this->_falseBody)();
      if(this->_falseBodyUpdateTicks!=this->_falseBody->getUpdateTicks())changed = true;
      this->_falseBodyUpdateTicks = this->_falseBody->getUpdateTicks();
    }
  }
  if(!changed)return;
  this->_updateTicks++;
  this->_dirtyFlag = false;
  this->setSignalingDirty();
}

