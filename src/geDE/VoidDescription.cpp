#include<geDE/VoidDescription.h>
#include<cassert>

using namespace ge::de;

VoidDescription::VoidDescription():TypeDescription(TypeRegister::VOID){
  PRINT_CALL_STACK();
}

VoidDescription::~VoidDescription(){
  PRINT_CALL_STACK();
}

bool VoidDescription::init(
    TypeRegister               *           ,
    TypeDescriptionVector const&description,
    size_t                     &i          ,
    bool                                   ){
  PRINT_CALL_STACK(description,i);
  if(i>=description.size())return false;
  if(description[i]!=TypeRegister::VOID)return false;
  i++;
  return true;
}

bool VoidDescription::operator==(VoidDescription const&)const{
  PRINT_CALL_STACK();
  return true;
}

bool VoidDescription::equal(TypeDescription const*other)const{
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  assert(other!=nullptr);
  if(this->type != other->type)return false;
  return *this==*(VoidDescription*)other;
}

std::string VoidDescription::toStr(TypeRegister const*tr,TypeId id)const{
  PRINT_CALL_STACK(tr,id);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  assert(tr->_typeId2Synonyms.count(id)!=0);
  std::stringstream ss;
  ss<<"Void-";
  ss<<*tr->_typeId2Synonyms.find(id)->second.begin();
  return ss.str();
}

void VoidDescription::copy(void*,void*,TypeRegister const*,TypeId)const{
  assert(false&&"ERROR: void cannot be copied!");
}

void VoidDescription::callConstructor(TypeRegister*,void*)const{
  assert(false&&"ERROR: void is not constructible!");
}

void VoidDescription::callDestructor(TypeRegister*,void*)const{
  assert(false&&"ERROR: void is not destructible!");
}

size_t VoidDescription::byteSize(TypeRegister const*)const{
  assert(false&&"ERROR: void has no size!");
  return 0;
}

