#include<geDE/FunctionFactory.h>

using namespace ge::de;

FunctionFactory::FunctionFactory(std::string const&name,Uses maxUses):StatementFactory(name,maxUses){
  PRINT_CALL_STACK(name,maxUses);
}

FunctionFactory::~FunctionFactory(){
  PRINT_CALL_STACK();
}

