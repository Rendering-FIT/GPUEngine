#include<geCore/tokenization.h>
#include<sstream>
#include<iterator>

using namespace ge::core;

Tokenization::Tokenization(std::string start){
  this->_data.fsa = std::make_shared<FSA>(start);
}

Tokenization::~Tokenization(){
}

void Tokenization::addTransition(
    std::string start ,
    std::string lex   ,
    std::string end   ,
    std::string token ,
    std::string config){
  Config conf=0;
  if(config.find(Tokenization::config_bit_begin )!=std::string::npos)conf|=BEGIN ;
  if(config.find(Tokenization::config_bit_end   )!=std::string::npos)conf|=END   ;
  if(config.find(Tokenization::config_bit_goback)!=std::string::npos)conf|=GOBACK;
  if(token==""){
    if(conf==EMPTY){
      this->_data.fsa->addTransition(start,lex,end);
    }else{
      this->_data.callbackData.push_back(std::make_shared<CallbackData>(conf,0,&this->_data));
      this->_data.fsa->addTransition(start,lex,end,
          this->_callback,&*this->_data.callbackData.back());
    }
    return;
  }

  if(end==""){
    this->_data.errorMessages.push_back(token);
    this->_data.fsa->addTransition(start,lex,end,
        this->_errorCallback,&this->_data.errorMessages.back());
    return;
  }

  TermType term = 0;
  if(token.find(" ")!=std::string::npos){
    std::stringstream ss(token);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    term = this->_registerToken(vstrings[0]);
    this->_data.hasKeywords.insert(term);
    for(auto x:vstrings)this->_registerToken(x);
  }else term = this->_registerToken(token);
  this->_data.callbackData.push_back(std::make_shared<CallbackData>(conf,term,&this->_data));
  this->_data.fsa->addTransition(start,lex,end,
      this->_callback,&*this->_data.callbackData.back());
}

std::string Tokenization::tokenName(TermType    term )const{
  auto ii=this->_data.term2name.find(term);
  if(ii!=this->_data.term2name.end())return ii->second;
  return "";
}

TermType    Tokenization::tokenType(std::string token)const{
  auto ii=this->_data.name2term.find(token);
  if(ii!=this->_data.name2term.end())return ii->second;
  return std::numeric_limits<TermType>::max();
}

TermType Tokenization::_registerToken(std::string token){
  auto ii=this->_data.name2term.find(token);
  if(ii!=this->_data.name2term.end())return ii->second;
  TermType result = this->_data.name2term.size();
  this->_data.name2term[token]=result;
  this->_data.term2name[result]=token;
  return result;
}

void Tokenization::_callback(ge::core::FSA*fsa,void*data){
  auto cd=(CallbackData*)data;
  if(cd->conf&BEGIN){
    cd->data->charPosition = fsa->getCurrentPosition();
    return;
  }
  if(cd->conf&Tokenization::END){
    auto word = fsa->getAlreadyReadString().substr(cd->data->charPosition);
    TermType term = cd->term;
    if(cd->data->hasKeywords.count(term)){
      auto ii=cd->data->name2term.find(word);
      if(ii!=cd->data->name2term.end())
        term=ii->second;
    }
    cd->data->tokens.push_back(Token(term,word));
  }else
    cd->data->tokens.push_back(Token(cd->term));
  if(cd->conf&GOBACK)fsa->goBack();
}

void Tokenization::_errorCallback(ge::core::FSA*fsa,void*data){
  std::string*cd=(std::string*)data;
  std::cerr<<"ERROR: Tokenization at position: ";
  std::cerr<<fsa->getCurrentPosition()<<" and char: ";
  std::cerr<<fsa->getCurrentChar()<<" - "<<*cd<<std::endl;
}


Tokenization::Token Tokenization::getToken(){
  return this->_data.tokens[this->_data.currentToken++];
}

bool Tokenization::empty()const{
  return this->_data.currentToken>=this->_data.tokens.size();
}

void Tokenization::clear(){
  this->_data.tokens.clear();
  this->_data.currentToken = 0;
}

void Tokenization::parse(std::string data){
  this->_data.fsa->unpause(data);
}

void Tokenization::end(){
  this->_data.fsa->stop("");
}

void Tokenization::begin(){
  this->_data.fsa->runWithPause("");
}
