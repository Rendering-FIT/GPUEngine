#include<geCore/StdFunctions.h>
#include<geCore/StdCastFunctions.h>

using namespace ge::core;

void ge::core::registerStdCastFunctions(std::shared_ptr<FunctionRegister>const&fr){
  auto tr=fr->getTypeRegister();
  //ADD_CAST_FUNCTION(int32_t,int32_t)
  ALL_LOOP2(ALL_LOOP3,ADD_CAST_FUNCTION)
}
