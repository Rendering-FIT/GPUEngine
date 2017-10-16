#pragma once

#include<GPUEngine/geGL/OpenGLObject.h>

/**
 * @brief table 23.18
 */
class GEGL_EXPORT ge::gl::Sampler: public OpenGLObject{
  public:
    Sampler ();
    Sampler (Sampler*sampler);
    Sampler (FunctionTablePointer const&table);
    Sampler (
        FunctionTablePointer const&table,
        Sampler*sampler);
    ~Sampler();
    void setBorderColor(GLfloat const*const&color    )const;
    void setCompareFunc(GLenum        const&func     )const;
    void setCompareMode(GLenum        const&mode     )const;
    void setLodBias    (GLfloat       const&lodBias  )const;
    void setMinLod     (GLfloat       const&minLod   )const;
    void setMaxLod     (GLfloat       const&maxLod   )const;
    void setMinFilter  (GLenum        const&minFilter)const;
    void setMagFilter  (GLenum        const&magFilter)const;
    void setWrapS      (GLenum        const&wrapS    )const;
    void setWrapT      (GLenum        const&wrapT    )const;
    void setWrapR      (GLenum        const&wrapR    )const;
    void    getBorderColor(GLfloat *const&constcolor)const;
    GLenum  getCompareFunc()const;
    GLenum  getCompareMode()const;
    GLfloat getLodBias    ()const;
    GLfloat getMinLod     ()const;
    GLfloat getMaxLod     ()const;
    GLenum  getMinFilter  ()const;
    GLenum  getMagFilter  ()const;
    GLenum  getWrapS      ()const;
    GLenum  getWrapT      ()const;
    GLenum  getWrapR      ()const;
    void bind  (GLuint const&unit)const;
    void unbind(GLuint const&unit)const;
};

