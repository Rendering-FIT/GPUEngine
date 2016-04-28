#pragma once

#include<geCore/Statement.h>

namespace ge{
  namespace core{
    class Function;
    class GECORE_EXPORT While: public Statement{
      protected:
        std::shared_ptr<Function> _condition = nullptr;
        std::shared_ptr<Statement>_body      = nullptr;
      public:
        inline While(
            std::shared_ptr<Function> const&condition = nullptr,
            std::shared_ptr<Statement>const&body      = nullptr);
        inline virtual ~While();
        inline void setBody     (std::shared_ptr<Statement>const&body = nullptr);
        inline void setCondition(std::shared_ptr<Function >const&condition = nullptr);
        inline std::shared_ptr<Function >const&getCondition()const;
        inline std::shared_ptr<Statement>const&getBody()const;
        virtual void operator()();
    };

    inline While::While(
        std::shared_ptr<Function >const&condition,
        std::shared_ptr<Statement>const&body     ):Statement(WHILE){
      this->_condition = condition;
      this->_body      = body;
    }

    inline While::~While(){

    }

    inline void While::setBody(std::shared_ptr<Statement>const&body){
      this->_body = body;
    }

    inline void While::setCondition(std::shared_ptr<Function>const&condition){
      this->_condition = condition;
    }

    inline std::shared_ptr<Function>const&While::getCondition()const{
      return this->_condition;
    }

    inline std::shared_ptr<Statement>const&While::getBody()const{
      return this->_body;
    }
  }
}
