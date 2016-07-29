#include<geDE/CompositeFunctionFactory.h>
#include<geDE/FunctionRegister.h>
#include<geDE/FunctionNodeFactory.h>
#include<geDE/CompositeFunction.h>
#include<geDE/FactoryOfFunctionFactory.h>

using namespace ge::de;

CompositeFunctionFactory::CompositeFunctionFactory(
    std::string const&name   ,
    Uses              maxUses):FunctionFactory(name,maxUses){
}

CompositeFunctionFactory::~CompositeFunctionFactory(){
}

std::shared_ptr<FunctionFactory>const&CompositeFunctionFactory::getInputFactory(size_t input)const{
  assert(this!=nullptr);
  return this->_factory->getInputFactory(input);
}


void CompositeFunctionFactory::setFactory(std::shared_ptr<StatementFactory>const&fac){
  assert(this!=nullptr);
  this->_factory = std::dynamic_pointer_cast<FunctionNodeFactory>(fac);
}

void CompositeFunctionFactory::setInputFactories(
    std::vector<FactoryInputList>const&inputs){
  assert(this!=nullptr);
  this->_inputs = inputs;
}

void _recBuildInput(
    CompositeFunction::FceInputList&                 output          ,
    std::shared_ptr<Function>                  const&fce             ,
    std::shared_ptr<FunctionFactory>           const&fac             ,
    CompositeFunctionFactory::FactoryInputList const&factoryInputList){
  assert((fce!=nullptr) == (fac!=nullptr));
  if(fce==nullptr || fac==nullptr)return;
  for(Function::InputIndex i=0;i<factoryInputList.size();++i)
    if(std::get<CompositeFunctionFactory::FACTORY>(factoryInputList[i])==fac)
      output.push_back(CompositeFunction::FceInput(fce,std::get<CompositeFunctionFactory::INPUT>(factoryInputList[i])));

  auto functionNodeFactory = std::dynamic_pointer_cast<FunctionNodeFactory>(fac);
  for(Function::InputIndex i=0;i<functionNodeFactory->getNofInputs();++i){
    if(functionNodeFactory == nullptr)
      _recBuildInput(output,fce->getInputFunction(i),nullptr,factoryInputList);
    else
      _recBuildInput(output,fce->getInputFunction(i),functionNodeFactory->getInputFactory(i),factoryInputList);
  }
}



std::shared_ptr<Statement>CompositeFunctionFactory::_do(
    std::shared_ptr<FunctionRegister>const&fr){
  assert(this!=nullptr);
  assert(fr!=nullptr);
  auto res = (*this->_factory)(fr);
  assert(res!=nullptr);
  auto ff = std::dynamic_pointer_cast<Function>(res);
  std::vector<CompositeFunction::FceInputList> fceInputs;
  assert(ff!=nullptr);
  for(Function::InputIndex i=0;i<this->_inputs.size();++i){
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
  assert(this!=nullptr);
  return this->_factory->getOutputType(fr);
}

size_t CompositeFunctionFactory::getNofInputs(
    std::shared_ptr<FunctionRegister>const&)const{
  assert(this!=nullptr);
  return this->_inputs.size();
}

TypeId CompositeFunctionFactory::getInputType(
    std::shared_ptr<FunctionRegister>const&fr,size_t i)const{
  assert(this!=nullptr);
  assert(i<this->_inputs.size());
  assert(this->_inputs.at(i).size()>0);
  auto const&fac=std::get<FACTORY>(this->_inputs.at(i).at(0));
  auto const&input=std::get<INPUT>(this->_inputs.at(i).at(0));
  return fac->getInputType(fr,input);
}

