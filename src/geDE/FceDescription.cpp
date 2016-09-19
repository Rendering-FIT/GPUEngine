#include<geDE/FceDescription.h>
#include<cassert>
#include<geCore/ErrorPrinter.h>

using namespace ge::de;

FceDescription::FceDescription(
    TypeId             const&returnType   ,
    std::vector<TypeId>const&argumentTypes):TypeDescription(TypeRegister::FCE){
  PRINT_CALL_STACK(returnType,argumentTypes);
  assert(this!=nullptr);
  this->returnType = returnType;
  this->argumentTypes = argumentTypes;
}

FceDescription::FceDescription():TypeDescription(TypeRegister::FCE){
  PRINT_CALL_STACK();
}

FceDescription::~FceDescription(){
  PRINT_CALL_STACK();
}

bool FceDescription::init(
    TypeRegister*               tr         ,
    TypeDescriptionVector const&description,
    size_t                     &i          ,
    bool                        exists     ){
  PRINT_CALL_STACK(tr,description,i,exists);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  size_t old = i;
  if(i>=description.size()){
    if(!exists)ge::core::printError(GE_CORE_FCENAME,"Function description is empty",tr,description,i,exists);
    i=old;
    return false;
  }
  if(description[i++]!=TypeRegister::FCE){
    if(!exists)ge::core::printError(GE_CORE_FCENAME,"Function description does not start with FCE",tr,description,i,exists);
    i=old;
    return false;
  }
  if(exists)
    this->returnType = tr->_typeExists(description,i);
  else
    this->returnType = tr->_addType("",description,i);
  if(returnType == TypeRegister::UNREGISTERED){
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


bool FceDescription::operator==(FceDescription const&other)const{
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  return 
    this->returnType == other.returnType && 
    this->argumentTypes == other.argumentTypes;
}

bool FceDescription::equal(TypeDescription const*other)const{
  PRINT_CALL_STACK(other);
  assert(this!=nullptr);
  assert(other!=nullptr);
  if(this->type != other->type)return false;
  return *this==*(FceDescription*)other;
}

std::string FceDescription::toStr(TypeRegister const*tr,TypeId)const{
  PRINT_CALL_STACK(tr);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  std::stringstream ss;
  ss<<"Fce-(";
  bool first=true;
  for(auto const&x:this->argumentTypes){
    if(first)first = false;
    else ss<<",";
    ss<<tr->type2Str(tr->_typeId2VectorIndex(x));
  }
  ss<<")->"<<tr->type2Str(tr->_typeId2VectorIndex(this->returnType));
  return ss.str();
}

void FceDescription::copy(void*,void*,TypeRegister const*,TypeId)const{
  assert(false&&"ERROR: Fce cannot be copied!");
}

void FceDescription::callConstructor(TypeRegister*,void*)const{
  assert(false&&"ERROR: Fce is not constructible!");
}

void FceDescription::callDestructor(TypeRegister*,void*)const{
  assert(false&&"ERROR: Fce is not destructible!");
}

size_t FceDescription::byteSize(TypeRegister const*)const{
  assert(false&&"ERROR: Fce has no size!");
  return 0;
}


