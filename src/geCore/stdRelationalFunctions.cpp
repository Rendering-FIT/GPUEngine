#include<geCore/stdFunctions.h>
#include<geCore/stdRelationalFunctions.h>

using namespace ge::core;

void ge::core::registerStdRelationalFunctions(std::shared_ptr<FunctionRegister>const&fr){
  auto tr=fr->getTypeRegister();
  RELATIONAL_FCE_LOOP(ALL_LOOP,ADD_BINARY_FUNCTION_COMPLEX)
}
