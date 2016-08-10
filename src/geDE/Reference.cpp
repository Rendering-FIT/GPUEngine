#include<geDE/Reference.h>
#include<geDE/Resource.h>
#include<cstring>

using namespace ge::de;

Reference::Reference(
    std::shared_ptr<FunctionRegister>const&fr      ,
    TypeId                                 id      ,
    bool                                   ignore   ):AtomicFunction(fr,fr->getFunctionId(
        keyword<Reference>()+"<"+fr->getTypeRegister()->getTypeIdName(id)+">"),ignore   ){
      PRINT_CALL_STACK(fr,id);
}

bool Reference::_do(){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  assert(this->getOutputData()!=nullptr);
  assert(this->getInputData(0)!=nullptr);
  assert(this->getOutputData()->getData()!=nullptr);
  assert(this->getInputData(0)->getDataAddress()!=nullptr);
  std::memcpy(this->getOutputData()->getData(),this->getInputData(0)->getDataAddress(),sizeof(void*));
  return true;
}
