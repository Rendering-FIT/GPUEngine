#include<geCore/StdFunctions.h>
#include<geCore/StdNumericFunctions.h>
#include<geCore/StdRelationalFunctions.h>
#include<geCore/StdIntegerFunctions.h>
#include<geCore/StdCastFunctions.h>

using namespace ge::core;

Nullary::Nullary(
    std::shared_ptr<FunctionRegister>const&fr  ,
    FunctionRegister::FunctionID           id  ,
    std::shared_ptr<Accessor>const&        data):AtomicFunction(fr,id){
  this->_outputData = data;
}


void ge::core::registerStdFunctions(std::shared_ptr<FunctionRegister>const&fr){
  auto tr=fr->getTypeRegister();
  fr->addFunction(tr->addType("",{TypeRegister::FCE,TypeRegister::UNREGISTERED,0}),
              TypeRegister::getTypeKeyword<Nullary>(),
              factoryOfFunctionFactory<Nullary>(TypeRegister::getTypeKeyword<Nullary>()));

  registerStdNumericFunctions(fr);
  registerStdRelationalFunctions(fr);
  registerStdIntegerFunctions(fr);
  registerStdCastFunctions(fr);

  ADD_BINARY_FUNCTION_SIMPLE(Add,std::string)
  ALL_LOOP(ADD_UNARY_FUNCTION_SIMPLE,Assignment)
  SIGNED_NUMERIC_LOOP(ADD_UNARY_FUNCTION_SIMPLE,UnaryMinus)
}
