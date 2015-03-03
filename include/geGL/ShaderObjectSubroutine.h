#ifndef _SHADEROBJECTSUBROUTINE_H_
#define _SHADEROBJECTSUBROUTINE_H_

#include<iostream>
#include<map>
#include<geGL/ShaderObjectSubroutineUniform.h>

namespace ge{
  namespace gl{
    /**
     * @brief This class represents shader parameter
     */
    class GEGL_EXPORT ShaderObjectSubroutine
    {
      public:
        /**
         * @brief List of subroutines uniforms
         */
        std::map<std::string,ShaderObjectSubroutineUniform>SubroutineUniformList;
        /**
         * @brief List of subroutines
         */
        std::map<std::string,GLuint>SubroutineList;
        GLuint*Indices;///<
        GLsizei NumIndices;///<
        /**
         * @brief Destructor
         */
        ~ShaderObjectSubroutine();
        /**
         * @brief Constructor
         */
        ShaderObjectSubroutine();
    };
  }//gl
}//ge


#endif//_CSHADEROBJECTSUBROUTINE_H_
