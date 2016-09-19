#include<geDE/MemFceDescription.h>
#include<cassert>
#include<geCore/ErrorPrinter.h>

using namespace ge::de;

MemFceDescription::MemFceDescription(
    TypeId             const&returnType   ,
    TypeId             const&classType    ,
    std::vector<TypeId>const&argumentTypes):TypeDescription(TypeRegister::MEMFCE){
  PRINT_CALL_STACK(returnType,classType,argumentTypes);
  assert(this!=nullptr);
  this->returnType = returnType;
  this->classType  = classType;
  this->argumentTypes = argumentTypes;
}

MemFceDescription::MemFceDescription():TypeDescription(TypeRegister::MEMFCE){
  PRINT_CALL_STACK();
}

MemFceDescription::~MemFceDescription(){
  PRINT_CALL_STACK();
}

bool MemFceDescription::init(
    TypeRegister*               tr         ,
    TypeDescriptionVector const&description,
    size_t                     &i          ,
    bool                        exists     ){
  PRINT_CALL_STACK(tr,description,i,exists);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  size_t old = i;

  if(i>=description.size()){
    if(!exists)ge::core::printError(GE_CORE_FCENAME,"Member Function description is empty",tr,description,i,exists);
    i=old;
    return false;
  }

  if(description[i++]!=TypeRegister::MEMFCE){
    if(!exists)ge::core::printError(GE_CORE_FCENAME,"Member Function description does not start with FCE",tr,description,i,exists);
    i=old;
    return false;
  }

  if(exists)
    this->returnType = tr->_typeExists(description,i);
  else
    this->returnType = tr->_addType("",description,i);
  if(this->returnType == TypeRegister::UNREGISTERED){
    i=old;
    return false;
  }

  if(exists)
    this->classType = tr->_typeExists(description,i);
  else
    this->classType = tr->_addType("",description,i);
  if(this->classType == TypeRegister::UNREGISTERED){
    i=old;
    return false;
  }

  if(i>=description.size()){i=old;return false;}
  size_t size = description[i++];
  for(size_t e=0;e<size;++e){
    if(exists)
      this->argumentTypes.push_back(tr->_typeExists(description,i));
    else
      this->argumentTypes.push_back(tr->_addType("",description,i));
    if(this->argumentTypes.back() == TypeRegister::UNREGISTERED){i=old;return false;}
  }
  return true;
}


bool MemFceDescription::operator==(MemFceDescription const&other)const{
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  return 
    this->returnType == other.returnType && 
    this->classType == other.classType &&
    this->argumentTypes == other.argumentTypes;
}

bool MemFceDescription::equal(TypeDescription const*other)const{
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  assert(other!=nullptr);
  if(this->type != other->type)return false;
  return *this==*(MemFceDescription*)other;
}

std::string MemFceDescription::toStr(TypeRegister const*tr,TypeId)const{
  PRINT_CALL_STACK(tr);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  std::stringstream ss;
  ss<<"MemFce-";
  ss<<tr->type2Str(tr->_typeId2VectorIndex(this->classType));
  ss<<"::(";
  bool first=true;
  for(auto const&x:this->argumentTypes){
    if(first)first = false;
    else ss<<",";
    ss<<tr->type2Str(tr->_typeId2VectorIndex(x));
  }
  ss<<")->"<<tr->type2Str(tr->_typeId2VectorIndex(this->returnType));
  return ss.str();
}

void MemFceDescription::copy(void*,void*,TypeRegister const*,TypeId)const{
  assert(false&&"ERROR: member function cannot be copied!");
}

void MemFceDescription::callConstructor(TypeRegister*,void*)const{
  assert(false&&"ERROR: member function is not constructible!");
}

void MemFceDescription::callDestructor(TypeRegister*,void*)const{
  assert(false&&"ERROR: member function is not destructible!");
}

size_t MemFceDescription::byteSize(TypeRegister const*)const{
  assert(false&&"ERROR: member function has no size!");
  return 0;
}


