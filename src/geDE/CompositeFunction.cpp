#include<geDE/CompositeFunction.h>
#include<geDE/FunctionNodeFactory.h>
#include<algorithm>

using namespace ge::de;

CompositeFunction::CompositeFunction(
    std::shared_ptr<FunctionRegister>const&fr,
    FunctionId id,
    std::shared_ptr<Function>const&output,
    std::vector<FceInputList>const&inputs):Function(fr,id){
  PRINT_CALL_STACK(fr,id,output,inputs);
  assert(this!=nullptr);
  this->_outputMapping = output;
  this->_inputMapping  = inputs;
}

CompositeFunction::~CompositeFunction(){
  PRINT_CALL_STACK();
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


bool CompositeFunction::bindInput(
    std::shared_ptr<FunctionRegister>const&fr,
    InputIndex                             i ,
    std::shared_ptr<Resource>        const&r ){
  PRINT_CALL_STACK(fr,i,r);
  assert(this!=nullptr);
  if(!this->_inputBindingCheck(fr,i,r))
    return false;
  for(auto const&x:this->_inputMapping[i]){
    assert(std::get<FUNCTION>(x)!=nullptr);
    std::get<FUNCTION>(x)->bindInput(fr,std::get<INPUT>(x),r);
  }
  this->setDirty();
  return true;
}


bool CompositeFunction::bindOutput(
    std::shared_ptr<FunctionRegister>const&fr,
    std::shared_ptr<Resource>        const&r ){
  PRINT_CALL_STACK(fr,r);
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  //this->setDirty();
  return this->_outputMapping->bindOutput(fr,r);
}

bool CompositeFunction::bindOutputAsVariable(
    std::shared_ptr<FunctionRegister>const&fr,
    std::shared_ptr<Resource>        const&r ){
  PRINT_CALL_STACK(fr,r);
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->bindOutputAsVariable(fr,r);
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


