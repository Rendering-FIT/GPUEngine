#pragma once

#include<geCore/FunctionFactory.h>
#include<vector>
#include<cassert>

namespace ge{
  namespace core{
    class ResourceFactory;
    class GECORE_EXPORT FunctionNodeFactory: public FunctionFactory{
      protected:
        std::shared_ptr<FunctionFactory>functionFactory = nullptr;
        std::vector<std::shared_ptr<ResourceFactory>>resourceFactories;
        std::vector<std::shared_ptr<FunctionFactory>>inputFactories;
      public:
        FunctionNodeFactory(std::string name = "",Uses maxUses = 1);
        void setFactory(std::shared_ptr<StatementFactory>const&fac);
        void addResourceFactory(std::shared_ptr<ResourceFactory>const&factory);
        void addInputFactory(std::shared_ptr<StatementFactory>const&factory);
        virtual ~FunctionNodeFactory();
        inline std::shared_ptr<FunctionFactory>const&getInputFactory(size_t input)const;
        void reset();
        virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister>const&fr);
    };

    inline std::shared_ptr<FunctionFactory>const&FunctionNodeFactory::getInputFactory(size_t input)const{
      assert(this!=nullptr);
      assert(input<this->inputFactories.size());
      return this->inputFactories.at(input);
    }
  }
}


