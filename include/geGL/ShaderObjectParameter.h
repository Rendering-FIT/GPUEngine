#ifndef _CSHADERPARAMETER_HPP_
#define _CSHADERPARAMETER_HPP_

#include<geGL/OpenGL.h>
#include<iostream>


namespace ge{
  namespace gl{
    /**
     * @brief This class represents shader parameter
     */
    class GEGL_EXPORT ShaderObjectParameter
    {
      public:
        GLint       location;///< parameter location
        GLenum      type;///< parameter type
        std::string name;///< parameter name
        GLint       size;///< sizeof parameter
        /**
         * @brief Constructor
         *
         * @param location parameter location
         * @param type parameter type
         * @param name parameter name
         * @param size parameter Size
         */
        ShaderObjectParameter(GLint location,GLenum type,std::string name,GLint size);
        ShaderObjectParameter(){};
    };

    /**
     * @brief translates enum to string for uniform types
     *
     * @param type uniform type
     *
     * @return string representation
     */
    GEGL_EXPORT std::string translateUniformType(GLenum type);
    /**
     * @brief translates enum to string for buffer property types
     *
     * @param property buffer property type
     *
     * @return string representation
     */
    GEGL_EXPORT std::string translateBufferProperty(GLenum property);

    class GEGL_EXPORT BufferParams{
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
        GLint       _binding;
        GLint       _params[TOP_LEVEL_ARRAY_STRIDE+1];
        std::string _name;
      public:
        BufferParams(GLuint program,GLuint index);
        BufferParams(){};
        GLint getProperty(enum Properties property);
        GLint getBinding();
        std::string getName();
        std::string toStr();
    };


  }
}

#endif//_CSHADERPARAMETER_HPP_
