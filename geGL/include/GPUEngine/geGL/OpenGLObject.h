#pragma once

#include<GPUEngine/geGL/OpenGLContext.h>

class GEGL_EXPORT ge::gl::OpenGLObject{
  public:
    OpenGLObject(GLuint id = 0u);
    OpenGLObject(FunctionTablePointer const&table,GLuint id = 0u);
    virtual ~OpenGLObject();
    GLuint getId()const;
    Context const&getContext()const;
    OpenGLObject(OpenGLObject const&) = delete;
  protected:
    GLuint _id = 0u;///<object id
    Context _gl;
};

