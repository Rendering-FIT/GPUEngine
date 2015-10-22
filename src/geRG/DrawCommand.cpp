#include <geRG/DrawCommand.h>

using namespace ge::rg;

static_assert(sizeof(DrawCommand)==4,
              "DrawCommand size is not 4 bytes.\n"
              "Consider its bits reallocation or rewising this assert.");



bool DrawCommandAllocationManager::alloc(DrawCommand *id)
{
   if(_numItemsAvailableAtTheEnd==0)
      return false;

   (*this)[_firstItemAvailableAtTheEnd]=id;
   unsigned mode=(*id).data&0xf8000000;
   (*id).data=mode|_firstItemAvailableAtTheEnd;
   _numItemsAvailable--;
   _numItemsAvailableAtTheEnd--;
   _firstItemAvailableAtTheEnd++;
   return true;
}


bool DrawCommandAllocationManager::alloc(unsigned num,DrawCommand *ids)
{
   if(_numItemsAvailableAtTheEnd<num)
      return false;

   for(unsigned i=0; i<num; i++)
   {
      (*this)[_firstItemAvailableAtTheEnd+i]=&ids[i];
      unsigned mode=ids[i].data&0xf8000000;
      ids[i].data=mode|(_firstItemAvailableAtTheEnd+i);
   }
   _numItemsAvailable-=num;
   _numItemsAvailableAtTheEnd-=num;
   _firstItemAvailableAtTheEnd+=num;
   return true;
}


void DrawCommandAllocationManager::free(DrawCommand* ids,unsigned num)
{
   for(unsigned i=0; i<num; i++)
      (*this)[ids[i].index()]=nullptr;
   _numItemsAvailable+=num;
}
