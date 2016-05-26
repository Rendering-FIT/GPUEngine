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
    TypeRegister::TypeId               id     ,
    size_t                             offset ):Resource(manager,id){
  //std::cerr<<"AtomicResource::AtomicResource() - "<<this<<std::endl;
  this->_data    = std::shared_ptr<char>((char*)data,[id,manager](char*ptr){manager->destroy(ptr,id);});
  this->_offset  =        offset ;
}

AtomicResource::AtomicResource(
    std::shared_ptr<TypeRegister>const&manager,
    std::shared_ptr<char>const&        data   ,
    TypeRegister::TypeId               id     ,
    size_t                             offset ):Resource(manager,id){
  //std::cerr<<"AtomicResource::AtomicResource() - "<<this<<std::endl;
  this->_data    = data   ;
  this->_offset  = offset ;
}

AtomicResource::AtomicResource(
    std::shared_ptr<TypeRegister>const&manager,
    TypeRegister::TypeId               id     ):Resource(manager,id){
  //std::cerr<<"AtomicResource::AtomicResource() - "<<this<<std::endl;
  this->_data    = nullptr;
  this->_offset  = 0      ;
}

AtomicResource::~AtomicResource(){
  //std::cerr<<"AtomicResource::~AtomicResource() - "<<this<<std::endl;
}

void*AtomicResource::getData()const{
  return (char*)&(*this->_data)+this->_offset;
}

void const*AtomicResource::getDataAddress()const{
  return &this->_data;
}

std::shared_ptr<Resource> AtomicResource::operator[](size_t elem){
  TypeRegister::TypeId innerType = 0;
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

TypeRegister::DescriptionElement AtomicResource::getNofElements()const{
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
  return (void*)this->getData();
}

std::string AtomicResource::data2Str()const{
  return "";//TODO
  /*
  TypeRegister::Type type=this->_manager->getTypeIdType(this->_id);
  std::stringstream ss;
  bool first;
  switch(type){
    case TypeRegister::VOID  :
      break;
    case TypeRegister::BOOL  :
      ss<<((bool)(*this)?"true":"false");
      break;
    case TypeRegister::I8    :
      ss<<(int)(char)(*this);
      break;
    case TypeRegister::I16   :
      ss<<(short)(*this);
      break;
    case TypeRegister::I32   :
      ss<<(int)(*this);
      break;
    case TypeRegister::I64   :
      ss<<(long long int)(*this);
      break;
    case TypeRegister::U8    :
      ss<<(unsigned)(unsigned char)(*this);
      break;
    case TypeRegister::U16   :
      ss<<(unsigned short)(*this);
      break;
    case TypeRegister::U32   :
      ss<<(unsigned)(*this);
      break;
    case TypeRegister::U64   :
      ss<<(unsigned long long)(*this);
      break;
    case TypeRegister::F32   :
      ss<<(float)(*this);
      break;
    case TypeRegister::F64   :
      ss<<(double)(*this);
      break;
    case TypeRegister::PTR   :
      ss<<(void*)(*this);
      break;
    case TypeRegister::STRING:
      ss<<(std::string&)(*this);
      break;
    case TypeRegister::ARRAY:
      ss<<"[";
      first=true;
      for(TypeRegister::DescriptionElement i=0;i<this->_manager->getArraySize(this->_id);++i){
        if(first)first=false;
        else ss<<",";
        ss<<((*(AtomicResource*)this)[i])->data2Str();
      }
      ss<<"]";
      break;
    case TypeRegister::STRUCT:
      ss<<"{";
      first=true;
      for(TypeRegister::DescriptionElement e=0;e<this->_manager->getNofStructElements(this->_id);++e){
        if(first)first=false;
        else ss<<",";
        ss<<((*(AtomicResource*)this)[e])->data2Str();
      }
      ss<<"}";
      break;
    case TypeRegister::FCE:
      break;
    case TypeRegister::OBJ:
      break;
    default:
      break;
  }
  return ss.str();
  */
}


