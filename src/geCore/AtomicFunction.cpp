#include<geCore/AtomicFunction.h>
#include<geCore/Resource.h>

using namespace ge::core;

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
  auto nofInputs = this->getNofInputs();
  for(decltype(nofInputs)i=0;i<nofInputs;++i)
    this->_inputs.push_back(AtomicFunctionInput());
}

AtomicFunction::AtomicFunction(
    std::shared_ptr<FunctionRegister>const&fr,
    TypeRegister::DescriptionList const&typeDescription,
    std::string name,
    std::shared_ptr<StatementFactory>const&factory):AtomicFunction(fr,fr->addFunction(fr->getTypeRegister()->addType("",typeDescription),name,factory)){
}

AtomicFunction::AtomicFunction(std::shared_ptr<FunctionRegister>const&fr,FunctionRegister::FunctionID id,std::shared_ptr<Resource>const&output):AtomicFunction(fr,id){
  assert(this!=nullptr);
  this->bindOutput(output);
}


AtomicFunction::~AtomicFunction(){
  //std::cerr<<"AtomicFunction::~AtomicFunction() - "<<this->_name<<" "<<this<<std::endl;
}

bool AtomicFunction::bindInput(InputIndex i,std::shared_ptr<Function>const&function){
  assert(this!=nullptr);
  if(!this->_inputBindingCheck(i,function))
    return false;
  //std::cerr<<this->_name<<".bindInput("<<i<<","<<function<<")"<<std::endl;
  this->_inputs[i].function = function;
  if(function)this->_inputs[i].updateTicks = function->getUpdateTicks() - 1;
  this->_inputs[i].changed  = true;
  return true;
}

bool AtomicFunction::bindOutput(std::shared_ptr<Resource>const&data){
  assert(this!=nullptr);
  if(
      data                    != nullptr                                                  &&
      this->getOutputType()   != TypeRegister::getTypeTypeId<TypeRegister::Unregistered>()&&
      data->getId()           != this->getOutputType()                                    ){
    std::cerr<<"ERROR: "<<this->_functionRegister->getName(this->_id)<<".output has different type - ";
    std::cerr<<this->getOutputType();
    std::cerr<<" != ";
    std::cerr<<data->getManager()->getTypeIdName(data->getId()    );
    std::cerr<<std::endl;
    return false;
  }
  this->_outputData = data;
  return true;
}

void AtomicFunction::operator()(){
  assert(this!=nullptr);
  this->_checkTicks++;
  this->_processInputs();
  if(this->_do())
    this->_updateTicks++;
}

void AtomicFunction::_processInputs(){
  assert(this!=nullptr);
  assert(this->_inputs.size()==this->getNofInputs());
  for(InputIndex i=0;i<this->getNofInputs();++i){
    assert(this->_inputs[i].function!=nullptr);
    if(!this->hasInput(i)||this->_inputs[i].function->getCheckTicks()>=this->_checkTicks){
      this->_inputs[i].changed = false;
      continue;
    }
    (*this->_inputs[i].function)();
    this->_inputs[i].function->setCheckTicks(this->_checkTicks);
    this->_inputs[i].changed=
      this->_inputs[i].updateTicks<this->_inputs[i].function->getUpdateTicks();
    if(this->_inputs[i].changed)
      this->_inputs[i].updateTicks=this->_inputs[i].function->getUpdateTicks();
  }
}

bool AtomicFunction::_do(){
  return true;
}
