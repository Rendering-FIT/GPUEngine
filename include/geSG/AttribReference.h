#ifndef GE_SG_ATTRIBS_REFERENCE_H
#define GE_SG_ATTRIBS_REFERENCE_H

#include <geSG/Export.h>

namespace ge
{
   namespace sg
   {
      class Array;
      class AttribsConfig;
      class AttribsStorage;
      class Mesh;


      class GE_EXPORT AttribsReference {
      public:

         AttribsStorage *attribsStorage;
         unsigned verticesDataId;
         unsigned indicesDataId;

         inline AttribsReference() : attribsStorage(NULL) {}
         AttribsReference(const AttribsReference&) = delete;
         inline AttribsReference(AttribsReference&& ref);
         AttribsReference& operator=(const AttribsReference&) = delete;
         inline AttribsReference& operator=(AttribsReference&& rhs);
         inline ~AttribsReference();

         inline void allocData(const AttribsConfig& attribsConfig,int numVertices,int numIndices);
         inline void reallocData(int numVertices,int numIndices,bool preserveContent=true);
         inline void freeData();

         inline void uploadVertexData(const std::vector<Array>& attribs,
                                      int fromIndex=0,int numVertices=-1);
         inline void uploadVertexData(Mesh *mesh,int fromIndex=0,int numVertices=-1);
         inline int uploadVertexData(Mesh *mesh,unsigned &currentPosition,int bytesToUpload);
         inline void uploadIndicesData(const Array& indices,int fromIndex=0,int numIndices=-1);
         inline void uploadIndicesData(Mesh *mesh,int fromIndex=0,int numIndices=-1);
         inline int uploadIndicesData(Mesh *mesh,unsigned &currentPosition,int bytesToUpload);

      };

   }
}



// inline methods
//
// note: they need their own includes that can not be placed on the beginning of this file
//       as there is a circular include reference and the classes need to be defined before
//       inline methods to avoid incomplete type compiler error

#include <geSG/AttribsStorage.h>
#include <geSG/AttribsManager.h>

namespace ge
{
   namespace sg
   {
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
      inline void AttribsReference::allocData(const AttribsConfig& attribsConfig,int numVertices,int numIndices)
      {
         AttribsManager::instance()->allocData(*this,attribsConfig,numVertices,numIndices);
      }
      inline void AttribsReference::reallocData(int numVertices,int numIndices,bool preserveContent)
      {
         AttribsManager::instance()->reallocData(*this,numVertices,numIndices,preserveContent);
      }
      inline void AttribsReference::freeData()
      {
         AttribsManager::instance()->freeData(*this);
      }
      inline void AttribsReference::uploadVertexData(const std::vector<Array>& attribs,
                                                     int fromIndex,int numVertices)
      {
         if(attribsStorage)
            attribsStorage->uploadVertexData(*this,attribs,fromIndex,numVertices);
      }
      inline void AttribsReference::uploadVertexData(Mesh *mesh,int fromIndex,int numVertices)
      {
         if(attribsStorage)
            attribsStorage->uploadVertexData(*this,mesh,fromIndex,numVertices);
      }
      inline int AttribsReference::uploadVertexData(Mesh *mesh,unsigned &currentPosition,int bytesToUpload)
      {
         if(attribsStorage)
            attribsStorage->uploadVertexData(*this,mesh,currentPosition,bytesToUpload);
      }
      inline void AttribsReference::uploadIndicesData(const Array& indices,int fromIndex,int numIndices)
      {
         if(attribsStorage)
            attribsStorage->uploadIndicesData(*this,indices,fromIndex,numIndices);
      }
      inline void AttribsReference::uploadIndicesData(Mesh *mesh,int fromIndex,int numIndices)
      {
         if(attribsStorage)
            attribsStorage->uploadIndicesData(*this,mesh,fromIndex,numIndices);
      }
      inline int AttribsReference::uploadIndicesData(Mesh *mesh,unsigned &currentPosition,int bytesToUpload)
      {
         if(attribsStorage)
            attribsStorage->uploadIndicesData(*this,mesh,currentPosition,bytesToUpload);
      }

   }
}

#endif // GE_SG_ATTRIBS_REFERENCE_H
