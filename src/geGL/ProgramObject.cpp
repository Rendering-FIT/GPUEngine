#include<geGL/ProgramObject.h>
#include<string>
#include<sstream>

using namespace ge::gl;

bool OpenGL320=false;
bool OpenGL400=false;
bool OpenGL410=false;

void(*matrixfFce[])(GLint,GLsizei,GLboolean,const GLfloat*)={
  glUniformMatrix2fv  ,
  glUniformMatrix3fv  ,
  glUniformMatrix4fv  ,
  glUniformMatrix2x3fv,
  glUniformMatrix3x2fv,
  glUniformMatrix2x4fv,
  glUniformMatrix4x2fv,
  glUniformMatrix3x4fv,
  glUniformMatrix4x3fv
};
void(*matrixdFce[])(GLint,GLsizei,GLboolean,const GLdouble*)={
  glUniformMatrix2dv  ,
  glUniformMatrix3dv  ,
  glUniformMatrix4dv  ,
  glUniformMatrix2x3dv,
  glUniformMatrix3x2dv,
  glUniformMatrix2x4dv,
  glUniformMatrix4x2dv,
  glUniformMatrix3x4dv,
  glUniformMatrix4x3dv
};
void(*matrixfFceDsa[])(GLuint,GLint,GLsizei,GLboolean,const GLfloat*)={
  glProgramUniformMatrix2fv  ,
  glProgramUniformMatrix3fv  ,
  glProgramUniformMatrix4fv  ,
  glProgramUniformMatrix2x3fv,
  glProgramUniformMatrix3x2fv,
  glProgramUniformMatrix2x4fv,
  glProgramUniformMatrix4x2fv,
  glProgramUniformMatrix3x4fv,
  glProgramUniformMatrix4x3fv
};
void(*matrixdFceDsa[])(GLuint,GLint,GLsizei,GLboolean,const GLdouble*)={
  glProgramUniformMatrix2dv  ,
  glProgramUniformMatrix3dv  ,
  glProgramUniformMatrix4dv  ,
  glProgramUniformMatrix2x3dv,
  glProgramUniformMatrix3x2dv,
  glProgramUniformMatrix2x4dv,
  glProgramUniformMatrix4x2dv,
  glProgramUniformMatrix3x4dv,
  glProgramUniformMatrix4x3dv
};

/**
 * @brief Initialise shader manager
 */
void ge::gl::initShadersAndPrograms(){
  OpenGL320=true;
  OpenGL400=true;
  OpenGL410=true;
  std::string Result32="";
  std::string Result40="";
  std::string Result41="";

  if(!glCreateShader                  ){Result32+="glCreateShader "                  ;OpenGL320=false;}
  if(!glShaderSource                  ){Result32+="glShaderSource "                  ;OpenGL320=false;}
  if(!glCompileShader                 ){Result32+="glCompileShader "                 ;OpenGL320=false;}
  if(!glDeleteShader                  ){Result32+="glDeleteShader "                  ;OpenGL320=false;}
  if(!glGetShaderiv                   ){Result32+="glGetShaderiv "                   ;OpenGL320=false;}
  if(!glGetShaderInfoLog              ){Result32+="glGetShaderInfoLog "              ;OpenGL320=false;}
  if(!glCreateProgram                 ){Result32+="glCreateProgram "                 ;OpenGL320=false;}
  if(!glAttachShader                  ){Result32+="glAttachShader "                  ;OpenGL320=false;}
  if(!glDetachShader                  ){Result32+="glDetachShader "                  ;OpenGL320=false;}
  if(!glLinkProgram                   ){Result32+="glLinkProgram "                   ;OpenGL320=false;}
  if(!glUseProgram                    ){Result32+="glUseProgram "                    ;OpenGL320=false;}
  if(!glDeleteProgram                 ){Result32+="glDeleteProgram "                 ;OpenGL320=false;}
  if(!glGetProgramiv                  ){Result32+="glGetProgramiv "                  ;OpenGL320=false;}
  if(!glGetProgramInfoLog             ){Result32+="glGetProgramInfoLog "             ;OpenGL320=false;}
  if(!glGetActiveAttrib               ){Result32+="glGetActiveAttrib "               ;OpenGL320=false;}
  if(!glGetAttribLocation             ){Result32+="glGetAttribLocation "             ;OpenGL320=false;}
  if(!glGetActiveUniform              ){Result32+="glGetActiveUniform "              ;OpenGL320=false;}
  if(!glGetUniformLocation            ){Result32+="glGetUniformLocation "            ;OpenGL320=false;}
  if(!glUniform1f                     ){Result32+="glUniform1f "                     ;OpenGL320=false;}
  if(!glUniform2f                     ){Result32+="glUniform2f "                     ;OpenGL320=false;}
  if(!glUniform3f                     ){Result32+="glUniform3f "                     ;OpenGL320=false;}
  if(!glUniform4f                     ){Result32+="glUniform4f "                     ;OpenGL320=false;}
  if(!glUniform1i                     ){Result32+="glUniform1i "                     ;OpenGL320=false;}
  if(!glUniform2i                     ){Result32+="glUniform2i "                     ;OpenGL320=false;}
  if(!glUniform3i                     ){Result32+="glUniform3i "                     ;OpenGL320=false;}
  if(!glUniform4i                     ){Result32+="glUniform4i "                     ;OpenGL320=false;}
  if(!glUniform1ui                    ){Result32+="glUniform1ui "                    ;OpenGL320=false;}
  if(!glUniform2ui                    ){Result32+="glUniform2ui "                    ;OpenGL320=false;}
  if(!glUniform3ui                    ){Result32+="glUniform3ui "                    ;OpenGL320=false;}
  if(!glUniform4ui                    ){Result32+="glUniform4ui "                    ;OpenGL320=false;}
  if(!glUniform1fv                    ){Result32+="glUniform1fv "                    ;OpenGL320=false;}
  if(!glUniform2fv                    ){Result32+="glUniform2fv "                    ;OpenGL320=false;}
  if(!glUniform3fv                    ){Result32+="glUniform3fv "                    ;OpenGL320=false;}
  if(!glUniform4fv                    ){Result32+="glUniform4fv "                    ;OpenGL320=false;}
  if(!glUniform1iv                    ){Result32+="glUniform1iv "                    ;OpenGL320=false;}
  if(!glUniform2iv                    ){Result32+="glUniform2iv "                    ;OpenGL320=false;}
  if(!glUniform3iv                    ){Result32+="glUniform3iv "                    ;OpenGL320=false;}
  if(!glUniform4iv                    ){Result32+="glUniform4iv "                    ;OpenGL320=false;}
  if(!glUniform1uiv                   ){Result32+="glUniform1uiv "                   ;OpenGL320=false;}
  if(!glUniform2uiv                   ){Result32+="glUniform2uiv "                   ;OpenGL320=false;}
  if(!glUniform3uiv                   ){Result32+="glUniform3uiv "                   ;OpenGL320=false;}
  if(!glUniform4uiv                   ){Result32+="glUniform4uiv "                   ;OpenGL320=false;}
  if(!glUniformMatrix2fv              ){Result32+="glUniformMatrix2fv "              ;OpenGL320=false;}
  if(!glUniformMatrix2x3fv            ){Result32+="glUniformMatrix2x3fv "            ;OpenGL320=false;}
  if(!glUniformMatrix2x4fv            ){Result32+="glUniformMatrix2x4fv "            ;OpenGL320=false;}
  if(!glUniformMatrix3fv              ){Result32+="glUniformMatrix3fv "              ;OpenGL320=false;}
  if(!glUniformMatrix3x2fv            ){Result32+="glUniformMatrix3x2fv "            ;OpenGL320=false;}
  if(!glUniformMatrix3x4fv            ){Result32+="glUniformMatrix3x4fv "            ;OpenGL320=false;}
  if(!glUniformMatrix4fv              ){Result32+="glUniformMatrix4fv "              ;OpenGL320=false;}
  if(!glUniformMatrix4x2fv            ){Result32+="glUniformMatrix4x2fv "            ;OpenGL320=false;}
  if(!glUniformMatrix4x3fv            ){Result32+="glUniformMatrix4x3fv "            ;OpenGL320=false;}

  if(!glGetActiveSubroutineName       ){Result40+="glGetActiveSubroutineName "       ;OpenGL400=false;}
  if(!glGetActiveSubroutineUniformiv  ){Result40+="glGetActiveSubroutineUniformiv "  ;OpenGL400=false;}
  if(!glGetActiveSubroutineUniformName){Result40+="glGetActiveSubroutineUniformName ";OpenGL400=false;}
  if(!glGetProgramStageiv             ){Result40+="glGetProgramStageiv "             ;OpenGL400=false;}
  if(!glGetSubroutineIndex            ){Result40+="glGetSubroutineIndex "            ;OpenGL400=false;}
  if(!glGetSubroutineUniformLocation  ){Result40+="glGetSubroutineUniformLocation "  ;OpenGL400=false;}
  if(!glUniformSubroutinesuiv         ){Result40+="glUniformSubroutinesuiv "         ;OpenGL400=false;}
  if(!glUniform1d                     ){Result40+="glUniform1d "                     ;OpenGL400=false;}
  if(!glUniform2d                     ){Result40+="glUniform2d "                     ;OpenGL400=false;}
  if(!glUniform3d                     ){Result40+="glUniform3d "                     ;OpenGL400=false;}
  if(!glUniform4d                     ){Result40+="glUniform4d "                     ;OpenGL400=false;}
  if(!glUniform1dv                    ){Result40+="glUniform1dv "                    ;OpenGL400=false;}
  if(!glUniform2dv                    ){Result40+="glUniform2dv "                    ;OpenGL400=false;}
  if(!glUniform3dv                    ){Result40+="glUniform3dv "                    ;OpenGL400=false;}
  if(!glUniform4dv                    ){Result40+="glUniform4dv "                    ;OpenGL400=false;}
  if(!glUniformMatrix2dv              ){Result40+="glUniformMatrix2dv "              ;OpenGL400=false;}
  if(!glUniformMatrix2x3dv            ){Result40+="glUniformMatrix2x3dv "            ;OpenGL400=false;}
  if(!glUniformMatrix2x4dv            ){Result40+="glUniformMatrix2x4dv "            ;OpenGL400=false;}
  if(!glUniformMatrix3dv              ){Result40+="glUniformMatrix3dv "              ;OpenGL400=false;}
  if(!glUniformMatrix3x2dv            ){Result40+="glUniformMatrix3x2dv "            ;OpenGL400=false;}
  if(!glUniformMatrix3x4dv            ){Result40+="glUniformMatrix3x4dv "            ;OpenGL400=false;}
  if(!glUniformMatrix4dv              ){Result40+="glUniformMatrix4dv "              ;OpenGL400=false;}
  if(!glUniformMatrix4x2dv            ){Result40+="glUniformMatrix4x2dv "            ;OpenGL400=false;}
  if(!glUniformMatrix4x3dv            ){Result40+="glUniformMatrix4x3dv "            ;OpenGL400=false;}

  if(!glProgramUniformMatrix2fv       ){Result41+="glProgramUniformMatrix2fv "       ;OpenGL410=false;}
  if(!glProgramUniformMatrix3fv       ){Result41+="glProgramUniformMatrix3fv "       ;OpenGL410=false;}
  if(!glProgramUniformMatrix4fv       ){Result41+="glProgramUniformMatrix4fv "       ;OpenGL410=false;}
  if(!glProgramUniformMatrix2x3fv     ){Result41+="glProgramUniformMatrix2x3fv "     ;OpenGL410=false;}
  if(!glProgramUniformMatrix3x2fv     ){Result41+="glProgramUniformMatrix3x2fv "     ;OpenGL410=false;}
  if(!glProgramUniformMatrix2x4fv     ){Result41+="glProgramUniformMatrix2x4fv "     ;OpenGL410=false;}
  if(!glProgramUniformMatrix4x2fv     ){Result41+="glProgramUniformMatrix4x2fv "     ;OpenGL410=false;}
  if(!glProgramUniformMatrix3x4fv     ){Result41+="glProgramUniformMatrix3x4fv "     ;OpenGL410=false;}
  if(!glProgramUniformMatrix4x3fv     ){Result41+="glProgramUniformMatrix4x3fv "     ;OpenGL410=false;}
  if(!glProgramUniformMatrix2dv       ){Result41+="glProgramUniformMatrix2dv "       ;OpenGL410=false;}
  if(!glProgramUniformMatrix3dv       ){Result41+="glProgramUniformMatrix3dv "       ;OpenGL410=false;}
  if(!glProgramUniformMatrix4dv       ){Result41+="glProgramUniformMatrix4dv "       ;OpenGL410=false;}
  if(!glProgramUniformMatrix2x3dv     ){Result41+="glProgramUniformMatrix2x3dv "     ;OpenGL410=false;}
  if(!glProgramUniformMatrix3x2dv     ){Result41+="glProgramUniformMatrix3x2dv "     ;OpenGL410=false;}
  if(!glProgramUniformMatrix2x4dv     ){Result41+="glProgramUniformMatrix2x4dv "     ;OpenGL410=false;}
  if(!glProgramUniformMatrix4x2dv     ){Result41+="glProgramUniformMatrix4x2dv "     ;OpenGL410=false;}
  if(!glProgramUniformMatrix3x4dv     ){Result41+="glProgramUniformMatrix3x4dv "     ;OpenGL410=false;}
  if(!glProgramUniformMatrix4x3dv     ){Result41+="glProgramUniformMatrix4x3dv "     ;OpenGL410=false;}
  if(!glProgramParameteri             ){Result41+="glProgramParameteri "             ;OpenGL410=false;}

  if(!OpenGL320)std::cerr<<"OpenGL 3.2 is not available, missing: "+Result32<<std::endl;
  if(!OpenGL400)std::cerr<<"OpenGL 4.0 is not available, missing: "+Result40<<std::endl;
  if(!OpenGL410)std::cerr<<"OpenGL 4.1 is not available, missing: "+Result41<<std::endl;

  matrixfFce[0]=glUniformMatrix2fv  ;
  matrixfFce[1]=glUniformMatrix3fv  ;
  matrixfFce[2]=glUniformMatrix4fv  ;
  matrixfFce[3]=glUniformMatrix2x3fv;
  matrixfFce[4]=glUniformMatrix3x2fv;
  matrixfFce[5]=glUniformMatrix2x4fv;
  matrixfFce[6]=glUniformMatrix4x2fv;
  matrixfFce[7]=glUniformMatrix3x4fv;
  matrixfFce[8]=glUniformMatrix4x3fv;

  matrixdFce[0]=glUniformMatrix2dv  ;
  matrixdFce[1]=glUniformMatrix3dv  ;
  matrixdFce[2]=glUniformMatrix4dv  ;
  matrixdFce[3]=glUniformMatrix2x3dv;
  matrixdFce[4]=glUniformMatrix3x2dv;
  matrixdFce[5]=glUniformMatrix2x4dv;
  matrixdFce[6]=glUniformMatrix4x2dv;
  matrixdFce[7]=glUniformMatrix3x4dv;
  matrixdFce[8]=glUniformMatrix4x3dv;

  matrixfFceDsa[0]=glProgramUniformMatrix2fv  ;
  matrixfFceDsa[1]=glProgramUniformMatrix3fv  ;
  matrixfFceDsa[2]=glProgramUniformMatrix4fv  ;
  matrixfFceDsa[3]=glProgramUniformMatrix2x3fv;
  matrixfFceDsa[4]=glProgramUniformMatrix3x2fv;
  matrixfFceDsa[5]=glProgramUniformMatrix2x4fv;
  matrixfFceDsa[6]=glProgramUniformMatrix4x2fv;
  matrixfFceDsa[7]=glProgramUniformMatrix3x4fv;
  matrixfFceDsa[8]=glProgramUniformMatrix4x3fv;

  matrixdFceDsa[0]=glProgramUniformMatrix2dv  ;
  matrixdFceDsa[1]=glProgramUniformMatrix3dv  ;
  matrixdFceDsa[2]=glProgramUniformMatrix4dv  ;
  matrixdFceDsa[3]=glProgramUniformMatrix2x3dv;
  matrixdFceDsa[4]=glProgramUniformMatrix3x2dv;
  matrixdFceDsa[5]=glProgramUniformMatrix2x4dv;
  matrixdFceDsa[6]=glProgramUniformMatrix4x2dv;
  matrixdFceDsa[7]=glProgramUniformMatrix3x4dv;
  matrixdFceDsa[8]=glProgramUniformMatrix4x3dv;
}

/**
 * @brief Function converts complex type (GL_FLOAT_VEC3 to GL_FLOAT)
 *
 * @param Type OpenGL Type GL_FLOAT_VEC2, ...
 *
 * @return GL_FLOAT, ...
 */
GLenum ge::gl::complexType2SimpleType(GLenum type){
  switch(type){
    case GL_FLOAT            :return GL_FLOAT       ;
    case GL_FLOAT_VEC2       :return GL_FLOAT       ;
    case GL_FLOAT_VEC3       :return GL_FLOAT       ;
    case GL_FLOAT_VEC4       :return GL_FLOAT       ;
    case GL_DOUBLE           :return GL_DOUBLE      ;
    case GL_DOUBLE_VEC2      :return GL_DOUBLE      ;
    case GL_DOUBLE_VEC3      :return GL_DOUBLE      ;
    case GL_DOUBLE_VEC4      :return GL_DOUBLE      ;
    case GL_INT              :return GL_INT         ;
    case GL_INT_VEC2         :return GL_INT         ;
    case GL_INT_VEC3         :return GL_INT         ;
    case GL_INT_VEC4         :return GL_INT         ;
    case GL_UNSIGNED_INT     :return GL_UNSIGNED_INT;
    case GL_UNSIGNED_INT_VEC2:return GL_UNSIGNED_INT;
    case GL_UNSIGNED_INT_VEC3:return GL_UNSIGNED_INT;
    case GL_UNSIGNED_INT_VEC4:return GL_UNSIGNED_INT;
    case GL_BOOL             :return GL_BOOL        ;
    case GL_BOOL_VEC2        :return GL_BOOL        ;
    case GL_BOOL_VEC3        :return GL_BOOL        ;
    case GL_BOOL_VEC4        :return GL_BOOL        ;
    default                  :return GL_FLOAT       ;//GL_FALSE glbinding...
  }
}

/**
 * @brief Function converts complex type (GL_FLOAT_VEC3 to 3)
 *
 * @param Type OpenGL Type GL_FLOAT_VEC2, ...
 *
 * @return 2, ...
 */
GLint ge::gl::complexType2Size(GLenum type){
  switch(type){
    case GL_FLOAT            :return 1;
    case GL_FLOAT_VEC2       :return 2;
    case GL_FLOAT_VEC3       :return 3;
    case GL_FLOAT_VEC4       :return 4;
    case GL_DOUBLE           :return 1;
    case GL_DOUBLE_VEC2      :return 2;
    case GL_DOUBLE_VEC3      :return 3;
    case GL_DOUBLE_VEC4      :return 4;
    case GL_INT              :return 1;
    case GL_INT_VEC2         :return 2;
    case GL_INT_VEC3         :return 3;
    case GL_INT_VEC4         :return 4;
    case GL_UNSIGNED_INT     :return 1;
    case GL_UNSIGNED_INT_VEC2:return 2;
    case GL_UNSIGNED_INT_VEC3:return 3;
    case GL_UNSIGNED_INT_VEC4:return 4;
    case GL_BOOL             :return 1;
    case GL_BOOL_VEC2        :return 2;
    case GL_BOOL_VEC3        :return 3;
    case GL_BOOL_VEC4        :return 4;
    default                  :return 0;
  }
}

ProgramObject::ProgramObject(std::vector<std::string>const&data,unsigned version,std::string profile){
  this->_sortAndCompileShaders(data,version,profile);
}

std::string ProgramObject::uniformsToStr(){
  std::stringstream ss;
  for(auto x:this->_uniformList)
    ss<<x.first<<" ";
  return ss.str();
}

void ProgramObject::setSeparable    (){
  glProgramParameteri(this->_id,GL_PROGRAM_SEPARABLE,GL_TRUE);
  glLinkProgram(this->_id);
}
void ProgramObject::resetSeparable  (){
  glProgramParameteri(this->_id,GL_PROGRAM_SEPARABLE,GL_FALSE);
  glLinkProgram(this->_id);
}
void ProgramObject::setRetrievable  (){
  glProgramParameteri(this->_id,GL_PROGRAM_BINARY_RETRIEVABLE_HINT,GL_TRUE);
  glLinkProgram(this->_id);
}
void ProgramObject::resetRetrievable(){
  glProgramParameteri(this->_id,GL_PROGRAM_BINARY_RETRIEVABLE_HINT,GL_FALSE);
  glLinkProgram(this->_id);
}

void ProgramObject::_createShaderProgram_Prologue(){
  if(!OpenGL320){
    std::cerr<<std::string("OpenGL 3.2 not available")<<std::endl;
    return;
  }
  this->_id=glCreateProgram();//creates a shader program
  if(!this->_id){//something is wrong
    std::cerr<< std::string("glCreateProgram failed")<<std::endl;
    return;
  }
}

void ProgramObject::_createShaderProgram_Epilogue(){
  glLinkProgram(this->_id);//link shader program
  std::cerr<<this->_getProgramInfo(this->_id);
  GLint Status;//status of linking
  glGetProgramiv(this->_id,GL_LINK_STATUS,&Status);//status
  if(static_cast<GLboolean>(Status)==GL_FALSE){//something is wrong
    std::cerr << std::string("program linking failed")<<std::endl;
    return;
  }
  this->_getParameterList();//get list of shader program parameter

  if(OpenGL400)
    this->_getSubroutineUniformList();

  if(OpenGL400)
    this->_getBufferList();

  bool hasComputeShader=false;
  for(auto x:this->_shaders)
    if(x->getType()==GL_COMPUTE_SHADER){
      hasComputeShader=true;
      break;
    }
  if(hasComputeShader)
    glGetProgramiv(this->_id,GL_COMPUTE_WORK_GROUP_SIZE,
        this->workGroupSize);
}

typedef void (*GETACTIVEFCE  )(GLuint,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLchar*);
typedef GLint(*GETLOCATIONFCE)(GLuint,const GLchar*);
void ProgramObject::_getParameterList(){
  const GETACTIVEFCE   getActive[]   = {
    (GETACTIVEFCE)glGetActiveAttrib ,
    (GETACTIVEFCE)glGetActiveUniform};
  const GETLOCATIONFCE getLocation[] = {
    (GETLOCATIONFCE)glGetAttribLocation ,
    (GETLOCATIONFCE)glGetUniformLocation};
  const GLenum Active[]={
    GL_ACTIVE_ATTRIBUTES,
    GL_ACTIVE_UNIFORMS  };
  const GLenum MaxLenght[]={
    GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
    GL_ACTIVE_UNIFORM_MAX_LENGTH  };
  for(unsigned t=0;t<sizeof(Active)/sizeof(const GLenum);++t){//loop over set of types {attribute,uniform}
    GLuint num;//number of active parameter
    glGetProgramiv(this->_id,Active[t],reinterpret_cast<GLint*>(&num));//number
    if(!num)continue;//there are no active parameters
    GLsizei bufLen;//length of the longest attribute name
    glGetProgramiv(this->_id,MaxLenght[t],&bufLen);
    GLchar*Buffer=new GLchar[bufLen+1];//alocate buffer
    for(GLuint i=0;i<num;++i){//loop over active parameter
      GLenum      type;//type of parameter
      GLint       size;//size of parameter
      std::string name;//name of parameter
      GLint       location;//location of parameter
      GLsizei     length;
      getActive[t](this->_id,i,bufLen,&length,&size,&type,Buffer);
      name = chopIndexingInPropertyName(std::string(Buffer));
      location = getLocation[t](this->_id,name.c_str());//location
      if(ge::gl::SamplerParam::isSampler(type)){
        GLint binding;
        glGetUniformiv(this->getId(),location,&binding);
        this->_samplerList[name]=SamplerParam(name,location,type,binding);
      }
      ProgramObjectParameter Param = ProgramObjectParameter(location,type,name,size);//param
      if(Active[t]==GL_ACTIVE_ATTRIBUTES)this->_attributeList[name]=Param;
      else                               this->_uniformList  [name]=Param;
    }
    delete[]Buffer;//free buffer
  }
}
void ProgramObject::_getSubroutineUniformList(){
  const GLenum ShaderType[]={
    GL_VERTEX_SHADER         ,
    GL_TESS_CONTROL_SHADER   ,
    GL_TESS_EVALUATION_SHADER,
    GL_GEOMETRY_SHADER       ,
    GL_FRAGMENT_SHADER       ,
    GL_COMPUTE_SHADER
  };
  for(unsigned i=0;i<sizeof(ShaderType)/sizeof(const GLenum);++i){//loop over shader types
    GLuint NumSubroutines;//number of subroutines in this shader
    GLsizei MaxSubroutineNameSize;//max legth of name of subroutine
    glGetProgramStageiv(this->_id,ShaderType[i],//get number of sub.
        GL_ACTIVE_SUBROUTINES,reinterpret_cast<GLint*>(&NumSubroutines));
    if(NumSubroutines>0){//there are subroutines
      glGetProgramStageiv(this->_id,ShaderType[i],//max lenght
          GL_ACTIVE_SUBROUTINE_MAX_LENGTH,&MaxSubroutineNameSize);
      char*BufferName=new char[MaxSubroutineNameSize];//allocate buffer

      for(GLuint sub=0;sub<NumSubroutines;++sub){//loop over subroutines
        glGetActiveSubroutineName(this->_id,ShaderType[i],sub,
            MaxSubroutineNameSize,NULL,BufferName);//obtain name of subroutine
        GLuint Location=glGetSubroutineIndex(this->_id,
            ShaderType[i],BufferName);//obtain index of subroutine
        std::string Name=std::string(BufferName);//convert buffer to string
        this->_subroutines[i].addSubroutine(Name,Location);
      }
      delete[]BufferName;//free buffer
    }

    GLuint NumSubroutineUniforms;//number of subroutine uniforms
    GLint MaxSubroutineUniformNameSize;//max legth of subroutine uniforms

    glGetProgramStageiv(this->_id,ShaderType[i],//get number
        GL_ACTIVE_SUBROUTINE_UNIFORMS,reinterpret_cast<GLint*>(&NumSubroutineUniforms));
    if(NumSubroutineUniforms){//there are subroutine uniforms
      unsigned ActIndex=0;
      glGetProgramStageiv(this->_id,ShaderType[i],//get lenght
          GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH,&MaxSubroutineUniformNameSize);
      char*BufferName=new char[MaxSubroutineNameSize];//allocate buffer
      for(GLuint sub=0;sub<NumSubroutineUniforms;++sub){
        GLint Size;
        glGetActiveSubroutineUniformiv(this->_id,ShaderType[i],sub,
            GL_UNIFORM_SIZE,&Size);
        GLsizei Length;
        glGetActiveSubroutineUniformName(this->_id,ShaderType[i],sub,
            MaxSubroutineUniformNameSize,&Length,BufferName);//obtain name
        //if(Size>1)BufferName[Length-3]='\0';
        //std::string Name=std::string(BufferName);//convert buffer to string
        std::string Name = chopIndexingInPropertyName(std::string(BufferName));
        GLint NumCompatible;
        glGetActiveSubroutineUniformiv(this->_id,ShaderType[i],sub,
            GL_NUM_COMPATIBLE_SUBROUTINES,&NumCompatible);
        GLint Location;
        Location=glGetSubroutineUniformLocation(this->_id,
            ShaderType[i],Name.c_str());
        ShaderObjectSubroutineUniform ShaderSubroutineUniform=
          ShaderObjectSubroutineUniform(Location,Size,NumCompatible,Name,ActIndex);
        ActIndex+=Size;
        this->_subroutines[i].addUniform(Name,ShaderSubroutineUniform);
      }
      delete[]BufferName;//free buffer
      this->_subroutines[i].allocInidices(ActIndex);
    }
  }
}

void ProgramObject::_getBufferList(){
  GLint nofBuffers=0;
  glGetProgramInterfaceiv(
      this->getId(),
      GL_SHADER_STORAGE_BLOCK,
      GL_ACTIVE_RESOURCES,
      &nofBuffers);
  for(GLint i=0;i<nofBuffers;++i){
    ProgramObjectBufferParams params(this->getId(),i);
    this->_bufferList[params.getName()]=params;
    this->_bufferNames.push_back(params.getName());
  }
}

/**
 * @brief Sets subroutine with name SubroutineName as active in Uniform
 *
 * @param shaderType type of shader
 * @param uniform uniform name
 * @param subroutineName subroutine name
 */
void ProgramObject::setSubroutine(
    GLenum ShaderType,
    std::string Uniform,
    unsigned OffSet,
    std::string SubroutineName){
  int WH=0;
  switch(ShaderType){
    case GL_VERTEX_SHADER         :WH=0;break;
    case GL_TESS_CONTROL_SHADER   :WH=1;break;
    case GL_TESS_EVALUATION_SHADER:WH=2;break;
    case GL_GEOMETRY_SHADER       :WH=3;break;
    case GL_FRAGMENT_SHADER       :WH=4;break;
    case GL_COMPUTE_SHADER        :WH=5;break;
  }
  this->_subroutines[WH].set(ShaderType,Uniform,OffSet,SubroutineName);
}


std::string ProgramObject::_getProgramInfo(GLuint ID){
  int Len=0;//length of message
  glGetProgramiv(ID,GL_INFO_LOG_LENGTH,&Len);//gets length of message
  if(Len<=1)return"";
  std::string Info(Len,' ');//create string of Len length
  glGetProgramInfoLog(ID,Len,NULL,&Info[0]);//get message
  return Info;//return message
}

void ProgramObject::_compileShaders(
    std::vector<std::string>shaders,
    std::vector<std::string>defs,
    unsigned version,
    std::string profile){

  this->_createShaderProgram_Prologue();//create shader program
  try{
    for(unsigned s=0;s<shaders.size();++s)
      this->attachShader(std::make_shared<ShaderObject>(shaders[s],defs[s],version,profile));
  }catch(std::string&e){
    this->_shaders.clear();
    std::cerr<<e<<std::endl;
    return;
  }
  this->_createShaderProgram_Epilogue();//gets attributes and uniforms
}

/*
   bool ProgramObject::_isShader(std::string data){
   enum State{
   START      ,
   V          ,
   O          ,
   I          ,
   D          ,
   M          ,
   A          ,
   I          ,
   N          ,
   LEFT       ,
   RIGHT      ,
   SLASH      ,
   COMMENT    ,
   BACKSLASH  ,
   CR         ,
   LF         ,
   LONGCOMMENT,
   STAR       ,
   }state=START;
   unsigned pos=0;
   while(pos<data.size()){
   switch(state){
   case START:
   if(pos=='')
   break;
   }
   }
   }
   void ProgramObject::_createProgram(
   std::vector<std::string>& data,
   unsigned                  version,
   std::string               profile){
   const std::string functionName="ProgramObject::_createProgram";
   if(data.size()==0){
   std::cerr<<functionName<<" - there are no data"<<std::endl;
   return;
   }

   std::vector<std::string>sources;
   for(unsigned i=0;i<data.size();++i)
   sources.push_back(this->_getShaderSource(data[i]));

   unsigned i=0;
   while(!this->_isShader(sources[i])){
   std::cerr<<functionName<<" - there has to be a shader before: "<<sources[i]<<std::endl;
   ++i;
   }
   if(i>=sources.size()){
   std::cerr<<functionName<<" - there are no shaders"<<std::endl;
   return;
   }

   std::vector<std::string>shaders;
   while(i<sources.size()){
   std::vector<std::string>component;
   component.push_back(sources[i++]);//push shader
   while(i<sources.size()&&!this->_isShader(sources[i]))//push definitions ...
   component.push_back(sources[i++]);
   shaders.push_back(this->_composeShaderSource(component,version,profile));
   if(i>=sources.size())break;
   }
   std::vector<unsigned>shaderMasks;
   for(unsigned i=0;i<shaders.size();++i)
   shaderMasks.push_back(this->_getShaderSourceTypeMask(shaders[i]));
//resolved
//unsigned resolved=0;
unsigned presentShaders=0;
for(unsigned i=0;i<shaderMasks.size();++i)
presentShaders|=shaderMasks[i];
enum ShaderTypeId{
  VERTEX     = 0u,
  CONTROL    = 1u,
  EVALUATION = 2u,
  GEOMETRY   = 3u,
  FRAGMENT   = 4u,
  COMPUTE    = 5u,
};
const char*shaderNames[]={
  "vertex"                 ,
  "tessellation control"   ,
  "tessellation evaluation",
  "geometry"               ,
  "fragment"               ,
  "compute"                ,
};
const unsigned nofShaderTypes=sizeof(shaderNames)/sizeof(const char*);
enum ShaderTypeMask{
  MASK_VERTEX     = 1u << VERTEX    ,
  MASK_CONTROL    = 1u << CONTROL   ,
  MASK_EVALUATION = 1u << EVALUATION,
  MASK_GEOMETRY   = 1u << GEOMETRY  ,
  MASK_FRAGMENT   = 1u << FRAGMENT  ,
  MASK_COMPUTE    = 1u << COMPUTE   ,
};
const unsigned allowedCombinations[]={
  MASK_VERTEX  ,
  MASK_FRAGMENT,
  MASK_COMPUTE ,
  MASK_VERTEX  |MASK_FRAGMENT,
  MASK_VERTEX  |MASK_GEOMETRY,
  MASK_VERTEX  |MASK_GEOMETRY|MASK_FRAGMENT  ,
  MASK_VERTEX  |MASK_CONTROL |MASK_EVALUATION,
  MASK_VERTEX  |MASK_CONTROL |MASK_EVALUATION|MASK_GEOMETRY,
  MASK_VERTEX  |MASK_CONTROL |MASK_EVALUATION|MASK_FRAGMENT,
  MASK_VERTEX  |MASK_CONTROL |MASK_EVALUATION|MASK_GEOMETRY|MASK_FRAGMENT
};
const unsigned nofAllowedCombinations=sizeof(allowedCombinations)/sizeof(unsigned);
auto combination2Str=[&shaderNames](unsigned mask){
  std::stringstream ss;
  for(unsigned s=0;s<nofShaderTypes;++s)
    if(mask&(MASK_VERTEX+s)){
      ss<<shaderNames[s];
      if(s<nofShaderTypes-1)
        ss<<"+";
    }
  return ss.str();
};
auto nofShadersInCombination=[](unsigned mask){
  return ge::core::bitCount(mask);
};
auto shaderSubset=[](unsigned inner,unsigned outer){
  return ge::core::bitCount(inner&outer)==ge::core::bitCount(inner);
}
if(nofShadersInCombination(presentShaders)<shaders.size()){
  std::cerr<<functionName<<" - there are duplicate shaders"<<std::endl;
  return;
}
std::vector<unsigned>allowedIncides;
  for(unsigned i=0;i<nofAllowedCombinations;++i)
if(shaderSubset(presentShaders,allowedCombinations[i]))
  allowedIncides.push_back(i);

  if(!allowedIncides.size()){
    std::cerr<<functionName<<" - disallowed shader combination: "<<combination2Str(presentShaders)<<std::endl;
    return;
  }

}
*/
void ProgramObject::_sortAndCompileShaders(
    std::vector<std::string>strings,
    unsigned version,
    std::string profile){
  unsigned NumShaders=0;
  for(unsigned s=0;s<strings.size();++s)//loop over strings
    if(file2ShaderType(strings[s])!=0)//it is not definition
      NumShaders++;//increment shader count
  std::vector<std::string>shaderSources;
  std::vector<std::string>defs;
  for(unsigned s=0;s<NumShaders;++s)defs.push_back("");//initialize definitions
  int ActShader=-1;
  for(unsigned s=0;s<strings.size();++s){//loop over strings
    if(file2ShaderType(strings[s])!=0){//it is shaders
      ActShader++;//increment shader index
      shaderSources.push_back(strings[s]);//insert shader
    }else{//it is definitions
      if(ActShader<0){//there was no shader
        std::cerr<<std::string("bad arguments")<<std::endl;//throw error
        return;
      }else defs[ActShader]+=strings[s];//set definitinos
    }
  }
  this->_compileShaders(shaderSources,defs,version,profile);//compile
}

/**
 * @brief Sets version of every shader in shader program
 *
 * @param version version
 * @param profile profile
 */
void ProgramObject::setVersion(unsigned version,std::string profile){
  for(auto x:this->_shaders)
    x->setVersion(version,profile);
}

/**
 * @brief Sets version in specific shader of shader program 
 *
 * @param type shader type
 * @param version version
 * @param profile profile
 */
void ProgramObject::setVersion(GLenum type,unsigned version,std::string profile){
  for(auto x:this->_shaders)
    if(x->getType()==type)
      x->setVersion(version,profile);
}

/**
 * @brief Appends definitions after version in every shader of program
 *
 * @param defs definitions
 */
void ProgramObject::appendAfterVersion(std::string defs){
  for(auto x:this->_shaders)
    x->appendAfterVersion(defs);
}

/**
 * @brief Appends definitions after version in specific shader
 *
 * @param type type of shader
 * @param defs definitions
 */
void ProgramObject::appendAfterVersion(GLenum type,std::string defs){
  for(auto x:this->_shaders)
    if(x->getType()==type)
      x->appendAfterVersion(defs);
}

void ProgramObject::_deleteProgram(){
  for(auto x:this->_shaders)
    this->detachShader(x);
  glDeleteProgram(this->_id);//deletes shader program
  this->_shaders      .clear();
  this->_attributeList.clear();
  this->_uniformList  .clear();
  this->_bufferList   .clear();
  this->_bufferNames  .clear();
  this->_samplerList  .clear();
}

/**
 * @brief Relink program
 */

/**
 * @brief Destructor
 */
ProgramObject::~ProgramObject(){
  this->_deleteProgram();
}

/**
 * @brief Attach shader to program
 *
 * @param shader shader
 */
void ProgramObject::attachShader(std::shared_ptr<ShaderObject>const&shader){
  this->_shaders.insert(shader);
  glAttachShader(this->getId(),shader->getId());
}

/**
 * @brief Detach shader from program
 *
 * @param shader shader
 */
void ProgramObject::detachShader(std::shared_ptr<ShaderObject>const&shader){
  glDetachShader(this->getId(),shader->getId());
}

void err(std::string error){
  std::cerr<<"ERROR: "<<error<<std::endl;
}

/**
 * @brief Gets uniform meta data
 *
 * @param name uniform name
 *
 * @return meta data (location,type,name,size)
 */
ProgramObjectParameter const&ProgramObject::getUniform  (std::string name)const{
  auto i=this->_uniformList.find(name);
  if(i==this->_uniformList.end()){
    err("ProgramObject::getUniform("+name+") - there is no such uniform");
    static const ProgramObjectParameter er;
    return er;
  }
  return i->second;
}

/**
 * @brief Gets attribute meta data
 *
 * @param name attribute name
 *
 * @return meta data (location,type,name,size)
 */
ProgramObjectParameter const&ProgramObject::getAttribute(std::string name)const{
  auto i=this->_attributeList.find(name);
  if(i==this->_attributeList.end()){
    err("ProgramObject::getAttribute("+name+") - there is no such attribute");
    static const ProgramObjectParameter er;
    return er;
  }
  return i->second;
}

/**
 * @brief Gets buffer meta data
 *
 * @param name buffer name
 *
 * @return meta data (binding,name,params)
 */
ProgramObjectBufferParams const&ProgramObject::getBuffer(std::string name)const{
  auto i=this->_bufferList.find(name);
  if(i==this->_bufferList.end()){
    err("ProgramObject::getBuffer("+name+") - there is no such buffer");
    static const ProgramObjectBufferParams er;
    return er;
  }
  return i->second;
}

/**
 * @brief Gets number of uniforms
 *
 * @return number of uniforms
 */
decltype(ProgramObject::_uniformList)::size_type ProgramObject::getNofUniforms()const{
  return this->_uniformList.size();
}

/**
 * @brief Gets number of attributes
 *
 * @return number of attributes
 */
decltype(ProgramObject::_attributeList)::size_type ProgramObject::getNofAttributes()const{
  return this->_attributeList.size();
}

/**
 * @brief gets number of buffers
 *
 * @return number of buffers
 */
decltype(ProgramObject::_bufferNames)::size_type ProgramObject::getNofBuffers()const{
  return this->_bufferNames.size();
}

void ProgramObject::bindSSBO(std::string name,ge::gl::BufferObject*buffer){
  buffer->bindBase(GL_SHADER_STORAGE_BUFFER,this->getBuffer(name).getBinding());
}
void ProgramObject::bindSSBO(std::string name,ge::gl::BufferObject*buffer,GLintptr offset,GLsizeiptr size){
  buffer->bindRange(GL_SHADER_STORAGE_BUFFER,this->getBuffer(name).getBinding(),offset,size);
}

GLenum ProgramObject::getSamplerBinding(std::string uniform){
  return GL_TEXTURE0+this->_samplerList[uniform].getBinding();
}

void ProgramObject::bindTexture(std::string uniform,ge::gl::TextureObject*texture){
  texture->bind(GL_TEXTURE0+this->_samplerList[uniform].getBinding());
}
void ProgramObject::bindImage(
    std::string           uniform,
    ge::gl::TextureObject*texture,
    GLint                 level  ,
    GLenum                format ,
    GLenum                access ,
    GLboolean             layered,
    GLint                 layer  ){
  texture->bindImage(this->_samplerList[uniform].getBinding(),level,format,access,layered,layer);
}

/**
 * @brief Sets this program as active
 */
void ProgramObject::use()const{
  glUseProgram(this->_id);
}

int ProgramObject::_floatMatrixType2Index(GLenum type){
  if(type<=GL_FLOAT_MAT4)return type-GL_FLOAT_MAT2;
  int index=type-GL_FLOAT_MAT2x3;
  if(index<0)return index;
  return index+GL_FLOAT_MAT4-GL_FLOAT_MAT2+1;
}

int ProgramObject::_doubleMatrixType2Index(GLenum type){
  if(type>GL_DOUBLE_MAT4x3||type<GL_DOUBLE_MAT2)return-1;
  return type-GL_DOUBLE_MAT2;
}


#define MATRIXBODYA(TYPE)\
  if(!this->_uniformList.count(name))return;\
ProgramObjectParameter param=this->_uniformList[name];\
int index=this->_##TYPE##MatrixType2Index(param.getType());\
if(index<0)return;\

#define MATRIXBODY(FCE,TYPE)\
  MATRIXBODYA(TYPE)\
FCE[index](param.getLocation(),count,transpose,value)

#define MATRIXBODYDSA(FCE,TYPE)\
  MATRIXBODYA(TYPE)\
FCE[index](this->_id,param.getLocation(),count,transpose,value)


void ProgramObject::set(
    std::string   name,
    GLsizei       count,
    GLboolean     transpose,
    const GLfloat*value){
  MATRIXBODY(matrixfFce,float);
}

void ProgramObject::set(
    std::string    name,
    GLsizei        count,
    GLboolean      transpose,
    const GLdouble*value){
  MATRIXBODY(matrixdFce,double);
}

void ProgramObject::setdsa(
    std::string   name,
    GLsizei       count,
    GLboolean     transpose,
    const GLfloat*value){
  MATRIXBODYDSA(matrixfFceDsa,float);
}

void ProgramObject::setdsa(
    std::string    name,
    GLsizei        count,
    GLboolean      transpose,
    const GLdouble*value){
  MATRIXBODYDSA(matrixdFceDsa,double);
}

  DEF_PROGRAMOBJECT_SET(1,f)
  DEF_PROGRAMOBJECT_SET(2,f)
  DEF_PROGRAMOBJECT_SET(3,f)
  DEF_PROGRAMOBJECT_SET(4,f)
  DEF_PROGRAMOBJECT_SET(1,d)
  DEF_PROGRAMOBJECT_SET(2,d)
  DEF_PROGRAMOBJECT_SET(3,d)
  DEF_PROGRAMOBJECT_SET(4,d)
  DEF_PROGRAMOBJECT_SET(1,i)
  DEF_PROGRAMOBJECT_SET(2,i)
  DEF_PROGRAMOBJECT_SET(3,i)
  DEF_PROGRAMOBJECT_SET(4,i)
  DEF_PROGRAMOBJECT_SET(1,ui)
  DEF_PROGRAMOBJECT_SET(2,ui)
  DEF_PROGRAMOBJECT_SET(3,ui)
  DEF_PROGRAMOBJECT_SET(4,ui)
  DEF_PROGRAMOBJECT_SET(1,boolean)
  DEF_PROGRAMOBJECT_SET(2,boolean)
  DEF_PROGRAMOBJECT_SET(3,boolean)
  DEF_PROGRAMOBJECT_SET(4,boolean)
  DEF_PROGRAMOBJECT_SETV(f)
  DEF_PROGRAMOBJECT_SETV(d)
  DEF_PROGRAMOBJECT_SETV(i)
  DEF_PROGRAMOBJECT_SETV(ui)
DEF_PROGRAMOBJECT_SETV(boolean)


  DEF_PROGRAMOBJECT_SETDSA(1,f)
  DEF_PROGRAMOBJECT_SETDSA(2,f)
  DEF_PROGRAMOBJECT_SETDSA(3,f)
  DEF_PROGRAMOBJECT_SETDSA(4,f)
  DEF_PROGRAMOBJECT_SETDSA(1,d)
  DEF_PROGRAMOBJECT_SETDSA(2,d)
  DEF_PROGRAMOBJECT_SETDSA(3,d)
  DEF_PROGRAMOBJECT_SETDSA(4,d)
  DEF_PROGRAMOBJECT_SETDSA(1,i)
  DEF_PROGRAMOBJECT_SETDSA(2,i)
  DEF_PROGRAMOBJECT_SETDSA(3,i)
  DEF_PROGRAMOBJECT_SETDSA(4,i)
  DEF_PROGRAMOBJECT_SETDSA(1,ui)
  DEF_PROGRAMOBJECT_SETDSA(2,ui)
  DEF_PROGRAMOBJECT_SETDSA(3,ui)
  DEF_PROGRAMOBJECT_SETDSA(4,ui)
  DEF_PROGRAMOBJECT_SETDSA(1,boolean)
  DEF_PROGRAMOBJECT_SETDSA(2,boolean)
  DEF_PROGRAMOBJECT_SETDSA(3,boolean)
  DEF_PROGRAMOBJECT_SETDSA(4,boolean)
  DEF_PROGRAMOBJECT_SETDSAV(f)
  DEF_PROGRAMOBJECT_SETDSAV(d)
  DEF_PROGRAMOBJECT_SETDSAV(i)
  DEF_PROGRAMOBJECT_SETDSAV(ui)
DEF_PROGRAMOBJECT_SETDSAV(boolean)

