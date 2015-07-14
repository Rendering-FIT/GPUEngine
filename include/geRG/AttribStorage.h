// some includes need to be placed before GE_RG_ATTRIB_STORAGE_H define
// to prevent problems of circular includes
#include <geRG/AttribConfig.h>

#ifndef GE_RG_ATTRIB_STORAGE_H
#define GE_RG_ATTRIB_STORAGE_H

#include <memory>
#include <geRG/Export.h>
#include <geRG/AllocationManagers.h>

namespace ge
{
   namespace rg
   {
      class Mesh;


      /** \brief AttribStorage class maintains vertex attributes,
       *  indices and draw commands data of scene objects.
       */
      class GERG_EXPORT AttribStorage {
      protected:

         bool _privateFlag;
         BlockAllocationManager<Mesh> _vertexAllocationManager;  ///< Allocation manager of blocks of vertices.
         BlockAllocationManager<Mesh> _indexAllocationManager;   ///< Allocation manager of blocks of indices.
         AttribConfigRef _attribConfig;        ///< Configuration and formats of OpenGL attributes stored in this AttribStorage.
         RenderingContext* _renderingContext;

      public:

         AttribStorage() = delete;
         AttribStorage(const AttribConfigRef &config,unsigned numVertices,unsigned numIndices);
         virtual ~AttribStorage();

         virtual void bind() const = 0;

         virtual bool allocData(Mesh &mesh,int numVertices,int numIndices);
         virtual bool reallocData(Mesh &mesh,int numVertices,int numIndices,
                                  bool preserveContent=true);
         virtual void freeData(Mesh &mesh);

         virtual void uploadVertices(Mesh &mesh,const void*const *attribList,
                                     unsigned attribListSize,
                                     int numVertices,int fromIndex=0) = 0;
         virtual void uploadIndices(Mesh &mesh,const void *indices,
                                    int numIndices,int fromIndex=0) = 0;

         inline const BlockAllocation<Mesh>& vertexAllocationBlock(unsigned id) const; ///< Returns vertex data allocation block at index id.
         inline const BlockAllocation<Mesh>& indexAllocationBlock(unsigned id) const;  ///< Returns index data allocation block at index id.
         inline BlockAllocation<Mesh>& vertexAllocationBlock(unsigned id);  ///< Returns vertex data allocation block at index id. If modifying returned data, the care must be taken to not break internal data consistency.
         inline BlockAllocation<Mesh>& indexAllocationBlock(unsigned id);   ///< Returns index data allocation block at index id. If modifying returned data, the care must be taken to not break internal data consistency.

         inline BlockAllocationManager<Mesh>& vertexAllocationManager();
         inline BlockAllocationManager<Mesh>& indexAllocationManager();
         inline const BlockAllocationManager<Mesh>& vertexAllocationManager() const;
         inline const BlockAllocationManager<Mesh>& indexAllocationManager() const;

         inline const AttribConfigRef& attribConfig() const;
         inline RenderingContext* renderingContext() const;
         inline bool isPrivate() const;

         virtual void cancelAllAllocations();

         class Factory {
         public:
            virtual std::shared_ptr<AttribStorage> create(const AttribConfigRef &config,
                     unsigned numVertices,unsigned numIndices);
         };
         static inline std::shared_ptr<Factory>& factory();
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

namespace ge
{
   namespace rg
   {
      inline const BlockAllocation<Mesh>& AttribStorage::vertexAllocationBlock(unsigned id) const  { return _vertexAllocationManager[id]; }
      inline const BlockAllocation<Mesh>& AttribStorage::indexAllocationBlock(unsigned id) const  { return _indexAllocationManager[id]; }
      inline BlockAllocation<Mesh>& AttribStorage::vertexAllocationBlock(unsigned id)  { return _vertexAllocationManager[id]; }
      inline BlockAllocation<Mesh>& AttribStorage::indexAllocationBlock(unsigned id)  { return _indexAllocationManager[id]; }
      inline BlockAllocationManager<Mesh>& AttribStorage::vertexAllocationManager()  { return _vertexAllocationManager; }
      inline BlockAllocationManager<Mesh>& AttribStorage::indexAllocationManager()  { return _indexAllocationManager; }
      inline const BlockAllocationManager<Mesh>& AttribStorage::vertexAllocationManager() const  { return _vertexAllocationManager; }
      inline const BlockAllocationManager<Mesh>& AttribStorage::indexAllocationManager() const  { return _indexAllocationManager; }
      inline const AttribConfigRef& AttribStorage::attribConfig() const  { return _attribConfig; }
      inline RenderingContext* AttribStorage::renderingContext() const  { return _renderingContext; }
      inline bool AttribStorage::isPrivate() const  { return _privateFlag; }
      inline std::shared_ptr<AttribStorage::Factory>& AttribStorage::factory() { return _factory; }
      inline void AttribStorage::setFactory(std::shared_ptr<AttribStorage::Factory>& f) { _factory = f; }

   }
}

#endif // GE_RG_ATTRIB_STORAGE_H
