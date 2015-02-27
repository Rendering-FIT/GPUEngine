#ifndef GE_SG_ALLOCATION_MANAGERS_H
#define GE_SG_ALLOCATION_MANAGERS_H

#include <vector>
#include <geSG/Export.h>

namespace ge
{
   namespace sg
   {
      class AttribReference;

      /** ChunkAllocation represents single allocation block of memory
       *  inside ChunkAllocationManager.
       *  Memory blocks may vary in size. The smallest allocation unit is one byte.
       *  The structure is used by AttribStorage and related classes for memory management purposes.
       */
      struct GESG_EXPORT ChunkAllocation {
         unsigned offset;         ///< Offset of the start of the block.
         unsigned size;           ///< Number of bytes in the block.
         unsigned nextRec;        ///< \brief Index of ChunkAllocation whose allocated memory follows the current block's memory.
         AttribReference *owner;  ///< AttribReference that owns the allocated block. Null indicates free block.
		 inline ChunkAllocation();  ///< Default constructor does nothing.
		 inline ChunkAllocation(unsigned offset,unsigned size,unsigned nextRec,AttribReference *owner);  ///< Constructs structure by given values.
      };


      /** BlockAllocation represents single allocation element of memory
       *  inside BlockAllocationManager. It works over arrays of elements of constant size.
       *  The smallest allocation unit is one array element.
       *  The structure is used by AttribStorage and related classes for memory management purposes.
       */
      struct GESG_EXPORT BlockAllocation {
         unsigned startIndex;     ///< Index of the start of the block. The real offset is startIndex multiplied by the size of the underlaying array element.
         unsigned numElements;    ///< Number of elements in the block. The real size is numElements multiplied by the size of the underlaying array element.
         unsigned nextRec;        ///< \brief Index of BlockAllocation whose allocated memory follows the current block's memory.
         AttribReference *owner;  ///< AttribReference that owns the allocated block. Null indicates free block.
		 inline BlockAllocation();  ///< Default constructor does nothing.
		 inline BlockAllocation(unsigned startIndex,unsigned numElements,unsigned nextRec,AttribReference *owner);  ///< Constructs structure by given values.
      };


      class GESG_EXPORT ChunkAllocationManager : public std::vector<ChunkAllocation> {
      public:
         unsigned _numBytesTotal;               ///< Total number of bytes. Sum of allocated and unallocated space.
         unsigned _numBytesAvailable;           ///< Number of bytes available for allocation.
         unsigned _numBytesAvailableAtTheEnd;   ///< Number of available bytes at the end of managed memory, e.g. size of the block of available bytes residing at the end.
         unsigned _firstByteAvailableAtTheEnd;  ///< Offset of the first available byte at the end of managed memory that is followed by available bytes only.
         unsigned _idOfBlockAtTheEnd;        ///< Id (index to std::vector\<ChunkAllocation\>) of the last allocated block at the end of managed memory.
         inline ChunkAllocationManager(unsigned capacity);
         inline bool canAllocate(unsigned numBytes) const;
         unsigned alloc(unsigned numBytes,AttribReference &r);  // Allocates memory block. Returns id of the block or zero on failure.
         inline void free(unsigned id);  // Frees allocated block. Id must be valid allocated block. Zero id is allowed and safely ignored.
         void clear();
      };


      class GESG_EXPORT BlockAllocationManager : public std::vector<BlockAllocation> {
      public:
         unsigned _numItemsTotal;               ///< Total number of items (allocated plus unallocated).
         unsigned _numItemsAvailable;           ///< Number of items available for allocation.
         unsigned _numItemsAvailableAtTheEnd;   ///< Number of available items at the end of managed memory, e.g. number of items in the block at the end.
         unsigned _firstItemAvailableAtTheEnd;  ///< Index of the first available item at the end of managed memory that is followed by available items only.
         unsigned _idOfBlockAtTheEnd;           ///< Id (index to std::vector\<BlockAllocation\>) of the last allocated block at the end of managed memory.
         inline BlockAllocationManager(unsigned capacity);
         inline bool canAllocate(unsigned numItems) const;
         unsigned alloc(unsigned numItems,AttribReference &r);  // Allocates number of items. Returns id or zero on failure.
         inline void free(unsigned id);  // Frees allocated items. Id must be valid. Zero id is allowed and safely ignored.
         void clear();
      };


      class GESG_EXPORT ItemAllocationManager : public std::vector<unsigned*> {
      public:
         unsigned _numItemsTotal;               ///< Total number of items (allocated plus unallocated).
         unsigned _numItemsAvailable;           ///< Number of items available for allocation.
         unsigned _numItemsAvailableAtTheEnd;   ///< Number of available items at the end of managed memory, e.g. number of items in the block at the end.
         unsigned _firstItemAvailableAtTheEnd;  ///< Index of the first available item at the end of managed memory that is followed by available items only.
         inline ItemAllocationManager(unsigned capacity);
         inline bool canAllocate(unsigned numItems) const;
         bool alloc(unsigned* id);  ///< \brief Allocates one item and stores the item's id to the variable pointed by id parameter.
         bool alloc(unsigned numItems,unsigned* ids);  ///< \brief Allocates number of items.
         void free(unsigned id);  ///< Frees allocated item. Id must be valid.
         void free(unsigned* ids,unsigned numItems);  ///< Frees allocated items. Ids pointed by ids parameter must be valid.
         void clear();
      };


      // inline and template methods
	  inline ChunkAllocation::ChunkAllocation()  {}
	  inline ChunkAllocation::ChunkAllocation(unsigned offset,unsigned size,unsigned nextRec,AttribReference *owner)
      { this->offset=offset; this->size=size; this->nextRec=nextRec; this->owner=owner; }
	  inline BlockAllocation::BlockAllocation()  {}
	  inline BlockAllocation::BlockAllocation(unsigned startIndex,unsigned numElements,unsigned nextRec,AttribReference *owner)
      { this->startIndex=startIndex; this->numElements=numElements; this->nextRec=nextRec; this->owner=owner; }
      inline ChunkAllocationManager::ChunkAllocationManager(unsigned capacity)
         : _numBytesTotal(capacity), _numBytesAvailable(capacity), _numBytesAvailableAtTheEnd(capacity),
           _firstByteAvailableAtTheEnd(0), _idOfBlockAtTheEnd(0)
      {
         // zero element is reserved for invalid object
         // and it serves as Null object (Null object design pattern)
         emplace_back(0,0,0,nullptr);
      }
      inline BlockAllocationManager::BlockAllocationManager(unsigned capacity)
         : _numItemsTotal(capacity), _numItemsAvailable(capacity), _numItemsAvailableAtTheEnd(capacity),
           _firstItemAvailableAtTheEnd(0), _idOfBlockAtTheEnd(0)
      {
         // zero element is reserved for invalid object
         // and it serves as Null object (Null object design pattern)
         emplace_back(0,0,0,nullptr);
      }
      inline ItemAllocationManager::ItemAllocationManager(unsigned capacity)
         : std::vector<unsigned*>(capacity), _numItemsTotal(capacity), _numItemsAvailable(capacity),
           _numItemsAvailableAtTheEnd(capacity), _firstItemAvailableAtTheEnd(0)  {}
      inline bool ChunkAllocationManager::canAllocate(unsigned numBytes) const
      { return _numBytesAvailableAtTheEnd>=numBytes; }
      inline bool BlockAllocationManager::canAllocate(unsigned numItems) const
      { return _numItemsAvailableAtTheEnd>=numItems; }
      inline bool ItemAllocationManager::canAllocate(unsigned numItems) const
      { return _numItemsAvailableAtTheEnd>=numItems; }
      inline void ChunkAllocationManager::free(unsigned id)  { operator[](id).owner=nullptr; }
      inline void BlockAllocationManager::free(unsigned id)  { operator[](id).owner=nullptr; }

   }
}

#endif /* GE_SG_ALLOCATION_MANAGERS_H */
