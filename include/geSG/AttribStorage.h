// some includes need to be placed before GE_SG_ATTRIB_STORAGE_H define
// to prevent problems of circular includes
#include <geSG/AttribConfig.h>

#ifndef GE_SG_ATTRIB_STORAGE_H
#define GE_SG_ATTRIB_STORAGE_H

#include <memory>
#include <vector>
#include <geSG/Export.h>

namespace ge
{
   namespace sg
   {
      class Array;
      class AttribReference;
      class Mesh;
      struct DrawCommandData;


      /** \brief AttribStorage class maintains vertex attributes,
       *  indices and draw commands data of scene objects.
       */
      class GE_EXPORT AttribStorage {
      public:

         /** AllocationBlock represents single allocation block of memory.
          *  It is used by AttribStorage internal Vertex Array Object (VAO) memory management
          *  of vertices and indices.
          */
         struct AllocationBlock {
            unsigned startIndex;     ///< Index of the start of the block. The real offset is startIndex multiplied by the size of the underlying array element.
            unsigned numElements;    ///< Number of elements in the block. The real size is numElements multiplied by the size of the underlying array element.
            AttribReference *owner;  ///< AttribReference that owns the allocated block. Null indicates free block.
            unsigned nextRec;        ///< \brief Index of AllocationBlock whose allocated memory follows the current block's memory.
            inline AllocationBlock(unsigned start,unsigned num, AttribReference *ref, unsigned next)
               : startIndex(start), numElements(num), owner(ref), nextRec(next) {}  ///< Constructs structure by given values.
         };

      protected:

         unsigned _numVerticesTotal;              ///< Total number of vertices that can be allocated in this AttribStorage.
         unsigned _numVerticesAvailable;          ///< Number of vertices that are available in this AttribStorage.
         unsigned _numVerticesAvailableAtTheEnd;  ///< Number of vertices that are available at the end of AttribStorage.
         unsigned _firstVertexAvailableAtTheEnd;  ///< Index of the first available vertex at the end of AttribStorage.
         unsigned _idOfVerticesBlockAtTheEnd;     ///< Id (index to _verticesDataAllocationMap) of the last allocated block at the end of AttribStorage.
         unsigned _numIndicesTotal;               ///< Total number of indices that can be allocated in this AttribStorage.
         unsigned _numIndicesAvailable;           ///< Number of indices that are available in this AttribStorage.
         unsigned _numIndicesAvailableAtTheEnd;   ///< Number of indices that are available at the end of AttribStorage.
         unsigned _firstIndexAvailableAtTheEnd;   ///< Index of the first available index at the end of AttribStorage.
         unsigned _idOfIndicesBlockAtTheEnd;      ///< Id (index to _indicesDataAllocationMap) of the last allocated block at the end of AttribStorage.
         unsigned _numDrawCommandsTotal;               ///< Total number of draw commands that can be allocated in this AttribStorage.
         unsigned _numDrawCommandsAvailable;           ///< Number of draw commands that are available in this AttribStorage.
         unsigned _numDrawCommandsAvailableAtTheEnd;   ///< Number of draw commands that are available at the end of AttribStorage.
         unsigned _firstDrawCommandAvailableAtTheEnd;  ///< Index of the first available draw command at the end of AttribStorage.
         unsigned _idOfDrawCommandBlockAtTheEnd;       ///< Id (index to _drawCommandAllocationMap) of the last allocated block at the end of AttribStorage.

         std::vector<AllocationBlock> _verticesDataAllocationMap;  ///< Allocation map of blocks of vertices.
         std::vector<AllocationBlock> _indicesDataAllocationMap;   ///< Allocation map of blocks of indices.
         std::vector<AllocationBlock> _drawCommandsAllocationMap;  ///< Allocation map of blocks of draw commands data.
         AttribConfigRef _attribConfig;        ///< Configuration and formats of OpenGL attributes stored in this AttribStorage.

      public:

         AttribStorage() = delete;
         AttribStorage(const AttribConfigRef &config,unsigned numVertices,
                       unsigned numIndices,unsigned numDrawCommands);
         virtual ~AttribStorage();

         virtual void bind() = 0;

         virtual bool allocData(AttribReference &r,int numVertices,
                                int numIndices,int numDrawCommands);
         virtual bool reallocData(AttribReference &r,int numVertices,int numIndices,
                                  int numDrawCommands,bool preserveContent=true);
         virtual void freeData(AttribReference &r);

         virtual void uploadVertexData(AttribReference &r,const std::vector<Array>& attribs,
                                       int fromIndex=0,int numVertices=-1) = 0;
         virtual void uploadIndices(AttribReference &r,const Array& indices,
                                    int fromIndex=0,int numIndices=-1) = 0;
         virtual void uploadDrawCommands(AttribReference &r,const DrawCommandData *drawCommands,
                                         int fromIndex,int numDrawCommands) = 0;
         inline void uploadDrawCommands(AttribReference &r,const DrawCommandData *drawCommands,
                                        int numDrawCommands);
         inline void uploadDrawCommands(AttribReference &r,
                                        const std::vector<DrawCommandData> &drawCommands,
                                        int fromIndex);

         inline const AllocationBlock& getVerticesAllocationBlock(unsigned id) const;
         inline const AllocationBlock& getIndicesAllocationBlock(unsigned id) const;
         inline const AllocationBlock& getDrawCommandsAllocationBlock(unsigned id) const;

         inline const AttribConfigRef& getAttribConfig() const;

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
         inline unsigned getNumDrawCommandsTotal() const;
         inline unsigned getNumDrawCommandsAvailable() const;
         inline unsigned getNumDrawCommandsAvailableAtTheEnd() const;
         inline unsigned getFirstDrawCommandAvailableAtTheEnd() const;
         inline unsigned getIdOfDrawCommandBlockAtTheEnd() const;
         inline std::vector<AllocationBlock>& getVerticesDataAllocationMap();
         inline std::vector<AllocationBlock>& getIndicesDataAllocationMap();
         inline std::vector<AllocationBlock>& getDrawCommandsAllocationMap();
         inline const std::vector<AllocationBlock>& getVerticesDataAllocationMap() const;
         inline const std::vector<AllocationBlock>& getIndicesDataAllocationMap() const;
         inline const std::vector<AllocationBlock>& getDrawCommandsAllocationMap() const;

         virtual void cancelAllAllocations();

         class Factory {
         public:
            virtual std::shared_ptr<AttribStorage> create(const AttribConfigRef &config,
                     unsigned numVertices,unsigned numIndices,unsigned numDrawCommands);
         };
         static inline std::shared_ptr<Factory>& getFactory();
         static inline void setFactory(std::shared_ptr<Factory>& f);

      protected:
         static std::shared_ptr<Factory> _factory;
      };

   }
}



// inline and template methods
//
// note: they need their own includes that can not be placed on the beginning of this file
//       as there are circular header includes and the classes need to be defined before
//       inline methods to avoid incomplete type compiler error

#include <geSG/DrawCommandData.h>

namespace ge
{
   namespace sg
   {
      inline void AttribStorage::uploadDrawCommands(AttribReference &r,const DrawCommandData *drawCommands,int numDrawCommands)
      { uploadDrawCommands(r,drawCommands,0,numDrawCommands); }
      inline void AttribStorage::uploadDrawCommands(AttribReference &r,const std::vector<DrawCommandData> &drawCommands,int fromIndex)
      { uploadDrawCommands(r,drawCommands.data(),drawCommands.size(),fromIndex); }
      inline const AttribStorage::AllocationBlock& AttribStorage::getVerticesAllocationBlock(unsigned id) const  { return _verticesDataAllocationMap[id]; }
      inline const AttribStorage::AllocationBlock& AttribStorage::getIndicesAllocationBlock(unsigned id) const  { return _indicesDataAllocationMap[id]; }
      inline const AttribStorage::AllocationBlock& AttribStorage::getDrawCommandsAllocationBlock(unsigned id) const  { return _drawCommandsAllocationMap[id]; }
      inline const AttribConfigRef& AttribStorage::getAttribConfig() const  { return _attribConfig; }
      inline unsigned AttribStorage::getNumVerticesTotal() const  { return _numVerticesTotal; }
      inline unsigned AttribStorage::getNumVerticesAvailable() const  { return _numVerticesAvailable; }
      inline unsigned AttribStorage::getNumVerticesAvailableAtTheEnd() const  { return _numVerticesAvailableAtTheEnd; }
      inline unsigned AttribStorage::getFirstVertexAvailableAtTheEnd() const  { return _firstVertexAvailableAtTheEnd; }
      inline unsigned AttribStorage::getIdOfVerticesBlockAtTheEnd() const  { return _idOfVerticesBlockAtTheEnd; }
      inline unsigned AttribStorage::getNumIndicesTotal() const  { return _numIndicesTotal; }
      inline unsigned AttribStorage::getNumIndicesAvailable() const  { return _numIndicesAvailable; }
      inline unsigned AttribStorage::getNumIndicesAvailableAtTheEnd() const  { return _numIndicesAvailableAtTheEnd; }
      inline unsigned AttribStorage::getFirstIndexAvailableAtTheEnd() const  { return _firstIndexAvailableAtTheEnd; }
      inline unsigned AttribStorage::getIdOfIndicesBlockAtTheEnd() const  { return _idOfIndicesBlockAtTheEnd; }
      inline unsigned AttribStorage::getNumDrawCommandsTotal() const  { return _numDrawCommandsTotal; }
      inline unsigned AttribStorage::getNumDrawCommandsAvailable() const  { return _numDrawCommandsAvailable; }
      inline unsigned AttribStorage::getNumDrawCommandsAvailableAtTheEnd() const  { return _numDrawCommandsAvailableAtTheEnd; }
      inline unsigned AttribStorage::getFirstDrawCommandAvailableAtTheEnd() const  { return _firstDrawCommandAvailableAtTheEnd; }
      inline unsigned AttribStorage::getIdOfDrawCommandBlockAtTheEnd() const  { return _idOfDrawCommandBlockAtTheEnd; }
      inline std::vector<AttribStorage::AllocationBlock>& AttribStorage::getVerticesDataAllocationMap()  { return _verticesDataAllocationMap; }
      inline std::vector<AttribStorage::AllocationBlock>& AttribStorage::getIndicesDataAllocationMap()  { return _indicesDataAllocationMap; }
      inline std::vector<AttribStorage::AllocationBlock>& AttribStorage::getDrawCommandsAllocationMap()  { return _drawCommandsAllocationMap; }
      inline const std::vector<AttribStorage::AllocationBlock>& AttribStorage::getVerticesDataAllocationMap() const  { return _verticesDataAllocationMap; }
      inline const std::vector<AttribStorage::AllocationBlock>& AttribStorage::getIndicesDataAllocationMap() const  { return _indicesDataAllocationMap; }
      inline const std::vector<AttribStorage::AllocationBlock>& AttribStorage::getDrawCommandsAllocationMap() const  { return _drawCommandsAllocationMap; }
      inline std::shared_ptr<AttribStorage::Factory>& AttribStorage::getFactory() { return _factory; }
      inline void AttribStorage::setFactory(std::shared_ptr<AttribStorage::Factory>& f) { _factory = f; }

   }
}

#endif // GE_SG_ATTRIB_STORAGE_H
