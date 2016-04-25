#include<geCore/NameRegister.h>
#include<sstream>

using namespace ge::core;

void NameRegister::addFceNaming(NameRegister::Id id,NameRegister::ElementIndex nofInputs){
  assert(this!=nullptr);
  std::vector<std::string>i2n;
  std::map<std::string,ElementIndex>n2i;
  i2n.resize(nofInputs);
  for(NameRegister::ElementIndex i=0;i<nofInputs;++i){
    std::stringstream ss;
    ss<<"input"<<i;
    i2n[i]=ss.str();
    n2i[ss.str()]=i;
  }
  this->_functionNaming[id] = FunctionNaming(i2n,n2i,"output");
}

void NameRegister::addStructNaming(NameRegister::Id id,NameRegister::ElementIndex nofElements){
  assert(this!=nullptr);
  std::vector<std::string>i2n;
  std::map<std::string,ElementIndex>n2i;
  i2n.resize(nofElements);
  for(NameRegister::ElementIndex i=0;i<nofElements;++i){
    std::stringstream ss;
    ss<<"element"<<i;
    i2n[i]=ss.str();
    n2i[ss.str()]=i;
  }
  this->_structureNaming[id] = StructureNaming(i2n,n2i);
}

void NameRegister::removeFceNaming(Id id){
  assert(this!=nullptr);
  this->_functionNaming.erase(id);
}

void NameRegister::removeStructNaming(Id id){
  assert(this!=nullptr);
  this->_structureNaming.erase(id);
}

