#include<geCore/token.h>

#include<sstream>
#include<geCore/fsa/fsa.h>

using namespace ge::core;

Token::Token(){
  this->type = 0;
  this->rawData = "";
}

Token::Token(Type const& type,Data const& rawData){
  this->type = type;
  this->rawData = rawData;
}

