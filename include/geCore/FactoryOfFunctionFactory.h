#pragma once

#include<geCore/FunctionFactory.h>
#include<geCore/FunctionRegister.h>

namespace ge{
  namespace core{
    template<typename TYPE>
      static inline std::shared_ptr<StatementFactory>factoryOfFunctionFactory(std::string const&name){
        class Factory: public FunctionFactory{
          public:
            Factory(std::string const&name,Uses maxUses = 1):FunctionFactory(name,maxUses){}
            virtual ~Factory(){}
            virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister>const&fr)override{
              return std::make_shared<TYPE>(fr,fr->getFunctionId(this->_name));
            }
        };
        return std::make_shared<Factory>(name);
      }
  }
}
