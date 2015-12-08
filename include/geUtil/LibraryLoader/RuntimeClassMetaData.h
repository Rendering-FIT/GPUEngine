#pragma once

#include<geUtil/LibraryLoader/ClassMetaData.h>
#include<geUtil/Export.h>
#include<geCore/TypeRegister.h>

namespace ge{
  namespace util{

    class GEUTIL_EXPORT RuntimeArgMetaData{
      protected:
        ge::core::TypeRegister::TypeID _type;
        std::string _name;
      public:
        RuntimeArgMetaData(
            std::shared_ptr<ge::core::TypeRegister>&typeRegister,
            ArgMetaData const&argMetaData);
        ge::core::TypeRegister::TypeID getType()const;
        std::string getName()const;
    };

    class GEUTIL_EXPORT RuntimeFceMetaData{
      protected:
        ge::core::TypeRegister::TypeID _returnType;
        std::string _name;
        std::vector<RuntimeArgMetaData>_args;
      public:
        RuntimeFceMetaData(
            std::shared_ptr<ge::core::TypeRegister>&typeRegister,
            FceMetaData const&fceMetaData);
        ge::core::TypeRegister::TypeID getReturnType()const;
        std::string getName()const;
        decltype(_args)::size_type getNofArgs()const;
        RuntimeArgMetaData const&getArg(unsigned i)const;
    };

    class GEUTIL_EXPORT RuntimeConstructorMetaData{
      protected:
        std::vector<RuntimeArgMetaData>_args;
      public:
        RuntimeConstructorMetaData(
            std::shared_ptr<ge::core::TypeRegister>&typeRegister,
            ConstructorMetaData const&constructorMetaData);
        decltype(_args)::size_type getNofArgs()const;
        RuntimeArgMetaData const&getArg(unsigned i)const;
    };

    class GEUTIL_EXPORT RuntimeClassMetaData{
      protected:
        std::string _name;
        std::vector<RuntimeFceMetaData>_fces;
        std::vector<RuntimeConstructorMetaData>_constructors;
      public:
        RuntimeClassMetaData(
            std::shared_ptr<ge::core::TypeRegister>&typeRegister,
            ClassMetaData const&classMetaData);
        std::string getName()const;
        decltype(_fces)::size_type getNofFces()const;
        RuntimeFceMetaData const&getFce(unsigned i)const;
        decltype(_constructors)::size_type getNofConstructors()const;
        RuntimeConstructorMetaData const&getConstructor(unsigned i)const;
    };

  }
}
