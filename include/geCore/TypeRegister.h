#pragma once

#include<geCore/dtemplates.h>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<typeinfo>
#include<functional>

namespace ge{
  namespace core{
    class Accessor;
    class TypeRegister{
      public:
        DEF_ENUM(Type,VOID,I8,I16,I32,I64,U8,U16,U32,U64,F32,F64,STRING,ARRAY,STRUCT,PTR,FCE,OBJ,TYPEID);
        typedef unsigned TypeID;
        typedef void(OBJConstructor)(signed   char*);
        typedef void(OBJDestructor )(unsigned char*);
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
        std::map<std::string,TypeID>_name2Id  ;
        std::map<TypeID,std::string>_id2name  ;
        std::map<TypeID,std::set<std::string>>_id2Synonyms;
        std::map<TypeID,std::function<OBJConstructor>>_id2Constructor;
        std::map<TypeID,std::function<OBJDestructor>>_id2Destructor;
        bool   _isNewTypeEqualTo(TypeID et,std::vector<unsigned>&type,unsigned&start);
        bool   _typeExists      (TypeID*et,std::vector<unsigned>&type,unsigned&start);
        TypeID _typeAdd         (          std::vector<unsigned>&type,unsigned&start);
        bool   _incrCheck(unsigned size,unsigned&start);
        void   _bindTypeIdName(TypeID id,const char*name);
        void   _callConstructors(char*ptr,TypeID id);

        /*
        OBJConstructor _argsToConstructor(){
          return NULL;
        }
        template<typename... ARGS>
        OBJConstructor _argsToConstructor(const char*,ARGS... args){
          return this->_argsToConstructor(args...);
        }
        template<typename... ARGS>
        OBJConstructor _argsToConstructor(unsigned,ARGS... args){
          return this->_argsToConstructor(args...);
        }
        template<typename... ARGS>
        OBJConstructor _argsToConstructor(int,ARGS... args){
          return this->_argsToConstructor(args...);
        }
        template<typename... ARGS>
        OBJConstructor _argsToConstructor(TypeRegister::Type,ARGS... args){
          return this->_argsToConstructor(args...);
        }
        template<typename... ARGS>
        OBJConstructor _argsToConstructor(OBJDestructor,ARGS... args){
          return this->_argsToConstructor(args...);
        }
        template<typename... ARGS>
        OBJConstructor _argsToConstructor(OBJConstructor constructor,ARGS... args){
          return constructor;
        }*/

        template<typename TO>
        TO _argsTo(){
          return NULL;
        }
        template<typename TO,typename... ARGS>
        TO _argsTo(TO to,ARGS... args){
          return to;
        }
        template<typename TO,typename NOTTO,typename... ARGS>
        typename std::enable_if<!std::is_same<TO,NOTTO>::value,TO>::type _argsTo(NOTTO,ARGS... args){
          return this->_argsTo<TO>(args...);
        }


        /*
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
        }*/
        void _argsToVector(std::vector<unsigned>&){
        }

        template<typename... Args>
          void _argsToVector(std::vector<unsigned>&typeConfig,unsigned t,Args... args){
            //this->_argsToVector(typeConfig,t);
            typeConfig.push_back(t);
            this->_argsToVector(typeConfig,args...);
          }
        /*
        template<typename... Args>
          void _argsToVector(std::vector<unsigned>&typeConfig,int t,Args... args){
            //this->_argsToVector(typeConfig,t);
            typeConfig.push_back((unsigned)t);
            this->_argsToVector(typeConfig,args...);
          }
        
        template<typename... Args>
          void _argsToVector(std::vector<unsigned>&typeConfig,TypeRegister::Type t,Args... args){
            //this->_argsToVector(typeConfig,t);
            _argsToVector(typeConfig,(unsigned)t);
            this->_argsToVector(typeConfig,args...);
          }*/
        template<typename... Args>
          void _argsToVector(std::vector<unsigned>&typeConfig,const char*t,Args... args){
            //this->_argsToVector(typeConfig,t);
            typeConfig.push_back(this->getTypeId(t));
            this->_argsToVector(typeConfig,args...);
          }
        template<typename... Args>
          void _argsToVector(std::vector<unsigned>&typeConfig,std::function<OBJConstructor>,Args... args){
            this->_argsToVector(typeConfig,args...);
          }
        template<typename... Args>
          void _argsToVector(std::vector<unsigned>&typeConfig,std::function<OBJDestructor>,Args... args){
            this->_argsToVector(typeConfig,args...);
          }

      public:
        template<typename TYPE>
        static std::function<OBJConstructor> getConstructor(){
          return std::function<OBJConstructor>([](signed char*ptr){new(ptr)TYPE();});
        }
        template<typename TYPE>
        static std::function<OBJDestructor> getDestructor(){
          return std::function<OBJDestructor>([](unsigned char*ptr){((TYPE*)ptr)->~TYPE();});
        }

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
        std::string getTypeIdName           (TypeID id);
        std::set<std::string>&getTypeIdSynonyms(TypeID id);
        bool                  hasSynonyms      (TypeID id);
        bool                  areSynonyms      (const char*name0,const char*name1);
        unsigned   computeTypeIdSize       (TypeID id);

        void*alloc(TypeID id);
        Accessor allocAccessor(TypeID id);
        Accessor allocAccessor(const char*name);
        void destroyUsingCustomDestroyer    (unsigned char*ptr,TypeID id);
        void constructUsingCustomConstructor(  signed char*ptr,TypeID id);

        template<typename... Args>
          unsigned addType(const char* name,Args... args){
            std::vector<unsigned>typeConfig;
            this->_argsToVector(typeConfig,args...);
            //if(this->_argsTo<std::function<OBJConstructor>>(args...)==NULL)std::cerr<<"const: je null"<<std::endl;
            //else std::cerr<<"const: neni null"<<std::endl;
            //if(this->_argsTo<std::function<OBJDestructor>>(args...)==NULL)std::cerr<<"destr: je null"<<std::endl;
            //else std::cerr<<"destr: neni null"<<std::endl;
          
            //std::cerr<<"const: "<<this->_argsTo<std::function<OBJConstructor>>(args...)<<std::endl;
            //std::cerr<<"destr: "<<this->_argsTo<std::function<OBJDestructor>> (args...)<<std::endl;
            return this->addType(name, typeConfig);// , (std::function<OBJConstructor>)NULL, (std::function<OBJDestructor>)NULL);// this->_argsTo<std::function<OBJConstructor>>(args...), this->_argsTo<std::function<OBJDestructor>>(args...));
          }
        TypeID addType(const char*name,std::vector<unsigned>&type,std::function<OBJConstructor> constructor=nullptr,std::function<OBJDestructor> destructor=nullptr);
        void addConstructor(TypeID id,std::function<OBJConstructor> constructor = NULL);
        void addDestructor(TypeID id,std::function<OBJDestructor> destructor = NULL);

        std::string toStr(TypeID id);
        std::string toStr();
    };

    class Accessor{
      protected:
        TypeRegister*        _manager;
        void*               _data   ;
        TypeRegister::TypeID _id     ;
        void _callDesctuctors(char*ptr,TypeRegister::TypeID id);
      public:
        Accessor();
        Accessor(Accessor const& ac);
        Accessor(TypeRegister*manager,const void*data,TypeRegister::TypeID id);
        TypeRegister* getManager();
        void*        getData   ();
        TypeRegister::TypeID getId     ();
        Accessor operator[](unsigned elem);
        unsigned getNofElements();
        void     free();
        const void*getPointer();
        std::string data2Str();
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

namespace ge{
  namespace core{
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::core::Accessor> const&sharedAccessor){
        return (TYPE)*sharedAccessor;
      }

    template<typename TYPE>
      inline TYPE convertTo(ge::core::Accessor const&accessor){
        return (TYPE)accessor;
      }
    template<typename TYPE>
      inline TYPE convertTo(ge::core::Accessor* const&ptrAccessor){
        return (TYPE)*ptrAccessor;
      }

    template<typename TYPE>
      inline void convertFrom(std::shared_ptr<ge::core::Accessor>&output,TYPE const&input){
        *output=input;
      }

    template<typename TYPE>
      inline void convertFrom(ge::core::Accessor*&output,TYPE const&input){
        (TYPE&)(*output)=input;
      }

    template<typename TYPE>
      inline void convertFrom(ge::core::Accessor &output,TYPE const&input){
        ((TYPE&)output) = input;
      }

  }
}
