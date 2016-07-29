#include<geDE/StructDescription.h>
#include<cassert>

using namespace ge::de;

StructDescription::StructDescription(
    std::vector<TypeId>const&elementTypes):TypeDescription(TypeRegister::STRUCT){
  this->elementTypes = elementTypes;
}

StructDescription::StructDescription():TypeDescription(TypeRegister::STRUCT){}

bool StructDescription::init(
    TypeRegister*           tr         ,
    TypeDescriptionVector const&description,
    size_t                 &i          ,
    bool                    exists     ){
  assert(this!=nullptr);
  size_t old = i;
  if(i>=description.size()){
    if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Struct description is empty"<<std::endl;
    i=old;
    return false;
  }
  if(description[i++]!=TypeRegister::STRUCT){
    if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Struct description does not start with STRUCT"<<std::endl;
    i=old;
    return false;
  }
  if(i>=description.size()){
    if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Struct description does not contain size"<<std::endl;
    i=old;
    return false;
  }
  size_t size = description[i++];
  for(size_t e=0;e<size;++e){
    if(exists)
      this->elementTypes.push_back(tr->_typeExists(description,i));
    else
      this->elementTypes.push_back(tr->_addType("",description,i));
    if(this->elementTypes.back() == TypeRegister::UNREGISTERED){i=old;return false;}
  }
  return true;
}

StructDescription::~StructDescription(){}

bool StructDescription::operator==(StructDescription const&other)const{
  assert(this!=nullptr);
  return this->elementTypes == other.elementTypes;
}

bool StructDescription::equal(TypeDescription const*other)const{
  assert(this!=nullptr);
  if(this->type != other->type)return false;
  return *this==*(StructDescription*)other;
}

std::string StructDescription::toStr(TypeRegister const*tr,TypeId)const{
  assert(this!=nullptr);
  std::stringstream ss;
  ss<<"struct{";
  bool first=true;
  for(auto const&x:this->elementTypes){
    if(first)first = false;
    else ss<<",";
    ss<<tr->type2Str(tr->_typeId2VectorIndex(x));
  }
  ss<<"}";
  return ss.str();
}

void StructDescription::callConstructor(TypeRegister*tr,void*ptr)const{
  PRINT_CALL_STACK("StructDescription::callConstructor",tr,ptr);
  assert(this!=nullptr);
  size_t offset = 0;
  for(auto const&x:this->elementTypes){
    tr->_callConstructors((uint8_t*)ptr+offset,x);
    offset += tr->computeTypeIdSize(x);
  }
}

void StructDescription::callDestructor(TypeRegister*tr,void*ptr)const{
  PRINT_CALL_STACK("StructDescription::callDestructor",tr,ptr);
  assert(this!=nullptr);
  size_t offset = 0;
  for(auto const&x:this->elementTypes){
    tr->_callDestructors((uint8_t*)ptr+offset,x);
    offset += tr->computeTypeIdSize(x);
  }
}

size_t StructDescription::byteSize(TypeRegister const*tr)const{
  PRINT_CALL_STACK("StructDescription::byteSize",tr);
  assert(this!=nullptr);
  size_t size = 0;
  for(auto const&x:this->elementTypes)
    size+=tr->computeTypeIdSize(x);
  return size;
}

std::string StructDescription::data2Str(TypeRegister const*tr,void*ptr){
  PRINT_CALL_STACK("StructDescription::data2Str",ptr);
  assert(this!=nullptr);
  if(this->data2StrPtr)this->TypeDescription::data2Str(tr,ptr);
  size_t offset = 0;
  std::stringstream ss;
  ss<<"{";
  bool first = true;
  for(auto const&x:this->elementTypes){
    if(first)first = false;
    else ss<<",";
    ss<<tr->data2Str((uint8_t*)ptr+offset,x);
    offset += tr->computeTypeIdSize(x);
  }
  ss<<"}";
  return ss.str();
}

