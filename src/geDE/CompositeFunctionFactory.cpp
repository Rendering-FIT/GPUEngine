#include<geDE/CompositeFunctionFactory.h>
#include<geDE/FunctionRegister.h>
#include<geDE/FunctionNodeFactory.h>
#include<geDE/CompositeFunction.h>
#include<geDE/FactoryOfFunctionFactory.h>
#include<geDE/Resource.h>

using namespace ge::de;

CompositeFunctionFactory::CompositeFunctionFactory(
    std::string const&name   ,
    Uses              maxUses):FunctionFactory(name,maxUses){
  PRINT_CALL_STACK(name,maxUses);
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
  for(size_t i=0;i<functionNodeFactory->getNofInputs();++i){
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
    _recBuildInput(fceInputs[i],std::dynamic_pointer_cast<Function>(res),this->_factory,this->_inputs[i]);
  }
  return std::dynamic_pointer_cast<Statement>(
      std::make_shared<CompositeFunction>(
        fr,
        fr->getFunctionId(this->_name),
        std::dynamic_pointer_cast<Function>(res),
        fceInputs));
}

TypeId CompositeFunctionFactory::getOutputType(
    std::shared_ptr<FunctionRegister>const&fr)const{
  PRINT_CALL_STACK(fr);
  assert(this!=nullptr);
  return this->_factory->getOutputType(fr);
}

size_t CompositeFunctionFactory::getNofInputs(
    std::shared_ptr<FunctionRegister>const&)const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  return this->_inputs.size();
}

TypeId CompositeFunctionFactory::getInputType(
    std::shared_ptr<FunctionRegister>const&fr,size_t i)const{
  PRINT_CALL_STACK(fr,i);
  assert(this!=nullptr);
  assert(i<this->_inputs.size());
  assert(this->_inputs.at(i).size()>0);
  auto const&fac=std::get<FACTORY>(this->_inputs.at(i).at(0));
  auto const&input=std::get<INPUT>(this->_inputs.at(i).at(0));
  return fac->getInputType(fr,input);
}

