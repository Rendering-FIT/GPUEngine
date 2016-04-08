#include<geCore/macroFunction.h>
#include<algorithm>

using namespace ge::core;

MacroFunction::MacroFunction(
    std::shared_ptr<FunctionRegister>const&fr,
    FunctionRegister::FunctionID id,
    std::shared_ptr<Function>const&output,
    std::vector<FceInputList>const&inputs):Function(fr,id){
  this->_outputMapping = output;
  this->_inputMapping  = inputs;
}

MacroFunction::~MacroFunction(){
}

bool MacroFunction::bindInput(InputIndex i,std::shared_ptr<Function>function){
  assert(this!=nullptr);
  if(!this->_inputBindingCheck(i,function))
    return false;
  for(auto x:this->_inputMapping[i]){
    assert(std::get<FUNCTION>(x)!=nullptr);
    std::get<FUNCTION>(x)->bindInput(std::get<INPUT>(x),function);
  }
  return true;
}


bool MacroFunction::bindOutput(std::shared_ptr<Accessor>data){
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->bindOutput(data);
}


bool MacroFunction::hasInput(InputIndex i)const{
  assert(this!=nullptr);
  for(auto x:this->_inputMapping[i]){
    assert(std::get<FUNCTION>(x)!=nullptr);
    if(!std::get<FUNCTION>(x)->hasInput(std::get<INPUT>(x)))return false;
  }
  return true;
}

bool MacroFunction::hasOutput()const{
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->hasOutput();
}

std::shared_ptr<Accessor>const&MacroFunction::getInputData(InputIndex i)const{
  assert(this!=nullptr);
  assert(i<this->_inputMapping.size());
  assert(this->_inputMapping[i].size()>0);
  FceInput const&mapping = this->_inputMapping[i][0];
  assert(std::get<FUNCTION>(mapping)!=nullptr);
  return std::get<FUNCTION>(mapping)->getInputData(std::get<INPUT>(mapping));
}

std::shared_ptr<Accessor>const&MacroFunction::getOutputData()const{
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->getOutputData();
}

Function::Ticks MacroFunction::getUpdateTicks()const{
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->getUpdateTicks();
}

Function::Ticks MacroFunction::getCheckTicks ()const{
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->getCheckTicks();
}

void  MacroFunction::setUpdateTicks(Ticks ticks){
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  this->_outputMapping->setUpdateTicks(ticks);
}

void  MacroFunction::setCheckTicks(Ticks ticks){
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  this->_outputMapping->setUpdateTicks(ticks);
}

std::shared_ptr<Function>const&MacroFunction::getInputFunction(InputIndex i)const{
  assert(this!=nullptr);
  assert(i<this->_inputMapping.size());
  assert(this->_inputMapping[i].size()>0);
  FceInput const&mapping = this->_inputMapping[i][0];
  assert(std::get<FUNCTION>(mapping)!=nullptr);
  return std::get<FUNCTION>(mapping)->getInputFunction(std::get<INPUT>(mapping));
}

FunctionNodeFactory::FunctionNodeFactory(
    std::string name,Uses maxUses):FunctionFactory(name,maxUses){
}

void FunctionNodeFactory::setFactory(
    std::shared_ptr<StatementFactory>const&fac){
  assert(this!=nullptr);
  this->functionFactory = std::dynamic_pointer_cast<FunctionFactory>(fac);
}

void FunctionNodeFactory::addResourceFactory(
    std::shared_ptr<ResourceFactory>const&factory){
  assert(this!=nullptr);
  this->resourceFactories.push_back(factory);
}

void FunctionNodeFactory::addInputFactory(
    std::shared_ptr<StatementFactory>const&factory){
  assert(this!=nullptr);
  this->inputFactories.push_back(std::dynamic_pointer_cast<FunctionFactory>(factory));
}

FunctionNodeFactory::~FunctionNodeFactory(){
}

std::shared_ptr<FunctionFactory>FunctionNodeFactory::getInputFactory(size_t input){
  assert(this!=nullptr);
  assert(input<this->inputFactories.size());
  return this->inputFactories[input];
}

void FunctionNodeFactory::reset(){
  assert(this!=nullptr);
  this->_uses    = 0      ;
  this->_first   = true   ;
  this->_result  = nullptr;
}

std::shared_ptr<Statement>FunctionNodeFactory::_do(
    std::shared_ptr<FunctionRegister> const&tr){
  assert(this!=nullptr);
  assert(tr!=nullptr);
  this->_first = this->_uses == 0;
  if(this->resourceFactories.size()!=this->inputFactories.size()){
    std::cerr<<"ERROR: FunctionNodeFactory::operator()() - different ";
    std::cerr<<"number of input functions and input resources"<<std::endl;
    return nullptr;
  }
  if(!this->functionFactory)return nullptr;

  auto res = (*this->functionFactory)(tr);

  auto fce=std::dynamic_pointer_cast<Function>(res);
  using Iter=decltype(this->resourceFactories)::size_type;
  for(Iter i=0;i<this->resourceFactories.size();++i){
    if(!this->resourceFactories[i]!=!this->inputFactories[i]){
      std::cerr<<"ERROR: FunctionNodeFactory::operator()() - input factory ";
      std::cerr<<"and input resource does not correspond"<<std::endl;
      return nullptr;
    }
    if(!this->resourceFactories[i])continue;
    auto in=(*this->inputFactories[i])(tr);
    auto inFce = std::dynamic_pointer_cast<Function>(in);
    assert(inFce!=nullptr);
    inFce->bindOutput((*this->resourceFactories[i])(tr));
    assert(fce!=nullptr);
    fce->bindInput(i,inFce);
  }
  return res;
}


MacroFunctionFactory::MacroFunctionFactory(std::string name,Uses maxUses):FunctionFactory(name,maxUses){
}

MacroFunctionFactory::~MacroFunctionFactory(){
}

std::shared_ptr<FunctionFactory>MacroFunctionFactory::getInputFactory(size_t input){
  assert(this!=nullptr);
  return this->_factory->getInputFactory(input);
}


void MacroFunctionFactory::setFactory(std::shared_ptr<StatementFactory>const&fac){
  assert(this!=nullptr);
  this->_factory = std::dynamic_pointer_cast<FunctionFactory>(fac);
}

void MacroFunctionFactory::setInputFactories(
    std::vector<FactoryInputList>const&inputs){
  assert(this!=nullptr);
  this->_inputs = inputs;
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
    this->_recBuildInput(fceInputs[i],std::dynamic_pointer_cast<Function>(res),this->_factory,this->_inputs[i]);
  }
  return std::dynamic_pointer_cast<Statement>(
      std::make_shared<MacroFunction>(
        fr,
        fr->getFunctionId(this->_name),
        std::dynamic_pointer_cast<Function>(res),
        fceInputs));
}

void MacroFunctionFactory::_recBuildInput(
    MacroFunction::FceInputList&          output          ,
    std::shared_ptr<Function>const&       fce             ,
    std::shared_ptr<FunctionFactory>const&fac             ,
    FactoryInputList const&               factoryInputList){
  assert(this!=nullptr);
  assert((fce!=nullptr) == (fac!=nullptr));
  if(fce==nullptr || fac==nullptr)return;
  for(Function::InputIndex i=0;i<factoryInputList.size();++i)
    if(std::get<FACTORY>(factoryInputList[i])==fac)
      output.push_back(MacroFunction::FceInput(fce,std::get<INPUT>(factoryInputList[i])));

  for(Function::InputIndex i=0;i<fce->getNofInputs();++i)
    this->_recBuildInput(output,fce->getInputFunction(i),fac->getInputFactory(i),factoryInputList);
}


