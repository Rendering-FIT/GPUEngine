#include<geCore/function.h>
#include<geCore/Accessor.h>

using namespace ge::core;


bool Function::_inputBindingCheck(InputIndex i,std::shared_ptr<Function>function)const{
  assert(this!=nullptr);
  if(i>=this->getNofInputs()){
    std::cerr<<"ERROR: "<<this->_functionRegister->getName(this->_id)<<"::bindInput("<<i<<",";
    if(function==nullptr)std::cerr<<"nullptr";
    else std::cerr<<function->_functionRegister->getName(function->_id);
    std::cerr<<") - out of range"<<std::endl;
    return false;
  }

  if(function!=nullptr)
    assert(function->getOutputData() != nullptr);

  if(
      function                           != nullptr                                                  &&
      this->getInputType(i)              != TypeRegister::getTypeTypeId<TypeRegister::Unregistered>()&&
      function->getOutputData()->getId() != this->getInputType(i)                                    ){
    std::cerr<<"ERROR: "<<this->_functionRegister->getName(this->_id)<<".input["<<this->_functionRegister->getNamer()->getFceInputName(this->_id,i)<<"] has different type - ";
    std::cerr<<function->getOutputData()->getManager()->getTypeIdName(this->getInputType(i));
    std::cerr<<" != ";
    std::cerr<<function->getOutputData()->getManager()->getTypeIdName(function->getOutputData()->getId());
    std::cerr<<std::endl;
    return false;
  }
  return true;
}



