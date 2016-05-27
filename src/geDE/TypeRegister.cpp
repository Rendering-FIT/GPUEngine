#include<geDE/TypeRegister.h>

#include<geDE/AtomicResource.h>
#include<sstream>
#include<memory>
#include<cassert>
#include<cstring>
#include<vector>

using namespace ge::de;

class Function;

std::ostream& operator<<(std::ostream& out,int8_t* const& f){
  return out << (void*)f;
}
std::ostream& operator<<(std::ostream& out,uint8_t* const& f){
  return out << (void*)f;
}

template<typename...ARGS>
std::string argsToStr(ARGS...);

template<typename F,typename...ARGS>
std::string argsToStr_help(F const&a,ARGS...args){
  std::stringstream ss;
  ss<<a;
  if(sizeof...(args)>0)
    ss<<","<<argsToStr(args...);
  return ss.str();
}

template<typename...ARGS>
std::string argsToStr(ARGS...args){
  return argsToStr_help(args...);
}

template<>std::string argsToStr(){
  return "";
}

int indentCounter = 0;
std::string indent = "";
class iii{
  public:
    template<typename...ARGS>
    iii(std::string fceName,ARGS...args){
      std::cout<<indent<<fceName<<"("<<argsToStr(args...)<<"){"<<std::endl;
      indentCounter+=2;
      indent="";
      for(int i=0;i<indentCounter;++i)
        indent+=" ";
    }
    ~iii(){
      indentCounter-=2;
      if(indentCounter<0)
        indentCounter=0;
      indent="";
      for(int i=0;i<indentCounter;++i)
        indent+=" ";
      std::cout<<indent<<"}"<<std::endl;
    }
};

//#define PRINT_CALL_STACK(...)iii superduperhidden(__VA_ARGS__)
#define PRINT_CALL_STACK(...)

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

class TypeRegister::TypeDescription{
  public:
    TypeType type;
    TypeDescription(TypeType const&type){
      this->type = type;
    }
    virtual ~TypeDescription(){}
    virtual bool init(
        TypeRegister           *tr         ,
        DescriptionVector const&description,
        size_t                 &i          ,
        bool                    exists     ) = 0;
    virtual std::string toStr(TypeRegister const*,TypeId)const = 0;
    virtual bool equal(TypeDescription const*other)const = 0;
    TypeId findInRegister(
        TypeRegister           *tr         ,
        DescriptionVector const&description,
        size_t                 &i          ){
      assert(this!=nullptr);
      size_t old = i;
      if(!this->init(tr,description,i,true))return UNREGISTERED;
      TypeId index = 0;
      for(auto const&x:tr->_types){
        if(x->equal(this))
          return tr->_vectorIndex2TypeId(index);
        index++;
      }
      i = old;
      return UNREGISTERED;
    }
    virtual void callConstructor(TypeRegister*tr,void*ptr)const = 0;
    virtual void callDestructor(TypeRegister*tr,void*ptr)const = 0;
    virtual size_t byteSize(TypeRegister const*tr)const = 0;

    static TypeId checkAndBindType(
        TypeRegister     *tr,
        std::string const&name,
        DescriptionVector const&description,
        TypeDescription*d,
        size_t &i){
      size_t old = i;
      if(!d->init(tr,description,i,false)){
        delete d;
        return UNREGISTERED;
      }
      auto id = tr->_vectorIndex2TypeId(tr->_types.size());
      auto ii = tr->_name2TypeId.find(name);
      if(ii != tr->_name2TypeId.end()){
        std::cerr<<"ERROR: TypeDescription::checkAndBindType() - ";
        std::cerr<<"name "<<name<<" is already used with different type: "<<ii->second<<" aka "<<ii->first;
        std::cerr<<std::endl;
        i=old;
        delete d;
        return UNREGISTERED;
      }
      tr->_types.push_back(d);
      tr->_bindTypeIdWithName(id,name);
      return id;
    }

};

class TypeRegister::ArrayDescription: public TypeDescription{
  public:
    size_t size;
    TypeId elementType;
    ArrayDescription(
        TypeId const&elementType,
        size_t const&size       ):TypeDescription(ARRAY){
      this->elementType = elementType;
      this->size = size;
    }
    ArrayDescription():TypeDescription(ARRAY){}
    virtual bool init(
        TypeRegister*           tr         ,
        DescriptionVector const&description,
        size_t                 &i          ,
        bool                    exists     )override{
      assert(this!=nullptr);
      size_t old = i;
      if(i>=description.size()){
        if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Array description is empty"<<std::endl;
        i=old;
        return false;
      }
      if(description[i++]!=ARRAY){
        if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Array description does not start with ARRAY"<<std::endl;
        i=old;
        return false;
      }
      if(i>=description.size()){
        if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Array description does not contain size"<<std::endl;
        i=old;
        return false;
      }
      this->size = description[i++];
      if(exists)
        this->elementType = tr->_typeExists(description,i);
      else
        this->elementType = tr->_addType("",description,i);
      if(elementType == UNREGISTERED){i=old;return UNREGISTERED;}
      return true;
    }
    virtual ~ArrayDescription(){}
    bool operator==(ArrayDescription const&other)const{
      assert(this!=nullptr);
      return this->size == other.size && this->elementType == other.elementType;
    }
    virtual bool equal(TypeDescription const*other)const override{
      assert(this!=nullptr);
      if(this->type != other->type)return false;
      return *this==*(ArrayDescription*)other;
    }
    virtual std::string toStr(TypeRegister const*tr,TypeId)const override{
      assert(this!=nullptr);
      std::stringstream ss;
      ss<<"["<<this->size<<","<<tr->type2Str(tr->_typeId2VectorIndex(this->elementType))<<"]";
      return ss.str();
    }
    virtual void callConstructor(TypeRegister*tr,void*ptr)const override{
      PRINT_CALL_STACK("ArrayDescription::callConstructor",tr,ptr);
      assert(this!=nullptr);
      size_t elementSize = tr->computeTypeIdSize(this->elementType);
      for(size_t i=0;i<this->size;++i)
        tr->_callConstructors((uint8_t*)ptr+elementSize*i,this->elementType);
    }
    virtual void callDestructor(TypeRegister*tr,void*ptr)const override{
      PRINT_CALL_STACK("ArrayDescription::callDestructor",tr,ptr);
      assert(this!=nullptr);
      size_t elementSize = tr->computeTypeIdSize(this->elementType);
      for(size_t i=0;i<this->size;++i)
        tr->_callDestructors((uint8_t*)ptr+elementSize*i,this->elementType);
    }
    virtual size_t byteSize(TypeRegister const*tr)const override{
      PRINT_CALL_STACK("ArrayDescription::byteSize",tr);
      assert(this!=nullptr);
      return this->size*tr->computeTypeIdSize(this->elementType);
    }
};

class TypeRegister::StructDescription: public TypeDescription{
  public:
    std::vector<TypeId>elementTypes;
    StructDescription(
        std::vector<TypeId>const&elementTypes):TypeDescription(STRUCT){
      this->elementTypes = elementTypes;
    }
    StructDescription():TypeDescription(STRUCT){}
    virtual bool init(
        TypeRegister*           tr         ,
        DescriptionVector const&description,
        size_t                 &i          ,
        bool                    exists     )override{
      assert(this!=nullptr);
      size_t old = i;
      if(i>=description.size()){
        if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Struct description is empty"<<std::endl;
        i=old;
        return false;
      }
      if(description[i++]!=STRUCT){
        if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Struct description does not start with STRUCT"<<std::endl;
        i=old;
        return false;
      }
      if(i>=description.size()){
        if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Struct description does not contain size"<<std::endl;
        i=old;
        return false;
      }
      size_t size = description[i++];
      for(size_t e=0;e<size;++e){
        if(exists)
          this->elementTypes.push_back(tr->_typeExists(description,i));
        else
          this->elementTypes.push_back(tr->_addType("",description,i));
        if(this->elementTypes.back() == UNREGISTERED){i=old;return false;}
      }
      return true;
    }
    virtual ~StructDescription(){}
    bool operator==(StructDescription const&other)const{
      assert(this!=nullptr);
      return this->elementTypes == other.elementTypes;
    }
    virtual bool equal(TypeDescription const*other)const override{
      assert(this!=nullptr);
      if(this->type != other->type)return false;
      return *this==*(StructDescription*)other;
    }
    virtual std::string toStr(TypeRegister const*tr,TypeId)const override{
      assert(this!=nullptr);
      std::stringstream ss;
      ss<<"struct{";
      bool first=true;
      for(auto const&x:this->elementTypes){
        if(first)first = false;
        else ss<<",";
        ss<<tr->type2Str(tr->_typeId2VectorIndex(x));
      }
      ss<<"}";
      return ss.str();
    }
    virtual void callConstructor(TypeRegister*tr,void*ptr)const override{
      PRINT_CALL_STACK("StructDescription::callConstructor",tr,ptr);
      assert(this!=nullptr);
      size_t offset = 0;
      for(auto const&x:this->elementTypes){
        tr->_callConstructors((uint8_t*)ptr+offset,x);
        offset += tr->computeTypeIdSize(x);
      }
    }
    virtual void callDestructor(TypeRegister*tr,void*ptr)const override{
      PRINT_CALL_STACK("StructDescription::callDestructor",tr,ptr);
      assert(this!=nullptr);
      size_t offset = 0;
      for(auto const&x:this->elementTypes){
        tr->_callDestructors((uint8_t*)ptr+offset,x);
        offset += tr->computeTypeIdSize(x);
      }
    }
    virtual size_t byteSize(TypeRegister const*tr)const override{
      PRINT_CALL_STACK("StructDescription::byteSize",tr);
      assert(this!=nullptr);
      size_t size = 0;
      for(auto const&x:this->elementTypes)
        size+=tr->computeTypeIdSize(x);
      return size;
    }
};

class TypeRegister::FunctionDescription: public TypeDescription{
  public:
    std::vector<TypeId>argumentTypes;
    TypeId returnType;
    FunctionDescription(
        TypeId             const&returnType   ,
        std::vector<TypeId>const&argumentTypes):TypeDescription(FCE){
      this->returnType = returnType;
      this->argumentTypes = argumentTypes;
    }
    FunctionDescription():TypeDescription(FCE){}
    virtual bool init(
        TypeRegister*           tr         ,
        DescriptionVector const&description,
        size_t                 &i          ,
        bool                    exists     )override{
      assert(this!=nullptr);
      size_t old = i;
      if(i>=description.size()){
        if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Function description is empty"<<std::endl;
        i=old;
        return false;
      }
      if(description[i++]!=FCE){
        if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Function description does not start with FCE"<<std::endl;
        i=old;
        return false;
      }
      if(exists)
        this->returnType = tr->_typeExists(description,i);
      else
        this->returnType = tr->_addType("",description,i);
      if(returnType == UNREGISTERED){
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
        if(this->argumentTypes.back() == UNREGISTERED){i=old;return false;}
      }
      return true;
    }
    virtual ~FunctionDescription(){}
    bool operator==(FunctionDescription const&other)const{
      assert(this!=nullptr);
      return 
        this->returnType == other.returnType && 
        this->argumentTypes == other.argumentTypes;
    }
    virtual bool equal(TypeDescription const*other)const override{
      assert(this!=nullptr);
      if(this->type != other->type)return false;
      return *this==*(FunctionDescription*)other;
    }
    virtual std::string toStr(TypeRegister const*tr,TypeId)const override{
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
    virtual void callConstructor(TypeRegister*,void*ptr)const override{
      PRINT_CALL_STACK("FunctionDescription::callConstructor",ptr);
      new(ptr)std::shared_ptr<Function>();
    }
    virtual void callDestructor(TypeRegister*,void*ptr)const override{
      PRINT_CALL_STACK("FunctionDescription::callDestructor",ptr);
      ((std::shared_ptr<Function>*)ptr)->~shared_ptr();
    }
    virtual size_t byteSize(TypeRegister const*)const override{
      PRINT_CALL_STACK("FunctionDescription::byteSize");
      return sizeof(std::shared_ptr<FunctionDescription>);
    }

};

class TypeRegister::AtomicDescription: public TypeDescription{
  public:
    size_t size;
    Destructor destructor;
    Constructor constructor;
    AtomicDescription(
        size_t      const&size                 ,
        Destructor  const&destructor  = nullptr,
        Constructor const&constructor = nullptr):TypeDescription(ATOMIC){
      this->size = size;
      this->destructor  = destructor;
      this->constructor = constructor;
    }
    virtual ~AtomicDescription(){}
    virtual bool init(
        TypeRegister*           ,
        DescriptionVector const&,
        size_t                 &,
        bool                    )override{return true;}
    bool operator==(AtomicDescription const&other)const{
      assert(this!=nullptr);
      return this->size == other.size &&
        this->destructor == other.destructor &&
        this->constructor == other.constructor;
    }
    virtual bool equal(TypeDescription const*other)const override{
      assert(this!=nullptr);
      if(this->type != other->type)return false;
      return *this==*(AtomicDescription*)other;
    }
    virtual std::string toStr(TypeRegister const*tr,TypeId id)const override{
      assert(this!=nullptr);
      assert(tr->_typeId2Synonyms.count(id)!=0);
      std::stringstream ss;
      ss<<*tr->_typeId2Synonyms.find(id)->second.begin();
      return ss.str();
    }
    virtual void callConstructor(TypeRegister*,void*ptr)const override{
      PRINT_CALL_STACK("AtomicDescription::callConstructor",ptr);
      assert(this!=nullptr);
      if(this->constructor)this->constructor(ptr);
    }
    virtual void callDestructor(TypeRegister*,void*ptr)const override{
      PRINT_CALL_STACK("AtomicDescription::callDestructor",ptr);
      assert(this!=nullptr);
      if(this->destructor)this->destructor(ptr);
    }
    virtual size_t byteSize(TypeRegister const*)const override{
      PRINT_CALL_STACK("AtomicDescription::byteSize");
      assert(this!=nullptr);
      return this->size;
    }

};

class TypeRegister::AutoDescription: public TypeDescription{
  public:
    AutoDescription():TypeDescription(AUTO){
    }
    virtual ~AutoDescription(){}
    virtual bool init(
        TypeRegister*           ,
        DescriptionVector const&description,
        size_t                 &i,
        bool                    )override{
      if(i>=description.size())return false;
      if(description[i]!=AUTO)return false;
      i++;
      return true;
    }
    bool operator==(AutoDescription const&)const{
      return true;
    }
    virtual bool equal(TypeDescription const*other)const override{
      assert(this!=nullptr);
      if(this->type != other->type)return false;
      return *this==*(AutoDescription*)other;
    }
    virtual std::string toStr(TypeRegister const*tr,TypeId id)const override{
      assert(this!=nullptr);
      assert(tr->_typeId2Synonyms.count(id)!=0);
      std::stringstream ss;
      ss<<*tr->_typeId2Synonyms.find(id)->second.begin();
      return ss.str();
    }
    virtual void callConstructor(TypeRegister*,void*)const override{};
    virtual void callDestructor(TypeRegister*,void*)const override{};
    virtual size_t byteSize(TypeRegister const*)const override{
      PRINT_CALL_STACK("AtomicDescription::byteSize");
      return 0;
    }

};

TypeRegister::TypeRegister(){
  this->addCompositeType(TypeRegister::getTypeKeyword<TypeRegister::Auto>(),{AUTO});
  this->addAtomicType(TypeRegister::getTypeKeyword<void       >(),0                  );
  this->addAtomicType(TypeRegister::getTypeKeyword<bool       >(),sizeof(bool       ));
  this->addAtomicType(TypeRegister::getTypeKeyword<int8_t     >(),sizeof(int8_t     ));
  this->addAtomicType(TypeRegister::getTypeKeyword<int16_t    >(),sizeof(int16_t    ));
  this->addAtomicType(TypeRegister::getTypeKeyword<int32_t    >(),sizeof(int32_t    ));
  this->addAtomicType(TypeRegister::getTypeKeyword<int64_t    >(),sizeof(int64_t    ));
  this->addAtomicType(TypeRegister::getTypeKeyword<uint8_t    >(),sizeof(uint8_t    ));
  this->addAtomicType(TypeRegister::getTypeKeyword<uint16_t   >(),sizeof(uint16_t   ));
  this->addAtomicType(TypeRegister::getTypeKeyword<uint32_t   >(),sizeof(uint32_t   ));
  this->addAtomicType(TypeRegister::getTypeKeyword<uint64_t   >(),sizeof(uint64_t   ));
  this->addAtomicType(TypeRegister::getTypeKeyword<float      >(),sizeof(float      ));
  this->addAtomicType(TypeRegister::getTypeKeyword<double     >(),sizeof(double     ));
  this->addAtomicType(TypeRegister::getTypeKeyword<std::string>(),sizeof(std::string),[](void*ptr){new(ptr)std::string();},[](void*ptr){((std::string*)ptr)->~basic_string();});

}

TypeRegister::~TypeRegister(){
  assert(this!=nullptr);
  for(auto const&x:this->_types)
    delete x;
}


TypeRegister::TypeId TypeRegister::addAtomicType(
    std::string const&name       ,
    size_t      const&size       ,
    Constructor const&constructor,
    Destructor  const&destructor ){
  assert(this!=nullptr);
  auto ii = this->_name2TypeId.find(name);
  if(ii!=this->_name2TypeId.end()){
    TypeId id = ii->second;
    auto index = this->_typeId2VectorIndex(id);
    assert(index<this->_types.size());
    auto type = (AtomicDescription*)this->_types[index];
    if(type->size != size)return UNREGISTERED;
    if(
        type->destructor != nullptr &&
        destructor       != nullptr && 
        type->destructor != destructor)return UNREGISTERED;
    if(
        type->constructor != nullptr &&
        constructor       != nullptr &&
        type->constructor != constructor)return UNREGISTERED;
    if(destructor)type->destructor = destructor;
    if(constructor)type->constructor = constructor;
    return id;
  }
  TypeId index = 0;
  for(auto const&x:this->_types){
    if(x->type != ATOMIC){
      index++;
      continue;
    }
    auto type = (AtomicDescription*)x;
    if(
        type->size == size &&
        type->destructor != nullptr &&
        type->constructor != nullptr &&
        type->destructor == destructor &&
        type->constructor == constructor){
      TypeId id = this->_vectorIndex2TypeId(index);
      assert(id<this->_typeId2Synonyms.size());
      if(name!="")this->_typeId2Synonyms[id].insert(name);
      return id;
    }
    index++;
  }
  TypeId id = this->_vectorIndex2TypeId(this->_types.size());
  this->_types.push_back(new AtomicDescription(size,destructor,constructor));
  this->_bindTypeIdWithName(id,name);
  return id;
}

void TypeRegister::_bindTypeIdWithName(TypeId id,std::string const&name){
  assert(this!=nullptr);
  if(name==""){
    std::stringstream ss;
    ss<<"type"<<id;
    this->_typeId2Synonyms[id].insert(ss.str());
    this->_name2TypeId[ss.str()]=id;
    return;
  }
  this->_typeId2Synonyms[id].insert(name);
  this->_name2TypeId[name]=id;
}

TypeRegister::TypeId TypeRegister::_typeExists(
    DescriptionVector const&description,
    size_t                 &i){
  assert(this!=nullptr);
  if(i>=description.size())return UNREGISTERED;
  switch(description[i]){
    case UNREGISTERED:return UNREGISTERED;
    case ATOMIC      :return UNREGISTERED;
    case ARRAY       :{ArrayDescription    desc;return desc.findInRegister(this,description,i);}
    case STRUCT      :{StructDescription   desc;return desc.findInRegister(this,description,i);}
    case FCE         :{FunctionDescription desc;return desc.findInRegister(this,description,i);}
    case AUTO        :{AutoDescription     desc;return desc.findInRegister(this,description,i);}
    default          :return this->_typeIdExists(description,i);
  }
}

TypeRegister::TypeId TypeRegister::_typeIdExists(
    DescriptionVector const&description,
    size_t                 &i){
  assert(this!=nullptr);
  if(i>=description.size())return UNREGISTERED;
  if(description[i]<TYPEID)return UNREGISTERED;
  if(this->_typeId2VectorIndex(description[i])>=this->_types.size())
    return UNREGISTERED;
  return description[i++];
}

TypeRegister::TypeId TypeRegister::addCompositeType(
    std::string        const&name       ,
    DescriptionVector  const&description){
  assert(this!=nullptr);
  size_t i=0;
  return this->_addType(name,description,i);
}

TypeRegister::TypeId TypeRegister::_addType(
    std::string       const&name       ,
    DescriptionVector const&description,
    size_t                 &i          ){
  assert(this!=nullptr);
  size_t old = i;
  auto id = this->_typeExists(description,i);
  if(id != UNREGISTERED){
    auto ii = this->_name2TypeId.find(name);
    if(ii != this->_name2TypeId.end()){
      if(ii->second != id){
        std::cerr<<"ERROR: TypeRegister::_addType() - ";
        std::cerr<<"name "<<name<<" is already used with different type: "<<ii->second;
        std::cerr<<std::endl;
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
    case AUTO        :return TypeDescription::checkAndBindType(this,name,description,new AutoDescription    (),i);
    case ARRAY       :return TypeDescription::checkAndBindType(this,name,description,new ArrayDescription   (),i);
    case STRUCT      :return TypeDescription::checkAndBindType(this,name,description,new StructDescription  (),i);
    case FCE         :return TypeDescription::checkAndBindType(this,name,description,new FunctionDescription(),i);
    default          :return this->_addTypeId(name,description,i);
  }
}

TypeRegister::TypeId TypeRegister::_addTypeId(
    std::string       const&name       ,
    DescriptionVector const&description,
    size_t                 &i          ){
  assert(this!=nullptr);
  if(i>=description.size())return UNREGISTERED;
  if(description[i]<TYPEID)return UNREGISTERED;
  if(this->_typeId2VectorIndex(description[i])>=this->_types.size())return UNREGISTERED;
  if(name!=""){
    auto ii = this->_name2TypeId.find(name);
    if(ii != this->_name2TypeId.end()){
      if(ii->second != description[i]){
        std::cerr<<"ERROR: TypeRegister::_addTypeId() - ";
        std::cerr<<"name "<<name<<" is already used with different type: "<<ii->second<<" aka "<<ii->first;
        std::cerr<<std::endl;
        return UNREGISTERED;
      }
      return description[i++];
    }
    this->_bindTypeIdWithName(description[i],name);
  }
  return description[i++];
}

TypeRegister::TypeId TypeRegister::_vectorIndex2TypeId(TypeId const&index)const{
  return index+TYPEID;
}

TypeRegister::TypeId TypeRegister::_typeId2VectorIndex(TypeId const&id)const{
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
  //std::cout<<indent<<"getTypeIdType("<<id<<")"<<std::endl;
  PRINT_CALL_STACK("TypeRegister::getTypeIdType",id);
  assert(this!=nullptr);
  return this->_getDescription(id)->type;
}

size_t TypeRegister::getNofStructElements(TypeId id)const{
  assert(this!=nullptr);
  assert((StructDescription*)this->_getDescription(id)!=nullptr);
  return ((StructDescription*)this->_getDescription(id))->elementTypes.size();
}

TypeRegister::TypeId TypeRegister::getStructElementTypeId(TypeId id,size_t index)const{
  assert(this!=nullptr);
  assert((StructDescription*)this->_getDescription(id)!=nullptr);
  assert(index<((StructDescription*)this->_getDescription(id))->elementTypes.size());
  return ((StructDescription*)this->_getDescription(id))->elementTypes[index];
}

size_t TypeRegister::getArraySize(TypeId id)const{
  assert(this!=nullptr);
  assert((ArrayDescription*)this->_getDescription(id)!=nullptr);
  return ((ArrayDescription*)this->_getDescription(id))->size;
}

TypeRegister::TypeId TypeRegister::getArrayElementTypeId(TypeId id)const{
  assert(this!=nullptr);
  assert((ArrayDescription*)this->_getDescription(id)!=nullptr);
  return ((ArrayDescription*)this->_getDescription(id))->elementType;
}

TypeRegister::TypeId TypeRegister::getFceReturnTypeId(TypeId id)const{
  assert(this!=nullptr);
  assert((FunctionDescription*)this->_getDescription(id)!=nullptr);
  return ((FunctionDescription*)this->_getDescription(id))->returnType;
}

size_t TypeRegister::getNofFceArgs(TypeId id)const{
  assert(this!=nullptr);
  assert((FunctionDescription*)this->_getDescription(id)!=nullptr);
  return ((FunctionDescription*)this->_getDescription(id))->argumentTypes.size();
}

TypeRegister::TypeId TypeRegister::getFceArgTypeId(TypeId id,size_t index)const{
  assert(this!=nullptr);
  assert((FunctionDescription*)this->_getDescription(id)!=nullptr);
  assert(index<((FunctionDescription*)this->_getDescription(id))->argumentTypes.size());
  return ((FunctionDescription*)this->_getDescription(id))->argumentTypes[index];
}

TypeRegister::TypeId TypeRegister::getTypeId(std::string const&name)const{
  assert(this!=nullptr);
  if(this->_name2TypeId.count(name)==0)
    return UNREGISTERED;
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
  PRINT_CALL_STACK("TypeRegister::computeTypeIdSize",id);
  assert(this!=nullptr);
  switch(this->getTypeIdType(id)){
    case ARRAY :
    case STRUCT:
    case FCE   :
    case ATOMIC:return this->_getDescription(id)->byteSize(this);
    default    :return 0;
  }
}

void*TypeRegister::alloc(TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::alloc",id);
  assert(this!=nullptr);
  size_t size = this->computeTypeIdSize(id);
  uint8_t*ptr=new uint8_t[size];
  std::memset(ptr,0,size);
  return ptr;
}

void TypeRegister::free(void*ptr)const{
  PRINT_CALL_STACK("TypeRegister::free",ptr);
  assert(this!=nullptr);
  delete[]((uint8_t*)ptr);
}

void*TypeRegister::construct(TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::construct",id);
  assert(this!=nullptr);
  auto ptr=this->alloc(id);
  this->_callConstructors(ptr,id);
  return ptr;
}

void TypeRegister::destroy(void*ptr,TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::destroy",ptr,id);
  this->_callDestructors(ptr,id);
  this->free(ptr);
}

void TypeRegister::_callConstructors(void*ptr,TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::_callConstructors",ptr,id);
  assert(this!=nullptr);
  switch(this->getTypeIdType(id)){
    case ATOMIC:
    case ARRAY :
    case STRUCT:
    case FCE   :
      this->_getDescription(id)->callConstructor((TypeRegister*)this,ptr);
      break;
    default    :break;
  }
}

void TypeRegister::_callDestructors(void*ptr,TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::_callDestructors",ptr,id);
  assert(this!=nullptr);
  switch(this->getTypeIdType(id)){
    case ATOMIC:
    case ARRAY :
    case STRUCT:
    case FCE   :this->_getDescription(id)->callDestructor((TypeRegister*)this,ptr);break;
    default    :break;
  }
}

TypeRegister::TypeDescription*TypeRegister::_getDescription(TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::_getDescription",id);
  assert(this!=nullptr);
  assert(this->_typeId2VectorIndex(id)<this->_types.size());
  return this->_types.at(this->_typeId2VectorIndex(id));
}

void TypeRegister::addDestructor(TypeId id,Destructor const&destructor){
  PRINT_CALL_STACK("TypeRegister::addDestructor",id,destructor);
  assert(this!=nullptr);
  assert(this->_getDescription(id)->type == ATOMIC);
  ((AtomicDescription*)this->_getDescription(id))->destructor = destructor;
}

void TypeRegister::addConstructor(TypeId id,Constructor const&constructor){
  PRINT_CALL_STACK("TypeRegister::addConstructor",id,constructor);
  assert(this!=nullptr);
  assert(this->_getDescription(id)->type == ATOMIC);
  ((AtomicDescription*)this->_getDescription(id))->constructor = constructor;
}

std::shared_ptr<Resource>TypeRegister::sharedResource(TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::sharedResource",id);
  assert(this!=nullptr);
  return std::make_shared<AtomicResource>(std::const_pointer_cast<TypeRegister>(this->shared_from_this()),this->construct(id),id);
}

std::shared_ptr<Resource>TypeRegister::sharedResource(std::string const&name)const{
  PRINT_CALL_STACK("TypeRegister::sharedResource",name);
  assert(this!=nullptr);
  auto id = this->getTypeId(name);
  return this->sharedResource(id);
}

std::shared_ptr<Resource>TypeRegister::sharedEmptyResource(TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::sharedEmptyResource",id);
  assert(this!=nullptr);

  return std::shared_ptr<AtomicResource>(new AtomicResource(std::const_pointer_cast<TypeRegister>(this->shared_from_this()),id)
      ,[](AtomicResource*ac){ac->getManager()->destroy(ac->getData(),ac->getId());delete ac;});
  //,[destructor](AtomicResource*ac){destructor((unsigned char*)ac->getData());delete(unsigned char*)ac->getData();delete ac;});
}

std::shared_ptr<Resource>TypeRegister::sharedEmptyResource(std::string const&name)const{
  PRINT_CALL_STACK("TypeRegister::sharedEmptyResource",name);
  assert(this!=nullptr);
  return this->sharedEmptyResource(this->getTypeId(name));
}




#if 0
#include<sstream>
#include<geDE/Interpret.h>
#include<geDE/Resource.h>
#include<geDE/AtomicResource.h>

using namespace ge::de;

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
  this->addType("unregistered"                             ,TypeRegister::UNREGISTERED);
  this->addType(TypeRegister::getTypeKeyword<void       >(),TypeRegister::VOID        );
  this->addType(TypeRegister::getTypeKeyword<bool       >(),TypeRegister::BOOL        );
  this->addType(TypeRegister::getTypeKeyword<int8_t     >(),TypeRegister::I8          );
  this->addType(TypeRegister::getTypeKeyword<int16_t    >(),TypeRegister::I16         );
  this->addType(TypeRegister::getTypeKeyword<int32_t    >(),TypeRegister::I32         );
  this->addType(TypeRegister::getTypeKeyword<int64_t    >(),TypeRegister::I64         );
  this->addType(TypeRegister::getTypeKeyword<uint8_t    >(),TypeRegister::U8          );
  this->addType(TypeRegister::getTypeKeyword<uint16_t   >(),TypeRegister::U16         );
  this->addType(TypeRegister::getTypeKeyword<uint32_t   >(),TypeRegister::U32         );
  this->addType(TypeRegister::getTypeKeyword<uint64_t   >(),TypeRegister::U64         );
  this->addType(TypeRegister::getTypeKeyword<float      >(),TypeRegister::F32         );
  this->addType(TypeRegister::getTypeKeyword<double     >(),TypeRegister::F64         );
  this->addType(TypeRegister::getTypeKeyword<std::string>(),TypeRegister::STRING      );
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

TypeRegister::TypeID TypeRegister::getTypeId(std::string const&name)const{
  if(!this->_name2Id.count(name)){
    std::cerr<<"ERROR: TypeRegister::getTypeId("<<name<<") - type \""<<name<<"\" does not exist."<<std::endl;
    return TypeRegister::getTypeTypeId<TypeRegister::Unregistered>();
  }
  return this->_name2Id.find(name)->second;
}

std::string TypeRegister::toStr(TypeID id)const{
  TypeRegister::Type type=this->getTypeIdType(id);
  std::stringstream ss;
  switch(type){
    case TypeRegister::UNREGISTERED:
    case TypeRegister::VOID        :
    case TypeRegister::BOOL        :
    case TypeRegister::I8          :
    case TypeRegister::I16         :
    case TypeRegister::I32         :
    case TypeRegister::I64         :
    case TypeRegister::U8          :
    case TypeRegister::U16         :
    case TypeRegister::U32         :
    case TypeRegister::U64         :
    case TypeRegister::F32         :
    case TypeRegister::F64         :
    case TypeRegister::STRING      :
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
    case TypeRegister::UNREGISTERED:
    case TypeRegister::VOID        :
    case TypeRegister::BOOL        :
    case TypeRegister::I8          :
    case TypeRegister::I16         :
    case TypeRegister::I32         :
    case TypeRegister::I64         :
    case TypeRegister::U8          :
    case TypeRegister::U16         :
    case TypeRegister::U32         :
    case TypeRegister::U64         :
    case TypeRegister::F32         :
    case TypeRegister::F64         :
    case TypeRegister::STRING      :
    case TypeRegister::TYPEID      :
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

std::string const&TypeRegister::getTypeIdName(TypeID id)const{
  static std::string empty = "";
  if(!this->_id2name.count(id))return empty;
  return this->_id2name.find(id)->second;
}

std::set<std::string>const &TypeRegister::getTypeIdSynonyms(TypeID id)const{
  return this->_id2Synonyms.find(id)->second;
}

bool TypeRegister::hasSynonyms(TypeID id)const{
  return this->_id2Synonyms.find(id)->second.size()>1;
}

bool TypeRegister::areSynonyms(std::string const&name0,std::string const&name1)const{
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
    case TypeRegister::UNREGISTERED:
    case TypeRegister::VOID        :
    case TypeRegister::BOOL        :
    case TypeRegister::I8          :
    case TypeRegister::I16         :
    case TypeRegister::I32         :
    case TypeRegister::I64         :
    case TypeRegister::U8          :
    case TypeRegister::U16         :
    case TypeRegister::U32         :
    case TypeRegister::U64         :
    case TypeRegister::F32         :
    case TypeRegister::F64         :
    case TypeRegister::STRING      :
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

void TypeRegister::_bindTypeIdName(TypeID id,std::string const&name){
  this->_name2Id[name] = id  ;
  if(!this->_id2name.count(id)){
    this->_id2name[id  ] = name;
    this->_id2Synonyms[id]=std::set<std::string>();
  }
  this->_id2Synonyms[id].insert(name);
}

TypeRegister::TypeID TypeRegister::addType(
    std::string                  const&name       ,
    DescriptionList              const&type       ,
    std::function<OBJConstructor>const&constructor,
    std::function<OBJDestructor >const&destructor ){
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
}

void TypeRegister::addConstructor(TypeID id,std::function<OBJConstructor>const&constructor){
  if(!constructor){
    this->_id2Constructor.erase(id);
    return;
  }
  this->_id2Constructor[id]=constructor;
}

void TypeRegister::addDestructor(TypeID id,std::function<OBJDestructor>const&destructor){
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
    case TypeRegister::UNREGISTERED:return 0                  ;
    case TypeRegister::VOID        :return 0                  ;
    case TypeRegister::BOOL        :return sizeof(bool       );
    case TypeRegister::I8          :return sizeof(int8_t     );
    case TypeRegister::I16         :return sizeof(int16_t    );
    case TypeRegister::I32         :return sizeof(int32_t    );
    case TypeRegister::I64         :return sizeof(int64_t    );
    case TypeRegister::U8          :return sizeof(uint8_t    );
    case TypeRegister::U16         :return sizeof(uint16_t   );
    case TypeRegister::U32         :return sizeof(uint32_t   );
    case TypeRegister::U64         :return sizeof(uint64_t   );
    case TypeRegister::F32         :return sizeof(float      );
    case TypeRegister::F64         :return sizeof(double     );
    case TypeRegister::STRING      :return sizeof(std::string);
    case TypeRegister::PTR         :return sizeof(void*      );
    case TypeRegister::ARRAY       :
                                    return this->getArraySize(id)*this->computeTypeIdSize(this->getArrayInnerTypeId(id));
    case TypeRegister::STRUCT      :
                                    for(DescriptionIndex e=0;e<this->getNofStructElements(id);++e)
                                      size+=this->computeTypeIdSize(this->getStructElementTypeId(id,e));
                                    return size;
    case TypeRegister::FCE         :
                                    return sizeof(std::shared_ptr<ge::de::Function>);
                                    /*
                                       size+=this->computeTypeIdSize(this->getFceReturnTypeId(id));
                                       for(unsigned e=0;e<this->getNofFceArgs(id);++e)
                                       size+=this->computeTypeIdSize(this->getFceArgTypeId(id,e));
                                       return size;
                                       */
    case TypeRegister::OBJ         :
                                    return this->getObjSize(id);
    default                        :
                                    std::cerr<<"ERROR: uta aus aus gerichtic himla!"<<std::endl;
                                    return 0;
  }
}

void   TypeRegister::_callConstructors(char*ptr,TypeID id)const{
  TypeRegister::Type type=this->getTypeIdType(id);
  switch(type){
    case TypeRegister::UNREGISTERED:
    case TypeRegister::VOID        :
    case TypeRegister::BOOL        :
    case TypeRegister::I8          :
    case TypeRegister::I16         :
    case TypeRegister::I32         :
    case TypeRegister::I64         :
    case TypeRegister::U8          :
    case TypeRegister::U16         :
    case TypeRegister::U32         :
    case TypeRegister::U64         :
    case TypeRegister::F32         :
    case TypeRegister::F64         :
    case TypeRegister::PTR         :break;
    case TypeRegister::STRING      :
                                    new(ptr)std::string();
                                    break;
    case TypeRegister::ARRAY       :
                                    for(DescriptionIndex i=0;i<this->getArraySize(id);++i)
                                      this->_callConstructors(ptr+this->computeTypeIdSize(this->getArrayInnerTypeId(id))*i,this->getArrayInnerTypeId(id));
                                    break;
    case TypeRegister::STRUCT      :
                                    for(DescriptionIndex e=0;e<this->getNofStructElements(id);++e){
                                      this->_callConstructors(ptr,this->getStructElementTypeId(id,e));
                                      ptr+=this->computeTypeIdSize(this->getStructElementTypeId(id,e));
                                    }
                                    break;
    case TypeRegister::FCE         :
                                    new(ptr)std::shared_ptr<ge::de::Function>();
                                    //TODO CO S FUNKCI
                                    break;
    case TypeRegister::OBJ         :
                                    this->constructUsingCustomConstructor((signed char*)ptr,id);
                                    break;
    default                        :
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
  std::memset(ptr,0,size);
  this->_callConstructors((char*)ptr,id);
  return ptr;
}

std::shared_ptr<Resource>TypeRegister::sharedResource(TypeID id)const{
  return std::make_shared<AtomicResource>(std::const_pointer_cast<TypeRegister>(this->shared_from_this()),this->alloc(id),id);
}

std::shared_ptr<Resource>TypeRegister::sharedResource(std::string const&name)const{
  return this->sharedResource(this->getTypeId(name));
}

std::shared_ptr<Resource>TypeRegister::sharedEmptyResource(TypeID id,std::function<OBJDestructor>destructor)const{
  if(destructor)
    return std::shared_ptr<Resource>(new AtomicResource(std::const_pointer_cast<TypeRegister>(this->shared_from_this()),id),[destructor](AtomicResource*ac){destructor((unsigned char*)ac->getData());delete(unsigned char*)ac->getData();delete ac;});

  return this->sharedEmptyResource(id,this->_id2Destructor.find(id)->second);
  //return std::shared_ptr<Resource>(new AtomicResource(this->shared_from_this(),id),[destructor](AtomicResource*ac){destructor((unsigned char*)ac->getData());delete ac;});
  //  return std::make_shared<AtomicResource>(this->shared_from_this(),id);
}

std::shared_ptr<Resource>TypeRegister::sharedEmptyResource(std::string const&name,std::function<OBJDestructor>destructor)const{
  return this->sharedEmptyResource(this->getTypeId(name),destructor);
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

#endif

