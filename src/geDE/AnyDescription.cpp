#include<geDE/AnyDescription.h>
#include<cassert>

using namespace ge::de;

AnyDescription::AnyDescription():TypeDescription(TypeRegister::ANY){
  PRINT_CALL_STACK();
}

AnyDescription::~AnyDescription(){
  PRINT_CALL_STACK();
}

bool AnyDescription::init(
    TypeRegister               *           ,
    TypeDescriptionVector const&description,
    size_t                     &i          ,
    bool                                   ){
  PRINT_CALL_STACK(description,i);
  if(i>=description.size())return false;
  if(description[i]!=TypeRegister::ANY)return false;
  i++;
  return true;
}

bool AnyDescription::operator==(AnyDescription const&)const{
  PRINT_CALL_STACK();
  return true;
}

bool AnyDescription::equal(TypeDescription const*other)const{
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  assert(other!=nullptr);
  if(this->type != other->type)return false;
  return *this==*(AnyDescription*)other;
}

std::string AnyDescription::toStr(TypeRegister const*tr,TypeId id)const{
  PRINT_CALL_STACK(tr,id);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  assert(tr->_typeId2Synonyms.count(id)!=0);
  std::stringstream ss;
  ss<<"Any-";
  ss<<*tr->_typeId2Synonyms.find(id)->second.begin();
  return ss.str();
}

void AnyDescription::copy(void*,void*,TypeRegister const*,TypeId)const{
  assert(false&&"ERROR: Any cannot be copied!");
}

void AnyDescription::callConstructor(TypeRegister*,void*)const{
  assert(false&&"ERROR: Any is not constructible!");
}

void AnyDescription::callDestructor(TypeRegister*,void*)const{
  assert(false&&"ERROR: Any is not destructible!");
}

size_t AnyDescription::byteSize(TypeRegister const*)const{
  assert(false&&"ERROR: Any has no size!");
  return 0;
}

