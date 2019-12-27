#pragma once

#include <geGL/OpenGLObject.h>
#include <iostream>
#include <set>
#include <vector>

class GEGL_EXPORT ge::gl::Buffer : public OpenGLObject {
 public:
  enum ReallocFlags {
    NEW_BUFFER   = 0u,
    KEEP_ID      = 1u << 0u,
    KEEP_DATA    = 1u << 1u,
    KEEP_DATA_ID = KEEP_ID | KEEP_DATA,
  };
  Buffer();
  Buffer(GLsizeiptr    size,
         GLvoid const* data  = nullptr,
         GLbitfield    flags = GL_STATIC_DRAW);
  Buffer(FunctionTablePointer const& table);
  Buffer(FunctionTablePointer const& table,
         GLsizeiptr                  size,
         GLvoid const*               data  = nullptr,
         GLbitfield                  flags = GL_STATIC_DRAW);
  virtual ~Buffer();
  void    alloc(GLsizeiptr    size,
                GLvoid const* data  = nullptr,
                GLbitfield    flags = GL_STATIC_DRAW);
  GLvoid* map(GLbitfield access = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT) const;
  GLvoid* map(GLintptr   offset,
              GLsizeiptr size,
              GLbitfield access = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT) const;
  void    unmap() const;
  void    setData(GLvoid const* data,
                  GLsizeiptr    size   = 0,
                  GLintptr      offset = 0) const;
  void    getData(GLvoid* data, GLsizeiptr size = 0, GLintptr offset = 0) const;
  void    bind(GLenum target) const;
  void    bindRange(GLenum     target,
                    GLuint     index,
                    GLintptr   offset,
                    GLsizeiptr size) const;
  void    bindBase(GLenum target, GLuint index) const;
  void    unbind(GLenum target) const;
  void    unbindRange(GLenum target, GLuint index) const;
  void    unbindBase(GLenum target, GLuint index) const;
  void    realloc(GLsizeiptr newSize, ReallocFlags flags = NEW_BUFFER);
  void    copy(Buffer const& buffer) const;
  void    flushMapped(GLsizeiptr size = 0, GLintptr offset = 0) const;
  void    invalidate(GLsizeiptr size = 0, GLintptr offset = 0) const;
  void    clear(GLenum        internalFormat,
                GLenum        format,
                GLenum        type,
                GLvoid const* Data = nullptr) const;
  void    clear(GLenum        internalFormat,
                GLintptr      offset,
                GLsizeiptr    size,
                GLenum        format,
                GLenum        type,
                GLvoid const* Data = nullptr) const;
  GLsizeiptr getSize() const;
  GLbitfield getUsage() const;
  GLenum     getAccess() const;
  GLbitfield getAccessFlags() const;
  GLboolean  isMapped() const;
  GLintptr   getMapOffset() const;
  GLsizeiptr getMapSize() const;
  GLvoid*    getMapPointer() const;
  GLboolean  isImmutable() const;

  template <typename T>
  Buffer(std::vector<T> const& data, GLbitfield flags = GL_STATIC_DRAW);
  template <typename T>
  Buffer(FunctionTablePointer const& table,
         std::vector<T> const&       data,
         GLbitfield                  flags = GL_STATIC_DRAW);
  template<typename T>
  void setData(std::vector<T>const&d,GLintptr offset = 0)const;
  template<typename T>
  void getData(std::vector<T>&d,GLintptr offset = 0)const;

 private:
  BufferImpl* impl = nullptr;
  friend class VertexArray;
  friend class VertexArrayImpl;
};

template <typename T>
ge::gl::Buffer::Buffer(std::vector<T> const& data, GLbitfield flags)
    : Buffer(data.size() * sizeof(T), data.data(), flags)
{
}

template <typename T>
ge::gl::Buffer::Buffer(FunctionTablePointer const& table,
                       std::vector<T> const&       data,
                       GLbitfield                  flags)
    : Buffer(table, data.size() * sizeof(T), data.data(), flags)
{
}


template<typename T>
void ge::gl::Buffer::setData(std::vector<T>const&d,GLintptr offset)const{
  setData(d.data(),d.size() * sizeof(T),offset);
}

template<typename T>
void ge::gl::Buffer::getData(std::vector<T>&d,GLintptr offset)const{
  auto const size = (getSize() - offset);
  d.resize(size/sizeof(T));
  getData(d.data(),size,offset);
}
