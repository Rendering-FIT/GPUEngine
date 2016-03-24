#pragma once

#include<geCore/statement.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT Body: public Statement{
      public:
        using StatementList = std::vector<std::shared_ptr<Statement>>;
        using StatementIndex = StatementList::size_type;
        using StatementIterator = StatementList::const_iterator;
      protected:
        StatementList _statements;
      public:
        Body();
        virtual ~Body();
        void addStatement(std::shared_ptr<Statement>const&statement);
        StatementIndex size()const;
        std::shared_ptr<Statement>const&operator[](StatementIndex index)const;
        StatementIterator begin()const;
        StatementIterator end  ()const;
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
