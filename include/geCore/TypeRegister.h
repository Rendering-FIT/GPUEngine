#pragma once

#include<geCore/Export.h>
#include<geCore/Dtemplates.h>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<typeinfo>
#include<functional>
#include<memory>

namespace ge{
  namespace core{
    class Resource;
    class AtomicResource;
    class GECORE_EXPORT TypeRegister: public std::enable_shared_from_this<TypeRegister>{
      public:
        struct Unregistered;
        DEF_ENUM(Type,UNREGISTERED,VOID,BOOL,I8,I16,I32,I64,U8,U16,U32,U64,F32,F64,STRING,ARRAY,STRUCT,PTR,FCE,OBJ,TYPEID);
        using TypeID                = size_t;
        using DescriptionElement    = TypeID;
        using DescriptionList       = std::vector<DescriptionElement>;
        using DescriptionIndex      = DescriptionList::size_type;
        using DescriptionStarts     = std::vector<DescriptionIndex>;
        using DescriptionStartIndex = DescriptionStarts::size_type;
        typedef void(OBJConstructor)(signed   char*);
        typedef void(OBJDestructor )(unsigned char*);
      protected:
        struct POSITION{
          static const DescriptionIndex TYPE = 0u;
          struct ARRAY{
            static const DescriptionIndex SIZE       = 1u;
            static const DescriptionIndex INNER_TYPE = 2u;
          };
          struct STRUCT{
            static const DescriptionIndex NOF_ELEMENTS      = 1u;
            static const DescriptionIndex INNER_TYPES_START = 2u;
          };
          struct PTR{
            static const DescriptionIndex INNER_TYPE = 1u;
          };
          struct FCE{
            static const DescriptionIndex RETURN_TYPE     = 1u;
            static const DescriptionIndex NOF_ARGUMENTS   = 2u;
            static const DescriptionIndex ARGUMENTS_START = 3u;
          };
          struct OBJ{
            static const DescriptionIndex SIZE = 1u;
          };
        };

        DescriptionStarts            _typeStart;
        DescriptionList              _types    ;
        std::map<std::string,TypeID> _name2Id  ;
        std::map<TypeID,std::string> _id2name  ;
        std::map<TypeID,std::set<std::string>>_id2Synonyms;
        std::map<TypeID,std::function<OBJConstructor>>_id2Constructor;
        std::map<TypeID,std::function<OBJDestructor >>_id2Destructor;
        bool   _isNewTypeEqualTo(TypeID et,DescriptionList const&type,DescriptionIndex&start);
        bool   _typeExists      (TypeID*et,DescriptionList const&type,DescriptionIndex&start);
        TypeID _typeAdd         (          DescriptionList const&type,DescriptionIndex&start);
        bool   _incrCheck(DescriptionIndex size,DescriptionIndex&start);
        void   _bindTypeIdName(TypeID id,std::string name);
        void   _callConstructors(char*ptr,TypeID id)const;

        template<typename TO>
        TO _argsTo()const;
        template<typename TO,typename... ARGS>
        TO _argsTo(TO to,ARGS... args)const;
        template<typename TO,typename NOTTO,typename... ARGS>
        typename std::enable_if<!std::is_same<TO,NOTTO>::value,TO>::type _argsTo(NOTTO,ARGS... args)const;


        template<typename...>
          inline void _argsToVector(DescriptionList&);
        template<typename... Args>
          inline void _argsToVector(DescriptionList&typeConfig,DescriptionElement t,Args... args);
        template<typename... Args>
          inline void _argsToVector(DescriptionList&typeConfig,std::string t,Args... args);
        template<typename... Args>
          inline void _argsToVector(DescriptionList&typeConfig,const char*t,Args... args);
        template<typename... Args>
          inline void _argsToVector(DescriptionList&typeConfig,std::function<OBJConstructor>,Args... args);
        template<typename... Args>
          inline void _argsToVector(DescriptionList&typeConfig,std::function<OBJDestructor>,Args... args);

      public:
        template<typename TYPE>
        static std::string getTypeKeyword();
        template<typename TYPE>
        static TypeID getTypeTypeId();
        template<typename TYPE>
        static DescriptionElement getTypeDescription();
        template<typename TYPE>
        std::function<OBJConstructor> getConstructor();
        template<typename TYPE>
        std::function<OBJDestructor> getDestructor();

        TypeRegister();
        ~TypeRegister();
        DescriptionStartIndex       getNofTypes             ()const;
        TypeID                      getTypeId               (DescriptionStartIndex index)const;
        DescriptionStartIndex       getIndex                (TypeID id)const;
        DescriptionIndex            getTypeDescriptionLength(TypeID id)const;
        DescriptionElement          getTypeDescriptionElem  (TypeID id,DescriptionIndex i)const;
        Type                        getTypeIdType           (TypeID id)const;
        Type                        getElementType          (DescriptionElement element)const;
        DescriptionElement          getNofStructElements    (TypeID id)const;
        TypeID                      getStructElementTypeId  (TypeID id,DescriptionIndex index)const;
        DescriptionElement          getArraySize            (TypeID id)const;
        TypeID                      getArrayInnerTypeId     (TypeID id)const;
        TypeID                      getPtrInnerTypeId       (TypeID id)const;
        TypeID                      getFceReturnTypeId      (TypeID id)const;
        DescriptionElement          getNofFceArgs           (TypeID id)const;
        TypeID                      getFceArgTypeId         (TypeID id,DescriptionIndex index)const;
        DescriptionElement          getObjSize              (TypeID id)const;
        TypeID                      getTypeId               (std::string name)const;
        std::string                 getTypeIdName           (TypeID id)const;
        std::set<std::string>const& getTypeIdSynonyms       (TypeID id)const;
        bool                        hasSynonyms             (TypeID id)const;
        bool                        areSynonyms             (std::string name0,std::string name1)const;
        size_t                      computeTypeIdSize       (TypeID id)const;

        bool integerType(TypeID type)const;
        bool floatType  (TypeID type)const;
        bool stringType (TypeID type)const;

        void*alloc(TypeID id)const;
        std::shared_ptr<Resource>sharedResource(TypeID id)const;
        std::shared_ptr<Resource>sharedResource(std::string name)const;

        std::shared_ptr<Resource>sharedEmptyResource(TypeID id       ,std::function<OBJDestructor> destructor  = nullptr)const;
        std::shared_ptr<Resource>sharedEmptyResource(std::string name,std::function<OBJDestructor> destructor  = nullptr)const;

        template<typename CLASS,typename... ARGS>
        inline std::shared_ptr<Resource>sharedResourceTypeID(TypeID id,ARGS... args)const;
        template<typename CLASS,typename... ARGS>
        inline std::shared_ptr<Resource>sharedResource(std::string name,ARGS... args)const;
        template<typename CLASS,typename... ARGS>
        inline std::shared_ptr<Resource>sharedResource(const char* name,ARGS... args)const;
        template<typename CLASS,typename... ARGS>
        inline std::shared_ptr<Resource>sharedResource(ARGS... args)const;

        template<typename CLASS,typename... ARGS>
        inline std::shared_ptr<Resource>sharedResourceAddCD(std::string name,ARGS... args);
        template<typename CLASS,typename... ARGS>
        inline std::shared_ptr<Resource>sharedResourceAddC(std::string name,ARGS... args);
        template<typename CLASS,typename... ARGS>
        inline std::shared_ptr<Resource>sharedResourceAddD(std::string name,ARGS... args);
        template<typename CLASS,typename... ARGS>
        inline std::shared_ptr<Resource>sharedResourceAdd(std::string name,ARGS... args);

        void destroyUsingCustomDestroyer    (unsigned char*ptr,TypeID id)const;
        void constructUsingCustomConstructor(  signed char*ptr,TypeID id)const;

        template<typename... Args>
          TypeID addType(std::string name,Args... args);

        TypeID addType(
            std::string                   name                 ,
            DescriptionList const&        type                 ,
            std::function<OBJConstructor> constructor = nullptr,
            std::function<OBJDestructor > destructor  = nullptr);


        template<typename CLASS>
        TypeID addClassCD(std::string name);
        template<typename CLASS>
        TypeID addClassD(std::string name);
        template<typename CLASS>
        TypeID addClassC(std::string name);
        template<typename CLASS>
        TypeID addClass(std::string name);

        void addConstructor(TypeID id,std::function<OBJConstructor> constructor = nullptr);
        void addDestructor (TypeID id,std::function<OBJDestructor > destructor  = nullptr);

        std::string toStr(TypeID id)const;
        std::string toStr()const;

        DescriptionIndex   getNofDescriptionUints()const;
        DescriptionElement getDescription(DescriptionIndex i)const;
    };

    template<typename TO>
      TO TypeRegister::_argsTo()const{
        return nullptr;
      }
    template<typename TO,typename... ARGS>
      TO TypeRegister::_argsTo(TO to,ARGS...)const{
        return to;
      }
    template<typename TO,typename NOTTO,typename... ARGS>
      typename std::enable_if<!std::is_same<TO,NOTTO>::value,TO>::type TypeRegister::_argsTo(NOTTO,ARGS... args)const{
        return this->_argsTo<TO>(args...);
      }


    template<typename...>
      void TypeRegister::_argsToVector(DescriptionList&){}
    template<typename... Args>
      void TypeRegister::_argsToVector(DescriptionList&typeConfig,DescriptionElement t,Args... args){
        typeConfig.push_back(t);
        this->_argsToVector(typeConfig,args...);
      }
    template<typename... Args>
      void TypeRegister::_argsToVector(DescriptionList&typeConfig,std::string t,Args... args){
        typeConfig.push_back(this->getTypeId(t));
        this->_argsToVector(typeConfig,args...);
      }
    template<typename... Args>
      void TypeRegister::_argsToVector(DescriptionList&typeConfig,const char*t,Args... args){
        typeConfig.push_back(this->getTypeId(std::string(t)));
        this->_argsToVector(typeConfig,args...);
      }
    template<typename... Args>
      void TypeRegister::_argsToVector(DescriptionList&typeConfig,std::function<OBJConstructor>,Args... args){
        this->_argsToVector(typeConfig,args...);
      }
    template<typename... Args>
      void TypeRegister::_argsToVector(DescriptionList&typeConfig,std::function<OBJDestructor>,Args... args){
        this->_argsToVector(typeConfig,args...);
      }


    template<>inline std::string TypeRegister::getTypeKeyword<TypeRegister::Unregistered>(){return"unregistered";}
    template<>inline std::string TypeRegister::getTypeKeyword<void                      >(){return"void"        ;}
    template<>inline std::string TypeRegister::getTypeKeyword<bool                      >(){return"bool"        ;}
    template<>inline std::string TypeRegister::getTypeKeyword<int8_t                    >(){return"i8"          ;}
    template<>inline std::string TypeRegister::getTypeKeyword<int16_t                   >(){return"i16"         ;}
    template<>inline std::string TypeRegister::getTypeKeyword<int32_t                   >(){return"i32"         ;}
    template<>inline std::string TypeRegister::getTypeKeyword<int64_t                   >(){return"i64"         ;}
    template<>inline std::string TypeRegister::getTypeKeyword<uint8_t                   >(){return"u8"          ;}
    template<>inline std::string TypeRegister::getTypeKeyword<uint16_t                  >(){return"u16"         ;}
    template<>inline std::string TypeRegister::getTypeKeyword<uint32_t                  >(){return"u32"         ;}
    template<>inline std::string TypeRegister::getTypeKeyword<uint64_t                  >(){return"u64"         ;}
    template<>inline std::string TypeRegister::getTypeKeyword<float                     >(){return"f32"         ;}
    template<>inline std::string TypeRegister::getTypeKeyword<double                    >(){return"f64"         ;}
    template<>inline std::string TypeRegister::getTypeKeyword<std::string               >(){return"string"      ;}


    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<TypeRegister::Unregistered>(){return TypeRegister::UNREGISTERED;}
    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<void                      >(){return TypeRegister::VOID        ;}
    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<bool                      >(){return TypeRegister::BOOL        ;}
    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<int8_t                    >(){return TypeRegister::I8          ;}
    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<int16_t                   >(){return TypeRegister::I16         ;}
    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<int32_t                   >(){return TypeRegister::I32         ;}
    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<int64_t                   >(){return TypeRegister::I64         ;}
    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<uint8_t                   >(){return TypeRegister::U8          ;}
    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<uint16_t                  >(){return TypeRegister::U16         ;}
    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<uint32_t                  >(){return TypeRegister::U32         ;}
    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<uint64_t                  >(){return TypeRegister::U64         ;}
    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<float                     >(){return TypeRegister::F32         ;}
    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<double                    >(){return TypeRegister::F64         ;}
    template<>inline TypeRegister::DescriptionElement TypeRegister::getTypeDescription<std::string               >(){return TypeRegister::STRING      ;}

    template<typename TYPE>
    inline TypeRegister::TypeID TypeRegister::getTypeTypeId(){return TypeRegister::TYPEID+TypeRegister::getTypeDescription<TYPE>();}//-1;}

    /*
    template<>inline TypeRegister::TypeID TypeRegister::getTypeTypeId<void              >(){return TypeRegister::TYPEID+TypeRegister::VOID  -1;}
    template<>inline TypeRegister::TypeID TypeRegister::getTypeTypeId<bool              >(){return TypeRegister::TYPEID+TypeRegister::BOOL  -1;}
    template<>inline TypeRegister::TypeID TypeRegister::getTypeTypeId<char              >(){return TypeRegister::TYPEID+TypeRegister::I8    -1;}
    template<>inline TypeRegister::TypeID TypeRegister::getTypeTypeId<short             >(){return TypeRegister::TYPEID+TypeRegister::I16   -1;}
    template<>inline TypeRegister::TypeID TypeRegister::getTypeTypeId<int               >(){return TypeRegister::TYPEID+TypeRegister::I32   -1;}
    template<>inline TypeRegister::TypeID TypeRegister::getTypeTypeId<long long int     >(){return TypeRegister::TYPEID+TypeRegister::I64   -1;}
    template<>inline TypeRegister::TypeID TypeRegister::getTypeTypeId<unsigned char     >(){return TypeRegister::TYPEID+TypeRegister::U8    -1;}
    template<>inline TypeRegister::TypeID TypeRegister::getTypeTypeId<unsigned short    >(){return TypeRegister::TYPEID+TypeRegister::U16   -1;}
    template<>inline TypeRegister::TypeID TypeRegister::getTypeTypeId<unsigned          >(){return TypeRegister::TYPEID+TypeRegister::U32   -1;}
    template<>inline TypeRegister::TypeID TypeRegister::getTypeTypeId<unsigned long long>(){return TypeRegister::TYPEID+TypeRegister::U64   -1;}
    template<>inline TypeRegister::TypeID TypeRegister::getTypeTypeId<float             >(){return TypeRegister::TYPEID+TypeRegister::F32   -1;}
    template<>inline TypeRegister::TypeID TypeRegister::getTypeTypeId<double            >(){return TypeRegister::TYPEID+TypeRegister::F64   -1;}
    template<>inline TypeRegister::TypeID TypeRegister::getTypeTypeId<std::string       >(){return TypeRegister::TYPEID+TypeRegister::STRING-1;}
    */

    template<typename TYPE>
      std::function<TypeRegister::OBJConstructor> TypeRegister::getConstructor(){
        return std::function<OBJConstructor>([](signed char*ptr){new(ptr)TYPE();});
      }
    template<typename TYPE>
      std::function<TypeRegister::OBJDestructor> TypeRegister::getDestructor(){
        return std::function<OBJDestructor>([](unsigned char*ptr){((TYPE*)ptr)->~TYPE();});
      }

    template<typename... Args>
      TypeRegister::TypeID TypeRegister::addType(std::string name,Args... args){
        DescriptionList typeConfig;
        this->_argsToVector(typeConfig,args...);
        return this->addType(name, typeConfig,this->_argsTo<std::function<OBJConstructor>>(args...),this->_argsTo<std::function<OBJDestructor>>(args...));
      }

    template<typename CLASS>
      TypeRegister::TypeID TypeRegister::addClassCD(std::string name){
        return this->addType(name,TypeRegister::OBJ,sizeof(CLASS),TypeRegister::getConstructor<CLASS>(),TypeRegister::getDestructor<CLASS>());
      }
    template<typename CLASS>
      TypeRegister::TypeID TypeRegister::addClassD(std::string name){
        return this->addType(name,TypeRegister::OBJ,sizeof(CLASS),TypeRegister::getDestructor<CLASS>());
      }
    template<typename CLASS>
      TypeRegister::TypeID TypeRegister::addClassC(std::string name){
        return this->addType(name,TypeRegister::OBJ,sizeof(CLASS),TypeRegister::getConstructor<CLASS>());
      }
    template<typename CLASS>
      TypeRegister::TypeID TypeRegister::addClass(std::string name){
        return this->addType(name,TypeRegister::OBJ,sizeof(CLASS));
      }

  }
}

namespace ge{
  namespace core{
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::core::Resource> const&sharedResource){
        return (TYPE)*sharedResource;
      }

    template<typename TYPE>
      inline TYPE convertTo(ge::core::Resource const&accessor){
        return (TYPE)accessor;
      }
    template<typename TYPE>
      inline TYPE convertTo(ge::core::Resource* const&ptrResource){
        return (TYPE)*ptrResource;
      }

    template<typename TYPE>
      inline void convertFrom(std::shared_ptr<ge::core::Resource>&output,TYPE const&input){
        *output=input;
      }

    template<typename TYPE>
      inline void convertFrom(ge::core::Resource*&output,TYPE const&input){
        (TYPE&)(*output)=input;
      }

    template<typename TYPE>
      inline void convertFrom(ge::core::Resource &output,TYPE const&input){
        ((TYPE&)output) = input;
      }

  }
}
