#include<geDE/StdFunctions.h>
#include<geDE/StdNumericFunctions.h>
#include<geDE/StdRelationalFunctions.h>
#include<geDE/StdIntegerFunctions.h>
#include<geDE/StdCastFunctions.h>

using namespace ge::de;

void ge::de::registerStdFunctions(std::shared_ptr<FunctionRegister>const&fr){
  auto tr=fr->getTypeRegister();
  fr->addFunction(tr->addCompositeType("",{TypeRegister::FCE,TypeRegister::ANY,0}),
      keyword<Nullary>(),
      factoryOfFunctionFactory<Nullary>(keyword<Nullary>()));

  registerStdNumericFunctions(fr);
  registerStdRelationalFunctions(fr);
  registerStdIntegerFunctions(fr);
  registerStdCastFunctions(fr);

  ADD_BINARY_FUNCTION_SIMPLE(Add,std::string)
    ALL_LOOP(ADD_UNARY_FUNCTION_SIMPLE,Assignment)
    SIGNED_NUMERIC_LOOP(ADD_UNARY_FUNCTION_SIMPLE,UnaryMinus)
}
