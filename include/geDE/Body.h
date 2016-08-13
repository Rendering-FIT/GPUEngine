#pragma once

#include<geDE/Statement.h>
#include<iostream>

namespace ge{
  namespace de{
    class GEDE_EXPORT Body: public Statement{
      public:
        using StatementVector   = std::vector<std::shared_ptr<Statement>>;
        using StatementIndex    = StatementVector::size_type;
        using StatementIterator = StatementVector::const_iterator;
      public:
        Body(bool ignore    = false);
        virtual ~Body();
        size_t addStatement(std::shared_ptr<Statement>const&statement);
        StatementIndex size()const;
        std::shared_ptr<Statement>const&operator[](StatementIndex index)const;
        StatementIterator begin()const;
        StatementIterator end  ()const;
        virtual void operator()()override;
        std::shared_ptr<Body>toBody()const override;
        std::shared_ptr<Statement>const&at(size_t i)const;
      protected:
        StatementVector _statements;
        std::vector<size_t>_statementsUpdateTicks;
    };

    inline Body::Body(bool ignore   ):Statement(BODY,ignore   ){
      PRINT_CALL_STACK();
    }

    inline Body::~Body(){
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      for(auto const&x:this->_statements){
        x->_removeSignalingTarget(this);
        this->_removeSignalingSource(&*x);
      }
    }

    inline size_t Body::addStatement(std::shared_ptr<Statement>const&statement){
      PRINT_CALL_STACK(statement);
      assert(this!=nullptr);
      size_t index = this->_statements.size();
      this->_statements.push_back(statement);
      this->_statementsUpdateTicks.push_back(0);
      statement->_addSignalingTarget(this);
      this->_addSignalingSource(&*statement);
      this->setDirty();
      return index;
    }

    inline Body::StatementIndex Body::size()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_statements.size();
    }

    inline std::shared_ptr<Statement>const&Body::operator[](StatementIndex index)const{
      PRINT_CALL_STACK(index);
      assert(this!=nullptr);
      return this->_statements.at(index);
    }

    inline Body::StatementIterator Body::begin()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_statements.begin();
    }

    inline Body::StatementIterator Body::end()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_statements.end();
    }

    inline void Body::operator()(){
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      if(!this->_ignoreDirty)
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

    inline std::shared_ptr<Body>Body::toBody()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return std::dynamic_pointer_cast<Body>(std::const_pointer_cast<Statement>(this->shared_from_this()));
    }

    inline std::shared_ptr<Statement>const&Body::at(size_t i)const{
      PRINT_CALL_STACK(i);
      assert(this!=nullptr);
      return this->_statements.at(i);
    }

  }
}
