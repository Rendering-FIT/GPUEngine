#pragma once

#include<geDE/AtomicFunction.h>
#include<geDE/FactoryOfFunctionFactory.h>

namespace ge{
  namespace de{
   template<typename OUTPUT,typename...ARGS>
      inline TypeRegister::DescriptionVector getDescription(
          std::shared_ptr<TypeRegister>const&tr,
          OUTPUT(*)(ARGS...)){
        assert(tr!=nullptr);
        TypeRegister::DescriptionVector result;
        result.push_back(TypeRegister::FCE);
        result.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<OUTPUT>()));
        result.push_back(sizeof...(ARGS));
        TypeRegister::DescriptionVector ar{tr->getTypeId(TypeRegister::getTypeKeyword<ARGS>())...};
        for(auto const&x:ar)result.push_back(x);
        return result;
      }

    template<typename OUTPUT,typename...ARGS,std::size_t...I>
      OUTPUT uber_call(Function*mf,OUTPUT(*FCE)(ARGS...),ge::core::index_sequence<I...>){
        assert(mf!=nullptr);
        assert(FCE!=nullptr);
#if defined(_MSC_VER) && _MSC_VER<1900
        return FCE((ARGS const&...)(*mf->getInputData(I))...);
#else
        return FCE((ARGS const&)(*mf->getInputData(I))...);
#endif
      }

    template<typename OUTPUT,typename...ARGS>
      FunctionRegister::FunctionID registerBasicFunction(
          std::shared_ptr<FunctionRegister>const&fr,
          const std::string name,
          OUTPUT(*FCE)(ARGS...)){
        assert(fr!=nullptr);
        assert(fr->getTypeRegister()!=nullptr);
        static const std::string ss=name;
        auto tr = fr->getTypeRegister();
        auto tid = tr->addCompositeType("",getDescription(tr,FCE));

        class BasicFunction: public AtomicFunction{
          protected:
            using FF = OUTPUT(*)(ARGS...);
            FF _fceImpl;
          public:
            BasicFunction(
                std::shared_ptr<FunctionRegister>const&fr,
                FunctionRegister::FunctionID                     id):AtomicFunction(fr,id){
              this->_fceImpl=reinterpret_cast<FF>(fr->getImplementation(this->_id));
            }
            virtual ~BasicFunction(){}
          protected:
            virtual bool _do(){
              assert(this!=nullptr);
              //assert(this->_functionRegister!=nullptr);
              //typedef OUTPUT(*FF)(ARGS...);
              //FF f=reinterpret_cast<FF>(this->_functionRegister->getImplementation(this->_id));
              //(OUTPUT&)(*this->getOutputData()) = uber_call(this,f,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              //(OUTPUT&)(*this->getOutputData()) = uber_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              *(OUTPUT*)(*this->getOutputData()) = uber_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              return true;
            }
        };
        auto f=fr->addFunction(tid,name,factoryOfFunctionFactory<BasicFunction>(name));
        fr->addImplementation(f,reinterpret_cast<void(*)()>(FCE));
        return f;
      }


  }
}
