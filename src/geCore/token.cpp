#include<geCore/token.h>

#include<sstream>
#include<geCore/fsa/fsa.h>

using namespace ge::core;

Token::Token(){
  this->term = 0;
  this->rawData = "";
}

Token::Token(Type const& term,Data const& rawData){
  this->term = term;
  this->rawData = rawData;
}

