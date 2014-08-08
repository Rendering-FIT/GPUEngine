#ifndef GE_GL_BUFFEROBJECT
#define GE_GL_BUFFEROBJECT

#include <geGL/Standard/OpenGL.h>
#include <geCore/Object.h>

#include <list>

namespace ge
{
   namespace gl
{
/**
 * Abstraction of the OpenGL Buffer Object.
 * Uses Direct State Access. It's internal data pointer can be used either for
 * mapping or as client-side data storage (not both).
 */
class GE_EXPORT BufferObject// : public ge::core::Object
{
public:
   BufferObject();
   BufferObject(const BufferObject& buf/*, const ge::core::CopyOp& copyop = ge::core::CopyOp::SHALLOW_COPY*/);
   virtual ~BufferObject();

   //class GE_EXPORT Mapping
   //{
   //public:
   //   Mapping(GLintptr offset, GLsizeiptr size, GLbitfield flags, GLuint bufferObject, void* data_)
   //      : _size(size)
   //      , _flags(flags)
   //      , _offset(offset)
   //      , _bufferObject(bufferObject)
   //      , data(data_)
   //      //, _myPlace()
   //   {

   //   }

   //   void *data;

   //   template <typename T> T* getData(){ return static_cast<T*> (_data); }
   //   //virtual void setPlace(const std::list<Mapping>::iterator& place){ _myPlace = place; }
   //protected:
   //   GLsizeiptr _size;
   //   GLbitfield _flags;
   //   GLintptr _offset;
   //   GLuint _bufferObject;
   //   //std::list<Mapping>::iterator _myPlace;

   //};

   //META_GE_Object(BufferObject)

   virtual void allocateClientSideBuffer(GLsizeiptr size, void* dataSource = NULL);
   virtual void freeClientSideBuffer();
   virtual void createAndInitGLBO(GLenum target, GLenum usage = GL_STATIC_DRAW, bool mutable_ = true, GLbitfield flags = 0);
   virtual void createAndInitGLBO(GLenum target, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW, void* data = NULL, bool mutable_ = true, GLbitfield flags = 0);
   virtual void deleteGLObject();
   virtual void map(GLintptr offset = 0, GLsizeiptr size = 0, GLenum mapFlags = 0);
   virtual void unmap();
   //virtual const Mapping *createMapping(GLintptr offset, GLsizeiptr size, GLbitfield flags);
   //virtual void destroyMapping(Mapping &mapping);
   virtual GLboolean isMapped();
   virtual void bind();
   virtual void unbind();

   inline void* data(){ return _data; }
   inline GLsizeiptr size(){return _size;}
   inline GLuint glName(){ return _bufferObject; }

protected:

   bool _mutable;
   void* _data; ///< Designed to be used with this buffer object only. If you use this pointer for e.g. mapping it to another BO you could crash the app.
   //std::list<Mapping> _mappings;

   GLuint _bufferObject; ///< Buffer Object OpenGL ID
   GLenum _target;
   GLsizeiptr _size;
   GLenum _usage;
   GLbitfield _flags;
};


}
}

#endif //GE_GL_BUFFEROBJECT