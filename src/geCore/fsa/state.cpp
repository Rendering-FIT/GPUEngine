#include<geCore/fsa/state.h>

#include<iostream>
#include<sstream>

using namespace ge::core;

State::State(const char* name){
  this->_name = name;
  this->_elseTransition.setCallback (NULL);
  this->_elseTransition.setNextState(NULL);
  this->_eofTransition .setCallback (NULL);
  this->_eofTransition .setNextState(NULL);
}

void State::addTransition(
    char         lex     ,
    State*       state   ,
    RuleCallback callback,
    void*        data    ){
  if(this->_transitions.count(lex)){
    if(this->_transitions[lex].getNextState()!=state){
      std::cerr<<"you cannot create nondeterministic fsa: "
        <<this->getName()<<"-"<<lex<<"->"<<state->getName()<<std::endl;
    }else this->_transitions[lex].setCallback(callback,data);
  }else this->_transitions[lex]=Transition(state,callback,data);
}

void State::addElseTransition(
    State*       state   ,
    RuleCallback callback,
    void*        data    ){
  this->_elseTransition.setNextState(state   );
  this->_elseTransition.setCallback (callback,data);
}

void State::addEOFTransition(
    State*       state   ,
    RuleCallback callback,
    void*        data    ){
  this->_eofTransition.setNextState(state   );
  this->_eofTransition.setCallback (callback,data);
}

void State::setCallback(char lex,RuleCallback cb,void*data){
  this->_transitions[lex].setCallback(cb,data);
}

void State::setElseCallback(RuleCallback cb,void*data){
  this->_elseTransition.setCallback(cb,data);
}

void State::setEOFCallback(RuleCallback cb,void*data){
  this->_eofTransition.setCallback(cb,data);
}

Transition&State::getTransition(char lex){
  return this->_transitions[lex];
}

Transition&State::getElseTransition(){
  return this->_elseTransition;
}

Transition&State::getEOFTransition(){
  return this->_eofTransition;
}

const char* State::getName(){
  return this->_name;
}

unsigned State::getNofTransition(){
  return this->_transitions.size();
}

char State::getTransitionLex(unsigned i){
  std::map<char,Transition>::iterator ii=this->_transitions.begin();
  for(unsigned j=0;j<i;++j)
    ii++;
  return ii->first;
}

void State::clearTransitions   (){
  this->_transitions.clear();
}
void State::clearElseTransition(){
  this->_elseTransition.setCallback ();
  this->_elseTransition.setNextState();
}
void State::clearEofTransition (){
  this->_eofTransition.setCallback ();
  this->_eofTransition.setNextState();
}

void State::setEndState(char lex,State*state){
  this->_transitions[lex].setNextState(state);
}

void State::setElseEndState(State*state){
  this->_elseTransition.setNextState(state);
}

void State::setEOFEndState(State*state){
  this->_eofTransition.setNextState(state);
}

State* State::apply(char lex,FSA*fsa){
  //std::cerr<<"apply: "<<this->getName()<<":"<<lex<<std::endl;
  if(!this->_transitions.count(lex)){
    this->_elseTransition.callCallback(fsa);
    return this->_elseTransition.getNextState();
  }
  Transition tt=this->_transitions[lex];
  tt.callCallback(fsa);
  return tt.getNextState();
}

std::string State::toStr(){
  std::stringstream ss;
  std::map<char,Transition>::iterator ii=this->_transitions.begin();
  if(ii!=this->_transitions.end()){
    ss<<ii->first<<"->"<<ii->second.toStr();
    ii++;
  }
  for(;ii!=this->_transitions.end();++ii)
    ss<<","<<ii->first<<"->"<<ii->second.toStr();
  if(this->_elseTransition.getNextState())
    ss<<",else->"<<this->_elseTransition.getNextState()->getName();
  if(this->_eofTransition.getNextState())
    ss<<",eof->"<<this->_eofTransition.getNextState()->getName();
  return ss.str();
}


