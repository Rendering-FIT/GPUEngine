#include<geDE/Function.h>
#include<geDE/Resource.h>
#include<geDE/FunctionRegister.h>
#include<geCore/ErrorPrinter.h>

using namespace ge::de;

bool Function::_inputBindingCheck(
    std::shared_ptr<FunctionRegister>const&fr      ,
    size_t                                 i       ,
    std::shared_ptr<Function>        const&function)const{
  assert(this!=nullptr);
  assert(fr!=nullptr);
  assert(fr->getTypeRegister()!=nullptr);
  assert(fr->getNameRegister()!=nullptr);
  auto tr = fr->getTypeRegister();
  auto nr = fr->getNameRegister();

  if(i>=fr->getNofInputs(this->_id)){
    ge::core::printError(fr->getName(this->_id)+"::bindInput","out of range",i,
        function?fr->getName(function->_id):"nullptr");
    return false;
  }

  if(function!=nullptr)
    assert(function->getOutputData() != nullptr);

  if(function == nullptr)return true;

  assert(function->getOutputData()!=nullptr);

  auto toType = tr->getFceArgTypeId(fr->getType(this->_id),i);
  auto fromType = function->getOutputData()->getId();
  if(tr->areConvertible(toType,fromType))return true;
  ge::core::printError(GE_CORE_FCENAME,
      std::string("input ")+fr->getName(this->_id)+"."+nr->getFceInputName(this->_id,i)+" has different type - "+
      tr->getTypeIdName(toType)+" != "+tr->getTypeIdName(fromType),
      fr,i,function);
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

