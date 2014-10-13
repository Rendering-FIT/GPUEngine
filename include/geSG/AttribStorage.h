#ifndef GE_SG_ATTRIB_STORAGE_H
#define GE_SG_ATTRIB_STORAGE_H

#include <map>
#include <memory>
#include <geSG/AttribObject.h>

namespace ge
{
   namespace sg
   {
      class AttribDataReference;
      class AttribObject;
      class Mesh;

      class AttribStorage {
      public:

         typedef std::multimap<uint16_t,std::unique_ptr<AttribObject>> AttribObjectMultiMap;

      protected:

         AttribObjectMultiMap _attribObjectMultiMap;

      public:

         virtual ~AttribStorage();

         inline std::pair<AttribObjectMultiMap::iterator,AttribObjectMultiMap::iterator> getAttribObjects(unsigned attribConfigID);
         inline AttribObjectMultiMap& getAttribObjects();
         inline const AttribObjectMultiMap& getAttribObjects() const;

         virtual bool allocData(AttribDataReference *r,int numVertices,int numIndices,uint16_t attribConfigId);
         virtual bool reallocData(AttribDataReference *r,int numVertices,int numIndices,bool preserveContent=true);
         virtual void freeData(AttribDataReference *r);
         virtual void uploadVertexData(AttribDataReference *r,Mesh *mesh,int fromIndex=0,int numVertices=-1);
         virtual int uploadVertexData(AttribDataReference *r,Mesh *mesh,unsigned &currentPosition,int bytesToUpload);
         virtual void uploadIndicesData(AttribDataReference *r,Mesh *mesh,int fromIndex=0,int numIndices=-1);
         virtual int uploadIndicesData(AttribDataReference *r,Mesh *mesh,unsigned &currentPosition,int bytesToUpload);

         static inline std::shared_ptr<AttribStorage>& instance();
         static void setInstance(std::shared_ptr<AttribStorage>& ptr);

      protected:
         static std::shared_ptr<AttribStorage> _instance;
      };



      // inline and template methods
      inline std::pair<AttribStorage::AttribObjectMultiMap::iterator,
            AttribStorage::AttribObjectMultiMap::iterator>
            AttribStorage::getAttribObjects(unsigned attribConfigID)
      {
         return _attribObjectMultiMap.equal_range(attribConfigID);
      }
      inline AttribStorage::AttribObjectMultiMap& AttribStorage::getAttribObjects()
      {
         return _attribObjectMultiMap;
      }
      inline const AttribStorage::AttribObjectMultiMap& AttribStorage::getAttribObjects() const
      {
         return _attribObjectMultiMap;
      }
      inline std::shared_ptr<AttribStorage>& AttribStorage::instance()
      {
         if(!_instance)
            _instance = std::make_shared<AttribStorage>();
         return _instance;
      }

   }
}

#endif // GE_SG_ATTRIB_STORAGE_H
