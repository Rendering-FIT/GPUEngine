#pragma once

typedef unsigned int	GLenum;
typedef unsigned char	GLboolean;
typedef unsigned int	GLbitfield;
typedef void		GLvoid;
typedef signed char	GLbyte;		/* 1-byte signed */
typedef short		GLshort;	/* 2-byte signed */
typedef int		GLint;		/* 4-byte signed */
typedef unsigned char	GLubyte;	/* 1-byte unsigned */
typedef unsigned short	GLushort;	/* 2-byte unsigned */
typedef unsigned int	GLuint;		/* 4-byte unsigned */
typedef int		GLsizei;	/* 4-byte signed */
typedef float		GLfloat;	/* single precision float */
typedef float		GLclampf;	/* single precision float in [0,1] */
typedef double		GLdouble;	/* double precision float */
typedef double		GLclampd;	/* double precision float in [0,1] */
typedef GLint GLfixed;
typedef uint64_t GLuint64;
typedef int64_t GLint64;
typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
typedef unsigned short GLhalf;
typedef struct __GLsync *GLsync;
typedef uint64_t GLuint64EXT;
typedef unsigned short GLhalfARB;
typedef void *GLhandleARB;
typedef char GLcharARB;
typedef ptrdiff_t GLsizeiptrARB;
typedef ptrdiff_t GLintptrARB;
typedef GLint GLfixed;
typedef int64_t GLint64EXT;
typedef GLintptr GLvdpauSurfaceNV;
typedef unsigned short GLhalfNV;
typedef void* GLeglImageOES;
typedef void (*GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
typedef void (*GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (*GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);

