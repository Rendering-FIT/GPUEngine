#include<geDE/TypeRegister.h>

#include<sstream>
#include<memory>
#include<cstring>
#include<vector>
#include<algorithm>

#include<geCore/ErrorPrinter.h>
#include<geDE/AtomicResource.h>
#include<geDE/TypeDescription.h>
#include<geDE/AtomicDescription.h>
#include<geDE/PtrDescription.h>
#include<geDE/ArrayDescription.h>
#include<geDE/StructDescription.h>
#include<geDE/FceDescription.h>
#include<geDE/MemFceDescription.h>
#include<geDE/EnumDescription.h>
#include<geDE/VoidDescription.h>
#include<geDE/AnyDescription.h>

using namespace ge::de;

TypeRegister::TypeRegister(){
}

TypeRegister::~TypeRegister(){
  assert(this!=nullptr);
  for(auto const&x:this->_types)
    delete x;
}


TypeId TypeRegister::_addTypeByDescription(std::string const&name,TypeDescription*d){
  assert(this!=nullptr);
  TypeId id = this->_vectorIndex2TypeId(this->_types.size());
  this->_types.push_back(d);
  this->_bindTypeIdWithName(id,name);
  return id;
}

bool TypeRegister::_checkIfTypeNameExists(
    TypeId               &result    ,
    std::string     const&name      ,
    TypeDescription      *d         ,
    std::string     const&errFceName,
    std::string     const&errMsg    ){
  assert(this!=nullptr);
  auto ii = this->_name2TypeId.find(name);
  if(ii==this->_name2TypeId.end())return false;
  if(!d->equal(this->_getDescription(ii->second))){
    ge::core::printError(errFceName,errMsg);
    delete d;
    result = UNREGISTERED;
    return true;
  }
  delete d;
  result = ii->second;
  return true;
}


bool TypeRegister::_checkIfTypeDescriptionExists(
    TypeId               &result,
    std::string     const&name  ,
    TypeDescription      *d     ){
  assert(this!=nullptr);
  TypeId index = 0;
  for(auto const&x:this->_types){
    if(d->equal(x)){
      TypeId id = this->_vectorIndex2TypeId(index);
      assert(this->_typeId2Synonyms.count(id)!=0);
      if(name!="")this->_typeId2Synonyms.at(id).insert(name);
      delete d;
      result = id;
      return true;
    }
    index++;
  }
  return false;
}

TypeId TypeRegister::_checkAndAddTypeByDescription(
    std::string     const&name      ,
    TypeDescription      *d         ,
    std::string     const&errFceName,
    std::string     const&errMsg    ){
  assert(this!=nullptr);
  TypeId id;
  if(this->_checkIfTypeNameExists(id,name,d,errFceName,errMsg))
    return id;

  if(this->_checkIfTypeDescriptionExists(id,name,d))
    return id;

  return this->_addTypeByDescription(name,d);
}


TypeId TypeRegister::addAtomicType(
    std::string const&name       ,
    size_t      const&size       ,
    CDPtr       const&constructor,
    CDPtr       const&destructor ){
  assert(this!=nullptr);
  auto newDesc = new AtomicDescription(size,constructor,destructor);
  assert(newDesc!=nullptr);

  TypeId id;
  if(this->_checkIfTypeNameExists(id,name,newDesc,GE_CORE_FCENAME,"Atomic type named "+name+" already exists and is different"))
    return id;

  if(constructor!=nullptr&&destructor!=nullptr)
    if(this->_checkIfTypeDescriptionExists(id,name,newDesc))
      return id;

  return this->_addTypeByDescription(name,newDesc);
}

TypeId TypeRegister::addPtrType(
    std::string const&name,
    TypeId      const&innerType){
  assert(this!=nullptr);
  auto newDesc = new PtrDescription(innerType);
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"Ptr type named "+name+" already exists and is different");
}

TypeId TypeRegister::addArrayType(
    std::string const&name     ,
    TypeId      const&innerType,
    size_t      const&size     ){
  assert(this!=nullptr);
  auto newDesc = new ArrayDescription(innerType,size);
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"Array type named "+name+" already exists and is different");
}

TypeId TypeRegister::addStructType(
    std::string        const&name     ,
    std::vector<TypeId>const&elements){
  assert(this!=nullptr);
  auto newDesc = new StructDescription(elements);
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"Struct type named "+name+" already exists and is different");
}

TypeId TypeRegister::addFceType(
    std::string        const&name      ,
    TypeId             const&returnType,
    std::vector<TypeId>const&elements  ){
  assert(this!=nullptr);
  auto newDesc = new FceDescription(returnType,elements);
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"Fce type named "+name+" already exists and is different");
}

TypeId TypeRegister::addMemFceType(
    std::string        const&name      ,
    TypeId             const&returnType,
    TypeId             const&classType ,
    std::vector<TypeId>const&elements  ){
  assert(this!=nullptr);
  auto newDesc = new MemFceDescription(returnType,classType,elements);
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"MemFce type named "+name+" already exists and is different");
}

TypeId TypeRegister::addEnumType(
    std::string                 const&name,
    std::vector<EnumElementType>const&elements){
  assert(this!=nullptr);
  auto newDesc = new EnumDescription(elements);
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"Enum type named "+name+" already exists and is different");
}

TypeId TypeRegister::addVoidType(
    std::string        const&name){
  assert(this!=nullptr);
  auto newDesc = new VoidDescription();
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"Void type named "+name+" already exists and is different");
}

TypeId TypeRegister::addAnyType(
    std::string        const&name){
  assert(this!=nullptr);
  auto newDesc = new AnyDescription();
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"Any type named "+name+" already exists and is different");
}




void TypeRegister::_bindTypeIdWithName(TypeId id,std::string const&name){
  assert(this!=nullptr);
  if(name==""){
    auto ii = this->_typeId2Synonyms.find(id);
    if(ii!=this->_typeId2Synonyms.end())return;
    std::stringstream ss;
    ss<<"type"<<id;
    this->_typeId2Synonyms[id].insert(ss.str());
    this->_name2TypeId[ss.str()]=id;
    return;
  }
  this->_typeId2Synonyms[id].insert(name);
  this->_name2TypeId[name]=id;
}

TypeId TypeRegister::_typeExists(
    TypeDescriptionVector const&description,
    size_t                 &i){
  assert(this!=nullptr);
  if(i>=description.size())return UNREGISTERED;
  switch(description[i]){
    case UNREGISTERED:return UNREGISTERED;
    case ATOMIC      :return UNREGISTERED;
    case PTR         :{PtrDescription      desc;return desc.findInRegister(this,description,i);}
    case ARRAY       :{ArrayDescription    desc;return desc.findInRegister(this,description,i);}
    case STRUCT      :{StructDescription   desc;return desc.findInRegister(this,description,i);}
    case FCE         :{FceDescription      desc;return desc.findInRegister(this,description,i);}
    case MEMFCE      :{MemFceDescription   desc;return desc.findInRegister(this,description,i);}
    case ENUM        :{EnumDescription     desc;return desc.findInRegister(this,description,i);}
    case VOID        :{VoidDescription     desc;return desc.findInRegister(this,description,i);}
    case ANY         :{AnyDescription      desc;return desc.findInRegister(this,description,i);}
    default          :return this->_typeIdExists(description,i);
  }
}

TypeId TypeRegister::_typeIdExists(
    TypeDescriptionVector const&description,
    size_t                 &i){
  assert(this!=nullptr);
  if(i>=description.size())return UNREGISTERED;
  if(description[i]<TYPEID)return UNREGISTERED;
  if(this->_typeId2VectorIndex(description[i])>=this->_types.size())
    return UNREGISTERED;
  return description[i++];
}

TypeId TypeRegister::addCompositeType(
    std::string        const&name       ,
    TypeDescriptionVector  const&description){
  assert(this!=nullptr);
  size_t i=0;
  return this->_addType(name,description,i);
}

TypeId TypeRegister::_addType(
    std::string           const&name       ,
    TypeDescriptionVector const&description,
    size_t                     &i          ){
  assert(this!=nullptr);
  size_t old = i;
  auto id = this->_typeExists(description,i);
  if(id != UNREGISTERED){
    auto ii = this->_name2TypeId.find(name);
    if(ii != this->_name2TypeId.end()){
      if(ii->second != id){
        ge::core::printError(GE_CORE_FCENAME,"name "+name+" is already used with different type: "+ge::core::value2str(ii->second),name,description,i);
        i = old;
        return UNREGISTERED;
      }
      return id;
    }
    this->_bindTypeIdWithName(id,name);
    return id;
  }
  if(i>=description.size())return UNREGISTERED;
  switch(description[i]){
    case UNREGISTERED:return UNREGISTERED;
    case ATOMIC      :return UNREGISTERED;
    case PTR         :return TypeDescription::checkAndBindType(this,name,description,new PtrDescription   (),i);
    case ARRAY       :return TypeDescription::checkAndBindType(this,name,description,new ArrayDescription (),i);
    case STRUCT      :return TypeDescription::checkAndBindType(this,name,description,new StructDescription(),i);
    case FCE         :return TypeDescription::checkAndBindType(this,name,description,new FceDescription   (),i);
    case MEMFCE      :return TypeDescription::checkAndBindType(this,name,description,new MemFceDescription(),i);
    case ENUM        :return TypeDescription::checkAndBindType(this,name,description,new EnumDescription  (),i);
    case VOID        :return TypeDescription::checkAndBindType(this,name,description,new VoidDescription  (),i);
    case ANY         :return TypeDescription::checkAndBindType(this,name,description,new AnyDescription   (),i);
    default          :return this->_addTypeId(name,description,i);
  }
}

TypeId TypeRegister::_addTypeId(
    std::string       const&name       ,
    TypeDescriptionVector const&description,
    size_t                 &i          ){
  assert(this!=nullptr);
  if(i>=description.size())return UNREGISTERED;
  if(description[i]<TYPEID)return UNREGISTERED;
  if(this->_typeId2VectorIndex(description[i])>=this->_types.size())return UNREGISTERED;
  if(name!=""){
    auto ii = this->_name2TypeId.find(name);
    if(ii != this->_name2TypeId.end()){
      if(ii->second != description[i]){
        ge::core::printError(GE_CORE_FCENAME,"name "+name+" is already used with different type: "+ge::core::value2str(ii->second)+" aka "+ii->first,name,description,i);
        return UNREGISTERED;
      }
      return description[i++];
    }
    this->_bindTypeIdWithName(description[i],name);
  }
  return description[i++];
}

TypeId TypeRegister::_vectorIndex2TypeId(TypeId const&index)const{
  return index+TYPEID;
}

TypeId TypeRegister::_typeId2VectorIndex(TypeId const&id)const{
  return id-TYPEID;
}


size_t TypeRegister::getNofTypes()const{
  assert(this!=nullptr);
  return this->_types.size();
}

std::string TypeRegister::type2Str(size_t index)const{
  assert(this!=nullptr);
  assert(index<this->_types.size());
  return this->_types.at(index)->toStr(this,this->_vectorIndex2TypeId(index));
}

TypeRegister::TypeType TypeRegister::getTypeIdType(TypeId id)const{
  PRINT_CALL_STACK(id);
  assert(this!=nullptr);
  return this->_getDescription(id)->type;
}

TypeId TypeRegister::getPtrType(TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == PTR);
  return ((PtrDescription*)d)->innerType;
}

size_t TypeRegister::getArraySize(TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == ARRAY);
  return ((ArrayDescription*)d)->size;
}

TypeId TypeRegister::getArrayElementTypeId(TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == ARRAY);
  return ((ArrayDescription*)d)->elementType;
}

size_t TypeRegister::getNofStructElements(TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == STRUCT);
  return ((StructDescription*)d)->elementTypes.size();
}

TypeId TypeRegister::getStructElementTypeId(TypeId id,size_t index)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == STRUCT);
  assert(index<((StructDescription*)d)->elementTypes.size());
  return ((StructDescription*)d)->elementTypes.at(index);
}

TypeId TypeRegister::getFceReturnTypeId(TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  if(d->type == MEMFCE)
    return this->getMemFceReturnTypeId(id);
  assert(d->type == FCE);
  return ((FceDescription*)d)->returnType;
}

size_t TypeRegister::getNofFceArgs(TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  if(d->type == MEMFCE)
    return this->getNofMemFceArgs(id)+1;
  assert(d->type == FCE);
  return ((FceDescription*)d)->argumentTypes.size();
}

TypeId TypeRegister::getFceArgTypeId(TypeId id,size_t index)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  if(d->type == MEMFCE){
    if(index==0)return this->getMemFceClassTypeId(id);
    else return this->getMemFceArgTypeId(id,index-1);
  }
  assert(d->type == FCE);
  assert(index<((FceDescription*)d)->argumentTypes.size());
  return ((FceDescription*)d)->argumentTypes.at(index);
}

TypeId TypeRegister::getMemFceReturnTypeId (TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  if(d->type == FCE)
    return this->getFceReturnTypeId(id);
  assert(d->type == MEMFCE);
  return ((MemFceDescription*)d)->returnType;
}

TypeId TypeRegister::getMemFceClassTypeId  (TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  if(d->type == FCE)
    return this->getFceArgTypeId(id,0);
  assert(d->type == MEMFCE);
  return ((MemFceDescription*)d)->classType;
}

size_t TypeRegister::getNofMemFceArgs      (TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  if(d->type == FCE)
    return this->getNofFceArgs(id)-1;
  assert(d->type == MEMFCE);
  return ((MemFceDescription*)d)->argumentTypes.size();
}

TypeId TypeRegister::getMemFceArgTypeId    (TypeId id,size_t index)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  if(d->type == FCE)
    return this->getFceArgTypeId(id,index+1);
  assert(d->type == MEMFCE);
  assert(index<((MemFceDescription*)d)->argumentTypes.size());
  return ((MemFceDescription*)d)->argumentTypes.at(index);
}

size_t TypeRegister::getNofEnumElements(TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == ENUM);
  return ((EnumDescription*)d)->elements.size();
}

EnumElementType TypeRegister::getEnumElement(TypeId id,size_t i)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == ENUM);
  assert(i<((EnumDescription*)d)->elements.size());
  return ((EnumDescription*)d)->elements.at(i);
}

size_t TypeRegister::getEnumElementIndex(TypeId id,EnumElementType element)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == ENUM);
  auto dd = (EnumDescription*)d;
  auto ii = std::find(dd->elements.begin(),dd->elements.end(),element);
  assert(ii!=dd->elements.end());
  return *ii;
}

TypeId TypeRegister::getTypeId(std::string const&name)const{
  assert(this!=nullptr);
  if(this->_name2TypeId.count(name)==0){
    ge::core::printError(GE_CORE_FCENAME,"there is no such type",name);
    return UNREGISTERED;
  }
  return this->_name2TypeId.find(name)->second;
}

std::string const& TypeRegister::getTypeIdName(TypeId id)const{
  assert(this!=nullptr);
  assert(this->_typeId2Synonyms.count(id)!=0);
  return *this->_typeId2Synonyms.find(id)->second.begin();
}

std::set<std::string>const& TypeRegister::getTypeIdSynonyms(TypeId id)const{
  assert(this!=nullptr);
  assert(this->_typeId2Synonyms.count(id)!=0);
  return this->_typeId2Synonyms.find(id)->second;
}

bool TypeRegister::hasSynonyms(TypeId id)const{
  assert(this!=nullptr);
  assert(this->_typeId2Synonyms.count(id)!=0);
  return this->_typeId2Synonyms.find(id)->second.size()>1;
}

bool TypeRegister::areSynonyms(std::string const&name0,std::string const&name1)const{
  assert(this!=nullptr);
  if(this->_name2TypeId.count(name0)==0)return false;
  if(this->_name2TypeId.count(name1)==0)return false;
  return this->getTypeId(name0)==this->getTypeId(name1);
}


size_t TypeRegister::computeTypeIdSize(TypeId id)const{
  PRINT_CALL_STACK(id);
  assert(this!=nullptr);
  return this->_getDescription(id)->byteSize(this);
}


bool TypeRegister::areConvertible(TypeId to,TypeId from)const{
  assert(this!=nullptr);
  if(to==from)return true;
  if(this->getTypeIdType(to)==ANY)return true;
  if(this->getTypeIdType(from)==ANY)return true;

  auto arrayInnerType = [this](TypeId a)->TypeId{
    while(this->getTypeIdType(a)==ARRAY)
      a=this->getArrayElementTypeId(a);
    return a;
  };
  auto arraySize = [this](TypeId a)->size_t{
    size_t s=1;
    while(this->getTypeIdType(a)==ARRAY){
      s*=this->getArraySize(a);
      a=this->getArrayElementTypeId(a);
    }
    return s;
  };

  if(this->getTypeIdType(to)==ARRAY && this->getTypeIdType(from) == ARRAY){
    if(arraySize(to)>arraySize(from))return false;
    return this->areConvertible(arrayInnerType(to),arrayInnerType(from));
  }

  auto fceConv = [this](TypeId memfce,TypeId fce)->bool{
    if(this->getMemFceReturnTypeId(memfce)!=this->getFceReturnTypeId(fce))return false;
    if(this->getNofMemFceArgs(memfce)!=this->getNofFceArgs(fce)+1)return false;
    if(this->getMemFceClassTypeId(memfce)!=this->getFceArgTypeId(fce,0))return false;
    for(size_t i=0;i<this->getNofMemFceArgs(memfce);++i)
      if(this->getMemFceArgTypeId(memfce,i)!=this->getFceArgTypeId(fce,1+i))return false;
    return true;
  };
  if(this->getTypeIdType(to)==MEMFCE && this->getTypeIdType(from) == FCE)
    return fceConv(to,from);
  if(this->getTypeIdType(to)==FCE && this->getTypeIdType(from) == MEMFCE)
    return fceConv(from,to);

  return false;
}

void*TypeRegister::alloc(TypeId id)const{
  PRINT_CALL_STACK(id);
  assert(this!=nullptr);
  size_t size = this->computeTypeIdSize(id);
  uint8_t*ptr=new uint8_t[size];
  std::memset(ptr,0,size);
  return ptr;
}

void TypeRegister::free(void*ptr)const{
  PRINT_CALL_STACK(ptr);
  assert(this!=nullptr);
  delete[]((uint8_t*)ptr);
}

void*TypeRegister::construct(TypeId id)const{
  PRINT_CALL_STACK(id);
  assert(this!=nullptr);
  auto ptr=this->alloc(id);
  this->_callConstructors(ptr,id);
  return ptr;
}

void TypeRegister::destroy(void*ptr,TypeId id)const{
  PRINT_CALL_STACK(ptr,id);
  this->_callDestructors(ptr,id);
  this->free(ptr);
}

void TypeRegister::_callConstructors(void*ptr,TypeId id)const{
  PRINT_CALL_STACK(ptr,id);
  assert(this!=nullptr);
  this->_getDescription(id)->callConstructor((TypeRegister*)this,ptr);
}

void TypeRegister::_callDestructors(void*ptr,TypeId id)const{
  PRINT_CALL_STACK(ptr,id);
  assert(this!=nullptr);
  this->_getDescription(id)->callDestructor((TypeRegister*)this,ptr);
}

std::string TypeRegister::data2Str(void*ptr,TypeId id)const{
  PRINT_CALL_STACK(ptr,id);
  assert(this!=nullptr);
  return this->_getDescription(id)->data2Str(this,ptr);
}

void TypeRegister::addToStrFunction(TypeId id,ToStr const&fce){
  PRINT_CALL_STACK(id,fce);
  assert(this!=nullptr);
  this->_getDescription(id)->data2StrPtr = fce;
}


TypeDescription*TypeRegister::_getDescription(TypeId id)const{
  PRINT_CALL_STACK(id);
  assert(this!=nullptr);
  assert(this->_typeId2VectorIndex(id)<this->_types.size());
  return this->_types.at(this->_typeId2VectorIndex(id));
}

void TypeRegister::addDestructor(TypeId id,CDPtr const&destructor){
  PRINT_CALL_STACK(id,destructor);
  assert(this!=nullptr);
  assert(this->_getDescription(id)->type == ATOMIC);
  if(this->_getDescription(id)->type == ATOMIC)
    ((AtomicDescription*)this->_getDescription(id))->destructor = destructor;
}

void TypeRegister::addConstructor(TypeId id,CDPtr const&constructor){
  PRINT_CALL_STACK(id,constructor);
  assert(this!=nullptr);
  assert(this->_getDescription(id)->type == ATOMIC);
  if(this->_getDescription(id)->type == ATOMIC)
    ((AtomicDescription*)this->_getDescription(id))->constructor = constructor;
}

std::shared_ptr<Resource>TypeRegister::sharedResource(TypeId id)const{
  PRINT_CALL_STACK(id);
  assert(this!=nullptr);
  return std::make_shared<AtomicResource>(std::const_pointer_cast<TypeRegister>(this->shared_from_this()),this->construct(id),id);
}

std::shared_ptr<Resource>TypeRegister::sharedResource(std::string const&name)const{
  PRINT_CALL_STACK(name);
  assert(this!=nullptr);
  auto id = this->getTypeId(name);
  return this->sharedResource(id);
}

std::shared_ptr<Resource>TypeRegister::sharedEmptyResource(TypeId id)const{
  PRINT_CALL_STACK(id);
  assert(this!=nullptr);

  return std::shared_ptr<AtomicResource>(new AtomicResource(std::const_pointer_cast<TypeRegister>(this->shared_from_this()),id)
      ,[](AtomicResource*ac){ac->getManager()->destroy(ac->getData(),ac->getId());delete ac;});
  //,[destructor](AtomicResource*ac){destructor((unsigned char*)ac->getData());delete(unsigned char*)ac->getData();delete ac;});
}

std::shared_ptr<Resource>TypeRegister::sharedEmptyResource(std::string const&name)const{
  PRINT_CALL_STACK(name);
  assert(this!=nullptr);
  return this->sharedEmptyResource(this->getTypeId(name));
}


