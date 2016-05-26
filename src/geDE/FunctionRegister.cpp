#include<geDE/Statement.h>
#include<geDE/Function.h>
#include<geDE/FunctionRegister.h>
#include<geDE/FunctionFactory.h>

using namespace ge::de;

std::string FunctionRegister::_genDefaultName(InputIndex i)const{
  std::stringstream ss;
  ss<<"input"<<i;
  return ss.str();
}

FunctionRegister::FunctionID FunctionRegister::addFunction(
    TypeRegister::TypeId             const&type   ,
    std::string                      const&name   ,
    std::shared_ptr<StatementFactory>const&factory){
  assert(this!=nullptr);
  assert(this->_typeRegister!=nullptr);
  assert(this->_namer!=nullptr);
  FunctionID id = this->_functions.size();
  this->_functions[id]=FunctionDefinition(type,name,factory);
  this->_namer->addFceNaming(id,this->_typeRegister->getNofFceArgs(type));
  this->_name2Function[name]=id;
  return id;
}

std::shared_ptr<Statement>FunctionRegister::sharedStatement(FunctionID id)const{
  assert(this!=nullptr);
  assert(std::get<FACTORY>(this->_getDefinition(id))!=nullptr);
  return (*std::get<FACTORY>(this->_getDefinition(id)))(std::const_pointer_cast<FunctionRegister>(this->shared_from_this()));
}

std::shared_ptr<Statement>FunctionRegister::sharedStatement(std::string const&name)const{
  assert(this!=nullptr);
  return this->sharedStatement(this->getFunctionId(name));
}

std::shared_ptr<Function>FunctionRegister::sharedFunction(FunctionID id)const{
  return std::dynamic_pointer_cast<Function>(this->sharedStatement(id));
}

std::shared_ptr<Function>FunctionRegister::sharedFunction(std::string const&name)const{
  return std::dynamic_pointer_cast<Function>(this->sharedStatement(name));
}

std::shared_ptr<StatementFactory>FunctionRegister::sharedFactory(FunctionID id,StatementFactory::Uses maxUses)const{
  assert(this!=nullptr);
  class Factory: public FunctionFactory{
    public:
      Factory(std::string const&name,Uses maxUses = 1):FunctionFactory(name,maxUses){}
      virtual ~Factory(){}
      virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister> const&fr){
        assert(this!=nullptr);
        assert(fr!=nullptr);
        return fr->sharedStatement(this->_name);
      }
  };
  return std::make_shared<Factory>(this->getName(id),maxUses);

//  return std::get<FACTORY>(this->_getDefinition(id));
}

std::shared_ptr<StatementFactory>FunctionRegister::sharedFactory(std::string const&name,StatementFactory::Uses maxUses)const{
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


