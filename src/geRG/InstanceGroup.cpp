#include <geRG/InstanceGroup.h>

using namespace ge::rg;

static_assert(sizeof(InstanceData)<=4,
              "InstanceData size is bigger than 4 bytes.\n"
              "Consider its bits reallocation or rewising this assert.");



bool InstanceAllocationManager::alloc(InstanceData *id)
{
   if(_numItemsAvailableAtTheEnd==0)
      return false;

   (*this)[_firstItemAvailableAtTheEnd]=id;
   uint32_t mode=(*id).data&0xf8000000;
   (*id).data=mode|_firstItemAvailableAtTheEnd;
   _numItemsAvailable--;
   _numItemsAvailableAtTheEnd--;
   _firstItemAvailableAtTheEnd++;
   return true;
}


bool InstanceAllocationManager::alloc(unsigned num,InstanceData *ids)
{
   if(_numItemsAvailableAtTheEnd<num)
      return false;

   for(unsigned i=0; i<num; i++)
   {
      (*this)[_firstItemAvailableAtTheEnd+i]=&ids[i];
      uint32_t mode=ids[i].data&0xf8000000;
      ids[i].data=mode|(_firstItemAvailableAtTheEnd+i);
   }
   _numItemsAvailable-=num;
   _numItemsAvailableAtTheEnd-=num;
   _firstItemAvailableAtTheEnd+=num;
   return true;
}


void InstanceAllocationManager::free(InstanceData* ids,unsigned num)
{
   for(unsigned i=0; i<num; i++)
      (*this)[ids[i].index()]=nullptr;
   _numItemsAvailable+=num;
}
