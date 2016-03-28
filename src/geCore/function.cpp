#include<geCore/function.h>
#include<geCore/Accessor.h>

using namespace ge::core;



AtomicFunctionInput::AtomicFunctionInput(
    std::shared_ptr<Function>const&fce        ,
    Function::Ticks                updateTicks,
    bool                           changed    ){
  this->function    = fce        ;
  this->updateTicks = updateTicks;
  this->changed     = changed    ;
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

AtomicFunction::~AtomicFunction(){
  //std::cerr<<"AtomicFunction::~AtomicFunction() - "<<this->_name<<" "<<this<<std::endl;
}

bool AtomicFunction::bindInput(InputIndex i,std::shared_ptr<Function>function){
  if(i>=this->_getNofInputs()){
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
  //std::cerr<<this->_name<<".bindInput("<<i<<","<<function<<")"<<std::endl;
  this->_getInput(i).function = function;
  if(function)this->_getInput(i).updateTicks = function->getUpdateTicks() - 1;
  this->_getInput(i).changed  = true;
  return true;
}

bool AtomicFunction::bindOutput(std::shared_ptr<Accessor>data){
  if(
      data                    != nullptr                                                  &&
      this->getOutputType()   != TypeRegister::getTypeTypeId<TypeRegister::Unregistered>()&&
      data->getId()           != this->getOutputType()                                    ){
    std::cerr<<"ERROR: "<<this->getName()<<".output has different type - ";
    std::cerr<<data->getManager()->getTypeIdName(this->getOutputType());
    std::cerr<<" != ";
    std::cerr<<data->getManager()->getTypeIdName(data->getId()    );
    std::cerr<<std::endl;
    return false;
  }
  this->_outputData = data;
  return true;
}

bool AtomicFunction::bindInput(std::string name,std::shared_ptr<Function>function){
  return this->bindInput(this->getInputIndex(name),function);
}

void AtomicFunction::operator()(){
  this->_checkTicks++;
  this->_processInputs();
  if(this->_do())
    this->_updateTicks++;
}

void AtomicFunction::_processInputs(){
  for(InputIndex i=0;i<this->_getNofInputs();++i){
    if(!this->hasInput(i)||this->_getInput(i).function->getCheckTicks()>=this->_checkTicks){
      this->_getInput(i).changed = false;
      continue;
    }
    (*this->_getInput(i).function)();
    this->_getInput(i).function->setCheckTicks(this->_checkTicks);
    this->_getInput(i).changed=
      this->_getInput(i).updateTicks<this->_getInput(i).function->getUpdateTicks();
    if(this->_getInput(i).changed)
      this->_getInput(i).updateTicks=this->_getInput(i).function->getUpdateTicks();
  }
}

bool AtomicFunction::_do(){
  return true;
}

FunctionFactory::~FunctionFactory(){}
