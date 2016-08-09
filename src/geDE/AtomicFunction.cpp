#include<geDE/AtomicFunction.h>
#include<geDE/Resource.h>
#include<geDE/StdFunctions.h>

using namespace ge::de;

AtomicFunctionInput::AtomicFunctionInput(
    std::shared_ptr<Resource>const&r          ,
    Ticks                          updateTicks,
    bool                           changed    ){
  PRINT_CALL_STACK(r,updateTicks,changed);
  assert(this!=nullptr);
  this->updateTicks = updateTicks;
  this->changed     = changed;
  this->resource    = r;
}

AtomicFunctionInput::AtomicFunctionInput(
    std::shared_ptr<Function>const&f          ,
    Ticks                          updateTicks,
    bool                           changed    ){
  PRINT_CALL_STACK(f,updateTicks,changed);
  assert(this!=nullptr);
  this->updateTicks = updateTicks;
  this->changed     = changed;
  this->function    = f;
}


AtomicFunctionInput::~AtomicFunctionInput(){
  PRINT_CALL_STACK();
}

AtomicFunction::AtomicFunction(
    std::shared_ptr<FunctionRegister>const&fr,
    FunctionId                             id):Function(fr,id){
  PRINT_CALL_STACK(fr,id);
  assert(this!=nullptr);
  assert(fr!=nullptr);
  for(size_t i=0;i<fr->getNofInputs(id);++i)
    this->_inputs.push_back(std::make_shared<AtomicFunctionInput>());
}

AtomicFunction::AtomicFunction(
    std::shared_ptr<FunctionRegister>const&fr     ,
    TypeId                                 type   ,
    std::string                      const&name   ,
    std::shared_ptr<StatementFactory>const&factory):AtomicFunction(fr,fr->addFunction(type,name,factory)){
  PRINT_CALL_STACK(fr,type,name,factory);
}

AtomicFunction::~AtomicFunction(){
  PRINT_CALL_STACK();
}


void AtomicFunction::_unbindInput(size_t i){
  assert(this!=nullptr);
  assert(i<this->_inputs.size());
  auto in = this->_inputs.at(i);
  assert(in!=nullptr);
  if(in->resource == nullptr && in->function == nullptr)return;
  assert(!in->resource != !in->function);
  if(in->resource){
    in->resource->_removeSignalingTarget(this);
    this->_removeSourceResource(&*in->resource);
    in->resource = nullptr;
  }else{
    in->function->_removeSignalingTarget(this);
    this->_removeSignalingSource(&*in->function);
    in->function->getOutputData()->_removeSignalingTarget(this);
    this->_removeSourceResource(&*in->function->getOutputData());
    this->_fce2Indices.at(in->function).erase(i);
    if(this->_fce2Indices.at(in->function).empty()){
      this->_fce2Indices.erase(in->function);
      this->_fce2FceInput.erase(in->function);
    }
    in->function = nullptr;
  }
}

void AtomicFunction::_unbindOutput(){
  assert(this!=nullptr);
  if(this->_outputData==nullptr)return;
  this->_outputData->_removeSignalingSource(this);
  this->_removeTargetResource(&*this->_outputData);
  this->_outputData = nullptr;
}

bool AtomicFunction::bindInput(
    std::shared_ptr<FunctionRegister>const&fr,
    size_t                                 i ,
    std::shared_ptr<Function>        const&f ){
  PRINT_CALL_STACK(fr,i,f);
  assert(this!=nullptr);
  assert(i<this->_inputs.size());
  if(f==nullptr){
    this->_unbindInput(i);
    this->setDirty();
    return true;
  }
  if(f->getOutputData()==nullptr){
    ge::core::printError(GE_CORE_FCENAME,"input function does not have output",fr,i,f);
    return false;
  }
  if(!this->_inputBindingCheck(fr,i,f))
    return false;
  if(!this->_inputBindingCircularCheck(fr,f))
    return false;

  this->_unbindInput(i);

  f->_addSignalingTarget(this);
  this->_addSignalingSource(&*f);
  f->getOutputData()->_addSignalingTarget(this);
  this->_addSourceResource(&*f->getOutputData());
  auto ii = this->_fce2Indices.find(f);
  if(ii==this->_fce2Indices.end()){
    this->_fce2Indices[f]=std::set<size_t>();
    this->_fce2FceInput[f]=this->_inputs.at(i);
  }
  this->_fce2Indices.at(f).insert(i);
  this->_inputs.at(i)->updateTicks = f->getOutputData()->getTicks() - 1;
  this->_inputs.at(i)->function = f;
  this->_inputs.at(i)->changed  = true;
  this->setDirty();
  return true;
}

bool AtomicFunction::bindInputAsVariable (
    std::shared_ptr<FunctionRegister>const&fr,
    size_t                                 i ,
    std::shared_ptr<Resource>        const&r ){
  PRINT_CALL_STACK(fr,i,r);
  assert(this!=nullptr);
  assert(i<this->_inputs.size());
  if(r==nullptr){
    this->_unbindInput(i);
    this->setDirty();
    return true;
  }
  if(!this->_inputBindingCheck(fr,i,r))
    return false;

  this->_unbindInput(i);
  r->_addSignalingTarget(this);
  this->_addSourceResource(&*r);
  this->_inputs.at(i)->updateTicks = r->getTicks() - 1;
  this->_inputs.at(i)->resource = r;
  this->_inputs.at(i)->changed  = true;
  this->setDirty();
  return true;
}


bool AtomicFunction::bindOutput(
    std::shared_ptr<FunctionRegister>const&fr,
    std::shared_ptr<Resource>        const&r ){
  PRINT_CALL_STACK(fr,r);
  assert(this!=nullptr);
  if(r==nullptr){
    this->_unbindOutput();
    return true;
  }
  if(!this->_outputBindingCheck(fr,r))
    return false;
  if(!this->_outputBindingCircularCheck(fr,r))
    return false;

  this->_unbindOutput();

  r->_addSignalingSource(this);
  this->_addTargetResource(&*r);
  this->_outputData = r;
  this->setDirty();
  return true;
}

std::shared_ptr<Function>const&AtomicFunction::getInputFunction(size_t i)const{
  PRINT_CALL_STACK(i);
  assert(this!=nullptr);
  assert(i<this->_inputs.size());
  return this->_inputs.at(i)->function;
}

bool AtomicFunction::hasInputFunction(size_t i)const{
  PRINT_CALL_STACK(i);
  assert(this!=nullptr);
  assert(i<this->_inputs.size());
  return this->_inputs.at(i)->function!=nullptr;
}

void AtomicFunction::operator()(){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  if(!this->_dirtyFlag)return;
  bool isAnyInputChanged = this->_processInputs();
  if(!isAnyInputChanged){
    this->_dirtyFlag = false;
    return;
  }
  bool isOutputChanged = this->_do();
  this->_dirtyFlag = false;
  if(isOutputChanged){
    this->getOutputData()->updateTicks();
    this->_updateTicks++;
    this->setSignalingDirty();
  }
}

bool AtomicFunction::_processInputs(){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  bool isAnyInputChanged = false;
  for(auto const&x:this->_fce2FceInput){
    assert(x.second->function!=nullptr);
    (*x.second->function)();
  }
  for(auto const&x:this->_inputs){
    bool changed = false;
    if(x->resource){
      changed = x->updateTicks < x->resource->getTicks();
      x->changed = changed;
      x->updateTicks = x->resource->getTicks();
    }else{
      changed = x->updateTicks < x->function->getOutputData()->getTicks();
      x->changed = changed;
      x->updateTicks = x->function->getOutputData()->getTicks();
    }
    isAnyInputChanged |= changed;
  }
  return isAnyInputChanged;
}

bool AtomicFunction::_do(){
  PRINT_CALL_STACK();
  return true;
}
