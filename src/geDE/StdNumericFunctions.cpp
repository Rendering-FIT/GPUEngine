#include<geDE/StdFunctions.h>
#include<geDE/StdNumericFunctions.h>

using namespace ge::de;

void ge::de::registerStdNumericFunctions(std::shared_ptr<FunctionRegister>const&fr){
  PRINT_CALL_STACK(fr);
  assert(fr!=nullptr);
  auto tr=fr->getTypeRegister();
  NUMERIC_FCE_LOOP(NUMERIC_LOOP,ADD_BINARY_FUNCTION_SIMPLE)
}
