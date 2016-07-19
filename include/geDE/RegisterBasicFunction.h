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

   template<typename OUTPUT,typename CLASS,typename...ARGS>
      inline TypeRegister::DescriptionVector getClassDescription(
          std::shared_ptr<TypeRegister>const&tr,
          OUTPUT(CLASS::*)(ARGS...)){
        assert(tr!=nullptr);
        TypeRegister::DescriptionVector result;
        result.push_back(TypeRegister::FCE);
        result.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<OUTPUT>()));
        result.push_back(sizeof...(ARGS)+1);
        TypeRegister::DescriptionVector ar{tr->getTypeId(TypeRegister::getTypeKeyword<ARGS>())...};
        result.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<CLASS>()));
        for(auto const&x:ar)result.push_back(x);
        return result;
      }


    template<typename OUTPUT,typename...ARGS,std::size_t...I>
      OUTPUT uber_call(Function*mf,OUTPUT(*FCE)(ARGS...),ge::core::index_sequence<I...>){
        assert(mf!=nullptr);
        assert(FCE!=nullptr);
#if defined(_MSC_VER) && _MSC_VER<1900
        return FCE(/*(const ARGS&...)*/(*mf->getInputData(I))...);
#else
        return FCE(/*(const ARGS&)*/(*mf->getInputData(I))...);
#endif
      }

    template<typename OUTPUT,typename CLASS,typename...ARGS,std::size_t...I>
      OUTPUT uber_class_call(Function*mf,OUTPUT(CLASS::*fce)(ARGS...),ge::core::index_sequence<I...>){
        assert(mf!=nullptr);
        assert(fce!=nullptr);
        using emptyType = OUTPUT(Empty::*)(ARGS...);
#if defined(_MSC_VER) && _MSC_VER<1900
        return (*(Empty**)(*mf->getInputData(0))->*((emptyType)fce))(/*(const ARGS&...)*/(*mf->getInputData(1+I))...);
#else
        return ((Empty*)(*mf->getInputData(0))->*((emptyType)fce))(/*(const ARGS&)*/(*mf->getInputData(1+I))...);
#endif
      }


    template<typename...ARGS,std::size_t...I>
      bool sig_uber_call(Function*mf,bool(*SIG)(ARGS...),ge::core::index_sequence<I...>){
        assert(mf!=nullptr);
        assert(SIG!=nullptr);
#if defined(_MSC_VER) && _MSC_VER<1900
        return SIG(/*(const ARGS&...)*/(*mf->getInputData(I))...);
#else
        return SIG(/*(const ARGS&)*/(*mf->getInputData(I))...);
#endif
      }



    template<typename OUTPUT,typename...ARGS>
      FunctionRegister::FunctionID registerBasicFunction(
          std::shared_ptr<FunctionRegister>const&fr,
          const std::string name,
          OUTPUT(*fce)(ARGS...),
          bool(*sig)(ARGS...) = nullptr){
        assert(fr!=nullptr);
        assert(fr->getTypeRegister()!=nullptr);
        static const std::string ss=name;
        auto tr = fr->getTypeRegister();
        auto tid = tr->addCompositeType("",getDescription(tr,fce));

        class BasicFunction: public AtomicFunction{
          protected:
            using FF = OUTPUT(*)(ARGS...);
            using SIGFF = bool(*)(ARGS...);
            FF _fceImpl;
            SIGFF _sigImpl;
          public:
            BasicFunction(
                std::shared_ptr<FunctionRegister>const&fr,
                FunctionRegister::FunctionID                     id):AtomicFunction(fr,id){
              this->_fceImpl=reinterpret_cast<FF>(fr->getImplementation(this->_id));
              this->_sigImpl=reinterpret_cast<SIGFF>(fr->getSignalingDecider(this->_id));
            }
            virtual ~BasicFunction(){}
          protected:
            virtual bool _do(){
              assert(this!=nullptr);

              bool doUberCall = true;
              if(this->_sigImpl)
                doUberCall = sig_uber_call(this,this->_sigImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              if(!doUberCall)return false;
              *this->getOutputData() = uber_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              //auto ret = uber_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              //std::memcpy(this->getOutputData()->getData(),&ret,sizeof(OUTPUT));
              //*(OUTPUT*)(*this->getOutputData()) = uber_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              return true;
            }
        };
        auto f=fr->addFunction(tid,name,factoryOfFunctionFactory<BasicFunction>(name));
        fr->addImplementation(f,reinterpret_cast<FunctionRegister::Implementation>(fce));
        fr->addSignalingDecider(f,reinterpret_cast<FunctionRegister::SignalingDecider>(sig));
        return f;
      }

    template<typename OUTPUT,typename CLASS,typename...ARGS>
      FunctionRegister::FunctionID registerClassFunction(
          std::shared_ptr<FunctionRegister>const&fr,
          const std::string name,
          OUTPUT(CLASS::*fce)(ARGS...),
          bool(*SIG)(ARGS...) = nullptr){
        assert(fr!=nullptr);
        assert(fr->getTypeRegister()!=nullptr);
        static const std::string ss=name;
        auto tr = fr->getTypeRegister();
        auto tid = tr->addCompositeType("",getClassDescription(tr,fce));

        class BasicFunction: public AtomicFunction{
          protected:
            using FF = OUTPUT(CLASS::*)(ARGS...);
            using SIGFF = bool(*)(ARGS...);
            FF _fceImpl;
            SIGFF _sigImpl;
          public:
            BasicFunction(
                std::shared_ptr<FunctionRegister>const&fr,
                FunctionRegister::FunctionID           id):AtomicFunction(fr,id){
              this->_fceImpl=reinterpret_cast<FF>(fr->getClassImplementation(this->_id));
              this->_sigImpl=reinterpret_cast<SIGFF>(fr->getSignalingDecider(this->_id));
            }
            virtual ~BasicFunction(){}
          protected:
            virtual bool _do(){
              assert(this!=nullptr);

              bool doUberCall = true;
              if(this->_sigImpl)
                doUberCall = sig_uber_call(this,this->_sigImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              if(!doUberCall)return false;
              *this->getOutputData() = uber_class_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              //auto ret = uber_class_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              //std::memcpy(this->getOutputData()->getData(),&ret,sizeof(OUTPUT));
              //*(OUTPUT*)(*this->getOutputData()) = uber_class_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              return true;
            }
        };
        auto f=fr->addFunction(tid,name,factoryOfFunctionFactory<BasicFunction>(name));
        fr->addClassImplementation(f,reinterpret_cast<FunctionRegister::ClassImplementation>(fce));
        fr->addSignalingDecider(f,reinterpret_cast<FunctionRegister::SignalingDecider>(SIG));
        return f;
      }

  }
}
