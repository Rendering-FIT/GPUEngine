#include<geDE/AtomicDescription.h>
#include<cassert>

using namespace ge::de;

AtomicDescription::AtomicDescription(
    size_t const&size       ,
    CDPtr  const&constructor,
    CDPtr  const&destructor ):TypeDescription(TypeRegister::ATOMIC){
  PRINT_CALL_STACK(size,destructor,constructor);
  assert(this!=nullptr);
  this->size = size;
  this->constructor = constructor;
  this->destructor  = destructor;
}

AtomicDescription::~AtomicDescription(){
  PRINT_CALL_STACK();
}

bool AtomicDescription::init(
    TypeRegister*           ,
    TypeDescriptionVector const&,
    size_t                 &,
    bool                    ){
  PRINT_CALL_STACK();
  return true;
}

bool AtomicDescription::operator==(AtomicDescription const&other)const{
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  return this->size == other.size &&
    this->destructor == other.destructor &&
    this->constructor == other.constructor;
}

bool AtomicDescription::equal(TypeDescription const*other)const{
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  if(this->type != other->type)return false;
  return *this==*(AtomicDescription*)other;
}

std::string AtomicDescription::toStr(TypeRegister const*tr,TypeId id)const{
  PRINT_CALL_STACK(tr,id);
  assert(this!=nullptr);
  assert(tr->_typeId2Synonyms.count(id)!=0);
  std::stringstream ss;
  ss<<*tr->_typeId2Synonyms.find(id)->second.begin();
  return ss.str();
}

void AtomicDescription::copy(void*o,void*i,TypeRegister const*tr,TypeId id)const{
  PRINT_CALL_STACK(o,i,tr,id);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  if(this->copyData)this->copyData(o,i);
  else std::memcpy(o,i,tr->computeTypeIdSize(id));
}

void AtomicDescription::callConstructor(TypeRegister*,void*ptr)const{
  PRINT_CALL_STACK(ptr);
  assert(this!=nullptr);
  if(this->constructor)this->constructor(ptr);
}

void AtomicDescription::callDestructor(TypeRegister*,void*ptr)const{
  PRINT_CALL_STACK(ptr);
  assert(this!=nullptr);
  if(this->destructor)this->destructor(ptr);
}

size_t AtomicDescription::byteSize(TypeRegister const*)const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  return this->size;
}
