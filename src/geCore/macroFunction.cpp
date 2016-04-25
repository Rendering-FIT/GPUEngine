#include<geCore/macroFunction.h>
#include<geCore/FunctionNodeFactory.h>
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

bool MacroFunction::bindInput(InputIndex i,std::shared_ptr<Function>const&function){
  assert(this!=nullptr);
  if(!this->_inputBindingCheck(i,function))
    return false;
  for(auto x:this->_inputMapping[i]){
    assert(std::get<FUNCTION>(x)!=nullptr);
    std::get<FUNCTION>(x)->bindInput(std::get<INPUT>(x),function);
  }
  return true;
}


bool MacroFunction::bindOutput(std::shared_ptr<Accessor>const&data){
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



