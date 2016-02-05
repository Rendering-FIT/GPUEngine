#pragma once

#include<geCore/Command.h>
#include<geCore/TypeRegister.h>

using namespace ge::core;

namespace ge{
  namespace core{
    class GECORE_EXPORT Statement: public ge::core::Command{
      public:
        enum Type{
          FUNCTION,
          BODY    ,
          WHILE   ,
          IF      ,
        };
      protected:
        Type _type;
      public:
        Statement(Type type);
        virtual ~Statement();
        virtual void operator()()=0;
    };

    using SharedTypeRegister = std::shared_ptr<TypeRegister>;

    class StatementFactory{
      public:
        virtual ~StatementFactory(){}
        virtual std::shared_ptr<Statement>operator()(SharedTypeRegister const&)=0;
    };

    class ResourceFactory{
      protected:
        TypeRegister::TypeID _type = TypeRegister::UNREGISTERED;
        std::shared_ptr<Accessor>_result  = nullptr;
        unsigned                 _maxUses = 0      ;
        unsigned                 _uses    = 0      ;
        bool                     _first   = true   ;
      public:
        ResourceFactory(TypeRegister::TypeID type,unsigned maxUses=1);
        virtual ~ResourceFactory();
        void reset();
        bool firstConstruction()const;
        std::shared_ptr<Accessor>operator()(SharedTypeRegister const&tr);
    };

  }
}

