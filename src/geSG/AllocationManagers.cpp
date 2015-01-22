#include <geSG/AllocationManagers.h>

using namespace ge::sg;


unsigned AllocationBlockManager::alloc(unsigned numBytes,AttribReference &r)
{
   if(_numBytesAvailableAtTheEnd<numBytes)
      return 0;

   unsigned id=size();
   emplace_back(_firstByteAvailableAtTheEnd,numBytes,0,&r);
   operator[](_idOfBlockAtTheEnd).nextRec=id;
   _idOfBlockAtTheEnd=id;
   return id;
}


unsigned AllocationItemManager::alloc(unsigned numItems,AttribReference &r)
{
   if(_numItemsAvailableAtTheEnd<numItems)
      return 0;

   unsigned id=size();
   emplace_back(_firstItemAvailableAtTheEnd,numItems,0,&r);
   operator[](_idOfBlockAtTheEnd).nextRec=id;
   _idOfBlockAtTheEnd=id;
   return id;
}


void AllocationBlockManager::clear()
{
   vector<AllocationBlock>::clear();
   _numBytesAvailable=_numBytesTotal;
   _numBytesAvailableAtTheEnd=_numBytesTotal;
   _firstByteAvailableAtTheEnd=0;
   _idOfBlockAtTheEnd=0;
}


void AllocationItemManager::clear()
{
   vector<AllocationItem>::clear();
   _numItemsAvailable=_numItemsTotal;
   _numItemsAvailableAtTheEnd=_numItemsTotal;
   _firstItemAvailableAtTheEnd=0;
   _idOfBlockAtTheEnd=0;
}
