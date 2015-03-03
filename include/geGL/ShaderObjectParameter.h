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
  }
}

#endif//_CSHADERPARAMETER_HPP_
