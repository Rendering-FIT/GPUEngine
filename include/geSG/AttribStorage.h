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

      /** AttribStorage class maintains vertex attributes of many scene objects
       *  in a single OpenGL vertex array object (VAO).
       *
       *  It is benefical to store all the vertex attributes in few AttribStorage
       *  objects because they can be drawn by a single draw command and handled
       *  together by various scene processing algorithms instead of processing
       *  many small VAOs separately, introducing smaller of bigger amount of overhead.
       *
       *  Each AttribStorage object can store vertex attributes of the same format only.
       *  For instance, vertex attributes composed of coordinates and colors are
       *  stored in different AttribStorage than vertex attributes composed of
       *  coordinates, normals and texture coordinates. Format of a particular
       *  attribute must be the same too. For instance, colors stored as RGBA8
       *  are stored in different AttribStorage than colors stored as three floats.
       *
       *  AttribStorage is expected to be used with one graphics context only and
       *  that context is expected to be current when working with the AttribStorage.
       *  The easiest rule is that whenever you are processing your scene graph
       *  and perform any changes that may change the scene geometry, including adding
       *  and removing objects, have your graphics context current.
       *
       *  Constructor require graphics context current to allocate internal VAO
       *  and other OpenGL objects. Destructor requires it to delete these OpenGL objects.
       *  However, there is a difficulty as the graphics context may be destroyed because of
       *  various reasons, including closing of the window or power-saving reasons
       *  on mobile devices. In such cases, the user is expected to call
       *  AttribManager::contextLost() before any further scene graph processing.
       *  AttribManager::contextLost() will forward the call to all AttribStorages,
       *  calling their contextLost(). This will clear all internal structures
       *  as if no data would be uploaded to graphics context yet. This could be performed
       *  even without active graphics context, after it was lost or destroyed.
       *  Depending on user choose, he might decide to recreate the graphics
       *  context and reinitialize attribute data, for instance, by reloading
       *  model files, or he might safely start to tear down the application that
       *  is in consistent state after calling AttribManager::contextLost().
       *
       *  For more details, which methods can be called without active graphics context
       *  refer to the documentation to each of the object's methods.
       *
       *  \sa AttribManager, AttribReference, Mesh::getAttribConfig()
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

         std::vector<AllocationBlock> _verticesDataAllocationMap;  ///< Allocation map of blocks of vertices.
         std::vector<AllocationBlock> _indicesDataAllocationMap;   ///< Allocation map of blocks of indices.
         AttribConfigRef _attribConfig;        ///< Configuration and formats of OpenGL attributes stored in this AttribStorage.

      public:

         AttribStorage() = delete;
         AttribStorage(const AttribConfigRef &config,unsigned numVertices,unsigned numIndices);
         virtual ~AttribStorage();

         virtual void bind() = 0;

         virtual bool allocData(AttribReference &r,int numVertices,int numIndices);
         virtual bool reallocData(AttribReference &r,int numVertices,int numIndices,
                                  bool preserveContent=true);
         virtual void freeData(AttribReference &r);

         virtual void uploadVertexData(AttribReference &r,const std::vector<Array>& attribs,
                                       int fromIndex=0,int numVertices=-1) = 0;
         virtual void uploadIndices(AttribReference &r,const Array& indices,
                                    int fromIndex=0,int numIndices=-1) = 0;

         inline const AllocationBlock& getVerticesAllocationBlock(unsigned id) const;
         inline const AllocationBlock& getIndicesAllocationBlock(unsigned id) const;

         inline const AttribConfigRef& getAttribConfig() const;

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

         virtual void cancelAllAllocations();

         class Factory {
         public:
            virtual std::shared_ptr<AttribStorage> create(const AttribConfigRef &config,
                                                          unsigned numVertices,unsigned numIndices);
         };
         static inline std::shared_ptr<Factory>& getFactory();
         static inline void setFactory(std::shared_ptr<Factory>& f);

      protected:
         static std::shared_ptr<Factory> _factory;
      };



      // inline and template methods
      inline const AttribStorage::AllocationBlock& AttribStorage::getVerticesAllocationBlock(unsigned id) const  { return _verticesDataAllocationMap[id]; }
      inline const AttribStorage::AllocationBlock& AttribStorage::getIndicesAllocationBlock(unsigned id) const  { return _indicesDataAllocationMap[id]; }
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
      inline std::vector<AttribStorage::AllocationBlock>& AttribStorage::getVerticesDataAllocationMap()  { return _verticesDataAllocationMap; }
      inline std::vector<AttribStorage::AllocationBlock>& AttribStorage::getIndicesDataAllocationMap()  { return _indicesDataAllocationMap; }
      inline const std::vector<AttribStorage::AllocationBlock>& AttribStorage::getVerticesDataAllocationMap() const  { return _verticesDataAllocationMap; }
      inline const std::vector<AttribStorage::AllocationBlock>& AttribStorage::getIndicesDataAllocationMap() const  { return _indicesDataAllocationMap; }
      inline std::shared_ptr<AttribStorage::Factory>& AttribStorage::getFactory() { return _factory; }
      inline void AttribStorage::setFactory(std::shared_ptr<AttribStorage::Factory>& f) { _factory = f; }

   }
}

#endif // GE_SG_ATTRIB_STORAGE_H
