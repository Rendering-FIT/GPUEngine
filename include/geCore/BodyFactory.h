#pragma once

#include<geCore/StatementFactory.h>

namespace ge{
  namespace core{
    class /*GECORE_EXPORT*/ BodyFactory: public StatementFactory{
      public:
        inline BodyFactory(std::string name = "",unsigned maxUses = 1);
        inline virtual ~BodyFactory();
        inline virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister> const&);
        std::vector<std::shared_ptr<StatementFactory>>factories;
    };

    inline BodyFactory::BodyFactory(std::string name,unsigned maxUses):StatementFactory(name,maxUses){
    }

    inline BodyFactory::~BodyFactory(){
    }

    inline std::shared_ptr<Statement>BodyFactory::_do(std::shared_ptr<FunctionRegister>const&fr){
      auto result = std::make_shared<Body>();
      for(auto x:this->factories)
        result->addStatement((*x)(fr));
      return result;
    }
  }
}

