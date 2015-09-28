#pragma once

#include<geGL/OpenGL.h>
#include<iostream>

namespace ge{
  namespace gl{
    /**
     * @brief This class represents shader parameter
     */
    class GEGL_EXPORT ProgramObjectParameter{
      protected:
        GLint       _location = -1      ;///< parameter location
        GLenum      _type     = GL_FLOAT;///< parameter type
        std::string _name     = ""      ;///< parameter name
        GLint       _size     = 1       ;///< sizeof parameter
      public:
        ProgramObjectParameter(
            GLint       location = -1      ,
            GLenum      type     = GL_FLOAT,
            std::string name     = ""      ,
            GLint       size     = 1       );
        virtual ~ProgramObjectParameter();
        GLint       getLocation()const;
        GLenum      getType    ()const;
        std::string getName    ()const;
        GLint       getSize    ()const;
    };

    GEGL_EXPORT std::string translateUniformType      (GLenum      type    );
    GEGL_EXPORT std::string translateBufferProperty   (GLenum      property);
    GEGL_EXPORT std::string chopIndexingInPropertyName(std::string name    );

    class GEGL_EXPORT ProgramObjectBufferParams{
      public:
        enum Properties{
          TYPE                                ,
          ARRAY_SIZE                          ,
          OFFSET                              ,
          BLOCK_INDEX                         ,
          ARRAY_STRIDE                        ,
          MATRIX_STRIDE                       ,
          IS_ROW_MAJOR                        ,
          REFERENCED_BY_VERTEX_SHADER         ,
          REFERENCED_BY_TESS_CONTROL_SHADER   ,
          REFERENCED_BY_TESS_EVALUATION_SHADER,
          REFERENCED_BY_GEOMETRY_SHADER       ,
          REFERENCED_BY_FRAGMENT_SHADER       ,
          REFERENCED_BY_COMPUTE_SHADER        ,
          TOP_LEVEL_ARRAY_SIZE                ,
          TOP_LEVEL_ARRAY_STRIDE              ,
          BUFFER_BINDING
        };
      protected:
        GLint       _binding = 0;
        GLint       _params[TOP_LEVEL_ARRAY_STRIDE+1] = {0};
        std::string _name = "";
      public:
        ProgramObjectBufferParams(GLuint program,GLuint index);
        ProgramObjectBufferParams(){};
        GLint getProperty(enum Properties property)const;
        GLint getBinding()const;
        std::string getName()const;
        std::string toStr()const;
    };

    class GEGL_EXPORT SamplerParam{
      protected:
        GLint       _location = -1           ;
        GLenum      _type     = GL_SAMPLER_2D;
        GLint       _binding  = 0            ;
        std::string _name     = ""           ;
      public:
        SamplerParam(
            std::string name = ""           ,
            GLint location   = -1           ,
            GLenum type      = GL_SAMPLER_2D,
            GLint binding    = 0            );
        std::string getName    ()const;
        GLint       getBinding ()const;
        GLint       getLocation()const;
        void        setBinding(GLint binding);
        static bool isSampler(GLenum type);
    };









  }
}

