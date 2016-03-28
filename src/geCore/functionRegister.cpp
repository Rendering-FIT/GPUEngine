#include<geCore/functionRegister.h>

using namespace ge::core;

std::string FunctionRegister::_genDefaultName(InputIndex i)const{
  std::stringstream ss;
  ss<<"input"<<i;
  return ss.str();
}

FunctionRegister::FunctionID FunctionRegister::addFunction(
    TypeRegister::TypeID type,
    std::string name,
    std::shared_ptr<StatementFactory>const&factory){
  FunctionID id = this->_functions.size();
  this->_functions[id]=FunctionDefinition(type,name,factory,std::map<InputIndex,std::string>(),std::map<std::string,InputIndex>(),"");
  for(TypeRegister::DescriptionElement i=0;i<this->_typeRegister->getNofFceArgs(type);++i)
    this->setInputName(id,i,this->_genDefaultName(i));
  this->setOutputName(id,"output");
  return id;
}

