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

FunctionId FunctionRegister::addFunction(
    TypeId                           const&type   ,
    std::string                      const&name   ,
    std::shared_ptr<StatementFactory>const&factory){
  assert(this!=nullptr);
  assert(this->_typeRegister!=nullptr);
  assert(this->_namer!=nullptr);
  FunctionId id = this->_functions.size();
  this->_functions[id]=FunctionDefinition(type,name,factory);
  this->_namer->addFceNaming(id,this->_typeRegister->getNofFceArgs(type));
  this->_name2Function[name]=id;
  return id;
}

std::shared_ptr<Statement>FunctionRegister::sharedStatement(FunctionId id)const{
  assert(this!=nullptr);
  assert(std::get<FACTORY>(this->_getDefinition(id))!=nullptr);
  return (*std::get<FACTORY>(this->_getDefinition(id)))(std::const_pointer_cast<FunctionRegister>(this->shared_from_this()));
}

std::shared_ptr<Statement>FunctionRegister::sharedStatement(std::string const&name)const{
  assert(this!=nullptr);
  return this->sharedStatement(this->getFunctionId(name));
}

std::shared_ptr<Function>FunctionRegister::sharedFunction(FunctionId id)const{
  assert(this!=nullptr);
  return std::dynamic_pointer_cast<Function>(this->sharedStatement(id));
}

std::shared_ptr<Function>FunctionRegister::sharedFunction(std::string const&name)const{
  assert(this!=nullptr);
  return std::dynamic_pointer_cast<Function>(this->sharedStatement(name));
}

std::shared_ptr<StatementFactory>FunctionRegister::sharedFactory(FunctionId id,StatementFactory::Uses maxUses)const{
  assert(this!=nullptr);
  class Factory: public FunctionFactory{
    public:
      Factory(std::string const&name,Uses maxUses = 0):FunctionFactory(name,maxUses){}
      virtual ~Factory(){}
      virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister> const&fr)override{
        assert(this!=nullptr);
        assert(fr!=nullptr);
        return fr->sharedStatement(this->_name);
      }
      virtual TypeId getOutputType(std::shared_ptr<FunctionRegister>const&fr)const override{
        assert(this!=nullptr);
        return fr->getOutputType(fr->getFunctionId(this->getName()));
      }
      virtual size_t getNofInputs(std::shared_ptr<FunctionRegister>const&fr)const override{
        assert(this!=nullptr);
        return fr->getNofInputs(fr->getFunctionId(this->getName()));
      }
      virtual TypeId getInputType(std::shared_ptr<FunctionRegister>const&fr,size_t i)const override{
        assert(this!=nullptr);
        return fr->getInputType(fr->getFunctionId(this->getName()),i);
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
  for(auto const&x:this->_name2Function)
    ss<<x.first<<std::endl;
  return ss.str();
}


