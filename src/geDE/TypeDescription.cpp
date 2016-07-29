#include<geDE/TypeDescription.h>
#include<cassert>
#include<geCore/ErrorPrinter.h>

using namespace ge::de;

TypeDescription::TypeDescription(TypeRegister::TypeType const&type){
  PRINT_CALL_STACK(type);
  assert(this!=nullptr);
  this->type = type;
  this->data2StrPtr = nullptr;
}

TypeId TypeDescription::findInRegister(
    TypeRegister               *tr         ,
    TypeDescriptionVector const&description,
    size_t                     &i          ){
  PRINT_CALL_STACK(tr,description,i);
  assert(this!=nullptr);
  assert(tr!=nullptr);
  size_t old = i;
  if(!this->init(tr,description,i,true))return TypeRegister::UNREGISTERED;
  TypeId index = 0;
  for(auto const&x:tr->_types){
    if(x->equal(this))
      return tr->_vectorIndex2TypeId(index);
    index++;
  }
  i = old;
  return TypeRegister::UNREGISTERED;
}

std::string TypeDescription::data2Str(TypeRegister const*,void*ptr){
  PRINT_CALL_STACK(ptr);
  assert(this!=nullptr);
  if(this->data2StrPtr)return this->data2StrPtr(ptr);
  return "";
}

TypeId TypeDescription::checkAndBindType(
    TypeRegister               *tr         ,
    std::string           const&name       ,
    TypeDescriptionVector const&description,
    TypeDescription            *d          ,
    size_t                     &i          ){
  PRINT_CALL_STACK(tr,name,description,d,i);
  assert(d!=nullptr);
  size_t old = i;
  if(!d->init(tr,description,i,false)){
    delete d;
    return TypeRegister::UNREGISTERED;
  }
  assert(tr!=nullptr);
  auto id = tr->_vectorIndex2TypeId(tr->_types.size());
  auto ii = tr->_name2TypeId.find(name);
  if(ii != tr->_name2TypeId.end()){
    ge::core::printError("TypeDescription::checkAndBindType",std::string("name ")+name+" is already used with different type: "+ge::core::value2str(ii->second)+" aka "+ii->first,tr,name,description,d,i);
    i=old;
    delete d;
    return TypeRegister::UNREGISTERED;
  }
  tr->_types.push_back(d);
  tr->_bindTypeIdWithName(id,name);
  return id;
}

