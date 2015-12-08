#include<geUtil/ArgumentManager/ArrayData.h>
#include<sstream>

using namespace ge::util;

ArrayData::ArrayData(ArrayData::Type innerType):ArgData(ArgData::ARRAY){
  this->_innerType = innerType;
}

ArrayData::~ArrayData(){
  for(auto x:this->_data)
    delete x;
}

ArgData*ArrayData::operator[](unsigned i){
  return this->_data[i];
}

void ArrayData::add(ArgData*item){
  this->_data.push_back(item);
}

decltype(ArrayData::_data)::size_type ArrayData::size(){
  return this->_data.size();
}

ArgData::Type ArrayData::getInnerType(){
  return this->_innerType;
}

bool ArrayData::sameType(ArgData*other){
  if(this->_type!=other->getType())return false;
  ArrayData*b=(ArrayData*)other;
  if(this->size()!=b->size())return false;
  return (*this)[0]->sameType((*b)[0]);
}

std::string ArrayData::toStr(){
  std::stringstream ss;
  ss<<"[";
  bool first=true;
  for(auto x:this->_data){
    if(first)first=false;
    else ss<<" ";
    ss<<x->toStr();
  }
  ss<<"]";
  return ss.str();
}
