#include<geDE/CompositeFunction.h>
#include<geDE/FunctionNodeFactory.h>
#include<algorithm>

using namespace ge::de;

CompositeFunction::CompositeFunction(
    std::shared_ptr<FunctionRegister>const&fr,
    FunctionRegister::FunctionID id,
    std::shared_ptr<Function>const&output,
    std::vector<FceInputList>const&inputs):Function(fr,id){
  this->_outputMapping = output;
  this->_inputMapping  = inputs;
}

CompositeFunction::~CompositeFunction(){
}

bool CompositeFunction::bindInput(
    std::shared_ptr<FunctionRegister>const&fr      ,
    InputIndex                             i       ,
    std::shared_ptr<Function>        const&function){
  assert(this!=nullptr);
  if(!this->_inputBindingCheck(fr,i,function))
    return false;
  for(auto x:this->_inputMapping[i]){
    assert(std::get<FUNCTION>(x)!=nullptr);
    std::get<FUNCTION>(x)->bindInput(fr,std::get<INPUT>(x),function);
  }
  return true;
}


bool CompositeFunction::bindOutput(
    std::shared_ptr<FunctionRegister>const&fr  ,
    std::shared_ptr<Resource>        const&data){
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->bindOutput(fr,data);
}

bool CompositeFunction::bindOutput(
    std::shared_ptr<FunctionRegister>const&fr     ,
    std::shared_ptr<Nullary>         const&nullary){
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->bindOutput(fr,nullary);
}

bool CompositeFunction::hasInput(InputIndex i)const{
  assert(this!=nullptr);
  for(auto x:this->_inputMapping[i]){
    assert(std::get<FUNCTION>(x)!=nullptr);
    if(!std::get<FUNCTION>(x)->hasInput(std::get<INPUT>(x)))return false;
  }
  return true;
}

bool CompositeFunction::hasOutput()const{
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->hasOutput();
}

std::shared_ptr<Resource>const&CompositeFunction::getInputData(InputIndex i)const{
  assert(this!=nullptr);
  assert(i<this->_inputMapping.size());
  assert(this->_inputMapping[i].size()>0);
  FceInput const&mapping = this->_inputMapping[i][0];
  assert(std::get<FUNCTION>(mapping)!=nullptr);
  return std::get<FUNCTION>(mapping)->getInputData(std::get<INPUT>(mapping));
}

std::shared_ptr<Resource>const&CompositeFunction::getOutputData()const{
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->getOutputData();
}

Function::Ticks CompositeFunction::getUpdateTicks()const{
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  return this->_outputMapping->getUpdateTicks();
}

void  CompositeFunction::setUpdateTicks(Ticks ticks){
  assert(this!=nullptr);
  assert(this->_outputMapping!=nullptr);
  this->_outputMapping->setUpdateTicks(ticks);
}

std::shared_ptr<Function>const&CompositeFunction::getInputFunction(InputIndex i)const{
  assert(this!=nullptr);
  assert(i<this->_inputMapping.size());
  assert(this->_inputMapping[i].size()>0);
  FceInput const&mapping = this->_inputMapping[i][0];
  assert(std::get<FUNCTION>(mapping)!=nullptr);
  return std::get<FUNCTION>(mapping)->getInputFunction(std::get<INPUT>(mapping));
}



