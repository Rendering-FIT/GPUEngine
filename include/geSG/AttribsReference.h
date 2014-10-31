#ifndef GE_SG_ATTRIBS_REFERENCE_H
#define GE_SG_ATTRIBS_REFERENCE_H

#include <geSG/AttribsManager.h>
#include <geSG/Export.h>

namespace ge
{
   namespace sg
   {
      class AttribsStorage;
      class Mesh;

      struct GE_EXPORT AttribsReference {

         AttribsStorage *attribsStorage;
         unsigned verticesDataId;
         unsigned indicesDataId;

         inline AttribsReference() : attribsStorage(NULL) {}
         AttribsReference(const AttribsReference&) = delete;
         inline AttribsReference(AttribsReference&& ref);
         AttribsReference& operator=(const AttribsReference&) = delete;
         inline AttribsReference& operator=(AttribsReference&& rhs);
         inline ~AttribsReference();

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
      inline AttribsReference::AttribsReference(AttribsReference&& ref)
         : attribsStorage(ref.attribsStorage)
         , verticesDataId(ref.verticesDataId)
         , indicesDataId(ref.indicesDataId)
      {
         ref.attribsStorage=NULL;
      }
      inline AttribsReference& AttribsReference::operator=(AttribsReference&& rhs)
      {
         attribsStorage=rhs.attribsStorage;
         verticesDataId=rhs.verticesDataId;
         indicesDataId=rhs.indicesDataId;
         rhs.attribsStorage=NULL;
      }
      AttribsReference::~AttribsReference()
      {
         freeData();
      }
      inline void AttribsReference::allocData(int numVertices,int numIndices,uint16_t attribConfigId)
      {
         AttribsManager::instance()->allocData(*this,numVertices,numIndices,attribConfigId);
      }
      inline void AttribsReference::reallocData(int numVertices,int numIndices,bool preserveContent)
      {
         AttribsManager::instance()->reallocData(*this,numVertices,numIndices,preserveContent);
      }
      inline void AttribsReference::freeData()
      {
         AttribsManager::instance()->freeData(*this);
      }
      inline void AttribsReference::uploadVertexData(Mesh *mesh,int fromIndex,int numVertices)
      {
         AttribsManager::instance()->uploadVertexData(*this,mesh,fromIndex,numVertices);
      }
      inline int AttribsReference::uploadVertexData(Mesh *mesh,unsigned &currentPosition,int bytesToUpload)
      {
         return AttribsManager::instance()->uploadVertexData(*this,mesh,currentPosition,bytesToUpload);
      }
      inline void AttribsReference::uploadIndicesData(Mesh *mesh,int fromIndex,int numIndices)
      {
         AttribsManager::instance()->uploadIndicesData(*this,mesh,fromIndex,numIndices);
      }
      inline int AttribsReference::uploadIndicesData(Mesh *mesh,unsigned &currentPosition,int bytesToUpload)
      {
         return AttribsManager::instance()->uploadIndicesData(*this,mesh,currentPosition,bytesToUpload);
      }

   }
}

#endif // GE_SG_ATTRIBS_REFERENCE_H
