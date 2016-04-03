#include<geCore/function.h>
#include<geCore/Accessor.h>

using namespace ge::core;


FunctionFactory::FunctionFactory(std::string name,unsigned maxUses):StatementFactory(name,maxUses){
}

bool Function::_inputBindingCheck(InputIndex i,std::shared_ptr<Function>function)const{
  if(i>=this->getNofInputs()){
    std::cerr<<"ERROR: "<<this->getName()<<"::bindInput("<<i<<",";
    if(function==nullptr)std::cerr<<"nullptr";
    else std::cerr<<function->getName();
    std::cerr<<") - out of range"<<std::endl;
    return false;
  }
  if(
      function                           != nullptr                                                  &&
      this->getInputType(i)              != TypeRegister::getTypeTypeId<TypeRegister::Unregistered>()&&
      function->getOutputData()->getId() != this->getInputType(i)                                    ){
    std::cerr<<"ERROR: "<<this->getName()<<".input["<<this->getInputName(i)<<"] has different type - ";
    std::cerr<<function->getOutputData()->getManager()->getTypeIdName(this->getInputType(i));
    std::cerr<<" != ";
    std::cerr<<function->getOutputData()->getManager()->getTypeIdName(function->getOutputData()->getId());
    std::cerr<<std::endl;
    return false;
  }
  return true;
}

AtomicFunctionInput::AtomicFunctionInput(
    std::shared_ptr<Function>const&fce        ,
    Function::Ticks                updateTicks,
    bool                           changed    ):FunctionInput(updateTicks,changed){
  this->function = fce;
}

AtomicFunctionInput::~AtomicFunctionInput(){
}

AtomicFunction::AtomicFunction(
    std::shared_ptr<FunctionRegister>const&fr,
    FunctionRegister::FunctionID id):Function(fr,id){
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

AtomicFunction::AtomicFunction(std::shared_ptr<FunctionRegister>const&fr,FunctionRegister::FunctionID id,std::shared_ptr<Accessor>const&output):AtomicFunction(fr,id){
  this->bindOutput(output);
}


AtomicFunction::~AtomicFunction(){
  //std::cerr<<"AtomicFunction::~AtomicFunction() - "<<this->_name<<" "<<this<<std::endl;
}

bool AtomicFunction::bindInput(InputIndex i,std::shared_ptr<Function>function){
  if(!this->_inputBindingCheck(i,function))
    return false;
  //std::cerr<<this->_name<<".bindInput("<<i<<","<<function<<")"<<std::endl;
  this->_inputs[i].function = function;
  if(function)this->_inputs[i].updateTicks = function->getUpdateTicks() - 1;
  this->_inputs[i].changed  = true;
  return true;
}

bool AtomicFunction::bindOutput(std::shared_ptr<Accessor>data){
  if(
      data                    != nullptr                                                  &&
      this->getOutputType()   != TypeRegister::getTypeTypeId<TypeRegister::Unregistered>()&&
      data->getId()           != this->getOutputType()                                    ){
    std::cerr<<"ERROR: "<<this->getName()<<".output has different type - ";
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
  this->_checkTicks++;
  this->_processInputs();
  if(this->_do())
    this->_updateTicks++;
}

void AtomicFunction::_processInputs(){
  for(InputIndex i=0;i<this->getNofInputs();++i){
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

FunctionFactory::~FunctionFactory(){}
