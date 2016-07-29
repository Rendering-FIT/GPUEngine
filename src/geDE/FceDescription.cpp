#include<geDE/FceDescription.h>
#include<cassert>

using namespace ge::de;

FceDescription::FceDescription(
    TypeId             const&returnType   ,
    std::vector<TypeId>const&argumentTypes):TypeDescription(TypeRegister::FCE){
  assert(this!=nullptr);
  this->returnType = returnType;
  this->argumentTypes = argumentTypes;
}

FceDescription::FceDescription():TypeDescription(TypeRegister::FCE){}

FceDescription::~FceDescription(){}

bool FceDescription::init(
    TypeRegister*           tr         ,
    TypeDescriptionVector const&description,
    size_t                 &i          ,
    bool                    exists     ){
  assert(this!=nullptr);
  size_t old = i;
  if(i>=description.size()){
    if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Function description is empty"<<std::endl;
    i=old;
    return false;
  }
  if(description[i++]!=TypeRegister::FCE){
    if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Function description does not start with FCE"<<std::endl;
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
  assert(this!=nullptr);
  return 
    this->returnType == other.returnType && 
    this->argumentTypes == other.argumentTypes;
}

bool FceDescription::equal(TypeDescription const*other)const{
  assert(this!=nullptr);
  if(this->type != other->type)return false;
  return *this==*(FceDescription*)other;
}

std::string FceDescription::toStr(TypeRegister const*tr,TypeId)const{
  assert(this!=nullptr);
  std::stringstream ss;
  ss<<"(";
  bool first=true;
  for(auto const&x:this->argumentTypes){
    if(first)first = false;
    else ss<<",";
    ss<<tr->type2Str(tr->_typeId2VectorIndex(x));
  }
  ss<<")->"<<tr->type2Str(tr->_typeId2VectorIndex(this->returnType));
  return ss.str();
}

void FceDescription::callConstructor(TypeRegister*,void*)const{
  PRINT_CALL_STACK("FunctionDescription::callConstructor",ptr);
  //new(ptr)std::shared_ptr<Function>();
}

void FceDescription::callDestructor(TypeRegister*,void*)const{
  PRINT_CALL_STACK("FunctionDescription::callDestructor",ptr);
  //((std::shared_ptr<Function>*)ptr)->~shared_ptr();
}

size_t FceDescription::byteSize(TypeRegister const*)const{
  PRINT_CALL_STACK("FunctionDescription::byteSize");
  return 0;
  //return sizeof(std::shared_ptr<FceDescription>);
}


