#ifndef GE_SG_ATTRIB_DATA_REFERENCE_H
#define GE_SG_ATTRIB_DATA_REFERENCE_H

#include <geSG/AttribStorage.h>

namespace ge
{
   namespace sg
   {
      class AttribObject;
      class Mesh;

      struct AttribDataReference {

         AttribObject *attribObject;
         unsigned verticesDataId;
         unsigned indicesDataId;

         inline AttribDataReference() : attribObject(NULL) {}
         AttribDataReference(const AttribDataReference&) = delete;
         inline AttribDataReference(AttribDataReference&& ref);
         AttribDataReference& operator=(const AttribDataReference&) = delete;
         inline AttribDataReference& operator=(AttribDataReference&& rhs);
         inline ~AttribDataReference();

         inline void allocData(int numVertices,int numIndices,uint16_t attribConfigId);
         inline void reallocData(int numVertices,int numIndices,bool preserveContent=true);
         inline void freeData();
         inline void uploadVertexData(Mesh *mesh,int fromIndex=0,int numVertices=-1);
         inline int uploadVertexData(Mesh *mesh,unsigned &currentPosition,int bytesToUpload);
         inline void uploadIndicesData(Mesh *mesh,int fromIndex=0,int numIndices=-1);
         inline int uploadIndicesData(Mesh *mesh,unsigned &currentPosition,int bytesToUpload);
         //inline void map();
         //inline void unmap();

      };



      // inline methods
      inline AttribDataReference::AttribDataReference(AttribDataReference&& ref) : attribObject(ref.attribObject),verticesDataId(ref.verticesDataId),indicesDataId(ref.indicesDataId)
      {
         ref.attribObject=NULL;
      }
      inline AttribDataReference& AttribDataReference::operator=(AttribDataReference&& rhs)
      {
         attribObject=rhs.attribObject;
         verticesDataId=rhs.verticesDataId;
         indicesDataId=rhs.indicesDataId;
         rhs.attribObject=NULL;
      }
      AttribDataReference::~AttribDataReference()
      {
         freeData();
      }
      inline void AttribDataReference::allocData(int numVertices,int numIndices,uint16_t attribConfigId)
      {
         AttribStorage::instance()->allocData(this,numVertices,numIndices,attribConfigId);
      }
      inline void AttribDataReference::reallocData(int numVertices,int numIndices,bool preserveContent)
      {
         AttribStorage::instance()->reallocData(this,numVertices,numIndices,preserveContent);
      }
      inline void AttribDataReference::freeData()
      {
         AttribStorage::instance()->freeData(this);
      }
      inline void AttribDataReference::uploadVertexData(Mesh *mesh,int fromIndex,int numVertices)
      {
         AttribStorage::instance()->uploadVertexData(this,mesh,fromIndex,numVertices);
      }
      inline int AttribDataReference::uploadVertexData(Mesh *mesh,unsigned &currentPosition,int bytesToUpload)
      {
         return AttribStorage::instance()->uploadVertexData(this,mesh,currentPosition,bytesToUpload);
      }
      inline void AttribDataReference::uploadIndicesData(Mesh *mesh,int fromIndex,int numIndices)
      {
         AttribStorage::instance()->uploadIndicesData(this,mesh,fromIndex,numIndices);
      }
      inline int AttribDataReference::uploadIndicesData(Mesh *mesh,unsigned &currentPosition,int bytesToUpload)
      {
         return AttribStorage::instance()->uploadIndicesData(this,mesh,currentPosition,bytesToUpload);
      }

   }
}

#endif // GE_SG_ATTRIB_DATA_REFERENCE_H
