#pragma once

#include<geDE/Interpret.h>
#include<geDE/Resource.h>
#include<geDE/AtomicFunction.h>
#include<geDE/FactoryOfFunctionFactory.h>

namespace ge{
  namespace de{
    template<typename TYPE>
    class /*GEDE_EXPORT*/ Assignment: public AtomicFunction{
      public:
        Assignment(
            std::shared_ptr<FunctionRegister>const&fr,
            FunctionId           id):AtomicFunction(fr,id){
          PRINT_CALL_STACK(fr,id);
        }
        Assignment(
            std::shared_ptr<FunctionRegister>const&fr):Assignment(fr,fr->getFunctionId(keyword<Assignment<TYPE>>())){
          PRINT_CALL_STACK(fr);
        }

        ~Assignment(){
          PRINT_CALL_STACK();
        }
        virtual bool _do(){
          PRINT_CALL_STACK();
          assert(this!=nullptr);
          assert(this->getOutputData()!=nullptr);
          assert(this->getInputData(0)!=nullptr);
          (TYPE&)(*this->getOutputData()) = (TYPE&)(*this->getInputData(0));
          return true;
        }
    };

    template<typename TYPE>
    class /*GEDE_EXPORT*/ UnaryMinus: public AtomicFunction{
      public:
        UnaryMinus(
            std::shared_ptr<FunctionRegister>const&fr,
            FunctionId           id):AtomicFunction(fr,id){
          PRINT_CALL_STACK(fr,id);
        }
        ~UnaryMinus(){
          PRINT_CALL_STACK();
        }
        virtual void operator()(){
          PRINT_CALL_STACK();
          assert(this!=nullptr);
          assert(this->getOutputData()!=nullptr);
          assert(this->getInputData(0)!=nullptr);
          if(!this->_dirtyFlag)return;
          this->_dirtyFlag = false;
          (TYPE&)(*this->getOutputData()) = (TYPE) (- (TYPE&)(*this->getInputData(0)));
          this->_updateTicks++;
        }
    };


#define DEF_CLASS_PROLOGUE2(CLASS,INPUT1)\
    class CLASS: public AtomicFunction{\
      public:\
              CLASS(std::shared_ptr<FunctionRegister>const&fr):AtomicFunction(fr,fr->getFunctionId(keyword<CLASS<INPUT1>>())){PRINT_CALL_STACK(fr);}\
              CLASS(std::shared_ptr<FunctionRegister>const&fr,FunctionId id):AtomicFunction(fr,id){PRINT_CALL_STACK(fr,id);}\
      protected:\
                virtual bool _do(){\
                  PRINT_CALL_STACK();\
                  assert(this!=nullptr);//}}

#define DEF_CLASS_PROLOGUE2_NONTEMP(CLASS,INPUT)\
    class CLASS: public AtomicFunction{\
      public:\
              CLASS(std::shared_ptr<FunctionRegister>const&fr):AtomicFunction(fr,fr->getFunctionId(keyword<CLASS<INPUT>>())){PRINT_CALL_STACK(fr);}\
              CLASS(std::shared_ptr<FunctionRegister>const&fr,FunctionId id):AtomicFunction(fr,id){PRINT_CALL_STACK(fr);}\
      protected:\
                virtual bool _do(){\
                  PRINT_CALL_STACK();\
                  assert(this!=nullptr);//}}

#define DEF_CLASS_EPILOGUE()/*{{*/\
    return true;\
  }\
  }

#define INPUT_CHECK()\
    bool missingInput=false;\
    for(InputIndex i=0;i<this->_inputs.size();++i)\
    if(!this->hasInput(i)){\
      if(!missingInput)std::cerr<<"ERROR: function "<</*this->_functionRegister->getName(this->_id)*/this->_id<<" has unbinded inputs: ";\
      else std::cerr<<" ,";\
      missingInput=true;\
      std::cerr<</*this->_functionRegister->getNameRegister()->getFceInputName(this->_id,i)*/i;\
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
    DEF_CLASS_PROLOGUE2_NONTEMP(CLASS,INPUT);\
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
    class CLASS: public AtomicFunction{\
      public:\
              CLASS(std::shared_ptr<FunctionRegister>const&fr):AtomicFunction(fr,fr->getFunctionId(keyword<CLASS>())){PRINT_CALL_STACK(fr);}\
              CLASS(std::shared_ptr<FunctionRegister>const&fr,FunctionId id):AtomicFunction(fr,id){PRINT_CALL_STACK(fr);}\
      protected:\
                virtual bool _do(){\
                  PRINT_CALL_STACK();\
                  assert(this!=nullptr);\
    INPUT_CHECK();\
    LEFT_RIGHT_SIDE(STD_CAST,bool,bool,OPERATOR,RIGHT_SIDE);\
    DEF_CLASS_EPILOGUE()//}}

//    DEF_SPEC_OPERATOR_2OUTPUT(CLASS,OPERATOR,bool,bool)

#define DEF_RELATIONAL_OPERATOR(CLASS,OPERATOR)\
    DEF_OPERATOR_2OUTPUT(CLASS,OPERATOR,bool)

#define DEF_NUMERIC_OPERATOR(CLASS,OPERATOR)\
    DEF_OPERATOR_2OUTPUT(CLASS,OPERATOR,TYPE)

    class Or;
    class And;
    template<>inline std::string keyword<Or>(){return "Or";}
    template<>inline std::string keyword<And>(){return "And";}


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
          Cast(std::shared_ptr<FunctionRegister>const&fr,FunctionId id):AtomicFunction(fr,id){PRINT_CALL_STACK(fr,id);}
          Cast(std::shared_ptr<ge::de::FunctionRegister>const&fr):AtomicFunction(fr,fr->getFunctionId(keyword<Cast<FROM,TO>>())){PRINT_CALL_STACK(fr);}
        protected:
          virtual bool _do(){
            PRINT_CALL_STACK();
            assert(this!=nullptr);
            if(!this->_inputChanged(0))return false;
            assert(this->_outputData!=nullptr);
            (TO&)(*this->_outputData)=(TO)((FROM&)(*this->getInputData(0)));
            return true;
          }
      };

#define SIGNED_INTEGER_LOOP(FCE,...)\
  /*FCE(__VA_ARGS__,int8_t  )*/\
  /*FCE(__VA_ARGS__,int16_t )*/\
  FCE(__VA_ARGS__,int32_t )\
  FCE(__VA_ARGS__,int64_t )

#define SIGNED_INTEGER_LOOP2(FCE,...)\
    SIGNED_INTEGER_LOOP(FCE,__VA_ARGS__)

#define UNSIGNED_INTEGER_LOOP(FCE,...)\
  /*FCE(__VA_ARGS__,uint8_t )*/\
  /*FCE(__VA_ARGS__,uint16_t)*/\
  FCE(__VA_ARGS__,uint32_t)\
  FCE(__VA_ARGS__,uint64_t)

#define UNSIGNED_INTEGER_LOOP2(FCE,...)\
  UNSIGNED_INTEGER_LOOP(FCE,__VA_ARGS__)

#define INTEGER_LOOP(FCE,...)\
  SIGNED_INTEGER_LOOP  (FCE,__VA_ARGS__)\
  UNSIGNED_INTEGER_LOOP(FCE,__VA_ARGS__)

#define INTEGER_LOOP2(FCE,...)\
  INTEGER_LOOP(FCE,__VA_ARGS__)

#define FLOATING_LOOP(FCE,...)\
  FCE(__VA_ARGS__,float )\
  FCE(__VA_ARGS__,double)

#define FLOATING_LOOP2(FCE,...)\
  FLOATING_LOOP(FCE,__VA_ARGS__)

#define NUMERIC_LOOP(FCE,...)\
  INTEGER_LOOP (FCE,__VA_ARGS__)\
  FLOATING_LOOP(FCE,__VA_ARGS__)

#define NUMERIC_LOOP2(FCE,...)\
  NUMERIC_LOOP(FCE,__VA_ARGS__)

#define SIGNED_NUMERIC_LOOP(FCE,...)\
  SIGNED_INTEGER_LOOP(FCE,__VA_ARGS__)\
  FLOATING_LOOP      (FCE,__VA_ARGS__)

#define SIGNED_NUMERIC_LOOP2(FCE,...)\
  SIGNED_NUMERIC_LOOP(FCE,__VA_ARGS__)

#define ALL_LOOP(FCE,...)\
  NUMERIC_LOOP(FCE,__VA_ARGS__)\
  FCE(__VA_ARGS__,bool)\
  FCE(__VA_ARGS__,std::string)

#define ALL_LOOP2(FCE,...)\
  /*FCE(__VA_ARGS__,int8_t  )*/\
  /*FCE(__VA_ARGS__,int16_t )*/\
  FCE(__VA_ARGS__,int32_t )\
  FCE(__VA_ARGS__,int64_t )\
  /*FCE(__VA_ARGS__,uint8_t )*/\
  /*FCE(__VA_ARGS__,uint16_t)*/\
  FCE(__VA_ARGS__,uint32_t)\
  FCE(__VA_ARGS__,uint64_t)\
  FCE(__VA_ARGS__,float )\
  FCE(__VA_ARGS__,double)\
  FCE(__VA_ARGS__,bool)

#define ALL_LOOP3(FCE,...)\
  /*FCE(__VA_ARGS__,int8_t  )*/\
  /*FCE(__VA_ARGS__,int16_t )*/\
  FCE(__VA_ARGS__,int32_t )\
  FCE(__VA_ARGS__,int64_t )\
  /*FCE(__VA_ARGS__,uint8_t )*/\
  /*FCE(__VA_ARGS__,uint16_t)*/\
  FCE(__VA_ARGS__,uint32_t)\
  FCE(__VA_ARGS__,uint64_t)\
  FCE(__VA_ARGS__,float )\
  FCE(__VA_ARGS__,double)\
  FCE(__VA_ARGS__,bool)

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
    template<>inline std::string keyword<NAME<TYPE>>(){\
      return std::string(#NAME)+std::string("<")+keyword<TYPE>()+std::string(">");\
    }

#define DEFINE_CASTKEYWORD(FROM,TO)\
    template<>inline std::string keyword<Cast<FROM,TO>>(){\
      return std::string("Cast")+std::string("<")+keyword<FROM>()+std::string(",")+keyword<TO>()+std::string(">");\
    }


#define ADD_BINARY_FUNCTION(OUTPUT,INPUT1,INPUT2,NAME,FACTORY)\
  fr->addFunction(tr->addType<OUTPUT(INPUT1,INPUT2)>(),NAME,FACTORY);

#define ADD_UNARY_FUNCTION(OUTPUT,INPUT1,NAME,FACTORY)\
  fr->addFunction(tr->addType<OUTPUT(INPUT1)>(),NAME,FACTORY);

#define ADD_BINARY_FUNCTION_SIMPLE(CLASS,TYPE)\
    ADD_BINARY_FUNCTION(TYPE,TYPE,TYPE,keyword<CLASS<TYPE>>(),factoryOfFunctionFactory<CLASS<TYPE>>())

#define ADD_BINARY_FUNCTION_COMPLEX(CLASS,TYPE)\
    ADD_BINARY_FUNCTION(bool,TYPE,TYPE,keyword<CLASS<TYPE>>(),factoryOfFunctionFactory<CLASS<TYPE>>())

#define ADD_UNARY_FUNCTION_SIMPLE(CLASS,TYPE)\
    ADD_UNARY_FUNCTION(TYPE,TYPE,keyword<CLASS<TYPE>>(),factoryOfFunctionFactory<CLASS<TYPE>>())

#define ADD_CAST_FUNCTION(FROM,TO)\
  fr->addFunction(tr->addType<TO(FROM)>(),keyword<Cast<FROM,TO>>(),factoryOfFunctionFactory<Cast<FROM,TO>>());

    NUMERIC_FCE_LOOP(NUMERIC_LOOP,DEFINE_GETTYPEKEYWORD)
    RELATIONAL_FCE_LOOP(ALL_LOOP,DEFINE_GETTYPEKEYWORD)
    INTEGER_FCE_LOOP(INTEGER_LOOP,DEFINE_GETTYPEKEYWORD)
    DEFINE_GETTYPEKEYWORD(Add,std::string)

    ALL_LOOP(DEFINE_GETTYPEKEYWORD,Assignment)
    SIGNED_NUMERIC_LOOP(DEFINE_GETTYPEKEYWORD,UnaryMinus)

    ALL_LOOP2(ALL_LOOP3,DEFINE_CASTKEYWORD)
    GEDE_EXPORT void registerStdFunctions(std::shared_ptr<FunctionRegister>const&fr);
  }
}

