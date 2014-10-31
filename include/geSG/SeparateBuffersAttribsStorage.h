#ifndef GE_SG_SEPARATE_BUFFERS_ATTRIBS_STORAGE_H
#define GE_SG_SEPARATE_BUFFERS_ATTRIBS_STORAGE_H

#include <geSG/AttribsStorage.h>

namespace ge
{
   namespace gl
   {
      class VertexArrayObject;
      class BufferObject;
   }
   namespace sg
   {
      /** AttribsStorage class maintains vertex attributes of many scene objects
       *  in a single OpenGL vertex array object (VAO).
       */
      class GE_EXPORT SeparateBuffersAttribsStorage : public AttribsStorage {
      protected:

         ge::gl::VertexArrayObject* _vao;
         std::vector<ge::gl::BufferObject*> _arrayBuffers;
         ge::gl::BufferObject *_ebo;

      public:

         SeparateBuffersAttribsStorage() = delete;
         SeparateBuffersAttribsStorage(const AttribsConfig &config,unsigned numVertices,unsigned numIndices);
         virtual ~SeparateBuffersAttribsStorage();

         virtual bool allocData(AttribsReference &r,int numVertices,int numIndices);
         virtual bool reallocData(AttribsReference &r,int numVertices,int numIndices,bool preserveContent=true);
         virtual void freeData(AttribsReference &r);
         virtual void uploadVertexData(AttribsReference &r,Mesh* mesh,int fromIndex=0,int numVertices=-1);
         virtual int uploadVertexData(AttribsReference &r,Mesh* mesh,unsigned &currentPosition,int bytesToUpload);
         virtual void uploadIndicesData(AttribsReference &r,Mesh* mesh,int fromIndex=0,int numVertices=-1);
         virtual int uploadIndicesData(AttribsReference &r,Mesh* mesh,unsigned &currentPosition,int bytesToUpload);

      };



      // inline and template methods

   }
}

#endif // GE_SG_SEPARATE_BUFFERS_ATTRIBS_STORAGE_H
