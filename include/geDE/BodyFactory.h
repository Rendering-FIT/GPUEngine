#pragma once

#include<geDE/StatementFactory.h>
#include<geDE/Body.h>
#include<vector>

namespace ge{
  namespace de{
    class /*GECORE_EXPORT*/ BodyFactory: public StatementFactory{
      public:
        inline BodyFactory(/*std::string name = "",*/unsigned maxUses = 0);
        inline virtual ~BodyFactory();
        inline virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister> const&);
        std::vector<std::shared_ptr<StatementFactory>>factories;
    };

    inline BodyFactory::BodyFactory(/*std::string name,*/unsigned maxUses):StatementFactory(/*name,*/maxUses){
      PRINT_CALL_STACK();
    }

    inline BodyFactory::~BodyFactory(){
      PRINT_CALL_STACK();
    }

    inline std::shared_ptr<Statement>BodyFactory::_do(std::shared_ptr<FunctionRegister>const&fr){
      PRINT_CALL_STACK(fr);
      assert(this!=nullptr);
      auto result = std::make_shared<Body>();
      for(auto const&x:this->factories)
        result->addStatement((*x)(fr));
      return result;
    }
  }
}

