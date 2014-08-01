#ifndef _SHADEROBJECTMANAGER_H_
#define _SHADEROBJECTMANAGER_H_

#include<iostream>

#include<geGL/Standard/OpenGL.h>
#include<geGL/ShadersAndPrograms/ShaderObjectsCommands.h>

namespace ge
{
  namespace gl
  {
    class GE_EXPORT CreateShaderObject: public Command
    {
      private:
        CreateShader  * _createShader;
        ShaderSource  * _shaderSource;
        CompileShader * _compileShader;
      public:
        CreateShaderObject(
            GLuint*shader,
            GLenum type,
            std::string text);
        ~CreateShaderObject();
        void apply();
    };
  }//ogl
}//ge


#endif//_SHADEROBJECTMANAGER_H_
