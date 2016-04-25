#include<geCore/StdFunctions.h>
#include<geCore/StdNumericFunctions.h>

using namespace ge::core;

void ge::core::registerStdNumericFunctions(std::shared_ptr<FunctionRegister>const&fr){
  auto tr=fr->getTypeRegister();
  NUMERIC_FCE_LOOP(NUMERIC_LOOP,ADD_BINARY_FUNCTION_SIMPLE)
}
