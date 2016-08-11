#pragma once

#include<geDE/FunctionFactory.h>
#include<geDE/FunctionRegister.h>

namespace ge{
  namespace de{
    template<typename TYPE>
      static inline std::shared_ptr<StatementFactory>factoryOfFunctionFactory(){
        class Factory: public FunctionFactory{
          public:
            Factory(Uses maxUses = 1):FunctionFactory(maxUses){}
            virtual ~Factory(){}
            virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister>const&fr)override{
              PRINT_CALL_STACK(fr);
              assert(this!=nullptr);
              assert(fr!=nullptr);
              return std::make_shared<TYPE>(fr,this->getFunctionId());
            }
        };
        return std::make_shared<Factory>();//name);
      }
  }
}
