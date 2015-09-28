#ifndef _SHADEROBJECTSUBROUTINEUNIFORM_H_
#define _SHADEROBJECTSUBROUTINEUNIFORM_H_

#include <geGL/OpenGL.h>
#include<iostream>

namespace ge{
  namespace gl{
    /**
     * @brief This class represents shader parameter
     */
    class GEGL_EXPORT ShaderObjectSubroutineUniform
    {
      public:
        GLint location;///< location of subroutine uniform
        GLint size;///< size of subroutine uniform array
        GLint numCompatible;///< number of compatible subroutines
        std::string name;///<subroutine uniform name
        unsigned index;///<index into array indices
        /**
         * @brief Constructor
         *
         * @param Location parameter location
         * @param Type parameter Size
         * @param Name parameter NumCompatible
         * @param Size parameter Name
         */
        ShaderObjectSubroutineUniform(GLint Location,GLint Size,GLint NumCompatible,
            std::string Name,unsigned Index);
        ShaderObjectSubroutineUniform(){};
    };
  }
}


#endif//_SHADEROBJECTSUBROUTINEUNIFORM_H_
