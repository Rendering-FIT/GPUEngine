#include<geGL/ProgramObject.h>

namespace ge{
  namespace gl{
    bool OpenGL320=false;
    bool OpenGL400=false;
    bool OpenGL410=false;
    void initShadersAndPrograms(){
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




      if(!OpenGL320)throw      "OpenGL 3.2 is not available, missing: "+Result32;
      if(!OpenGL400)std::cerr<<"OpenGL 4.0 is not available, missing: "+Result40<<std::endl;
      if(!OpenGL410)std::cerr<<"OpenGL 4.1 is not available, missing: "+Result41<<std::endl;

    }
    GLenum complexType2SimpleType(GLenum type){
      switch(type){
        case GL_FLOAT            :return GL_FLOAT;
        case GL_FLOAT_VEC2       :return GL_FLOAT;
        case GL_FLOAT_VEC3       :return GL_FLOAT;
        case GL_FLOAT_VEC4       :return GL_FLOAT;
        case GL_DOUBLE           :return GL_DOUBLE;
        case GL_DOUBLE_VEC2      :return GL_DOUBLE;
        case GL_DOUBLE_VEC3      :return GL_DOUBLE;
        case GL_DOUBLE_VEC4      :return GL_DOUBLE;
        case GL_INT              :return GL_INT;
        case GL_INT_VEC2         :return GL_INT;
        case GL_INT_VEC3         :return GL_INT;
        case GL_INT_VEC4         :return GL_INT;
        case GL_UNSIGNED_INT     :return GL_UNSIGNED_INT;
        case GL_UNSIGNED_INT_VEC2:return GL_UNSIGNED_INT;
        case GL_UNSIGNED_INT_VEC3:return GL_UNSIGNED_INT;
        case GL_UNSIGNED_INT_VEC4:return GL_UNSIGNED_INT;
        case GL_BOOL             :return GL_BOOL;
        case GL_BOOL_VEC2        :return GL_BOOL;
        case GL_BOOL_VEC3        :return GL_BOOL;
        case GL_BOOL_VEC4        :return GL_BOOL;
        default                  :return GL_FLOAT;//GL_FALSE glbinding...
      }
    }

    GLint complexType2Size(GLenum type){
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
        default:return 0;
      }
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
      if(!OpenGL320)throw std::string("OpenGL 3.2 not available");
      this->_id=glCreateProgram();//creates a shader program
      if(!this->_id)//something is wrong
        throw std::string("glCreateProgram failed");//+GetGLError());//error message
      //this->AttributeList=new std::map<std::string,ShaderObjectParameter>();
      //this->UniformList=new std::map<std::string,int>();
    }

    void ProgramObject::createShaderProgram_Epilogue(){
      glLinkProgram(this->_id);//link shader program
      std::cerr<<this->getProgramInfo(this->_id);
      GLint Status;//status of linking
      glGetProgramiv(this->_id,GL_LINK_STATUS,&Status);//status
      if((GLboolean)Status==GL_FALSE)//something is wrong
        throw std::string("Shader linking failed");//+GetGLError());//error message
      this->getParameterList();//get list of shader program parameter

      if(OpenGL400)
        this->getSubroutineUniformList();

      bool HasComputeShader=false;
      //for(unsigned i=0;i<this->ShaderList.size();++i){
      for(unsigned i=0;i<this->_shaders.size();++i){
        GLenum Type=GL_VERTEX_SHADER;
        GLuint Shader=this->_shaders[i]->getId();
        glGetShaderiv(Shader,GL_SHADER_TYPE,(GLint*)&Type);
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
      GETACTIVEFCE   getActive[2]   = {
        (GETACTIVEFCE)glGetActiveAttrib,
        (GETACTIVEFCE)glGetActiveUniform};
      GETLOCATIONFCE getLocation[2] = {
        (GETLOCATIONFCE)glGetAttribLocation,
        (GETLOCATIONFCE)glGetUniformLocation};
      GLenum Active[2]={
        GL_ACTIVE_ATTRIBUTES,
        GL_ACTIVE_UNIFORMS};
      GLenum MaxLenght[2]={
        GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
        GL_ACTIVE_UNIFORM_MAX_LENGTH};
      for(int t=0;t<2;++t){//loop over set of types {attribute,uniform}
        GLint Num;//number of active parameter
        glGetProgramiv(this->_id,Active[t],&Num);//number
        if(!Num)continue;//there are no active parameters
        GLint BufLen;//length of the longest attribute name
        glGetProgramiv(this->_id,MaxLenght[t],&BufLen);
        char*Buffer=new char[BufLen+1];//alocate buffer
        for(GLint i=0;i<Num;++i){//loop over active parameter
          GLenum Type;//type of parameter
          GLint Size;//size of parameter
          std::string Name;//name of parameter
          GLint Location;//location of parameter
          GLsizei Length;
          getActive[t](this->_id,i,BufLen,&Length,&Size,&Type,Buffer);
          Name=std::string(Buffer);//convert buffer to string
          if(Name.find("[0]")!=std::string::npos){
            //std::cerr<<"####"<<Name<<std::endl;
            Name.erase(Name.end()-3,Name.end());
            //std::cerr<<"####"<<Name<<std::endl;
          }

          //if(Size>1)Buffer[Length-3]='\0';//get rid of [0] part
          Location=getLocation[t](this->_id,Name.c_str());//location
          //std::cerr<<Name<<" : "<<Location<<std::endl;
          //std::cerr<<"Name: "<<Name<<std::endl;
          ShaderObjectParameter Param=ShaderObjectParameter(Location,Type,Name,Size);//param
          if(t==0)this->_attributeList.insert(
              std::pair<std::string,ShaderObjectParameter>(Name,Param));
          else this->_uniformList.insert(
              std::pair<std::string,ShaderObjectParameter>(Name,Param));
        }
        delete[]Buffer;//free buffer
      }
    }
    void ProgramObject::getSubroutineUniformList(){
      GLenum ShaderType[]={
        GL_VERTEX_SHADER,
        GL_TESS_CONTROL_SHADER,
        GL_TESS_EVALUATION_SHADER,
        GL_GEOMETRY_SHADER,
        GL_FRAGMENT_SHADER,
        GL_COMPUTE_SHADER
      };
      for(int i=0;i<6;++i){//loop over shader types
        GLint NumSubroutines;//number of subroutines in this shader
        GLsizei MaxSubroutineNameSize;//max legth of name of subroutine
        glGetProgramStageiv(this->_id,ShaderType[i],//get number of sub.
            GL_ACTIVE_SUBROUTINES,&NumSubroutines);
        if(NumSubroutines>0){//there are subroutines
          glGetProgramStageiv(this->_id,ShaderType[i],//max lenght
              GL_ACTIVE_SUBROUTINE_MAX_LENGTH,&MaxSubroutineNameSize);
          char*BufferName=new char[MaxSubroutineNameSize];//allocate buffer

          for(int sub=0;sub<NumSubroutines;++sub){//loop over subroutines
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

        GLint NumSubroutineUniforms;//number of subroutine uniforms
        GLint MaxSubroutineUniformNameSize;//max legth of subroutine uniforms

        glGetProgramStageiv(this->_id,ShaderType[i],//get number
            GL_ACTIVE_SUBROUTINE_UNIFORMS,&NumSubroutineUniforms);
        if(NumSubroutineUniforms){//there are subroutine uniforms
          unsigned ActIndex=0;
          glGetProgramStageiv(this->_id,ShaderType[i],//get lenght
              GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH,&MaxSubroutineUniformNameSize);
          char*BufferName=new char[MaxSubroutineNameSize];//allocate buffer
          for(int sub=0;sub<NumSubroutineUniforms;++sub){
            GLint Size;
            glGetActiveSubroutineUniformiv(this->_id,ShaderType[i],sub,
                GL_UNIFORM_SIZE,&Size);
            GLsizei Length;
            glGetActiveSubroutineUniformName(this->_id,ShaderType[i],sub,
                MaxSubroutineUniformNameSize,&Length,BufferName);//obtain name
            //if(Size>1)BufferName[Length-3]='\0';
            std::string Name=std::string(BufferName);//convert buffer to string
            if(Name.find("[0]")!=std::string::npos){
              //std::cerr<<"####"<<Name<<std::endl;
              Name.erase(Name.end()-3,Name.end());
              //std::cerr<<"####"<<Name<<std::endl;
            }
            GLint NumCompatible;
            glGetActiveSubroutineUniformiv(this->_id,ShaderType[i],sub,
                GL_NUM_COMPATIBLE_SUBROUTINES,&NumCompatible);
            GLuint Location;
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
    void ProgramObject::setSubroutine(
        GLenum ShaderType,
        std::string Uniform,
        unsigned OffSet,
        std::string SubroutineName){
      int WH=0;
      switch(ShaderType){
        case GL_VERTEX_SHADER:WH=0;break;
        case GL_TESS_CONTROL_SHADER:WH=1;break;
        case GL_TESS_EVALUATION_SHADER:WH=2;break;
        case GL_GEOMETRY_SHADER:WH=3;break;
        case GL_FRAGMENT_SHADER:WH=4;break;
        case GL_COMPUTE_SHADER:WH=5;break;
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
        throw e;//send error message
      }
      for(unsigned s=0;s<NumShaders;++s){
        glAttachShader(this->_id,S[s]->getId());
        this->_shaders.push_back(S[s]);
      }
      delete[]S;//free shaders array
      this->createShaderProgram_Epilogue();//gets attributes and uniforms
    }

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
            throw std::string("bad arguments");//throw error
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
        throw e;
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
        throw e;
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
        throw e;
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
        throw e;
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
        throw e;
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
      for(int i=0;i<this->_shaders.size();++i)//loop over shader objects
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

    GLuint ProgramObject::getAttribute(std::string AttributeName){
      return this->_attributeList[AttributeName].location;
    }

    GLenum ProgramObject::getAttributeType(std::string AttributeName){
      return this->_attributeList[AttributeName].type;
    }

    GLint ProgramObject::getAttributeSize(std::string AttributeName){
      return this->_attributeList[AttributeName].size;
    }

    GLuint ProgramObject::getUniform(std::string UniformName){
      return this->_uniformList[UniformName].location;
    }

    GLenum ProgramObject::getUniformType(std::string UniformName){
      return this->_uniformList[UniformName].type;
    }

    GLint ProgramObject::getUniformSize(std::string UniformName){
      return this->_uniformList[UniformName].size;
    }

    void ProgramObject::use(){
      glUseProgram(this->_id);
    }
    DEFFCE(1,f);
    DEFFCE(2,f);
    DEFFCE(3,f);
    DEFFCE(4,f);
    DEFFCE(1,d);
    DEFFCE(2,d);
    DEFFCE(3,d);
    DEFFCE(4,d);
    DEFFCE(1,i);
    DEFFCE(2,i);
    DEFFCE(3,i);
    DEFFCE(4,i);
    DEFFCE(1,ui);
    DEFFCE(2,ui);
    DEFFCE(3,ui);
    DEFFCE(4,ui);
    DEFFCE(1,boolean);
    DEFFCE(2,boolean);
    DEFFCE(3,boolean);
    DEFFCE(4,boolean);
    DEFFCEV(f);
    DEFFCEV(d);
    DEFFCEV(i);
    DEFFCEV(ui);
    DEFFCEV(boolean);


    void ProgramObject::set(
        std::string UniformName,
        GLsizei Count,
        GLboolean Transpose,
        GLfloat*Value){
      ShaderObjectParameter Param=this->_uniformList[UniformName];
      switch(Param.type){
        case GL_FLOAT_MAT2:
          glUniformMatrix2fv(Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT3:
          glUniformMatrix3fv(Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT4:
          glUniformMatrix4fv(Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT2x3:
          glUniformMatrix2x3fv(Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT3x2:
          glUniformMatrix3x2fv(Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT2x4:
          glUniformMatrix2x4fv(Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT4x2:
          glUniformMatrix4x2fv(Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT3x4:
          glUniformMatrix3x4fv(Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT4x3:
          glUniformMatrix4x3fv(Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        default:
          break;
      }
    }
    void ProgramObject::set(
        std::string  uniformName,
        GLsizei      count,
        GLboolean    transpose,
        GLdouble    *value){
      ShaderObjectParameter param=this->_uniformList[uniformName];
      switch(param.type){
        case GL_DOUBLE_MAT2:
          glUniformMatrix2dv  (param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT3:
          glUniformMatrix3dv  (param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT4:
          glUniformMatrix4dv  (param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT2x3:
          glUniformMatrix2x3dv(param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT3x2:
          glUniformMatrix3x2dv(param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT2x4:
          glUniformMatrix2x4dv(param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT4x2:
          glUniformMatrix4x2dv(param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT3x4:
          glUniformMatrix3x4dv(param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT4x3:
          glUniformMatrix4x3dv(param.location,count,transpose,(const GLdouble*)value);
          break;
        default:
          break;
      }
    }

    DEFDSAFCE(1,f);
    DEFDSAFCE(2,f);
    DEFDSAFCE(3,f);
    DEFDSAFCE(4,f);
    DEFDSAFCE(1,d);
    DEFDSAFCE(2,d);
    DEFDSAFCE(3,d);
    DEFDSAFCE(4,d);
    DEFDSAFCE(1,i);
    DEFDSAFCE(2,i);
    DEFDSAFCE(3,i);
    DEFDSAFCE(4,i);
    DEFDSAFCE(1,ui);
    DEFDSAFCE(2,ui);
    DEFDSAFCE(3,ui);
    DEFDSAFCE(4,ui);
    DEFDSAFCE(1,boolean);
    DEFDSAFCE(2,boolean);
    DEFDSAFCE(3,boolean);
    DEFDSAFCE(4,boolean);
    DEFDSAFCEV(f);
    DEFDSAFCEV(d);
    DEFDSAFCEV(i);
    DEFDSAFCEV(ui);
    DEFDSAFCEV(boolean);


    void ProgramObject::setdsa(
        std::string UniformName,
        GLsizei Count,
        GLboolean Transpose,
        GLfloat*Value){
      ShaderObjectParameter Param=this->_uniformList[UniformName];
      switch(Param.type){
        case GL_FLOAT_MAT2:
          glProgramUniformMatrix2fv  (this->_id,Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT3:
          glProgramUniformMatrix3fv  (this->_id,Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT4:
          glProgramUniformMatrix4fv  (this->_id,Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT2x3:
          glProgramUniformMatrix2x3fv(this->_id,Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT3x2:
          glProgramUniformMatrix3x2fv(this->_id,Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT2x4:
          glProgramUniformMatrix2x4fv(this->_id,Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT4x2:
          glProgramUniformMatrix4x2fv(this->_id,Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT3x4:
          glProgramUniformMatrix3x4fv(this->_id,Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        case GL_FLOAT_MAT4x3:
          glProgramUniformMatrix4x3fv(this->_id,Param.location,Count,Transpose,(const GLfloat*)Value);
          break;
        default:
          break;
      }
    }
    void ProgramObject::setdsa(
        std::string  uniformName,
        GLsizei      count,
        GLboolean    transpose,
        GLdouble    *value){
      ShaderObjectParameter param=this->_uniformList[uniformName];
      switch(param.type){
        case GL_DOUBLE_MAT2:
          glProgramUniformMatrix2dv  (this->_id,param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT3:
          glProgramUniformMatrix3dv  (this->_id,param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT4:
          glProgramUniformMatrix4dv  (this->_id,param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT2x3:
          glProgramUniformMatrix2x3dv(this->_id,param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT3x2:
          glProgramUniformMatrix3x2dv(this->_id,param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT2x4:
          glProgramUniformMatrix2x4dv(this->_id,param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT4x2:
          glProgramUniformMatrix4x2dv(this->_id,param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT3x4:
          glProgramUniformMatrix3x4dv(this->_id,param.location,count,transpose,(const GLdouble*)value);
          break;
        case GL_DOUBLE_MAT4x3:
          glProgramUniformMatrix4x3dv(this->_id,param.location,count,transpose,(const GLdouble*)value);
          break;
        default:
          break;
      }
    }

  }//gl
}//ge

