#ifndef GE_SG_SEPARATE_BUFFERS_ATTRIB_STORAGE_H
#define GE_SG_SEPARATE_BUFFERS_ATTRIB_STORAGE_H

#include <geSG/AttribStorage.h>

namespace ge
{
   namespace gl
   {
      class VertexArrayObject;
      class BufferObject;
   }
   namespace sg
   {
      /** AttribStorage class maintains vertex attributes of many scene objects
       *  in a single OpenGL vertex array object (VAO).
       */
      class GE_EXPORT SeparateBuffersAttribStorage : public AttribStorage {
      protected:

         ge::gl::VertexArrayObject* _vao;
         std::vector<ge::gl::BufferObject*> _arrayBuffers;
         ge::gl::BufferObject* _ebo;

      public:

         SeparateBuffersAttribStorage() = delete;
         SeparateBuffersAttribStorage(const AttribConfigRef &config,unsigned numVertices,unsigned numIndices);
         virtual ~SeparateBuffersAttribStorage();

         virtual void bind();

         virtual bool reallocData(AttribReference &r,int numVertices,int numIndices,
                                  bool preserveContent=true) override;
         virtual void uploadVertexData(AttribReference &r,const std::vector<Array>& data,
                                       int fromIndex=0,int numVertices=-1) override;
         virtual void uploadIndices(AttribReference &r,const Array& data,
                                    int fromIndex=0,int numIndices=-1) override;

      };



      // inline and template methods

   }
}

#endif // GE_SG_SEPARATE_BUFFERS_ATTRIB_STORAGE_H
