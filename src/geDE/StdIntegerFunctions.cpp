#include<geDE/StdFunctions.h>
#include<geDE/StdIntegerFunctions.h>

using namespace ge::de;

void ge::de::registerStdIntegerFunctions(std::shared_ptr<FunctionRegister>const&fr){
  PRINT_CALL_STACK(fr);
  assert(fr!=nullptr);
  auto tr=fr->getTypeRegister();
  INTEGER_FCE_LOOP(INTEGER_LOOP,ADD_BINARY_FUNCTION_SIMPLE)
}
