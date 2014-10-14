#ifndef _SHADEROBJECTMANAGER_H_
#define _SHADEROBJECTMANAGER_H_

#include<iostream>

#include<geGL/Standard/OpenGL.h>

#include<vector>
#include<map>

namespace ge
{
  namespace gl
  {
    class GE_EXPORT ProgramObjectManager
    {
      private:
        std::map<std::string,GLuint>_programs;
    };
  }
}
