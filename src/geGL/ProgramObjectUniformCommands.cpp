#include<geGL/ProgramObjectUniformCommands.h>

using namespace ge::gl;

ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLfloat a0){
  return new Uniform<1,GLfloat>(program->getUniform(name),a0);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1){
  return new Uniform<2,GLfloat>(program->getUniform(name),a0,a1);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1,GLfloat a2){
  return new Uniform<3,GLfloat>(program->getUniform(name),a0,a1,a2);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1,GLfloat a2,GLfloat a3){
  return new Uniform<4,GLfloat>(program->getUniform(name),a0,a1,a2,a3);
}

ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLint a0){
  return new Uniform<1,GLint>(program->getUniform(name),a0);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLint a0,GLint a1){
  return new Uniform<2,GLint>(program->getUniform(name),a0,a1);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLint a0,GLint a1,GLint a2){
  return new Uniform<3,GLint>(program->getUniform(name),a0,a1,a2);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLint a0,GLint a1,GLint a2,GLint a3){
  return new Uniform<4,GLint>(program->getUniform(name),a0,a1,a2,a3);
}

ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLuint a0){
  return new Uniform<1,GLuint>(program->getUniform(name),a0);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1){
  return new Uniform<2,GLuint>(program->getUniform(name),a0,a1);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1,GLuint a2){
  return new Uniform<3,GLuint>(program->getUniform(name),a0,a1,a2);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1,GLuint a2,GLuint a3){
  return new Uniform<4,GLuint>(program->getUniform(name),a0,a1,a2,a3);
}

ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLdouble a0){
  return new Uniform<1,GLdouble>(program->getUniform(name),a0);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1){
  return new Uniform<2,GLdouble>(program->getUniform(name),a0,a1);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1,GLdouble a2){
  return new Uniform<3,GLdouble>(program->getUniform(name),a0,a1,a2);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1,GLdouble a2,GLdouble a3){
  return new Uniform<4,GLdouble>(program->getUniform(name),a0,a1,a2,a3);
}

template<typename TYPE,GLenum v1,GLenum v2,GLenum v3,GLenum v4>
inline ge::core::Command*createUniformV(ProgramObject*program,std::string name,const TYPE* data,GLsizei count,std::string typeName){
  GLenum type=program->getUniformType(name);
  if(type==v1)return new UniformV<1,TYPE>(program->getUniform(name),data,count);
  if(type==v2)return new UniformV<2,TYPE>(program->getUniform(name),data,count);
  if(type==v3)return new UniformV<3,TYPE>(program->getUniform(name),data,count);
  if(type==v4)return new UniformV<4,TYPE>(program->getUniform(name),data,count);
  std::cerr<<"ERROR: uniform type for "<<name<<" and program "<<program->getId()<<" is: "<<ge::gl::translateUniformType(type)<<"which does not match data type: const "<<typeName<<"*"<<std::endl;
  return NULL;
}

ge::core::Command*ge::gl::newUniformV(ProgramObject*program,std::string name,const GLfloat* data,GLsizei count){
  return createUniformV<GLfloat,GL_FLOAT,GL_FLOAT_VEC2,GL_FLOAT_VEC3,GL_FLOAT_VEC4>(program,name,data,count,"GLfloat");
}
ge::core::Command*ge::gl::newUniformV(ProgramObject*program,std::string name,const GLint*   data,GLsizei count){
  return createUniformV<GLint,GL_INT,GL_INT_VEC2,GL_INT_VEC3,GL_INT_VEC4>(program,name,data,count,"GLint");
}
ge::core::Command*ge::gl::newUniformV(ProgramObject*program,std::string name,const GLuint*  data,GLsizei count){
  return createUniformV<GLuint,GL_UNSIGNED_INT,GL_UNSIGNED_INT_VEC2,GL_UNSIGNED_INT_VEC3,GL_UNSIGNED_INT_VEC4>(program,name,data,count,"GLuint");
}
ge::core::Command*ge::gl::newUniformV(ProgramObject*program,std::string name,const GLdouble*data,GLsizei count){
  return createUniformV<GLdouble,GL_DOUBLE,GL_DOUBLE_VEC2,GL_DOUBLE_VEC3,GL_DOUBLE_VEC4>(program,name,data,count,"GLdouble");
}

ge::core::Command*ge::gl::newUniformMatrix(ProgramObject*program,std::string name,const GLfloat* data,GLsizei count,GLboolean transpose){
  GLenum type=program->getUniformType(name);
  switch(type){
    case GL_FLOAT_MAT2  :return new UniformMatrix<2,2,GLfloat>(program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT3  :return new UniformMatrix<3,3,GLfloat>(program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT4  :return new UniformMatrix<4,4,GLfloat>(program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT2x3:return new UniformMatrix<2,3,GLfloat>(program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT3x2:return new UniformMatrix<3,2,GLfloat>(program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT2x4:return new UniformMatrix<2,4,GLfloat>(program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT4x2:return new UniformMatrix<4,2,GLfloat>(program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT3x4:return new UniformMatrix<3,4,GLfloat>(program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT4x3:return new UniformMatrix<4,3,GLfloat>(program->getUniform(name),data,count,transpose);
    default             :
                         std::cerr<<"ERROR: uniform type for "<<name<<" and program "<<program->getId();
                         std::cerr<<" is: "<<ge::gl::translateUniformType(type)<<"which does not match data type: const GLfloat*"<<std::endl;
                         return NULL;
  }
}
ge::core::Command*ge::gl::newUniformMatrix(ProgramObject*program,std::string name,const GLdouble*data,GLsizei count,GLboolean transpose){
  GLenum type=program->getUniformType(name);
  switch(type){
    case GL_DOUBLE_MAT2  :return new UniformMatrix<2,2,GLdouble>(program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT3  :return new UniformMatrix<3,3,GLdouble>(program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT4  :return new UniformMatrix<4,4,GLdouble>(program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT2x3:return new UniformMatrix<2,3,GLdouble>(program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT3x2:return new UniformMatrix<3,2,GLdouble>(program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT2x4:return new UniformMatrix<2,4,GLdouble>(program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT4x2:return new UniformMatrix<4,2,GLdouble>(program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT3x4:return new UniformMatrix<3,4,GLdouble>(program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT4x3:return new UniformMatrix<4,3,GLdouble>(program->getUniform(name),data,count,transpose);
    default              :
                         std::cerr<<"ERROR: uniform type for "<<name<<" and program "<<program->getId();
                         std::cerr<<" is: "<<ge::gl::translateUniformType(type)<<"which does not match data type: const GLdouble*"<<std::endl;
                         return NULL;
  }
}

ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLfloat a0){
  return new ProgramUniform<1,GLfloat>(program->getId(),program->getUniform(name),a0);
}
ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1){
  return new ProgramUniform<2,GLfloat>(program->getId(),program->getUniform(name),a0,a1);
}
ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1,GLfloat a2){
  return new ProgramUniform<3,GLfloat>(program->getId(),program->getUniform(name),a0,a1,a2);
}
ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1,GLfloat a2,GLfloat a3){
  return new ProgramUniform<4,GLfloat>(program->getId(),program->getUniform(name),a0,a1,a2,a3);
}

ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLint a0){
  return new ProgramUniform<1,GLint>(program->getId(),program->getUniform(name),a0);
}
ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLint a0,GLint a1){
  return new ProgramUniform<2,GLint>(program->getId(),program->getUniform(name),a0,a1);
}
ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLint a0,GLint a1,GLint a2){
  return new ProgramUniform<3,GLint>(program->getId(),program->getUniform(name),a0,a1,a2);
}
ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLint a0,GLint a1,GLint a2,GLint a3){
  return new ProgramUniform<4,GLint>(program->getId(),program->getUniform(name),a0,a1,a2,a3);
}

ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLuint a0){
  return new ProgramUniform<1,GLuint>(program->getId(),program->getUniform(name),a0);
}
ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1){
  return new ProgramUniform<2,GLuint>(program->getId(),program->getUniform(name),a0,a1);
}
ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1,GLuint a2){
  return new ProgramUniform<3,GLuint>(program->getId(),program->getUniform(name),a0,a1,a2);
}
ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1,GLuint a2,GLuint a3){
  return new ProgramUniform<4,GLuint>(program->getId(),program->getUniform(name),a0,a1,a2,a3);
}

ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLdouble a0){
  return new ProgramUniform<1,GLdouble>(program->getId(),program->getUniform(name),a0);
}
ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1){
  return new ProgramUniform<2,GLdouble>(program->getId(),program->getUniform(name),a0,a1);
}
ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1,GLdouble a2){
  return new ProgramUniform<3,GLdouble>(program->getId(),program->getUniform(name),a0,a1,a2);
}
ge::core::Command*ge::gl::newProgramUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1,GLdouble a2,GLdouble a3){
  return new ProgramUniform<4,GLdouble>(program->getId(),program->getUniform(name),a0,a1,a2,a3);
}

template<typename TYPE,GLenum v1,GLenum v2,GLenum v3,GLenum v4>
inline ge::core::Command*createProgramUniformV(ProgramObject*program,std::string name,const TYPE* data,GLsizei count,std::string typeName){
  GLenum type=program->getUniformType(name);
  if(type==v1)return new ProgramUniformV<1,TYPE>(program->getId(),program->getUniform(name),data,count);
  if(type==v2)return new ProgramUniformV<2,TYPE>(program->getId(),program->getUniform(name),data,count);
  if(type==v3)return new ProgramUniformV<3,TYPE>(program->getId(),program->getUniform(name),data,count);
  if(type==v4)return new ProgramUniformV<4,TYPE>(program->getId(),program->getUniform(name),data,count);
  std::cerr<<"ERROR: uniform type for "<<name<<" and program "<<program->getId()<<" is: "<<ge::gl::translateUniformType(type)<<"which does not match data type: const "<<typeName<<"*"<<std::endl;
  return NULL;
}

ge::core::Command*ge::gl::newProgramUniformV(ProgramObject*program,std::string name,const GLfloat* data,GLsizei count){
  return createProgramUniformV<GLfloat,GL_FLOAT,GL_FLOAT_VEC2,GL_FLOAT_VEC3,GL_FLOAT_VEC4>(program,name,data,count,"GLfloat");
}
ge::core::Command*ge::gl::newProgramUniformV(ProgramObject*program,std::string name,const GLint*   data,GLsizei count){
  return createProgramUniformV<GLint,GL_INT,GL_INT_VEC2,GL_INT_VEC3,GL_INT_VEC4>(program,name,data,count,"GLint");
}
ge::core::Command*ge::gl::newProgramUniformV(ProgramObject*program,std::string name,const GLuint*  data,GLsizei count){
  return createProgramUniformV<GLuint,GL_UNSIGNED_INT,GL_UNSIGNED_INT_VEC2,GL_UNSIGNED_INT_VEC3,GL_UNSIGNED_INT_VEC4>(program,name,data,count,"GLuint");
}
ge::core::Command*ge::gl::newProgramUniformV(ProgramObject*program,std::string name,const GLdouble*data,GLsizei count){
  return createProgramUniformV<GLdouble,GL_DOUBLE,GL_DOUBLE_VEC2,GL_DOUBLE_VEC3,GL_DOUBLE_VEC4>(program,name,data,count,"GLdouble");
}

ge::core::Command*ge::gl::newProgramUniformMatrix(ProgramObject*program,std::string name,const GLfloat* data,GLsizei count,GLboolean transpose){
  GLenum type=program->getUniformType(name);
  switch(type){
    case GL_FLOAT_MAT2  :return new ProgramUniformMatrix<2,2,GLfloat>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT3  :return new ProgramUniformMatrix<3,3,GLfloat>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT4  :return new ProgramUniformMatrix<4,4,GLfloat>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT2x3:return new ProgramUniformMatrix<2,3,GLfloat>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT3x2:return new ProgramUniformMatrix<3,2,GLfloat>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT2x4:return new ProgramUniformMatrix<2,4,GLfloat>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT4x2:return new ProgramUniformMatrix<4,2,GLfloat>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT3x4:return new ProgramUniformMatrix<3,4,GLfloat>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_FLOAT_MAT4x3:return new ProgramUniformMatrix<4,3,GLfloat>(program->getId(),program->getUniform(name),data,count,transpose);
    default             :
                         std::cerr<<"ERROR: uniform type for "<<name<<" and program "<<program->getId();
                         std::cerr<<" is: "<<ge::gl::translateUniformType(type)<<"which does not match data type: const GLfloat*"<<std::endl;
                         return NULL;
  }
}
ge::core::Command*ge::gl::newProgramUniformMatrix(ProgramObject*program,std::string name,const GLdouble*data,GLsizei count,GLboolean transpose){
  GLenum type=program->getUniformType(name);
  switch(type){
    case GL_DOUBLE_MAT2  :return new ProgramUniformMatrix<2,2,GLdouble>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT3  :return new ProgramUniformMatrix<3,3,GLdouble>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT4  :return new ProgramUniformMatrix<4,4,GLdouble>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT2x3:return new ProgramUniformMatrix<2,3,GLdouble>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT3x2:return new ProgramUniformMatrix<3,2,GLdouble>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT2x4:return new ProgramUniformMatrix<2,4,GLdouble>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT4x2:return new ProgramUniformMatrix<4,2,GLdouble>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT3x4:return new ProgramUniformMatrix<3,4,GLdouble>(program->getId(),program->getUniform(name),data,count,transpose);
    case GL_DOUBLE_MAT4x3:return new ProgramUniformMatrix<4,3,GLdouble>(program->getId(),program->getUniform(name),data,count,transpose);
    default              :
                         std::cerr<<"ERROR: uniform type for "<<name<<" and program "<<program->getId();
                         std::cerr<<" is: "<<ge::gl::translateUniformType(type)<<"which does not match data type: const GLdouble*"<<std::endl;
                         return NULL;
  }
}

