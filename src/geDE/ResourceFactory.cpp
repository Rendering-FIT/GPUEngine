#include<geDE/ResourceFactory.h>
#include<geDE/FunctionRegister.h>
#include<geDE/TypeRegister.h>

using namespace ge::de;

std::shared_ptr<Resource>ResourceFactory::operator()(
    std::shared_ptr<FunctionRegister>const&fr){
  PRINT_CALL_STACK(fr);
  assert(this!=nullptr);
  assert(fr!=nullptr);
  this->_first=this->_uses==0;
  if(!this->_result)
    this->_result = fr->getTypeRegister()->sharedResource(this->_type);
  auto res=this->_result;
  this->_uses++;
  if(this->_uses==this->_maxUses){
    this->_uses   = 0      ;
    this->_result = nullptr;
  }
  return res;
}


