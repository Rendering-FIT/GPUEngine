#include<geCore/Namespace.h>

#include<algorithm>
#include<sstream>
#include<geCore/Accessor.h>

using namespace ge::core::sim;

std::string Namespace::_toUpper(std::string str){
  std::transform(str.begin(), str.end(),str.begin(), ::toupper);
  return str;
}

Namespace::Namespace(std::string name,SharedNamespace const&parent){
  this->_name   = name  ;
  this->_parent = parent;
}

Namespace::~Namespace(){
}

bool Namespace::empty()const{
  return this->_name2Variable.size()==0 && this->_name2Namespace.size()==0;
}

void Namespace::setParent(SharedNamespace const&parent){
  this->_parent = parent;
}

void Namespace::insertNamespace(std::string name,SharedNamespace const&nmspace){
  this->_name2Namespace.insert(std::pair<std::string,SharedNamespace>(name,nmspace));
}

std::string Namespace::toStr(unsigned indentation)const{
  std::stringstream ss;
  std::string ind="";
  for(unsigned i=0;i<indentation;++i)ind+=" ";
  ss<<ind<<this->_name<<"{"<<std::endl;
  for(auto x:this->_name2Variable){
    if(x.first.find(".")==std::string::npos)
      ss<<ind<<"  "<<x.second->getManager()->getTypeIdName(x.second->getId())<<" "<<x.first<<" = "<<x.second->data2Str()<<std::endl;
  }
  for(auto x:this->_name2Namespace)
    ss<<x.second->toStr(indentation+2);
  ss<<ind<<"}"<<std::endl;
  return ss.str();
}

Namespace::SharedNamespace Namespace::getNamespace(std::string name)const{
  if(this->_name2Namespace.count(name))
    return this->_name2Namespace.find(name)->second;
  return nullptr;
}

void Namespace::insert(std::string name,SharedAccessor const&variable){
  std::size_t pos=name.find(".");
  if(pos==0){
    std::cerr<<"ERROR: can't insert variable "+name+" into "+this->_name+" - incorrect variable name, there is no namespace name before \".\""<<std::endl;
    return;
  }
  if(this->contain(name))this->erase(name);
  this->_name2Variable[name]=variable;
  if(pos==std::string::npos)return;
  std::string rest=name.substr(pos+1);
  std::string namespaceName=name.substr(0,pos);
  auto nextNamespace=this->getNamespace(namespaceName);
  if(!nextNamespace){
    nextNamespace=std::make_shared<Namespace>(namespaceName);
    this->insertNamespace(namespaceName,nextNamespace);
    nextNamespace->setParent(this->shared_from_this());
  }
  nextNamespace->insert(rest,variable);
}

void Namespace::erase(std::string name){
  std::size_t pos=name.find(".");
  if(pos==0){
    std::cerr<<"ERROR: can't erase variable "+name+" from "+this->_name+" - incorrect variable name, there is no namespace name before \".\""<<std::endl;
    return;
  }
  this->_name2Variable.erase(name);
  if(pos==std::string::npos)return;
  std::string rest=name.substr(pos+1);
  std::string namespaceName=name.substr(0,pos);
  auto nextNamespace=this->getNamespace(namespaceName);
  if(!nextNamespace){
    std::cerr<<"ERROR: namespace "+this->_name+" does not sub namepace "+namespaceName<<std::endl;
    return;
  }
  nextNamespace->erase(rest);
  if(nextNamespace->empty())
    this->_name2Namespace.erase(namespaceName);
}

Namespace::SharedAccessor Namespace::getVariable (std::string name)const{
  auto it=this->_name2Variable.find(name);
  if(it==this->_name2Variable.end()){
    std::cerr<<"Namespace::getVariable Error: there is no variable with name: "<<name<<std::endl;
    return nullptr;
  }
  return it->second;
}

bool Namespace::contain(std::string name)const{
  return this->_name2Variable.find(name)!=this->_name2Variable.end();
}

Namespace::CNSIter  Namespace::namespacesBegin()const{
  return this->_name2Namespace.begin();
}

Namespace::CNSIter  Namespace::namespacesEnd  ()const{
  return this->_name2Namespace.end();
}

Namespace::CVarIter Namespace::varsBegin()const{
  return this->_name2Variable.begin();
}

Namespace::CVarIter Namespace::varsEnd  ()const{
  return this->_name2Variable.end();
}


