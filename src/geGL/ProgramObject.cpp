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

std::string ProgramObject::uniformsToStr(){
  std::stringstream ss;
  for(std::map<std::string,ShaderObjectParameter>::iterator it=this->_uniformList.begin();it!=this->_uniformList.end();++it){
    ss<<it->first<<" ";
  }
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
void ProgramObject::createShaderProgram_Prologue(){
  if(!OpenGL320){
    /*throw*/std::cerr<<std::string("OpenGL 3.2 not available")<<std::endl;
    return;
  }
  this->_id=glCreateProgram();//creates a shader program
  if(!this->_id){//something is wrong
    /*throw*/ std::cerr<< std::string("glCreateProgram failed")<<std::endl;//+GetGLError());//error message
    return;
  }
  //this->AttributeList=new std::map<std::string,ShaderObjectParameter>();
  //this->UniformList=new std::map<std::string,int>();
}

void ProgramObject::createShaderProgram_Epilogue(){
  glLinkProgram(this->_id);//link shader program
  std::cerr<<this->getProgramInfo(this->_id);
  GLint Status;//status of linking
  glGetProgramiv(this->_id,GL_LINK_STATUS,&Status);//status
  if(static_cast<GLboolean>(Status)==GL_FALSE){//something is wrong
    /*throw*/std::cerr << std::string("Shader linking failed")<<std::endl;//+GetGLError());//error message
    return;
  }
  this->getParameterList();//get list of shader program parameter

  if(OpenGL400)
    this->getSubroutineUniformList();

  if(OpenGL400)
    this->getBufferList();

  bool HasComputeShader=false;
  //for(unsigned i=0;i<this->ShaderList.size();++i){
  for(unsigned i=0;i<this->_shaders.size();++i){
    GLenum Type=GL_VERTEX_SHADER;
    GLuint Shader=this->_shaders[i]->getId();
    glGetShaderiv(Shader,GL_SHADER_TYPE,reinterpret_cast<GLint*>(&Type));
    if(Type==GL_COMPUTE_SHADER){
      HasComputeShader=true;
      break;
    }
  }
  if(HasComputeShader)
    glGetProgramiv(this->_id,GL_COMPUTE_WORK_GROUP_SIZE,
        this->workGroupSize);
}

typedef void (*GETACTIVEFCE  )(GLuint,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLchar*);
typedef GLint(*GETLOCATIONFCE)(GLuint,const GLchar*);
void ProgramObject::getParameterList(){
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
      ShaderObjectParameter Param = ShaderObjectParameter(location,type,name,size);//param
      if(Active[t]==GL_ACTIVE_ATTRIBUTES)this->_attributeList[name]=Param;
      else                               this->_uniformList  [name]=Param;
    }
    delete[]Buffer;//free buffer
  }
}
void ProgramObject::getSubroutineUniformList(){
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
        this->_subroutines[i].SubroutineList.insert(//insert subroutine
            std::pair<std::string,GLuint>(Name,Location));
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
        this->_subroutines[i].SubroutineUniformList.insert(
            std::pair<std::string,ShaderObjectSubroutineUniform>(Name,ShaderSubroutineUniform));
      }
      delete[]BufferName;//free buffer
      this->_subroutines[i].NumIndices=ActIndex;
      this->_subroutines[i].Indices=new GLuint[this->_subroutines[i].NumIndices];
      for(GLsizei ind=0;ind<this->_subroutines[i].NumIndices;++ind)
        this->_subroutines[i].Indices[ind]=0;
    }
  }
}

void ProgramObject::getBufferList(){
  GLint nofBuffers=0;
  glGetProgramInterfaceiv(
      this->getId(),
      GL_SHADER_STORAGE_BLOCK,
      GL_ACTIVE_RESOURCES,
      &nofBuffers);
  for(GLint i=0;i<nofBuffers;++i){
    BufferParams params(this->getId(),i);
    this->_bufferList.insert(
        std::pair<std::string,BufferParams>(
          params.getName(),
          params));
    this->_bufferNames.push_back(params.getName());
  }
}

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
  this->_subroutines[WH].Indices[
    this->_subroutines[WH].SubroutineUniformList[Uniform].Index+OffSet
    ]=this->_subroutines[WH].SubroutineList[SubroutineName];
  glUniformSubroutinesuiv(ShaderType,
      this->_subroutines[WH].NumIndices,
      this->_subroutines[WH].Indices);
}


std::string ProgramObject::getProgramInfo(GLuint ID){
  int Len=0;//length of message
  glGetProgramiv(ID,GL_INFO_LOG_LENGTH,&Len);//gets length of message
  if(Len<=1)return"";
  std::string Info(Len,' ');//create string of Len length
  glGetProgramInfoLog(ID,Len,NULL,&Info[0]);//get message
  return Info;//return message
}

void ProgramObject::compileShaders(
    unsigned NumShaders,
    std::string*Shaders,
    std::string*Defs,
    unsigned Version,
    std::string Profile){
  this->createShaderProgram_Prologue();//create shader program
  ShaderObject**S=new ShaderObject*[NumShaders];//alocate shaders array
  for(unsigned s=0;s<NumShaders;++s)S[s]=NULL;//initilize

  try{//try to create shaders
    for(unsigned s=0;s<NumShaders;++s)//loop over shaders
      S[s]=new ShaderObject(Shaders[s],Defs[s],Version,Profile);//create shader
  }catch(std::string&e){//catch errors
    for(unsigned s=0;s<NumShaders;++s)//loop over shaders
      if(S[s])delete S[s];//free allocate shaders
    delete[]S;//free shaders array
    std::cerr<<e<<std::endl;
    return;
    //throw e;//send error message
  }
  for(unsigned s=0;s<NumShaders;++s){
    glAttachShader(this->_id,S[s]->getId());
    this->_shaders.push_back(S[s]);
  }
  delete[]S;//free shaders array
  this->createShaderProgram_Epilogue();//gets attributes and uniforms
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
void ProgramObject::sortAndCompileShaders(
    unsigned NumStrings,
    std::string*Strings,
    unsigned Version,
    std::string Profile){
  unsigned NumShaders=0;
  for(unsigned s=0;s<NumStrings;++s)//loop over strings
    if(ShaderObject::file2ShaderType(Strings[s])!=0)//it is not definition
      NumShaders++;//increment shader count
  std::string*ShaderSources=new std::string[NumShaders];//allocate shaders
  std::string*Defs=new std::string[NumShaders];//allocate definitions
  for(unsigned s=0;s<NumShaders;++s)Defs[s]="";//initialize definitions
  int ActShader=-1;
  for(unsigned s=0;s<NumStrings;++s){//loop over strings
    if(ShaderObject::file2ShaderType(Strings[s])!=0){//it is shaders
      ActShader++;//increment shader index
      ShaderSources[ActShader]=Strings[s];//insert shader
    }else{//it is definitions
      if(ActShader<0){//there was no shader
        delete[]ShaderSources;//deallocate shader array
        delete[]Defs;//deallaocate definitions array
        /*throw*/
        std::cerr<<std::string("bad arguments")<<std::endl;//throw error
        return;
      }else Defs[ActShader]+=Strings[s];//set definitinos
    }
  }
  //std::cerr<<"NumShaders: "<<NumShaders<<std::endl;
  //for(unsigned s=0;s<NumShaders;++s){
  //  std::cerr<<ShaderSources[s]<<std::endl;
  //  std::cerr<<Defs[s]<<std::endl;
  //}
  //std::cerr<<"Before this->ComputeShaders\n";
  this->compileShaders(NumShaders,ShaderSources,Defs,Version,Profile);//compile
  //std::cerr<<"CompileShaders\n";
  delete[]ShaderSources;//deallocate shaders
  delete[]Defs;//deallocate definitions
}

ProgramObject::ProgramObject(
    std::string Shader0,
    unsigned    Version,
    std::string Profile){
  std::string*Strings=new std::string[1];
  Strings[0]=Shader0;
  this->sortAndCompileShaders(1,Strings,Version,Profile);
  delete[]Strings;
}

ProgramObject::ProgramObject(
    std::string Shader0,
    std::string Shader1,
    unsigned    Version,
    std::string Profile){
  std::string*Strings=new std::string[2];
  Strings[0]=Shader0;
  Strings[1]=Shader1;
  this->sortAndCompileShaders(2,Strings,Version,Profile);
  delete[]Strings;
}

ProgramObject::ProgramObject(
    std::string Shader0,
    std::string Shader1,
    std::string Shader2,
    unsigned    Version,
    std::string Profile){
  std::string*Strings=new std::string[3];
  Strings[0]=Shader0;
  Strings[1]=Shader1;
  Strings[2]=Shader2;
  this->sortAndCompileShaders(3,Strings,Version,Profile);
  delete[]Strings;
}

ProgramObject::ProgramObject(
    std::string Shader0,
    std::string Shader1,
    std::string Shader2,
    std::string Shader3,
    unsigned    Version,
    std::string Profile){
  std::string*Strings=new std::string[4];
  Strings[0]=Shader0;
  Strings[1]=Shader1;
  Strings[2]=Shader2;
  Strings[3]=Shader3;
  this->sortAndCompileShaders(4,Strings,Version,Profile);
  delete[]Strings;

}

ProgramObject::ProgramObject(
    std::string Shader0,
    std::string Shader1,
    std::string Shader2,
    std::string Shader3,
    std::string Shader4,
    unsigned    Version,
    std::string Profile){
  std::string*Strings=new std::string[5];
  Strings[0]=Shader0;
  Strings[1]=Shader1;
  Strings[2]=Shader2;
  Strings[3]=Shader3;
  Strings[4]=Shader4;

  this->sortAndCompileShaders(5,Strings,Version,Profile);
  delete[]Strings;
}
ProgramObject::ProgramObject(
    std::string Shader0,
    std::string Shader1,
    std::string Shader2,
    std::string Shader3,
    std::string Shader4,
    std::string Shader5,
    unsigned    Version,
    std::string Profile){
  std::string*Strings=new std::string[6];
  Strings[0]=Shader0;
  Strings[1]=Shader1;
  Strings[2]=Shader2;
  Strings[3]=Shader3;
  Strings[4]=Shader4;
  Strings[5]=Shader5;

  this->sortAndCompileShaders(6,Strings,Version,Profile);
  delete[]Strings;

}
ProgramObject::ProgramObject(
    std::string Shader0,
    std::string Shader1,
    std::string Shader2,
    std::string Shader3,
    std::string Shader4,
    std::string Shader5,
    std::string Shader6,
    unsigned    Version,
    std::string Profile){
  std::string*Strings=new std::string[7];
  Strings[0]=Shader0;
  Strings[1]=Shader1;
  Strings[2]=Shader2;
  Strings[3]=Shader3;
  Strings[4]=Shader4;
  Strings[5]=Shader5;
  Strings[6]=Shader6;

  this->sortAndCompileShaders(7,Strings,Version,Profile);
  delete[]Strings;

}
ProgramObject::ProgramObject(
    std::string Shader0,
    std::string Shader1,
    std::string Shader2,
    std::string Shader3,
    std::string Shader4,
    std::string Shader5,
    std::string Shader6,
    std::string Shader7,
    unsigned    Version,
    std::string Profile){
  std::string*Strings=new std::string[8];
  Strings[0]=Shader0;
  Strings[1]=Shader1;
  Strings[2]=Shader2;
  Strings[3]=Shader3;
  Strings[4]=Shader4;
  Strings[5]=Shader5;
  Strings[6]=Shader6;
  Strings[7]=Shader7;

  this->sortAndCompileShaders(8,Strings,Version,Profile);
  delete[]Strings;
}
ProgramObject::ProgramObject(
    std::string Shader0,
    std::string Shader1,
    std::string Shader2,
    std::string Shader3,
    std::string Shader4,
    std::string Shader5,
    std::string Shader6,
    std::string Shader7,
    std::string Shader8,
    unsigned    Version,
    std::string Profile){
  std::string*Strings=new std::string[9];
  Strings[0]=Shader0;
  Strings[1]=Shader1;
  Strings[2]=Shader2;
  Strings[3]=Shader3;
  Strings[4]=Shader4;
  Strings[5]=Shader5;
  Strings[6]=Shader6;
  Strings[7]=Shader7;
  Strings[8]=Shader8;

  this->sortAndCompileShaders(9,Strings,Version,Profile);
  delete[]Strings;
}
ProgramObject::ProgramObject(
    std::string Shader0,
    std::string Shader1,
    std::string Shader2,
    std::string Shader3,
    std::string Shader4,
    std::string Shader5,
    std::string Shader6,
    std::string Shader7,
    std::string Shader8,
    std::string Shader9,
    unsigned    Version,
    std::string Profile){
  std::string*Strings=new std::string[10];
  Strings[0]=Shader0;
  Strings[1]=Shader1;
  Strings[2]=Shader2;
  Strings[3]=Shader3;
  Strings[4]=Shader4;
  Strings[5]=Shader5;
  Strings[6]=Shader6;
  Strings[7]=Shader7;
  Strings[8]=Shader8;
  Strings[9]=Shader9;

  this->sortAndCompileShaders(10,Strings,Version,Profile);
  delete[]Strings;
}
ProgramObject::ProgramObject(
    GLenum Type0,std::string Shader0){
  this->createShaderProgram_Prologue();
  ShaderObject*S0=NULL;

  try{
    S0=new ShaderObject(Type0,Shader0);
  }catch(std::string&e){
    if(S0)delete S0;
    std::cerr<<e<<std::endl;
    return;
    //throw e;
  }

  glAttachShader(this->_id,S0->getId());
  this->_shaders.push_back(S0);
  this->createShaderProgram_Epilogue();
}
ProgramObject::ProgramObject(
    GLenum Type0,std::string Shader0,
    GLenum Type1,std::string Shader1){
  this->createShaderProgram_Prologue();
  ShaderObject*S0=NULL;
  ShaderObject*S1=NULL;

  try{
    S0=new ShaderObject(Type0,Shader0);
    S1=new ShaderObject(Type1,Shader1);
  }catch(std::string&e){
    if(S0)delete S0;
    if(S1)delete S1;
    std::cerr<<e<<std::endl;
    return;
    //throw e;
  }

  glAttachShader(this->_id,S0->getId());
  glAttachShader(this->_id,S1->getId());
  this->_shaders.push_back(S0);
  this->_shaders.push_back(S1);
  this->createShaderProgram_Epilogue();

}
ProgramObject::ProgramObject(
    GLenum Type0,std::string Shader0,
    GLenum Type1,std::string Shader1,
    GLenum Type2,std::string Shader2){
  this->createShaderProgram_Prologue();
  ShaderObject*S0=NULL;
  ShaderObject*S1=NULL;
  ShaderObject*S2=NULL;

  try{
    S0=new ShaderObject(Type0,Shader0);
    S1=new ShaderObject(Type1,Shader1);
    S2=new ShaderObject(Type2,Shader2);
  }catch(std::string&e){
    if(S0)delete S0;
    if(S1)delete S1;
    if(S2)delete S2;
    std::cerr<<e<<std::endl;
    return;
    //throw e;
  }

  glAttachShader(this->_id,S0->getId());
  glAttachShader(this->_id,S1->getId());
  glAttachShader(this->_id,S2->getId());
  this->_shaders.push_back(S0);
  this->_shaders.push_back(S1);
  this->_shaders.push_back(S2);
  this->createShaderProgram_Epilogue();
}
ProgramObject::ProgramObject(
    GLenum Type0,std::string Shader0,
    GLenum Type1,std::string Shader1,
    GLenum Type2,std::string Shader2,
    GLenum Type3,std::string Shader3){
  this->createShaderProgram_Prologue();
  ShaderObject*S0=NULL;
  ShaderObject*S1=NULL;
  ShaderObject*S2=NULL;
  ShaderObject*S3=NULL;

  try{
    S0=new ShaderObject(Type0,Shader0);
    S1=new ShaderObject(Type1,Shader1);
    S2=new ShaderObject(Type2,Shader2);
    S3=new ShaderObject(Type3,Shader3);
  }catch(std::string&e){
    if(S0)delete S0;
    if(S1)delete S1;
    if(S2)delete S2;
    if(S3)delete S3;
    std::cerr<<e<<std::endl;
    return;
    //throw e;
  }

  glAttachShader(this->_id,S0->getId());
  glAttachShader(this->_id,S1->getId());
  glAttachShader(this->_id,S2->getId());
  glAttachShader(this->_id,S3->getId());
  this->_shaders.push_back(S0);
  this->_shaders.push_back(S1);
  this->_shaders.push_back(S2);
  this->_shaders.push_back(S3);
  this->createShaderProgram_Epilogue();
}
ProgramObject::ProgramObject(
    GLenum Type0,std::string Shader0,
    GLenum Type1,std::string Shader1,
    GLenum Type2,std::string Shader2,
    GLenum Type3,std::string Shader3,
    GLenum Type4,std::string Shader4){
  this->createShaderProgram_Prologue();
  ShaderObject*S0=NULL;
  ShaderObject*S1=NULL;
  ShaderObject*S2=NULL;
  ShaderObject*S3=NULL;
  ShaderObject*S4=NULL;

  try{
    S0=new ShaderObject(Type0,Shader0);
    S1=new ShaderObject(Type1,Shader1);
    S2=new ShaderObject(Type2,Shader2);
    S3=new ShaderObject(Type3,Shader3);
    S4=new ShaderObject(Type4,Shader4);
  }catch(std::string&e){
    if(S0)delete S0;
    if(S1)delete S1;
    if(S2)delete S2;
    if(S3)delete S3;
    if(S4)delete S4;
    std::cerr<<e<<std::endl;
    return;
    //throw e;
  }

  glAttachShader(this->_id,S0->getId());
  glAttachShader(this->_id,S1->getId());
  glAttachShader(this->_id,S2->getId());
  glAttachShader(this->_id,S3->getId());
  glAttachShader(this->_id,S4->getId());
  this->_shaders.push_back(S0);
  this->_shaders.push_back(S1);
  this->_shaders.push_back(S2);
  this->_shaders.push_back(S3);
  this->_shaders.push_back(S4);
  this->createShaderProgram_Epilogue();
}
void ProgramObject::setVersion(unsigned Version,std::string Profile){
  for(unsigned s=0;s<this->_shaders.size();++s)
    this->_shaders[s]->setVersion(Version,Profile);
}

void ProgramObject::setVersion(GLenum Type,unsigned Version,std::string Profile){
  for(unsigned s=0;s<this->_shaders.size();++s){
    if(this->_shaders[s]->getType()==Type){
      this->_shaders[s]->setVersion(Version,Profile);
    }
  }
}

void ProgramObject::appendAfterVersion(std::string Defs){
  for(unsigned s=0;s<this->_shaders.size();++s)
    this->_shaders[s]->appendAfterVersion(Defs);
}

void ProgramObject::appendAfterVersion(GLenum Type,std::string Defs){
  for(unsigned s=0;s<this->_shaders.size();++s){
    if(this->_shaders[s]->getType()==Type){
      this->_shaders[s]->appendAfterVersion(Defs);
    }
  }
}

void ProgramObject::deleteProgram(){
  for(unsigned i=0;i<this->_shaders.size();++i)//loop over shader objects
    glDetachShader(this->_id,this->_shaders[i]->getId());//detach shader
  glDeleteProgram(this->_id);//deletes shader program
  this->_attributeList.clear();
  this->_uniformList.clear();
}

void ProgramObject::relink(){
  this->deleteProgram();//delete previous program

  this->createShaderProgram_Prologue();//create new program

  for(unsigned s=0;s<this->_shaders.size();++s){
    this->_shaders[s]->recompile();//recompile shaders
    glAttachShader(this->_id,this->_shaders[s]->getId());//attach shader
  }

  this->createShaderProgram_Epilogue();//get attribs and uniforms,...
}


ProgramObject::ProgramObject(unsigned Num,...){
  this->createShaderProgram_Prologue();//prologue of creating of shader prg.
  va_list args;//arguments
  va_start(args,Num);//start point of arguments
  for(size_t i=0;i<Num;++i){//loop over arguments
    ShaderObject*Shader=(ShaderObject*)va_arg(args,ShaderObject*);
    glAttachShader(//attach shader object to shader program
        this->_id,//shader program
        Shader->getId());
    this->_shaders.push_back(Shader);
  }
  va_end(args);//end point of arguments
  this->createShaderProgram_Epilogue();//epilogue of creating of shader prg.
}

ProgramObject::ProgramObject(ShaderObject**Shader,unsigned Num){
  this->createShaderProgram_Prologue();//prologue of creating of shader prg.
  for(unsigned i=0;i<Num;++i){//loop over shaders
    glAttachShader(//attach shader object to shader program
        this->_id,//shader program
        Shader[i]->getId());
    this->_shaders.push_back(Shader[i]);
  }
  this->createShaderProgram_Epilogue();//epilogue of creating of shader prg.
}

ProgramObject::~ProgramObject(){
  this->deleteProgram();

  for(unsigned s=0;s<this->_shaders.size();++s)
    delete this->_shaders[s];

  //this->ShaderList.clear();//clear list of shader object
  //delete this->AttributeList;
  //delete this->UniformList;
}

GLint ProgramObject::operator[](std::string Name){
  return this->_uniformList[Name].location;//uniform id
}

GLint ProgramObject::getAttribute(std::string name){
  if(!this->_attributeList.count(name))return-1;
  return this->_attributeList[name].location;
}

GLenum ProgramObject::getAttributeType(std::string AttributeName){
  return this->_attributeList[AttributeName].type;
}

GLint ProgramObject::getAttributeSize(std::string AttributeName){
  return this->_attributeList[AttributeName].size;
}

GLint ProgramObject::getUniform(std::string UniformName){
  if(!this->_uniformList.count(UniformName))return-1;
  return this->_uniformList[UniformName].location;
}

GLenum ProgramObject::getUniformType(std::string UniformName){
  return this->_uniformList[UniformName].type;
}

GLint ProgramObject::getUniformSize(std::string UniformName){
  return this->_uniformList[UniformName].size;
}

unsigned ProgramObject::getNofBuffers(){
  return this->_bufferNames.size();
}
std::string ProgramObject::getBufferName(unsigned i){
  return this->_bufferNames[i];
}
GLuint ProgramObject::getBuffer(std::string name){
  if(!this->_bufferList.count(name))return-1;
  return this->_bufferList[name].getBinding();
}
GLint ProgramObject::getBufferProperty(
    std::string name,
    BufferParams::Properties property){
  if(!this->_bufferList.count(name))return 0;
  return this->_bufferList[name].getProperty(property);
}
BufferParams ProgramObject::getBufferParams(std::string name){
  return this->_bufferList[name];
}
void ProgramObject::bindSSBO(std::string name,ge::gl::BufferObject*buffer){
  buffer->bindBase(GL_SHADER_STORAGE_BUFFER,this->getBuffer(name));
}
void ProgramObject::bindSSBO(std::string name,ge::gl::BufferObject*buffer,GLintptr offset,GLsizeiptr size){
  buffer->bindRange(GL_SHADER_STORAGE_BUFFER,this->getBuffer(name),offset,size);
}
/*
unsigned ProgramObject::getSamplerBinding(std::string uniform){
  return this->_samplerBindings[uniform];
}
*/
void ProgramObject::bindTexture(std::string uniform,ge::gl::TextureObject*texture){
  texture->bind(GL_TEXTURE0+this->_samplerList[uniform].getBinding());
}

void ProgramObject::use(){
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
ShaderObjectParameter param=this->_uniformList[name];\
int index=this->_##TYPE##MatrixType2Index(param.type);\
if(index<0)return;\

#define MATRIXBODY(FCE,TYPE)\
  MATRIXBODYA(TYPE)\
FCE[index](param.location,count,transpose,value);

#define MATRIXBODYDSA(FCE,TYPE)\
  MATRIXBODYA(TYPE)\
FCE[index](this->_id,param.location,count,transpose,value);


void ProgramObject::set(
    std::string   name,
    GLsizei       count,
    GLboolean     transpose,
    const GLfloat*value){
  MATRIXBODY(matrixfFce,float)
}

void ProgramObject::set(
    std::string    name,
    GLsizei        count,
    GLboolean      transpose,
    const GLdouble*value){
  MATRIXBODY(matrixdFce,double)
}

void ProgramObject::setdsa(
    std::string   name,
    GLsizei       count,
    GLboolean     transpose,
    const GLfloat*value){
  MATRIXBODYDSA(matrixfFceDsa,float)
}

void ProgramObject::setdsa(
    std::string    name,
    GLsizei        count,
    GLboolean      transpose,
    const GLdouble*value){
  MATRIXBODYDSA(matrixdFceDsa,double)
}

  DEFFCE(1,f)
  DEFFCE(2,f)
  DEFFCE(3,f)
  DEFFCE(4,f)
  DEFFCE(1,d)
  DEFFCE(2,d)
  DEFFCE(3,d)
  DEFFCE(4,d)
  DEFFCE(1,i)
  DEFFCE(2,i)
  DEFFCE(3,i)
  DEFFCE(4,i)
  DEFFCE(1,ui)
  DEFFCE(2,ui)
  DEFFCE(3,ui)
  DEFFCE(4,ui)
  DEFFCE(1,boolean)
  DEFFCE(2,boolean)
  DEFFCE(3,boolean)
  DEFFCE(4,boolean)
  DEFFCEV(f)
  DEFFCEV(d)
  DEFFCEV(i)
  DEFFCEV(ui)
DEFFCEV(boolean)


  DEFDSAFCE(1,f)
  DEFDSAFCE(2,f)
  DEFDSAFCE(3,f)
  DEFDSAFCE(4,f)
  DEFDSAFCE(1,d)
  DEFDSAFCE(2,d)
  DEFDSAFCE(3,d)
  DEFDSAFCE(4,d)
  DEFDSAFCE(1,i)
  DEFDSAFCE(2,i)
  DEFDSAFCE(3,i)
  DEFDSAFCE(4,i)
  DEFDSAFCE(1,ui)
  DEFDSAFCE(2,ui)
  DEFDSAFCE(3,ui)
  DEFDSAFCE(4,ui)
  DEFDSAFCE(1,boolean)
  DEFDSAFCE(2,boolean)
  DEFDSAFCE(3,boolean)
  DEFDSAFCE(4,boolean)
  DEFDSAFCEV(f)
  DEFDSAFCEV(d)
  DEFDSAFCEV(i)
  DEFDSAFCEV(ui)
DEFDSAFCEV(boolean)

