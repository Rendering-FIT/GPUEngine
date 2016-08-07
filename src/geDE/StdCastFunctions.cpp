#include<geDE/StdFunctions.h>
#include<geDE/StdCastFunctions.h>

using namespace ge::de;

void ge::de::registerStdCastFunctions(std::shared_ptr<FunctionRegister>const&fr){
  PRINT_CALL_STACK(fr);
  assert(fr!=nullptr);
  auto tr=fr->getTypeRegister();
  //ADD_CAST_FUNCTION(int32_t,int32_t)
  ALL_LOOP2(ALL_LOOP3,ADD_CAST_FUNCTION)
}
