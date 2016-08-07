#include<geDE/Function.h>
#include<geDE/Resource.h>
#include<geDE/FunctionRegister.h>
#include<geCore/ErrorPrinter.h>

using namespace ge::de;

Function::~Function(){
  for(auto const&x:this->_targetResources)
    x->_removeSignalingSource(this);
  for(auto const&x:this->_sourceResources)
    x->_removeSignalingTarget(this);
}

bool Function::_inputBindingCheck(
    std::shared_ptr<FunctionRegister>const&fr,
    size_t                                 i ,
    std::shared_ptr<Resource>        const&r )const{
  assert(this!=nullptr);
  assert(fr!=nullptr);
  assert(fr->getTypeRegister()!=nullptr);
  assert(fr->getNameRegister()!=nullptr);
  auto tr = fr->getTypeRegister();
  auto nr = fr->getNameRegister();

  if(i>=fr->getNofInputs(this->_id)){
    ge::core::printError(fr->getName(this->_id)+"::bindInput","out of range",i,r);
    return false;
  }

  if(r == nullptr)return true;

  auto toType = tr->getFceArgTypeId(fr->getType(this->_id),i);
  auto fromType = r->getId();
  if(tr->areConvertible(toType,fromType))return true;
  ge::core::printError(GE_CORE_FCENAME,
      std::string("in function of type: ")+tr->getTypeIdName(fr->getType(this->_id))+", "+
      std::string("input ")+fr->getName(this->_id)+"."+nr->getFceInputName(this->_id,i)+" has different type - "+
      tr->getTypeIdName(toType)+" != "+tr->getTypeIdName(fromType),
      fr,i,r);
  return false;
}

bool Function::_outputBindingCheck(
    std::shared_ptr<FunctionRegister>const&fr  ,
    std::shared_ptr<Resource>        const&data)const{
  assert(this!=nullptr);
  assert(fr!=nullptr);
  assert(fr->getTypeRegister()!=nullptr);
  auto tr = fr->getTypeRegister();
  if(data == nullptr)return true;
  auto toType = tr->getFceReturnTypeId(fr->getType(this->_id));
  auto fromType = data->getId();
  if(tr->areConvertible(toType,fromType))return true;
  ge::core::printError(GE_CORE_FCENAME,
      "output has different type - "+
      tr->getTypeIdName(toType)+" != "+tr->getTypeIdName(fromType),
      fr,data);
  return false;
}

void Function::setSignalingDirty(){
  this->Statement::setSignalingDirty();
  for(auto const&x:this->_targetResources)
    x->_setSignalingDirty();
}

std::shared_ptr<Function>const&Function::getInputFunction(size_t i)const{
  assert(this!=nullptr);
  assert(this->getInputData(i)!=nullptr);
  return this->getInputData(i)->_producer;
}
