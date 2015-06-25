#include<geCore/dtemplates.h>

using namespace ge::core;

unsigned ge::core::getDispatchSize(unsigned workSize,unsigned workGroupSize){
  return workSize%workGroupSize?workSize/workGroupSize+1:workSize/workGroupSize;
}

unsigned ge::core::bitCount(unsigned value){
  unsigned result=0;
  while(value){
    result+=value&1u;
    value>>=1;
  }
  return result;
}
