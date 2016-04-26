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
      struct RenderingCommandData;


      /** \brief AttribStorage class maintains vertex attributes
       *  and indices of scene geometry.
       */
      class GERG_EXPORT AttribStorage {
      protected:

         bool _privateFlag;
         ArrayAllocationManager<Mesh> _vertexAllocationManager;  ///< Allocation manager for arrays of vertices.
         ArrayAllocationManager<Mesh> _indexAllocationManager;   ///< Allocation manager for arrays of indices.
         AttribConfigRef _attribConfig;        ///< Configuration and formats of OpenGL attributes stored in this AttribStorage.
         RenderingContext* _renderingContext;

      public:

         AttribStorage() = delete;
         AttribStorage(const AttribConfigRef &config,unsigned numVertices,unsigned numIndices);
         virtual ~AttribStorage();

         virtual void bind() const = 0;

         virtual bool allocData(Mesh &mesh,unsigned numVertices,unsigned numIndices);
         virtual bool reallocData(Mesh &mesh,unsigned numVertices,unsigned numIndices,
                                  bool preserveContent=true);
         virtual void freeData(Mesh &mesh);

         virtual void uploadVertices(Mesh &mesh,const void*const *attribList,
                                     unsigned attribListSize,
                                     unsigned numVertices,unsigned fromIndex=0) = 0;
         virtual void uploadIndices(Mesh &mesh,const void *indices,
                                    unsigned numIndices,unsigned fromIndex=0) = 0;

         inline const ArrayAllocation<Mesh>& vertexArrayAllocation(unsigned id) const; ///< Returns vertex array allocation for particular id.
         inline const ArrayAllocation<Mesh>& indexArrayAllocation(unsigned id) const;  ///< Returns index array allocation for particular id.
         inline ArrayAllocation<Mesh>& vertexArrayAllocation(unsigned id);  ///< Returns vertex array allocation for particular id. When modifying returned data, the care must be taken to not break internal data consistency.
         inline ArrayAllocation<Mesh>& indexArrayAllocation(unsigned id);   ///< Returns index array allocation for particular id. When modifying returned data, the care must be taken to not break internal data consistency.

         inline ArrayAllocationManager<Mesh>& vertexAllocationManager();
         inline ArrayAllocationManager<Mesh>& indexAllocationManager();
         inline const ArrayAllocationManager<Mesh>& vertexAllocationManager() const;
         inline const ArrayAllocationManager<Mesh>& indexAllocationManager() const;

         inline const AttribConfigRef& attribConfig() const;
         inline RenderingContext* renderingContext() const;
         inline bool isPrivate() const;

         virtual void render(const std::vector<RenderingCommandData>& renderingDataList);
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
      inline const ArrayAllocation<Mesh>& AttribStorage::vertexArrayAllocation(unsigned id) const  { return _vertexAllocationManager[id]; }
      inline const ArrayAllocation<Mesh>& AttribStorage::indexArrayAllocation(unsigned id) const  { return _indexAllocationManager[id]; }
      inline ArrayAllocation<Mesh>& AttribStorage::vertexArrayAllocation(unsigned id)  { return _vertexAllocationManager[id]; }
      inline ArrayAllocation<Mesh>& AttribStorage::indexArrayAllocation(unsigned id)  { return _indexAllocationManager[id]; }
      inline ArrayAllocationManager<Mesh>& AttribStorage::vertexAllocationManager()  { return _vertexAllocationManager; }
      inline ArrayAllocationManager<Mesh>& AttribStorage::indexAllocationManager()  { return _indexAllocationManager; }
      inline const ArrayAllocationManager<Mesh>& AttribStorage::vertexAllocationManager() const  { return _vertexAllocationManager; }
      inline const ArrayAllocationManager<Mesh>& AttribStorage::indexAllocationManager() const  { return _indexAllocationManager; }
      inline const AttribConfigRef& AttribStorage::attribConfig() const  { return _attribConfig; }
      inline RenderingContext* AttribStorage::renderingContext() const  { return _renderingContext; }
      inline bool AttribStorage::isPrivate() const  { return _privateFlag; }
      inline std::shared_ptr<AttribStorage::Factory>& AttribStorage::factory() { return _factory; }
      inline void AttribStorage::setFactory(std::shared_ptr<AttribStorage::Factory>& f) { _factory = f; }

   }
}

#endif // GE_RG_ATTRIB_STORAGE_H
