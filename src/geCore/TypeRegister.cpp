#include<geCore/TypeRegister.h>

#include<sstream>
#include<geCore/interpret.h>

using namespace ge::core;

template<typename T>
void printVec(const std::vector<T>&data,unsigned from=0){
  for(unsigned i=from;i<data.size();++i)
    std::cerr<<data[i]<<" ";
  std::cerr<<std::endl;
}

template<typename T>
std::string vec2str(std::vector<T>const&data,unsigned from=0){
  std::stringstream ss;
  ss<<"[";
  if(from<data.size())ss<<data[from];
  for(unsigned i=from+1;i<data.size();++i)
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
  //  return this->_name2Id[name];
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
      ss<<"asdasd: "<<id<<"#"<<this->getTypeIdName(id)<<"#";
      return ss.str();
    default:
      return "unknown";
  }
}

std::string TypeRegister::toStr()const{
  printVec(this->_types);

  std::stringstream ss;
  for(unsigned t=0;t<this->getNofTypes();++t){
    ss<<this->toStr(this->getTypeId(t));
    for(auto x:this->getTypeIdSynonyms(this->getTypeId(t)))
      ss<<" "<<x;
    ss<<std::endl;

  }
  return ss.str();
}


TypeRegister::~TypeRegister(){

}

unsigned TypeRegister::getNofTypes()const{
  return (unsigned)this->_typeStart.size();
}

TypeRegister::TypeID TypeRegister::getTypeId(unsigned index)const{
  return index+TypeRegister::TYPEID;
}

unsigned TypeRegister::getIndex(TypeID id)const{
  return id-TypeRegister::TYPEID;
}

unsigned TypeRegister::getTypeDescriptionLength(TypeID id)const{
  unsigned index=this->getIndex(id);
  if(this->_typeStart.size()-1==index)return (unsigned)(this->_types.size()-this->_typeStart[index]);
  return this->_typeStart[index+1]-this->_typeStart[index];
}

unsigned TypeRegister::getTypeDescriptionElem  (TypeID id,unsigned i)const{
  //std::cerr<<"id: "<<id<<", i: "<<i<<std::endl;
  return this->_types[this->_typeStart[this->getIndex(id)]+i];
}

TypeRegister::Type TypeRegister::getElementType(unsigned element)const{
  if(element>=TYPEID)return TYPEID;
  return (TypeRegister::Type)element;
}

TypeRegister::Type TypeRegister::getTypeIdType(TypeID id)const{
  unsigned element=this->getTypeDescriptionElem(id,TypeRegister::POSITION::TYPE);
  return this->getElementType(element);
}

unsigned TypeRegister::getNofStructElements(TypeID id)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::STRUCT::NOF_ELEMENTS);
}

TypeRegister::TypeID TypeRegister::getStructElementTypeId(TypeID id,unsigned element)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::STRUCT::INNER_TYPES_START+element);
}

unsigned TypeRegister::getArraySize(TypeID id)const{
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

unsigned TypeRegister::getNofFceArgs(TypeID id)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::FCE::NOF_ARGUMENTS);
}

TypeRegister::TypeID TypeRegister::getFceArgTypeId(TypeID id,unsigned element)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::FCE::ARGUMENTS_START+element);
}

unsigned TypeRegister::getObjSize(TypeID id)const{
  return this->getTypeDescriptionElem(id,TypeRegister::POSITION::OBJ::SIZE);
}

bool TypeRegister::_incrCheck(std::vector<unsigned>::size_type size,std::vector<unsigned>::size_type&start){
  start++;
  return start<size;
}

bool TypeRegister::_isNewTypeEqualTo(TypeID et,std::vector<unsigned>const&type,std::vector<unsigned>::size_type&start){
  //std::cout<<"TypeRegister::_isNewTypeEqualTo("<<et<<","<<vec2str(type)<<","<<start<<")"<<std::endl;
  if(start>=type.size())return false;
  std::vector<unsigned>::size_type lastStart=start;
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
      if(!this->_incrCheck((unsigned)type.size(),start))                    return falseBranch();
      if(!this->_isNewTypeEqualTo(this->getArrayInnerTypeId(et),type,start))return falseBranch();
      return true;
    case TypeRegister::STRUCT:
      if(!this->_incrCheck(type.size(),start))          return falseBranch();
      if(this->getNofStructElements(et)!=type[start])   return falseBranch();
      if(!this->_incrCheck((unsigned)type.size(),start))return falseBranch();
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
      if(!this->_incrCheck((unsigned)type.size(),start))                   return falseBranch();
      for(unsigned e=0;e<this->getNofFceArgs(et);++e)
        if(!this->_isNewTypeEqualTo(this->getFceArgTypeId(et,e),type,start))return falseBranch();
      return true;
    case TypeRegister::OBJ:
      //std::cerr<<"OBJ isNewType"<<std::endl;
      return falseBranch();
    default:
      return falseBranch();
  }
}

bool TypeRegister::_typeExists(TypeRegister::TypeID*id,std::vector<unsigned>const&type,std::vector<unsigned>::size_type&start){
  for(unsigned t=0;t<this->getNofTypes();++t)
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

TypeRegister::TypeID TypeRegister::_typeAdd(std::vector<unsigned>const&type,std::vector<unsigned>::size_type&start){
  std::vector<unsigned>::size_type lastStart=start;
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
      this->_typeStart.push_back((unsigned)this->_types.size());
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
      this->_typeStart.push_back((unsigned)this->_types.size());
      this->_types.push_back(newType);//write type
      this->_types.push_back(size);//write length
      this->_types.push_back(innerTypes[0]);//write inner type
      return this->getTypeId(this->getNofTypes()-1);
    case TypeRegister::STRUCT:
      if(start+1>=type.size())return err("new struct type has no size");
      start+=2;
      size=type[start-1];
      if(size==0)return err("number of structs elements cannot be zero");
      for(unsigned e=0;e<size;++e){
        TypeRegister::TypeID id=this->_typeAdd(type,start);
        if(id==0)return err("new structs element number: "+getStr(e)+" has invalid format");
        innerTypes.push_back(id);
      }
      if(innerTypes.size()!=size)return err("new struct has "+getStr(size)+" elements by only "+getStr(innerTypes.size())+" elements were provided");
      this->_typeStart.push_back((unsigned)this->_types.size());
      this->_types.push_back(newType);//write type
      this->_types.push_back(size);//write length
      for(unsigned e=0;e<size;++e)
        this->_types.push_back(innerTypes[e]);
      return this->getTypeId(this->getNofTypes()-1);
    case TypeRegister::PTR:
      start+=1;
      innerTypes.push_back(this->_typeAdd(type,start));
      if(innerTypes[0]==0)return err("new ptrs inner type has invalid format");
      this->_typeStart.push_back((unsigned)this->_types.size());
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
      this->_typeStart.push_back((unsigned)this->_types.size());
      this->_types.push_back(newType);//write type
      this->_types.push_back(innerTypes[0]);//write return type
      this->_types.push_back(size);//write length
      for(unsigned e=0;e<size;++e)//write args
        this->_types.push_back(innerTypes[1+e]);
      return this->getTypeId(this->getNofTypes()-1);
    case TypeRegister::OBJ:
      if(start+1>=type.size())return err("new OBJ has no size");
      size=type[start+1];
      this->_typeStart.push_back((unsigned)this->_types.size());
      this->_types.push_back(newType);//write type
      this->_types.push_back(size);//write size
      start++;
      return this->getTypeId(this->getNofTypes()-1);
    default:
      return err("what a stupid day...");
  }
}

void TypeRegister::_bindTypeIdName(TypeID id,std::string name){
  //std::cout<<"TypeRegister::_bindTypeIdName("<<id<<","<<name<<")"<<std::endl;
  this->_name2Id[name] = id  ;
  if(!this->_id2name.count(id)){
    this->_id2name[id  ] = name;
    this->_id2Synonyms[id]=std::set<std::string>();
  }
  this->_id2Synonyms[id].insert(name);
}

TypeRegister::TypeID TypeRegister::addType(std::string name,std::vector<unsigned>const&type,std::function<OBJConstructor> constructor,std::function<OBJDestructor> destructor){
  //std::cerr<<"TypeRegister::addType(\""<<name<<"\","<<vec2str(type)<<");"<<std::endl;
  std::vector<unsigned>::size_type start=0;
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
  //std::cerr<<"pridavam constructor k: "<<this->getTypeIdName(id)<<"ktery existuje? "<<(!constructor?"ne":"ano")<<std::endl;
  if(!constructor){
    this->_id2Constructor.erase(id);
    return;
  }
  this->_id2Constructor[id]=constructor;
}

void TypeRegister::addDestructor(TypeID id,std::function<OBJDestructor> destructor){
  //std::cerr<<"pridavam destructor k: "<<this->getTypeIdName(id)<<"ktery existuje? "<<(!destructor?"ne":"ano")<<std::endl;
  if(!destructor){
    this->_id2Destructor[id]=nullptr;//.erase(id);
    return;
  }
  this->_id2Destructor[id]=destructor;
}

unsigned TypeRegister::computeTypeIdSize(TypeID id)const{
  TypeRegister::Type type=this->getTypeIdType(id);
  unsigned size=0;
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
                              for(unsigned e=0;e<this->getNofStructElements(id);++e)
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
  //std::cerr<<"TypeRegister::_callConstructors: "<<id<<" "<<this->getTypeIdType(id)<<std::endl;
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
  unsigned size=this->computeTypeIdSize(id);
  void*ptr=(void*)(new char[size]);
  this->_callConstructors((char*)ptr,id);
  return ptr;
}

Accessor TypeRegister::allocAccessor(TypeID id)const{
  return Accessor(this->shared_from_this(),this->alloc(id),id);
}

Accessor TypeRegister::allocAccessor(std::string name)const{
  return this->allocAccessor(this->getTypeId(name));
}

std::shared_ptr<Accessor>TypeRegister::sharedAccessor(TypeID id)const{
  return std::make_shared<Accessor>(this->shared_from_this(),this->alloc(id),id);
}

std::shared_ptr<Accessor>TypeRegister::sharedAccessor(std::string name)const{
  return this->sharedAccessor(this->getTypeId(name));
}

Accessor TypeRegister::emptyAccessor(TypeID id)const{
  return Accessor(this->shared_from_this(),id);
}

Accessor TypeRegister::emptyAccessor(std::string name)const{
  return this->emptyAccessor(this->getTypeId(name));
}

std::shared_ptr<Accessor>TypeRegister::sharedEmptyAccessor(TypeID id,std::function<OBJDestructor>destructor)const{
  if(destructor)
    return std::shared_ptr<Accessor>(new Accessor(this->shared_from_this(),id),[destructor](Accessor*ac){destructor((unsigned char*)ac->getData());delete ac;});
  //return std::shared_ptr<Accessor>(new Accessor(this->shared_from_this(),id),[](Accessor*ac){ac->free();delete ac;});
  return std::make_shared<Accessor>(this->shared_from_this(),id);
}

std::shared_ptr<Accessor>TypeRegister::sharedEmptyAccessor(std::string name,std::function<OBJDestructor>destructor)const{
  return this->sharedEmptyAccessor(this->getTypeId(name),destructor);
}


void TypeRegister::destroyUsingCustomDestroyer(unsigned char*ptr,TypeID id)const{
  //std::cerr<<"volam destroyUsingCustomDestroyer"<<std::endl;
  std::map<TypeID,std::function<OBJDestructor>>::const_iterator ii=this->_id2Destructor.find(id);
  if(ii!=this->_id2Destructor.end()){
    //std::cerr<<"mam customDeleter"<<std::endl;
    ii->second(ptr);
  }
}

void TypeRegister::constructUsingCustomConstructor(signed char*ptr,TypeID id)const{
  std::map<TypeID,std::function<OBJConstructor>>::const_iterator ii=this->_id2Constructor.find(id);
  if(ii!=this->_id2Constructor.end()){
    ii->second(ptr);
  }
}

std::vector<unsigned>::size_type TypeRegister::getNofDescriptionUints()const{
  return this->_types.size();
}

unsigned TypeRegister::getDescription(unsigned i)const{
  return this->_types[i];
}


Accessor::Accessor(Accessor const& ac){
  this->_manager = ac._manager;
  this->_data    = ac._data   ;
  this->_id      = ac._id     ;
  this->_offset  = ac._offset ;
}

Accessor::Accessor(
    std::shared_ptr<const TypeRegister>const&manager,
    const void*                              data   ,
    TypeRegister::TypeID                     id     ,
    unsigned                                 offset ){
  this->_manager =        manager;
  this->_id      =        id     ;
  this->_data    = std::shared_ptr<char>((char*)data,[id,manager](char*ptr){Accessor::_callDestructors(ptr,id,manager);delete[]ptr;});
  this->_offset  =        offset ;
}

Accessor::Accessor(
    std::shared_ptr<const TypeRegister>const&manager,
    std::shared_ptr<char>const&              data   ,
    TypeRegister::TypeID                     id     ,
    unsigned                                 offset ){
  this->_manager = manager;
  this->_data    = data   ;
  this->_id      = id     ;
  this->_offset  = offset ;
}

Accessor::Accessor(
    std::shared_ptr<const TypeRegister>const&manager,
    TypeRegister::TypeID               id           ){
  this->_manager = manager;
  this->_data    = nullptr;
  this->_id      = id     ;
  this->_offset  = 0      ;
}

Accessor::~Accessor(){
}

std::shared_ptr<const TypeRegister>Accessor::getManager()const{
  return this->_manager;
}

void*Accessor::getData()const{
  return (char*)&(*this->_data)+this->_offset;
}

TypeRegister::TypeID Accessor::getId()const{
  return this->_id;
}

Accessor Accessor::operator[](unsigned elem)const{
  TypeRegister::TypeID innerType = 0;
  unsigned            offset    = 0;
  switch(this->getManager()->getTypeIdType(this->_id)){
    case TypeRegister::ARRAY :
      innerType = this->getManager()->getArrayInnerTypeId(this->getId());
      offset    = this->getManager()->computeTypeIdSize(innerType)*elem;
      return Accessor(this->getManager(),this->_data,innerType,offset);
    case TypeRegister::STRUCT:
      innerType = this->getManager()->getStructElementTypeId(this->getId(),elem);
      for(unsigned i=0;i<elem;++i)
        offset += this->getManager()->computeTypeIdSize(this->getManager()->getStructElementTypeId(this->getId(),i));
      return Accessor(this->getManager(),this->_data,innerType,offset);
    default:
      return Accessor(this->getManager(),this->_data,this->getId());
  }
}

unsigned Accessor::getNofElements()const{
  switch(this->_id){
    case TypeRegister::ARRAY :
      return this->getManager()->getArraySize(this->getId());
    case TypeRegister::STRUCT:
      return this->getManager()->getNofStructElements(this->getId());
    default                 :
      return 0;
  }
}

void Accessor::_callDestructors(char*ptr,TypeRegister::TypeID id,std::shared_ptr<const TypeRegister>const&manager){
  TypeRegister::Type type=manager->getTypeIdType(id);
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
                              ((std::string*)ptr)->~basic_string();
                              break;
    case TypeRegister::ARRAY:
                              for(unsigned i=0;i<manager->getArraySize(id);++i)
                                Accessor::_callDestructors(ptr+manager->computeTypeIdSize(manager->getArrayInnerTypeId(id))*i,manager->getArrayInnerTypeId(id),manager);
                              break;
    case TypeRegister::STRUCT:
                              for(unsigned e=0;e<manager->getNofStructElements(id);++e){
                                Accessor::_callDestructors(ptr,manager->getStructElementTypeId(id,e),manager);
                                ptr+=manager->computeTypeIdSize(manager->getStructElementTypeId(id,e));
                              }
                              break;
    case TypeRegister::FCE:
                              ((std::shared_ptr<ge::core::Function>*)ptr)->~shared_ptr();
                              //TODO CO S FUNKCI
                              break;
    case TypeRegister::OBJ:
                              manager->destroyUsingCustomDestroyer((unsigned char*)ptr,id);
                              break;
    default:
                              break;
  }
}

const void*Accessor::getPointer()const{
  return (void*)this->getData();
}

std::string Accessor::data2Str()const{
  TypeRegister::Type type=this->_manager->getTypeIdType(this->_id);
  std::stringstream ss;
  bool first;
  switch(type){
    case TypeRegister::VOID  :
      break;
    case TypeRegister::BOOL  :
      ss<<((bool)(*this)?"true":"false");
      break;
    case TypeRegister::I8    :
      ss<<(int)(char)(*this);
      break;
    case TypeRegister::I16   :
      ss<<(short)(*this);
      break;
    case TypeRegister::I32   :
      ss<<(int)(*this);
      break;
    case TypeRegister::I64   :
      ss<<(long long int)(*this);
      break;
    case TypeRegister::U8    :
      ss<<(unsigned)(unsigned char)(*this);
      break;
    case TypeRegister::U16   :
      ss<<(unsigned short)(*this);
      break;
    case TypeRegister::U32   :
      ss<<(unsigned)(*this);
      break;
    case TypeRegister::U64   :
      ss<<(unsigned long long)(*this);
      break;
    case TypeRegister::F32   :
      ss<<(float)(*this);
      break;
    case TypeRegister::F64   :
      ss<<(double)(*this);
      break;
    case TypeRegister::PTR   :
      ss<<(void*)(*this);
      break;
    case TypeRegister::STRING:
      ss<<(std::string&)(*this);
      break;
    case TypeRegister::ARRAY:
      ss<<"[";
      first=true;
      for(unsigned i=0;i<this->_manager->getArraySize(this->_id);++i){
        if(first)first=false;
        else ss<<",";
        ss<<((*this)[i]).data2Str();
      }
      ss<<"]";
      break;
    case TypeRegister::STRUCT:
      ss<<"{";
      first=true;
      for(unsigned e=0;e<this->_manager->getNofStructElements(this->_id);++e){
        if(first)first=false;
        else ss<<",";
        ss<<((*this)[e]).data2Str();
      }
      ss<<"}";
      break;
    case TypeRegister::FCE:
      break;
    case TypeRegister::OBJ:
      break;
    default:
      break;
  }
  return ss.str();
}

void Accessor::callDestructor(){
  this->_callDestructors(&*this->_data,this->_id,this->_manager);
}
