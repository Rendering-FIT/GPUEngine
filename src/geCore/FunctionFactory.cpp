#include<geCore/FunctionFactory.h>

using namespace ge::core;

FunctionFactory::FunctionFactory(std::string const&name,Uses maxUses):StatementFactory(name,maxUses){
}

FunctionFactory::~FunctionFactory(){
}

