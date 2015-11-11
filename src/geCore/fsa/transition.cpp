#include<geCore/fsa/transition.h>
#include<geCore/fsa/state.h>

#include<sstream>

using namespace ge::core;

Transition::Transition(State*state,RuleCallback callback,void* data){
  this->_nextState    = state   ;
  this->_callback     = callback;
  this->_callbackData = data    ;
}

Transition::~Transition(){
}

void Transition::setCallback(RuleCallback callback,void* data){
  this->_callback     = callback;
  this->_callbackData = data    ;
}

State* Transition::getNextState()const{
  return this->_nextState;
}

void Transition::setNextState(State*state){
  this->_nextState = state;
}

RuleCallback Transition::getCallback()const{
  return this->_callback;
}

void* Transition::getCallbackData()const{
  return this->_callbackData;
}

void Transition::callCallback(FSA*fsa)const{
  if(this->_callback)this->_callback(fsa,this->_callbackData);
}
std::string Transition::toStr()const{
  std::stringstream ss;
  ss<<this->_nextState->getName();
  return ss.str();
}

