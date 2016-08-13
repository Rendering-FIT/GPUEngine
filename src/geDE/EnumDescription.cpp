#include<geDE/EnumDescription.h>
#include<cassert>
#include<geCore/ErrorPrinter.h>

using namespace ge::de;

EnumDescription::EnumDescription(
    std::vector<EnumElementType>const&elements):TypeDescription(TypeRegister::ENUM){
  PRINT_CALL_STACK(elements);
  assert(this!=nullptr);
  this->elements = elements;
}

EnumDescription::EnumDescription():TypeDescription(TypeRegister::ENUM){
  PRINT_CALL_STACK();
}

EnumDescription::~EnumDescription(){
  PRINT_CALL_STACK();
}

bool EnumDescription::init(
    TypeRegister*               tr         ,
    TypeDescriptionVector const&description,
    size_t                     &i          ,
    bool                        exists     ){
  PRINT_CALL_STACK(tr,description,i,exists);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  size_t old = i;

  if(i>=description.size()){
    if(!exists)ge::core::printError(GE_CORE_FCENAME,"Enum description is empty",tr,description,i,exists);
    i=old;
    return false;
  }

  if(description[i++]!=TypeRegister::ENUM){
    if(!exists)ge::core::printError(GE_CORE_FCENAME,"Enum description does not start with FCE",tr,description,i,exists);
    i=old;
    return false;
  }

  if(i>=description.size()){i=old;return false;}
  size_t size = description[i++];

  if(i+size>description.size()){i=old;return false;}
  i+=size;
  return true;
}


bool EnumDescription::operator==(EnumDescription const&other)const{
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  return this->elements == other.elements;
}

bool EnumDescription::equal(TypeDescription const*other)const{
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  assert(other!=nullptr);
  if(this->type != other->type)return false;
  return *this==*(EnumDescription*)other;
}

std::string EnumDescription::toStr(TypeRegister const*,TypeId)const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  std::stringstream ss;
  ss<<"Enum-{"<<ge::core::value2str(this->elements)<<"}";
  return ss.str();
}

void EnumDescription::callConstructor(TypeRegister*,void*ptr)const{
  PRINT_CALL_STACK();
  assert(this->elements.size()>0);
  *(EnumElementType*)ptr=this->elements.at(0);
}

void EnumDescription::callDestructor(TypeRegister*,void*)const{
  PRINT_CALL_STACK();
}

size_t EnumDescription::byteSize(TypeRegister const*)const{
  PRINT_CALL_STACK();
  return sizeof(EnumElementType);
}


