#include<geCore/fsa/state.h>

#include<iostream>
#include<sstream>

using namespace ge::core;

State::State(std::string name){
  this->_name = name;
  this->_elseTransition.setCallback (nullptr);
  this->_elseTransition.setNextState(nullptr);
  this->_eofTransition .setCallback (nullptr);
  this->_eofTransition .setNextState(nullptr);
}

State::~State(){
}

void State::addTransition(
    char         lex     ,
    State*       state   ,
    RuleCallback callback,
    void*        data    ){
  auto ii=this->_transitions.find(lex);
  if(ii==this->_transitions.end()){
    this->_transitions[lex]=Transition(state,callback,data);
    return;
  }
  if(ii->second.getNextState()!=state){
    std::cerr<<"you cannot create nondeterministic fsa: "
      <<this->getName()<<"-"<<lex<<"->"<<state->getName()<<std::endl;
    return;
  }
  ii->second.setCallback(callback,data);
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

Transition const&State::getTransition(char lex)const{
  return this->_transitions.find(lex)->second;
}

Transition const&State::getElseTransition()const{
  return this->_elseTransition;
}

Transition const&State::getEOFTransition()const{
  return this->_eofTransition;
}

std::string State::getName()const{
  return this->_name;
}

unsigned State::getNofTransition()const{
  return this->_transitions.size();
}

char State::getTransitionLex(unsigned i)const{
  unsigned counter=0;
  for(auto x:this->_transitions)
    if(counter==i)return x.first;
  return 0;
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
  auto ii=this->_transitions.find(lex);
  if(ii==this->_transitions.end()){
    this->_elseTransition.callCallback(fsa);
    return this->_elseTransition.getNextState();
  }
  ii->second.callCallback(fsa);
  return ii->second.getNextState();
}

std::string State::toStr()const{
  std::stringstream ss;
  bool first=true;
  for(auto x:this->_transitions){
    if(first)first=false;
    else ss<<",";
    ss<<x.first<<"->"<<x.second.toStr();
  }

  if(this->_elseTransition.getNextState()){
    if(this->_transitions.size()>0)ss<<",";
    ss<<"else->"<<this->_elseTransition.getNextState()->getName();
  }
  if(this->_eofTransition.getNextState()){
    if(this->_transitions.size()>0||this->_elseTransition.getNextState()!=nullptr)ss<<",";
    ss<<"eof->"<<this->_eofTransition.getNextState()->getName();
  }
  return ss.str();
}


