#pragma once

#include<geDE/ObjectFactory.h>
#include<memory>

namespace ge{
  namespace de{
    class FunctionRegister;
    class Statement;
    class GEDE_EXPORT StatementFactory: public ObjectFactory{
      protected:
        std::shared_ptr<Statement>_result = nullptr;
      public:
        StatementFactory(Uses const&maxUses = 1);
        virtual ~StatementFactory();
        void reset();
        virtual std::shared_ptr<Statement>operator()(
            std::shared_ptr<FunctionRegister>const&tr);
        virtual std::shared_ptr<Statement>_do(
            std::shared_ptr<FunctionRegister>const&fr)=0;
    };

    inline StatementFactory::StatementFactory(
        Uses const&maxUses): ObjectFactory(maxUses){
      PRINT_CALL_STACK(name,maxUses);
      assert(this!=nullptr);
    }

    inline StatementFactory::~StatementFactory(){
      PRINT_CALL_STACK();
    }

    inline void StatementFactory::reset(){
      PRINT_CALL_STACK();
    }
  }
}
