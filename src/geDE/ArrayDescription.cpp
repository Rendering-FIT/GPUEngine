#include<geDE/ArrayDescription.h>
#include<cassert>
#include<geCore/ErrorPrinter.h>

using namespace ge::de;

ArrayDescription::ArrayDescription(
    TypeId const&elementType,
    size_t const&size       ):TypeDescription(TypeRegister::ARRAY){
  PRINT_CALL_STACK(elementType,size);
  assert(this!=nullptr);
  this->elementType = elementType;
  this->size = size;
}

ArrayDescription::ArrayDescription():TypeDescription(TypeRegister::ARRAY){
  PRINT_CALL_STACK();
}

ArrayDescription::~ArrayDescription(){
  PRINT_CALL_STACK();
}

bool ArrayDescription::init(
    TypeRegister*               tr         ,
    TypeDescriptionVector const&description,
    size_t                     &i          ,
    bool                        exists     ){
  PRINT_CALL_STACK(tr,description,i,exists);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  size_t old = i;
  if(i>=description.size()){
    if(!exists)ge::core::printError(GE_CORE_FCENAME,"Array description is empty",tr,description,i,exists);
    i=old;
    return false;
  }
  if(description[i++]!=TypeRegister::ARRAY){
    if(!exists)ge::core::printError(GE_CORE_FCENAME,"Array description does not start with ARRAY",tr,description,i,exists);
    i=old;
    return false;
  }
  if(i>=description.size()){
    if(!exists)ge::core::printError(GE_CORE_FCENAME,"Array description does not contain size",tr,description,i,exists);
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
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  return this->size == other.size && this->elementType == other.elementType;
}

bool ArrayDescription::equal(TypeDescription const*other)const{
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  assert(other!=nullptr);
  if(this->type != other->type)return false;
  return *this==*(ArrayDescription*)other;
}

std::string ArrayDescription::toStr(TypeRegister const*tr,TypeId)const{
  PRINT_CALL_STACK(tr);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  std::stringstream ss;
  ss<<"Array-{";
  ss<<tr->type2Str(tr->_typeId2VectorIndex(this->elementType));
  ss<<"}[";
  ss<<this->size;
  ss<<"]";
  return ss.str();
}

void ArrayDescription::callConstructor(TypeRegister*tr,void*ptr)const{
  PRINT_CALL_STACK(tr,ptr);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  size_t elementSize = tr->computeTypeIdSize(this->elementType);
  for(size_t i=0;i<this->size;++i)
    tr->_callConstructors((uint8_t*)ptr+elementSize*i,this->elementType);
}

void ArrayDescription::callDestructor(TypeRegister*tr,void*ptr)const{
  PRINT_CALL_STACK(tr,ptr);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  size_t elementSize = tr->computeTypeIdSize(this->elementType);
  for(size_t i=0;i<this->size;++i)
    tr->_callDestructors((uint8_t*)ptr+elementSize*i,this->elementType);
}

size_t ArrayDescription::byteSize(TypeRegister const*tr)const{
  PRINT_CALL_STACK(tr);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  return this->size*tr->computeTypeIdSize(this->elementType);
}

std::string ArrayDescription::data2Str(TypeRegister const*tr,void*ptr){
  PRINT_CALL_STACK(tr,ptr);
  assert(this!=nullptr);
  assert(tr!=nullptr);
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

