#include<geDE/AtomicFunction.h>
#include<geDE/Resource.h>
#include<geDE/StdFunctions.h>

using namespace ge::de;

AtomicFunctionInput::AtomicFunctionInput(
    std::shared_ptr<Function>const&fce        ,
    Function::Ticks                updateTicks,
    bool                           changed    ){
  assert(this!=nullptr);
  this->updateTicks = updateTicks;
  this->changed     = changed;
  this->function    = fce;
}

AtomicFunctionInput::~AtomicFunctionInput(){
}

AtomicFunction::AtomicFunction(
    std::shared_ptr<FunctionRegister>const&fr,
    FunctionRegister::FunctionID id):Function(fr,id){
  assert(this!=nullptr);
  auto nofInputs = fr->getNofInputs(id);
  for(decltype(nofInputs)i=0;i<nofInputs;++i)
    this->_inputs.push_back(std::make_shared<AtomicFunctionInput>());
}

AtomicFunction::AtomicFunction(
    std::shared_ptr<FunctionRegister>const&fr,
    TypeRegister::DescriptionVector const&typeDescription,
    std::string name,
    std::shared_ptr<StatementFactory>const&factory):AtomicFunction(fr,fr->addFunction(fr->getTypeRegister()->addCompositeType("",typeDescription),name,factory)){
}

AtomicFunction::AtomicFunction(std::shared_ptr<FunctionRegister>const&fr,FunctionRegister::FunctionID id,std::shared_ptr<Resource>const&output):AtomicFunction(fr,id){
  assert(this!=nullptr);
  this->bindOutput(fr,output);
}


AtomicFunction::~AtomicFunction(){
  for(auto const&x:this->_forSignaling)
    x->_removeSignaling(this);
}

bool AtomicFunction::bindInput(
    std::shared_ptr<FunctionRegister>const&fr      ,
    InputIndex                             i       ,
    std::shared_ptr<Function>        const&function){
  assert(this!=nullptr);
  if(!this->_inputBindingCheck(fr,i,function))
    return false;
  assert(i<this->_inputs.size());
  auto oldFunction = this->_inputs.at(i)->function;
  if(oldFunction == function)return true;
  if(oldFunction){
    std::dynamic_pointer_cast<Statement>(oldFunction)->_removeSignaling(this);
    this->_fce2Indices.at(oldFunction).erase(i);
    if(this->_fce2Indices.at(oldFunction).empty()){
      this->_fce2Indices.erase(oldFunction);
      this->_fce2FceInput.erase(oldFunction);
    }
  }
  if(function){
    std::dynamic_pointer_cast<Statement>(function)->_addSignaling(this);
    auto ii = this->_fce2Indices.find(function);
    if(ii==this->_fce2Indices.end()){
      this->_fce2Indices[function]=std::set<InputIndex>();
      this->_fce2FceInput[function]=this->_inputs.at(i);
    }
    this->_fce2Indices.at(function).insert(i);
    this->_inputs.at(i)->updateTicks = function->getUpdateTicks() - 1;
  }
  this->_inputs.at(i)->function = function;
  this->_inputs.at(i)->changed  = true;
  this->setDirty();
  return true;
}

bool AtomicFunction::bindOutput(
    std::shared_ptr<FunctionRegister>const&fr  ,
    std::shared_ptr<Resource>        const&data){
  assert(this!=nullptr);
  if(!this->_outputBindingCheck(fr,data))
    return false;
  this->_outputData = data;
  this->setDirty();
  return true;
}

bool AtomicFunction::bindOutput(
    std::shared_ptr<FunctionRegister>const&fr     ,
    std::shared_ptr<Nullary>         const&nullary){
  assert(this!=nullptr);
  if(!this->_outputBindingCheck(fr,nullary->getOutputData()))
    return false;
  if(this->_outputSignaling)this->_removeSignaling(this->_outputSignaling);
  this->_outputData = nullary->getOutputData();
  this->_outputSignaling = &*nullary;
  this->_addSignaling(this->_outputSignaling);
  return true;
}


void AtomicFunction::operator()(){
  assert(this!=nullptr);
  if(!this->_dirtyFlag)return;
  this->_dirtyFlag = false;
  bool anyInputChanged = this->_processInputs();
  if(!anyInputChanged)
    return;
  if(this->_do()){
    this->_updateTicks++;
    this->setSignalingDirty();
  }
  //this->_dirtyFlag = false;
}

bool AtomicFunction::_processInputs(){
  assert(this!=nullptr);
  bool anyInputChanged = false;
  for(auto const&x:this->_fce2FceInput){
    auto input = x.second;
    (*input->function)();
    bool changed = input->updateTicks < input->function->getUpdateTicks();
    input->changed = changed;
    input->updateTicks = input->function->getUpdateTicks();
    anyInputChanged |= changed;
  }
  return anyInputChanged;
}

bool AtomicFunction::_do(){
  return true;
}
