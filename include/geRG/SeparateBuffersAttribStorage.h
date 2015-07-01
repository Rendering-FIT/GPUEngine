#ifndef GE_RG_SEPARATE_BUFFERS_ATTRIB_STORAGE_H
#define GE_RG_SEPARATE_BUFFERS_ATTRIB_STORAGE_H

#include <geRG/AttribStorage.h>

namespace ge
{
   namespace gl
   {
      class VertexArrayObject;
      class BufferObject;
   }
   namespace rg
   {
      /** AttribStorage class maintains vertex attributes of many scene objects
       *  in a single OpenGL vertex array object (VAO).
       */
      class GESG_EXPORT SeparateBuffersAttribStorage : public AttribStorage {
      protected:

         ge::gl::VertexArrayObject* _vao;
         std::vector<ge::gl::BufferObject*> _arrayBuffers;
         ge::gl::BufferObject* _ebo;

      public:

         SeparateBuffersAttribStorage() = delete;
         SeparateBuffersAttribStorage(const AttribConfigRef &config,unsigned numVertices,
                                      unsigned numIndices);
         virtual ~SeparateBuffersAttribStorage();

         virtual void bind() const override;

         virtual bool reallocData(Mesh &mesh,int numVertices,int numIndices,
                                  bool preserveContent=true) override;
         virtual void uploadVertices(Mesh &mesh,const void*const *attribList,
                                     unsigned attribListSize,
                                     int numVertices,int fromIndex=0) override;
         virtual void uploadIndices(Mesh &mesh,const void *indices,
                                    int numIndices,int fromIndex=0) override;

      };

   }
}

#endif // GE_RG_SEPARATE_BUFFERS_ATTRIB_STORAGE_H
