#include<geCore/macroFunction.h>

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
  if(!this->_inputBindingCheck(i,function))
    return false;
  for(auto x:this->_inputMapping[i])
    std::get<FUNCTION>(x)->bindInput(std::get<INPUT>(x),function);
  return true;
}


bool MacroFunction::bindOutput(std::shared_ptr<Accessor>data){
  return this->_outputMapping->bindOutput(data);
}


bool MacroFunction::hasInput(InputIndex i)const{
  for(auto x:this->_inputMapping[i])
    if(!std::get<FUNCTION>(x)->hasInput(std::get<INPUT>(x)))return false;
  return true;
}

bool MacroFunction::hasOutput()const{
  return this->_outputMapping->hasOutput();
}

std::shared_ptr<Accessor>const&MacroFunction::getInputData(InputIndex i)const{
  FceInput const&mapping = this->_inputMapping[i][0];
  return std::get<FUNCTION>(mapping)->getInputData(std::get<INPUT>(mapping));
}

std::shared_ptr<Accessor>const&MacroFunction::getOutputData()const{
  return this->_outputMapping->getOutputData();
}

Function::Ticks MacroFunction::getUpdateTicks()const{
  return this->_outputMapping->getUpdateTicks();
}

Function::Ticks MacroFunction::getCheckTicks ()const{
  return this->_outputMapping->getCheckTicks();
}

void  MacroFunction::setUpdateTicks(Ticks ticks){
  this->_outputMapping->setUpdateTicks(ticks);
}

void  MacroFunction::setCheckTicks(Ticks ticks){
  this->_outputMapping->setUpdateTicks(ticks);
}

std::shared_ptr<Function>const&MacroFunction::getInputFunction(InputIndex i)const{
  FceInput const&mapping = this->_inputMapping[i][0];
  return std::get<FUNCTION>(mapping)->getInputFunction(std::get<INPUT>(mapping));
}
/*
   MacroFunction::MacroFunction(
   std::shared_ptr<TypeRegister>const&tr,TypeRegister::TypeID id):
   Function(tr,id,"MacroFunction"){
   }

   MacroFunction::~MacroFunction(){
   }

   bool MacroFunction::_do(){
   std::cerr<<"ERROR: MacroFunction::_do() - ";
   std::cerr<<"this should not be called at all"<<std::endl;
   return false;
   }
   */
FunctionNodeFactory::FunctionNodeFactory(std::string name,Uses maxUses):FunctionFactory(name,maxUses){
}

void FunctionNodeFactory::setFactory(std::shared_ptr<StatementFactory>const&fac){
  this->functionFactory = std::dynamic_pointer_cast<FunctionFactory>(fac);
}

void FunctionNodeFactory::addResourceFactory(std::shared_ptr<ResourceFactory>const&factory){
  this->resourceFactories.push_back(factory);
}
void FunctionNodeFactory::addInputFactory(std::shared_ptr<StatementFactory>const&factory){
  this->inputFactories.push_back(std::dynamic_pointer_cast<FunctionFactory>(factory));
}

FunctionNodeFactory::~FunctionNodeFactory(){
}

void FunctionNodeFactory::reset(){
  this->_uses    = 0      ;
  this->_first   = true   ;
  this->_result  = nullptr;
}

std::shared_ptr<Statement>FunctionNodeFactory::_do(
    std::shared_ptr<FunctionRegister> const&tr){
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
    inFce->bindOutput((*this->resourceFactories[i])(tr));
    fce->bindInput((unsigned)i,inFce);
  }
  return res;
}


MacroFunctionFactory::MacroFunctionFactory(std::string name,Uses maxUses):FunctionFactory(name,maxUses){
}

MacroFunctionFactory::~MacroFunctionFactory(){
}

void MacroFunctionFactory::setFactory(std::shared_ptr<StatementFactory>const&fac){
  this->_factory = std::dynamic_pointer_cast<FunctionFactory>(fac);
}

void MacroFunctionFactory::setInputFactories(std::vector<FactoryInputList> const&inputs){
  this->_inputs = inputs;
}

std::shared_ptr<Statement>MacroFunctionFactory::_do(std::shared_ptr<FunctionRegister>const&fr){
  auto res = (*this->_factory)(fr);
  auto mf = std::dynamic_pointer_cast<MacroFunction>(res);
  std::vector<MacroFunction::FceInputList> inputs;
  auto ff=std::dynamic_pointer_cast<Function>(res);
  return std::dynamic_pointer_cast<Statement>(std::make_shared<MacroFunction>(fr,fr->getType(fr->getFunctionId(this->_name)),std::dynamic_pointer_cast<Function>(res),inputs));
}

