#pragma once

#include<geDE/Resource.h>
#include<geDE/AtomicFunction.h>
#include<geDE/FactoryOfFunctionFactory.h>
#include<geCore/Dtemplates.h>

namespace ge{
  namespace de{
    template<typename OUTPUT,typename...ARGS,std::size_t...I>
      inline OUTPUT uber_call(Function*mf,OUTPUT(*fce)(ARGS...),ge::core::index_sequence<I...>){
        PRINT_CALL_STACK(mf,fce);
        assert(mf!=nullptr);
        assert(fce!=nullptr);
        return fce((*mf->getInputData(I))...);
      }

    template<typename OUTPUT,typename CLASS,typename...ARGS,std::size_t...I>
      inline OUTPUT uber_class_call(Function*mf,OUTPUT(CLASS::*fce)(ARGS...),ge::core::index_sequence<I...>){
        PRINT_CALL_STACK(mf,fce);
        assert(mf!=nullptr);
        assert(fce!=nullptr);
        using EmptyType = OUTPUT(CLASS::*)(ARGS...);
        if(mf->getInputData(0)->isPointer()){
          assert(mf->getInputData(0)!=nullptr);
          assert(mf->getInputData(0)->getData()!=nullptr);
          return ((CLASS*)(*(void**)mf->getInputData(0)->getData())->*((EmptyType)fce))((*mf->getInputData(1+I))...);
        }else
          return ((CLASS&)(*mf->getInputData(0)).*((EmptyType)fce))((*mf->getInputData(1+I))...);
      }


    template<typename...ARGS,std::size_t...I>
      inline bool sig_uber_call(Function*mf,bool(*sig)(ARGS...),ge::core::index_sequence<I...>){
        PRINT_CALL_STACK(mf,sig);
        assert(mf!=nullptr);
        assert(sig!=nullptr);
        return sig((*mf->getInputData(I))...);
      }

#define GE_DE_REGISTER_BASIC_FUNCTION_PROLOGUE()\
    PRINT_CALL_STACK(fr,name,fce,sig);\
    assert(fr!=nullptr);\
    assert(fr->getTypeRegister()!=nullptr);\
    static const std::string ss=name;\
    auto tr = fr->getTypeRegister();\
    auto tid = tr->addType<OUTPUT(ARGS...)>();\
    class BasicFunction: public AtomicFunction{\
      protected:\
                \
      using FceType          = OUTPUT(*)(ARGS...);\
      using SignalingFceType = bool(*)(ARGS...);\
      FceType          _fceImpl;\
      SignalingFceType _sigImpl;\
      public:\
             \
      BasicFunction(\
          std::shared_ptr<FunctionRegister>const&fr,\
          FunctionId                     id):AtomicFunction(fr,id){\
        PRINT_CALL_STACK(fr,id);\
        assert(this!=nullptr);\
        assert(fr!=nullptr);\
        this->_fceImpl=reinterpret_cast<FceType>(fr->getImplementation(this->_id));\
        this->_sigImpl=reinterpret_cast<SignalingFceType>(fr->getSignalingDecider(this->_id));\
      }\
      virtual ~BasicFunction(){\
        PRINT_CALL_STACK();\
      }\
      protected:\
                \
      virtual bool _do(){\
        PRINT_CALL_STACK();\
        assert(this!=nullptr);\
        bool doUberCall = true;\
        if(this->_sigImpl)\
        doUberCall = sig_uber_call(this,this->_sigImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});\
        if(!doUberCall)return false;\
        assert(this->getOutputData()!=nullptr)//}}

#define GE_DE_REGISTER_BASIC_FUNCTION_EPILOGUE()\
    return true;\
    /*{*/}\
    /*{*/};\
    auto f=fr->addFunction(tid,name,factoryOfFunctionFactory<BasicFunction>(name));\
    fr->addImplementation(f,reinterpret_cast<FunctionRegister::Implementation>(fce));\
    fr->addSignalingDecider(f,reinterpret_cast<FunctionRegister::SignalingDecider>(sig));\
    return f


    template<typename OUTPUT,typename...ARGS,typename std::enable_if<!std::is_same<OUTPUT,void>::value,unsigned>::type = 0>
      FunctionId registerBasicFunction(
          std::shared_ptr<FunctionRegister>const&fr,
          const std::string name,
          OUTPUT(*fce)(ARGS...),
          bool(*sig)(ARGS...) = nullptr){
        GE_DE_REGISTER_BASIC_FUNCTION_PROLOGUE();
        *this->getOutputData() = uber_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
        GE_DE_REGISTER_BASIC_FUNCTION_EPILOGUE();
      }

    template<typename OUTPUT,typename...ARGS,typename std::enable_if<std::is_same<OUTPUT,void>::value,unsigned>::type = 0>
      FunctionId registerBasicFunction(
          std::shared_ptr<FunctionRegister>const&fr,
          const std::string name,
          OUTPUT(*fce)(ARGS...),
          bool(*sig)(ARGS...) = nullptr){
        GE_DE_REGISTER_BASIC_FUNCTION_PROLOGUE();
        uber_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
        GE_DE_REGISTER_BASIC_FUNCTION_EPILOGUE();
      }


    template<typename OUTPUT,typename CLASS,typename...ARGS,typename std::enable_if<!std::is_same<OUTPUT,void>::value,unsigned>::type = 0>
      FunctionId registerClassFunction(
          std::shared_ptr<FunctionRegister>const&fr,
          const std::string name,
          OUTPUT(CLASS::*fce)(ARGS...),
          bool(*sig)(ARGS...) = nullptr){
        PRINT_CALL_STACK(fr,name,fce,sig);
        assert(fr!=nullptr);
        assert(fr->getTypeRegister()!=nullptr);
        static const std::string ss=name;
        auto tr = fr->getTypeRegister();
        auto tid = tr->addType<OUTPUT(CLASS::*)(ARGS...)>();

        class BasicFunction: public AtomicFunction{
          protected:
            using FF = OUTPUT(CLASS::*)(ARGS...);
            using SIGFF = bool(*)(ARGS...);
            FF _fceImpl;
            SIGFF _sigImpl;
          public:
#if defined(_MSC_VER)
            class MyCLSImpl: public FunctionRegister::CLSImpl{
              public:
                using FF = OUTPUT(CLASS::*)(ARGS...);
                FF ptr;
                MyCLSImpl(FF const&z){
                  this->ptr = z;
                }
            };
#endif
            BasicFunction(
                std::shared_ptr<FunctionRegister>const&fr,
                FunctionId           id):AtomicFunction(fr,id){
              PRINT_CALL_STACK(fr,id);
              assert(this!=nullptr);
              assert(fr!=nullptr);
#if defined(_MSC_VER)
              this->_fceImpl = ((MyCLSImpl*)fr->getClassImplementation(this->_id))->ptr;
#else
              this->_fceImpl=reinterpret_cast<FF>(fr->getClassImplementation(this->_id));
#endif
              this->_sigImpl=reinterpret_cast<SIGFF>(fr->getSignalingDecider(this->_id));
            }
            virtual ~BasicFunction(){
              PRINT_CALL_STACK();
            }
          protected:
            virtual bool _do(){
              assert(this!=nullptr);

              bool doUberCall = true;
              if(this->_sigImpl)
                doUberCall = sig_uber_call(this,this->_sigImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              if(!doUberCall)return false;
              *this->getOutputData() = uber_class_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              return true;
            }
        };
        auto f=fr->addFunction(tid,name,factoryOfFunctionFactory<BasicFunction>(name));
#if defined(_MSC_VER)
        fr->addClassImplementation(f,new BasicFunction::MyCLSImpl(fce));
#else
        fr->addClassImplementation(f,reinterpret_cast<FunctionRegister::ClassImplementation>(fce));
#endif
        fr->addSignalingDecider(f,reinterpret_cast<FunctionRegister::SignalingDecider>(sig));
        return f;
      }

    template<typename OUTPUT,typename CLASS,typename...ARGS,typename std::enable_if<std::is_same<OUTPUT,void>::value,unsigned>::type = 0>
      FunctionId registerClassFunction(
          std::shared_ptr<FunctionRegister>const&fr,
          const std::string name,
          OUTPUT(CLASS::*fce)(ARGS...),
          bool(*sig)(ARGS...) = nullptr){
        PRINT_CALL_STACK(fr,name,fce,sig);
        assert(fr!=nullptr);
        assert(fr->getTypeRegister()!=nullptr);
        static const std::string ss=name;
        auto tr = fr->getTypeRegister();
        auto tid = tr->addType<OUTPUT(CLASS::*)(ARGS...)>();

        class BasicFunction: public AtomicFunction{
          protected:
            using FF = OUTPUT(CLASS::*)(ARGS...);
            using SIGFF = bool(*)(ARGS...);
            FF _fceImpl;
            SIGFF _sigImpl;
          public:
            BasicFunction(
                std::shared_ptr<FunctionRegister>const&fr,
                FunctionId           id):AtomicFunction(fr,id){
              PRINT_CALL_STACK(fr,id);
              assert(this!=nullptr);
              assert(fr!=nullptr);
              this->_fceImpl=reinterpret_cast<FF>(fr->getClassImplementation(this->_id));
              this->_sigImpl=reinterpret_cast<SIGFF>(fr->getSignalingDecider(this->_id));
            }
            virtual ~BasicFunction(){
              PRINT_CALL_STACK();
            }
          protected:
            virtual bool _do(){
              PRINT_CALL_STACK();
              assert(this!=nullptr);

              bool doUberCall = true;
              if(this->_sigImpl)
                doUberCall = sig_uber_call(this,this->_sigImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              if(!doUberCall)return false;
              uber_class_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              return true;
            }
        };
        auto f=fr->addFunction(tid,name,factoryOfFunctionFactory<BasicFunction>(name));
        fr->addClassImplementation(f,reinterpret_cast<FunctionRegister::ClassImplementation>(fce));
        fr->addSignalingDecider(f,reinterpret_cast<FunctionRegister::SignalingDecider>(sig));
        return f;
      }

  }
}
