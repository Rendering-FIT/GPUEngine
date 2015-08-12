#pragma once

#include<geCore/dtemplates.h>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<typeinfo>

namespace ge{
  namespace core{
    class Accessor;
    class TypeRegister{
      public:
        DEF_ENUM(Type,VOID,I8,I16,I32,I64,U8,U16,U32,U64,F32,F64,STRING,ARRAY,STRUCT,PTR,FCE,OBJ,TYPEID);
        typedef unsigned TypeID;
      protected:
        struct{
          static const unsigned TYPE = 0u;
          struct{
            static const unsigned SIZE       = 1u;
            static const unsigned INNER_TYPE = 2u;
          }static const ARRAY;
          struct{
            static const unsigned NOF_ELEMENTS      = 1u;
            static const unsigned INNER_TYPES_START = 2u;
          }static const STRUCT;
          struct{
            static const unsigned INNER_TYPE = 1u;
          }static const PTR;
          struct{
            static const unsigned RETURN_TYPE     = 1u;
            static const unsigned NOF_ARGUMENTS   = 2u;
            static const unsigned ARGUMENTS_START = 3u;
          }static const FCE;
          struct{
            static const unsigned SIZE = 1u;
          }static const OBJ;
        }static const POSITION;

        std::vector<unsigned>       _typeStart;
        std::vector<unsigned>       _types    ;
        std::map<const char*,TypeID>_name2Id  ;
        std::map<TypeID,const char*>_id2name  ;
        std::map<TypeID,std::set<const char*>>_id2Synonyms;
        bool   _typeExists(TypeID et,std::vector<unsigned>&type,unsigned*start);
        bool   _typeExists(TypeID*et,std::vector<unsigned>&type,unsigned*start);
        TypeID _typeAdd(std::vector<unsigned>&type,unsigned*start);
        bool   _incrCheck(unsigned size,unsigned*start);
        void   _bindTypeIdName(TypeID id,const char*name);
        void _argsToVector(std::vector<unsigned>&typeConfig,unsigned element){
          typeConfig.push_back(element);
        }
        void _argsToVector(std::vector<unsigned>&typeConfig,int element){
          typeConfig.push_back((unsigned)element);
        }
        void _argsToVector(std::vector<unsigned>&typeConfig,TypeRegister::Type type){
          _argsToVector(typeConfig,(unsigned)type);
        }
        void _argsToVector(std::vector<unsigned>&typeConfig,const char*typeName){
          typeConfig.push_back(this->getTypeId(typeName));
        }
        template<typename T,typename... Args>
          void _argsToVector(std::vector<unsigned>&typeConfig,T t,Args... args){
            _argsToVector(typeConfig,t);
            _argsToVector(typeConfig,args...);
          }
      public:
        TypeRegister();
        ~TypeRegister();
        unsigned   getNofTypes();
        TypeID     getTypeId               (unsigned index);
        unsigned   getIndex                (TypeID id);
        unsigned   getTypeDescriptionLength(TypeID id);
        unsigned   getTypeDescriptionElem  (TypeID id,unsigned i);
        Type       getTypeIdType           (TypeID id);
        Type       getElementType          (unsigned element);
        unsigned   getNofStructElements    (TypeID id);
        TypeID     getStructElementTypeId  (TypeID id,unsigned element);
        unsigned   getArraySize            (TypeID id);
        TypeID     getArrayInnerTypeId     (TypeID id);
        TypeID     getPtrInnerTypeId       (TypeID id);
        TypeID     getFceReturnTypeId      (TypeID id);
        unsigned   getNofFceArgs           (TypeID id);
        TypeID     getFceArgTypeId         (TypeID id,unsigned element);
        unsigned   getObjSize              (TypeID id);
        TypeID     getTypeId               (const char*name);
        const char*getTypeIdName           (TypeID id);
        std::set<const char*>&getTypeIdSynonyms(TypeID id);
        bool                  hasSynonyms      (TypeID id);
        bool                  areSynonyms      (const char*name0,const char*name1);
        unsigned   computeTypeIdSize       (TypeID id);

        void*alloc(TypeID id);
        Accessor allocAccessor(TypeID id);
        Accessor allocAccessor(const char*name);

        template<typename... Args>
          unsigned addType(const char* name,Args... args){
            std::vector<unsigned>typeConfig;
            this->_argsToVector(typeConfig,args...);
            return this->addType(name,typeConfig);
          }
        TypeID addType(const char*name,std::vector<unsigned>&type);

        std::string toStr(TypeID id);
        std::string toStr();
    };

    class Accessor{
      protected:
        TypeRegister*        _manager;
        void*               _data   ;
        TypeRegister::TypeID _id     ;
      public:
        Accessor(TypeRegister*manager,const void*data,TypeRegister::TypeID id);
        TypeRegister* getManager();
        void*        getData   ();
        TypeRegister::TypeID getId     ();
        Accessor operator[](unsigned elem);
        unsigned getNofElements();
        void     free();
        const void*getPointer();
        template<typename T>
          Accessor& operator=(const T&data){
            *((T*)this->getData()) = data;
            return *this;
          }
        template<typename T>
          operator T&(){
            return *((T*)((Accessor*)this)->getData());
          }
    };
  }
}

