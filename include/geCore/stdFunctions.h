#pragma once

#include<geCore/interpret.h>
#include<geCore/Accessor.h>

namespace ge{
  namespace core{

    class GECORE_EXPORT Nullary: public Function{
      public:
        Nullary(std::shared_ptr<ge::core::TypeRegister>const&tr,
            std::shared_ptr<ge::core::Accessor>data = nullptr);
        template<typename TYPE>
          Nullary(std::shared_ptr<ge::core::TypeRegister>const&tr,TYPE const&data):Function(tr,{TypeRegister::FCE,TypeRegister::UNREGISTERED,0},"Nullary"){
            this->_getOutput().data=tr->sharedAccessor<TYPE>(data);//data);
          }
        template<typename TYPE>
          void update(TYPE const&data){
            (TYPE&)*this->_getOutput().data=data;
            this->_updateTicks++;
          }
        static inline std::shared_ptr<Function>sharedInstance(std::shared_ptr<ge::core::TypeRegister>const&tr){
          return std::make_shared<Nullary>(tr);
        }
        static inline std::string name(){
          return "Nullary";
        }
    };

#define DEF_CLASS_PROLOGUE2(CLASS,OUTPUT,INPUT1,INPUT2)\
    class CLASS: public Function{\
      public:\
            static inline std::shared_ptr<Function>sharedInstance(std::shared_ptr<ge::core::TypeRegister>const&tr){\
              return std::make_shared<CLASS<INPUT1>>(tr);\
            }\
            static inline std::string name(){\
              return #CLASS+std::string("_")+std::string(ge::core::TypeRegister::getTypeKeyword<INPUT1>());\
            }\
             CLASS(std::shared_ptr<ge::core::TypeRegister>const&tr,\
                   std::shared_ptr<ge::core::Accessor>const&output=nullptr):Function(tr,{\
                     ge::core::TypeRegister::FCE,\
                     ge::core::TypeRegister::getTypeDescription<OUTPUT>(),\
                     2,\
                     ge::core::TypeRegister::getTypeDescription<INPUT1>(),\
                     ge::core::TypeRegister::getTypeDescription<INPUT2>()\
                     },CLASS::name()){\
               /*this->_setOutput(  TypeRegister::getTypeTypeId<OUTPUT>());*/\
               /*this->_setInput (0,TypeRegister::getTypeTypeId<INPUT1>());*/\
               /*this->_setInput (1,TypeRegister::getTypeTypeId<INPUT2>());*/\
               this->bindOutput(output);\
             }\
      protected:\
        virtual bool _do(){//}}

#define DEF_CLASS_PROLOGUE2_NONTEMP(CLASS,OUTPUT,INPUT1,INPUT2)\
    class CLASS: public Function{\
      public:\
            static inline std::shared_ptr<Function>sharedInstance(std::shared_ptr<ge::core::TypeRegister>const&tr){\
              return std::make_shared<CLASS>(tr);\
            }\
            static inline std::string name(){\
              return #CLASS+std::string("_")+std::string(ge::core::TypeRegister::getTypeKeyword<INPUT1>());\
            }\
             CLASS(std::shared_ptr<ge::core::TypeRegister>const&tr,\
                   std::shared_ptr<ge::core::Accessor>const&output=nullptr):Function(tr,{\
                     ge::core::TypeRegister::FCE,\
                     ge::core::TypeRegister::getTypeDescription<OUTPUT>(),\
                     2,\
                     ge::core::TypeRegister::getTypeDescription<INPUT1>(),\
                     ge::core::TypeRegister::getTypeDescription<INPUT2>()\
                     },CLASS::name()){\
               /*this->_setOutput(  TypeRegister::getTypeTypeId<OUTPUT>());*/\
               /*this->_setInput (0,TypeRegister::getTypeTypeId<INPUT1>());*/\
               /*this->_setInput (1,TypeRegister::getTypeTypeId<INPUT2>());*/\
               this->bindOutput(output);\
             }\
      protected:\
        virtual bool _do(){//}}


#define DEF_CLASS_PROLOGUE1(CLASS,OUTPUT,INPUT1)\
    class CLASS: public Function{\
      public:\
            static inline std::shared_ptr<Function>sharedInstance(std::shared_ptr<ge::core::TypeRegister>const&tr){\
              return std::make_shared<CLASS<INPUT1>>(tr);\
            }\
             static inline std::string name(){\
               return #CLASS+std::string("_")+std::string(ge::core::TypeRegister::getTypeKeyword<INPUT1>());\
             }\
             CLASS(std::shared_ptr<ge::core::TypeRegister>const&tr,\
                 std::shared_ptr<ge::core::Accessor>const&output=nullptr):Function(tr,{\
                   ge::core::TypeRegister::FCE,\
                   ge::core::TypeRegister::getTypeDescription<OUTPUT>(),\
                   1,\
                   ge::core::TypeRegister::getTypeDescription<INPUT1>()\
                   },CLASS::name()){\
               /*this->_setOutput(  TypeRegister::getTypeTypeId<OUTPUT>());*/\
               /*this->_setInput (0,TypeRegister::getTypeTypeId<INPUT1>());*/\
               this->bindOutput(output);\
             }\
      protected:\
        virtual bool _do(){//}}

#define DEF_CLASS_EPILOGUE()/*{{*/\
          return true;\
        }\
    }

#define DEF_SPEC_OPERATOR_2(CLASS,OPERATOR,OUTPUT,INPUT1,INPUT2)\
    DEF_CLASS_PROLOGUE2(CLASS,OUTPUT,INPUT1,INPUT2);\
    if(this->hasOutput())\
    (OUTPUT&)*(this->_getOutput().data)=\
    (INPUT1&)(*this->getInputData(0)) OPERATOR\
    (INPUT2 )(*this->getInputData(1));\
    else\
    (INPUT1&)(*this->getInputData(0)) OPERATOR\
    (INPUT2 )(*this->getInputData(1));\
    DEF_CLASS_EPILOGUE()

    //OUTPUT means that function requires output to be defined

#define DEF_SPEC_OPERATOR_2OUTPUT(CLASS,OPERATOR,OUTPUT,INPUT1,INPUT2)\
    DEF_CLASS_PROLOGUE2_NONTEMP(CLASS,OUTPUT,INPUT1,INPUT2);\
    (OUTPUT&)*(this->_getOutput().data)=\
    (INPUT1&)(*this->getInputData(0)) OPERATOR\
    (INPUT2 )(*this->getInputData(1));\
    DEF_CLASS_EPILOGUE()

#define DEF_OPERATOR_2INT(CLASS,OPERATOR)\
    template<typename TYPE>\
    DEF_CLASS_PROLOGUE2(CLASS,TYPE,TYPE,TYPE);\
    if(this->hasOutput())\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->_getOutput().data)=\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->getInputData(0)) OPERATOR\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type )(*this->getInputData(1));\
    else\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->getInputData(0)) OPERATOR\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type )(*this->getInputData(1));\
    DEF_CLASS_EPILOGUE()

#define DEF_OPERATOR_2OUTPUT_INT(CLASS,OPERATOR)\
    template<typename TYPE>\
    DEF_CLASS_PROLOGUE2(CLASS,TYPE,TYPE,TYPE);\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->_getOutput().data)=\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->getInputData(0)) OPERATOR\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type )(*this->getInputData(1));\
    DEF_CLASS_EPILOGUE()

#define DEF_SPEC_OPERATOR_1INTPRE(CLASS,OPERATOR)\
    template<typename TYPE>\
    DEF_CLASS_PROLOGUE1(CLASS,TYPE,TYPE);\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->_getOutput().data)=\
    OPERATOR ((typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->getInputData(0)));\
    DEF_CLASS_EPILOGUE()

#define DEF_SPEC_OPERATOR_1INTPOST(CLASS,OPERATOR)\
    template<typename TYPE>\
    DEF_CLASS_PROLOGUE1(CLASS,TYPE,TYPE);\
    if(this->hasOutput())\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->_getOutput().data)=\
    ((typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->getInputData(0))) OPERATOR;\
    else\
    ((typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->getInputData(0))) OPERATOR;\
    DEF_CLASS_EPILOGUE()



#define DEF_OPERATOR_2(CLASS,OPERATOR,OUTPUT)\
    template<typename TYPE>\
    DEF_SPEC_OPERATOR_2(CLASS,OPERATOR,OUTPUT,TYPE,TYPE)

#define DEF_OPERATOR_2OUTPUT(CLASS,OPERATOR,OUTPUT)\
    template<typename TYPE>\
    DEF_SPEC_OPERATOR_2OUTPUT(CLASS,OPERATOR,OUTPUT,TYPE,TYPE)

    DEF_OPERATOR_2OUTPUT      (Add     ,+  ,TYPE);
    DEF_OPERATOR_2OUTPUT      (Sub     ,-  ,TYPE);
    DEF_OPERATOR_2OUTPUT      (Mul     ,*  ,TYPE);
    DEF_OPERATOR_2OUTPUT      (Div     ,/  ,TYPE);
    DEF_OPERATOR_2            (Ass     ,=  ,TYPE);
    DEF_OPERATOR_2            (Adds    ,+= ,TYPE);
    DEF_OPERATOR_2            (Subs    ,-= ,TYPE);
    DEF_OPERATOR_2            (Muls    ,*= ,TYPE);
    DEF_OPERATOR_2            (Divs    ,/= ,TYPE);
    DEF_OPERATOR_2OUTPUT      (Less    ,<  ,bool);
    DEF_OPERATOR_2OUTPUT      (Leq     ,<= ,bool);
    DEF_OPERATOR_2OUTPUT      (Greater ,>  ,bool);
    DEF_OPERATOR_2OUTPUT      (Geq     ,>= ,bool);
    DEF_OPERATOR_2OUTPUT      (Eq      ,== ,bool);
    DEF_OPERATOR_2OUTPUT      (Neq     ,!= ,bool);
    DEF_OPERATOR_2OUTPUT_INT  (Mod     ,%  );
    DEF_OPERATOR_2OUTPUT_INT  (LShift  ,<< );
    DEF_OPERATOR_2OUTPUT_INT  (RShift  ,>> );
    DEF_OPERATOR_2OUTPUT_INT  (BAnd    ,&  );
    DEF_OPERATOR_2OUTPUT_INT  (BOr     ,|  );
    DEF_OPERATOR_2OUTPUT_INT  (BXor    ,^  );
    DEF_SPEC_OPERATOR_2OUTPUT (And     ,&& ,bool,bool,bool);
    DEF_SPEC_OPERATOR_2OUTPUT (Or      ,|| ,bool,bool,bool);
    DEF_OPERATOR_2INT         (Mods    ,%= );
    DEF_OPERATOR_2INT         (LShifts ,<<=);
    DEF_OPERATOR_2INT         (RShifts ,>>=);
    DEF_OPERATOR_2INT         (BAnds   ,&= );
    DEF_OPERATOR_2INT         (BOrs    ,|= );
    DEF_OPERATOR_2INT         (BXors   ,^= );
    DEF_SPEC_OPERATOR_1INTPRE (IncrPre ,++);
    DEF_SPEC_OPERATOR_1INTPOST(IncrPost,++);
    DEF_SPEC_OPERATOR_1INTPRE (DecrPre ,--);
    DEF_SPEC_OPERATOR_1INTPOST(DecrPost,--);

    template<typename FROM,typename TO>
      class Cast: public Function{
        public:
          Cast(std::shared_ptr<ge::core::TypeRegister>const&tr,
              std::shared_ptr<ge::core::Accessor>const&output=nullptr):Function(tr,{TypeRegister::FCE,TypeRegister::getTypeDescription<TO>(),1,TypeRegister::getTypeDescription<FROM>()},"Cast"){
            //this->_setOutput(TypeRegister::getTypeTypeId<TO>());
            //this->_setInput(0,TypeRegister::getTypeTypeId<FROM>());
            this->bindOutput(output);
          }
          static inline std::string name(){
            return "Cast_"+std::string(ge::core::TypeRegister::getTypeKeyword<FROM>())+"_"+std::string(ge::core::TypeRegister::getTypeKeyword<TO>());
          }
          static inline std::shared_ptr<Function>sharedInstance(std::shared_ptr<ge::core::TypeRegister>const&tr){
            return std::make_shared<Cast<FROM,TO>>(tr);
          }
          static inline std::shared_ptr<FunctionFactory>sharedFactory(){
            class Factory: public FunctionFactory{
              public:
                virtual ~Factory(){}
                virtual std::shared_ptr<Statement>operator()(SharedTypeRegister const&tr){
                  return std::make_shared<Cast<FROM,TO>>(tr);
                }
            };
            return std::make_shared<Factory>();
          }
        protected:
          virtual bool _do(){
            if(!this->_inputChanged(0))return false;
            (TO&)(*this->_getOutput().data)=(TO)((FROM)(*this->getInputData(0)));
            return true;
          }
      };

    //}}
  }
}
