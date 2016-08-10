#include<geDE/CompositeFunction.h>
#include<geDE/FunctionNodeFactory.h>
#include<algorithm>

using namespace ge::de;

CompositeFunction::CompositeFunction(
    std::shared_ptr<FunctionRegister>const&fr,
    FunctionId id,
    std::shared_ptr<Function>const&output,
    std::vector<FceInputList>const&inputs,
    bool immediate):Function(fr,id,immediate){
  PRINT_CALL_STACK(fr,id,output,inputs);
  assert(this!=nullptr);
  this->_outputMapping = output;
  this->_inputMapping  = inputs;
}

CompositeFunction::~CompositeFunction(){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  for(size_t i=0;i<this->_inputMapping.size();++i)
    this->unbindInput(i);
  this->unbindOutput();
}

bool CompositeFunction::bindInput (
    std::shared_ptr<FunctionRegister>const&fr,
    size_t                                 i ,
    std::shared_ptr<Function>        const&f ){
  PRINT_CALL_STACK(fr,i,f);
  assert(this!=nullptr);
  assert(i<this->_inputMapping.size());

  for(auto const&x:this->_inputMapping.at(i)){
    if(!std::get<FUNCTION>(x)->_inputBindingCheck(fr,std::get<INPUT>(x),f))
      return false;
    if(!std::get<FUNCTION>(x)->_inputBindingCircularCheck(fr,f))
      return false;
  }

  for(auto const&x:this->_inputMapping.at(i)){
    assert(std::get<FUNCTION>(x)!=nullptr);
    auto status = std::get<FUNCTION>(x)->bindInput(fr,std::get<INPUT>(x),f);
    assert(status==true);
    (void)status;
  }
  this->setDirty();
  return true;
}

bool CompositeFunction::bindInputAsVariable(
    std::shared_ptr<FunctionRegister>const&fr,
    size_t                                 i ,
    std::shared_ptr<Resource>        const&r ){
  PRINT_CALL_STACK(fr,i,r);
  assert(this!=nullptr);
  assert(i<this->_inputMapping.size());
  for(auto const&x:this->_inputMapping.at(i)){
    if(!std::get<FUNCTION>(x)->_inputBindingCheck(fr,std::get<INPUT>(x),r))
      return false;
  }
  for(auto const&x:this->_inputMapping.at(i)){
    assert(std::get<FUNCTION>(x)!=nullptr);
    auto status = std::get<FUNCTION>(x)->bindInputAsVariable(fr,std::get<INPUT>(x),r);
    assert(status==true);
    (void)status;
  }
  this->setDirty();
  return true;
}

bool CompositeFunction::bindOutput(
    std::shared_ptr<FunctionRegister>const&fr  ,
    std::shared_ptr<Resource>        const&data){
  PRINT_CALL_STACK(fr,data);
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->bindOutput(fr,data);
}

void CompositeFunction::unbindInput(size_t i){
  PRINT_CALL_STACK(fr,i,f);
  assert(this!=nullptr);
  assert(i<this->_inputMapping.size());

  for(auto const&x:this->_inputMapping.at(i)){
    assert(std::get<FUNCTION>(x)!=nullptr);
    std::get<FUNCTION>(x)->unbindInput(std::get<INPUT>(x));
  }
}

void CompositeFunction::unbindOutput(){
  PRINT_CALL_STACK(fr,data);
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->unbindOutput();
}

bool CompositeFunction::hasInput(InputIndex i)const{
  PRINT_CALL_STACK(i);
  assert(this!=nullptr);
  for(auto const&x:this->_inputMapping[i]){
    assert(std::get<FUNCTION>(x)!=nullptr);
    if(!std::get<FUNCTION>(x)->hasInput(std::get<INPUT>(x)))return false;
  }
  return true;
}

bool CompositeFunction::hasOutput()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->hasOutput();
}

std::shared_ptr<Resource>const&CompositeFunction::getInputData(InputIndex i)const{
  PRINT_CALL_STACK(i);
  assert(this!=nullptr);
  assert(i<this->_inputMapping.size());
  assert(this->_inputMapping[i].size()>0);
  FceInput const&mapping = this->_inputMapping.at(i).at(0);
  assert(std::get<FUNCTION>(mapping)!=nullptr);
  return std::get<FUNCTION>(mapping)->getInputData(std::get<INPUT>(mapping));
}

std::shared_ptr<Resource>const&CompositeFunction::getOutputData()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->getOutputData();
}

std::shared_ptr<Function>const&CompositeFunction::getInputFunction(size_t i)const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  assert(i<this->_inputMapping.size());
  assert(this->_inputMapping.at(i).size()>0);
  FceInput const&mapping = this->_inputMapping.at(i).at(0);
  assert(std::get<FUNCTION>(mapping)!=nullptr);
  return std::get<FUNCTION>(mapping)->getInputFunction(std::get<INPUT>(mapping));
}

void CompositeFunction::_addSignalingTarget(Statement*statement){
  PRINT_CALL_STACK(statement);
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  this->_outputMapping->_addSignalingTarget(statement);
}

void CompositeFunction::_removeSignalingTarget(Statement*statement){
  PRINT_CALL_STACK(statement);
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  this->_outputMapping->_removeSignalingTarget(statement);
}

void CompositeFunction::_addTargetResource(Resource*resource){
  PRINT_CALL_STACK(resource);
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  this->_outputMapping->_addTargetResource(resource);
}

void CompositeFunction::_removeTargetResource(Resource*resource){
  PRINT_CALL_STACK(resource);
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  this->_outputMapping->_removeTargetResource(resource);
}

bool CompositeFunction::isImmediate()const{
  PRINT_CALL_STACK(resource);
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->isImmediate();
}

void CompositeFunction::setImmediate(bool immediate){
  PRINT_CALL_STACK(resource);
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  this->_outputMapping->setImmediate(immediate);
}

