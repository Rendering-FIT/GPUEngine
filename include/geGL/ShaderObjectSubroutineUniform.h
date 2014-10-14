#ifndef _SHADEROBJECTSUBROUTINEUNIFORM_H_
#define _SHADEROBJECTSUBROUTINEUNIFORM_H_

#include <geGL/OpenGL.h>
#include<iostream>

namespace ge{
  namespace gl{
    /**
     * @brief This class represents shader parameter
     */
    class ShaderObjectSubroutineUniform
    {
      public:
        GLint Location;///< location of subroutine uniform
        GLint Size;///< size of subroutine uniform array
        GLint NumCompatible;///< number of compatible subroutines
        std::string Name;///<subroutine uniform name
        unsigned Index;///<index into array indices
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
