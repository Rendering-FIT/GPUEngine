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
  assert(this!=nullptr);
  assert(this->_typeRegister!=nullptr);
  FunctionID id = this->_functions.size();
  this->_functions[id]=FunctionDefinition(type,name,factory,std::map<InputIndex,std::string>(),std::map<std::string,InputIndex>(),"");
  for(TypeRegister::DescriptionElement i=0;i<this->_typeRegister->getNofFceArgs(type);++i)
    this->setInputName(id,i,this->_genDefaultName(i));
  this->setOutputName(id,"output");
  this->_name2Function[name]=id;
  return id;
}

std::shared_ptr<Statement>FunctionRegister::sharedFunction(FunctionID id)const{
  assert(this!=nullptr);
  assert(std::get<FACTORY>(this->_getDefinition(id))!=nullptr);
  return (*std::get<FACTORY>(this->_getDefinition(id)))(std::const_pointer_cast<FunctionRegister>(this->shared_from_this()));
}

std::shared_ptr<Statement>FunctionRegister::sharedFunction(std::string name)const{
  assert(this!=nullptr);
  return this->sharedFunction(this->getFunctionId(name));
}

std::shared_ptr<StatementFactory>FunctionRegister::sharedFactory(FunctionID id,StatementFactory::Uses maxUses)const{
  assert(this!=nullptr);
  class Factory: public FunctionFactory{
    public:
      Factory(std::string name,Uses maxUses = 1):FunctionFactory(name,maxUses){}
      virtual ~Factory(){}
      virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister> const&fr){
        assert(this!=nullptr);
        assert(fr!=nullptr);
        return fr->sharedFunction(this->_name);
      }
  };
  return std::make_shared<Factory>(this->getName(id),maxUses);

//  return std::get<FACTORY>(this->_getDefinition(id));
}

std::shared_ptr<StatementFactory>FunctionRegister::sharedFactory(std::string name,StatementFactory::Uses maxUses)const{
  assert(this!=nullptr);
  return this->sharedFactory(this->getFunctionId(name),maxUses);
}


std::string FunctionRegister::str()const{
  assert(this!=nullptr);
  std::stringstream ss;
  for(auto x:this->_name2Function)
    ss<<x.first<<std::endl;
  return ss.str();
}
