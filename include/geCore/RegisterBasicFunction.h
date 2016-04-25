#pragma once

#include<geCore/AtomicFunction.h>
#include<geCore/FactoryOfFunctionFactory.h>

namespace ge{
  namespace core{
   template<typename OUTPUT,typename...ARGS>
      inline std::vector<ge::core::TypeRegister::DescriptionElement>getDescription(
          std::shared_ptr<ge::core::TypeRegister>const&tr,
          OUTPUT(*)(ARGS...)){
        assert(tr!=nullptr);
        std::vector<ge::core::TypeRegister::DescriptionElement>result;
        result.push_back(ge::core::TypeRegister::FCE);
        result.push_back(tr->getTypeId(ge::core::TypeRegister::getTypeKeyword<OUTPUT>()));
        result.push_back(sizeof...(ARGS));
        std::vector<ge::core::TypeRegister::DescriptionElement> ar(tr->getTypeId(ge::core::TypeRegister::getTypeKeyword<ARGS>())...);
        for(auto x:ar)result.push_back(x);
        return result;
      }

    template<typename OUTPUT,typename...ARGS,std::size_t...I>
      OUTPUT uber_call(Function*mf,OUTPUT(*FCE)(ARGS...),ge::core::index_sequence<I...>){
        assert(mf!=nullptr);
        assert(FCE!=nullptr);
#if defined(_MSC_VER) && _MSC_VER<1900
        return FCE((ARGS&...)(*mf->getInputData(I))...);
#else
        return FCE((ARGS&)(*mf->getInputData(I))...);
#endif
      }

    template<typename OUTPUT,typename...ARGS>
      void registerBasicFunction(
          std::shared_ptr<ge::core::FunctionRegister>const&fr,
          const std::string name,
          OUTPUT(*FCE)(ARGS...)){
        assert(fr!=nullptr);
        assert(fr->getTypeRegister()!=nullptr);
        static const std::string ss=name;
        auto tr = fr->getTypeRegister();
        auto tid = tr->addType("",getDescription(tr,FCE));

        class BasicFunction: public ge::core::AtomicFunction{
          public:
            BasicFunction(
                std::shared_ptr<ge::core::FunctionRegister>const&f ,
                FunctionRegister::FunctionID                     id):AtomicFunction(f,id){}
            virtual ~BasicFunction(){}
          protected:
            virtual bool _do(){
              assert(this!=nullptr);
              assert(this->_functionRegister!=nullptr);
              typedef OUTPUT(*FF)(ARGS...);
              FF f=reinterpret_cast<FF>(this->_functionRegister->getImplementation(this->_id));
              (OUTPUT&)(*this->getOutputData()) = uber_call(this,f,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              return true;
            }
        };
        auto f=fr->addFunction(tid,name,ge::core::factoryOfFunctionFactory<BasicFunction>(name));
        fr->addImplementation(f,reinterpret_cast<void(*)()>(FCE));
      }


  }
}
