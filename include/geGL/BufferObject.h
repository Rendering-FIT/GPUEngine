#ifndef GE_GL_BUFFEROBJECT
#define GE_GL_BUFFEROBJECT

#include <geGL/Standard/OpenGL.h>
#include <geCore/Object.h>

namespace ge
{
   namespace gl
{
class GE_EXPORT BufferObject// : public ge::core::Object
{
public:
   BufferObject();
   BufferObject(const BufferObject& buf, const ge::core::CopyOp& copyop = ge::core::CopyOp::SHALLOW_COPY);
   virtual ~BufferObject();

   //META_GE_Object(BufferObject)

   virtual void allocateClientSideBuffer(GLsizeiptr size, void* dataSource = NULL);
   virtual void freeClientSideBuffer();
   virtual void createAndInitGLBO(GLenum target, GLenum usage = GL_STATIC_DRAW, bool mutable_ = true, GLbitfield flags = 0);
   virtual void createAndInitGLBO(GLenum target, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW, void* data = NULL, bool mutable_ = true, GLbitfield flags = 0);
   virtual void deleteGLObject();
   virtual void map(GLenum mapFlags = 0);
   virtual void unmap();
   virtual GLboolean isMapped();
   virtual void bind();
   virtual void unbind();

   void* data(){ return _data; }
   GLsizeiptr size(){return _size;}
   GLuint glName(){ return _bufferObject; }

protected:

   bool _mutable;
   void* _data; ///< Designed to be used with this buffer object only. If you use this pointer for e.g. mapping it to another BO you could crash the app.

   GLuint _bufferObject; ///< Buffer Object OpenGL ID
   GLenum _target;
   GLsizeiptr _size;
   GLenum _usage;
   GLbitfield _flags;
};


}
}

#endif //GE_GL_BUFFEROBJECT