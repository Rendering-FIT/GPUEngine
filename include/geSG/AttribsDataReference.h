#ifndef GE_SG_ATTRIBS_DATA_REFERENCE_H
#define GE_SG_ATTRIBS_DATA_REFERENCE_H

#include <geSG/AttribsManager.h>

namespace ge
{
   namespace sg
   {
      class AttribsStorage;
      class Mesh;

      struct AttribsDataReference {

         AttribsStorage *attribsStorage;
         unsigned verticesDataId;
         unsigned indicesDataId;

         inline AttribsDataReference() : attribsStorage(NULL) {}
         AttribsDataReference(const AttribsDataReference&) = delete;
         inline AttribsDataReference(AttribsDataReference&& ref);
         AttribsDataReference& operator=(const AttribsDataReference&) = delete;
         inline AttribsDataReference& operator=(AttribsDataReference&& rhs);
         inline ~AttribsDataReference();

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
      inline AttribsDataReference::AttribsDataReference(AttribsDataReference&& ref)
         : attribsStorage(ref.attribsStorage)
         , verticesDataId(ref.verticesDataId)
         , indicesDataId(ref.indicesDataId)
      {
         ref.attribsStorage=NULL;
      }
      inline AttribsDataReference& AttribsDataReference::operator=(AttribsDataReference&& rhs)
      {
         attribsStorage=rhs.attribsStorage;
         verticesDataId=rhs.verticesDataId;
         indicesDataId=rhs.indicesDataId;
         rhs.attribsStorage=NULL;
      }
      AttribsDataReference::~AttribsDataReference()
      {
         freeData();
      }
      inline void AttribsDataReference::allocData(int numVertices,int numIndices,uint16_t attribConfigId)
      {
         AttribsManager::instance()->allocData(this,numVertices,numIndices,attribConfigId);
      }
      inline void AttribsDataReference::reallocData(int numVertices,int numIndices,bool preserveContent)
      {
         AttribsManager::instance()->reallocData(this,numVertices,numIndices,preserveContent);
      }
      inline void AttribsDataReference::freeData()
      {
         AttribsManager::instance()->freeData(this);
      }
      inline void AttribsDataReference::uploadVertexData(Mesh *mesh,int fromIndex,int numVertices)
      {
         AttribsManager::instance()->uploadVertexData(this,mesh,fromIndex,numVertices);
      }
      inline int AttribsDataReference::uploadVertexData(Mesh *mesh,unsigned &currentPosition,int bytesToUpload)
      {
         return AttribsManager::instance()->uploadVertexData(this,mesh,currentPosition,bytesToUpload);
      }
      inline void AttribsDataReference::uploadIndicesData(Mesh *mesh,int fromIndex,int numIndices)
      {
         AttribsManager::instance()->uploadIndicesData(this,mesh,fromIndex,numIndices);
      }
      inline int AttribsDataReference::uploadIndicesData(Mesh *mesh,unsigned &currentPosition,int bytesToUpload)
      {
         return AttribsManager::instance()->uploadIndicesData(this,mesh,currentPosition,bytesToUpload);
      }

   }
}

#endif // GE_SG_ATTRIBS_DATA_REFERENCE_H
