#pragma once

#include <geGL/Export.h>
#include <GL/glew.h>
#include <vector>

namespace ge
{
  namespace gl
  {

  }
}

/*
#ifndef glTextureImage3D
extern decltype(glTextureImage3DEXT) glTextureImage3D;
#endif

#ifndef glTextureImage2D
extern decltype(glTextureImage2DEXT) glTextureImage2D;
#endif

#ifndef glTextureImage1D
extern decltype(glTextureImage1DEXT) glTextureImage1D;
#endif

#ifndef glCompressedTextureImage3D
extern decltype(glCompressedTextureImage3DEXT) glCompressedTextureImage3D;
#endif

#ifndef glCompressedTextureImage2D
extern decltype(glCompressedTextureImage2DEXT) glCompressedTextureImage2D;
#endif

#ifndef glCompressedTextureImage1D
extern decltype(glCompressedTextureImage1DEXT) glCompressedTextureImage1D;
#endif
*/
#ifndef glTextureImage3DMultisample
extern void (*glTextureImage3DMultisample) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
#endif

#ifndef glTextureImage2DMultisample
extern void (*glTextureImage2DMultisample) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
#endif

extern decltype(glDeleteTextures)*glDeleteTexturesGEGL;
