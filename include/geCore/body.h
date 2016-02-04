#pragma once

#include<geCore/statement.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT Body: public Statement{
      protected:
        std::vector<std::shared_ptr<Statement>>_statements;
      public:
        Body();
        virtual ~Body();
        void addStatement(std::shared_ptr<Statement>const&statement);
        std::vector<std::shared_ptr<Statement>>::size_type size()const;
        typedef std::vector<std::shared_ptr<Statement>>::const_iterator Iterator;
        Iterator begin()const;
        Iterator end  ()const;
        virtual void operator()();
    };

    class GECORE_EXPORT BodyFactory: public StatementFactory{
      public:
        virtual ~BodyFactory();
        std::vector<std::shared_ptr<StatementFactory>>factories;
        virtual std::shared_ptr<Statement>operator()(SharedTypeRegister const&);
    };
  }
}
