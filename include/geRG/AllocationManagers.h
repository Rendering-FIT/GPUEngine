#ifndef GE_RG_ALLOCATION_MANAGERS_H
#define GE_RG_ALLOCATION_MANAGERS_H

#include <vector>
#include <geRG/Export.h>

namespace ge
{
   namespace rg
   {

      /** ChunkAllocation represents a single allocation block of memory
       *  inside ChunkAllocationManager. ChunkAllocation is accessed internally
       *  by ChunkAllocationManager through integer-based ID value that is returned
       *  to the user during the allocation process.
       *
       *  ChunkAllocation is used for allocation of memory chunk. The size of
       *  the memory chunk is specified by user and may vary from chunk to chunk.
       *  The smallest allocation unit is one byte.
       */
      template<typename OwnerType>
      struct ChunkAllocation {
         unsigned offset;           ///< Offset of the start of the block.
         unsigned size;             ///< Number of bytes in the block.
         unsigned nextRec;          ///< \brief Index of ChunkAllocation whose allocated memory follows the current block's memory.
         OwnerType *owner;          ///< Object that owns the allocated block. Null indicates free block.
         inline ChunkAllocation()  {}  ///< Default constructor. It does nothing.
         inline ChunkAllocation(unsigned offset,unsigned size,unsigned nextRec,OwnerType *owner);  ///< Constructs structure by given values.
      };


      /** BlockAllocation represents a single allocation element of memory
       *  inside BlockAllocationManager. BlockAllocation is accessed internally
       *  by BlockAllocationManager through integer-based ID value that is returned
       *  to the user during the allocation process.
       *
       *  BlockAllocation is used for allocation of items. The items are allocated in arrays
       *  of some size. The smallest allocation is one array element, or theoretically zero
       *  for allocating just ID. All the items in the array are expected to be the same size.
       */
      template<typename OwnerType>
      struct BlockAllocation {
         unsigned startIndex;       ///< Index of the start of the block. The real offset is startIndex multiplied by the size of the underlaying array element.
         unsigned numItems;         ///< Number of items in the block. The real size is numItems multiplied by the size of the item.
         unsigned nextRec;          ///< \brief Index of BlockAllocation whose allocated memory follows the current block's memory.
         OwnerType *owner;          ///< Object that owns the allocated block. Null indicates free block.
         inline BlockAllocation()  {}  ///< Default constructor. It does nothing.
         inline BlockAllocation(unsigned startIndex,unsigned numItems,unsigned nextRec,OwnerType *owner);  ///< Constructs structure by the given values.
      };


      /** ChunkAllocationManager provides memory management functionality.
       *  It allows to allocate chunks of memory. Each chunk may be of a different size.
       *  Chunks are identified by the intenger-based ID.
       *  The smallest allocation unit is one byte. The largest allocation possible
       *  is equal to the largest available block.
       *
       *  ChunkAllocationManager does not maintain any memory buffer. It just provides
       *  memory management functionality. See BufferStorage template for combining
       *  ge::gl::BufferObject and ChunkAllocationManager functionality.
       */
      template<typename ChunkOwnerType>
      class ChunkAllocationManager : public std::vector<ChunkAllocation<ChunkOwnerType>> {
      protected:

         unsigned _numBytesTotal;               ///< Total number of bytes, e.g. sum of allocated and unallocated space.
         unsigned _numBytesAvailable;           ///< Number of bytes available for allocation.
         unsigned _numBytesAvailableAtTheEnd;   ///< Number of available bytes at the end of the managed memory, e.g. size of the block of available bytes residing at the end.
         unsigned _firstByteAvailableAtTheEnd;  ///< Offset of the first available byte at the end of the managed memory, e.g. the first available byte that is followed by available space only.
         unsigned _idOfBlockAtTheEnd;           ///< Id (index to std::vector\<ChunkAllocation\>) of the last allocated block at the end of the managed memory.

      public:

         typedef ChunkOwnerType AllocationOwner;

         inline unsigned numBytesTotal() const;              ///< Returns total number of bytes, e.g. sum of allocated and unallocated space.
         inline unsigned numBytesAvailable() const;          ///< Returns the number of bytes available for allocation.
         inline unsigned numBytesAvailableAtTheEnd() const;  ///< Returns the number of available bytes at the end of the managed memory, e.g. size of the block of available bytes residing at the end.
         inline unsigned firstByteAvailableAtTheEnd() const; ///< Returns the offset of the first available byte at the end of the managed memory, e.g. the first available byte that is followed by available space only.
         inline unsigned idOfBlockAtTheEnd() const;          ///< Returns id (index to std::vector\<BlockAllocation\>) of the last allocated block at the end of the managed memory.

         inline ChunkAllocationManager(unsigned capacity=0);
         inline ChunkAllocationManager(unsigned capacity,unsigned nullObjectSize);
         void setCapacity(unsigned value);
         inline unsigned capacity() const;
         inline unsigned availableSpace() const;
         inline unsigned largestAvailableBlock() const;
         inline unsigned availableSpaceAtTheEnd() const;

         inline bool canAllocate(unsigned numBytes) const;
         unsigned alloc(unsigned numBytes,ChunkOwnerType &owner);  // Allocates memory block. Returns id of the block or zero on failure.
         inline void free(unsigned id);  // Frees allocated block. Id must be valid allocated block. Zero id is allowed and safely ignored.
         void clear();
      };


      /** BlockAllocationManager provides memory management functionality.
       *  It allows to allocate blocks of items. All the items must be of the same size,
       *  but the item can be anything from a single byte to a large structure.
       *  Blocks are identified by the intenger-based ID.
       *  The smallest allocation unit is one item. The largest allocation possible
       *  is equal to the largest available block.
       *
       *  BlockAllocationManager does not maintain any memory buffer. It just provides
       *  memory management functionality. See BufferStorage template for combining
       *  ge::gl::BufferObject and BlockAllocationManager functionality.
       */
      template<typename BlockOwnerType>
      class BlockAllocationManager : public std::vector<BlockAllocation<BlockOwnerType>> {
      protected:

         unsigned _numItemsTotal;               ///< Total number of items (allocated and unallocated).
         unsigned _numItemsAvailable;           ///< Number of items available for allocation.
         unsigned _numItemsAvailableAtTheEnd;   ///< Number of available items at the end of the managed memory, e.g. number of items in the block at the end.
         unsigned _firstItemAvailableAtTheEnd;  ///< Index of the first available item at the end of the managed memory, e.g. the first available item that is followed by available items only.
         unsigned _idOfBlockAtTheEnd;           ///< Id (index to std::vector\<BlockAllocation\>) of the last allocated block at the end of the managed memory.

      public:

         typedef BlockOwnerType AllocationOwner;

         inline unsigned numItemsTotal() const;              ///< Returns total number of items (allocated and unallocated).
         inline unsigned numItemsAvailable() const;          ///< Returns the number of items that are available for allocation.
         inline unsigned numItemsAvailableAtTheEnd() const;  ///< Returns the number of items that are available at the end of the managed memory, e.g. number of items in the block at the end.
         inline unsigned firstItemAvailableAtTheEnd() const; ///< Returns the index of the first available item at the end of the managed memory, e.g. the first available item that is followed by available items only.
         inline unsigned idOfBlockAtTheEnd() const;          ///< Returns id (index to std::vector\<BlockAllocation\>) of the last allocated block at the end of the managed memory.

         inline BlockAllocationManager(unsigned capacity=0);
         inline BlockAllocationManager(unsigned capacity,unsigned nullObjectNumElements);
         void setCapacity(unsigned value);
         inline unsigned capacity() const;
         inline unsigned availableSpace() const;
         inline unsigned largestAvailableBlock() const;
         inline unsigned availableSpaceAtTheEnd() const;

         inline bool canAllocate(unsigned numItems) const;
         unsigned alloc(unsigned numItems,BlockOwnerType &owner);  // Allocates number of items. Returns id or zero on failure.
         inline void free(unsigned id);  // Frees allocated items. Id must be valid. Zero id is allowed and safely ignored.
         void clear();
      };


      /** ItemAllocationManager provides memory management functionality.
       *  It allows to allocate items. All the items must be of the same size,
       *  but the item can be anything from a single byte to a large structure.
       *  Items are identified by the intenger-based ID. ID is the number of the item,
       *  begining at 0 for the first item and ending at numItemsTotal()-1 for the last item.
       *
       *  The smallest allocation unit is one item. The largest allocation possible
       *  is equal to the number of available items.
       *
       *  ItemAllocationManager does not maintain any memory buffer. It just provides
       *  memory management functionality. See BufferStorage template for combining
       *  ge::gl::BufferObject and ItemAllocationManager functionality.
       */
      class GERG_EXPORT ItemAllocationManager : public std::vector<unsigned*> {
      protected:

         unsigned _numItemsTotal;               ///< Total number of items (allocated plus unallocated).
         unsigned _numItemsAvailable;           ///< Number of items available for allocation.
         unsigned _numItemsAvailableAtTheEnd;   ///< Number of available items at the end of the managed memory, e.g. number of items in the block at the end.
         unsigned _firstItemAvailableAtTheEnd;  ///< Index of the first available item at the end of the managed memory that is followed by available items only.
         unsigned _numNullObjects;              ///< Number of null objects (null design pattern) allocated at the beginning of the managed memory.

      public:

         inline unsigned numItemsTotal() const;              ///< Returns total number of items (allocated and unallocated).
         inline unsigned numItemsAvailable() const;          ///< Returns the number of items that are available for allocation.
         inline unsigned numItemsAvailableAtTheEnd() const;  ///< Returns the number of items that are available at the end of the managed memory, e.g. number of items in the block at the end.
         inline unsigned firstItemAvailableAtTheEnd() const; ///< Returns the index of the first available item at the end of the managed memory, e.g. the first available item that is followed by available items only.
         inline unsigned numNullObjects() const;             ///< Returns the number of null objects (null design pattern) allocated at the beginning of the managed memory.

         inline ItemAllocationManager(unsigned capacity=0);
         inline ItemAllocationManager(unsigned capacity,unsigned numNullObjects);
         void setCapacity(unsigned value);
         inline unsigned capacity() const;
         inline unsigned availableSpace() const;
         inline unsigned largestAvailableBlock() const;
         inline unsigned availableSpaceAtTheEnd() const;

         inline bool canAllocate(unsigned numItems) const;
         bool alloc(unsigned *id);  ///< \brief Allocates one item and stores the item's id in the variable pointed by id parameter.
         bool alloc(unsigned numItems,unsigned* ids);  ///< \brief Allocates number of items. The returned items may not form the continuous block of memory. Array pointed by ids must be at least numItems long.
         void free(unsigned id);  ///< Frees allocated item. Id must be valid.
         void free(unsigned* ids,unsigned numItems);  ///< Frees allocated items. Ids pointed by ids parameter must be valid.
         void clear();
         void assertEmpty();
         inline void setOwner(unsigned id,unsigned* const owner);
         inline unsigned* owner(unsigned id) const;
      };

   }
}



// inline and template methods

#include <cstring>

namespace ge
{
   namespace rg
   {

      template<typename OwnerType> inline ChunkAllocation<OwnerType>::ChunkAllocation(unsigned offset,unsigned size,unsigned nextRec,OwnerType *owner)
      { this->offset=offset; this->size=size; this->nextRec=nextRec; this->owner=owner; }
      template<typename OwnerType> inline BlockAllocation<OwnerType>::BlockAllocation(unsigned startIndex,unsigned numItems,unsigned nextRec,OwnerType *owner)
      { this->startIndex=startIndex; this->numItems=numItems; this->nextRec=nextRec; this->owner=owner; }
      template<typename OwnerType> inline unsigned ChunkAllocationManager<OwnerType>::numBytesTotal() const  { return _numBytesTotal; }
      template<typename OwnerType> inline unsigned ChunkAllocationManager<OwnerType>::numBytesAvailable() const  { return _numBytesAvailable; }
      template<typename OwnerType> inline unsigned ChunkAllocationManager<OwnerType>::numBytesAvailableAtTheEnd() const  { return _numBytesAvailableAtTheEnd; }
      template<typename OwnerType> inline unsigned ChunkAllocationManager<OwnerType>::firstByteAvailableAtTheEnd() const  { return _firstByteAvailableAtTheEnd; }
      template<typename OwnerType> inline unsigned ChunkAllocationManager<OwnerType>::idOfBlockAtTheEnd() const  { return _idOfBlockAtTheEnd; }
      template<typename OwnerType> inline unsigned BlockAllocationManager<OwnerType>::numItemsTotal() const  { return _numItemsTotal; }
      template<typename OwnerType> inline unsigned BlockAllocationManager<OwnerType>::numItemsAvailable() const  { return _numItemsAvailable; }
      template<typename OwnerType> inline unsigned BlockAllocationManager<OwnerType>::numItemsAvailableAtTheEnd() const  { return _numItemsAvailableAtTheEnd; }
      template<typename OwnerType> inline unsigned BlockAllocationManager<OwnerType>::firstItemAvailableAtTheEnd() const  { return _firstItemAvailableAtTheEnd; }
      template<typename OwnerType> inline unsigned BlockAllocationManager<OwnerType>::idOfBlockAtTheEnd() const  { return _idOfBlockAtTheEnd; }
      inline unsigned ItemAllocationManager::numItemsTotal() const  { return _numItemsTotal; }
      inline unsigned ItemAllocationManager::numItemsAvailable() const  { return _numItemsAvailable; }
      inline unsigned ItemAllocationManager::numItemsAvailableAtTheEnd() const  { return _numItemsAvailableAtTheEnd; }
      inline unsigned ItemAllocationManager::firstItemAvailableAtTheEnd() const  { return _firstItemAvailableAtTheEnd; }
      inline unsigned ItemAllocationManager::numNullObjects() const  { return _numNullObjects; }
      template<typename OwnerType>
      inline ChunkAllocationManager<OwnerType>::ChunkAllocationManager(unsigned capacity)
         : _numBytesTotal(capacity), _numBytesAvailable(capacity), _numBytesAvailableAtTheEnd(capacity),
           _firstByteAvailableAtTheEnd(0), _idOfBlockAtTheEnd(0)
      {
         // zero element is reserved for invalid object
         // and it serves as Null object (Null object design pattern)
         std::vector<ChunkAllocation<OwnerType>>::emplace_back(0,0,0,nullptr);
      }
      template<typename OwnerType>
      inline ChunkAllocationManager<OwnerType>::ChunkAllocationManager(unsigned capacity,unsigned nullObjectSize)
         : _numBytesTotal(capacity), _numBytesAvailable(capacity-nullObjectSize),
           _numBytesAvailableAtTheEnd(capacity-nullObjectSize),
           _firstByteAvailableAtTheEnd(nullObjectSize), _idOfBlockAtTheEnd(0)
      {
         // zero element is reserved for invalid object
         // and it serves as Null object (Null object design pattern)
         std::vector<ChunkAllocation<OwnerType>>::emplace_back(0,nullObjectSize,0,nullptr);
      }
      template<typename OwnerType> void ChunkAllocationManager<OwnerType>::setCapacity(unsigned value)
      {
         unsigned delta=value-_numBytesTotal;
         _numBytesTotal=value;
         _numBytesAvailable+=delta;
         _numBytesAvailableAtTheEnd+=delta;
      }
      template<typename OwnerType>
      inline BlockAllocationManager<OwnerType>::BlockAllocationManager(unsigned capacity)
         : _numItemsTotal(capacity), _numItemsAvailable(capacity), _numItemsAvailableAtTheEnd(capacity),
           _firstItemAvailableAtTheEnd(0), _idOfBlockAtTheEnd(0)
      {
         // zero element is reserved for invalid object
         // and it serves as Null object (Null object design pattern)
         std::vector<BlockAllocation<OwnerType>>::emplace_back(0,0,0,nullptr);
      }
      template<typename OwnerType>
      inline BlockAllocationManager<OwnerType>::BlockAllocationManager(unsigned capacity,unsigned nullObjectNumElements)
         : _numItemsTotal(capacity), _numItemsAvailable(capacity-nullObjectNumElements),
           _numItemsAvailableAtTheEnd(capacity-nullObjectNumElements),
           _firstItemAvailableAtTheEnd(nullObjectNumElements), _idOfBlockAtTheEnd(0)
      {
         // zero element is reserved for invalid object
         // and it serves as Null object (Null object design pattern)
         std::vector<BlockAllocation<OwnerType>>::emplace_back(0,nullObjectNumElements,0,nullptr);
      }
      template<typename OwnerType> void BlockAllocationManager<OwnerType>::setCapacity(unsigned value)
      {
         unsigned delta=value-_numItemsTotal;
         _numItemsTotal=value;
         _numItemsAvailable+=delta;
         _numItemsAvailableAtTheEnd+=delta;
      }
      inline ItemAllocationManager::ItemAllocationManager(unsigned capacity)
         : std::vector<unsigned*>(capacity), // sets the capacity and resizes the vector, default-inserting elements
           _numItemsTotal(capacity), _numItemsAvailable(capacity), _numItemsAvailableAtTheEnd(capacity),
           _firstItemAvailableAtTheEnd(0), _numNullObjects(0)  {}
      inline ItemAllocationManager::ItemAllocationManager(unsigned capacity,unsigned numNullObjects)
         : std::vector<unsigned*>(capacity), // sets the capacity and resizes the vector, default-inserting elements
           _numItemsTotal(capacity), _numItemsAvailable(capacity-numNullObjects),
           _numItemsAvailableAtTheEnd(capacity-numNullObjects),
           _firstItemAvailableAtTheEnd(numNullObjects), _numNullObjects(numNullObjects)
      {
         std::memset(this->data(),0,numNullObjects*sizeof(unsigned*));
      }
      template<typename OwnerType> inline unsigned ChunkAllocationManager<OwnerType>::capacity() const  { return unsigned(std::vector<ChunkAllocation<OwnerType>>::size()); }
      template<typename OwnerType> inline unsigned BlockAllocationManager<OwnerType>::capacity() const  { return unsigned(std::vector<BlockAllocation<OwnerType>>::size()); }
      inline unsigned ItemAllocationManager::capacity() const  { return unsigned(size()); }
      template<typename OwnerType> inline unsigned ChunkAllocationManager<OwnerType>::availableSpace() const  { return _numBytesAvailable; }
      template<typename OwnerType> inline unsigned BlockAllocationManager<OwnerType>::availableSpace() const  { return _numItemsAvailable; }
      inline unsigned ItemAllocationManager::availableSpace() const  { return _numItemsAvailable; }
      template<typename OwnerType> inline unsigned ChunkAllocationManager<OwnerType>::largestAvailableBlock() const  { return _numBytesAvailableAtTheEnd; }
      template<typename OwnerType> inline unsigned BlockAllocationManager<OwnerType>::largestAvailableBlock() const  { return _numItemsAvailableAtTheEnd; }
      inline unsigned ItemAllocationManager::largestAvailableBlock() const  { return _numItemsAvailableAtTheEnd; }
      template<typename OwnerType> inline unsigned ChunkAllocationManager<OwnerType>::availableSpaceAtTheEnd() const  { return _numBytesAvailableAtTheEnd; }
      template<typename OwnerType> inline unsigned BlockAllocationManager<OwnerType>::availableSpaceAtTheEnd() const  { return _numItemsAvailableAtTheEnd; }
      inline unsigned ItemAllocationManager::availableSpaceAtTheEnd() const  { return _numItemsAvailableAtTheEnd; }
      template<typename OwnerType> inline bool ChunkAllocationManager<OwnerType>::canAllocate(unsigned numBytes) const
      { return _numBytesAvailableAtTheEnd>=numBytes; }
      template<typename OwnerType> inline bool BlockAllocationManager<OwnerType>::canAllocate(unsigned numItems) const
      { return _numItemsAvailableAtTheEnd>=numItems; }
      inline bool ItemAllocationManager::canAllocate(unsigned numItems) const
      { return _numItemsAvailableAtTheEnd>=numItems; }
      template<typename OwnerType> inline void ChunkAllocationManager<OwnerType>::free(unsigned id)  { std::vector<ChunkAllocation<OwnerType>>::operator[](id).owner=nullptr; }
      template<typename OwnerType> inline void BlockAllocationManager<OwnerType>::free(unsigned id)  { std::vector<BlockAllocation<OwnerType>>::operator[](id).owner=nullptr; }
      inline void ItemAllocationManager::setOwner(unsigned id,unsigned* const owner)  { operator[](id)=owner; }
      inline unsigned* ItemAllocationManager::owner(unsigned id) const  { return operator[](id); }

      template<typename OwnerType>
      unsigned ChunkAllocationManager<OwnerType>::alloc(unsigned numBytes,OwnerType &owner)
      {
         if(_numBytesAvailableAtTheEnd<numBytes)
            return 0;

         unsigned id=unsigned(std::vector<ChunkAllocation<OwnerType>>::size());
         std::vector<ChunkAllocation<OwnerType>>::emplace_back(_firstByteAvailableAtTheEnd,numBytes,0,&owner);
         std::vector<ChunkAllocation<OwnerType>>::operator[](_idOfBlockAtTheEnd).nextRec=id;
         _numBytesAvailable-=numBytes;
         _numBytesAvailableAtTheEnd-=numBytes;
         _firstByteAvailableAtTheEnd+=numBytes;
         _idOfBlockAtTheEnd=id;
         return id;
      }

      template<typename OwnerType>
      unsigned BlockAllocationManager<OwnerType>::alloc(unsigned numItems,OwnerType &owner)
      {
         if(_numItemsAvailableAtTheEnd<numItems)
            return 0;

         unsigned id=unsigned(std::vector<BlockAllocation<OwnerType>>::size());
         std::vector<BlockAllocation<OwnerType>>::emplace_back(_firstItemAvailableAtTheEnd,numItems,0,&owner);
         std::vector<BlockAllocation<OwnerType>>::operator[](_idOfBlockAtTheEnd).nextRec=id;
         _numItemsAvailable-=numItems;
         _numItemsAvailableAtTheEnd-=numItems;
         _firstItemAvailableAtTheEnd+=numItems;
         _idOfBlockAtTheEnd=id;
         return id;
      }

      template<typename OwnerType>
      void ChunkAllocationManager<OwnerType>::clear()
      {
         std::vector<ChunkAllocation<OwnerType>>::clear();
         _numBytesAvailable=_numBytesTotal;
         _numBytesAvailableAtTheEnd=_numBytesTotal;
         _firstByteAvailableAtTheEnd=0;
         _idOfBlockAtTheEnd=0;
      }

      template<typename OwnerType>
      void BlockAllocationManager<OwnerType>::clear()
      {
         std::vector<BlockAllocation<OwnerType>>::clear();
         _numItemsAvailable=_numItemsTotal;
         _numItemsAvailableAtTheEnd=_numItemsTotal;
         _firstItemAvailableAtTheEnd=0;
         _idOfBlockAtTheEnd=0;
      }

   }
}

#endif /* GE_RG_ALLOCATION_MANAGERS_H */
