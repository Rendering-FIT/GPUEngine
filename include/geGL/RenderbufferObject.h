#include<GL/glew.h>

class RenderbufferObject
{
  protected:
    GLuint _id;
  public:
    RenderbufferObject(
        GLenum  internalFormat,
        GLsizei samples,
        GLsizei width,
        GLsizei height);
    RenderbufferObject(
        GLenum  internalFormat,
        GLsizei width,
        GLsizei height);
    ~RenderbufferObject();
    void   bind             ();
    void   unbind           ();
    GLuint getId            ();
    GLint  getWidth         ();
    GLint  getHeight        ();
    GLenum getInternalFormat();
    GLint  getSamples       ();
    GLint  getRedSize       ();
    GLint  getGreenSize     ();
    GLint  getBlueSize      ();
    GLint  getAlphaSize     ();
    GLint  getDepthSize     ();
    GLint  getStencilSize   ();
};

