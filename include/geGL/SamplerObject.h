#pragma once

#include<geGL/OpenGLObject.h>

namespace ge{
  namespace gl{
    /**
     * @brief table 23.18
     */
    class GEGL_EXPORT SamplerObject: public OpenGLObject{
      public:
        SamplerObject ();
        SamplerObject (SamplerObject*sampler);
#if defined(REPLACE_GLEW)
        SamplerObject (std::shared_ptr<OpenGLFunctionTable>const&table);
        SamplerObject (
            std::shared_ptr<OpenGLFunctionTable>const&table,
            SamplerObject*sampler);
#endif
        ~SamplerObject();
        void setBorderColor(GLfloat*color    )const;
        void setCompareFunc(GLenum  func     )const;
        void setCompareMode(GLenum  mode     )const;
        void setLodBias    (GLfloat lodBias  )const;
        void setMinLod     (GLfloat minLod   )const;
        void setMaxLod     (GLfloat maxLod   )const;
        void setMinFilter  (GLenum  minFilter)const;
        void setMagFilter  (GLenum  magFilter)const;
        void setWrapS      (GLenum  wrapS    )const;
        void setWrapT      (GLenum  wrapT    )const;
        void setWrapR      (GLenum  wrapR    )const;
        void    getBorderColor(GLfloat*color)const;
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
        void bind  (GLuint unit)const;
        void unbind(GLuint unit)const;
    };
  }//gl
}//ge

