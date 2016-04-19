#include<geCore/Namer.h>
#include<sstream>

using namespace ge::core;

void Namer::addFceNaming(Namer::Id id,Namer::ElementIndex nofInputs){
  assert(this!=nullptr);
  std::vector<std::string>i2n;
  std::map<std::string,ElementIndex>n2i;
  i2n.resize(nofInputs);
  for(Namer::ElementIndex i=0;i<nofInputs;++i){
    std::stringstream ss;
    ss<<"input"<<i;
    i2n[i]=ss.str();
    n2i[ss.str()]=i;
  }
  this->_functionNaming[id] = FunctionNaming(i2n,n2i,"output");
}

void Namer::addStructNaming(Namer::Id id,Namer::ElementIndex nofElements){
  assert(this!=nullptr);
  std::vector<std::string>i2n;
  std::map<std::string,ElementIndex>n2i;
  i2n.resize(nofElements);
  for(Namer::ElementIndex i=0;i<nofElements;++i){
    std::stringstream ss;
    ss<<"element"<<i;
    i2n[i]=ss.str();
    n2i[ss.str()]=i;
  }
  this->_structureNaming[id] = StructureNaming(i2n,n2i);
}

void Namer::removeFceNaming(Id id){
  assert(this!=nullptr);
  this->_functionNaming.erase(id);
}

void Namer::removeStructNaming(Id id){
  assert(this!=nullptr);
  this->_structureNaming.erase(id);
}

