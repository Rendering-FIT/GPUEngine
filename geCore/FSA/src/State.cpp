#include<GPUEngine/geCore/FSA/State.h>

#include<set>
#include<iostream>
#include<sstream>

using namespace ge::core;

FSAState::FSAState(std::string name){
  this->_name = name;
  this->_eofTransition .setCallback ();
  this->_eofTransition .setNextState();
}

FSAState::~FSAState(){
}

void FSAState::addTransition(
    char             lex     ,
    FSAState*        state   ,
    FSAFusedCallback callback){
  auto ii=this->_transitions.find(lex);
  if(ii==this->_transitions.end()){
    this->_transitions[lex]=FSATransition(state,callback);
    return;
  }
  if(ii->second.getNextState()!=state){
    std::cerr<<"you cannot create nondeterministic fsa: "
      <<this->getName()<<"-"<<lex<<"->"<<state->getName()<<std::endl;
    return;
  }
  ii->second.setCallback(callback);
}

void FSAState::addElseTransition(
    FSAState*        state   ,
    FSAFusedCallback callback){
  std::set<char>present;
  for(auto x:this->_transitions)
    present.insert(x.first);
  for(unsigned i=0;i<256;++i){
    char c=(char)i;
    if(present.find(c)==present.end())
      this->_transitions[c]=FSATransition(state,callback);
  }
}

void FSAState::addEOFTransition(
    FSAState*        state   ,
    FSAFusedCallback callback){
  this->_eofTransition.setNextState(state   );
  this->_eofTransition.setCallback (callback);
}

void FSAState::setCallback(char lex,FSAFusedCallback cb){
  this->_transitions[lex].setCallback(cb);
}

void FSAState::setEOFCallback(FSAFusedCallback cb){
  this->_eofTransition.setCallback(cb);
}

FSATransition const&FSAState::getTransition(char lex)const{
  return this->_transitions.find(lex)->second;
}

FSATransition const&FSAState::getEOFTransition()const{
  return this->_eofTransition;
}

std::string FSAState::getName()const{
  return this->_name;
}

decltype(FSAState::_transitions)::size_type FSAState::getNofTransition()const{
  return this->_transitions.size();
}

char FSAState::getTransitionLex(unsigned i)const{
  unsigned counter=0;
  for(auto x:this->_transitions)
    if(counter==i)return x.first;
  return 0;
}

void FSAState::clearTransitions   (){
  this->_transitions.clear();
}

void FSAState::clearEofTransition (){
  this->_eofTransition.setCallback ();
  this->_eofTransition.setNextState();
}

void FSAState::setEndState(char lex,FSAState*state){
  this->_transitions[lex].setNextState(state);
}

void FSAState::setEOFEndState(FSAState*state){
  this->_eofTransition.setNextState(state);
}

FSAState* FSAState::apply(char lex,FSA*fsa){
  auto ii=this->_transitions.find(lex);
  if(ii==this->_transitions.end())return nullptr;
  ii->second.callCallback(fsa);
  return ii->second.getNextState();
}

bool FSAState::hasEOFTransition()const{
  return this->_eofTransition.getNextState()!=nullptr;
}

bool FSAState::hasTransition(char lex)const{
  return this->_transitions.find(lex)!=this->_transitions.end();
}

std::string FSAState::toStr()const{
  std::stringstream ss;
  bool first=true;
  for(auto x:this->_transitions){
    if(first)first=false;
    else ss<<",";
    ss<<x.first<<"->"<<x.second.toStr();
  }

  if(this->_eofTransition.getNextState()){
    if(this->_transitions.size()>0)ss<<",";
    ss<<"eof->"<<this->_eofTransition.getNextState()->getName();
  }
  return ss.str();
}

FSAState::Iterator FSAState::begin()const{
  return this->_transitions.begin();
}

FSAState::Iterator FSAState::end  ()const{
  return this->_transitions.end();
}

