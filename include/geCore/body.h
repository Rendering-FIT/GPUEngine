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
        inline Body();
        inline virtual ~Body();
        inline void addStatement(std::shared_ptr<Statement>const&statement);
        inline StatementIndex size()const;
        inline std::shared_ptr<Statement>const&operator[](StatementIndex index)const;
        inline StatementIterator begin()const;
        inline StatementIterator end  ()const;
        inline virtual void operator()();
    };

    inline Body::Body():Statement(BODY){
    }

    inline Body::~Body(){
    }

    inline void Body::addStatement(std::shared_ptr<Statement>const&statement){
      this->_statements.push_back(statement);
    }

    inline Body::StatementIndex Body::size()const{
      return this->_statements.size();
    }

    inline std::shared_ptr<Statement>const&Body::operator[](StatementIndex index)const{
      return this->_statements[index];
    }

    inline Body::StatementIterator Body::begin()const{
      return this->_statements.begin();
    }

    inline Body::StatementIterator Body::end()const{
      return this->_statements.end();
    }

    inline void Body::operator()(){
      for(auto x:this->_statements)
        (*x)();
    }
  }
}
