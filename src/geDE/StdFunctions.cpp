#include<geDE/StdFunctions.h>
#include<geDE/StdNumericFunctions.h>
#include<geDE/StdRelationalFunctions.h>
#include<geDE/StdIntegerFunctions.h>
#include<geDE/StdCastFunctions.h>

using namespace ge::de;

Nullary::Nullary(
    std::shared_ptr<FunctionRegister>const&fr  ,
    FunctionRegister::FunctionID           id  ,
    std::shared_ptr<Resource>const&        data):AtomicFunction(fr,id){
  this->_outputData = data;
}


void ge::de::registerStdFunctions(std::shared_ptr<FunctionRegister>const&fr){
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
