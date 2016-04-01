#pragma once

#include<geCore/interpret.h>
#include<geCore/Accessor.h>

namespace ge{
  namespace core{

    class GECORE_EXPORT Nullary: public AtomicFunction{
      public:
        Nullary(std::shared_ptr<ge::core::FunctionRegister>const&fr,
            std::shared_ptr<ge::core::Accessor>data = nullptr);
        template<typename TYPE>
          Nullary(std::shared_ptr<ge::core::FunctionRegister>const&fr,TYPE const&data):AtomicFunction(
              fr,fr->getFunctionId(TypeRegister::getTypeKeyword<Nullary>())){
            this->_outputData=fr->getTypeRegister()->sharedAccessor<TYPE>(data);//data);
          }
        template<typename TYPE>
          void update(TYPE const&data){
            (TYPE&)*this->_outputData=data;
            this->_updateTicks++;
          }
    };

    template<typename TYPE>
    class GECORE_EXPORT Assignment: public AtomicFunction{
      public:
        Assignment(std::shared_ptr<ge::core::FunctionRegister>const&fr):AtomicFunction(
              fr,fr->getFunctionId(TypeRegister::getTypeKeyword<Assignment<TYPE>>())){}
        ~Assignment(){}
        virtual void operator()(){
          (TYPE&)(*this->getOutputData()) = (TYPE&)(*this->getInputData(0));
        }
    };

    template<typename TYPE>
    class GECORE_EXPORT UnaryMinus: public AtomicFunction{
      public:
        UnaryMinus(std::shared_ptr<ge::core::FunctionRegister>const&fr):AtomicFunction(
              fr,fr->getFunctionId(TypeRegister::getTypeKeyword<UnaryMinus<TYPE>>())){}
        ~UnaryMinus(){}
        virtual void operator()(){
          (TYPE&)(*this->getOutputData()) = (TYPE) (- (TYPE&)(*this->getInputData(0)));
        }
    };


#define DEF_CLASS_PROLOGUE2(CLASS,INPUT1)\
    class CLASS: public AtomicFunction{\
      public:\
             CLASS(std::shared_ptr<ge::core::FunctionRegister>const&fr,\
                 std::shared_ptr<ge::core::Accessor>const&output=nullptr):AtomicFunction(\
                   fr,fr->getFunctionId(TypeRegister::getTypeKeyword<CLASS<INPUT1>>())){\
                   this->bindOutput(output);\
                 }\
      protected:\
                virtual bool _do(){//}}

#define DEF_CLASS_PROLOGUE2_NONTEMP(CLASS)\
    class CLASS: public AtomicFunction{\
      public:\
             CLASS(std::shared_ptr<ge::core::FunctionRegister>const&fr,\
                 std::shared_ptr<ge::core::Accessor>const&output=nullptr):AtomicFunction(\
                   fr,fr->getFunctionId(TypeRegister::getTypeKeyword<CLASS>())){\
                   this->bindOutput(output);\
                 }\
      protected:\
                virtual bool _do(){//}}

#define DEF_CLASS_EPILOGUE()/*{{*/\
    return true;\
  }\
  }

#define INPUT_CHECK()\
    bool missingInput=false;\
    for(InputIndex i=0;i<this->getNofInputs();++i)\
    if(!this->hasInput(i)){\
      if(!missingInput)std::cerr<<"ERROR: function "<<this->getName()<<" has unbinded inputs: ";\
      else std::cerr<<" ,";\
      missingInput=true;\
      std::cerr<<this->getInputName(i);\
    }\
    if(missingInput){\
      std::cerr<<std::endl;\
      return true;\
    }

#define STD_CAST(TYPE) TYPE
#define INTEGER_CAST(TYPE) typename std::enable_if<std::is_integral<TYPE>::value,TYPE>::type

#define REFERENCE &
#define NOREFERENCE

#define CASTING(CAST_OPERATOR,TYPE,REF,VALUE) ((CAST_OPERATOR(TYPE) REF)VALUE)

#define GET_INPUT(CAST_OPERATOR,TYPE,REF,N) CASTING(CAST_OPERATOR,TYPE,REF,(*this->getInputData(N)))
#define GET_OUTPUT(CAST_OPERATOR,TYPE,REF)  CASTING(CAST_OPERATOR,TYPE,REF,(*this->getOutputData()))

#define RIGHT_SIDE(CAST_OPERATOR,TYPE,OPERATOR)\
    (GET_INPUT(CAST_OPERATOR,TYPE,REFERENCE,0) OPERATOR GET_INPUT(CAST_OPERATOR,TYPE,REFERENCE,1))

#define LEFT_RIGHT_SIDE(CAST_OPERATOR,OUTTYPE,TYPE,OPERATOR,RIGHT_SIDE_TYPE)\
    GET_OUTPUT(CAST_OPERATOR,OUTTYPE,REFERENCE) = CASTING(CAST_OPERATOR,OUTTYPE,NOREFERENCE,RIGHT_SIDE_TYPE(CAST_OPERATOR,TYPE,OPERATOR))


    //OUTPUT means that function requires output to be defined

#define DEF_SPEC_OPERATOR_2OUTPUT(CLASS,OPERATOR,OUTPUT,INPUT)\
    DEF_CLASS_PROLOGUE2_NONTEMP(CLASS);\
    INPUT_CHECK();\
    LEFT_RIGHT_SIDE(STD_CAST,OUTPUT,INPUT,OPERATOR,RIGHT_SIDE);\
    DEF_CLASS_EPILOGUE()

#define DEF_INTEGER_OPERATOR(CLASS,OPERATOR)\
    template<typename TYPE>\
    DEF_CLASS_PROLOGUE2(CLASS,TYPE);\
    INPUT_CHECK();\
    LEFT_RIGHT_SIDE(INTEGER_CAST,TYPE,TYPE,OPERATOR,RIGHT_SIDE);\
    DEF_CLASS_EPILOGUE()


#define DEF_OPERATOR_2OUTPUT(CLASS,OPERATOR,OUTPUT)\
    template<typename TYPE>\
    DEF_SPEC_OPERATOR_2OUTPUT(CLASS,OPERATOR,OUTPUT,TYPE)

#define DEF_AND_OR_OPERATOR(CLASS,OPERATOR)\
    DEF_SPEC_OPERATOR_2OUTPUT(CLASS,OPERATOR,bool,bool)

#define DEF_RELATIONAL_OPERATOR(CLASS,OPERATOR)\
    DEF_OPERATOR_2OUTPUT(CLASS,OPERATOR,bool)

#define DEF_NUMERIC_OPERATOR(CLASS,OPERATOR)\
    DEF_OPERATOR_2OUTPUT(CLASS,OPERATOR,TYPE)

    class Or;
    class And;
    template<>inline std::string TypeRegister::getTypeKeyword<Or>(){return "Or";}
    template<>inline std::string TypeRegister::getTypeKeyword<And>(){return "And";}


    DEF_NUMERIC_OPERATOR         (Add     ,+ );
    DEF_NUMERIC_OPERATOR         (Sub     ,- );
    DEF_NUMERIC_OPERATOR         (Mul     ,* );
    DEF_NUMERIC_OPERATOR         (Div     ,/ );
    DEF_RELATIONAL_OPERATOR      (Less    ,< );
    DEF_RELATIONAL_OPERATOR      (Leq     ,<=);
    DEF_RELATIONAL_OPERATOR      (Greater ,> );
    DEF_RELATIONAL_OPERATOR      (Geq     ,>=);
    DEF_RELATIONAL_OPERATOR      (Eq      ,==);
    DEF_RELATIONAL_OPERATOR      (Neq     ,!=);
    DEF_INTEGER_OPERATOR         (Mod     ,% );
    DEF_INTEGER_OPERATOR         (LShift  ,<<);
    DEF_INTEGER_OPERATOR         (RShift  ,>>);
    DEF_INTEGER_OPERATOR         (BAnd    ,& );
    DEF_INTEGER_OPERATOR         (BOr     ,| );
    DEF_INTEGER_OPERATOR         (BXor    ,^ );
    DEF_AND_OR_OPERATOR          (And     ,&&);
    DEF_AND_OR_OPERATOR          (Or      ,||);

    template<typename FROM,typename TO>
      class Cast: public AtomicFunction{
        public:
          Cast(std::shared_ptr<ge::core::FunctionRegister>const&fr,
              std::shared_ptr<ge::core::Accessor>const&output=nullptr):AtomicFunction(fr,{TypeRegister::FCE,TypeRegister::getTypeDescription<TO>(),1,TypeRegister::getTypeDescription<FROM>()},Cast::name(),Function::factory<Cast<FROM,TO>>()){
            this->bindOutput(output);
          }
          static inline std::string name(){
            return "Cast_"+std::string(ge::core::TypeRegister::getTypeKeyword<FROM>())+"_"+std::string(ge::core::TypeRegister::getTypeKeyword<TO>());
          }
        protected:
          virtual bool _do(){
            if(!this->_inputChanged(0))return false;
            (TO&)(*this->_outputData)=(TO)((FROM)(*this->getInputData(0)));
            return true;
          }
      };

#define SIGNED_INTEGER_LOOP(FCE,...)\
  FCE(__VA_ARGS__,int8_t  )\
  FCE(__VA_ARGS__,int16_t )\
  FCE(__VA_ARGS__,int32_t )\
  FCE(__VA_ARGS__,int64_t )

#define UNSIGNED_INTEGER_LOOP(FCE,...)\
  FCE(__VA_ARGS__,uint8_t )\
  FCE(__VA_ARGS__,uint16_t)\
  FCE(__VA_ARGS__,uint32_t)\
  FCE(__VA_ARGS__,uint64_t)

#define INTEGER_LOOP(FCE,...)\
  SIGNED_INTEGER_LOOP  (FCE,__VA_ARGS__)\
  UNSIGNED_INTEGER_LOOP(FCE,__VA_ARGS__)

#define FLOATING_LOOP(FCE,...)\
  FCE(__VA_ARGS__,float )\
  FCE(__VA_ARGS__,double)

#define NUMERIC_LOOP(FCE,...)\
  INTEGER_LOOP (FCE,__VA_ARGS__)\
  FLOATING_LOOP(FCE,__VA_ARGS__)

#define SIGNED_NUMERIC_LOOP(FCE,...)\
  SIGNED_INTEGER_LOOP(FCE,__VA_ARGS__)\
  FLOATING_LOOP      (FCE,__VA_ARGS__)

#define ALL_LOOP(FCE,...)\
  NUMERIC_LOOP(FCE,__VA_ARGS__)\
  FCE(__VA_ARGS__,bool)\
  FCE(__VA_ARGS__,std::string)

#define NUMERIC_FCE_LOOP(FCE,...)\
  FCE(__VA_ARGS__,Add )\
  FCE(__VA_ARGS__,Sub )\
  FCE(__VA_ARGS__,Mul )\
  FCE(__VA_ARGS__,Div )

#define RELATIONAL_FCE_LOOP(FCE,...)\
  FCE(__VA_ARGS__,Less   )\
  FCE(__VA_ARGS__,Leq    )\
  FCE(__VA_ARGS__,Greater)\
  FCE(__VA_ARGS__,Geq    )\
  FCE(__VA_ARGS__,Eq     )\
  FCE(__VA_ARGS__,Neq    )

#define INTEGER_FCE_LOOP(FCE,...)\
  FCE(__VA_ARGS__,Mod   )\
  FCE(__VA_ARGS__,LShift)\
  FCE(__VA_ARGS__,RShift)\
  FCE(__VA_ARGS__,BAnd  )\
  FCE(__VA_ARGS__,BOr   )\
  FCE(__VA_ARGS__,BXor  )



#define DEFINE_GETTYPEKEYWORD(NAME,TYPE)\
    template<>inline std::string TypeRegister::getTypeKeyword<NAME<TYPE>>(){\
      return std::string(#NAME)+std::string("<")+TypeRegister::getTypeKeyword<TYPE>()+std::string(">");\
    }

    NUMERIC_FCE_LOOP(NUMERIC_LOOP,DEFINE_GETTYPEKEYWORD)
    RELATIONAL_FCE_LOOP(ALL_LOOP,DEFINE_GETTYPEKEYWORD)
    INTEGER_FCE_LOOP(INTEGER_LOOP,DEFINE_GETTYPEKEYWORD)
    DEFINE_GETTYPEKEYWORD(Add,std::string)

    ALL_LOOP(DEFINE_GETTYPEKEYWORD,Assignment)
    SIGNED_NUMERIC_LOOP(DEFINE_GETTYPEKEYWORD,UnaryMinus)
    template<>inline std::string TypeRegister::getTypeKeyword<Nullary>(){return "Nullary";}
    void registerStdFunctions(std::shared_ptr<FunctionRegister>const&fr);

  }
}

