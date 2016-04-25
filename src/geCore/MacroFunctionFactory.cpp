#include<geCore/MacroFunctionFactory.h>
#include<geCore/functionRegister.h>
#include<geCore/FunctionNodeFactory.h>
#include<geCore/macroFunction.h>

using namespace ge::core;

MacroFunctionFactory::MacroFunctionFactory(
    std::string const&name   ,
    Uses              maxUses):FunctionFactory(name,maxUses){
}

MacroFunctionFactory::~MacroFunctionFactory(){
}

std::shared_ptr<FunctionFactory>const&MacroFunctionFactory::getInputFactory(size_t input)const{
  assert(this!=nullptr);
  return this->_factory->getInputFactory(input);
}


void MacroFunctionFactory::setFactory(std::shared_ptr<StatementFactory>const&fac){
  assert(this!=nullptr);
  this->_factory = std::dynamic_pointer_cast<FunctionNodeFactory>(fac);
}

void MacroFunctionFactory::setInputFactories(
    std::vector<FactoryInputList>const&inputs){
  assert(this!=nullptr);
  this->_inputs = inputs;
}

void _recBuildInput(
    MacroFunction::FceInputList&                 output          ,
    std::shared_ptr<Function>              const&fce             ,
    std::shared_ptr<FunctionFactory>       const&fac             ,
    MacroFunctionFactory::FactoryInputList const&factoryInputList){
  assert((fce!=nullptr) == (fac!=nullptr));
  if(fce==nullptr || fac==nullptr)return;
  for(Function::InputIndex i=0;i<factoryInputList.size();++i)
    if(std::get<MacroFunctionFactory::FACTORY>(factoryInputList[i])==fac)
      output.push_back(MacroFunction::FceInput(fce,std::get<MacroFunctionFactory::INPUT>(factoryInputList[i])));

  for(Function::InputIndex i=0;i<fce->getNofInputs();++i){
    auto functionNodeFactory = std::dynamic_pointer_cast<FunctionNodeFactory>(fac);
    if(functionNodeFactory == nullptr)
      _recBuildInput(output,fce->getInputFunction(i),nullptr,factoryInputList);
    else
      _recBuildInput(output,fce->getInputFunction(i),functionNodeFactory->getInputFactory(i),factoryInputList);
  }
}



std::shared_ptr<Statement>MacroFunctionFactory::_do(
    std::shared_ptr<FunctionRegister>const&fr){
  assert(this!=nullptr);
  assert(fr!=nullptr);
  auto res = (*this->_factory)(fr);
  assert(res!=nullptr);
  auto ff = std::dynamic_pointer_cast<Function>(res);
  std::vector<MacroFunction::FceInputList> fceInputs;
  assert(ff!=nullptr);
  assert(ff->getNofInputs()==this->_inputs.size());
  for(Function::InputIndex i=0;i<ff->getNofInputs();++i){
    fceInputs.push_back(MacroFunction::FceInputList());
    _recBuildInput(fceInputs[i],std::dynamic_pointer_cast<Function>(res),this->_factory,this->_inputs[i]);
  }
  return std::dynamic_pointer_cast<Statement>(
      std::make_shared<MacroFunction>(
        fr,
        fr->getFunctionId(this->_name),
        std::dynamic_pointer_cast<Function>(res),
        fceInputs));
}


