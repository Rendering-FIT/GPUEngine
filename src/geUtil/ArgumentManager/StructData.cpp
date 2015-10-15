#include<geUtil/ArgumentManager/StructData.h>
#include<geUtil/ArgumentManager/ArgData.h>
#include<sstream>

using namespace ge::util;

StructData::StructData():ArgData(ArgData::STRUCT){}

StructData::~StructData(){
  for(auto x:this->_data)
    delete x;
}

ArgData*StructData::operator[](unsigned i){
  return this->_data[i];
}

void StructData::add(ArgData*item){
  this->_data.push_back(item);
}

unsigned StructData::size(){
  return this->_data.size();
}

bool StructData::sameType(ArgData*other){
  if(this->_type!=other->getType())return false;
  StructData*b=(StructData*)other;
  if(b->size()!=this->size())return false;
  for(unsigned i=0;i<this->size();++i)
    if(!(*this)[i]->sameType((*b)[i]))return false;
  return true;
}


std::string StructData::toStr(){
  std::stringstream ss;
  ss<<"struct{";
  bool first=true;
  for(auto x:this->_data){
    if(first)first=false;
    else ss<<" ";
    ss<<x->toStr();
  }
  ss<<"}";
  return ss.str();
}
