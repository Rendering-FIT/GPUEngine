#include<geCore/TypeRegister.h>

#include<sstream>
#include<geCore/interpret.h>
#include<geCore/Accessor.h>

using namespace ge::core;

template<typename T>
void printVec(const std::vector<T>&data,typename std::vector<T>::size_type from=0){
  for(typename std::vector<T>::size_type i=from;i<data.size();++i)
    std::cerr<<data[i]<<" ";
  std::cerr<<std::endl;
}

template<typename T>
std::string vec2str(std::vector<T>const&data,typename std::vector<T>::size_type from=0){
  std::stringstream ss;
  ss<<"[";
  if(from<data.size())ss<<data[from];
  for(typename std::vector<T>::size_type i=from+1;i<data.size();++i)
    ss<<","<<data[i];
  ss<<"]";
  return ss.str();
}

TypeRegister::TypeRegister(){
  this->addType(TypeRegister::getTypeKeyword<void              >(),TypeRegister::VOID  );
  this->addType(TypeRegister::getTypeKeyword<bool              >(),TypeRegister::BOOL  );
  this->addType(TypeRegister::getTypeKeyword<char              >(),TypeRegister::I8    );
  this->addType(TypeRegister::getTypeKeyword<short             >(),TypeRegister::I16   );
  this->addType(TypeRegister::getTypeKeyword<int               >(),TypeRegister::I32   );
  this->addType(TypeRegister::getTypeKeyword<long long int     >(),TypeRegister::I64   );
  this->addType(TypeRegister::getTypeKeyword<unsigned char     >(),TypeRegister::U8    );
  this->addType(TypeRegister::getTypeKeyword<unsigned short    >(),TypeRegister::U16   );
  this->addType(TypeRegister::getTypeKeyword<unsigned          >(),TypeRegister::U32   );
  this->addType(TypeRegister::getTypeKeyword<unsigned long long>(),TypeRegister::U64   );
  this->addType(TypeRegister::getTypeKeyword<float             >(),TypeRegister::F32   );
  this->addType(TypeRegister::getTypeKeyword<double            >(),TypeRegister::F64   );
  this->addType(TypeRegister::getTypeKeyword<std::string       >(),TypeRegister::STRING);
  this->addType("ivec2" ,TypeRegister::ARRAY,2,"i32");
  this->addType("ivec3" ,TypeRegister::ARRAY,3,"i32");
  this->addType("ivec4" ,TypeRegister::ARRAY,4,"i32");
  this->addType("uvec2" ,TypeRegister::ARRAY,2,"u32");
  this->addType("uvec3" ,TypeRegister::ARRAY,3,"u32");
  this->addType("uvec4" ,TypeRegister::ARRAY,4,"u32");
  this->addType("vec2"  ,TypeRegister::ARRAY,2,"f32");
  this->addType("vec3"  ,TypeRegister::ARRAY,3,"f32");
  this->addType("vec4"  ,TypeRegister::ARRAY,4,"f32");
}

TypeRegister::TypeID TypeRegister::getTypeId(std::string name)const{
  if(!this->_name2Id.count(name)){
    std::cerr<<"ERROR: TypeRegister::getTypeId("<<name<<") - type \""<<name<<"\" does not exist."<<std::endl;
    return TypeRegister::UNREGISTERED;
  }
  return this->_name2Id.find(name)->second;
}

std::string TypeRegister::toStr(TypeID id)const{
  TypeRegister::Type type=this->getTypeIdType(id);
  std::stringstream ss;
  switch(type){
    case TypeRegister::VOID  :
    case TypeRegister::BOOL  :
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
      for(DescriptionIndex e=0;e<this->getNofStructElements(id);++e){
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
      for(DescriptionIndex e=0;e<this->getNofFceArgs(id);++e){
        ss<<this->toStr(this->getFceArgTypeId(id,e));
        if(e+1<this->getNofFceArgs(id))ss<<",";
      }
      ss<<")->"<<this->getTypeIdName(this->getFceReturnTypeId(id));
      return ss.str();
    case TypeRegister::OBJ:
      ss<<"class "<<this->getTypeIdName(id);
      return ss.str();
    case TypeRegister::TYPEID:
      ss<<"asdasd: "<<id<<"#"<<this->getTypeIdName(id)<<"#";
      return ss.str();
    default:
      return "unknown";
  }
}

std::string TypeRegister::toStr()const{
  printVec(this->_types);

  std::stringstream ss;
  for(DescriptionStartIndex t=0;t<this->getNofTypes();++t){
    ss<<this->toStr(this->getTypeId(t));
    for(auto x:this->getTypeIdSynonyms(this->getTypeId(t)))
      ss<<" "<<x;
    ss<<std::endl;

  }
  return ss.str();
}


TypeRegister::~TypeRegister(){

}

TypeRegister::DescriptionStartIndex TypeRegister::getNofTypes()const{
  return this->_typeStart.size();
}

TypeRegister::TypeID TypeRegister::getTypeId(DescriptionStartIndex index)const{
  return index+TypeRegister::TYPEID;
}

TypeRegister::DescriptionStartIndex TypeRegister::getIndex(TypeID id)const{
  return id-TypeRegister::TYPEID;
}

TypeRegister::DescriptionIndex TypeRegister::getTypeDescriptionLength(TypeID id)const{
  auto index=this->getIndex(id);
  if(this->_typeStart.size()-1==index)return this->_types.size()-this->_typeStart[index];
  return this->_typeStart[index+1]-this->_typeStart[index];
}

TypeRegister::DescriptionElement TypeRegister::getTypeDescriptionElem(TypeID id,TypeRegister::DescriptionIndex i)const{
  return this->_types[this->_typeStart[this->getIndex(id)]+i];
}

TypeRegister::Type TypeRegister::getElementType(DescriptionElement element)const{
  if(element>=TYPEID)return TYPEID;
  return (TypeRegister::Type)element;
}

TypeRegister::Type TypeRegister::getTypeIdType(TypeID id)const{
  DescriptionElement element=this->getTypeDescriptionElem(id,TypeRegister::POSITION::TYPE);
  return this->getElementType(element);
}

TypeRegister::DescriptionIndex TypeRegister::getNofStructElements(TypeID id)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::STRUCT::NOF_ELEMENTS);
}

TypeRegister::TypeID TypeRegister::getStructElementTypeId(TypeID id,DescriptionIndex index)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::STRUCT::INNER_TYPES_START+index);
}

TypeRegister::DescriptionElement TypeRegister::getArraySize(TypeID id)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::ARRAY::SIZE);
}

TypeRegister::TypeID TypeRegister::getArrayInnerTypeId(TypeID id)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::ARRAY::INNER_TYPE);
}

TypeRegister::TypeID TypeRegister::getPtrInnerTypeId(TypeID id)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::PTR::INNER_TYPE);
}

TypeRegister::TypeID TypeRegister::getFceReturnTypeId(TypeID id)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::FCE::RETURN_TYPE);
}

TypeRegister::DescriptionElement TypeRegister::getNofFceArgs(TypeID id)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::FCE::NOF_ARGUMENTS);
}

TypeRegister::TypeID TypeRegister::getFceArgTypeId(TypeID id,DescriptionIndex element)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::FCE::ARGUMENTS_START+element);
}

TypeRegister::DescriptionElement TypeRegister::getObjSize(TypeID id)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::OBJ::SIZE);
}

bool TypeRegister::_incrCheck(DescriptionIndex size,DescriptionIndex&start){
  start++;
  return start<size;
}

bool TypeRegister::_isNewTypeEqualTo(TypeID et,DescriptionList const&type,DescriptionIndex &start){
  //std::cout<<"TypeRegister::_isNewTypeEqualTo("<<et<<","<<vec2str(type)<<","<<start<<")"<<std::endl;
  if(start>=type.size())return false;
  DescriptionIndex lastStart=start;
  auto falseBranch=[&start,&lastStart](){start=lastStart;return false;};
  if(this->getElementType(type[start])==TypeRegister::TYPEID){
    if(et==type[start]){
      start++;
      return true;
    }
    return false;
  }
  if(this->getTypeIdType(et)!=this->getElementType(type[start]))return falseBranch();
  switch(this->getTypeIdType(et)){
    case TypeRegister::VOID  :
    case TypeRegister::BOOL  :
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
      ++start;
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
      for(DescriptionIndex e=0;e<this->getNofStructElements(et);++e)
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
      for(DescriptionIndex e=0;e<this->getNofFceArgs(et);++e)
        if(!this->_isNewTypeEqualTo(this->getFceArgTypeId(et,e),type,start))return falseBranch();
      return true;
    case TypeRegister::OBJ:
      //std::cerr<<"OBJ isNewType"<<std::endl;
      return falseBranch();
    default:
      return falseBranch();
  }
}

bool TypeRegister::_typeExists(TypeRegister::TypeID*id,DescriptionList const&type,DescriptionIndex&start){
  for(DescriptionStartIndex t=0;t<this->getNofTypes();++t)
    if(this->_isNewTypeEqualTo(this->getTypeId(t),type,start)){
      *id=this->getTypeId(t);
      return true;
    }
  return false;
}

std::string TypeRegister::getTypeIdName(TypeID id)const{
  if(!this->_id2name.count(id))return"";
  return this->_id2name.find(id)->second;
}

std::set<std::string>const &TypeRegister::getTypeIdSynonyms(TypeID id)const{
  return this->_id2Synonyms.find(id)->second;
}

bool TypeRegister::hasSynonyms(TypeID id)const{
  return this->_id2Synonyms.find(id)->second.size()>1;
}

bool TypeRegister::areSynonyms(std::string name0,std::string name1)const{
  return this->getTypeId(name0)==this->getTypeId(name1);
}

template<typename T>
std::string getStr(T t){
  std::stringstream ss;
  ss<<t;
  return ss.str();
}

TypeRegister::TypeID TypeRegister::_typeAdd(DescriptionList const&type,DescriptionIndex&start){
  DescriptionIndex lastStart=start;
  auto err=[&start,&lastStart](std::string m){std::cerr<<"ERROR: "<<m<<std::endl;start=lastStart;return 0;};
  //std::cout<<"TypeRegister::_typeAdd("<<vec2str(type)<<","<<start<<")"<<std::endl;
  if(start>=type.size())return err("new type has no description");
  TypeRegister::TypeID id;
  if(this->_typeExists(&id,type,start))return id;
  DescriptionElement size=0;
  TypeRegister::Type newType = this->getElementType(type[start]);
  std::vector<TypeRegister::TypeID>innerTypes;

  switch(newType){
    case TypeRegister::VOID  :
    case TypeRegister::BOOL  :
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
      if(size==0)return err("number of arrays elements cannot be zero");
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
      if(size==0)return err("number of structs elements cannot be zero");
      for(DescriptionElement e=0;e<size;++e){
        TypeRegister::TypeID id=this->_typeAdd(type,start);
        if(id==0)return err("new structs element number: "+getStr(e)+" has invalid format");
        innerTypes.push_back(id);
      }
      if(innerTypes.size()!=size)return err("new struct has "+getStr(size)+" elements by only "+getStr(innerTypes.size())+" elements were provided");
      this->_typeStart.push_back(this->_types.size());
      this->_types.push_back(newType);//write type
      this->_types.push_back(size);//write length
      for(DescriptionElement e=0;e<size;++e)
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
      for(DescriptionElement e=0;e<size;++e){
        TypeRegister::TypeID id=this->_typeAdd(type,start);
        if(id==0)return err("new functions argument number: "+getStr(e)+" has invalid format");
        innerTypes.push_back(id);
      }
      this->_typeStart.push_back(this->_types.size());
      this->_types.push_back(newType);//write type
      this->_types.push_back(innerTypes[0]);//write return type
      this->_types.push_back(size);//write length
      for(DescriptionElement e=0;e<size;++e)//write args
        this->_types.push_back(innerTypes[1+e]);
      return this->getTypeId(this->getNofTypes()-1);
    case TypeRegister::OBJ:
      if(start+1>=type.size())return err("new OBJ has no size");
      size=type[start+1];
      this->_typeStart.push_back(this->_types.size());
      this->_types.push_back(newType);//write type
      this->_types.push_back(size);//write size
      start++;
      return this->getTypeId(this->getNofTypes()-1);
    default:
      return err("what a stupid day...");
  }
}

void TypeRegister::_bindTypeIdName(TypeID id,std::string name){
  this->_name2Id[name] = id  ;
  if(!this->_id2name.count(id)){
    this->_id2name[id  ] = name;
    this->_id2Synonyms[id]=std::set<std::string>();
  }
  this->_id2Synonyms[id].insert(name);
}

TypeRegister::TypeID TypeRegister::addType(std::string name,DescriptionList const&type,std::function<OBJConstructor> constructor,std::function<OBJDestructor> destructor){
  DescriptionIndex start=0;
  TypeRegister::TypeID id;
  if(this->_typeExists(&id,type,start)){
    if(this->_name2Id.count(name)&&this->_name2Id[name]!=id)
      std::cerr<<"ERROR: typeName: "<<name<<" clashes with TypeIds: "<<this->_name2Id[name]<<" and "<<id<<std::endl;
    else if(name!="")this->_bindTypeIdName(id,name);
    this->addConstructor(id,constructor);
    this->addDestructor(id,destructor);
    return id;
  }
  start=0;
  TypeID newTypeId=this->_typeAdd(type,start);
  if(name!=""){
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
    this->_id2Destructor[id]=nullptr;//.erase(id);
    return;
  }
  this->_id2Destructor[id]=destructor;
}

size_t TypeRegister::computeTypeIdSize(TypeID id)const{
  TypeRegister::Type type=this->getTypeIdType(id);
  size_t size=0;
  switch(type){
    case TypeRegister::VOID  :return 0                         ;
    case TypeRegister::BOOL  :return sizeof(bool              );
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
                              for(DescriptionIndex e=0;e<this->getNofStructElements(id);++e)
                                size+=this->computeTypeIdSize(this->getStructElementTypeId(id,e));
                              return size;
    case TypeRegister::FCE:
                              return sizeof(std::shared_ptr<ge::core::Function>);
                              /*
                                 size+=this->computeTypeIdSize(this->getFceReturnTypeId(id));
                                 for(unsigned e=0;e<this->getNofFceArgs(id);++e)
                                 size+=this->computeTypeIdSize(this->getFceArgTypeId(id,e));
                                 return size;
                                 */
    case TypeRegister::OBJ:
                              return this->getObjSize(id);
    default:
                              std::cerr<<"ERROR: uta aus aus gerichtic himla!"<<std::endl;
                              return 0;
  }
}

void   TypeRegister::_callConstructors(char*ptr,TypeID id)const{
  TypeRegister::Type type=this->getTypeIdType(id);
  switch(type){
    case TypeRegister::VOID  :
    case TypeRegister::BOOL  :
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
                              for(DescriptionIndex i=0;i<this->getArraySize(id);++i)
                                this->_callConstructors(ptr+this->computeTypeIdSize(this->getArrayInnerTypeId(id))*i,this->getArrayInnerTypeId(id));
                              break;
    case TypeRegister::STRUCT:
                              for(DescriptionIndex e=0;e<this->getNofStructElements(id);++e){
                                this->_callConstructors(ptr,this->getStructElementTypeId(id,e));
                                ptr+=this->computeTypeIdSize(this->getStructElementTypeId(id,e));
                              }
                              break;
    case TypeRegister::FCE:
                              new(ptr)std::shared_ptr<ge::core::Function>();
                              //TODO CO S FUNKCI
                              break;
    case TypeRegister::OBJ:
                              this->constructUsingCustomConstructor((signed char*)ptr,id);
                              break;
    default:
                              break;
  }
}

bool TypeRegister::integerType(TypeID type)const{
  switch(this->getTypeDescriptionElem(type,0)){
    case I8 :
    case I16:
    case I32:
    case I64:
    case U8 :
    case U16:
    case U32:
    case U64:
      return true;
    default:
      return false;
  }
}

bool TypeRegister::floatType  (TypeID type)const{
  switch(this->getTypeDescriptionElem(type,0)){
    case F32:
    case F64:
      return true;
    default:
      return false;
  }
}

bool TypeRegister::stringType (TypeID type)const{
  return this->getTypeDescriptionElem(type,0)==STRING;
}

void* TypeRegister::alloc(TypeID id)const{
  auto size=this->computeTypeIdSize(id);
  void*ptr=(void*)(new char[size]);
  this->_callConstructors((char*)ptr,id);
  return ptr;
}

std::shared_ptr<Accessor>TypeRegister::sharedAccessor(TypeID id)const{
  return std::make_shared<AtomicAccessor>(this->shared_from_this(),this->alloc(id),id);
}

std::shared_ptr<Accessor>TypeRegister::sharedAccessor(std::string name)const{
  return this->sharedAccessor(this->getTypeId(name));
}

std::shared_ptr<Accessor>TypeRegister::sharedEmptyAccessor(TypeID id,std::function<OBJDestructor>destructor)const{
  if(destructor)
    return std::shared_ptr<Accessor>(new AtomicAccessor(this->shared_from_this(),id),[destructor](AtomicAccessor*ac){destructor((unsigned char*)ac->getData());delete ac;});

  return this->sharedEmptyAccessor(id,this->_id2Destructor.find(id)->second);
  //return std::shared_ptr<Accessor>(new AtomicAccessor(this->shared_from_this(),id),[destructor](AtomicAccessor*ac){destructor((unsigned char*)ac->getData());delete ac;});
//  return std::make_shared<AtomicAccessor>(this->shared_from_this(),id);
}

std::shared_ptr<Accessor>TypeRegister::sharedEmptyAccessor(std::string name,std::function<OBJDestructor>destructor)const{
  return this->sharedEmptyAccessor(this->getTypeId(name),destructor);
}


void TypeRegister::destroyUsingCustomDestroyer(unsigned char*ptr,TypeID id)const{
  std::map<TypeID,std::function<OBJDestructor>>::const_iterator ii=this->_id2Destructor.find(id);
  if(ii!=this->_id2Destructor.end()){
    if(ii->second)ii->second(ptr);
  }
}

void TypeRegister::constructUsingCustomConstructor(signed char*ptr,TypeID id)const{
  std::map<TypeID,std::function<OBJConstructor>>::const_iterator ii=this->_id2Constructor.find(id);
  if(ii!=this->_id2Constructor.end()){
    if(ii->second)ii->second(ptr);
  }
}

TypeRegister::DescriptionIndex TypeRegister::getNofDescriptionUints()const{
  return this->_types.size();
}

TypeRegister::DescriptionElement TypeRegister::getDescription(DescriptionIndex i)const{
  return this->_types[i];
}



