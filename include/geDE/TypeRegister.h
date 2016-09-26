#pragma once

#include<geDE/Export.h>
#include<geCore/CallStackPrinter.h>
#include<geDE/Types.h>
#include<geDE/Keyword.h>

#include<vector>
#include<map>
#include<set>
#include<iostream>
#include<memory>
#include<cassert>
#include<typeinfo>
#include<typeindex>

namespace ge{
  namespace de{
    class Any;
    class Resource;
    class TypeDescription;
    class AtomicDescription;
    class PtrDescription;
    class ArrayDescription;
    class StructDescription;
    class FceDescription;
    class MemFceDescription;
    class EnumDescription;
    class VoidDescription;
    class AnyDescription;
    using EnumElementType = uint32_t;
    class GEDE_EXPORT TypeRegister: public std::enable_shared_from_this<TypeRegister>{
      friend class TypeDescription;
      friend class AtomicDescription;
      friend class PtrDescription;
      friend class ArrayDescription;
      friend class StructDescription;
      friend class FceDescription;
      friend class MemFceDescription;
      friend class EnumDescription;
      friend class VoidDescription;
      friend class AnyDescription;
      public:
        using ToStr = std::string(*)(void*);
        using Copy = void(*)(void*,void*);
        enum TypeType{
          UNREGISTERED = 0 ,
          ATOMIC       = 1 ,
          PTR          = 2 ,
          ARRAY        = 3 ,
          STRUCT       = 4 ,
          FCE          = 5 ,
          MEMFCE       = 6 ,
          ENUM         = 7 ,
          VOID         = 8 ,
          ANY          = 9 ,
          TYPEID       = 10,
        };
        TypeRegister();
        virtual ~TypeRegister();
        TypeId addAtomicType(
              std::string const&name                 ,
              size_t      const&size                 ,
              CDPtr       const&constructor = nullptr,
              CDPtr       const&destructor  = nullptr);
        TypeId addPtrType(
            std::string const&name     ,
            TypeId      const&innerType);
        TypeId addArrayType(
            std::string const&name     ,
            TypeId      const&innerType,
            size_t      const&size     );
        TypeId addStructType(
            std::string        const&name    ,
            std::vector<TypeId>const&elements);
        TypeId addFceType(
            std::string        const&name      ,
            TypeId             const&returnType,
            std::vector<TypeId>const&args      );
        TypeId addMemFceType(
            std::string        const&name      ,
            TypeId             const&returnType,
            TypeId             const&classType ,
            std::vector<TypeId>const&args      );
        TypeId addEnumType(
            std::string const&name,
            std::vector<EnumElementType>const&values);
        TypeId addVoidType(
            std::string const&name);
        TypeId addAnyType(
            std::string const&name);
        TypeId addCompositeType(
            std::string           const&name       ,
            TypeDescriptionVector const&description);
        size_t getNofTypes()const;
        std::string type2Str(size_t typeIndex)const;
        TypeType                    getTypeIdType         (TypeId id)const;
        TypeId                      getPtrType            (TypeId id)const;
        size_t                      getArraySize          (TypeId id)const;
        TypeId                      getArrayElementTypeId (TypeId id)const;
        size_t                      getNofStructElements  (TypeId id)const;
        TypeId                      getStructElementTypeId(TypeId id,size_t index)const;
        TypeId                      getFceReturnTypeId    (TypeId id)const;
        size_t                      getNofFceArgs         (TypeId id)const;
        TypeId                      getFceArgTypeId       (TypeId id,size_t index)const;
        TypeId                      getMemFceReturnTypeId (TypeId id)const;
        TypeId                      getMemFceClassTypeId  (TypeId id)const;
        size_t                      getNofMemFceArgs      (TypeId id)const;
        TypeId                      getMemFceArgTypeId    (TypeId id,size_t index)const;
        size_t                      getNofEnumElements    (TypeId id)const;
        EnumElementType             getEnumElement        (TypeId id,size_t index)const;
        size_t                      getEnumElementIndex   (TypeId id,EnumElementType element)const;
        TypeId                      getTypeId             (std::string const&name)const;
        std::string const&          getTypeIdName         (TypeId id)const;
        std::set<std::string>const& getTypeIdSynonyms     (TypeId id)const;
        bool                        hasSynonyms           (TypeId id)const;
        bool                        areSynonyms           (std::string const&name0,std::string const&name1)const;
        size_t                      computeTypeIdSize     (TypeId id)const;
        bool                        areConvertible        (TypeId to,TypeId from)const;
        void*alloc(TypeId id)const;
        void free(void*ptr)const;
        void*construct(TypeId id)const;
        void destroy(void*ptr,TypeId id)const;
        std::string data2Str(void*ptr,TypeId id)const;
        void addToStrFunction(TypeId id,ToStr const&fce = nullptr);
        void copy(void*o,void*i,TypeId id)const;
        void addCopyFunction(TypeId id,Copy const&fce = nullptr);
        std::shared_ptr<Resource>sharedResource(TypeId id)const;
        std::shared_ptr<Resource>sharedResource(std::string const&name)const;
        template<typename T>
          std::shared_ptr<Resource>createResource(T const&value)const;
        std::shared_ptr<Resource>sharedEmptyResource(TypeId id)const;
        std::shared_ptr<Resource>sharedEmptyResource(std::string const&name)const;
        void addDestructor (TypeId id,CDPtr const&destructor  = nullptr);
        void addConstructor(TypeId id,CDPtr const&constructor = nullptr);
        template<typename T,typename std::enable_if<ge::core::is_basic<T>::value && !std::is_same<T,void>::value,unsigned>::type = 0>
          TypeId addType(std::string const&name = keyword<T>(),CDPtr c = nullptr,CDPtr d = nullptr);
        template<typename T,typename std::enable_if<std::is_class<T>::value && !std::is_same<T,Any>::value,unsigned>::type = 0>
          TypeId addType(std::string const&name = keyword<T>(),CDPtr c = nullptr,CDPtr d = nullptr);
        template<typename T,typename std::enable_if<std::is_class<T>::value && !std::is_same<T,Any>::value,unsigned>::type = 0>
          TypeId addType(CDPtr c,CDPtr d = nullptr);
        template<typename T,typename std::enable_if<std::is_pointer<T>::value,unsigned>::type = 0>
          TypeId addType(std::string const&name = keyword<T>());
        template<typename T,typename std::enable_if<std::is_array<T>::value && std::rank<T>::value==1,unsigned>::type = 0>
          TypeId addType(std::string const&name = keyword<T>());
        template<typename T,typename std::enable_if<std::is_array<T>::value && std::rank<T>::value!=1,unsigned>::type = 0>
          TypeId addType(std::string const&name = keyword<T>());
        template<typename T,typename std::enable_if<std::is_function<T>::value,unsigned>::type = 0>
          TypeId addType(std::string const&name = keyword<T>());
        template<typename T,typename std::enable_if<std::is_member_function_pointer<T>::value,unsigned>::type = 0>
          TypeId addType(std::string const&name = keyword<T>());
        template<typename T,typename std::enable_if<std::is_same<T,void>::value,unsigned>::type = 0>
          TypeId addType(std::string const&name = keyword<T>());
        template<typename T,typename std::enable_if<std::is_same<T,Any>::value,unsigned>::type = 0>
          TypeId addType(std::string const&name = keyword<T>());
      protected:
        std::vector<TypeDescription*> _types;
        std::map<TypeId,std::set<std::string>>_typeId2Synonyms;
        std::map<std::type_index,TypeId>_typeIndex2TypeId;
        std::map<std::string,TypeId>_name2TypeId;
        TypeId _vectorIndex2TypeId(TypeId const&index)const;
        TypeId _typeId2VectorIndex(TypeId const&id   )const;
        void _bindTypeIdWithName(TypeId id,std::string const&name);
        TypeId _typeExists(
            TypeDescriptionVector const&description,
            size_t                     &i);
        TypeId _typeIdExists(
            TypeDescriptionVector const&description,
            size_t                     &i);
        TypeId _addType(
            std::string           const&name       ,
            TypeDescriptionVector const&description,
            size_t                     &i          );
        TypeId _addTypeId(
            std::string           const&name       ,
            TypeDescriptionVector const&description,
            size_t                     &i          );
        void _callConstructors(void*ptr,TypeId id)const;
        void _callDestructors (void*ptr,TypeId id)const;
        TypeDescription*_getDescription(TypeId id)const;
        TypeId _addTypeByDescription(std::string const&name,TypeDescription*d);
        bool _checkIfTypeNameExists(
            TypeId&result,
            std::string     const&name      ,
            TypeDescription      *d         ,
            std::string     const&errFceName,
            std::string     const&errMsg    );
        bool _checkIfTypeDescriptionExists(
            TypeId               &result,
            std::string     const&name  ,
            TypeDescription      *d     );
        TypeId _checkAndAddTypeByDescription(
            std::string     const&name      ,
            TypeDescription      *d         ,
            std::string     const&errFceName,
            std::string     const&errMsg    );
        template<typename TUPLE,std::size_t...I>
          inline std::vector<TypeId>_tupleToTypeIds2_help(ge::core::index_sequence<I...>){
            assert(this!=nullptr);
            return {this->getTypeId(keyword<typename std::tuple_element<I,TUPLE>::type>())...};
          }
        template<typename TUPLE>
          inline std::vector<TypeId>_tupleToTypeIds2(){
            assert(this!=nullptr);
            return this->_tupleToTypeIds2_help<TUPLE>(typename ge::core::make_index_sequence<std::tuple_size<TUPLE>::value>::type{});
          }
    };
    template<typename T>
      std::shared_ptr<Resource>TypeRegister::createResource(T const&value)const{
        assert(this!=nullptr);
        auto result = this->sharedResource(keyword<T>());
        *result = value;
        return result;
      }

    template<typename T,typename std::enable_if<ge::core::is_basic<T>::value && !std::is_same<T,void>::value,unsigned>::type>
      TypeId TypeRegister::addType(std::string const&name,CDPtr c,CDPtr d){
        PRINT_CALL_STACK(c,d);
        assert(this!=nullptr);
        auto id = this->addAtomicType(name,sizeof(T),c,d);
        if(id!=UNREGISTERED)this->_typeIndex2TypeId[typeid(T)]=id;
        return id;
      }

    template<typename T,typename std::enable_if<std::is_class<T>::value && !std::is_same<T,Any>::value,unsigned>::type>
      TypeId TypeRegister::addType(std::string const&name,CDPtr c,CDPtr d){
        PRINT_CALL_STACK(c,d);
        assert(this!=nullptr);
        auto id = this->addAtomicType(name,sizeof(T),c,d);
        if(id!=UNREGISTERED)this->_typeIndex2TypeId[typeid(T)]=id;
        return id;
      }

    template<typename T,typename std::enable_if<std::is_class<T>::value && !std::is_same<T,Any>::value,unsigned>::type>
      TypeId TypeRegister::addType(CDPtr c,CDPtr d){
        PRINT_CALL_STACK(c,d);
        assert(this!=nullptr);
        auto id = this->addAtomicType(keyword<T>(),sizeof(T),c,d);
        if(id!=UNREGISTERED)this->_typeIndex2TypeId[typeid(T)]=id;
        return id;
      }

    template<typename T,typename std::enable_if<std::is_pointer<T>::value,unsigned>::type>
      TypeId TypeRegister::addType(std::string const&name){
        PRINT_CALL_STACK();
        assert(this!=nullptr);
        using pure = typename std::remove_pointer<T>::type;
        auto id = this->addPtrType(name,this->getTypeId(keyword<pure>()));
        if(id!=UNREGISTERED)this->_typeIndex2TypeId[typeid(T)]=id;
        return id;
      }

    template<typename T,typename std::enable_if<std::is_array<T>::value && std::rank<T>::value==1,unsigned>::type>
      TypeId TypeRegister::addType(std::string const&name){
        PRINT_CALL_STACK();
        assert(this!=nullptr);
        auto id =  this->addArrayType(name,this->getTypeId(keyword<typename std::remove_extent<T>::type>()),std::extent<T>::value);
        if(id!=UNREGISTERED)this->_typeIndex2TypeId[typeid(T)]=id;
        return id;
      }

    template<typename T,typename std::enable_if<std::is_array<T>::value && std::rank<T>::value!=1,unsigned>::type>
      TypeId TypeRegister::addType(std::string const&name){
        PRINT_CALL_STACK();
        assert(this!=nullptr);
        auto innerId = this->addType<typename std::remove_extent<T>::type>();
        auto id = this->addArrayType(name,innerId,std::extent<T>::value);
        if(id!=UNREGISTERED)this->_typeIndex2TypeId[typeid(T)]=id;
        return id;
      }

    template<typename T,typename std::enable_if<std::is_function<T>::value,unsigned>::type>
      TypeId TypeRegister::addType(std::string const&name){
        PRINT_CALL_STACK();
        assert(this!=nullptr);
        using OUTPUT = typename ge::core::FceReturnType<T>::type;
        using ARGS = typename ge::core::FceArgType<T>::type;
        auto id = this->addFceType(name,this->getTypeId(keyword<OUTPUT>()),this->_tupleToTypeIds2<ARGS>());
        if(id!=UNREGISTERED)this->_typeIndex2TypeId[typeid(T)]=id;
        return id;
      }

    template<typename T,typename std::enable_if<std::is_member_function_pointer<T>::value,unsigned>::type>
      TypeId TypeRegister::addType(std::string const&name){
        PRINT_CALL_STACK();
        assert(this!=nullptr);
        using OUTPUT = typename ge::core::MemFceReturnType<T>::type;
        using CLASS = typename ge::core::MemFceClassType<T>::type;
        using ARGS = typename ge::core::MemFceArgType<T>::type;
        auto id = this->addMemFceType(name,this->getTypeId(keyword<OUTPUT>()),this->getTypeId(keyword<CLASS>()),this->_tupleToTypeIds2<ARGS>());
        if(id!=UNREGISTERED)this->_typeIndex2TypeId[typeid(T)]=id;
        return id;
      }

    template<typename T,typename std::enable_if<std::is_same<T,void>::value,unsigned>::type>
      TypeId TypeRegister::addType(std::string const&name){
        PRINT_CALL_STACK(name);
        assert(this!=nullptr);
        auto id = this->addVoidType(name);
        if(id!=UNREGISTERED)this->_typeIndex2TypeId[typeid(T)]=id;
        return id;
      }

    template<typename T,typename std::enable_if<std::is_same<T,Any>::value,unsigned>::type>
      TypeId TypeRegister::addType(std::string const&name){
        PRINT_CALL_STACK();
        assert(this!=nullptr);
        return this->addAnyType(name);
      }


#define GE_DE_ADD_KEYWORD(type,name)\
    template<>inline std::string keyword<type>(){return name;}

    GE_DE_ADD_KEYWORD(void       ,"void"  )
      GE_DE_ADD_KEYWORD(bool       ,"bool"  )
      GE_DE_ADD_KEYWORD(int8_t     ,"i8"    )
      GE_DE_ADD_KEYWORD(int16_t    ,"i16"   )
      GE_DE_ADD_KEYWORD(int32_t    ,"i32"   )
      GE_DE_ADD_KEYWORD(int64_t    ,"i64"   )
      GE_DE_ADD_KEYWORD(uint8_t    ,"u8"    )
      GE_DE_ADD_KEYWORD(uint16_t   ,"u16"   )
      GE_DE_ADD_KEYWORD(uint32_t   ,"u32"   )
      GE_DE_ADD_KEYWORD(uint64_t   ,"u64"   )
      GE_DE_ADD_KEYWORD(float      ,"f32"   )
      GE_DE_ADD_KEYWORD(double     ,"f64"   )
      GE_DE_ADD_KEYWORD(std::string,"string")
      GE_DE_ADD_KEYWORD(Any        ,"any"   )
  }
}

