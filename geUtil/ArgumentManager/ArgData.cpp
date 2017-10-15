#include<geUtil/ArgumentManager/ArgData.h>

using namespace ge::util;

ArgData::ArgData(ArgData::Type type){
  this->_type = type;
}

ArgData::~ArgData(){}

ArgData::Type ArgData::getType(){
  return this->_type;
}

bool ArgData::sameType(ArgData*other){
  return this->_type == other->_type;
}

std::string ArgData::toStr(){
  return "";
}
