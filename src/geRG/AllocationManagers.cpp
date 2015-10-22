#include <algorithm>
#include <cassert>
#include <geRG/AllocationManagers.h>

using namespace ge::rg;



void ItemAllocationManager::setCapacity(unsigned value)
{
   unsigned delta=value-_numItemsTotal;
   resize(value);
   _numItemsTotal=value;
   _numItemsAvailable+=delta;
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
   _numItemsAvailable--;
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
   _numItemsAvailable-=numItems;
   _numItemsAvailableAtTheEnd-=numItems;
   _firstItemAvailableAtTheEnd+=numItems;
   return true;
}


void ItemAllocationManager::free(unsigned id)
{
   unsigned* &item=(*this)[id];
   if(item==nullptr) {
      assert(id<_numNullObjects && "ItemAllocationManager::free(): Freeing non-allocated or already freed item");
      return;
   }
   item=nullptr;
   _numItemsAvailable++;
}


void ItemAllocationManager::free(unsigned* ids,unsigned numItems)
{
   unsigned numRemoved=numItems;
   for(unsigned i=0; i<numItems; i++)
   {
      unsigned* &item=(*this)[ids[i]];
      if(item==nullptr) {
         assert(ids[i]<_numNullObjects && "ItemAllocationManager::free(): Freeing non-allocated or already freed item");
         numRemoved--;
         continue;
      }
      item=nullptr;
   }
   _numItemsAvailable+=numRemoved;
}


void ItemAllocationManager::clear()
{
   _numItemsAvailable=_numItemsTotal-_numNullObjects;
   _numItemsAvailableAtTheEnd=_numItemsTotal-_numNullObjects;
   _firstItemAvailableAtTheEnd=_numNullObjects;
}


void ItemAllocationManager::assertEmpty()
{
   assert(_numItemsAvailable+_numNullObjects==_numItemsTotal &&
          "ItemAllocationManager::_numItemsAvailable does not contain valid value.");
}
