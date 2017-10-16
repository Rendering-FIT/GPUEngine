#include<sstream>

#include<GPUEngine/geCore/FSA/Transition.h>
#include<GPUEngine/geCore/FSA/State.h>
#include<GPUEngine/geCore/FSA/FusedCallbackData.h>


using namespace ge::core;

FSATransition::FSATransition(FSAState*state,FSAFusedCallback const&callback){
  this->_nextState = state   ;
  this->_callback  = callback;
}

FSATransition::~FSATransition(){
}

bool FSATransition::operator==(FSATransition const&other)const{
  return this->_nextState == other._nextState && this->_callback == other._callback;
}

bool FSATransition::operator!=(FSATransition const&other)const{
  return !(*this==other);
}

void FSATransition::setCallback(FSAFusedCallback const& callback){
  this->_callback = callback;
}

FSAState* FSATransition::getNextState()const{
  return this->_nextState;
}

void FSATransition::setNextState(FSAState*state){
  this->_nextState = state;
}

FSAFusedCallback const&FSATransition::getCallback()const{
  return this->_callback;
}

void FSATransition::callCallback(FSA*fsa)const{
  this->_callback(fsa);
}

std::string FSATransition::toStr()const{
  std::stringstream ss;
  ss<<this->_nextState->getName();
  return ss.str();
}

