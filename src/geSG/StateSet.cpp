#include <geSG/StateSet.h>
#include <geSG/RenderingContext.h>

using namespace ge::sg;



void StateSet::incrementDrawCommandModeCounter(unsigned incrementAmount,uint16_t mode,
                                               AttribStorageData &storageData)
{
   // increment internal StateSet counters
   // and allocate StateSet buffer data on the first appearance of a given primitive kind
   _numPrimitives+=incrementAmount;
   storageData._numPrimitives+=incrementAmount;
   if(storageData._numPrimitivesOfKind[mode]==0)
      storageData._stateSetBufferIndex[mode]=RenderingContext::current()->allocStateSetBufferItem();
   storageData._numPrimitivesOfKind[mode]+=incrementAmount;
}


void StateSet::decrementDrawCommandModeCounter(unsigned decrementAmount,uint16_t mode,
                                               AttribStorageData &storageData)
{
   // decrement internal StateSetCounters
   // and free StateSet buffer data on the removal of the last primitive of a particular kind
   _numPrimitives-=decrementAmount;
   storageData._numPrimitives-=decrementAmount;
   storageData._numPrimitivesOfKind[mode]-=decrementAmount;
   if(storageData._numPrimitivesOfKind[mode]==0) {
      RenderingContext::current()->freeStateSetBufferItem(storageData._stateSetBufferIndex[mode]);
      storageData._stateSetBufferIndex[mode]=0;
   }
}


void StateSet::decrementDrawCommandModeCounter(unsigned decrementAmount,uint16_t mode,const AttribStorage *storage)
{
   auto storageDataIterator=getOrCreateAttribStorageData(storage);
   decrementDrawCommandModeCounter(decrementAmount,mode,storageDataIterator->second);
   releaseAttribStorageDataIfEmpty(storageDataIterator);
}
