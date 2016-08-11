#include<geDE/CompositeFunctionFactory.h>
#include<geDE/FunctionRegister.h>
#include<geDE/FunctionNodeFactory.h>
#include<geDE/CompositeFunction.h>
#include<geDE/FactoryOfFunctionFactory.h>
#include<geDE/Resource.h>

using namespace ge::de;

CompositeFunctionFactory::CompositeFunctionFactory(
    Uses maxUses):FunctionFactory(maxUses){
  PRINT_CALL_STACK(maxUses);
}

CompositeFunctionFactory::~CompositeFunctionFactory(){
  PRINT_CALL_STACK();
}

std::shared_ptr<FunctionFactory>const&CompositeFunctionFactory::getInputFactory(size_t input)const{
  PRINT_CALL_STACK(input);
  assert(this!=nullptr);
  return this->_factory->getInputFactory(input);
}


void CompositeFunctionFactory::setFactory(std::shared_ptr<StatementFactory>const&fac){
  PRINT_CALL_STACK(fac);
  assert(this!=nullptr);
  this->_factory = std::dynamic_pointer_cast<FunctionNodeFactory>(fac);
}

void CompositeFunctionFactory::setInputFactories(
    std::vector<FactoryInputList>const&inputs){
  PRINT_CALL_STACK(inputs);
  assert(this!=nullptr);
  this->_inputs = inputs;
}

void _recBuildInput(
    CompositeFunction::FceInputList&                 output          ,
    std::shared_ptr<Function>                  const&fce             ,
    std::shared_ptr<FunctionFactory>           const&fac             ,
    CompositeFunctionFactory::FactoryInputList const&factoryInputList){
  PRINT_CALL_STACK(output,fce,fac,factoryInputList);
  assert((fce!=nullptr) == (fac!=nullptr));
  if(fce==nullptr || fac==nullptr)return;
  for(size_t i=0;i<factoryInputList.size();++i)
    if(std::get<CompositeFunctionFactory::FACTORY>(factoryInputList[i])==fac)
      output.push_back(CompositeFunction::FceInput(fce,std::get<CompositeFunctionFactory::INPUT>(factoryInputList[i])));

  auto functionNodeFactory = std::dynamic_pointer_cast<FunctionNodeFactory>(fac);
  for(size_t i=0;i<fce->getNofInputs();++i){
    if(functionNodeFactory == nullptr){
      if(fce->getInputData(i))
        _recBuildInput(output,fce->getInputFunction(i),nullptr,factoryInputList);
      else
        _recBuildInput(output,nullptr,nullptr,factoryInputList);
    }else{
      if(fce->getInputData(i))
        _recBuildInput(output,fce->getInputFunction(i),functionNodeFactory->getInputFactory(i),factoryInputList);
      else
        _recBuildInput(output,nullptr,functionNodeFactory->getInputFactory(i),factoryInputList);
    }
  }
}



std::shared_ptr<Statement>CompositeFunctionFactory::_do(
    std::shared_ptr<FunctionRegister>const&fr){
  PRINT_CALL_STACK(fr);
  assert(this!=nullptr);
  assert(fr!=nullptr);
  auto res = (*this->_factory)(fr);
  assert(res!=nullptr);
  auto ff = std::dynamic_pointer_cast<Function>(res);
  std::vector<CompositeFunction::FceInputList> fceInputs;
  assert(ff!=nullptr);
  for(size_t i=0;i<this->_inputs.size();++i){
    fceInputs.push_back(CompositeFunction::FceInputList());
    _recBuildInput(fceInputs[i],ff,this->_factory,this->_inputs[i]);
  }
  return std::dynamic_pointer_cast<Statement>(
      std::make_shared<CompositeFunction>(
        fr,
        this->getFunctionId(),
        ff,
        fceInputs));
}

TypeId CompositeFunctionFactory::getNofInputs()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  return this->_inputs.size();
}

TypeId CompositeFunctionFactory::getOutputType(std::shared_ptr<FunctionRegister>const&fr)const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  assert(fr!=nullptr);
  auto tr = fr->getTypeRegister();
  assert(tr!=nullptr);
  return tr->getFceReturnTypeId(fr->getType(this->_factory->getFactory()->getFunctionId()));
}

TypeId CompositeFunctionFactory::getInputType(std::shared_ptr<FunctionRegister>const&fr,size_t i)const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  assert(fr!=nullptr);
  auto tr = fr->getTypeRegister();
  assert(tr!=nullptr);
  assert(i<this->_inputs.size());
  assert(this->_inputs.at(i).size()!=0);
  auto const&x=this->_inputs.at(i).at(0);
  assert(std::get<FACTORY>(x)!=nullptr);
  return tr->getFceArgTypeId(fr->getType(std::get<FACTORY>(x)->getFunctionId()),std::get<INPUT>(x));
}

