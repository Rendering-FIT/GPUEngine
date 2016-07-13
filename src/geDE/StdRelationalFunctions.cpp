#include<geDE/StdFunctions.h>
#include<geDE/StdRelationalFunctions.h>

using namespace ge::de;

void ge::de::registerStdRelationalFunctions(std::shared_ptr<FunctionRegister>const&fr){
  auto tr=fr->getTypeRegister();
  RELATIONAL_FCE_LOOP(ALL_LOOP,ADD_BINARY_FUNCTION_COMPLEX)
}
