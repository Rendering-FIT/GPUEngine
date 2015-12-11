#pragma once

#include<geCore/interpret.h>

namespace ge{
  namespace core{

    class GECORE_EXPORT Nullary: public Function{
      public:
        Nullary(std::shared_ptr<ge::core::Accessor>data = nullptr);
        template<typename TYPE>
          Nullary(TYPE const&data,std::shared_ptr<ge::core::TypeRegister>const&typeRegister):Function(0){
            this->_output=typeRegister->sharedAccessor<TYPE>(data);//data);
            this->_setOutput(this->_output->getId());
          }
        template<typename TYPE>
          void update(TYPE const&data){
            (TYPE&)*this->_output=data;
            this->_updateTicks++;
          }

    };

#define DEF_CLASS_PROLOGUE2(CLASS,NARRY,OUTPUT,INPUT0,INPUT1)\
    class CLASS: public Function{\
      public:\
             CLASS(std::shared_ptr<ge::core::Accessor>const&output=nullptr):Function(NARRY){\
               this->bindOutput(output);\
               this->_setOutput(TypeRegister::getTypeTypeId<OUTPUT>());\
               this->_setInput(0,TypeRegister::getTypeTypeId<INPUT0>());\
               this->_setInput(1,TypeRegister::getTypeTypeId<INPUT1>());\
             }\
      protected:\
        virtual bool _do(){
//        this->_beginOperator()

#define DEF_CLASS_PROLOGUE1(CLASS,NARRY,OUTPUT,INPUT0)\
    class CLASS: public Function{\
      public:\
             CLASS(std::shared_ptr<ge::core::Accessor>const&output=nullptr):Function(NARRY){\
               this->bindOutput(output);\
               this->_setOutput(TypeRegister::getTypeTypeId<OUTPUT>());\
               this->_setInput(0,TypeRegister::getTypeTypeId<INPUT0>());\
             }\
      protected:\
        virtual bool _do(){
//        this->_beginOperator()

#define DEF_CLASS_EPILOGUE()\
          return true;\
/*        this->_endOperator();*/\
        }\
    }

#define DEF_SPEC_OPERATOR_2(CLASS,OPERATOR,OUTPUT,INPUT0,INPUT1)\
    DEF_CLASS_PROLOGUE2(CLASS,2,OUTPUT,INPUT0,INPUT1);\
    if(this->_output)\
    (OUTPUT&)*(this->_output)=\
    (INPUT0&)(*this->getInputData(0)) OPERATOR\
    (INPUT1 )(*this->getInputData(1));\
    else\
    (INPUT0&)(*this->getInputData(0)) OPERATOR\
    (INPUT1 )(*this->getInputData(1));\
    DEF_CLASS_EPILOGUE()

    //OUTPUT means that function requires output to be defined

#define DEF_SPEC_OPERATOR_2OUTPUT(CLASS,OPERATOR,OUTPUT,INPUT0,INPUT1)\
    DEF_CLASS_PROLOGUE2(CLASS,2,OUTPUT,INPUT0,INPUT1);\
    (OUTPUT&)*(this->_output)=\
    (INPUT0&)(*this->getInputData(0)) OPERATOR\
    (INPUT1 )(*this->getInputData(1));\
    DEF_CLASS_EPILOGUE()

#define DEF_OPERATOR_2INT(CLASS,OPERATOR)\
    template<typename TYPE>\
    DEF_CLASS_PROLOGUE2(CLASS,2,TYPE,TYPE,TYPE);\
    if(this->_output)\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->_output)=\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->getInputData(0)) OPERATOR\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type )(*this->getInputData(1));\
    else\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->getInputData(0)) OPERATOR\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type )(*this->getInputData(1));\
    DEF_CLASS_EPILOGUE()

#define DEF_OPERATOR_2OUTPUT_INT(CLASS,OPERATOR)\
    template<typename TYPE>\
    DEF_CLASS_PROLOGUE2(CLASS,2,TYPE,TYPE,TYPE);\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->_output)=\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->getInputData(0)) OPERATOR\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type )(*this->getInputData(1));\
    DEF_CLASS_EPILOGUE()

#define DEF_SPEC_OPERATOR_1INTPRE(CLASS,OPERATOR)\
    template<typename TYPE>\
    DEF_CLASS_PROLOGUE1(CLASS,1,TYPE,TYPE);\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->_output)=\
    OPERATOR ((typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->getInputData(0)));\
    DEF_CLASS_EPILOGUE()

#define DEF_SPEC_OPERATOR_1INTPOST(CLASS,OPERATOR)\
    template<typename TYPE>\
    DEF_CLASS_PROLOGUE1(CLASS,1,TYPE,TYPE);\
    if(this->_output)\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*this->_output)=\
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
          Cast(std::shared_ptr<ge::core::Accessor>const&output=nullptr):Function(1){
            this->bindOutput(output);
            this->_setOutput(TypeRegister::getTypeTypeId<TO>());
            this->_setInput(0,TypeRegister::getTypeTypeId<FROM>());
          }
        protected:
          virtual bool _do(){
            if(!this->_inputChanged(0))return false;
            (TO&)(*this->_output)=(TO)((FROM)(*this->getInputData(0)));
            return true;
          }
      };
  }
}
