#ifndef GE_SG_ATTRIBS_MANAGER_H
#define GE_SG_ATTRIBS_MANAGER_H

#include <map>
#include <memory>
#include <geSG/AttribsStorage.h>
#include <geSG/Export.h>

namespace ge
{
   namespace sg
   {
      class AttribsReference;
      class Mesh;

      class GE_EXPORT AttribsManager {
      public:

         typedef std::multimap<uint16_t,std::unique_ptr<AttribsStorage>> AttribsStorageMultiMap;

      protected:

         AttribsStorageMultiMap _attribsStorageMultiMap;

      public:

         inline AttribsManager() {}
         virtual ~AttribsManager();

         inline std::pair<AttribsStorageMultiMap::iterator,AttribsStorageMultiMap::iterator> getAttribsStorages(unsigned attribConfigID);
         inline AttribsStorageMultiMap& getAttribsStorages();
         inline const AttribsStorageMultiMap& getAttribsStorages() const;

         virtual bool allocData(AttribsReference &r,int numVertices,int numIndices,uint16_t attribConfigId);
         virtual bool reallocData(AttribsReference &r,int numVertices,int numIndices,bool preserveContent=true);
         virtual void freeData(AttribsReference &r);
         virtual void uploadVertexData(AttribsReference &r,Mesh *mesh,int fromIndex=0,int numVertices=-1);
         virtual int uploadVertexData(AttribsReference &r,Mesh *mesh,unsigned &currentPosition,int bytesToUpload);
         virtual void uploadIndicesData(AttribsReference &r,Mesh *mesh,int fromIndex=0,int numIndices=-1);
         virtual int uploadIndicesData(AttribsReference &r,Mesh *mesh,unsigned &currentPosition,int bytesToUpload);

         static inline std::shared_ptr<AttribsManager>& instance();
         static void setInstance(std::shared_ptr<AttribsManager>& ptr);

      protected:
         static std::shared_ptr<AttribsManager> _instance;
      };



      // inline and template methods
      inline std::pair<AttribsManager::AttribsStorageMultiMap::iterator,
            AttribsManager::AttribsStorageMultiMap::iterator>
            AttribsManager::getAttribsStorages(unsigned attribConfigID)
      {
         return _attribsStorageMultiMap.equal_range(attribConfigID);
      }
      inline AttribsManager::AttribsStorageMultiMap& AttribsManager::getAttribsStorages()
      {
         return _attribsStorageMultiMap;
      }
      inline const AttribsManager::AttribsStorageMultiMap& AttribsManager::getAttribsStorages() const
      {
         return _attribsStorageMultiMap;
      }
      inline std::shared_ptr<AttribsManager>& AttribsManager::instance()
      {
         if(!_instance)
            _instance = std::make_shared<AttribsManager>();
         return _instance;
      }

   }
}

#endif // GE_SG_ATTRIBS_MANAGER_H
