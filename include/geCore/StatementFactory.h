#pragma once

#include<geCore/ObjectFactory.h>
#include<memory>
#include<iostream>

namespace ge{
  namespace core{
    class FunctionRegister;
    class Statement;
    class GECORE_EXPORT StatementFactory: public ObjectFactory{
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
      this->_name = name;
    }

    inline StatementFactory::~StatementFactory(){
    }

    inline void StatementFactory::reset(){
    }

    inline std::string const&StatementFactory::getName()const{
      return this->_name;
    }
  }
}
