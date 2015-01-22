#ifndef GE_SG_ALLOCATION_MANAGERS_H
#define GE_SG_ALLOCATION_MANAGERS_H

#include <vector>
#include <geSG/Export.h>

namespace ge
{
   namespace sg
   {
      class AttribReference;

      /** AllocationBlock represents single allocation block of memory inside AllocationBlockManager.
       *  Blocks may vary in size. The smallest allocation unit is one byte.
       *  The structure is used by AttribStorage and related classes for memory management purposes.
       */
      struct GE_EXPORT AllocationBlock {
         unsigned offset;         ///< Offset of the start of the block.
         unsigned size;           ///< Number of bytes in the block.
         unsigned nextRec;        ///< \brief Index of AllocationBlock whose allocated memory follows the current block's memory.
         AttribReference *owner;  ///< AttribReference that owns the allocated block. Null indicates free block.
         inline AllocationBlock(unsigned offset,unsigned size,unsigned nextRec,AttribReference *owner);  ///< Constructs structure by given values.
      };


      /** AllocationItem represents single allocation element of memory inside AllocationItemManager.
       *  It works over arrays of elements of constant size. The smallest allocation unit is one
       *  array element.
       *  The structure is used by AttribStorage and related classes for memory management purposes.
       */
      struct GE_EXPORT AllocationItem {
         unsigned startIndex;     ///< Index of the start of the block. The real offset is startIndex multiplied by the size of the underlaying array element.
         unsigned numElements;    ///< Number of elements in the block. The real size is numElements multiplied by the size of the underlaying array element.
         unsigned nextRec;        ///< \brief Index of AllocationBlock whose allocated memory follows the current block's memory.
         AttribReference *owner;  ///< AttribReference that owns the allocated block. Null indicates free block.
         inline AllocationItem(unsigned startIndex,unsigned numElements,unsigned nextRec,AttribReference *owner);  ///< Constructs structure by given values.
      };


      class GE_EXPORT AllocationBlockManager : public std::vector<AllocationBlock> {
      public:
         unsigned _numBytesTotal;               ///< Total number of bytes. Sum of allocated and unallocated space.
         unsigned _numBytesAvailable;           ///< Number of bytes available for allocation.
         unsigned _numBytesAvailableAtTheEnd;   ///< Number of available bytes at the end of managed memory, e.g. size of the block of available bytes residing at the end.
         unsigned _firstByteAvailableAtTheEnd;  ///< Offset of the first available byte at the end of managed memory that is followed by available bytes only.
         unsigned _idOfBlockAtTheEnd;        ///< Id (index to std::vector\<AllocationBlock\>) of the last allocated block at the end of managed memory.
         inline AllocationBlockManager(unsigned capacity);
         inline bool canAllocate(unsigned numBytes) const;
         unsigned alloc(unsigned numBytes,AttribReference &r);  // Allocates memory block. Returns id of the block or zero if failed.
         inline void free(unsigned id);  // Frees allocated block. Id must be valid allocated block. Zero id is allowed and safely ignored.
         void clear();
      };


      class GE_EXPORT AllocationItemManager : public std::vector<AllocationItem> {
      public:
         unsigned _numItemsTotal;               ///< Total number of items (allocated plus unallocated).
         unsigned _numItemsAvailable;           ///< Number of items available for allocation.
         unsigned _numItemsAvailableAtTheEnd;   ///< Number of available items at the end of managed memory, e.g. number of items in the block at the end.
         unsigned _firstItemAvailableAtTheEnd;  ///< Index of the first available item at the end of managed memory that is followed by available items only.
         unsigned _idOfBlockAtTheEnd;        ///< Id (index to std::vector\<AllocationItem\>) of the last allocated block at the end of managed memory.
         inline AllocationItemManager(unsigned capacity);
         inline bool canAllocate(unsigned numItems) const;
         unsigned alloc(unsigned numItems,AttribReference &r);  // Allocates number of items. Returns id or zero if failed.
         inline void free(unsigned id);  // Frees allocated items. Id must be valid. Zero id is allowed and safely ignored.
         void clear();
      };


      // inline and template methods
      inline AllocationBlock::AllocationBlock(unsigned offset,unsigned size,unsigned nextRec,AttribReference *owner)
      { this->offset=offset; this->size=size; this->nextRec=nextRec; this->owner=owner; }
      inline AllocationItem::AllocationItem(unsigned startIndex,unsigned numElements,unsigned nextRec,AttribReference *owner)
      { this->startIndex=startIndex; this->numElements=numElements; this->nextRec=nextRec; this->owner=owner; }
      inline AllocationBlockManager::AllocationBlockManager(unsigned capacity)
         : _numBytesTotal(capacity), _numBytesAvailable(capacity), _numBytesAvailableAtTheEnd(capacity),
           _firstByteAvailableAtTheEnd(0), _idOfBlockAtTheEnd(0)
      {
         // zero element is reserved for invalid object
         // and it serves as Null object (Null object design pattern)
         emplace_back(0,0,0,nullptr);
      }
      inline AllocationItemManager::AllocationItemManager(unsigned capacity)
         : _numItemsTotal(capacity), _numItemsAvailable(capacity), _numItemsAvailableAtTheEnd(capacity),
           _firstItemAvailableAtTheEnd(0), _idOfBlockAtTheEnd(0)
      {
         // zero element is reserved for invalid object
         // and it serves as Null object (Null object design pattern)
         emplace_back(0,0,0,nullptr);
      }
      inline bool AllocationBlockManager::canAllocate(unsigned numBytes) const
      { return _numBytesAvailableAtTheEnd>=numBytes; }
      inline bool AllocationItemManager::canAllocate(unsigned numItems) const
      { return _numItemsAvailableAtTheEnd>=numItems; }
      inline void AllocationBlockManager::free(unsigned id)  { operator[](id).owner=nullptr; }
      inline void AllocationItemManager::free(unsigned id)  { operator[](id).owner=nullptr; }

   };
};

#endif /* GE_SG_ALLOCATION_MANAGERS_H */
