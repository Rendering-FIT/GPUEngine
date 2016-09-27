#pragma once

#include<geAd/LibraryLoader/ClassMetaData.h>
#include<geAd/Export.h>
#include<geDE/TypeRegister.h>

namespace ge{
  namespace ad{

    class GEAD_EXPORT RuntimeArgMetaData{
      protected:
        de::TypeId _type;
        std::string _name;
      public:
        RuntimeArgMetaData(
            std::shared_ptr<de::TypeRegister>&typeRegister,
            ArgMetaData const&argMetaData);
        de::TypeId getType()const;
        std::string getName()const;
    };

    class GEAD_EXPORT RuntimeFceMetaData{
      protected:
        de::TypeId _returnType;
        std::string _name;
        std::vector<RuntimeArgMetaData>_args;
      public:
        RuntimeFceMetaData(
            std::shared_ptr<de::TypeRegister>&typeRegister,
            FceMetaData const&fceMetaData);
        de::TypeId getReturnType()const;
        std::string getName()const;
        decltype(_args)::size_type getNofArgs()const;
        RuntimeArgMetaData const&getArg(unsigned i)const;
    };

    class GEAD_EXPORT RuntimeConstructorMetaData{
      protected:
        std::vector<RuntimeArgMetaData>_args;
      public:
        RuntimeConstructorMetaData(
            std::shared_ptr<de::TypeRegister>&typeRegister,
            ConstructorMetaData const&constructorMetaData);
        decltype(_args)::size_type getNofArgs()const;
        RuntimeArgMetaData const&getArg(unsigned i)const;
    };

    class GEAD_EXPORT RuntimeClassMetaData{
      protected:
        std::string _name;
        std::vector<RuntimeFceMetaData>_fces;
        std::vector<RuntimeConstructorMetaData>_constructors;
      public:
        RuntimeClassMetaData(
            std::shared_ptr<de::TypeRegister>&typeRegister,
            ClassMetaData const&classMetaData);
        std::string getName()const;
        decltype(_fces)::size_type getNofFces()const;
        RuntimeFceMetaData const&getFce(unsigned i)const;
        decltype(_constructors)::size_type getNofConstructors()const;
        RuntimeConstructorMetaData const&getConstructor(unsigned i)const;
    };

  }
}
