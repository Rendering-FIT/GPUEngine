#include<geDE/PtrDescription.h>
#include<geCore/ErrorPrinter.h>
#include<cassert>

using namespace ge::de;

PtrDescription::PtrDescription(TypeId id):TypeDescription(TypeRegister::PTR){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  this->innerType = id;
}

PtrDescription::PtrDescription():TypeDescription(TypeRegister::PTR){
  PRINT_CALL_STACK();
}

PtrDescription::~PtrDescription(){
  PRINT_CALL_STACK();
}

bool PtrDescription::init(
    TypeRegister*               tr         ,
    TypeDescriptionVector const&description,
    size_t                     &i          ,
    bool                        exists     ){
  PRINT_CALL_STACK(tr,description,i,exits);
  assert(this!=nullptr);
  size_t old = i;
  if(i>=description.size()){
    if(!exists)ge::core::printError(GE_CORE_FCENAME,"Ptr description is empty",tr,description,i,exists);
    i=old;
    return false;
  }
  if(description[i++]!=TypeRegister::PTR){
    if(!exists)ge::core::printError(GE_CORE_FCENAME,"Ptr description does not start with PTR",tr,description,i,exists);
    i=old;
    return false;
  }
  if(i>=description.size()){
    if(!exists)ge::core::printError(GE_CORE_FCENAME,"Ptr description does not contain innter type",tr,description,i,exists);
    i=old;
    return false;
  }
  if(exists)this->innerType = tr->_typeExists(description,i);
  else this->innerType = tr->_addType("",description,i);
  if(this->innerType == TypeRegister::UNREGISTERED){i=old;return false;}
  return true;
}

bool PtrDescription::operator==(PtrDescription const&other)const{
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  return this->innerType == other.innerType;
}

bool PtrDescription::equal(TypeDescription const*other)const{
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  if(this->type != other->type)return false;
  return *this==*(PtrDescription*)other;
}

std::string PtrDescription::toStr(TypeRegister const*tr,TypeId)const{
  PRINT_CALL_STACK(tr);
  assert(this!=nullptr);
  std::stringstream ss;
  ss<<tr->type2Str(tr->_typeId2VectorIndex(this->innerType));
  ss<<"*";
  return ss.str();
}

void PtrDescription::callConstructor(TypeRegister*,void*ptr)const{
  PRINT_CALL_STACK(ptr);
  (void)ptr;
  PRINT_CALL_STACK("PtrDescription::callConstructor",ptr);
  if(this->constructor)this->constructor(ptr);
}

void PtrDescription::callDestructor(TypeRegister*,void*ptr)const{
  (void)ptr;
  PRINT_CALL_STACK("PtrDescription::callDestructor",ptr);
  if(this->destructor)this->destructor(ptr);
}

size_t PtrDescription::byteSize(TypeRegister const*)const{
  PRINT_CALL_STACK("PtrDescription::byteSize");
  assert(this!=nullptr);
  return sizeof(void*);
}

