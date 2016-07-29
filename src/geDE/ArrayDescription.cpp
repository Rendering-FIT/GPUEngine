#include<geDE/ArrayDescription.h>
#include<cassert>

using namespace ge::de;

ArrayDescription::ArrayDescription(
    TypeId const&elementType,
    size_t const&size       ):TypeDescription(TypeRegister::ARRAY){
  assert(this!=nullptr);
  this->elementType = elementType;
  this->size = size;
}

ArrayDescription::ArrayDescription():TypeDescription(TypeRegister::ARRAY){}

ArrayDescription::~ArrayDescription(){}

bool ArrayDescription::init(
    TypeRegister*           tr         ,
    TypeDescriptionVector const&description,
    size_t                 &i          ,
    bool                    exists     ){
  assert(this!=nullptr);
  size_t old = i;
  if(i>=description.size()){
    if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Array description is empty"<<std::endl;
    i=old;
    return false;
  }
  if(description[i++]!=TypeRegister::ARRAY){
    if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Array description does not start with ARRAY"<<std::endl;
    i=old;
    return false;
  }
  if(i>=description.size()){
    if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Array description does not contain size"<<std::endl;
    i=old;
    return false;
  }
  this->size = description[i++];
  if(exists)
    this->elementType = tr->_typeExists(description,i);
  else
    this->elementType = tr->_addType("",description,i);
  if(elementType == TypeRegister::UNREGISTERED){i=old;return TypeRegister::UNREGISTERED;}
  return true;
}

bool ArrayDescription::operator==(ArrayDescription const&other)const{
  assert(this!=nullptr);
  return this->size == other.size && this->elementType == other.elementType;
}

bool ArrayDescription::equal(TypeDescription const*other)const{
  assert(this!=nullptr);
  if(this->type != other->type)return false;
  return *this==*(ArrayDescription*)other;
}

std::string ArrayDescription::toStr(TypeRegister const*tr,TypeId)const{
  assert(this!=nullptr);
  std::stringstream ss;
  ss<<"["<<this->size<<","<<tr->type2Str(tr->_typeId2VectorIndex(this->elementType))<<"]";
  return ss.str();
}

void ArrayDescription::callConstructor(TypeRegister*tr,void*ptr)const{
  PRINT_CALL_STACK("ArrayDescription::callConstructor",tr,ptr);
  assert(this!=nullptr);
  size_t elementSize = tr->computeTypeIdSize(this->elementType);
  for(size_t i=0;i<this->size;++i)
    tr->_callConstructors((uint8_t*)ptr+elementSize*i,this->elementType);
}

void ArrayDescription::callDestructor(TypeRegister*tr,void*ptr)const{
  PRINT_CALL_STACK("ArrayDescription::callDestructor",tr,ptr);
  assert(this!=nullptr);
  size_t elementSize = tr->computeTypeIdSize(this->elementType);
  for(size_t i=0;i<this->size;++i)
    tr->_callDestructors((uint8_t*)ptr+elementSize*i,this->elementType);
}

size_t ArrayDescription::byteSize(TypeRegister const*tr)const{
  PRINT_CALL_STACK("ArrayDescription::byteSize",tr);
  assert(this!=nullptr);
  return this->size*tr->computeTypeIdSize(this->elementType);
}

std::string ArrayDescription::data2Str(TypeRegister const*tr,void*ptr){
  PRINT_CALL_STACK("ArrayDescription::data2Str",ptr);
  assert(this!=nullptr);
  if(this->data2StrPtr)this->TypeDescription::data2Str(tr,ptr);
  size_t elementSize = tr->computeTypeIdSize(this->elementType);
  std::stringstream ss;
  ss<<"[";
  for(size_t i=0;i<this->size;++i){
    if(i>0)ss<<",";
    ss<<tr->data2Str((uint8_t*)ptr+elementSize*i,this->elementType);
  }
  ss<<"]";
  return ss.str();
}

