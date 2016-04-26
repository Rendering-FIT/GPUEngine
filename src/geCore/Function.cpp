#include<geCore/Function.h>
#include<geCore/Resource.h>

using namespace ge::core;


bool Function::_inputBindingCheck(InputIndex i,std::shared_ptr<Function>function)const{
  assert(this!=nullptr);
  auto fr = this->_functionRegister;
  auto tr = this->_functionRegister->getTypeRegister();
  auto nr = this->_functionRegister->getNameRegister();

  if(i>=fr->getNofInputs(this->_id)){
    std::cerr<<"ERROR: "<<fr->getName(this->_id)<<"::bindInput("<<i<<",";
    if(function==nullptr)std::cerr<<"nullptr";
    else std::cerr<<fr->getName(function->_id);
    std::cerr<<") - out of range"<<std::endl;
    return false;
  }

  if(function!=nullptr)
    assert(function->getOutputData() != nullptr);

  if(
      function                                      != nullptr                                                  &&
      tr->getFceArgTypeId(fr->getType(this->_id),i) != TypeRegister::getTypeTypeId<TypeRegister::Unregistered>()&&
      tr->getFceArgTypeId(fr->getType(this->_id),i) != function->getOutputData()->getId()                       ){
    std::cerr<<"ERROR: "<<fr->getName(this->_id)<<".input["<<nr->getFceInputName(this->_id,i)<<"] has different type - ";
    std::cerr<<tr->getTypeIdName(tr->getFceArgTypeId(fr->getType(this->_id        ),i));
    std::cerr<<" != ";
    std::cerr<<tr->getTypeIdName(tr->getFceArgTypeId(fr->getType(function->getId()),i));
    std::cerr<<std::endl;
    return false;
  }
  return true;
}

bool Function::_outputBindingCheck(std::shared_ptr<Resource>data)const{
  assert(this!=nullptr);
  auto fr = this->_functionRegister;
  auto tr = this->_functionRegister->getTypeRegister();
  if(
      data                    != nullptr                                                  &&
      this->getOutputType()   != TypeRegister::getTypeTypeId<TypeRegister::Unregistered>()&&
      data->getId()           != tr->getFceReturnTypeId(fr->getType(this->_id))){
    std::cerr<<"ERROR: "<<fr->getName(this->_id)<<".output has different type - ";
    std::cerr<<tr->getTypeIdName(fr->getType(this->_id));
    std::cerr<<" != ";
    std::cerr<<tr->getTypeIdName(data->getId());
    std::cerr<<std::endl;
    return false;
  }
  return true;
}

