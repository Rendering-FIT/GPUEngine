#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geGL/OpenGLCommands.h>

#define UNIFORM_GLM_MATRIX_ARGS(T)this->_location,this->_count,this->_transpose,(const T*)glm::value_ptr(*this->matrix.get())

namespace ge
{
   namespace core
   {
      template<>
      inline const float* convertTo<const float*,glm::mat4>(const glm::mat4& mat){
         return glm::value_ptr(mat);
      }

      template<>
      inline const float* convertTo<const float*,std::shared_ptr<glm::mat4>>(const std::shared_ptr<glm::mat4>& mat){
         return glm::value_ptr(*mat);
      }
   }
}

namespace fsg{

   typedef ge::gl::UniformMatrix4fv<GLint, GLsizei, GLboolean, glm::mat4> UniformMatrixGLM;
   typedef ge::gl::UniformMatrix4fv<GLint, GLsizei, GLboolean, std::shared_ptr<glm::mat4>> UniformMatrixGLMShared;

   /*template < unsigned X, unsigned Y, typename T, typename MatrixType >
   class  UniformMatrix : public ge::gl::UniformCommand{
   protected:
      GLsizei   _count;
      GLboolean _transpose;
   public:
      UniformMatrix(
         ge::gl::ProgramObject*program,
         std::string           name,
         std::shared_ptr<MatrixType>&              data,
         GLsizei               count = 1,
         GLboolean             transpose = GL_FALSE) :UniformCommand(program, name){
         this->set(data, count, transpose);
      }
      UniformMatrix(
         GLint     location,
         std::shared_ptr<MatrixType>&  data,
         GLsizei   count = 1,
         GLboolean transpose = GL_FALSE) :UniformCommand(location){
         this->set(data, count, transpose);
      }
      void operator()(){
         if(typeid(T) == typeid(float) ||
            typeid(T) == typeid(GLfloat)){
            if(X == 2 && Y == 2)glUniformMatrix2fv(UNIFORM_GLM_MATRIX_ARGS(GLfloat));
            if(X == 3 && Y == 3)glUniformMatrix3fv(UNIFORM_GLM_MATRIX_ARGS(GLfloat));
            if(X == 4 && Y == 4)glUniformMatrix4fv(UNIFORM_GLM_MATRIX_ARGS(GLfloat));
            if(X == 2 && Y == 3)glUniformMatrix2x3fv(UNIFORM_GLM_MATRIX_ARGS(GLfloat));
            if(X == 3 && Y == 2)glUniformMatrix3x2fv(UNIFORM_GLM_MATRIX_ARGS(GLfloat));
            if(X == 2 && Y == 4)glUniformMatrix2x4fv(UNIFORM_GLM_MATRIX_ARGS(GLfloat));
            if(X == 4 && Y == 2)glUniformMatrix4x2fv(UNIFORM_GLM_MATRIX_ARGS(GLfloat));
            if(X == 3 && Y == 4)glUniformMatrix3x4fv(UNIFORM_GLM_MATRIX_ARGS(GLfloat));
            if(X == 4 && Y == 3)glUniformMatrix4x3fv(UNIFORM_GLM_MATRIX_ARGS(GLfloat));
         }
         if(typeid(T) == typeid(double) ||
            typeid(T) == typeid(GLdouble)){
            if(X == 2 && Y == 2)glUniformMatrix2dv(UNIFORM_GLM_MATRIX_ARGS(GLdouble));
            if(X == 3 && Y == 3)glUniformMatrix3dv(UNIFORM_GLM_MATRIX_ARGS(GLdouble));
            if(X == 4 && Y == 4)glUniformMatrix4dv(UNIFORM_GLM_MATRIX_ARGS(GLdouble));
            if(X == 2 && Y == 3)glUniformMatrix2x3dv(UNIFORM_GLM_MATRIX_ARGS(GLdouble));
            if(X == 3 && Y == 2)glUniformMatrix3x2dv(UNIFORM_GLM_MATRIX_ARGS(GLdouble));
            if(X == 2 && Y == 4)glUniformMatrix2x4dv(UNIFORM_GLM_MATRIX_ARGS(GLdouble));
            if(X == 4 && Y == 2)glUniformMatrix4x2dv(UNIFORM_GLM_MATRIX_ARGS(GLdouble));
            if(X == 3 && Y == 4)glUniformMatrix3x4dv(UNIFORM_GLM_MATRIX_ARGS(GLdouble));
            if(X == 4 && Y == 3)glUniformMatrix4x3dv(UNIFORM_GLM_MATRIX_ARGS(GLdouble));
         }
      }
      void set(std::shared_ptr<MatrixType> &data, GLsizei count = 1, GLboolean transpose = GL_FALSE){
         this->matrix = data;
         this->_count = count;
         this->_transpose = transpose;
      }

      std::shared_ptr<MatrixType> matrix;
   };*/
}
