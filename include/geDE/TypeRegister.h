#pragma once

#include<geDE/Export.h>

#include<vector>
#include<map>
#include<set>
#include<iostream>
#include<memory>

namespace ge{
  namespace de{
    class Resource;
    class GEDE_EXPORT TypeRegister: public std::enable_shared_from_this<TypeRegister>{
      protected:
        class TypeDescription;
        using TypeVector = std::vector<TypeDescription*>;
      public:
        struct Auto;
        using Destructor         = void(*)(void*);
        using Constructor        = void(*)(void*);
        using ToStr              = std::string(*)(void*);
        using TypeId             = TypeVector::size_type;
        using DescriptionElement = size_t;
        using DescriptionVector  = std::vector<DescriptionElement>;
        enum TypeType{
          UNREGISTERED = 0,
          AUTO         = 1,
          ATOMIC       = 2,
          ARRAY        = 3,
          STRUCT       = 4,
          FCE          = 5,
          TYPEID       = 6,
        };
        TypeRegister();
        virtual ~TypeRegister();
        TypeId addAtomicType(
              std::string const&name                 ,
              size_t      const&size                 ,
              Constructor const&constructor = nullptr,
              Destructor  const&destructor  = nullptr);
        TypeId addCompositeType(
            std::string       const&name       ,
            DescriptionVector const&description);
        size_t getNofTypes()const;
        std::string type2Str(size_t typeIndex)const;
        TypeType                    getTypeIdType         (TypeId id)const;
        size_t                      getNofStructElements  (TypeId id)const;
        TypeId                      getStructElementTypeId(TypeId id,size_t index)const;
        size_t                      getArraySize          (TypeId id)const;
        TypeId                      getArrayElementTypeId (TypeId id)const;
        TypeId                      getFceReturnTypeId    (TypeId id)const;
        size_t                      getNofFceArgs         (TypeId id)const;
        TypeId                      getFceArgTypeId       (TypeId id,size_t index)const;
        TypeId                      getTypeId             (std::string const&name)const;
        std::string const&          getTypeIdName         (TypeId id)const;
        std::set<std::string>const& getTypeIdSynonyms     (TypeId id)const;
        bool                        hasSynonyms           (TypeId id)const;
        bool                        areSynonyms           (std::string const&name0,std::string const&name1)const;
        size_t                      computeTypeIdSize     (TypeId id)const;
        void*alloc(TypeId id)const;
        void free(void*ptr)const;
        void*construct(TypeId id)const;
        void destroy(void*ptr,TypeId id)const;
        std::string data2Str(void*ptr,TypeId id)const;
        void addToStrFunction(TypeId id,ToStr const&fce = nullptr);
        std::shared_ptr<Resource>sharedResource(TypeId id)const;
        std::shared_ptr<Resource>sharedResource(std::string const&name)const;
        std::shared_ptr<Resource>sharedEmptyResource(TypeId id)const;
        std::shared_ptr<Resource>sharedEmptyResource(std::string const&name)const;
        void addDestructor (TypeId id,Destructor  const&destructor  = nullptr);
        void addConstructor(TypeId id,Constructor const&constructor = nullptr);
        template<typename TYPE>
        static std::string getTypeKeyword();
      protected:
        class ArrayDescription;
        class StructDescription;
        class FunctionDescription;
        class AtomicDescription;
        class AutoDescription;
        TypeVector _types;
        std::map<TypeId,std::set<std::string>>_typeId2Synonyms;
        std::map<std::string,TypeId>_name2TypeId;
        TypeId _vectorIndex2TypeId(TypeId const&index)const;
        TypeId _typeId2VectorIndex(TypeId const&id   )const;
        void _bindTypeIdWithName(TypeId id,std::string const&name);
        TypeId _typeExists(
            DescriptionVector const&description,
            size_t                 &i);
        TypeId _typeIdExists(
            DescriptionVector const&description,
            size_t                 &i);
        TypeId _addType(
            std::string       const&name       ,
            DescriptionVector const&description,
            size_t                 &i          );
        TypeId _addTypeId(
            std::string       const&name       ,
            DescriptionVector const&description,
            size_t                 &i          );
        void _callConstructors(void*ptr,TypeId id)const;
        void _callDestructors (void*ptr,TypeId id)const;
        TypeDescription*_getDescription(TypeId id)const;
    };

    template<>inline std::string TypeRegister::getTypeKeyword<TypeRegister::Auto>(){return"auto"  ;}
    template<>inline std::string TypeRegister::getTypeKeyword<void              >(){return"void"  ;}
    template<>inline std::string TypeRegister::getTypeKeyword<bool              >(){return"bool"  ;}
    template<>inline std::string TypeRegister::getTypeKeyword<int8_t            >(){return"i8"    ;}
    template<>inline std::string TypeRegister::getTypeKeyword<int16_t           >(){return"i16"   ;}
    template<>inline std::string TypeRegister::getTypeKeyword<int32_t           >(){return"i32"   ;}
    template<>inline std::string TypeRegister::getTypeKeyword<int64_t           >(){return"i64"   ;}
    template<>inline std::string TypeRegister::getTypeKeyword<uint8_t           >(){return"u8"    ;}
    template<>inline std::string TypeRegister::getTypeKeyword<uint16_t          >(){return"u16"   ;}
    template<>inline std::string TypeRegister::getTypeKeyword<uint32_t          >(){return"u32"   ;}
    template<>inline std::string TypeRegister::getTypeKeyword<uint64_t          >(){return"u64"   ;}
    template<>inline std::string TypeRegister::getTypeKeyword<float             >(){return"f32"   ;}
    template<>inline std::string TypeRegister::getTypeKeyword<double            >(){return"f64"   ;}
    template<>inline std::string TypeRegister::getTypeKeyword<std::string       >(){return"string";}
  }
}

