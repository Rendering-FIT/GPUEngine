#include<geCore/tokenization.h>

using namespace ge::core;

Tokenization::Tokenization(std::string start){
  this->_fsa = std::make_shared<FSA>(start);
}

Tokenization::~Tokenization(){
}

void Tokenization::addTransition(
    std::string start,
    std::string lex  ,
    std::string end  ,
    std::string token,
    Config      conf ){
  if(token==""){
    this->_fsa->addTransition(start,lex,end);
    return;
  }
  auto term=this->_registerToken(token);
  this->_data.push_back(CallbackData(conf,term,&this->_position));
  this->_fsa->addTransition(start,lex,end,this->_callback,&this->_data[this->_data.size()-1]);
}

TermType Tokenization::_registerToken(std::string token){
  auto ii=this->_name2term.find(token);
  if(ii!=this->_name2term.end())return ii->second;
  TermType result=this->_name2term[token]=this->_name2term.size();
  this->_term2name[result]=token;
  return result;
}

void Tokenization::_callback(ge::core::FSA*fsa,void*data){
  auto cd=(CallbackData*)data;
  if(cd->conf&BEGIN)*cd->position = fsa->getCurrentPosition();
}
