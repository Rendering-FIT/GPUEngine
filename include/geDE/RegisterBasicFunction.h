#pragma once

#include<geDE/Resource.h>
#include<geDE/AtomicFunction.h>
#include<geDE/FactoryOfFunctionFactory.h>
#include<geCore/Dtemplates.h>

namespace ge{
  namespace de{
    /**
     * @brief This function register external non void function into FunctionRegister
     *
     * @param fr function register
     * @param name name of function
     * @param fce function pointer that will be registered
     * @param sig signaling function, if this function returns true, output is marked as changed
     * when no sig function is provided output is always marked as changed
     *
     * @return function id of registered function
     */
    template<typename OUTPUT,typename...ARGS,typename std::enable_if<!std::is_same<OUTPUT,void>::value,unsigned>::type = 0>
      FunctionId registerBasicFunction(std::shared_ptr<FunctionRegister>const&fr,std::string const&name,OUTPUT(*fce)(ARGS...),bool(*sig)(ARGS...) = nullptr);
    /**
     * @brief This function register external void function into FunctionRegister
     *
     * @param fr function register
     * @param name name of function
     * @param fce function pointer that will be registered
     * @param sig signaling function, if this function returns true, output is marked as changed
     * when no sig function is provided output is always marked as changed
     *
     * @return function id of registered function
     */
    template<typename OUTPUT,typename...ARGS,typename std::enable_if<std::is_same<OUTPUT,void>::value,unsigned>::type = 0>
      FunctionId registerBasicFunction(std::shared_ptr<FunctionRegister>const&fr,std::string const&name,OUTPUT(*fce)(ARGS...),bool(*sig)(ARGS...) = nullptr);
    /**
     * @brief This function register member non void function into FunctionRegister
     *
     * @param fr function register
     * @param name name of function
     * @param fce member function pointer that will be registered
     * @param sig signaling function, if this function returns true, output is marked as changed
     * when no sig function is provided output is always marked as changed
     *
     * @return function id of registered function
     */
    template<typename OUTPUT,typename CLASS,typename...ARGS,typename std::enable_if<!std::is_same<OUTPUT,void>::value,unsigned>::type = 0>
      FunctionId registerClassFunction(std::shared_ptr<FunctionRegister>const&fr,std::string const&name,OUTPUT(CLASS::*fce)(ARGS...),bool(*sig)(ARGS...) = nullptr);
    /**
     * @brief This function register member void function into FunctionRegister
     *
     * @param fr function register
     * @param name name of function
     * @param fce member function pointer that will be registered
     * @param sig signaling function, if this function returns true, output is marked as changed
     * when no sig function is provided output is always marked as changed
     *
     * @return function id of registered function
     */
    template<typename OUTPUT,typename CLASS,typename...ARGS,typename std::enable_if<std::is_same<OUTPUT,void>::value,unsigned>::type = 0>
      FunctionId registerClassFunction(std::shared_ptr<FunctionRegister>const&fr,std::string const&name,OUTPUT(CLASS::*fce)(ARGS...),bool(*sig)(ARGS...) = nullptr);
    /**
     * @brief This function register member non void function into FunctionRegister
     *
     * @param fr function register
     * @param name name of function
     * @param fce member function pointer that will be registered
     * @param sig signaling function, if this function returns true, output is marked as changed
     * when no sig function is provided output is always marked as changed
     *
     * @return function id of registered function
     */
    template<typename OUTPUT,typename CLASS,typename...ARGS,typename std::enable_if<!std::is_same<OUTPUT,void>::value,unsigned>::type = 0>
      FunctionId registerClassFunction(std::shared_ptr<FunctionRegister>const&fr,std::string const&name,OUTPUT(CLASS::*fce)(ARGS...)const,bool(*sig)(ARGS...) = nullptr);
    /**
     * @brief This function register member void function into FunctionRegister
     *
     * @param fr function register
     * @param name name of function
     * @param fce member function pointer that will be registered
     * @param sig signaling function, if this function returns true, output is marked as changed
     * when no sig function is provided output is always marked as changed
     *
     * @return function id of registered function
     */
    template<typename OUTPUT,typename CLASS,typename...ARGS,typename std::enable_if<std::is_same<OUTPUT,void>::value,unsigned>::type = 0>
      FunctionId registerClassFunction(std::shared_ptr<FunctionRegister>const&fr,std::string const&name,OUTPUT(CLASS::*fce)(ARGS...)const,bool(*sig)(ARGS...) = nullptr);




/////////////YOU SHOULD NOT LOOK BELOW THIS LINE////////////////

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

    template<typename OUTPUT,typename CLASS,typename...ARGS,std::size_t...I>
      inline OUTPUT uber_class_call(Function*mf,OUTPUT(CLASS::*fce)(ARGS...)const,ge::core::index_sequence<I...>){
        PRINT_CALL_STACK(mf,fce);
        assert(mf!=nullptr);
        assert(fce!=nullptr);
        using EmptyType = OUTPUT(CLASS::*)(ARGS...)const;
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
        if(!doUberCall)return false//}}

#define GE_DE_REGISTER_BASIC_FUNCTION_EPILOGUE()\
    return true;\
    /*{*/}\
    /*{*/};\
    auto f=fr->addFunction(tid,name,factoryOfFunctionFactory<BasicFunction>(/*name*/));\
    fr->addImplementation(f,reinterpret_cast<FunctionRegister::Implementation>(fce));\
    fr->addSignalingDecider(f,reinterpret_cast<FunctionRegister::SignalingDecider>(sig));\
    return f


    template<typename OUTPUT,typename...ARGS,typename std::enable_if<!std::is_same<OUTPUT,void>::value,unsigned>::type>
      FunctionId registerBasicFunction(
          std::shared_ptr<FunctionRegister>const&fr,
          std::string const&name,
          OUTPUT(*fce)(ARGS...),
          bool(*sig)(ARGS...)){
        GE_DE_REGISTER_BASIC_FUNCTION_PROLOGUE();
        assert(this->getOutputData()!=nullptr);
        *this->getOutputData() = uber_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
        GE_DE_REGISTER_BASIC_FUNCTION_EPILOGUE();
      }

    template<typename OUTPUT,typename...ARGS,typename std::enable_if<std::is_same<OUTPUT,void>::value,unsigned>::type>
      FunctionId registerBasicFunction(
          std::shared_ptr<FunctionRegister>const&fr,
          std::string const&name,
          OUTPUT(*fce)(ARGS...),
          bool(*sig)(ARGS...)){
        GE_DE_REGISTER_BASIC_FUNCTION_PROLOGUE();
        uber_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
        GE_DE_REGISTER_BASIC_FUNCTION_EPILOGUE();
      }

#define GE_DE_REGISTER_CLASS_FUNCTION_PROLOGUE()\
    PRINT_CALL_STACK(fr,name,fce,sig);\
    assert(fr!=nullptr);\
    assert(fr->getTypeRegister()!=nullptr);\
    auto tr = fr->getTypeRegister();\
    auto tid = tr->addType<decltype(fce)>();\
    class BasicFunction: public AtomicFunction{\
      protected:\
                \
      using FceType          = decltype(fce);/*OUTPUT(CLASS::*)(ARGS...);*/\
      using SignalingFceType = bool(*)(ARGS...);\
      FceType _fceImpl;\
      SignalingFceType _sigImpl;\
      public:\
             \
      class MyCLSImpl: public FunctionRegister::CLSImpl{\
        public:\
               \
        using FceType = decltype(fce);/*OUTPUT(CLASS::*)(ARGS...);*/\
        FceType ptr;\
        MyCLSImpl(FceType const&z){\
          this->ptr = z;\
        }\
      };\
      BasicFunction(\
          std::shared_ptr<FunctionRegister>const&fr,\
          FunctionId           id):AtomicFunction(fr,id){\
        PRINT_CALL_STACK(fr,id);\
        assert(this!=nullptr);\
        assert(fr!=nullptr);\
        this->_fceImpl = ((MyCLSImpl*)fr->getClassImplementation(this->_id))->ptr;\
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
        if(!doUberCall)return false//}}

#define GE_DE_REGISTER_CLASS_FUNCTION_EPILOGUE()\
    return true;\
    /*{*/}\
    /*{*/};\
    auto f=fr->addFunction(tid,name,factoryOfFunctionFactory<BasicFunction>(/*name*/));\
    fr->addClassImplementation(f,new typename BasicFunction::MyCLSImpl(fce));\
    fr->addSignalingDecider(f,reinterpret_cast<FunctionRegister::SignalingDecider>(sig));\
    return f


    template<typename OUTPUT,typename CLASS,typename...ARGS,typename std::enable_if<!std::is_same<OUTPUT,void>::value,unsigned>::type>
      FunctionId registerClassFunction(
          std::shared_ptr<FunctionRegister>const&fr,
          std::string const&name,
          OUTPUT(CLASS::*fce)(ARGS...),
          bool(*sig)(ARGS...)){
        GE_DE_REGISTER_CLASS_FUNCTION_PROLOGUE();
        assert(this->getOutputData()!=nullptr);
        *this->getOutputData() = uber_class_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
        GE_DE_REGISTER_CLASS_FUNCTION_EPILOGUE();
      }

    template<typename OUTPUT,typename CLASS,typename...ARGS,typename std::enable_if<std::is_same<OUTPUT,void>::value,unsigned>::type>
      FunctionId registerClassFunction(
          std::shared_ptr<FunctionRegister>const&fr,
          std::string const&name,
          OUTPUT(CLASS::*fce)(ARGS...),
          bool(*sig)(ARGS...)){
        GE_DE_REGISTER_CLASS_FUNCTION_PROLOGUE();
        uber_class_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
        GE_DE_REGISTER_CLASS_FUNCTION_EPILOGUE();
      }

    template<typename OUTPUT,typename CLASS,typename...ARGS,typename std::enable_if<!std::is_same<OUTPUT,void>::value,unsigned>::type>
      FunctionId registerClassFunction(
          std::shared_ptr<FunctionRegister>const&fr,
          std::string const&name,
          OUTPUT(CLASS::*fce)(ARGS...)const,
          bool(*sig)(ARGS...)){
        GE_DE_REGISTER_CLASS_FUNCTION_PROLOGUE();
        assert(this->getOutputData()!=nullptr);
        *this->getOutputData() = uber_class_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
        GE_DE_REGISTER_CLASS_FUNCTION_EPILOGUE();
      }

    template<typename OUTPUT,typename CLASS,typename...ARGS,typename std::enable_if<std::is_same<OUTPUT,void>::value,unsigned>::type>
      FunctionId registerClassFunction(
          std::shared_ptr<FunctionRegister>const&fr,
          std::string const&name,
          OUTPUT(CLASS::*fce)(ARGS...)const,
          bool(*sig)(ARGS...)){
        GE_DE_REGISTER_CLASS_FUNCTION_PROLOGUE();
        uber_class_call(this,this->_fceImpl,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
        GE_DE_REGISTER_CLASS_FUNCTION_EPILOGUE();
      }

  }
}

