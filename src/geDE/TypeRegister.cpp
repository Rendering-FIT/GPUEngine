#include<geDE/TypeRegister.h>

#include<geDE/AtomicResource.h>
#include<sstream>
#include<memory>
#include<cassert>
#include<cstring>
#include<vector>

using namespace ge::de;

class Function;

/*
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

#if 0
#define PRINT_CALL_STACK(...)iii superduperhidden(__VA_ARGS__)
#else
#define PRINT_CALL_STACK(...)
#endif
*/

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
    ToStr data2StrPtr = nullptr;
    TypeDescription(TypeType const&type){
      this->type = type;
      this->data2StrPtr = nullptr;
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
    virtual std::string data2Str(TypeRegister const*,void*ptr){
      PRINT_CALL_STACK("TypeDescription::data2Str",ptr);
      assert(this!=nullptr);
      if(this->data2StrPtr)return this->data2StrPtr(ptr);
      return "";
    }

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
    virtual std::string data2Str(TypeRegister const*tr,void*ptr)override{
      PRINT_CALL_STACK("ArrayDescription::data2Str",ptr);
      assert(this!=nullptr);
      if(this->data2StrPtr)this->TypeDescription::data2Str(tr,ptr);
      size_t elementSize = tr->computeTypeIdSize(this->elementType);
      std::stringstream ss;
      ss<<"[";
      for(size_t i=0;i<this->size;++i){
        if(i>0)ss<<",";
        ss<<tr->data2Str((uint8_t*)ptr+elementSize*i,this->elementType);
      }
      ss<<"]";
      return ss.str();
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
    virtual std::string data2Str(TypeRegister const*tr,void*ptr)override{
      PRINT_CALL_STACK("StructDescription::data2Str",ptr);
      assert(this!=nullptr);
      if(this->data2StrPtr)this->TypeDescription::data2Str(tr,ptr);
      size_t offset = 0;
      std::stringstream ss;
      ss<<"{";
      bool first = true;
      for(auto const&x:this->elementTypes){
        if(first)first = false;
        else ss<<",";
        ss<<tr->data2Str((uint8_t*)ptr+offset,x);
        offset += tr->computeTypeIdSize(x);
      }
      ss<<"}";
      return ss.str();
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

class TypeRegister::PtrDescription: public TypeDescription{
  public:
    TypeId innerType;
    Destructor destructor = nullptr;
    Constructor constructor = nullptr;
    PtrDescription(TypeId id):TypeDescription(PTR){
      this->innerType = id;
    }
    PtrDescription():TypeDescription(PTR){}
    virtual ~PtrDescription(){}
    virtual bool init(
        TypeRegister*           tr         ,
        DescriptionVector const&description,
        size_t                 &i          ,
        bool                    exists     )override{
      assert(this!=nullptr);
      size_t old = i;
      if(i>=description.size()){
        if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Ptr description is empty"<<std::endl;
        i=old;
        return false;
      }
      if(description[i++]!=PTR){
        if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Ptr description does not start with PTR"<<std::endl;
        i=old;
        return false;
      }
      if(i>=description.size()){
        if(!exists)std::cerr<<"ERROR - TypeRegister::addCompositeType("<<vec2str(description)<<") - Ptr description does not contain innter type"<<std::endl;
        i=old;
        return false;
      }
      if(exists)this->innerType = tr->_typeExists(description,i);
      else this->innerType = tr->_addType("",description,i);
      if(this->innerType == UNREGISTERED){i=old;return false;}
      return true;
    }
    bool operator==(PtrDescription const&other)const{
      assert(this!=nullptr);
      return this->innerType == other.innerType;
    }
    virtual bool equal(TypeDescription const*other)const override{
      assert(this!=nullptr);
      if(this->type != other->type)return false;
      return *this==*(PtrDescription*)other;
    }
    virtual std::string toStr(TypeRegister const*tr,TypeId)const override{
      assert(this!=nullptr);
      std::stringstream ss;
      ss<<tr->type2Str(tr->_typeId2VectorIndex(this->innerType));
      ss<<"*";
      return ss.str();
    }
    virtual void callConstructor(TypeRegister*,void*ptr)const override{
      (void)ptr;
      PRINT_CALL_STACK("PtrDescription::callConstructor",ptr);
      if(this->constructor)this->constructor(ptr);
    }
    virtual void callDestructor(TypeRegister*,void*ptr)const override{
      (void)ptr;
      PRINT_CALL_STACK("PtrDescription::callDestructor",ptr);
      if(this->destructor)this->destructor(ptr);
    }
    virtual size_t byteSize(TypeRegister const*)const override{
      PRINT_CALL_STACK("PtrDescription::byteSize");
      assert(this!=nullptr);
      return sizeof(void*);
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
  auto Void   = this->addAtomicType(TypeRegister::getTypeKeyword<void       >(),0                  );(void)Void;
  auto Bool   = this->addAtomicType(TypeRegister::getTypeKeyword<bool       >(),sizeof(bool       ));
  auto I8     = this->addAtomicType(TypeRegister::getTypeKeyword<int8_t     >(),sizeof(int8_t     ));
  auto I16    = this->addAtomicType(TypeRegister::getTypeKeyword<int16_t    >(),sizeof(int16_t    ));
  auto I32    = this->addAtomicType(TypeRegister::getTypeKeyword<int32_t    >(),sizeof(int32_t    ));
  auto I64    = this->addAtomicType(TypeRegister::getTypeKeyword<int64_t    >(),sizeof(int64_t    ));
  auto U8     = this->addAtomicType(TypeRegister::getTypeKeyword<uint8_t    >(),sizeof(uint8_t    ));
  auto U16    = this->addAtomicType(TypeRegister::getTypeKeyword<uint16_t   >(),sizeof(uint16_t   ));
  auto U32    = this->addAtomicType(TypeRegister::getTypeKeyword<uint32_t   >(),sizeof(uint32_t   ));
  auto U64    = this->addAtomicType(TypeRegister::getTypeKeyword<uint64_t   >(),sizeof(uint64_t   ));
  auto F32    = this->addAtomicType(TypeRegister::getTypeKeyword<float      >(),sizeof(float      ));
  auto F64    = this->addAtomicType(TypeRegister::getTypeKeyword<double     >(),sizeof(double     ));
  auto String = this->addAtomicType(TypeRegister::getTypeKeyword<std::string>(),sizeof(std::string),[](void*ptr){new(ptr)std::string();},[](void*ptr){((std::string*)ptr)->~basic_string();});
  this->addCompositeType("vec2",{ARRAY,2,F32});
  this->addCompositeType("vec3",{ARRAY,3,F32});
  this->addCompositeType("vec4",{ARRAY,4,F32});
  this->addCompositeType("ivec2",{ARRAY,2,I32});
  this->addCompositeType("ivec3",{ARRAY,3,I32});
  this->addCompositeType("ivec4",{ARRAY,4,I32});
  this->addCompositeType("uvec2",{ARRAY,2,U32});
  this->addCompositeType("uvec3",{ARRAY,3,U32});
  this->addCompositeType("uvec4",{ARRAY,4,U32});
  this->addToStrFunction(Bool,  [](void*ptr){if((bool&)ptr)return std::string("true");else return std::string("false");});
  this->addToStrFunction(I8 ,   [](void*ptr){std::stringstream ss;ss<<*(int8_t  *)ptr;return ss.str();});
  this->addToStrFunction(I16,   [](void*ptr){std::stringstream ss;ss<<*(int16_t *)ptr;return ss.str();});
  this->addToStrFunction(I32,   [](void*ptr){std::stringstream ss;ss<<*(int32_t *)ptr;return ss.str();});
  this->addToStrFunction(I64,   [](void*ptr){std::stringstream ss;ss<<*(int64_t *)ptr;return ss.str();});
  this->addToStrFunction(U8 ,   [](void*ptr){std::stringstream ss;ss<<*(uint8_t *)ptr;return ss.str();});
  this->addToStrFunction(U16,   [](void*ptr){std::stringstream ss;ss<<*(uint16_t*)ptr;return ss.str();});
  this->addToStrFunction(U32,   [](void*ptr){std::stringstream ss;ss<<*(uint32_t*)ptr;return ss.str();});
  this->addToStrFunction(U64,   [](void*ptr){std::stringstream ss;ss<<*(uint64_t*)ptr;return ss.str();});
  this->addToStrFunction(F32,   [](void*ptr){std::stringstream ss;ss<<*(float   *)ptr;return ss.str();});
  this->addToStrFunction(F64,   [](void*ptr){std::stringstream ss;ss<<*(double  *)ptr;return ss.str();});
  this->addToStrFunction(String,[](void*ptr){std::stringstream ss;ss<<"\""<<*(std::string*)ptr<<"\"";return ss.str();});
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
    case PTR         :{PtrDescription      desc;return desc.findInRegister(this,description,i);}
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
    case PTR         :return TypeDescription::checkAndBindType(this,name,description,new PtrDescription     (),i);
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

TypeRegister::TypeId TypeRegister::getPtrType(TypeId id)const{
  assert(this!=nullptr);
  assert((PtrDescription*)this->_getDescription(id)!=nullptr);
  return ((PtrDescription*)this->_getDescription(id))->innerType;
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
  if(this->_name2TypeId.count(name)==0){
    ge::core::printError("TypeRegister::getTypeId","there is no such type",name);
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
  PRINT_CALL_STACK("TypeRegister::computeTypeIdSize",id);
  assert(this!=nullptr);
  switch(this->getTypeIdType(id)){
    case ARRAY :
    case STRUCT:
    case FCE   :
    case PTR   :
    case ATOMIC:return this->_getDescription(id)->byteSize(this);
    default    :return 0;
  }
}


bool TypeRegister::areConvertible(TypeId a,TypeId b)const{
  assert(this!=nullptr);
  if(a==b)return true;
  if(this->getTypeIdType(a)==AUTO)return true;
  if(this->getTypeIdType(b)==AUTO)return true;
  if(this->getTypeIdType(a)==ARRAY){
    if(this->getTypeIdType(b)==PTR)
      return this->getArrayElementTypeId(a) == this->getPtrType(b);
  }
  if(this->getTypeIdType(a)==PTR){
    if(this->getTypeIdType(b)==ARRAY)
      return this->getArrayElementTypeId(b) == this->getPtrType(a);
  }
  return false;
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
    case PTR   :
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
    case PTR   :
    case FCE   :this->_getDescription(id)->callDestructor((TypeRegister*)this,ptr);break;
    default    :break;
  }
}

std::string TypeRegister::data2Str(void*ptr,TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::data2Str",ptr,id);
  assert(this!=nullptr);
  return this->_getDescription(id)->data2Str(this,ptr);
}

void TypeRegister::addToStrFunction(TypeId id,ToStr const&fce){
  PRINT_CALL_STACK("TypeRegister::addToStrFunction",id,fce);
  assert(this!=nullptr);
  this->_getDescription(id)->data2StrPtr = fce;
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
  assert(this->_getDescription(id)->type == ATOMIC || this->_getDescription(id)->type == PTR);
  if(this->_getDescription(id)->type == ATOMIC)
    ((AtomicDescription*)this->_getDescription(id))->destructor = destructor;
  if(this->_getDescription(id)->type == PTR)
    ((PtrDescription*)this->_getDescription(id))->destructor = destructor;
}

void TypeRegister::addConstructor(TypeId id,Constructor const&constructor){
  PRINT_CALL_STACK("TypeRegister::addConstructor",id,constructor);
  assert(this!=nullptr);
  assert(this->_getDescription(id)->type == ATOMIC || this->_getDescription(id)->type == PTR);
  if(this->_getDescription(id)->type == ATOMIC)
    ((AtomicDescription*)this->_getDescription(id))->constructor = constructor;
  if(this->_getDescription(id)->type == PTR)
    ((PtrDescription*)this->_getDescription(id))->constructor = constructor;
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


