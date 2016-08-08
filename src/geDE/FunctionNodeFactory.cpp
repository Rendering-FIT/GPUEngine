#include<geDE/FunctionNodeFactory.h>
#include<geDE/Function.h>
#include<geDE/ResourceFactory.h>
#include<geCore/ErrorPrinter.h>

using namespace ge::de;

FunctionNodeFactory::FunctionNodeFactory(
    std::string name,Uses maxUses):FunctionFactory(name,maxUses){
  PRINT_CALL_STACK(name,maxUses);
}

void FunctionNodeFactory::setFactory(
    std::shared_ptr<StatementFactory>const&fac){
  PRINT_CALL_STACK(fac);
  assert(this!=nullptr);
  this->functionFactory = std::dynamic_pointer_cast<FunctionFactory>(fac);
}

void FunctionNodeFactory::addResourceFactory(
    std::shared_ptr<ResourceFactory>const&factory){
  PRINT_CALL_STACK(factory);
  assert(this!=nullptr);
  this->resourceFactories.push_back(factory);
  if(factory)factory->setUses(factory->getUses()+1);
}

void FunctionNodeFactory::addInputFactory(
    std::shared_ptr<StatementFactory>const&factory){
  PRINT_CALL_STACK(factory);
  assert(this!=nullptr);
  this->inputFactories.push_back(std::dynamic_pointer_cast<FunctionFactory>(factory));
  if(factory)factory->setUses(factory->getUses()+1);
}

FunctionNodeFactory::~FunctionNodeFactory(){
  PRINT_CALL_STACK();
}

void FunctionNodeFactory::reset(){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  this->_uses    = 0      ;
  this->_first   = true   ;
  this->_result  = nullptr;
}

std::shared_ptr<Statement>FunctionNodeFactory::_do(
    std::shared_ptr<FunctionRegister> const&fr){
  PRINT_CALL_STACK(fr);
  assert(this!=nullptr);
  assert(fr!=nullptr);
  this->_first = this->_uses == 0;
  if(this->resourceFactories.size()!=this->inputFactories.size()){
    ge::core::printError(GE_CORE_FCENAME,"different number of input functions and input resources",fr);
    return nullptr;
  }
  if(!this->functionFactory)return nullptr;

  auto statement = (*this->functionFactory)(fr);
  assert(statement!=nullptr);

  auto fce=std::dynamic_pointer_cast<Function>(statement);
  for(size_t i=0;i<this->resourceFactories.size();++i){
    if(this->resourceFactories[i]==nullptr&&this->inputFactories[i]!=nullptr){
      ge::core::printError(GE_CORE_FCENAME,"there is input factory but there is no resource factory",fr);
      return nullptr;
    }
    if(this->resourceFactories[i]==nullptr)continue;
    auto resource = (*this->resourceFactories[i])(fr);
    assert(resource!=nullptr);
    if(this->inputFactories[i]){
      auto in=(*this->inputFactories[i])(fr);
      auto inFce = std::dynamic_pointer_cast<Function>(in);
      assert(inFce!=nullptr);
      inFce->bindOutput(fr,resource);
    }
    assert(fce!=nullptr);
    fce->bindInput(fr,i,resource);
  }
  return statement;
}

std::shared_ptr<FunctionFactory>const&FunctionNodeFactory::getFactory()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  return this->functionFactory;
}

TypeId FunctionNodeFactory::getOutputType(std::shared_ptr<FunctionRegister>const&fr)const{
  PRINT_CALL_STACK(fr);
  assert(this!=nullptr);
  return this->functionFactory->getOutputType(fr);
}

size_t FunctionNodeFactory::getNofInputs(std::shared_ptr<FunctionRegister>const&fr)const{
  PRINT_CALL_STACK(fr);
  assert(this!=nullptr);
  return this->functionFactory->getNofInputs(fr);
}

TypeId FunctionNodeFactory::getInputType(std::shared_ptr<FunctionRegister>const&fr,size_t i)const{
  PRINT_CALL_STACK(fr,i);
  assert(this!=nullptr);
  return this->functionFactory->getInputType(fr,i);
}

