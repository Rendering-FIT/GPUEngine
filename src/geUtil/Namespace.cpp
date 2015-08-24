#include<geUtil/Namespace.h>

#include<algorithm>
#include<sstream>

using namespace ge::util::sim;

std::string Namespace::_toUpper(std::string str){
  std::transform(str.begin(), str.end(),str.begin(), ::toupper);
  return str;
}

Namespace::Namespace(std::string name,Namespace*parent){
  this->_name   = name  ;
  this->_parent = parent;
}

Namespace::~Namespace(){
  for(auto x:this->_name2Namespace)
    delete x.second;
}

bool Namespace::empty(){
  return this->_name2Variable.size()==0 && this->_name2Namespace.size()==0;
}

void Namespace::setParent(Namespace*parent){
  this->_parent = parent;
}

void Namespace::insertNamespace(std::string name,Namespace*nmspace){
  this->_name2Namespace.insert(std::pair<std::string,Namespace*>(name,nmspace));
}

std::string Namespace::toStr(unsigned indentation){
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

Namespace*Namespace::getNamespace(std::string name){
  if(this->_name2Namespace.count(name))
    return this->_name2Namespace[name];
  return nullptr;
}

void Namespace::insert(std::string name,std::shared_ptr<ge::core::Accessor>const&variable){
  std::size_t pos=name.find(".");
  if(pos==0){
    std::cerr<<"ERROR: can't insert variable "+name+" into "+this->_name+" - incorrect variable name, there is no namespace name before \".\""<<std::endl;
    return;
  }
  this->_name2Variable[name]=variable;
  if(pos==std::string::npos)return;
  std::string rest=name.substr(pos+1);
  std::string namespaceName=name.substr(0,pos);
  Namespace*nextNamespace=this->getNamespace(namespaceName);
  if(nextNamespace==NULL){
    nextNamespace=new Namespace(namespaceName);
    this->insertNamespace(namespaceName,nextNamespace);
    nextNamespace->setParent(this);
  }
  nextNamespace->insert(rest,variable);
}

void Namespace::erase(std::string name){
  std::size_t pos=name.find(".");
  if(pos==0){
    std::cerr<<"ERROR: can't erase variable "+name+" from "+this->_name+" - incorrect variable name, there is no namspace name before \".\""<<std::endl;
    return;
  }
  this->_name2Variable.erase(name);
  if(pos==std::string::npos)return;
  std::string rest=name.substr(pos+1);
  std::string namespaceName=name.substr(0,pos);
  Namespace*nextNamespace=this->getNamespace(namespaceName);
  if(!nextNamespace){
    std::cerr<<"ERROR: namespace "+this->_name+" does not sub namepace "+namespaceName<<std::endl;
    return;
  }
  nextNamespace->erase(rest);
  if(nextNamespace->empty())
    this->_name2Namespace.erase(namespaceName);
}

std::shared_ptr<ge::core::Accessor>&Namespace::getVariable (std::string name){
  return this->_name2Variable[name];
}

bool Namespace::contain(std::string name){
  return this->_name2Variable.find(name)!=this->_name2Variable.end();
}

