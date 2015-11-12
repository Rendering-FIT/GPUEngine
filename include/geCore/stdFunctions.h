#pragma once

#include"interpret.h"

namespace ge{
  namespace core{

    class Nullary: public Function{
      public:
        Nullary(std::shared_ptr<ge::core::Accessor>data = nullptr);
        template<typename TYPE>
          Nullary(TYPE const&data,std::shared_ptr<ge::core::TypeRegister>const&typeRegister):Function(0){
            this->_output=typeRegister->sharedAccessor<TYPE>(data);//data);
          }
    };

#define DEF_CLASS_PROLOGUE(CLASS,NARRY)\
    class CLASS: public Function{\
      public:\
             CLASS(std::shared_ptr<ge::core::Accessor>const&output=nullptr):Function(NARRY){\
               this->setOutput(output);\
             }\
      virtual void operator()(){\
        this->beginOperator()

#define DEF_CLASS_EPILOGUE()\
        this->endOperator();\
      }\
    }

#define DEF_SPEC_OPERATOR_2(CLASS,OPERATOR,OUTPUT,INPUT0,INPUT1)\
    DEF_CLASS_PROLOGUE(CLASS,2);\
    if(this->_output)\
    (OUTPUT&)*(this->_output)=\
    (INPUT0&)(*(this->_inputs[0]->getOutput())) OPERATOR\
    (INPUT1)(*(this->_inputs[1]->getOutput()));\
    else\
    (INPUT0&)(*(this->_inputs[0]->getOutput())) OPERATOR\
    (INPUT1)(*(this->_inputs[1]->getOutput()));\
    DEF_CLASS_EPILOGUE()

    //OUTPUT means that function requires output to be defined

#define DEF_SPEC_OPERATOR_2OUTPUT(CLASS,OPERATOR,OUTPUT,INPUT0,INPUT1)\
    DEF_CLASS_PROLOGUE(CLASS,2);\
    (OUTPUT&)*(this->_output)=\
    (INPUT0&)(*(this->_inputs[0]->getOutput())) OPERATOR\
    (INPUT1)(*(this->_inputs[1]->getOutput()));\
    DEF_CLASS_EPILOGUE()

#define DEF_OPERATOR_2INT(CLASS,OPERATOR)\
    template<typename TYPE>\
    DEF_CLASS_PROLOGUE(CLASS,2);\
    if(this->_output)\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&) *(this->_output)=\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*(this->_inputs[0]->getOutput())) OPERATOR\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type )(*(this->_inputs[1]->getOutput()));\
    else\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*(this->_inputs[0]->getOutput())) OPERATOR\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type )(*(this->_inputs[1]->getOutput()));\
    DEF_CLASS_EPILOGUE()

#define DEF_OPERATOR_2OUTPUT_INT(CLASS,OPERATOR)\
    template<typename TYPE>\
    DEF_CLASS_PROLOGUE(CLASS,2);\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&) *(this->_output)=\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*(this->_inputs[0]->getOutput())) OPERATOR\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type )(*(this->_inputs[1]->getOutput()));\
    DEF_CLASS_EPILOGUE()

#define DEF_SPEC_OPERATOR_1INTPRE(CLASS,OPERATOR)\
    template<typename TYPE>\
    DEF_CLASS_PROLOGUE(CLASS,1);\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)*(this->_output)=\
    OPERATOR ((typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*(this->_inputs[0]->getOutput())));\
    DEF_CLASS_EPILOGUE()

#define DEF_SPEC_OPERATOR_1INTPOST(CLASS,OPERATOR)\
    template<typename TYPE>\
    DEF_CLASS_PROLOGUE(CLASS,1);\
    if(this->_output)\
    (typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)*(this->_output)=\
    ((typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*(this->_inputs[0]->getOutput()))) OPERATOR;\
    else\
    ((typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type&)(*(this->_inputs[0]->getOutput()))) OPERATOR;\
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
            this->setOutput(output);
          }
          virtual void operator()(){
            this->beginOperator();
            (TO&)(*this->_output)=(FROM)(*this->_inputs[0]->getOutput());
            this->endOperator();
          }
      };
  }
}
