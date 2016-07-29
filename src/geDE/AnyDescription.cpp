#include<geDE/AnyDescription.h>
#include<cassert>

using namespace ge::de;

AnyDescription::AnyDescription():TypeDescription(TypeRegister::ANY){
}

AnyDescription::~AnyDescription(){}

bool AnyDescription::init(
    TypeRegister               *           ,
    TypeDescriptionVector const&description,
    size_t                     &i          ,
    bool                                   ){
  if(i>=description.size())return false;
  if(description[i]!=TypeRegister::ANY)return false;
  i++;
  return true;
}

bool AnyDescription::operator==(AnyDescription const&)const{
  return true;
}

bool AnyDescription::equal(TypeDescription const*other)const{
  assert(this!=nullptr);
  if(this->type != other->type)return false;
  return *this==*(AnyDescription*)other;
}

std::string AnyDescription::toStr(TypeRegister const*tr,TypeId id)const{
  assert(this!=nullptr);
  assert(tr->_typeId2Synonyms.count(id)!=0);
  std::stringstream ss;
  ss<<*tr->_typeId2Synonyms.find(id)->second.begin();
  return ss.str();
}

void AnyDescription::callConstructor(TypeRegister*,void*)const{
}

void AnyDescription::callDestructor(TypeRegister*,void*)const{
}

size_t AnyDescription::byteSize(TypeRegister const*)const{
  PRINT_CALL_STACK("AtomicDescription::byteSize");
  return 0;
}

