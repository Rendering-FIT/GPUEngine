#pragma once

#include<geGL/OpenGLObject.h>

/**
 * @brief table 23.18
 */
class ge::gl::Sampler: public OpenGLObject{
  public:
    GEGL_EXPORT Sampler ();
	GEGL_EXPORT Sampler (Sampler*sampler);
	GEGL_EXPORT Sampler (FunctionTablePointer const&table);
	GEGL_EXPORT Sampler (
        FunctionTablePointer const&table,
        Sampler*sampler);
	GEGL_EXPORT ~Sampler();
	GEGL_EXPORT void setBorderColor(GLfloat const*const&color    )const;
	GEGL_EXPORT void setCompareFunc(GLenum        const&func     )const;
	GEGL_EXPORT void setCompareMode(GLenum        const&mode     )const;
	GEGL_EXPORT void setLodBias    (GLfloat       const&lodBias  )const;
	GEGL_EXPORT void setMinLod     (GLfloat       const&minLod   )const;
	GEGL_EXPORT void setMaxLod     (GLfloat       const&maxLod   )const;
	GEGL_EXPORT void setMinFilter  (GLenum        const&minFilter)const;
	GEGL_EXPORT void setMagFilter  (GLenum        const&magFilter)const;
	GEGL_EXPORT void setWrapS      (GLenum        const&wrapS    )const;
	GEGL_EXPORT void setWrapT      (GLenum        const&wrapT    )const;
	GEGL_EXPORT void setWrapR      (GLenum        const&wrapR    )const;
	GEGL_EXPORT void    getBorderColor(GLfloat *const&constcolor)const;
	GEGL_EXPORT GLenum  getCompareFunc()const;
	GEGL_EXPORT GLenum  getCompareMode()const;
	GEGL_EXPORT GLfloat getLodBias    ()const;
	GEGL_EXPORT GLfloat getMinLod     ()const;
	GEGL_EXPORT GLfloat getMaxLod     ()const;
	GEGL_EXPORT GLenum  getMinFilter  ()const;
	GEGL_EXPORT GLenum  getMagFilter  ()const;
	GEGL_EXPORT GLenum  getWrapS      ()const;
	GEGL_EXPORT GLenum  getWrapT      ()const;
	GEGL_EXPORT GLenum  getWrapR      ()const;
	GEGL_EXPORT void bind  (GLuint const&unit)const;
	GEGL_EXPORT void unbind(GLuint const&unit)const;
};

