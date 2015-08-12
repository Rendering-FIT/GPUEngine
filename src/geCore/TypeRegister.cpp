#include<geCore/TypeRegister.h>

#include<sstream>

using namespace ge::core;

template<typename T>
void printVec(std::vector<T>&data,unsigned from=0){
  for(unsigned i=from;i<data.size();++i)
    std::cerr<<data[i]<<" ";
  std::cerr<<std::endl;
}

template<typename T>
std::string vec2str(std::vector<T>&data,unsigned from=0){
  std::stringstream ss;
  ss<<"[";
  if(from<data.size())ss<<data[from];
  for(unsigned i=from+1;i<data.size();++i)
    ss<<","<<data[i];
  ss<<"]";
  return ss.str();
}

TypeRegister::TypeRegister(){
  this->addType("void"  ,TypeRegister::VOID  );
  this->addType("int8"  ,TypeRegister::I8    );
  this->addType("int16" ,TypeRegister::I16   );
  this->addType("int32" ,TypeRegister::I32   );
  this->addType("int64" ,TypeRegister::I64   );
  this->addType("uint8" ,TypeRegister::U8    );
  this->addType("uint16",TypeRegister::U16   );
  this->addType("uint32",TypeRegister::U32   );
  this->addType("uint64",TypeRegister::U64   );
  this->addType("float" ,TypeRegister::F32   );
  this->addType("double",TypeRegister::F64   );
  this->addType("string",TypeRegister::STRING);
}

TypeRegister::TypeID TypeRegister::getTypeId(const char*name){
  if(!this->_name2Id.count(name)){
    std::cerr<<"ERROR: name: \""<<name<<"\" does not have TypeId"<<std::endl;
    return -1;
  }
  return this->_name2Id[name];
}

std::string TypeRegister::toStr(TypeID id){
  TypeRegister::Type type=this->getTypeIdType(id);
  std::stringstream ss;
  switch(type){
    case TypeRegister::VOID  :
    case TypeRegister::I8    :
    case TypeRegister::I16   :
    case TypeRegister::I32   :
    case TypeRegister::I64   :
    case TypeRegister::U8    :
    case TypeRegister::U16   :
    case TypeRegister::U32   :
    case TypeRegister::U64   :
    case TypeRegister::F32   :
    case TypeRegister::F64   :
    case TypeRegister::STRING:
      return this->getTypeIdName(id);
    case TypeRegister::ARRAY:
      ss<<"array[";
      ss<<this->getArraySize(id);
      ss<<",";
      ss<<this->toStr(this->getArrayInnerTypeId(id));
      ss<<"]";
      return ss.str();
    case TypeRegister::STRUCT:
      ss<<"struct{";
      for(unsigned e=0;e<this->getNofStructElements(id);++e){
        ss<<this->toStr(this->getStructElementTypeId(id,e));
        if(e+1<this->getNofStructElements(id))ss<<",";
      }
      ss<<"}";
      return ss.str();
    case TypeRegister::PTR:
      ss<<this->getTypeIdName(this->getPtrInnerTypeId(id))<<"*";
      return ss.str();
    case TypeRegister::FCE:
      ss<<"(";
      for(unsigned e=0;e<this->getNofFceArgs(id);++e){
        ss<<this->toStr(this->getFceArgTypeId(id,e));
        if(e+1<this->getNofFceArgs(id))ss<<",";
      }
      ss<<")->"<<this->getTypeIdName(this->getFceReturnTypeId(id));
      return ss.str();
    case TypeRegister::OBJ:
      ss<<"class "<<this->getTypeIdName(id);
      return ss.str();
    case TypeRegister::TYPEID:
      //ss<<"asdasd: "<<id<<"#"<<this->getTypeIdName(id)<<"#";
      return ss.str();
    default:
      return "unknown";
  }
}

std::string TypeRegister::toStr(){
  printVec(this->_types);

  std::stringstream ss;
  for(unsigned t=0;t<this->getNofTypes();++t)
    ss<<this->toStr(this->getTypeId(t))<<std::endl;
  return ss.str();
}


TypeRegister::~TypeRegister(){

}

unsigned TypeRegister::getNofTypes(){
  return this->_typeStart.size();
}

TypeRegister::TypeID TypeRegister::getTypeId(unsigned index){
  return index+TypeRegister::TYPEID;
}

unsigned TypeRegister::getIndex(TypeID id){
  return id-TypeRegister::TYPEID;
}

unsigned TypeRegister::getTypeDescriptionLength(TypeID id){
  unsigned index=this->getIndex(id);
  if(this->_typeStart.size()-1==index)return this->_types.size()-this->_typeStart[index];
  return this->_typeStart[index+1]-this->_typeStart[index];
}

unsigned TypeRegister::getTypeDescriptionElem  (TypeID id,unsigned i){
  //std::cerr<<"id: "<<id<<", i: "<<i<<std::endl;
  return this->_types[this->_typeStart[this->getIndex(id)]+i];
}

TypeRegister::Type TypeRegister::getElementType(unsigned element){
  if(element>=TYPEID)return TYPEID;
  return (TypeRegister::Type)element;
}

TypeRegister::Type TypeRegister::getTypeIdType(TypeID id){
  unsigned element=this->getTypeDescriptionElem(id,this->POSITION.TYPE);
  return this->getElementType(element);
}

unsigned TypeRegister::getNofStructElements(TypeID id){
  return this->getTypeDescriptionElem(id,this->POSITION.STRUCT.NOF_ELEMENTS);
}

TypeRegister::TypeID TypeRegister::getStructElementTypeId(TypeID id,unsigned element){
  return this->getTypeDescriptionElem(id,this->POSITION.STRUCT.INNER_TYPES_START+element);
}

unsigned TypeRegister::getArraySize(TypeID id){
  return this->getTypeDescriptionElem(id,this->POSITION.ARRAY.SIZE);
}

TypeRegister::TypeID TypeRegister::getArrayInnerTypeId(TypeID id){
  return this->getTypeDescriptionElem(id,this->POSITION.ARRAY.INNER_TYPE);
}

TypeRegister::TypeID TypeRegister::getPtrInnerTypeId(TypeID id){
  return this->getTypeDescriptionElem(id,this->POSITION.PTR.INNER_TYPE);
}

TypeRegister::TypeID TypeRegister::getFceReturnTypeId(TypeID id){
  return this->getTypeDescriptionElem(id,this->POSITION.FCE.RETURN_TYPE);
}

unsigned TypeRegister::getNofFceArgs(TypeID id){
  return this->getTypeDescriptionElem(id,this->POSITION.FCE.NOF_ARGUMENTS);
}

TypeRegister::TypeID TypeRegister::getFceArgTypeId(TypeID id,unsigned element){
  return this->getTypeDescriptionElem(id,this->POSITION.FCE.ARGUMENTS_START+element);
}

unsigned TypeRegister::getObjSize(TypeID id){
  return this->getTypeDescriptionElem(id,this->POSITION.OBJ.SIZE);
}

bool TypeRegister::_incrCheck(unsigned size,unsigned&start){
  start++;
  return start<size;
}

bool TypeRegister::_isNewTypeEqualTo(TypeID et,std::vector<unsigned>&type,unsigned&start){
  //std::cout<<"TypeRegister::_isNewTypeEqualTo("<<et<<","<<vec2str(type)<<","<<start<<")"<<std::endl;
  if(start>=type.size())return false;
  unsigned lastStart=start;
  auto falseBranch=[&start,&lastStart](){start=lastStart;return false;};
  if(this->getElementType(type[start])==TypeRegister::TYPEID){
    if(et==type[start]){
      start++;
      return true;
    }
    return false;
  }
  if(this->getTypeIdType(et)!=this->getElementType(type[start]))return falseBranch();
  start++;
  switch(this->getTypeIdType(et)){
    case TypeRegister::VOID  :
    case TypeRegister::I8    :
    case TypeRegister::I16   :
    case TypeRegister::I32   :
    case TypeRegister::I64   :
    case TypeRegister::U8    :
    case TypeRegister::U16   :
    case TypeRegister::U32   :
    case TypeRegister::U64   :
    case TypeRegister::F32   :
    case TypeRegister::F64   :
    case TypeRegister::STRING:
    case TypeRegister::TYPEID:
      return true;
    case TypeRegister::ARRAY:
      if(!this->_incrCheck(type.size(),start))                              return falseBranch();
      if(this->getArraySize(et)!=type[start])                               return falseBranch();
      if(!this->_incrCheck(type.size(),start))                              return falseBranch();
      if(!this->_isNewTypeEqualTo(this->getArrayInnerTypeId(et),type,start))return falseBranch();
      return true;
    case TypeRegister::STRUCT:
      if(!this->_incrCheck(type.size(),start))       return falseBranch();
      if(this->getNofStructElements(et)!=type[start])return falseBranch();
      if(!this->_incrCheck(type.size(),start))       return falseBranch();
      for(unsigned e=0;e<this->getNofStructElements(et);++e)
        if(!this->_isNewTypeEqualTo(this->getStructElementTypeId(et,e),type,start))return falseBranch();
      return true;
    case TypeRegister::PTR:
      if(!this->_incrCheck(type.size(),start))                            return falseBranch();
      if(!this->_isNewTypeEqualTo(this->getPtrInnerTypeId(et),type,start))return falseBranch();
      return true;
    case TypeRegister::FCE:
      if(!this->_incrCheck(type.size(),start))                             return falseBranch();
      if(!this->_isNewTypeEqualTo(this->getFceReturnTypeId(et),type,start))return falseBranch();
      if(this->getNofFceArgs(et)!=type[start])                             return falseBranch();
      if(!this->_incrCheck(type.size(),start))                             return falseBranch();
      for(unsigned e=0;e<this->getNofFceArgs(et);++e)
        if(!this->_isNewTypeEqualTo(this->getFceArgTypeId(et,e),type,start))return falseBranch();
      return true;
    case TypeRegister::OBJ:
      std::cerr<<"OBJ isNewType"<<std::endl;
      return falseBranch();
    default:
      return falseBranch();
  }
}

bool TypeRegister::_typeExists(TypeRegister::TypeID*id,std::vector<unsigned>&type,unsigned&start){
  for(unsigned t=0;t<this->getNofTypes();++t)
    if(this->_isNewTypeEqualTo(this->getTypeId(t),type,start)){
      *id=this->getTypeId(t);
      return true;
    }
  return false;
}

std::string TypeRegister::getTypeIdName(TypeID id){
  if(!this->_id2name.count(id))return"";
  return this->_id2name[id];
}
std::set<std::string>&TypeRegister::getTypeIdSynonyms(TypeID id){
  return this->_id2Synonyms[id];
}
bool                  TypeRegister::hasSynonyms      (TypeID id){
  return this->_id2Synonyms[id].size()>1;
}
bool                  TypeRegister::areSynonyms      (const char*name0,const char*name1){
  return this->getTypeId(name0)==this->getTypeId(name1);
}

template<typename T>
std::string getStr(T t){
  std::stringstream ss;
  ss<<t;
  return ss.str();
}

TypeRegister::TypeID TypeRegister::_typeAdd(std::vector<unsigned>&type,unsigned&start){
  unsigned lastStart=start;
  auto err=[&start,&lastStart](std::string m){std::cerr<<"ERROR: "<<m<<std::endl;start=lastStart;return 0;};
  //std::cout<<"TypeRegister::_typeAdd("<<vec2str(type)<<","<<start<<")"<<std::endl;
  if(start>=type.size())return err("new type has no description");
  TypeRegister::TypeID id;
  if(this->_typeExists(&id,type,start))return id;

  unsigned size=0;
  TypeRegister::Type newType = this->getElementType(type[start]);
  std::vector<TypeRegister::TypeID>innerTypes;

  switch(newType){
    case TypeRegister::VOID  :
    case TypeRegister::I8    :
    case TypeRegister::I16   :
    case TypeRegister::I32   :
    case TypeRegister::I64   :
    case TypeRegister::U8    :
    case TypeRegister::U16   :
    case TypeRegister::U32   :
    case TypeRegister::U64   :
    case TypeRegister::F32   :
    case TypeRegister::F64   :
    case TypeRegister::STRING:
      this->_typeStart.push_back(this->_types.size());
      this->_types.push_back(newType);//write type
      start++;
      return this->getTypeId(this->getNofTypes()-1);
    case TypeRegister::TYPEID:
      return err("new type is typeid = "+getStr(type[start])+" that does not exists");
    case TypeRegister::ARRAY:
      if(start+1>=type.size())return err("new array type has no size");
      start+=2;
      size=type[start-1];
      innerTypes.push_back(this->_typeAdd(type,start));
      if(innerTypes[0]==0)return err("new arrays inner type has invalid description");
      this->_typeStart.push_back(this->_types.size());
      this->_types.push_back(newType);//write type
      this->_types.push_back(size);//write length
      this->_types.push_back(innerTypes[0]);//write inner type
      return this->getTypeId(this->getNofTypes()-1);
    case TypeRegister::STRUCT:
      if(start+1>=type.size())return err("new struct type has no size");
      start+=2;
      size=type[start-1];
      for(unsigned e=0;e<size;++e){
        TypeRegister::TypeID id=this->_typeAdd(type,start);
        if(id==0)return err("new structs element number: "+getStr(e)+" has invalid format");
        innerTypes.push_back(id);
      }
      if(innerTypes.size()!=size)return err("new struct has "+getStr(size)+" elements by only "+getStr(innerTypes.size())+" elements were provided");
      this->_typeStart.push_back(this->_types.size());
      this->_types.push_back(newType);//write type
      this->_types.push_back(size);//write length
      for(unsigned e=0;e<size;++e)
        this->_types.push_back(innerTypes[e]);
      return this->getTypeId(this->getNofTypes()-1);
    case TypeRegister::PTR:
      start+=1;
      innerTypes.push_back(this->_typeAdd(type,start));
      if(innerTypes[0]==0)return err("new ptrs inner type has invalid format");
      this->_typeStart.push_back(this->_types.size());
      this->_types.push_back(newType);//write type
      this->_types.push_back(innerTypes[0]);
      return this->getTypeId(this->getNofTypes()-1);
    case TypeRegister::FCE:
      start+=1;
      innerTypes.push_back(this->_typeAdd(type,start));
      if(innerTypes[0]==0)return err("function return type has invalid return format");
      if(size>=type.size())return err("new function has no size");
      size=type[start];
      start+=1;
      for(unsigned e=0;e<size;++e){
        TypeRegister::TypeID id=this->_typeAdd(type,start);
        if(id==0)return err("new functions argument number: "+getStr(e)+" has invalid format");
        innerTypes.push_back(id);
      }
      this->_typeStart.push_back(this->_types.size());
      this->_types.push_back(newType);//write type
      this->_types.push_back(innerTypes[0]);//write return type
      this->_types.push_back(size);//write length
      for(unsigned e=0;e<size;++e)//write args
        this->_types.push_back(innerTypes[1+e]);
      return this->getTypeId(this->getNofTypes()-1);
    case TypeRegister::OBJ:
      size=type[start];
      this->_typeStart.push_back(this->_types.size());
      this->_types.push_back(newType);//write type
      this->_types.push_back(size);//write size
      start++;
      return this->getTypeId(this->getNofTypes()-1);
    default:
      return err("what a stupid day...");
  }
}

void TypeRegister::_bindTypeIdName(TypeID id,const char*name){
  //std::cout<<"TypeRegister::_bindTypeIdName("<<id<<","<<name<<")"<<std::endl;
  this->_name2Id[name] = id  ;
  if(!this->_id2name.count(id))
    this->_id2name[id  ] = name;
  this->_id2Synonyms[id].insert(name);
}

TypeRegister::TypeID TypeRegister::addType(const char*name,std::vector<unsigned>&type,std::function<OBJConstructor> constructor,std::function<OBJDestructor> destructor){
  //std::cerr<<"TypeRegister::addType("<<name<<","<<vec2str(type)<<");"<<std::endl;
  unsigned start=0;
  TypeRegister::TypeID id;
  if(this->_typeExists(&id,type,start)){
    if(this->_name2Id.count(name)&&this->_name2Id[name]!=id)
      std::cerr<<"ERROR: typeName: "<<name<<" clashes with TypeIds: "<<this->_name2Id[name]<<" and "<<id<<std::endl;
    else if(std::strcmp(name,""))this->_bindTypeIdName(id,name);
    this->addConstructor(id,constructor);
    this->addDestructor(id,destructor);
    return id;
  }
  start=0;
  TypeID newTypeId=this->_typeAdd(type,start);
  if(std::strcmp(name,"")){
    this->_bindTypeIdName(newTypeId,name);
    this->addConstructor(newTypeId,constructor);
    this->addDestructor(newTypeId,destructor);
    return newTypeId;
  }else{
    std::stringstream ss;
    ss<<"_type"<<newTypeId;
    this->_bindTypeIdName(newTypeId,ss.str().c_str());
    this->addConstructor(newTypeId,constructor);
    this->addDestructor(newTypeId,destructor);
    return newTypeId;
  }
  return 0;
}

void TypeRegister::addConstructor(TypeID id,std::function<OBJConstructor> constructor){
  if(!constructor){
    this->_id2Constructor.erase(id);
    return;
  }
  this->_id2Constructor[id]=constructor;
}

void TypeRegister::addDestructor(TypeID id,std::function<OBJDestructor> destructor){
  if(!destructor){
    this->_id2Destructor.erase(id);
    return;
  }
  this->_id2Destructor[id]=destructor;
}

unsigned TypeRegister::computeTypeIdSize(TypeID id){
  TypeRegister::Type type=this->getTypeIdType(id);
  unsigned size=0;
  switch(type){
    case TypeRegister::VOID  :return 0;
    case TypeRegister::I8    :return sizeof(char              );
    case TypeRegister::I16   :return sizeof(short             );
    case TypeRegister::I32   :return sizeof(int               );
    case TypeRegister::I64   :return sizeof(long long int     );
    case TypeRegister::U8    :return sizeof(unsigned char     );
    case TypeRegister::U16   :return sizeof(unsigned short    );
    case TypeRegister::U32   :return sizeof(unsigned          );
    case TypeRegister::U64   :return sizeof(unsigned long long);
    case TypeRegister::F32   :return sizeof(float             );
    case TypeRegister::F64   :return sizeof(double            );
    case TypeRegister::STRING:return sizeof(std::string       );
    case TypeRegister::PTR   :return sizeof(void*             );
    case TypeRegister::ARRAY:
                              return this->getArraySize(id)*this->computeTypeIdSize(this->getArrayInnerTypeId(id));
    case TypeRegister::STRUCT:
                              for(unsigned e=0;e<this->getNofStructElements(id);++e)
                                size+=this->computeTypeIdSize(this->getStructElementTypeId(id,e));
                              return size;
    case TypeRegister::FCE:
                              size+=this->computeTypeIdSize(this->getFceReturnTypeId(id));
                              for(unsigned e=0;e<this->getNofFceArgs(id);++e)
                                size+=this->computeTypeIdSize(this->getFceArgTypeId(id,e));
                              return size;
    case TypeRegister::OBJ:
                              return this->getObjSize(id);
    default:
                              std::cerr<<"ERROR: uta aus aus gerichtic himla!"<<std::endl;
                              return 0;
  }
}

void   TypeRegister::_callConstructors(char*ptr,TypeID id){
  //std::cerr<<"TypeRegister::_callConstructors: "<<id<<" "<<this->getTypeIdType(id)<<std::endl;
  TypeRegister::Type type=this->getTypeIdType(id);
  switch(type){
    case TypeRegister::VOID  :
    case TypeRegister::I8    :
    case TypeRegister::I16   :
    case TypeRegister::I32   :
    case TypeRegister::I64   :
    case TypeRegister::U8    :
    case TypeRegister::U16   :
    case TypeRegister::U32   :
    case TypeRegister::U64   :
    case TypeRegister::F32   :
    case TypeRegister::F64   :
    case TypeRegister::PTR   :break;
    case TypeRegister::STRING:
                              new(ptr)std::string();
                              break;
    case TypeRegister::ARRAY:
                              for(unsigned i=0;i<this->getArraySize(id);++i)
                                this->_callConstructors(ptr+this->computeTypeIdSize(this->getArrayInnerTypeId(id))*i,this->getArrayInnerTypeId(id));
                              break;
    case TypeRegister::STRUCT:
                              for(unsigned e=0;e<this->getNofStructElements(id);++e){
                                this->_callConstructors(ptr,this->getStructElementTypeId(id,e));
                                ptr+=this->computeTypeIdSize(this->getStructElementTypeId(id,e));
                              }
                              break;
    case TypeRegister::FCE:
                              //TODO CO S FUNKCI
                              break;
    case TypeRegister::OBJ:
                              this->constructUsingCustomConstructor((signed char*)ptr,id);
                              break;
    default:
                              break;
  }
}

void* TypeRegister::alloc(TypeID id){
  unsigned size=this->computeTypeIdSize(id);
  void*ptr=(void*)(new char[size]);
  this->_callConstructors((char*)ptr,id);
  return ptr;
}

Accessor TypeRegister::allocAccessor(TypeID id){
  return Accessor(this,this->alloc(id),id);
}

Accessor TypeRegister::allocAccessor(const char*name){
  return this->allocAccessor(this->getTypeId(name));
}

void TypeRegister::destroyUsingCustomDestroyer(unsigned char*ptr,TypeID id){
  std::map<TypeID,std::function<OBJDestructor>>::iterator ii=this->_id2Destructor.find(id);
  if(ii!=this->_id2Destructor.end()){
    ii->second(ptr);
  }
}

void TypeRegister::constructUsingCustomConstructor(signed char*ptr,TypeID id){
  std::map<TypeID,std::function<OBJConstructor>>::iterator ii=this->_id2Constructor.find(id);
  if(ii!=this->_id2Constructor.end()){
    ii->second(ptr);
  }
}


Accessor::Accessor(){}

Accessor::Accessor(Accessor const& ac){
  this->_manager = ac._manager;
  this->_data    = ac._data   ;
  this->_id      = ac._id     ;
}

Accessor::Accessor(TypeRegister*manager,const void*data,TypeRegister::TypeID id){
  this->_manager =        manager;
  this->_data    = (void*)data   ;
  this->_id      =        id     ;
}


TypeRegister*        Accessor::getManager(){return this->_manager;}
void*               Accessor::getData   (){return this->_data   ;}
TypeRegister::TypeID Accessor::getId     (){return this->_id     ;}

Accessor Accessor::operator[](unsigned elem){
  TypeRegister::TypeID innerType = 0;
  unsigned            offset    = 0;
  switch(this->getManager()->getTypeIdType(this->_id)){
    case TypeRegister::ARRAY :
      innerType = this->getManager()->getArrayInnerTypeId(this->getId());
      offset    = this->getManager()->computeTypeIdSize(innerType)*elem;
      return Accessor(this->getManager(),((char*)this->getData())+offset,innerType);
    case TypeRegister::STRUCT:
      innerType = this->getManager()->getStructElementTypeId(this->getId(),elem);
      for(unsigned i=0;i<elem;++i)
        offset += this->getManager()->computeTypeIdSize(this->getManager()->getStructElementTypeId(this->getId(),i));
      return Accessor(this->getManager(),((char*)this->getData())+offset,innerType);
    default:
      return Accessor(this->getManager(),this->getData(),this->getId());
  }
}

unsigned Accessor::getNofElements(){
  switch(this->_id){
    case TypeRegister::ARRAY :
      return this->getManager()->getArraySize(this->getId());
    case TypeRegister::STRUCT:
      return this->getManager()->getNofStructElements(this->getId());
    default                 :
      return 0;
  }
}

void Accessor::_callDesctuctors(char*ptr,TypeRegister::TypeID id){
  TypeRegister::Type type=this->_manager->getTypeIdType(id);
  switch(type){
    case TypeRegister::VOID  :
    case TypeRegister::I8    :
    case TypeRegister::I16   :
    case TypeRegister::I32   :
    case TypeRegister::I64   :
    case TypeRegister::U8    :
    case TypeRegister::U16   :
    case TypeRegister::U32   :
    case TypeRegister::U64   :
    case TypeRegister::F32   :
    case TypeRegister::F64   :
    case TypeRegister::PTR   :break;
    case TypeRegister::STRING:
                              ((std::string*)ptr)->~basic_string();
                              break;
    case TypeRegister::ARRAY:
                              for(unsigned i=0;i<this->_manager->getArraySize(id);++i)
                                this->_callDesctuctors(ptr+this->_manager->computeTypeIdSize(this->_manager->getArrayInnerTypeId(id))*i,this->_manager->getArrayInnerTypeId(id));
                              break;
    case TypeRegister::STRUCT:
                              for(unsigned e=0;e<this->_manager->getNofStructElements(id);++e){
                                this->_callDesctuctors(ptr,this->_manager->getStructElementTypeId(id,e));
                                ptr+=this->_manager->computeTypeIdSize(this->_manager->getStructElementTypeId(id,e));
                              }
                              break;
    case TypeRegister::FCE:
                              //TODO CO S FUNKCI
                              break;
    case TypeRegister::OBJ:
                              this->_manager->destroyUsingCustomDestroyer((unsigned char*)ptr,id);
                              break;
    default:
                              break;
  }
}

void Accessor::free(){
  this->_callDesctuctors((char*)this->_data,this->_id);
  delete[](char*)this->_data;
  this->_data = NULL;
  this->_id   = 0;
}

const void*Accessor::getPointer(){return (void*)this->getData();}


