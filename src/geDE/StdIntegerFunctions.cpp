#include<geDE/StdFunctions.h>
#include<geDE/StdIntegerFunctions.h>

using namespace ge::de;

void ge::de::registerStdIntegerFunctions(std::shared_ptr<FunctionRegister>const&fr){
  auto tr=fr->getTypeRegister();
  INTEGER_FCE_LOOP(INTEGER_LOOP,ADD_BINARY_FUNCTION_SIMPLE)
}
