#pragma once

#include<geDE/Statement.h>

namespace ge{
  namespace de{
    class GECORE_EXPORT Body: public Statement{
      public:
        using StatementVector   = std::vector<std::shared_ptr<Statement>>;
        using StatementIndex    = StatementVector::size_type;
        using StatementIterator = StatementVector::const_iterator;
      public:
        inline Body();
        inline virtual ~Body();
        inline void addStatement(std::shared_ptr<Statement>const&statement);
        inline StatementIndex size()const;
        inline std::shared_ptr<Statement>const&operator[](StatementIndex index)const;
        inline StatementIterator begin()const;
        inline StatementIterator end  ()const;
        inline virtual void operator()()override;
      protected:
        StatementVector _statements;
        std::vector<size_t>_statementsUpdateTicks;
    };

    inline Body::Body():Statement(BODY){
    }

    inline Body::~Body(){
      for(auto const&x:this->_statements)
        x->_removeSignaling(this);
    }

    inline void Body::addStatement(std::shared_ptr<Statement>const&statement){
      this->_statements.push_back(statement);
      this->_statementsUpdateTicks.push_back(0);
      statement->_addSignaling(this);
      this->setDirty();
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
      if(!this->_dirtyFlag)return;
      this->_dirtyFlag = false;
      bool changed = false;
      for(size_t i=0;i<this->_statements.size();++i){
        (*this->_statements.at(i))();
        if(this->_statementsUpdateTicks.at(i)!=this->_statements.at(i)->getUpdateTicks())
          changed = true;
        this->_statementsUpdateTicks[i]=this->_statements.at(i)->getUpdateTicks();
      }
      if(!changed)return;
      this->_updateTicks++;
      this->setSignalingDirty();
    }
  }
}
