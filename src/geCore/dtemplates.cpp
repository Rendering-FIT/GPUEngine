#include<geCore/dtemplates.h>

using namespace ge::core;

unsigned ge::core::getDispatchSize(unsigned workSize,unsigned workGroupSize){
  return workSize%workGroupSize?workSize/workGroupSize+1:workSize/workGroupSize;
}
