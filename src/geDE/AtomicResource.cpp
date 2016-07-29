#include<geDE/AtomicResource.h>

using namespace ge::de;

namespace ge{
  namespace de{
    class AtomicFunction;
  }
}

AtomicResource::AtomicResource(AtomicResource const& ac):Resource(ac._manager,ac._id){
  //std::cerr<<"AtomicResource::AtomicResource() - "<<this<<std::endl;
  this->_data   = ac._data  ;
  this->_offset = ac._offset;
}

AtomicResource::AtomicResource(
    std::shared_ptr<TypeRegister>const&manager,
    const void*                        data   ,
    TypeId                             id     ,
    size_t                             offset ):Resource(manager,id){
  //std::cerr<<"AtomicResource::AtomicResource() - "<<this<<std::endl;
  this->_data    = std::shared_ptr<char>((char*)data,[id,manager](char*ptr){manager->destroy(ptr,id);});
  this->_offset  = offset ;
}

AtomicResource::AtomicResource(
    std::shared_ptr<TypeRegister>const&manager,
    std::shared_ptr<char>const&        data   ,
    TypeId                             id     ,
    size_t                             offset ):Resource(manager,id){
  //std::cerr<<"AtomicResource::AtomicResource() - "<<this<<std::endl;
  this->_data    = data   ;
  this->_offset  = offset ;
}

AtomicResource::AtomicResource(
    std::shared_ptr<TypeRegister>const&manager,
    TypeId               id     ):Resource(manager,id){
  //std::cerr<<"AtomicResource::AtomicResource() - "<<this<<std::endl;
  this->_data    = nullptr;
  this->_offset  = 0      ;
}

AtomicResource::~AtomicResource(){
  //std::cerr<<"AtomicResource::~AtomicResource() - "<<this<<std::endl;
}

void*AtomicResource::getData()const{
  assert(this!=nullptr);
  return (char*)&(*this->_data)+this->_offset;
}

void const*AtomicResource::getDataAddress()const{
  assert(this!=nullptr);
  return &this->_data;
}

std::shared_ptr<Resource> AtomicResource::operator[](size_t elem){
  assert(this!=nullptr);
  TypeId innerType = 0;
  size_t               offset    = 0;
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
  assert(this!=nullptr);
  switch(this->_manager->getTypeIdType(this->_id)){
    case TypeRegister::ARRAY :
      return this->getManager()->getArraySize(this->getId());
    case TypeRegister::STRUCT:
      return this->getManager()->getNofStructElements(this->getId());
    default                 :
      return 1;
  }
}

const void*AtomicResource::getPointer()const{
  assert(this!=nullptr);
  return (void*)this->getData();
}

std::string AtomicResource::data2Str()const{
  assert(this!=nullptr);
  return this->_manager->data2Str(this->getData(),this->_id);
}


