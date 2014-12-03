#ifndef GE_SG_ATTRIBS_MANAGER_H
#define GE_SG_ATTRIBS_MANAGER_H

#include <list>
#include <map>
#include <memory>
#include <geSG/AttribConfig.h>
#include <geSG/Export.h>

namespace ge
{
   namespace sg
   {
      class Array;
      class AttribReference;
      class AttribStorage;
      class Mesh;


      class GE_EXPORT AttribManager {
      public:

         typedef std::multimap<AttribConfig,std::shared_ptr<AttribStorage>> AttribStorageMultiMap;

      protected:

         typedef std::map<AttribConfigId,std::pair<AttribStorageMultiMap::iterator,
               AttribStorageMultiMap::iterator>> Id2IteratorMap;
         AttribStorageMultiMap _attribStorageMultiMap;
         Id2IteratorMap _id2IteratorMap;
         int _defaultStorageNumVertices = 1000*1024;
         int _defaultStorageNumIndices = 4000*1024;
         std::list<std::shared_ptr<AttribStorage>> _privateAttribStorages;

      public:

         inline AttribManager() {}
         virtual ~AttribManager();

         inline std::pair<AttribStorageMultiMap::iterator,AttribStorageMultiMap::iterator>
               getAttribStorages(const AttribConfig& attribConfig);
         inline AttribStorageMultiMap& getAttribStorages();
         inline const AttribStorageMultiMap& getAttribStorages() const;

         virtual bool allocData(AttribReference &r,const AttribConfig& attribConfig,
                                int numVertices,int numIndices);
         virtual bool reallocData(AttribReference &r,int numVertices,int numIndices,
                                  bool preserveContent=true);
         virtual void freeData(AttribReference &r);

         static inline void uploadVertexData(AttribReference &r,const std::vector<Array>& attribs,
                                             int fromIndex=0,int numVertices=-1);
         static inline void uploadIndices(AttribReference &r,const Array& indices,
                                          int fromIndex=0,int numIndices=-1);

         virtual std::shared_ptr<AttribStorage> allocStorage(const AttribConfig &config,
                                                             unsigned numVertices,unsigned numIndices,
                                                             bool privateFlag);

         static inline std::shared_ptr<AttribManager>& instance();
         static void setInstance(std::shared_ptr<AttribManager>& ptr);

      protected:
         static std::shared_ptr<AttribManager> _instance;
      };

   }
}



// inline methods
//
// note: they need their own includes that can not be placed on the beginning of this file
//       as there is a circular include reference and the classes need to be defined before
//       inline methods to avoid incomplete type compiler error

#include <geSG/AttribReference.h>

namespace ge
{
   namespace sg
   {
      inline void AttribManager::uploadVertexData(AttribReference &r,
                                                  const std::vector<Array>& attribs,
                                                  int fromIndex,int numVertices)
      {
         if(r.attribStorage)
            r.attribStorage->uploadVertexData(r,attribs,fromIndex,numVertices);
      }
      inline void AttribManager::uploadIndices(AttribReference &r,const Array& indices,
                                               int fromIndex,int numIndices)
      {
         if(r.attribStorage)
            r.attribStorage->uploadIndices(r,indices,fromIndex,numIndices);
      }


      inline std::pair<AttribManager::AttribStorageMultiMap::iterator,
            AttribManager::AttribStorageMultiMap::iterator>
            AttribManager::getAttribStorages(const AttribConfig& attribConfig)
      {
         return attribConfig.configId!=0 ? _id2IteratorMap[attribConfig.configId]
                                         : _attribStorageMultiMap.equal_range(attribConfig);
      }
      inline AttribManager::AttribStorageMultiMap& AttribManager::getAttribStorages()
      {
         return _attribStorageMultiMap;
      }
      inline const AttribManager::AttribStorageMultiMap& AttribManager::getAttribStorages() const
      {
         return _attribStorageMultiMap;
      }
      inline std::shared_ptr<AttribManager>& AttribManager::instance()
      {
         return _instance;
      }

   }
}

#endif // GE_SG_ATTRIBS_MANAGER_H
