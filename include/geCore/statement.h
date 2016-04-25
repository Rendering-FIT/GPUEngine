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
        Statement(Type const&type);
        virtual ~Statement();
        virtual void operator()()=0;
    };

    using SharedTypeRegister = std::shared_ptr<TypeRegister>;

    class GECORE_EXPORT ObjectFactory{
      public:
        using Uses = size_t;
      protected:
        Uses _maxUses = 1   ;
        Uses _uses    = 0   ;
        bool _first   = true;
      public:
        ObjectFactory(Uses const&maxUses = 1);
        virtual ~ObjectFactory();
    };

    class FunctionRegister;
    class GECORE_EXPORT StatementFactory: public ObjectFactory{
      protected:
        std::string               _name   = ""     ;
        std::shared_ptr<Statement>_result = nullptr;
      public:
        StatementFactory(std::string const&name = "",Uses const&maxUses = 1);
        virtual ~StatementFactory();
        void reset();
        virtual std::shared_ptr<Statement>operator()(
            std::shared_ptr<FunctionRegister>const&tr);
        virtual std::shared_ptr<Statement>_do(
            std::shared_ptr<FunctionRegister>const&fr)=0;
        inline std::string const&getName()const;
    };

    class GECORE_EXPORT ResourceFactory: public ObjectFactory{
      protected:
        TypeRegister::TypeID     _type   = TypeRegister::UNREGISTERED;
        std::shared_ptr<Accessor>_result = nullptr                   ;
      public:
        ResourceFactory(TypeRegister::TypeID const&type,Uses const&maxUses=1);
        virtual ~ResourceFactory();
        void reset();
        bool firstConstruction()const;
        std::shared_ptr<Accessor>operator()(std::shared_ptr<FunctionRegister>const&tr);
    };


    inline std::string const&StatementFactory::getName()const{
      return this->_name;
    }

  }
}

