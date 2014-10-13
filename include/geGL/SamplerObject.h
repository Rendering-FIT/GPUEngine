#ifndef _SAMPLEROBJECT_H_
#define _SAMPLEROBJECT_H_

#include<geGL/Standard/OpenGL.h>

namespace ge{
  namespace gl{
    /**
     * @brief table 23.18
     */
    class GE_EXPORT SamplerObject
    {
      protected:
        GLuint _id;
      public:
        SamplerObject ();
        SamplerObject (SamplerObject*sampler);
        ~SamplerObject();
        void setBorderColor(GLfloat*color    );
        void setCompareFunc(GLenum  func     );
        void setCompareMode(GLenum  mode     );
        void setLodBias    (GLfloat lodBias  );
        void setMinLod     (GLfloat minLod   );
        void setMaxLod     (GLfloat maxLod   );
        void setMinFilter  (GLenum  minFilter);
        void setMagFilter  (GLenum  magFilter);
        void setWrapS      (GLenum  wrapS    );
        void setWrapT      (GLenum  wrapT    );
        void setWrapR      (GLenum  wrapR    );
        void    getBorderColor(GLfloat*color    );
        GLenum  getCompareFunc();
        GLenum  getCompareMode();
        GLfloat getLodBias    ();
        GLfloat getMinLod     ();
        GLfloat getMaxLod     ();
        GLenum  getMinFilter  ();
        GLenum  getMagFilter  ();
        GLenum  getWrapS      ();
        GLenum  getWrapT      ();
        GLenum  getWrapR      ();
        void bind          (GLuint  unit     );
        void unbind        (GLuint  unit     );
    };
  }//gl
}//ge


#endif//_SAMPLEROBJECT_H_
