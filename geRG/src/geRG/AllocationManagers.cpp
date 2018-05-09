#include <algorithm>
#include <cassert>
#include <geRG/AllocationManagers.h>

using namespace ge::rg;



void ItemAllocationManager::setCapacity(unsigned value)
{
   int delta=value-_capacity;
   _allocations.resize(value);
   _capacity=value;
   _available+=delta;
   _numItemsAvailableAtTheEnd+=delta;
}


// brief doc in declaration
/** The relation is established that whenever the item is moved
 *  (f.ex. by various memory optimization or compactation routines),
 *  variable pointed by id is updated to the new item's location.
 *
 *  True is returned on success, false otherwise.
 */
bool ItemAllocationManager::alloc(unsigned *id)
{
   // handle out of free items
   if(_numItemsAvailableAtTheEnd==0)
      return false;

   // alloc item
   (*this)[_firstItemAvailableAtTheEnd]=id;
   (*id)=_firstItemAvailableAtTheEnd;
   _available--;
   _numItemsAvailableAtTheEnd--;
   _firstItemAvailableAtTheEnd++;
   return true;
}


// brief doc in declaration
/** Ids of allocated items are stored in the array given by ids pointer.
 *
 *  The relation is established that whenever the item is moved
 *  (f.ex. by various memory optimization or compactation routines),
 *  variables pointed by ids are updated to the new item's locations.
 *
 *  True is returned on success, false otherwise. On failure,
 *  array given by ids parameter is left in undefined state.
 */
bool ItemAllocationManager::alloc(unsigned numItems,unsigned* ids)
{
   // handle out of free items
   if(_numItemsAvailableAtTheEnd<numItems)
      return false;

   // alloc item
   for(unsigned i=0; i<numItems; i++)
   {
      (*this)[_firstItemAvailableAtTheEnd+i]=&ids[i];
      ids[i]=_firstItemAvailableAtTheEnd+i;
   }
   _available-=numItems;
   _numItemsAvailableAtTheEnd-=numItems;
   _firstItemAvailableAtTheEnd+=numItems;
   return true;
}


void ItemAllocationManager::free(unsigned id)
{
   unsigned* &item=(*this)[id];
   if(item==nullptr) {
      assert(id<_numNullItems && "ItemAllocationManager::free(): Freeing non-allocated or already freed item");
      return;
   }
   item=nullptr;
   _available++;
}


void ItemAllocationManager::free(unsigned* ids,unsigned numItems)
{
   unsigned numRemoved=numItems;
   for(unsigned i=0; i<numItems; i++)
   {
      unsigned* &item=(*this)[ids[i]];
      if(item==nullptr) {
         assert(ids[i]<_numNullItems && "ItemAllocationManager::free(): Freeing non-allocated or already freed item");
         numRemoved--;
         continue;
      }
      item=nullptr;
   }
   _available+=numRemoved;
}


void ItemAllocationManager::clear()
{
   _available=_capacity-_numNullItems;
   _numItemsAvailableAtTheEnd=_capacity-_numNullItems;
   _firstItemAvailableAtTheEnd=_numNullItems;
}


void ItemAllocationManager::assertEmpty()
{
   assert(_available+_numNullItems==_capacity &&
          "ItemAllocationManager::_available does not contain valid value.");
}
