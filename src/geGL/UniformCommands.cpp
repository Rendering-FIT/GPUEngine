#include<geGL/UniformCommands.h>

using namespace ge::gl;

UniformCommand::UniformCommand(GLint location){
  this->_location=location;
}

ProgramUniformCommand::ProgramUniformCommand(
    GLuint program,
    GLint location):UniformCommand(location){
  this->_program = program;
}

#define UNIFORM_ARGS1 this->_data[0]
#define UNIFORM_ARGS2 this->_data[0],this->_data[1]
#define UNIFORM_ARGS3 this->_data[0],this->_data[1],this->_data[2]
#define UNIFORM_ARGS4 this->_data[0],this->_data[1],this->_data[2],this->_data[3]

template<>void Uniform<1,GLfloat >::operator()(){glUniform1f (this->_location,UNIFORM_ARGS1);}
template<>void Uniform<2,GLfloat >::operator()(){glUniform2f (this->_location,UNIFORM_ARGS2);}
template<>void Uniform<3,GLfloat >::operator()(){glUniform3f (this->_location,UNIFORM_ARGS3);}
template<>void Uniform<4,GLfloat >::operator()(){glUniform4f (this->_location,UNIFORM_ARGS4);}
template<>void Uniform<1,GLint   >::operator()(){glUniform1i (this->_location,UNIFORM_ARGS1);}
template<>void Uniform<2,GLint   >::operator()(){glUniform2i (this->_location,UNIFORM_ARGS2);}
template<>void Uniform<3,GLint   >::operator()(){glUniform3i (this->_location,UNIFORM_ARGS3);}
template<>void Uniform<4,GLint   >::operator()(){glUniform4i (this->_location,UNIFORM_ARGS4);}
template<>void Uniform<1,GLuint  >::operator()(){glUniform1ui(this->_location,UNIFORM_ARGS1);}
template<>void Uniform<2,GLuint  >::operator()(){glUniform2ui(this->_location,UNIFORM_ARGS2);}
template<>void Uniform<3,GLuint  >::operator()(){glUniform3ui(this->_location,UNIFORM_ARGS3);}
template<>void Uniform<4,GLuint  >::operator()(){glUniform4ui(this->_location,UNIFORM_ARGS4);}
template<>void Uniform<1,GLdouble>::operator()(){glUniform1d (this->_location,UNIFORM_ARGS1);}
template<>void Uniform<2,GLdouble>::operator()(){glUniform2d (this->_location,UNIFORM_ARGS2);}
template<>void Uniform<3,GLdouble>::operator()(){glUniform3d (this->_location,UNIFORM_ARGS3);}
template<>void Uniform<4,GLdouble>::operator()(){glUniform4d (this->_location,UNIFORM_ARGS4);}

template<>void UniformV<1,GLfloat >::operator()(){glUniform1fv (this->_location,this->_count,this->_data);}
template<>void UniformV<2,GLfloat >::operator()(){glUniform2fv (this->_location,this->_count,this->_data);}
template<>void UniformV<3,GLfloat >::operator()(){glUniform3fv (this->_location,this->_count,this->_data);}
template<>void UniformV<4,GLfloat >::operator()(){glUniform4fv (this->_location,this->_count,this->_data);}
template<>void UniformV<1,GLint   >::operator()(){glUniform1iv (this->_location,this->_count,this->_data);}
template<>void UniformV<2,GLint   >::operator()(){glUniform2iv (this->_location,this->_count,this->_data);}
template<>void UniformV<3,GLint   >::operator()(){glUniform3iv (this->_location,this->_count,this->_data);}
template<>void UniformV<4,GLint   >::operator()(){glUniform4iv (this->_location,this->_count,this->_data);}
template<>void UniformV<1,GLuint  >::operator()(){glUniform1uiv(this->_location,this->_count,this->_data);}
template<>void UniformV<2,GLuint  >::operator()(){glUniform2uiv(this->_location,this->_count,this->_data);}
template<>void UniformV<3,GLuint  >::operator()(){glUniform3uiv(this->_location,this->_count,this->_data);}
template<>void UniformV<4,GLuint  >::operator()(){glUniform4uiv(this->_location,this->_count,this->_data);}
template<>void UniformV<1,GLdouble>::operator()(){glUniform1dv (this->_location,this->_count,this->_data);}
template<>void UniformV<2,GLdouble>::operator()(){glUniform2dv (this->_location,this->_count,this->_data);}
template<>void UniformV<3,GLdouble>::operator()(){glUniform3dv (this->_location,this->_count,this->_data);}
template<>void UniformV<4,GLdouble>::operator()(){glUniform4dv (this->_location,this->_count,this->_data);}

template<>void ProgramUniform<1,GLfloat >::operator()(){glProgramUniform1f (this->_program,this->_location,UNIFORM_ARGS1);}
template<>void ProgramUniform<2,GLfloat >::operator()(){glProgramUniform2f (this->_program,this->_location,UNIFORM_ARGS2);}
template<>void ProgramUniform<3,GLfloat >::operator()(){glProgramUniform3f (this->_program,this->_location,UNIFORM_ARGS3);}
template<>void ProgramUniform<4,GLfloat >::operator()(){glProgramUniform4f (this->_program,this->_location,UNIFORM_ARGS4);}
template<>void ProgramUniform<1,GLint   >::operator()(){glProgramUniform1i (this->_program,this->_location,UNIFORM_ARGS1);}
template<>void ProgramUniform<2,GLint   >::operator()(){glProgramUniform2i (this->_program,this->_location,UNIFORM_ARGS2);}
template<>void ProgramUniform<3,GLint   >::operator()(){glProgramUniform3i (this->_program,this->_location,UNIFORM_ARGS3);}
template<>void ProgramUniform<4,GLint   >::operator()(){glProgramUniform4i (this->_program,this->_location,UNIFORM_ARGS4);}
template<>void ProgramUniform<1,GLuint  >::operator()(){glProgramUniform1ui(this->_program,this->_location,UNIFORM_ARGS1);}
template<>void ProgramUniform<2,GLuint  >::operator()(){glProgramUniform2ui(this->_program,this->_location,UNIFORM_ARGS2);}
template<>void ProgramUniform<3,GLuint  >::operator()(){glProgramUniform3ui(this->_program,this->_location,UNIFORM_ARGS3);}
template<>void ProgramUniform<4,GLuint  >::operator()(){glProgramUniform4ui(this->_program,this->_location,UNIFORM_ARGS4);}
template<>void ProgramUniform<1,GLdouble>::operator()(){glProgramUniform1d (this->_program,this->_location,UNIFORM_ARGS1);}
template<>void ProgramUniform<2,GLdouble>::operator()(){glProgramUniform2d (this->_program,this->_location,UNIFORM_ARGS2);}
template<>void ProgramUniform<3,GLdouble>::operator()(){glProgramUniform3d (this->_program,this->_location,UNIFORM_ARGS3);}
template<>void ProgramUniform<4,GLdouble>::operator()(){glProgramUniform4d (this->_program,this->_location,UNIFORM_ARGS4);}

template<>void ProgramUniformV<1,GLfloat >::operator()(){glProgramUniform1fv (this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<2,GLfloat >::operator()(){glProgramUniform2fv (this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<3,GLfloat >::operator()(){glProgramUniform3fv (this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<4,GLfloat >::operator()(){glProgramUniform4fv (this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<1,GLint   >::operator()(){glProgramUniform1iv (this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<2,GLint   >::operator()(){glProgramUniform2iv (this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<3,GLint   >::operator()(){glProgramUniform3iv (this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<4,GLint   >::operator()(){glProgramUniform4iv (this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<1,GLuint  >::operator()(){glProgramUniform1uiv(this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<2,GLuint  >::operator()(){glProgramUniform2uiv(this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<3,GLuint  >::operator()(){glProgramUniform3uiv(this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<4,GLuint  >::operator()(){glProgramUniform4uiv(this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<1,GLdouble>::operator()(){glProgramUniform1dv (this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<2,GLdouble>::operator()(){glProgramUniform2dv (this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<3,GLdouble>::operator()(){glProgramUniform3dv (this->_program,this->_location,this->_count,this->_data);}
template<>void ProgramUniformV<4,GLdouble>::operator()(){glProgramUniform4dv (this->_program,this->_location,this->_count,this->_data);}


#define UNIFORM_MATRIX_ARGS(T)this->_location,this->_count,this->_transpose,(const T*)this->_data
template<>void UniformMatrix<2,2,GLfloat >::operator()(){glUniformMatrix2fv  (UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void UniformMatrix<3,3,GLfloat >::operator()(){glUniformMatrix3fv  (UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void UniformMatrix<4,4,GLfloat >::operator()(){glUniformMatrix4fv  (UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void UniformMatrix<2,3,GLfloat >::operator()(){glUniformMatrix2x3fv(UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void UniformMatrix<3,2,GLfloat >::operator()(){glUniformMatrix3x2fv(UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void UniformMatrix<2,4,GLfloat >::operator()(){glUniformMatrix2x4fv(UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void UniformMatrix<4,2,GLfloat >::operator()(){glUniformMatrix4x2fv(UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void UniformMatrix<3,4,GLfloat >::operator()(){glUniformMatrix3x4fv(UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void UniformMatrix<4,3,GLfloat >::operator()(){glUniformMatrix4x3fv(UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void UniformMatrix<2,2,GLdouble>::operator()(){glUniformMatrix2dv  (UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void UniformMatrix<3,3,GLdouble>::operator()(){glUniformMatrix3dv  (UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void UniformMatrix<4,4,GLdouble>::operator()(){glUniformMatrix4dv  (UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void UniformMatrix<2,3,GLdouble>::operator()(){glUniformMatrix2x3dv(UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void UniformMatrix<3,2,GLdouble>::operator()(){glUniformMatrix3x2dv(UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void UniformMatrix<2,4,GLdouble>::operator()(){glUniformMatrix2x4dv(UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void UniformMatrix<4,2,GLdouble>::operator()(){glUniformMatrix4x2dv(UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void UniformMatrix<3,4,GLdouble>::operator()(){glUniformMatrix3x4dv(UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void UniformMatrix<4,3,GLdouble>::operator()(){glUniformMatrix4x3dv(UNIFORM_MATRIX_ARGS(GLdouble));}

#define PROGRAM_UNIFORM_MATRIX_ARGS(T)this->_program,UNIFORM_MATRIX_ARGS(T)
template<>void ProgramUniformMatrix<2,2,GLfloat >::operator()(){glProgramUniformMatrix2fv  (PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void ProgramUniformMatrix<3,3,GLfloat >::operator()(){glProgramUniformMatrix3fv  (PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void ProgramUniformMatrix<4,4,GLfloat >::operator()(){glProgramUniformMatrix4fv  (PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void ProgramUniformMatrix<2,3,GLfloat >::operator()(){glProgramUniformMatrix2x3fv(PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void ProgramUniformMatrix<3,2,GLfloat >::operator()(){glProgramUniformMatrix3x2fv(PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void ProgramUniformMatrix<2,4,GLfloat >::operator()(){glProgramUniformMatrix2x4fv(PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void ProgramUniformMatrix<4,2,GLfloat >::operator()(){glProgramUniformMatrix4x2fv(PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void ProgramUniformMatrix<3,4,GLfloat >::operator()(){glProgramUniformMatrix3x4fv(PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void ProgramUniformMatrix<4,3,GLfloat >::operator()(){glProgramUniformMatrix4x3fv(PROGRAM_UNIFORM_MATRIX_ARGS(GLfloat ));}
template<>void ProgramUniformMatrix<2,2,GLdouble>::operator()(){glProgramUniformMatrix2dv  (PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void ProgramUniformMatrix<3,3,GLdouble>::operator()(){glProgramUniformMatrix3dv  (PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void ProgramUniformMatrix<4,4,GLdouble>::operator()(){glProgramUniformMatrix4dv  (PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void ProgramUniformMatrix<2,3,GLdouble>::operator()(){glProgramUniformMatrix2x3dv(PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void ProgramUniformMatrix<3,2,GLdouble>::operator()(){glProgramUniformMatrix3x2dv(PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void ProgramUniformMatrix<2,4,GLdouble>::operator()(){glProgramUniformMatrix2x4dv(PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void ProgramUniformMatrix<4,2,GLdouble>::operator()(){glProgramUniformMatrix4x2dv(PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void ProgramUniformMatrix<3,4,GLdouble>::operator()(){glProgramUniformMatrix3x4dv(PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));}
template<>void ProgramUniformMatrix<4,3,GLdouble>::operator()(){glProgramUniformMatrix4x3dv(PROGRAM_UNIFORM_MATRIX_ARGS(GLdouble));}

UniformSubroutines::UniformSubroutines(GLenum shaderType,GLsizei count,GLuint* indices){
  this->_shaderType = shaderType;
  this->_count      = count     ;
  this->_indices    = indices   ;
}

UniformSubroutines::~UniformSubroutines(){
  delete[]this->_indices;
}

void UniformSubroutines::operator()(){
  glUniformSubroutinesuiv(this->_shaderType,this->_count,this->_indices);
}

