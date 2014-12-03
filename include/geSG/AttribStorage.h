#ifndef GE_SG_ATTRIBS_STORAGE_H
#define GE_SG_ATTRIBS_STORAGE_H

#include <memory>
#include <vector>
#include <geSG/Export.h>
#include <geSG/AttribsConfig.h>

namespace ge
{
   namespace sg
   {
      class Array;
      class AttribsReference;
      class Mesh;

      /** AttribsStorage class maintains vertex attributes of many scene objects
       *  in a single OpenGL vertex array object (VAO).
       *
       *  It is benefical to store all the vertex attributes in few AttribsStorage
       *  objects because they can be drawn by a single draw command and handled
       *  together by various scene processing algorithms instead of processing
       *  many small VAOs separately, introducing smaller of bigger amount of overhead.
       *
       *  Each AttribsStorage object can store vertex attributes of the same format only.
       *  For instance, vertex attributes composed of coordinates and colors are
       *  stored in different AttribsStorage than vertex attributes composed of
       *  coordinates, normals and texture coordinates. Format of a particular
       *  attribute must be the same too. For instance, colors stored as RGBA8
       *  are stored in different AttribsStorage than colors stored as three floats.
       *
       *  AttribsStorage is expected to be used with one graphics context only and
       *  that context is expected to be current when working with the AttribsStorage.
       *  The easiest rule is that whenever you are processing your scene graph
       *  and perform any changes that may change the scene geometry, including adding
       *  and removing objects, have your graphics context current.
       *
       *  Constructor require graphics context current to allocate internal VAO
       *  and other OpenGL objects. Destructor requires it to delete these OpenGL objects.
       *  However, there is a difficulty as the graphics context may be destroyed because of
       *  various reasons, including closing of the window or power-saving reasons
       *  on mobile devices. In such cases, the user is expected to call
       *  AttribsManager::contextLost() before any further scene graph processing.
       *  AttribsManager::contextLost() will forward the call to all AttribsStorages,
       *  calling their contextLost(). This will clear all internal structures
       *  as if no data would be uploaded to graphics context yet. This could be performed
       *  even without active graphics context, after it was lost or destroyed.
       *  Depending on user choose, he might decide to recreate the graphics
       *  context and reinitialize attribute data, for instance, by reloading
       *  model files, or he might safely start to tear down the application that
       *  is in consistent state after calling AttribsManager::contextLost().
       *
       *  For more details, which methods can be called without active graphics context
       *  refer to the documentation to each of the object's methods.
       *
       *  \sa AttribsManager, AttribsReference, Mesh::getAttribsConfig(), Mesh::getAttribsConfigId()
       */
      class GE_EXPORT AttribsStorage {
      protected:

         unsigned _numVerticesTotal;              ///< Total number of vertices that can be allocated in this AttribsStorage.
         unsigned _numVerticesAvailable;          ///< Number of vertices that are available in this AttribsStorage.
         unsigned _numVerticesAvailableAtTheEnd;  ///< Number of vertices that are available at the end of AttribsStorage.
         unsigned _firstVertexAvailableAtTheEnd;  ///< Index of the first available vertex at the end of AttribsStorage.
         unsigned _idOfVerticesBlockAtTheEnd;     ///< Id (index to _verticesDataAllocationMap) of the last allocated block at the end of AttribsStorage.
         unsigned _numIndicesTotal;               ///< Total number of indices that can be allocated in this AttribsStorage.
         unsigned _numIndicesAvailable;           ///< Number of indices that are available in this AttribsStorage.
         unsigned _numIndicesAvailableAtTheEnd;   ///< Number of indices that are available at the end of AttribsStorage.
         unsigned _firstIndexAvailableAtTheEnd;   ///< Index of the first available index at the end of AttribsStorage.
         unsigned _idOfIndicesBlockAtTheEnd;      ///< Id (index to _indicesDataAllocationMap) of the last allocated block at the end of AttribsStorage.

         /** AllocationBlock represents single allocation block of memory.
          *  It is used by AttribsStorage internal Vertex Array Object (VAO) memory management
          *  of vertices and indices.
          */
         struct AllocationBlock {
            unsigned startIndex;   ///< Index of the start of the block. The real offset is startIndex multiplied by the size of the underlying array element.
            unsigned numElements;  ///< Number of elements in the block. The real size is numElements multiplied by the size of the underlying array element.
            AttribsReference *owner;  ///< AttribsReference that owns the allocated block. Null indicates free block.
            unsigned nextRec;      ///< \brief Index of AllocationBlock whose allocated memory follows the current block's memory.
            inline AllocationBlock(unsigned start,unsigned num, AttribsReference *ref, unsigned next)
               : startIndex(start), numElements(num), owner(ref), nextRec(next) {}  ///< Constructs structure by given values.
         };
         std::vector<AllocationBlock> _verticesDataAllocationMap;  ///< Allocation map of blocks of vertices.
         std::vector<AllocationBlock> _indicesDataAllocationMap;   ///< Allocation map of blocks of indices.
         AttribsConfig _attribsConfig;      ///< Configuration and formats of OpenGL attributes stored in this AttribsStorage.

      public:

         AttribsStorage() = delete;
         AttribsStorage(const AttribsConfig &config,unsigned numVertices,unsigned numIndices);
         virtual ~AttribsStorage();

         virtual void bind() = 0;

         virtual bool allocData(AttribsReference &r,int numVertices,int numIndices);
         virtual bool reallocData(AttribsReference &r,int numVertices,int numIndices,
                                  bool preserveContent=true);
         virtual void freeData(AttribsReference &r);
         virtual void uploadVertexData(AttribsReference &r,const std::vector<Array>& attribs,
                                       int fromIndex=0,int numVertices=-1) = 0;
         virtual void uploadVertexData(AttribsReference &r,Mesh* mesh,
                                       int fromIndex=0,int numVertices=-1) = 0;
         virtual int uploadVertexData(AttribsReference &r,Mesh* mesh,
                                      unsigned &currentPosition,int bytesToUpload) = 0;
         virtual void uploadIndicesData(AttribsReference &r,const Array& indices,
                                        int fromIndex=0,int numVertices=-1) = 0;
         virtual void uploadIndicesData(AttribsReference &r,Mesh* mesh,
                                        int fromIndex=0,int numVertices=-1) = 0;
         virtual int uploadIndicesData(AttribsReference &r,Mesh* mesh,
                                       unsigned &currentPosition,int bytesToUpload) = 0;

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
            virtual std::shared_ptr<AttribsStorage> create(const AttribsConfig &config,
                                                           unsigned numVertices,unsigned numIndices) = 0;
         };
         static inline std::shared_ptr<Factory>& getFactory();
         static inline void setFactory(std::shared_ptr<Factory>& f);

      protected:
         static std::shared_ptr<Factory> _factory;
      };



      // inline and template methods
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

#endif // GE_SG_ATTRIBS_STORAGE_H
