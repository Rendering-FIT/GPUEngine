#include<geDE/VariableRegister.h>
#include<geDE/TypeRegister.h>
#include<geDE/Resource.h>
#include<geDE/StdFunctions.h>
#include<cassert>
#include<algorithm>

using namespace ge::de;

VariableRegister::VariableRegister(
    std::string      name  ,
    VariableRegister*parent){
  PRINT_CALL_STACK(name,parent);
  assert(this!=nullptr);
  this->_name   = name  ;
  this->_parent = parent;
}

VariableRegister::~VariableRegister(){
  PRINT_CALL_STACK();
}

bool VariableRegister::empty()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  return this->_name2Variable.size()==0 && this->_name2Register.size()==0;
}

void VariableRegister::setParent(VariableRegister*parent){
  PRINT_CALL_STACK(parent);
  assert(this!=nullptr);
  this->_parent = parent;
}

void VariableRegister::insertVariableRegister(
    std::string name,
    SharedVariableRegister const&vr){
  PRINT_CALL_STACK(name,vr);
  assert(this!=nullptr);
  this->_name2Register[name]=vr;
}

std::string VariableRegister::toStr(
    unsigned indentation,
    std::shared_ptr<TypeRegister>const&tr)const{
  PRINT_CALL_STACK(indentation,tr);
  assert(this!=nullptr);
  std::stringstream ss;
  std::string ind="";
  for(unsigned i=0;i<indentation;++i)ind+=" ";
  ss<<ind<<this->_name<<"{"<<std::endl;
  for(auto x:this->_name2Variable){
    if(x.first.find(".")==std::string::npos){
      ss<<ind<<"  "<<x.first;
      auto resource = x.second;
      if(resource){
        ss<<" "<<tr->getTypeIdName(resource->getId())<<": ";
        ss<<resource->data2Str()<<std::endl;
      }
    }
  }
  for(auto x:this->_name2Register)
    ss<<x.second->toStr(indentation+2,tr);
  ss<<ind<<"}"<<std::endl;
  return ss.str();
}

std::string VariableRegister::getName()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  return this->_name;
}

std::string VariableRegister::getFullName()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  std::stringstream ss;
  VariableRegister const*node=this;
  std::vector<std::string>path;
  while(node){
    path.push_back(node->getName());
    node = node->_parent;
  }
  std::reverse(path.begin(),path.end());
  bool first=true;
  for(auto const&x:path){
    if(first)first=false;
    else ss<<".";
    ss<<x;
  }
  return ss.str();
}

bool VariableRegister::hasVariableRegister(std::string name)const{
  PRINT_CALL_STACK(name);
  assert(this!=nullptr);
  return this->_name2Register.count(name)!=0;
}

bool VariableRegister::hasVariable(std::string name)const{
  PRINT_CALL_STACK(name);
  assert(this!=nullptr);
  return this->_name2Variable.count(name)!=0;
}


VariableRegister::SharedVariableRegister const&VariableRegister::getVariableRegister(std::string name)const{
  PRINT_CALL_STACK(name);
  assert(this!=nullptr);
  auto ii = this->_name2Register.find(name);
  if(ii==this->_name2Register.end())
    ge::core::printError(GE_CORE_FCENAME,"there is no such sub variable register",name);
  assert(ii!=this->_name2Register.end());
  return ii->second;
}

bool VariableRegister::insert(std::string name,SharedVariable const&variable){
  PRINT_CALL_STACK(name,variable);
  assert(this!=nullptr);
  if(!this->_checkPath(name)){
    ge::core::printError(GE_CORE_FCENAME,"can't insert variable "+name+" into variableRegister "+this->getFullName()+" - incorrect variable name",name,variable);
    return false;
  }
  std::size_t pos=name.find(".");
  if(pos!=std::string::npos){
    std::string rest=name.substr(pos+1);
    std::string registerName=name.substr(0,pos);
    SharedVariableRegister nextVariableRegister = nullptr;
    if(this->hasVariableRegister(registerName))
      nextVariableRegister=this->getVariableRegister(registerName);
    if(!nextVariableRegister){
      nextVariableRegister=std::make_shared<VariableRegister>(registerName);
      this->insertVariableRegister(registerName,nextVariableRegister);
      nextVariableRegister->setParent(this);
    }
    if(!nextVariableRegister->insert(rest,variable))
      return false;
  }

  if(this->contain(name))this->erase(name);
  this->_name2Variable[name]=variable;
  return true;
}

void VariableRegister::erase(std::string name){
  PRINT_CALL_STACK(name);
  assert(this!=nullptr);

  name = this->getFullName()+"."+name;
  if(!this->_checkPath(name)){
    ge::core::printError(GE_CORE_FCENAME,"can't erase variable "+name+" - incorrect variable name",name);
    return;
  }

  name = name.substr(name.find(".")+1);
  VariableRegister*reg = this;
  while(reg->_parent)reg = reg->_parent;
  do{
    reg->_name2Variable.erase(name);
    size_t pos = name.find(".");
    if(pos==std::string::npos)break;
    auto regName = name.substr(0,pos);
    name = name.substr(pos+1);
    if(!reg->hasVariableRegister(regName))break;
    reg = &*reg->getVariableRegister(regName);
  }while(true);

  while(reg->empty()){
    std::string regName = reg->_name;
    if(!reg->_parent)break;
    reg = reg->_parent;
    reg->_name2Register.erase(regName);
  }
}

void VariableRegister::eraseVariableRegister(std::string name){
  PRINT_CALL_STACK(name);
  assert(this!=nullptr);
  std::size_t pos;
  VariableRegister*reg = this;
  std::string path = name;
  while((pos = path.find("."))!=std::string::npos){
    std::string first = path.substr(0,pos);
    if(!reg->hasVariableRegister(first))return;
    reg = &*reg->getVariableRegister(first);
    path = path.substr(pos+1);
  }
  std::vector<std::string>varsToErase;
  for(auto const&x:reg->_name2Variable){
    auto varName = reg->getFullName()+"."+x.first;
    varName = varName.substr(varName.find(".")+1);
    varsToErase.push_back(varName);
  }
  reg = this;
  while(reg->_parent)
    reg = reg->_parent;

  for(auto const&x:varsToErase)
    reg->erase(x);
}

VariableRegister::SharedVariable const&VariableRegister::getVariable (std::string name)const{
  PRINT_CALL_STACK(name);
  assert(this!=nullptr);
  auto it=this->_name2Variable.find(name);
  if(it==this->_name2Variable.end())
    ge::core::printError(GE_CORE_FCENAME,"there is no such variable",name);
  assert(this->_name2Variable.count(name)!=0);
  return it->second;
}

bool VariableRegister::contain(std::string name)const{
  PRINT_CALL_STACK(name);
  assert(this!=nullptr);
  return this->_name2Variable.count(name)!=0;
}

bool VariableRegister::_checkPath(std::string const&path)const{
  PRINT_CALL_STACK(path);
  size_t pos = 0;
  size_t newPos;
  do{
    newPos = path.find(".",pos);
    if(newPos==std::string::npos)return true;
    if(newPos==pos)return false;
    pos = newPos+1;
    if(pos>=path.size())return false;
  }while(true);
  return true;
}

VariableRegister::VariableIterator VariableRegister::varsBegin     (){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  return this->_name2Variable.begin();
}

VariableRegister::VariableIterator VariableRegister::varsEnd       (){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  return this->_name2Variable.end();
}

VariableRegister::RegisterIterator VariableRegister::registersBegin(){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  return this->_name2Register.begin();
}

VariableRegister::RegisterIterator VariableRegister::registersEnd  (){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  return this->_name2Register.end();
}

