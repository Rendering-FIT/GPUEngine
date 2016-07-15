#pragma once

#include<geDE/Statement.h>

namespace ge{
  namespace de{
    class Function;
    class GEDE_EXPORT While: public Statement{
      public:
        While(
            std::shared_ptr<Function> const&condition = nullptr,
            std::shared_ptr<Statement>const&body      = nullptr);
        virtual ~While();
        void setBody     (std::shared_ptr<Statement>const&body = nullptr);
        void setCondition(std::shared_ptr<Function >const&condition = nullptr);
        std::shared_ptr<Function >const&getCondition()const;
        std::shared_ptr<Statement>const&getBody()const;
        virtual void operator()()override;
        virtual std::shared_ptr<While>toWhile()const override;
      protected:
        std::shared_ptr<Function> _condition = nullptr;
        std::shared_ptr<Statement>_body      = nullptr;
        size_t _conditionUpdateTicks = 0;
        size_t _bodyUpdateTicks = 0;
    };

    inline While::While(
        std::shared_ptr<Function >const&condition,
        std::shared_ptr<Statement>const&body     ):Statement(WHILE){
      this->setCondition(condition);
      this->setBody(body);
    }

    inline While::~While(){
    }

    inline void While::setBody(std::shared_ptr<Statement>const&body){
      if(this->_body){
        this->_body->_removeSignalingTarget(this);
        this->_removeSignalingSource(&*this->_body);
      }
      this->_body = body;
      if(this->_body){
        this->_body->_addSignalingTarget(this);
        this->_addSignalingSource(&*this->_body);
      }
      this->setDirty();
    }

    inline void While::setCondition(std::shared_ptr<Function>const&condition){
      if(this->_condition){
        std::dynamic_pointer_cast<Statement>(this->_condition)->_removeSignalingTarget(this);
        this->_removeSignalingSource((Statement*)&*this->_condition);
      }
      this->_condition = condition;
      if(this->_condition){
        std::dynamic_pointer_cast<Statement>(this->_condition)->_addSignalingTarget(this);
        this->_addSignalingSource((Statement*)&*this->_condition);
      }
      this->setDirty();
    }

    inline std::shared_ptr<Function>const&While::getCondition()const{
      return this->_condition;
    }

    inline std::shared_ptr<Statement>const&While::getBody()const{
      return this->_body;
    }

    inline std::shared_ptr<While>While::toWhile()const{
      return std::dynamic_pointer_cast<While>(std::const_pointer_cast<Statement>(this->shared_from_this()));
    }

  }
}
