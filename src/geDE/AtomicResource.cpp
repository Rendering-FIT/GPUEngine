#include<geDE/AtomicResource.h>

using namespace ge::de;

namespace ge{
  namespace de{
    class AtomicFunction;
  }
}

AtomicResource::AtomicResource(AtomicResource const& ac):Resource(ac._manager,ac._id){
  PRINT_CALL_STACK(ac);
  assert(this!=nullptr);
  this->_data   = ac._data  ;
  this->_offset = ac._offset;
}

AtomicResource::AtomicResource(
    std::shared_ptr<TypeRegister>const&manager,
    const void*                        data   ,
    TypeId                             id     ,
    size_t                             offset ):Resource(manager,id){
  PRINT_CALL_STACK(manager,data,id,offset);
  assert(this!=nullptr);
  this->_data = std::shared_ptr<uint8_t>((uint8_t*)data,[id,manager](uint8_t*ptr){
      PRINT_CALL_STACK(ptr);
      assert(manager!=nullptr);
      manager->destroy(ptr,id);});
  this->_offset  = offset ;
}

AtomicResource::AtomicResource(
    std::shared_ptr<TypeRegister>const&manager,
    std::shared_ptr<uint8_t>const&        data   ,
    TypeId                             id     ,
    size_t                             offset ):Resource(manager,id){
  PRINT_CALL_STACK(manager,data,id,offset);
  assert(this!=nullptr);
  this->_data    = data   ;
  this->_offset  = offset ;
}

AtomicResource::AtomicResource(
    std::shared_ptr<TypeRegister>const&manager,
    TypeId               id     ):Resource(manager,id){
  PRINT_CALL_STACK(manager,id);
  assert(this!=nullptr);
  this->_data    = nullptr;
  this->_offset  = 0      ;
}

AtomicResource::~AtomicResource(){
  PRINT_CALL_STACK();
}

void*AtomicResource::getData()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  assert(this->_data!=nullptr);
  return (uint8_t*)&(*this->_data)+this->_offset;
}

void const*AtomicResource::getDataAddress()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  return &this->_data;
}

std::shared_ptr<Resource> AtomicResource::operator[](size_t elem){
  PRINT_CALL_STACK(elem);
  assert(this!=nullptr);
  assert(this->getManager()!=nullptr);
  TypeId innerType = 0;
  size_t offset    = 0;
  switch(this->getManager()->getTypeIdType(this->_id)){
    case TypeRegister::ARRAY :
      innerType = this->getManager()->getArrayElementTypeId(this->getId());
      offset    = this->getManager()->computeTypeIdSize(innerType)*elem;
      return std::make_shared<AtomicResource>(this->getManager(),this->_data,innerType,offset);
    case TypeRegister::STRUCT:
      innerType = this->getManager()->getStructElementTypeId(this->getId(),elem);
      for(size_t i=0;i<elem;++i)
        offset += this->getManager()->computeTypeIdSize(this->getManager()->getStructElementTypeId(this->getId(),i));
      return std::make_shared<AtomicResource>(this->getManager(),this->_data,innerType,offset);
    default:
      return std::make_shared<AtomicResource>(this->getManager(),this->_data,this->getId());
  }
}

size_t AtomicResource::getNofElements()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  assert(this->getManager()!=nullptr);
  switch(this->getManager()->getTypeIdType(this->_id)){
    case TypeRegister::ARRAY :
      return this->getManager()->getArraySize(this->getId());
    case TypeRegister::STRUCT:
      return this->getManager()->getNofStructElements(this->getId());
    default                 :
      return 1;
  }
}

const void*AtomicResource::getPointer()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  return (void*)this->getData();
}

std::string AtomicResource::data2Str()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  assert(this->getManager()!=nullptr);
  return this->getManager()->data2Str(this->getData(),this->_id);
}


