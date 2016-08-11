#include<geDE/Statement.h>
#include<geDE/Function.h>
#include<geDE/FunctionRegister.h>
#include<geDE/FunctionFactory.h>

using namespace ge::de;

std::string FunctionRegister::_genDefaultName(InputIndex i)const{
  PRINT_CALL_STACK(i);
  std::stringstream ss;
  ss<<"input"<<i;
  return ss.str();
}

FunctionId FunctionRegister::addFunction(
    TypeId                           const&type   ,
    std::string                      const&name   ,
    std::shared_ptr<StatementFactory>const&factory){
  PRINT_CALL_STACK(type,name,factory);
  assert(this!=nullptr);
  assert(this->_typeRegister!=nullptr);
  assert(this->_namer!=nullptr);
  FunctionId id = this->_functions.size();
  auto fceFac = std::dynamic_pointer_cast<FunctionFactory>(factory);
  if(fceFac)fceFac->setFunctionId(id);
  this->_functions[id]=FunctionDefinition(type,name,factory);
  this->_namer->addFceNaming(id,this->_typeRegister->getNofFceArgs(type));
  this->_name2Function[name]=id;
  return id;
}

std::shared_ptr<Statement>FunctionRegister::sharedStatement(FunctionId id)const{
  PRINT_CALL_STACK(id);
  assert(this!=nullptr);
  assert(std::get<FACTORY>(this->_getDefinition(id))!=nullptr);
  return (*std::get<FACTORY>(this->_getDefinition(id)))(std::const_pointer_cast<FunctionRegister>(this->shared_from_this()));
}

std::shared_ptr<Statement>FunctionRegister::sharedStatement(std::string const&name)const{
  PRINT_CALL_STACK(name);
  assert(this!=nullptr);
  return this->sharedStatement(this->getFunctionId(name));
}

std::shared_ptr<Function>FunctionRegister::sharedFunction(FunctionId id)const{
  PRINT_CALL_STACK(id);
  assert(this!=nullptr);
  return std::dynamic_pointer_cast<Function>(this->sharedStatement(id));
}

std::shared_ptr<Function>FunctionRegister::sharedFunction(std::string const&name)const{
  PRINT_CALL_STACK(name);
  assert(this!=nullptr);
  return std::dynamic_pointer_cast<Function>(this->sharedStatement(name));
}

std::shared_ptr<StatementFactory>FunctionRegister::sharedFactory(FunctionId id,StatementFactory::Uses maxUses)const{
  PRINT_CALL_STACK(id,maxUses);
  assert(this!=nullptr);
  class Factory: public FunctionFactory{
    public:
      Factory(FunctionId id,Uses maxUses = 0):FunctionFactory(maxUses){
        assert(this!=nullptr);
        this->setFunctionId(id);
      }
      virtual ~Factory(){}
      virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister> const&fr)override{
        assert(this!=nullptr);
        assert(fr!=nullptr);
        return fr->sharedStatement(this->getFunctionId());
      }
  };
  return std::make_shared<Factory>(id,maxUses);
}

std::shared_ptr<StatementFactory>FunctionRegister::sharedFactory(std::string const&name,StatementFactory::Uses maxUses)const{
  PRINT_CALL_STACK(name,maxUses);
  assert(this!=nullptr);
  return this->sharedFactory(this->getFunctionId(name),maxUses);
}


std::string FunctionRegister::str()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  std::stringstream ss;
  for(auto const&x:this->_name2Function)
    ss<<x.first<<std::endl;
  return ss.str();
}


