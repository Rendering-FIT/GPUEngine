#pragma once

#include<geCore/Statement.h>

namespace ge{
  namespace core{
    class AtomicFunction;
    class GECORE_EXPORT If: public Statement{
      protected:
        std::shared_ptr<AtomicFunction >_condition = nullptr;
        std::shared_ptr<Statement>_trueBody  = nullptr;
        std::shared_ptr<Statement>_falseBody = nullptr;
      public:
        inline If(
            std::shared_ptr<AtomicFunction >const&condition = nullptr,
            std::shared_ptr<Statement>const&trueBody  = nullptr,
            std::shared_ptr<Statement>const&falseBody = nullptr);
        inline virtual ~If()override;
        inline void setCondition(std::shared_ptr<AtomicFunction >const&condition = nullptr);
        inline void setTrueBody (std::shared_ptr<Statement>const&trueBody  = nullptr);
        inline void setFalseBody(std::shared_ptr<Statement>const&falseBody = nullptr);
        inline std::shared_ptr<AtomicFunction >const&getCondition()const;
        inline std::shared_ptr<Statement>const&getTrueBody ()const;
        inline std::shared_ptr<Statement>const&getFalseBody()const;
        virtual void operator()()override;
    };

    inline If::If(
        std::shared_ptr<AtomicFunction>const&condition,
        std::shared_ptr<Statement>     const&trueBody ,
        std::shared_ptr<Statement>     const&falseBody):Statement(IF){
      this->_condition = condition;
      this->_trueBody  = trueBody ;
      this->_falseBody = falseBody;
    }

    inline If::~If(){

    }

    inline void If::setCondition(std::shared_ptr<AtomicFunction>const&condition){
      this->_condition = condition;
    }

    inline void If::setTrueBody (std::shared_ptr<Statement>const&trueBody ){
      this->_trueBody = trueBody;
    }

    inline void If::setFalseBody(std::shared_ptr<Statement>const&falseBody){
      this->_falseBody = falseBody;
    }

    inline std::shared_ptr<AtomicFunction> const&If::getCondition()const{
      return this->_condition;
    }

    inline std::shared_ptr<Statement>const&If::getTrueBody()const{
      return this->_trueBody;
    }

    inline std::shared_ptr<Statement>const&If::getFalseBody()const{
      return this->_falseBody;
    }

  }
}
