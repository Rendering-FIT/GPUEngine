#include<geCore/statement.h>
#include<geCore/function.h>
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
  this->_name2Function[name]=id;
  return id;
}

std::shared_ptr<Function>FunctionRegister::sharedFunction(FunctionID id)const{
  id=id;
  return nullptr;
  //return (*std::get<FACTORY>(this->_getDefinition(id)))(this->shared_from_this());
}

std::shared_ptr<Function>FunctionRegister::sharedFunction(std::string name)const{
  return this->sharedFunction(this->getFunctionId(name));
}

std::string FunctionRegister::str()const{
  std::stringstream ss;
  for(auto x:this->_name2Function)
    ss<<x.first<<std::endl;
  return ss.str();
}
