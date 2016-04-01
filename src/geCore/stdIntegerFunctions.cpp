#include<geCore/stdFunctions.h>
#include<geCore/stdIntegerFunctions.h>

using namespace ge::core;

void ge::core::registerStdIntegerFunctions(std::shared_ptr<FunctionRegister>const&fr){
  auto tr=fr->getTypeRegister();
  INTEGER_FCE_LOOP(INTEGER_LOOP,ADD_BINARY_FUNCTION_SIMPLE)
}
