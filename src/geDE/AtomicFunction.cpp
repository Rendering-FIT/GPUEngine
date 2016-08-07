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

bool AtomicFunction::bindInput(
    std::shared_ptr<FunctionRegister>const&fr,
    size_t                                 i ,
    std::shared_ptr<Resource>        const&r ){
  PRINT_CALL_STACK(fr,i,r);
  assert(this!=nullptr);
  if(!this->_inputBindingCheck(fr,i,r))
    return false;
  if(!this->_inputBindingCircularCheck(fr,r))
    return false;
  assert(i<this->_inputs.size());
  auto oldResource = this->_inputs.at(i)->resource;
  if(oldResource == r)return true;
  if(oldResource){
    oldResource->_removeSignalingTarget(this);
    this->_removeSourceResource(&*oldResource);
    this->_res2Indices.at(oldResource).erase(i);
    if(this->_res2Indices.at(oldResource).empty()){
      this->_res2Indices.erase(oldResource);
      this->_res2FceInput.erase(oldResource);
    }
  }
  if(r){
    r->_addSignalingTarget(this);
    this->_addSourceResource(&*r);
    auto ii = this->_res2Indices.find(r);
    if(ii==this->_res2Indices.end()){
      this->_res2Indices[r]=std::set<size_t>();
      this->_res2FceInput[r]=this->_inputs.at(i);
    }
    this->_res2Indices.at(r).insert(i);
    this->_inputs.at(i)->updateTicks = r->_ticks - 1;
  }
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
  if(!this->_outputBindingCheck(fr,r))
    return false;
  if(!this->_outputBindingCircularCheck(fr,r))
    return false;
  if(this->_outputData == r){
    if(r==nullptr)return true;
    if(r->_producer)
      if(&*r->_producer == this)return true;
    r->setProducer(std::dynamic_pointer_cast<Function>(this->shared_from_this()));
    return true;
  }
  if(this->_outputData){
    this->_outputData->_removeSignalingSource(this);
    this->_removeTargetResource(&*this->_outputData);
    r->setProducer(nullptr);
  }
  if(r){
    this->_addTargetResource(&*r);
    r->_addSignalingSource(this);
    auto st = this->shared_from_this();
    auto cst = std::dynamic_pointer_cast<Function>(st);
    r->setProducer(cst);//std::dynamic_pointer_cast<Function>(this->shared_from_this()));
    //r->setProducer(std::dynamic_pointer_cast<Function>(this->shared_from_this()));
  }
  this->_outputData = r;
  this->setDirty();
  return true;
}

bool AtomicFunction::bindOutputAsVariable(
    std::shared_ptr<FunctionRegister>const&fr,
    std::shared_ptr<Resource>        const&r ){
  PRINT_CALL_STACK(fr,r);
  assert(this!=nullptr);
  if(!this->_outputBindingCheck(fr,r))
    return false;
  if(this->_outputData == r){
    if(r->_producer)
      if(&*r->_producer == this)r->_producer = nullptr;
    return true;
  }
  if(this->_outputData){
    this->_outputData->_removeSignalingSource(this);
    this->_removeTargetResource(&*this->_outputData);
    r->setProducer(nullptr);
  }
  if(r){
    this->_addTargetResource(&*r);
    r->_addSignalingSource(this);
  }
  this->_outputData = r;
  this->setDirty();
  return true;
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
  for(auto const&x:this->_res2FceInput){
    auto input = x.second;
    (*input->resource)();
    bool changed = input->updateTicks < input->resource->_ticks;
    input->changed = changed;
    input->updateTicks = input->resource->_ticks;
    isAnyInputChanged |= changed;
  }
  return isAnyInputChanged;
}

bool AtomicFunction::_do(){
  PRINT_CALL_STACK();
  return true;
}
