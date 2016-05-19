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
  this->_name   = name  ;
  this->_parent = parent;
}

VariableRegister::~VariableRegister(){
}

bool VariableRegister::empty()const{
  return this->_name2Variable.size()==0 && this->_name2Register.size()==0;
}

void VariableRegister::setParent(VariableRegister*parent){
  this->_parent = parent;
}

void VariableRegister::insertVariableRegister(
    std::string name,
    SharedVariableRegister const&vr){
  this->_name2Register[name]=vr;
}

std::string VariableRegister::toStr(
    unsigned indentation,
    std::shared_ptr<TypeRegister>const&tr)const{
  std::stringstream ss;
  std::string ind="";
  for(unsigned i=0;i<indentation;++i)ind+=" ";
  ss<<ind<<this->_name<<"{"<<std::endl;
  for(auto x:this->_name2Variable){
    if(x.first.find(".")==std::string::npos){
      ss<<ind<<"  "<<x.first;
      auto resource = x.second->getOutputData();
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
  return this->_name;
}

std::string VariableRegister::getFullName()const{
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
  assert(this!=nullptr);
  return this->_name2Register.count(name)!=0;
}

bool VariableRegister::hasVariable(std::string name)const{
  assert(this!=nullptr);
  return this->_name2Variable.count(name)!=0;
}


VariableRegister::SharedVariableRegister const&VariableRegister::getVariableRegister(std::string name)const{
  assert(this!=nullptr);
  assert(this->_name2Register.count(name)!=0);
  auto ii = this->_name2Register.find(name);
  return ii->second;
}

bool VariableRegister::insert(std::string name,SharedVariable const&variable){
  assert(this!=nullptr);
  std::size_t pos=name.find(".");
  if(pos==0){
    std::cerr<<"ERROR: can't insert variable "+name+" into "+this->_name+" - incorrect variable name, there is no namespace name before \".\""<<std::endl;
    return false;
  }
  if(this->contain(name))this->erase(name);
  this->_name2Variable[name]=variable;
  if(pos==std::string::npos)return true;
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
  return nextVariableRegister->insert(rest,variable);
}

void VariableRegister::erase(std::string name){
  assert(this!=nullptr);
  std::size_t pos=name.find(".");
  if(pos==0){
    std::cerr<<"ERROR: can't erase variable "+name+" from "+this->_name+" - incorrect variable name, there is no namespace name before \".\""<<std::endl;
    return;
  }
  this->_name2Variable.erase(name);
  if(pos==std::string::npos)return;
  std::string rest=name.substr(pos+1);
  std::string namespaceName=name.substr(0,pos);
  auto nextVariableRegister=this->getVariableRegister(namespaceName);
  if(!nextVariableRegister){
    std::cerr<<"ERROR: namespace "+this->_name+" does not sub namepace "+namespaceName<<std::endl;
    return;
  }
  nextVariableRegister->erase(rest);
  if(nextVariableRegister->empty())
    this->_name2Register.erase(namespaceName);
}

VariableRegister::SharedVariable const&VariableRegister::getVariable (std::string name)const{
  assert(this!=nullptr);
  assert(this->_name2Variable.count(name)!=0);
  auto it=this->_name2Variable.find(name);
  return it->second;
}

bool VariableRegister::contain(std::string name)const{
  return this->_name2Variable.count(name)!=0;
}

VariableRegister::VariableIterator VariableRegister::varsBegin     (){return this->_name2Variable.begin();}
VariableRegister::VariableIterator VariableRegister::varsEnd       (){return this->_name2Variable.end();}
VariableRegister::RegisterIterator VariableRegister::registersBegin(){return this->_name2Register.begin();}
VariableRegister::RegisterIterator VariableRegister::registersEnd  (){return this->_name2Register.end();}

