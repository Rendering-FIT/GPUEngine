#pragma once

#include<geGL/OpenGLContext.h>

class GEGL_EXPORT ge::gl::OpenGLObject{
  public:
	OpenGLObject(GLuint id = 0u);
	OpenGLObject(FunctionTablePointer const&table,GLuint id = 0u);
	virtual ~OpenGLObject();
	GLuint getId()const;
  GLuint&getId();
	Context const&getContext()const;
	OpenGLObject(OpenGLObject const&) = delete;
  private:
    OpenGLObjectImpl*impl = nullptr;
};

