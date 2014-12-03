#ifndef GE_SG_ATTRIBS_MANAGER_H
#define GE_SG_ATTRIBS_MANAGER_H

#include <list>
#include <map>
#include <memory>
#include <geSG/AttribsConfig.h>
#include <geSG/Export.h>

namespace ge
{
   namespace sg
   {
      class Array;
      class AttribsReference;
      class AttribsStorage;
      class Mesh;


      class GE_EXPORT AttribsManager {
      public:

         typedef std::multimap<AttribsConfig,std::shared_ptr<AttribsStorage>> AttribsStorageMultiMap;

      protected:

         typedef std::map<AttribsConfigId,std::pair<AttribsStorageMultiMap::iterator,
               AttribsStorageMultiMap::iterator>> Id2IteratorMap;
         AttribsStorageMultiMap _attribsStorageMultiMap;
         Id2IteratorMap _id2IteratorMap;
         int _defaultStorageNumVertices = 1000*1024;
         int _defaultStorageNumIndices = 4000*1024;
         std::list<std::shared_ptr<AttribsStorage>> _privateAttribsStorages;

      public:

         inline AttribsManager() {}
         virtual ~AttribsManager();

         inline std::pair<AttribsStorageMultiMap::iterator,AttribsStorageMultiMap::iterator>
               getAttribsStorages(const AttribsConfig& attribsConfig);
         inline AttribsStorageMultiMap& getAttribsStorages();
         inline const AttribsStorageMultiMap& getAttribsStorages() const;

         virtual bool allocData(AttribsReference &r,const AttribsConfig& attribsConfig,
                                int numVertices,int numIndices);
         virtual bool reallocData(AttribsReference &r,int numVertices,int numIndices,
                                  bool preserveContent=true);
         virtual void freeData(AttribsReference &r);

         static inline void uploadVertexData(AttribsReference &r,const std::vector<Array>& attribs,
                                             int fromIndex=0,int numVertices=-1);
         static inline void uploadVertexData(AttribsReference &r,Mesh *mesh,
                                             int fromIndex=0,int numVertices=-1);
         static inline int uploadVertexData(AttribsReference &r,Mesh *mesh,
                                            unsigned &currentPosition,int bytesToUpload);
         static inline void uploadIndicesData(AttribsReference &r,const Array& indices,
                                              int fromIndex=0,int numIndices=-1);
         static inline void uploadIndicesData(AttribsReference &r,Mesh *mesh,
                                              int fromIndex=0,int numIndices=-1);
         static inline int uploadIndicesData(AttribsReference &r,Mesh *mesh,
                                             unsigned &currentPosition,int bytesToUpload);

         virtual std::shared_ptr<AttribsStorage> allocStorage(const AttribsConfig &config,
                                                              unsigned numVertices,unsigned numIndices,
                                                              bool privateFlag);

         static inline std::shared_ptr<AttribsManager>& instance();
         static void setInstance(std::shared_ptr<AttribsManager>& ptr);

      protected:
         static std::shared_ptr<AttribsManager> _instance;
      };

   }
}



// inline methods
//
// note: they need their own includes that can not be placed on the beginning of this file
//       as there is a circular include reference and the classes need to be defined before
//       inline methods to avoid incomplete type compiler error

#include <geSG/AttribsReference.h>

namespace ge
{
   namespace sg
   {
      inline void AttribsManager::uploadVertexData(AttribsReference &r,
                                                   const std::vector<Array>& attribs,
                                                   int fromIndex,int numVertices)
      {
         if(r.attribsStorage)
            r.attribsStorage->uploadVertexData(r,attribs,fromIndex,numVertices);
      }
      inline void AttribsManager::uploadVertexData(AttribsReference &r,Mesh *mesh,
                                                   int fromIndex,int numVertices)
      {
         if(r.attribsStorage)
            r.attribsStorage->uploadVertexData(r,mesh,fromIndex,numVertices);
      }
      inline int AttribsManager::uploadVertexData(AttribsReference &r,Mesh *mesh,
                                                  unsigned &currentPosition,int bytesToUpload)
      {
         if(r.attribsStorage)
            r.attribsStorage->uploadVertexData(r,mesh,currentPosition,bytesToUpload);
      }
      inline void AttribsManager::uploadIndicesData(AttribsReference &r,const Array& indices,
                                                    int fromIndex,int numIndices)
      {
         if(r.attribsStorage)
            r.attribsStorage->uploadIndicesData(r,indices,fromIndex,numIndices);
      }
      inline void AttribsManager::uploadIndicesData(AttribsReference &r,Mesh *mesh,
                                                    int fromIndex,int numIndices)
      {
         if(r.attribsStorage)
            r.attribsStorage->uploadIndicesData(r,mesh,fromIndex,numIndices);
      }
      inline int AttribsManager::uploadIndicesData(AttribsReference &r,Mesh *mesh,
                                                   unsigned &currentPosition,int bytesToUpload)
      {
         if(r.attribsStorage)
            r.attribsStorage->uploadIndicesData(r,mesh,currentPosition,bytesToUpload);
      }


      inline std::pair<AttribsManager::AttribsStorageMultiMap::iterator,
            AttribsManager::AttribsStorageMultiMap::iterator>
            AttribsManager::getAttribsStorages(const AttribsConfig& attribsConfig)
      {
         return attribsConfig.configId!=0 ? _id2IteratorMap[attribsConfig.configId]
                                          : _attribsStorageMultiMap.equal_range(attribsConfig);
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
         return _instance;
      }

   }
}

#endif // GE_SG_ATTRIBS_MANAGER_H
