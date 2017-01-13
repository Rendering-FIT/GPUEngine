#pragma once

#include <geGL/OpenGLCommands.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ge
{
   namespace core
   {
      template<typename TYPE>
      inline TYPE convertTo(glm::mat4& mat){
         return glm::value_ptr(mat);
      }

      template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<glm::mat4>& mat){
         return glm::value_ptr(*mat);
      }

      template<typename TYPE>
      inline TYPE convertTo(glm::vec4& vec4){
         return glm::value_ptr(vec4);
      }

      template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<glm::vec4>& vec4){
         return glm::value_ptr(*vec4);
      }
   }
}

namespace fsg{

   typedef ge::gl::UniformMatrix4fv<GLint, GLsizei, GLboolean, glm::mat4> UniformMatrixGLM;
   typedef ge::gl::UniformMatrix4fv<GLint, GLsizei, GLboolean, std::shared_ptr<glm::mat4>> UniformMatrixGLMShared;

   typedef ge::gl::Uniform4fv<GLint, GLsizei, glm::vec4> Uniform4fGLM;
   typedef ge::gl::Uniform4fv<GLint, GLsizei, std::shared_ptr<glm::vec4>> Uniform4fGLMShared;

}
