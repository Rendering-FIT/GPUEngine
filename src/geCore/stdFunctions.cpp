#include<geCore/stdFunctions.h>

using namespace ge::core;

Nullary::Nullary(
    std::shared_ptr<ge::core::FunctionRegister>const&fr,
    std::shared_ptr<ge::core::Accessor>data):AtomicFunction(fr,fr->getFunctionId(TypeRegister::getTypeKeyword<Nullary>())){
  this->_outputData = data;
}


void ge::core::registerStdFunctions(std::shared_ptr<FunctionRegister>const&fr){
  auto tr=fr->getTypeRegister();
  fr->addFunction(tr->addType("",{TypeRegister::FCE,TypeRegister::UNREGISTERED,0}),
              TypeRegister::getTypeKeyword<Nullary>(),
              Function::factory<Nullary>());

#define BINARY_FUNTION_DESCRIPTION(OUTPUT,INPUT1,INPUT2){\
  TypeRegister::FCE,\
  TypeRegister::getTypeDescription<OUTPUT>(),\
  2,\
  TypeRegister::getTypeDescription<INPUT1>(),\
  TypeRegister::getTypeDescription<INPUT2>()}

#define UNARY_FUNTION_DESCRIPTION(OUTPUT,INPUT1){\
  TypeRegister::FCE,\
  TypeRegister::getTypeDescription<OUTPUT>(),\
  1,\
  TypeRegister::getTypeDescription<INPUT1>()}

#define ADD_BINARY_FUNCTION(OUTPUT,INPUT1,INPUT2,NAME,FACTORY)\
  fr->addFunction(tr->addType("",BINARY_FUNTION_DESCRIPTION(OUTPUT,INPUT1,INPUT2)),NAME,FACTORY);

#define ADD_UNARY_FUNCTION(OUTPUT,INPUT1,NAME,FACTORY)\
  fr->addFunction(tr->addType("",UNARY_FUNTION_DESCRIPTION(OUTPUT,INPUT1)),NAME,FACTORY);

#define ADD_BINARY_FUNCTION_SIMPLE(CLASS,TYPE)\
    ADD_BINARY_FUNCTION(TYPE,TYPE,TYPE,TypeRegister::getTypeKeyword<CLASS<TYPE>>(),Function::factory<CLASS<TYPE>>())

#define ADD_BINARY_FUNCTION_COMPLEX(CLASS,TYPE)\
    ADD_BINARY_FUNCTION(bool,TYPE,TYPE,TypeRegister::getTypeKeyword<CLASS<TYPE>>(),Function::factory<CLASS<TYPE>>())

#define ADD_UNARY_FUNCTION_SIMPLE(CLASS,TYPE)\
    ADD_UNARY_FUNCTION(TYPE,TYPE,TypeRegister::getTypeKeyword<CLASS<TYPE>>(),Function::factory<CLASS<TYPE>>())

  auto a=fr->getTypeRegister()->sharedAccessor("string");

  NUMERIC_FCE_LOOP(NUMERIC_LOOP,ADD_BINARY_FUNCTION_SIMPLE)
  RELATIONAL_FCE_LOOP(ALL_LOOP,ADD_BINARY_FUNCTION_COMPLEX)
  INTEGER_FCE_LOOP(INTEGER_LOOP,ADD_BINARY_FUNCTION_SIMPLE)
  ADD_BINARY_FUNCTION_SIMPLE(Add,std::string)
  ALL_LOOP(ADD_UNARY_FUNCTION_SIMPLE,Assignment)
  SIGNED_NUMERIC_LOOP(ADD_UNARY_FUNCTION_SIMPLE,UnaryMinus)
}
