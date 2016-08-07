#pragma once

#include<geDE/ObjectFactory.h>
#include<memory>
#include<iostream>

namespace ge{
  namespace de{
    class FunctionRegister;
    class Statement;
    class GEDE_EXPORT StatementFactory: public ObjectFactory{
      protected:
        std::string               _name   = ""     ;
        std::shared_ptr<Statement>_result = nullptr;
      public:
        StatementFactory(std::string const&name = "",Uses const&maxUses = 1);
        virtual ~StatementFactory();
        void reset();
        virtual std::shared_ptr<Statement>operator()(
            std::shared_ptr<FunctionRegister>const&tr);
        virtual std::shared_ptr<Statement>_do(
            std::shared_ptr<FunctionRegister>const&fr)=0;
        inline std::string const&getName()const;
    };

    inline StatementFactory::StatementFactory(
        std::string const&name   ,
        Uses        const&maxUses): ObjectFactory(maxUses){
      PRINT_CALL_STACK(name,maxUses);
      assert(this!=nullptr);
      this->_name = name;
    }

    inline StatementFactory::~StatementFactory(){
      PRINT_CALL_STACK();
    }

    inline void StatementFactory::reset(){
      PRINT_CALL_STACK();
    }

    inline std::string const&StatementFactory::getName()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_name;
    }
  }
}
