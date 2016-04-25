#include<geCore/StdFunctions.h>
#include<geCore/StdIntegerFunctions.h>

using namespace ge::core;

void ge::core::registerStdIntegerFunctions(std::shared_ptr<FunctionRegister>const&fr){
  auto tr=fr->getTypeRegister();
  INTEGER_FCE_LOOP(INTEGER_LOOP,ADD_BINARY_FUNCTION_SIMPLE)
}
