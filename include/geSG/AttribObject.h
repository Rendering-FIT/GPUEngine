#ifndef GE_SG_ATTRIB_OBJECT_H
#define GE_SG_ATTRIB_OBJECT_H

#include <memory>
#include <vector>

namespace ge
{
   namespace sg
   {
      class AttribDataReference;
      class Mesh;

      class AttribObject {
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
            AttribDataReference *owner; //< AttribDataReference that owns the allocated block. Null indicates free block.
            unsigned nextRec;     //< Index of AllocationBlock whose allocated memory follows the current block's
                                  //< memory. Order of AllocationBlocks stored in std::vector<AllocationBlock>
                                  //< often does not correspond with the order of their memory placements.
                                  //< nextRec is index to the std::vector<AllocationBlock> and points
                                  //< to the AllocationBlock whose allocated memory follows the current one.
            inline AllocationBlock(unsigned start,unsigned num, AttribDataReference *ref, unsigned next)
               : startIndex(start), numElements(num), owner(ref), nextRec(next) {}
         };
         std::vector<AllocationBlock> _verticesDataAllocationMap;
         std::vector<AllocationBlock> _indicesDataAllocationMap;

      public:

         AttribObject();
         virtual ~AttribObject();

         virtual bool allocData(AttribDataReference *r,int numVertices,int numIndices);
         virtual bool reallocData(AttribDataReference *r,int numVertices,int numIndices,bool preserveContent=true);
         virtual void freeData(AttribDataReference *r);
         virtual void uploadVertexData(AttribDataReference *r,Mesh* mesh,int fromIndex=0,int numVertices=-1);
         virtual int uploadVertexData(AttribDataReference *r,Mesh* mesh,unsigned &currentPosition,int bytesToUpload);
         virtual void uploadIndicesData(AttribDataReference *r,Mesh* mesh,int fromIndex=0,int numVertices=-1);
         virtual int uploadIndicesData(AttribDataReference *r,Mesh* mesh,unsigned &currentPosition,int bytesToUpload);

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
            virtual AttribObject* create() = 0;
         };
         static inline std::shared_ptr<Factory>& getFactory();
         static inline void setFactory(std::shared_ptr<Factory>& f);

      protected:
         static std::shared_ptr<Factory> _factory;
      };



      // inline and template methods
      inline unsigned AttribObject::getVertexDataSize() const  { return _vertexDataSize; }
      inline unsigned AttribObject::getNumVerticesTotal() const  { return _numVerticesTotal; }
      inline unsigned AttribObject::getNumVerticesAvailable() const  { return _numVerticesAvailable; }
      inline unsigned AttribObject::getNumVerticesAvailableAtTheEnd() const  { return _numVerticesAvailableAtTheEnd; }
      inline unsigned AttribObject::getFirstVertexAvailableAtTheEnd() const  { return _firstVertexAvailableAtTheEnd; }
      inline unsigned AttribObject::getIdOfVerticesBlockAtTheEnd() const  { return _idOfVerticesBlockAtTheEnd; }
      inline unsigned AttribObject::getNumIndicesTotal() const  { return _numIndicesTotal; }
      inline unsigned AttribObject::getNumIndicesAvailable() const  { return _numIndicesAvailable; }
      inline unsigned AttribObject::getNumIndicesAvailableAtTheEnd() const  { return _numIndicesAvailableAtTheEnd; }
      inline unsigned AttribObject::getFirstIndexAvailableAtTheEnd() const  { return _firstIndexAvailableAtTheEnd; }
      inline unsigned AttribObject::getIdOfIndicesBlockAtTheEnd() const  { return _idOfIndicesBlockAtTheEnd; }
      inline std::vector<AttribObject::AllocationBlock>& AttribObject::getVerticesDataAllocationMap()  { return _verticesDataAllocationMap; }
      inline std::vector<AttribObject::AllocationBlock>& AttribObject::getIndicesDataAllocationMap()  { return _indicesDataAllocationMap; }
      inline const std::vector<AttribObject::AllocationBlock>& AttribObject::getVerticesDataAllocationMap() const  { return _verticesDataAllocationMap; }
      inline const std::vector<AttribObject::AllocationBlock>& AttribObject::getIndicesDataAllocationMap() const  { return _indicesDataAllocationMap; }
      inline std::shared_ptr<AttribObject::Factory>& AttribObject::getFactory() { return _factory; }
      inline void AttribObject::setFactory(std::shared_ptr<AttribObject::Factory>& f) { _factory = f; }

   }
}

#endif // GE_SG_ATTRIB_OBJECT_H
