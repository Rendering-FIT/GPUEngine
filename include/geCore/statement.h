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

    class GECORE_EXPORT ObjectFactory{
      public:
        using Uses = uint32_t;
      protected:
        Uses _maxUses = 1   ;
        Uses _uses    = 0   ;
        bool _first   = true;
      public:
        ObjectFactory(Uses maxUses = 1);
        virtual ~ObjectFactory();
    };

    class FunctionRegister;
    class GECORE_EXPORT StatementFactory: public ObjectFactory{
      protected:
        std::string               _name   = ""     ;
        std::shared_ptr<Statement>_result = nullptr;
      public:
        StatementFactory(std::string name = "",Uses maxUses = 1): ObjectFactory(maxUses){
          this->_name = name;
        }
        virtual ~StatementFactory(){}
        void reset();
        virtual std::shared_ptr<Statement>operator()(
            std::shared_ptr<FunctionRegister> const&)=0;
    };

    class GECORE_EXPORT ResourceFactory: public ObjectFactory{
      protected:
        TypeRegister::TypeID     _type   = TypeRegister::UNREGISTERED;
        std::shared_ptr<Accessor>_result = nullptr                   ;
      public:
        ResourceFactory(TypeRegister::TypeID type,Uses maxUses=1);
        virtual ~ResourceFactory();
        void reset();
        bool firstConstruction()const;
        std::shared_ptr<Accessor>operator()(std::shared_ptr<FunctionRegister> const&tr);
    };

  }
}

