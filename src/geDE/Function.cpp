#include<geDE/Function.h>
#include<geDE/Resource.h>

using namespace ge::de;


bool Function::_inputBindingCheck(
    std::shared_ptr<FunctionRegister>const&fr      ,
    InputIndex                             i       ,
    std::shared_ptr<Function>        const&function)const{
  assert(this!=nullptr);
  auto tr = fr->getTypeRegister();
  auto nr = fr->getNameRegister();

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
      function                                      != nullptr                   &&
      tr->getFceArgTypeId(fr->getType(this->_id),i) != TypeRegister::UNREGISTERED&&
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

bool Function::_outputBindingCheck(
    std::shared_ptr<FunctionRegister>const&fr  ,
    std::shared_ptr<Resource>        const&data)const{
  assert(this!=nullptr);
  auto tr = fr->getTypeRegister();
  if(
      data                                           != nullptr                   &&
      tr->getFceReturnTypeId(fr->getType(this->_id)) != TypeRegister::UNREGISTERED&&
      data->getId()                                  != tr->getFceReturnTypeId(fr->getType(this->_id))){
    std::cerr<<"ERROR: "<<fr->getName(this->_id)<<".output has different type - ";
    std::cerr<<tr->getTypeIdName(fr->getType(this->_id));
    std::cerr<<" != ";
    std::cerr<<tr->getTypeIdName(data->getId());
    std::cerr<<std::endl;
    return false;
  }
  return true;
}

void Function::setDirty(){
  if(!this->_dirtyFlag)this->_setOutputDirty();
  this->_dirtyFlag = true;
}

bool Function::isDirty()const{
  return this->_dirtyFlag;
}

void Function::_setOutputDirty(){
  for(auto const&x:this->_outputFunctions){
    if(std::get<0>(x)->_dirtyFlag)continue;
    std::get<0>(x)->_dirtyFlag = true;
    std::get<0>(x)->_setOutputDirty();
  }
}

void Function::_addOutputFunction(Function*fce,InputIndex index){
  this->_outputFunctions.insert(Function::OutputFunction(fce,index));
}

void Function::_removeOutputFunction(Function*fce,InputIndex index){
  this->_outputFunctions.erase(Function::OutputFunction(fce,index));
}

