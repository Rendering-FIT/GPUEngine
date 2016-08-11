#pragma once

#include<geDE/FunctionFactory.h>
#include<vector>

namespace ge{
  namespace de{
    class ResourceFactory;
    class GEDE_EXPORT FunctionNodeFactory: public FunctionFactory{
      public:
        using InputFactoryVector = std::vector<std::shared_ptr<FunctionFactory>>;
      protected:
        std::shared_ptr<FunctionFactory>functionFactory = nullptr;
        std::vector<std::shared_ptr<ResourceFactory>>resourceFactories;
        InputFactoryVector inputFactories;
      public:
        FunctionNodeFactory(Uses maxUses = 0);
        void setFactory(std::shared_ptr<StatementFactory>const&fac);
        void addResourceFactory(std::shared_ptr<ResourceFactory>const&factory);
        void addInputFactory(std::shared_ptr<StatementFactory>const&factory);
        virtual ~FunctionNodeFactory();
        inline std::shared_ptr<FunctionFactory>const&getInputFactory(size_t input)const;
        void reset();
        virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister>const&fr)override;

        std::shared_ptr<FunctionFactory>const&getFactory()const;
        size_t getNofInputs()const;
        virtual FunctionId getFunctionId()const override;
    };

    inline std::shared_ptr<FunctionFactory>const&FunctionNodeFactory::getInputFactory(size_t input)const{
      PRINT_CALL_STACK(input);
      assert(this!=nullptr);
      assert(input<this->inputFactories.size());
      return this->inputFactories.at(input);
    }
  }
}


