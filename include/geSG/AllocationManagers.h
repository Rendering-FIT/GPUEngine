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
      template<typename OwnerType>
      struct GESG_EXPORT ChunkAllocation {
         unsigned offset;           ///< Offset of the start of the block.
         unsigned size;             ///< Number of bytes in the block.
         unsigned nextRec;          ///< \brief Index of ChunkAllocation whose allocated memory follows the current block's memory.
         OwnerType *owner;          ///< Object that owns the allocated block. Null indicates free block.
         inline ChunkAllocation();  ///< Default constructor does nothing.
         inline ChunkAllocation(unsigned offset,unsigned size,unsigned nextRec,AttribReference *owner);  ///< Constructs structure by given values.
      };


      /** BlockAllocation represents single allocation element of memory
       *  inside BlockAllocationManager. It works over arrays of elements of constant size.
       *  The smallest allocation unit is one array element.
       *  The structure is used by AttribStorage and related classes for memory management purposes.
       */
      template<typename OwnerType>
      struct GESG_EXPORT BlockAllocation {
         unsigned startIndex;       ///< Index of the start of the block. The real offset is startIndex multiplied by the size of the underlaying array element.
         unsigned numElements;      ///< Number of elements in the block. The real size is numElements multiplied by the size of the underlaying array element.
         unsigned nextRec;          ///< \brief Index of BlockAllocation whose allocated memory follows the current block's memory.
         OwnerType *owner;          ///< Object that owns the allocated block. Null indicates free block.
         inline BlockAllocation();  ///< Default constructor does nothing.
         inline BlockAllocation(unsigned startIndex,unsigned numElements,unsigned nextRec,OwnerType *owner);  ///< Constructs structure by the given values.
      };


      template<typename ChunkOwnerType>
      class GESG_EXPORT ChunkAllocationManager : public std::vector<ChunkAllocation<ChunkOwnerType>> {
      public:
         unsigned _numBytesTotal;               ///< Total number of bytes. Sum of allocated and unallocated space.
         unsigned _numBytesAvailable;           ///< Number of bytes available for allocation.
         unsigned _numBytesAvailableAtTheEnd;   ///< Number of available bytes at the end of managed memory, e.g. size of the block of available bytes residing at the end.
         unsigned _firstByteAvailableAtTheEnd;  ///< Offset of the first available byte at the end of managed memory that is followed by available bytes only.
         unsigned _idOfBlockAtTheEnd;        ///< Id (index to std::vector\<ChunkAllocation\>) of the last allocated block at the end of managed memory.
         inline ChunkAllocationManager(unsigned capacity);
         inline ChunkAllocationManager(unsigned capacity,unsigned nullObjectSize);
         inline bool canAllocate(unsigned numBytes) const;
         unsigned alloc(unsigned numBytes,AttribReference &r);  // Allocates memory block. Returns id of the block or zero on failure.
         inline void free(unsigned id);  // Frees allocated block. Id must be valid allocated block. Zero id is allowed and safely ignored.
         void clear();
      };


      template<typename BlockOwnerType>
      class GESG_EXPORT BlockAllocationManager : public std::vector<BlockAllocation<BlockOwnerType>> {
      public:
         unsigned _numItemsTotal;               ///< Total number of items (allocated plus unallocated).
         unsigned _numItemsAvailable;           ///< Number of items available for allocation.
         unsigned _numItemsAvailableAtTheEnd;   ///< Number of available items at the end of managed memory, e.g. number of items in the block at the end.
         unsigned _firstItemAvailableAtTheEnd;  ///< Index of the first available item at the end of managed memory that is followed by available items only.
         unsigned _idOfBlockAtTheEnd;           ///< Id (index to std::vector\<BlockAllocation\>) of the last allocated block at the end of managed memory.
         inline BlockAllocationManager(unsigned capacity);
         inline BlockAllocationManager(unsigned capacity,unsigned nullObjectNumElements);
         inline bool canAllocate(unsigned numItems) const;
         unsigned alloc(unsigned numItems,BlockOwnerType &r);  // Allocates number of items. Returns id or zero on failure.
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
         bool alloc(unsigned *id);  ///< \brief Allocates one item and stores the item's id to the variable pointed by id parameter.
         bool alloc(unsigned numItems,unsigned* ids);  ///< \brief Allocates number of items.
         void free(unsigned id);  ///< Frees allocated item. Id must be valid.
         void free(unsigned* ids,unsigned numItems);  ///< Frees allocated items. Ids pointed by ids parameter must be valid.
         void clear();
      };


      // inline and template methods
      template<typename OwnerType> inline ChunkAllocation<OwnerType>::ChunkAllocation()  {}
      template<typename OwnerType> inline ChunkAllocation<OwnerType>::ChunkAllocation(unsigned offset,unsigned size,unsigned nextRec,AttribReference *owner)
      { this->offset=offset; this->size=size; this->nextRec=nextRec; this->owner=owner; }
      template<typename OwnerType> inline BlockAllocation<OwnerType>::BlockAllocation()  {}
      template<typename OwnerType> inline BlockAllocation<OwnerType>::BlockAllocation(unsigned startIndex,unsigned numElements,unsigned nextRec,OwnerType *owner)
      { this->startIndex=startIndex; this->numElements=numElements; this->nextRec=nextRec; this->owner=owner; }
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
      inline ItemAllocationManager::ItemAllocationManager(unsigned capacity)
         : std::vector<unsigned*>(capacity), _numItemsTotal(capacity), _numItemsAvailable(capacity),
           _numItemsAvailableAtTheEnd(capacity), _firstItemAvailableAtTheEnd(0)  {}
      template<typename OwnerType> inline bool ChunkAllocationManager<OwnerType>::canAllocate(unsigned numBytes) const
      { return _numBytesAvailableAtTheEnd>=numBytes; }
      template<typename OwnerType> inline bool BlockAllocationManager<OwnerType>::canAllocate(unsigned numItems) const
      { return _numItemsAvailableAtTheEnd>=numItems; }
      inline bool ItemAllocationManager::canAllocate(unsigned numItems) const
      { return _numItemsAvailableAtTheEnd>=numItems; }
      template<typename OwnerType> inline void ChunkAllocationManager<OwnerType>::free(unsigned id)  { std::vector<ChunkAllocation<OwnerType>>::operator[](id).owner=nullptr; }
      template<typename OwnerType> inline void BlockAllocationManager<OwnerType>::free(unsigned id)  { std::vector<BlockAllocation<OwnerType>>::operator[](id).owner=nullptr; }

      template<typename OwnerType>
      unsigned ChunkAllocationManager<OwnerType>::alloc(unsigned numBytes,AttribReference &r)
      {
         if(_numBytesAvailableAtTheEnd<numBytes)
            return 0;

         unsigned id=unsigned(std::vector<ChunkAllocation<OwnerType>>::size());
         std::vector<ChunkAllocation<OwnerType>>::emplace_back(_firstByteAvailableAtTheEnd,numBytes,0,&r);
         std::vector<ChunkAllocation<OwnerType>>::operator[](_idOfBlockAtTheEnd).nextRec=id;
         _numBytesAvailable-=numBytes;
         _numBytesAvailableAtTheEnd-=numBytes;
         _firstByteAvailableAtTheEnd+=numBytes;
         _idOfBlockAtTheEnd=id;
         return id;
      }

      template<typename OwnerType>
      unsigned BlockAllocationManager<OwnerType>::alloc(unsigned numItems,OwnerType &r)
      {
         if(_numItemsAvailableAtTheEnd<numItems)
            return 0;

         unsigned id=unsigned(std::vector<BlockAllocation<OwnerType>>::size());
         std::vector<BlockAllocation<OwnerType>>::emplace_back(_firstItemAvailableAtTheEnd,numItems,0,&r);
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

#endif /* GE_SG_ALLOCATION_MANAGERS_H */
