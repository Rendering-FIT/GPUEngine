#pragma once
#include<cstddef>
#include<cstdint>
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
typedef char GLchar;
typedef unsigned short GLhalf;
typedef struct __GLsync *GLsync;
typedef uint64_t GLuint64;
typedef int64_t GLint64;
typedef void ( *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef uint64_t GLuint64EXT;
typedef void ( *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef unsigned short GLhalfARB;
#if __APPLE__
typedef void* GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif
typedef char GLcharARB;
typedef ptrdiff_t GLsizeiptrARB;
typedef ptrdiff_t GLintptrARB;
typedef GLint GLfixed;
typedef void ( *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
typedef int64_t GLint64EXT;
typedef void *GLeglClientBufferEXT;
typedef void ( *GLVULKANPROCNV)(void);
typedef unsigned short GLhalfNV;
typedef GLintptr GLvdpauSurfaceNV;
typedef void* GLeglImageOES;
struct _cl_context;
struct _cl_event;
