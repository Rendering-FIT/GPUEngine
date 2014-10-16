#ifndef GE_SG_ATTRIB_OBJECT_H
#define GE_SG_ATTRIB_OBJECT_H

#include <memory>
#include <vector>

namespace ge
{
   namespace sg
   {
      class AttribsDataReference;
      class Mesh;

      class AttribsStorage {
      protected:

         unsigned _mode;

         unsigned _vertexDataSize;
         unsigned _numVerticesTotal;
         unsigned _numVerticesAvailable;
         unsigned _numVerticesAvailableAtTheEnd;
         unsigned _firstVertexAvailableAtTheEnd;
         unsigned _idOfVerticesBlockAtTheEnd;
         unsigned _numIndicesTotal;
         unsigned _numIndicesAvailable;
         unsigned _numIndicesAvailableAtTheEnd;
         unsigned _firstIndexAvailableAtTheEnd;
         unsigned _idOfIndicesBlockAtTheEnd;

         struct AllocationBlock {
            unsigned startIndex;  //< Start of block. Real offset is the buffer is startIndex*sizeof(Element).
            unsigned numElements; //< Number of elements in the block. Real size is numElements*sizeof(Element).
            AttribsDataReference *owner; //< AttribsDataReference that owns the allocated block. Null indicates free block.
            unsigned nextRec;     //< Index of AllocationBlock whose allocated memory follows the current block's
                                  //< memory. Order of AllocationBlocks stored in std::vector<AllocationBlock>
                                  //< often does not correspond with the order of their memory placements.
                                  //< nextRec is index to the std::vector<AllocationBlock> and points
                                  //< to the AllocationBlock whose allocated memory follows the current one.
            inline AllocationBlock(unsigned start,unsigned num, AttribsDataReference *ref, unsigned next)
               : startIndex(start), numElements(num), owner(ref), nextRec(next) {}
         };
         std::vector<AllocationBlock> _verticesDataAllocationMap;
         std::vector<AllocationBlock> _indicesDataAllocationMap;

      public:

         AttribsStorage();
         virtual ~AttribsStorage();

         virtual bool allocData(AttribsDataReference *r,int numVertices,int numIndices);
         virtual bool reallocData(AttribsDataReference *r,int numVertices,int numIndices,bool preserveContent=true);
         virtual void freeData(AttribsDataReference *r);
         virtual void uploadVertexData(AttribsDataReference *r,Mesh* mesh,int fromIndex=0,int numVertices=-1);
         virtual int uploadVertexData(AttribsDataReference *r,Mesh* mesh,unsigned &currentPosition,int bytesToUpload);
         virtual void uploadIndicesData(AttribsDataReference *r,Mesh* mesh,int fromIndex=0,int numVertices=-1);
         virtual int uploadIndicesData(AttribsDataReference *r,Mesh* mesh,unsigned &currentPosition,int bytesToUpload);

         inline unsigned getVertexDataSize() const;
         inline unsigned getNumVerticesTotal() const;
         inline unsigned getNumVerticesAvailable() const;
         inline unsigned getNumVerticesAvailableAtTheEnd() const;
         inline unsigned getFirstVertexAvailableAtTheEnd() const;
         inline unsigned getIdOfVerticesBlockAtTheEnd() const;
         inline unsigned getNumIndicesTotal() const;
         inline unsigned getNumIndicesAvailable() const;
         inline unsigned getNumIndicesAvailableAtTheEnd() const;
         inline unsigned getFirstIndexAvailableAtTheEnd() const;
         inline unsigned getIdOfIndicesBlockAtTheEnd() const;
         inline std::vector<AllocationBlock>& getVerticesDataAllocationMap();
         inline std::vector<AllocationBlock>& getIndicesDataAllocationMap();
         inline const std::vector<AllocationBlock>& getVerticesDataAllocationMap() const;
         inline const std::vector<AllocationBlock>& getIndicesDataAllocationMap() const;

         class Factory {
         public:
            virtual AttribsStorage* create() = 0;
         };
         static inline std::shared_ptr<Factory>& getFactory();
         static inline void setFactory(std::shared_ptr<Factory>& f);

      protected:
         static std::shared_ptr<Factory> _factory;
      };



      // inline and template methods
      inline unsigned AttribsStorage::getVertexDataSize() const  { return _vertexDataSize; }
      inline unsigned AttribsStorage::getNumVerticesTotal() const  { return _numVerticesTotal; }
      inline unsigned AttribsStorage::getNumVerticesAvailable() const  { return _numVerticesAvailable; }
      inline unsigned AttribsStorage::getNumVerticesAvailableAtTheEnd() const  { return _numVerticesAvailableAtTheEnd; }
      inline unsigned AttribsStorage::getFirstVertexAvailableAtTheEnd() const  { return _firstVertexAvailableAtTheEnd; }
      inline unsigned AttribsStorage::getIdOfVerticesBlockAtTheEnd() const  { return _idOfVerticesBlockAtTheEnd; }
      inline unsigned AttribsStorage::getNumIndicesTotal() const  { return _numIndicesTotal; }
      inline unsigned AttribsStorage::getNumIndicesAvailable() const  { return _numIndicesAvailable; }
      inline unsigned AttribsStorage::getNumIndicesAvailableAtTheEnd() const  { return _numIndicesAvailableAtTheEnd; }
      inline unsigned AttribsStorage::getFirstIndexAvailableAtTheEnd() const  { return _firstIndexAvailableAtTheEnd; }
      inline unsigned AttribsStorage::getIdOfIndicesBlockAtTheEnd() const  { return _idOfIndicesBlockAtTheEnd; }
      inline std::vector<AttribsStorage::AllocationBlock>& AttribsStorage::getVerticesDataAllocationMap()  { return _verticesDataAllocationMap; }
      inline std::vector<AttribsStorage::AllocationBlock>& AttribsStorage::getIndicesDataAllocationMap()  { return _indicesDataAllocationMap; }
      inline const std::vector<AttribsStorage::AllocationBlock>& AttribsStorage::getVerticesDataAllocationMap() const  { return _verticesDataAllocationMap; }
      inline const std::vector<AttribsStorage::AllocationBlock>& AttribsStorage::getIndicesDataAllocationMap() const  { return _indicesDataAllocationMap; }
      inline std::shared_ptr<AttribsStorage::Factory>& AttribsStorage::getFactory() { return _factory; }
      inline void AttribsStorage::setFactory(std::shared_ptr<AttribsStorage::Factory>& f) { _factory = f; }

   }
}

#endif // GE_SG_ATTRIB_OBJECT_H
