#include <geSG/AllocationManagers.h>

using namespace ge::sg;


unsigned ChunkAllocationManager::alloc(unsigned numBytes,AttribReference &r)
{
   if(_numBytesAvailableAtTheEnd<numBytes)
      return 0;

   unsigned id=unsigned(size());
   emplace_back(_firstByteAvailableAtTheEnd,numBytes,0,&r);
   operator[](_idOfBlockAtTheEnd).nextRec=id;
   _numBytesAvailable-=numBytes;
   _numBytesAvailableAtTheEnd-=numBytes;
   _firstByteAvailableAtTheEnd+=numBytes;
   _idOfBlockAtTheEnd=id;
   return id;
}


unsigned BlockAllocationManager::alloc(unsigned numItems,AttribReference &r)
{
   if(_numItemsAvailableAtTheEnd<numItems)
      return 0;

   unsigned id=unsigned(size());
   emplace_back(_firstItemAvailableAtTheEnd,numItems,0,&r);
   operator[](_idOfBlockAtTheEnd).nextRec=id;
   _numItemsAvailable-=numItems;
   _numItemsAvailableAtTheEnd-=numItems;
   _firstItemAvailableAtTheEnd+=numItems;
   _idOfBlockAtTheEnd=id;
   return id;
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
   if(_numItemsAvailableAtTheEnd==0)
      return false;

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
   if(_numItemsAvailableAtTheEnd<numItems)
      return false;

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
   (*this)[id]=nullptr;
   _numItemsAvailable++;
}


void ItemAllocationManager::free(unsigned* ids,unsigned numItems)
{
   for(unsigned i=0; i<numItems; i++)
      (*this)[ids[i]]=nullptr;
   _numItemsAvailable+=numItems;
}


void ChunkAllocationManager::clear()
{
   vector<ChunkAllocation>::clear();
   _numBytesAvailable=_numBytesTotal;
   _numBytesAvailableAtTheEnd=_numBytesTotal;
   _firstByteAvailableAtTheEnd=0;
   _idOfBlockAtTheEnd=0;
}


void BlockAllocationManager::clear()
{
   vector<BlockAllocation>::clear();
   _numItemsAvailable=_numItemsTotal;
   _numItemsAvailableAtTheEnd=_numItemsTotal;
   _firstItemAvailableAtTheEnd=0;
   _idOfBlockAtTheEnd=0;
}


void ItemAllocationManager::clear()
{
   _numItemsAvailable=_numItemsTotal;
   _numItemsAvailableAtTheEnd=_numItemsTotal;
   _firstItemAvailableAtTheEnd=0;
}
