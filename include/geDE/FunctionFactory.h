#pragma once

#include<geDE/StatementFactory.h>
#include<geDE/Types.h>

namespace ge{
  namespace de{
    class Statement;
    class FunctionRegister;
    class FunctionFactory: public StatementFactory{
      protected:
        FunctionId _fceId = 0;
      public:
        FunctionFactory(Uses maxUses = 0);
        virtual ~FunctionFactory();
        virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister> const&)=0;
        virtual FunctionId getFunctionId()const;
        void setFunctionId(FunctionId id);
    };

    inline FunctionFactory::FunctionFactory(Uses maxUses):StatementFactory(maxUses){
      PRINT_CALL_STACK();
    }

    inline FunctionFactory::~FunctionFactory(){
      PRINT_CALL_STACK();
    }

    inline FunctionId FunctionFactory::getFunctionId()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_fceId;
    }

    inline void FunctionFactory::setFunctionId(FunctionId id){
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      this->_fceId = id;
    }
  }
}

