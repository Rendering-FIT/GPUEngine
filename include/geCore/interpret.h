#pragma once

#include<geCore/Command.h>
#include<geCore/TypeRegister.h>

namespace ge{
  namespace core{
    class Statement: public ge::core::Command{
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

    class Function: public Statement{
      protected:
        std::vector<std::shared_ptr<Function>>_inputs;
        std::vector<bool>_lazy;
        std::vector<unsigned long long>_inputsTicks;
        std::shared_ptr<ge::core::Accessor>_output = nullptr;
        unsigned long long _tickNumber = 1;//this has to be one to call init in parent Function at least once
      public:
        Function(unsigned n);
        virtual ~Function();
        unsigned long long getTick()const;
        void setTick(unsigned long long tick);
        void updateTick();
        void setInput(unsigned i,std::shared_ptr<Function>function=nullptr,bool lazy=false);
        void setOutput(std::shared_ptr<ge::core::Accessor>data = nullptr);
        std::shared_ptr<ge::core::Accessor>const&getOutput()const;
        typedef std::vector<std::shared_ptr<Function>>::const_iterator Iterator;
        Iterator begin()const;
        Iterator end  ()const;
        virtual void operator()();
        void beginOperator();
        void endOperator();
        bool inputChanged(unsigned i)const;
    };

    class Body: public Statement{
      protected:
        std::vector<std::shared_ptr<Statement>>_statements;
      public:
        Body();
        virtual ~Body();
        void addStatement(std::shared_ptr<Statement>const&statement);
        unsigned size()const;
        typedef std::vector<std::shared_ptr<Statement>>::const_iterator Iterator;
        Iterator begin()const;
        Iterator end  ()const;
        virtual void operator()();
    };

    class While: public Statement{
      protected:
        std::shared_ptr<Function >_condition = nullptr;
        std::shared_ptr<Statement>_body      = nullptr;
      public:
        While(std::shared_ptr<Function>const&condition = nullptr,std::shared_ptr<Statement>const&body = nullptr);
        virtual ~While();
        void setBody     (std::shared_ptr<Statement>const&body      = nullptr);
        void setCondition(std::shared_ptr<Function >const&condition = nullptr);
        std::shared_ptr<Function >const&getCondition()const;
        std::shared_ptr<Statement>const&getBody     ()const;
        virtual void operator()();
    };

    class If: public Statement{
      protected:
        std::shared_ptr<Function >_condition = nullptr;
        std::shared_ptr<Statement>_trueBody  = nullptr;
        std::shared_ptr<Statement>_falseBody = nullptr;
      public:
        If(
            std::shared_ptr<Function >const&condition = nullptr,
            std::shared_ptr<Statement>const&trueBody  = nullptr,
            std::shared_ptr<Statement>const&falseBody = nullptr);
        virtual ~If();
        void setCondition(std::shared_ptr<Function >const&condition = nullptr);
        void setTrueBody (std::shared_ptr<Statement>const&trueBody  = nullptr);
        void setFalseBody(std::shared_ptr<Statement>const&falseBody = nullptr);
        std::shared_ptr<Function >const&getCondition()const;
        std::shared_ptr<Statement>const&getTrueBody ()const;
        std::shared_ptr<Statement>const&getFalseBody()const;
        virtual void operator()();
    };
  }
}
