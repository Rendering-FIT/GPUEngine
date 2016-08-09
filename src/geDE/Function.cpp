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
    std::shared_ptr<Function>        const&f )const{
  assert(this!=nullptr);
  if(f==nullptr)return true;
  assert(f->getOutputData()!=nullptr);
  return this->_inputBindingCheck(fr,i,f->getOutputData());
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
      std::string("input ")+fr->getName(this->_id)+"."+nr->getFceInputName(this->_id,i)+" has different type - INPUT: "+
      tr->getTypeIdName(toType)+" != RESOURCE: "+tr->getTypeIdName(fromType),
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
      "function: "+fr->getName(this->getId())+
      " of type: "+fr->getTypeRegister()->getTypeIdName(fr->getType(this->getId()))+
      ", output has different type - OUTPUT: "+
      tr->getTypeIdName(toType)+" != RESOURCE: "+tr->getTypeIdName(fromType),
      fr,data);
  return false;
}

void Function::setSignalingDirty(){
  this->Statement::setSignalingDirty();
  for(auto const&x:this->_targetResources)
    x->_setSignalingDirty();
}

bool Function::_recOutputBindingCircularCheck(
    std::shared_ptr<FunctionRegister>const&fr      ,
    std::set<Function const*>             &visited ,
    std::shared_ptr<Resource>        const&resource)const{
  assert(this!=nullptr);
  assert(fr!=nullptr);
  if(visited.count(this)!=0)return true;
  size_t n = fr->getNofInputs(this->getId());
  for(size_t i=0;i<n;++i){
    if(!this->hasInputFunction(i))continue;
    if(this->getInputFunction(i)->getOutputData()==resource)return false;
  }
  visited.insert(this);
  for(size_t i=0;i<n;++i){
    if(!this->hasInputFunction(i))continue;
    if(!this->getInputFunction(i)->_recOutputBindingCircularCheck(fr,visited,resource))
      return false;
  }
  return true;
}

bool Function::_inputBindingCircularCheck(
    std::shared_ptr<FunctionRegister>const&fr      ,
    std::shared_ptr<Function>        const&function)const{
  assert(this!=nullptr);
  assert(fr!=nullptr);
  if(function==nullptr)return true;
  assert(function->getOutputData()!=nullptr);
  auto o = this->getOutputData();
  if(o==nullptr)return true;
  if(o==function->getOutputData()){
    ge::core::printError(GE_CORE_FCENAME,"1 binding function as input would result in fast circular dependence, you should use bindInputAsVariable in some point",fr,function);
    return false;
  }
  if(!function->_outputBindingCircularCheck(fr,o)){
    ge::core::printError(GE_CORE_FCENAME,"2 binding function as input would result in fast circular dependence, you should use bindInputAsVariable in some point",fr,function);
    return false;
  }
  return true;
}

bool Function::_outputBindingCircularCheck(
    std::shared_ptr<FunctionRegister>const&fr      ,
    std::shared_ptr<Resource>        const&resource)const{
  assert(this!=nullptr);
  if(resource==nullptr)return true;
  auto visited = std::set<Function const*>();
  if(!this->_recOutputBindingCircularCheck(fr,visited,resource)){
    ge::core::printError(GE_CORE_FCENAME,"binding resource as output would result in fast cicular dependence, you should use bindInputAsVariable in some point",fr,resource);
    return false;
  }
  return true;
}


