#pragma once

#include<geDE/Statement.h>

namespace ge{
  namespace de{
    class Function;
    class GEDE_EXPORT If: public Statement{
      public:
        If(
            std::shared_ptr<Function >const&condition = nullptr,
            std::shared_ptr<Statement>const&trueBody  = nullptr,
            std::shared_ptr<Statement>const&falseBody = nullptr,
            bool                            ignore    = false  );
        virtual ~If()override;
        void setCondition(std::shared_ptr<Function >const&condition = nullptr);
        void setTrueBody (std::shared_ptr<Statement>const&trueBody  = nullptr);
        void setFalseBody(std::shared_ptr<Statement>const&falseBody = nullptr);
        std::shared_ptr<Function >const&getCondition()const;
        std::shared_ptr<Statement>const&getTrueBody ()const;
        std::shared_ptr<Statement>const&getFalseBody()const;
        virtual void operator()()override;
        std::shared_ptr<If>toIf()const override;
      protected:
        size_t _conditionUpdateTicks = 0;
        size_t _trueBodyUpdateTicks = 0;
        size_t _falseBodyUpdateTicks = 0;
        std::shared_ptr<Function >_condition = nullptr;
        std::shared_ptr<Statement>_trueBody  = nullptr;
        std::shared_ptr<Statement>_falseBody = nullptr;
    };

    inline If::If(
        std::shared_ptr<Function >const&condition,
        std::shared_ptr<Statement>const&trueBody ,
        std::shared_ptr<Statement>const&falseBody,
        bool                            ignore   ):Statement(IF,ignore   ){
      PRINT_CALL_STACK(condition,trueBody,falseBody);
      assert(this!=nullptr);
      this->setCondition(condition);
      this->setTrueBody(trueBody);
      this->setFalseBody(falseBody);
    }

    inline If::~If(){
      PRINT_CALL_STACK();
      /*
      if(this->_condition){
        std::dynamic_pointer_cast<Statement>(this->_condition)->_removeSignalingSource(this);
        std::dynamic_pointer_cast<Statement>(this->_condition)->_removeSignalingSource(this);

      }
      if(this->_trueBody)this->_trueBody->_removeSignaling(this);
      if(this->_falseBody)this->_falseBody->_removeSignaling(this);
      */
    }

    inline void If::setCondition(std::shared_ptr<Function>const&condition){
      PRINT_CALL_STACK(condition);
      assert(this!=nullptr);
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

    inline void If::setTrueBody (std::shared_ptr<Statement>const&trueBody ){
      PRINT_CALL_STACK(trueBody);
      assert(this!=nullptr);
      if(this->_trueBody){
        this->_trueBody->_removeSignalingTarget(this);
        this->_removeSignalingSource(&*this->_trueBody);
      }
      this->_trueBody = trueBody;
      if(this->_trueBody){
        this->_trueBody->_addSignalingTarget(this);
        this->_addSignalingSource(&*this->_trueBody);
      }
      this->setDirty();
    }

    inline void If::setFalseBody(std::shared_ptr<Statement>const&falseBody){
      PRINT_CALL_STACK(falseBody);
      assert(this!=nullptr);
      if(this->_falseBody){
        this->_falseBody->_removeSignalingTarget(this);
        this->_removeSignalingSource(&*this->_falseBody);
      }
      this->_falseBody = falseBody;
      if(this->_falseBody){
        this->_falseBody->_addSignalingTarget(this);
        this->_addSignalingSource(&*this->_falseBody);
      }
      this->setDirty();
    }

    inline std::shared_ptr<Function>const&If::getCondition()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_condition;
    }

    inline std::shared_ptr<Statement>const&If::getTrueBody()const{
      assert(this!=nullptr);
      return this->_trueBody;
    }

    inline std::shared_ptr<Statement>const&If::getFalseBody()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_falseBody;
    }

    inline std::shared_ptr<If>If::toIf()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return std::dynamic_pointer_cast<If>(std::const_pointer_cast<Statement>(this->shared_from_this()));
    }

  }
}
