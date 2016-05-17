#pragma once

#include<geGL/OpenGLObject.h>
#include<stdarg.h>
#include<vector>
#include<map>
#include<set>
#include<geGL/ShaderObject.h>
#include<geGL/ProgramObjectParameter.h>
#include<geGL/ProgramObjectSubroutine.h>
#include<geGL/ProgramObjectMacro.h>
#include<geGL/Buffer.h>
#include<geGL/Texture.h>
#include<geCore/Dtemplates.h>

namespace ge{
  namespace gl{
    GEGL_EXPORT GLenum complexType2SimpleType(GLenum Type);
    GEGL_EXPORT GLint  complexType2Size(GLenum Type);
    class GEGL_EXPORT ProgramObject: public OpenGLObject{
      public:
        using AttributeMap = std::map<std::string,std::shared_ptr<ProgramObjectParameter>>;
        using UniformMap = std::map<std::string,std::shared_ptr<ProgramObjectParameter>>;
        using BufferMap = std::map<std::string,std::shared_ptr<ProgramObjectBufferParams>>;
        using AttributeIndex = AttributeMap::size_type;
        using UniformIndex = UniformMap::size_type;
        using BufferIndex = BufferMap::size_type;

        template<typename...ARGS>
          ProgramObject(ARGS...args){
            this->_resolveConstructorArgs(args...);
          }
        ProgramObject(std::vector<std::string>const&data,unsigned version = 450,std::string profile = "core");
        template<typename...ARGS>
          ProgramObject(
              opengl::FunctionTablePointer const&table,
              ARGS...args):OpenGLObject(table){
            this->_resolveConstructorArgs(args...);
          }
        ProgramObject(
            opengl::FunctionTablePointer const&table,
            std::vector<std::string>const&data,
            unsigned version = 450,
            std::string profile = "core");
        ~ProgramObject();
        void attachShader(std::shared_ptr<ShaderObject>const&shader);
        void detachShader(std::shared_ptr<ShaderObject>const&shader);
        std::string uniformsToStr();
        GLint workGroupSize[3];///< work group size
        void setSeparable    ();
        void resetSeparable  ();
        void setRetrievable  ();
        void resetRetrievable();

        void setVersion(unsigned version,std::string profile);
        void setVersion(GLenum type,unsigned version,std::string profile);
        void appendAfterVersion(std::string defs);
        void appendAfterVersion(GLenum type,std::string defs);
        ProgramObjectParameter    const&getUniform  (std::string name,bool printErrors = false)const;
        ProgramObjectParameter    const&getAttribute(std::string name,bool printErrors = false)const;
        ProgramObjectBufferParams const&getBuffer   (std::string name,bool printErrors = false)const;
        UniformIndex   getNofUniforms  ()const;
        AttributeIndex getNofAttributes()const;
        BufferIndex    getNofBuffers   ()const;
        void use()const;
        void bindSSBO(std::string name,ge::gl::Buffer*buffer);
        void bindSSBO(std::string name,ge::gl::Buffer*buffer,GLintptr offset,GLsizeiptr size);
        GLenum getSamplerBinding(std::string uniform);
        void bindTexture(std::string uniform,ge::gl::Texture*texture);
        void bindImage(
            std::string           uniform                ,
            ge::gl::Texture*texture                ,
            GLint                 level   = 0            ,
            GLenum                format  = 0            ,
            GLenum                access  = GL_READ_WRITE,
            GLboolean             layered = GL_FALSE     ,
            GLint                 layer   = 0            );

        void setSubroutine(GLenum shader,std::string uniform,unsigned offSet,std::string subroutine);
        void set(std::string name,GLsizei count,GLboolean transpose,const GLfloat*value);
        void set(std::string name,GLsizei count,GLboolean transpose,const GLdouble*value);
        void setdsa(std::string name,GLsizei count,GLboolean transpose,const GLfloat*value);
        void setdsa(std::string name,GLsizei count,GLboolean transpose,const GLdouble*value);
        void set(std::string name,GLfloat v0);
        void set(std::string name,GLfloat v0,GLfloat v1);
        void set(std::string name,GLfloat v0,GLfloat v1,GLfloat v2);
        void set(std::string name,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3);
        void set(std::string name,GLdouble v0);
        void set(std::string name,GLdouble v0,GLdouble v1);
        void set(std::string name,GLdouble v0,GLdouble v1,GLdouble v2);
        void set(std::string name,GLdouble v0,GLdouble v1,GLdouble v2,GLdouble v3);
        void set(std::string name,GLint v0);
        void set(std::string name,GLint v0,GLint v1);
        void set(std::string name,GLint v0,GLint v1,GLint v2);
        void set(std::string name,GLint v0,GLint v1,GLint v2,GLint v3);
        void set(std::string name,GLuint v0);
        void set(std::string name,GLuint v0,GLuint v1);
        void set(std::string name,GLuint v0,GLuint v1,GLuint v2);
        void set(std::string name,GLuint v0,GLuint v1,GLuint v2,GLuint v3);
        void set(std::string name,GLboolean v0);
        void set(std::string name,GLboolean v0,GLboolean v1);
        void set(std::string name,GLboolean v0,GLboolean v1,GLboolean v2);
        void set(std::string name,GLboolean v0,GLboolean v1,GLboolean v2,GLboolean v3);
        void set(std::string name,GLsizei count,const GLfloat*  v);
        void set(std::string name,GLsizei count,const GLdouble* v);
        void set(std::string name,GLsizei count,const GLint*    v);
        void set(std::string name,GLsizei count,const GLuint*   v);
        void set(std::string name,GLsizei count,const GLboolean*v);
        void setdsa(std::string name,GLfloat v0);
        void setdsa(std::string name,GLfloat v0,GLfloat v1);
        void setdsa(std::string name,GLfloat v0,GLfloat v1,GLfloat v2);
        void setdsa(std::string name,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3);
        void setdsa(std::string name,GLdouble v0);
        void setdsa(std::string name,GLdouble v0,GLdouble v1);
        void setdsa(std::string name,GLdouble v0,GLdouble v1,GLdouble v2);
        void setdsa(std::string name,GLdouble v0,GLdouble v1,GLdouble v2,GLdouble v3);
        void setdsa(std::string name,GLint v0);
        void setdsa(std::string name,GLint v0,GLint v1);
        void setdsa(std::string name,GLint v0,GLint v1,GLint v2);
        void setdsa(std::string name,GLint v0,GLint v1,GLint v2,GLint v3);
        void setdsa(std::string name,GLuint v0);
        void setdsa(std::string name,GLuint v0,GLuint v1);
        void setdsa(std::string name,GLuint v0,GLuint v1,GLuint v2);
        void setdsa(std::string name,GLuint v0,GLuint v1,GLuint v2,GLuint v3);
        void setdsa(std::string name,GLboolean v0);
        void setdsa(std::string name,GLboolean v0,GLboolean v1);
        void setdsa(std::string name,GLboolean v0,GLboolean v1,GLboolean v2);
        void setdsa(std::string name,GLboolean v0,GLboolean v1,GLboolean v2,GLboolean v3);
        void setdsa(std::string name,GLsizei count,const GLfloat*  v);
        void setdsa(std::string name,GLsizei count,const GLdouble* v);
        void setdsa(std::string name,GLsizei count,const GLint*    v);
        void setdsa(std::string name,GLsizei count,const GLuint*   v);
        void setdsa(std::string name,GLsizei count,const GLboolean*v);
      private:
        int _floatMatrixType2Index(GLenum type);
        int _doubleMatrixType2Index(GLenum type);

        template<typename...     >void _typeStringConstructor();
        template<typename... ARGS>void _typeStringConstructor(GLenum type,std::string shader,ARGS...args);

        template<typename...     >void _sharedShaderConstructor();
        template<typename... ARGS>void _sharedShaderConstructor(std::shared_ptr<ShaderObject>const&shader,ARGS...args);

        template<typename...    >void _copyStringList2Vector(std::vector<std::string>&);
        template<typename TYPE  >void _copyStringList2Vector(std::vector<std::string>&,unsigned);
        template<typename...ARGS>void _copyStringList2Vector(std::vector<std::string>&vec,std::string shader,ARGS...args);

        template<typename...    >void _copyVersionProfile(unsigned&versionOut,std::string&profileOut,unsigned version = 0,std::string profile="");
        template<typename...ARGS>void _copyVersionProfile(unsigned&versionOut,std::string&profileOut,std::string,ARGS...args);

        template<typename...    >void _stringListConstructor();
        template<typename...ARGS>void _stringListConstructor(std::string shader,ARGS...args);

        template<typename...ARGS>void _resolveConstructorArgs(GLenum type,std::string shader,ARGS...args);
        template<typename...ARGS>void _resolveConstructorArgs(std::shared_ptr<ShaderObject>const&shader,ARGS...args);
        template<typename...ARGS>void _resolveConstructorArgs(std::string shader,ARGS...args);
      protected:
        std::set<std::shared_ptr<ShaderObject>>                         _shaders       ;///<list of shaders
        AttributeMap _attributeList ;///<list of attributes
        UniformMap   _uniformList   ;///<list of uniforms
        BufferMap    _bufferList    ;///<list of buffers
        std::vector<std::string>                   _bufferNames   ;///<list of buffer names
        std::shared_ptr<ShaderObjectSubroutine>    _subroutines[6];///<subroutines in shaders
        std::map<std::string,std::shared_ptr<SamplerParam>>_samplerList   ;///<sampler parameters
        void _createShaderProgram_Prologue();  ///<prologue of creating of shader prg.
        void _createShaderProgram_Epilogue();  ///<epilogue of creating of shader prg.
        void _getParameterList();              ///<obtain shader parameters
        void _getSubroutineUniformList();      ///<obtain shader subroutines
        void _getBufferList();                 ///<obtain shader buffers
        std::string _getProgramInfo(GLuint ID);///<obtain program info log
        void _deleteProgram();                 ///<delete shader program
        void _compileShaders(
            std::vector<std::string>shaders,
            std::vector<std::string>defs,
            unsigned     version,
            std::string  profile);
        void _sortAndCompileShaders(
            std::vector<std::string>strings,
            unsigned     version,
            std::string  profile);
    };


    template<typename...     >
      void ProgramObject::_typeStringConstructor(){}
    template<typename... ARGS>
      void ProgramObject::_typeStringConstructor(GLenum type,std::string shader,ARGS...args){
        std::shared_ptr<ShaderObject>s;
        try{
          s=std::make_shared<ShaderObject>(type,shader);
        }catch(std::string&e){
          std::cerr<<e<<std::endl;
          return;
        }
        this->attachShader(s);
        this->_typeStringConstructor(args...);
      }

    template<typename...>
      void ProgramObject::_sharedShaderConstructor(){}
    template<typename... ARGS>
      void ProgramObject::_sharedShaderConstructor(std::shared_ptr<ShaderObject>const&shader,ARGS...args){
        this->attachShader(shader);
        this->_sharedShaderConstructor(args...);
      }

    template<typename...>
      void ProgramObject::_copyStringList2Vector(std::vector<std::string>&){}
    template<typename TYPE>
      void ProgramObject::_copyStringList2Vector(std::vector<std::string>&,unsigned){}
    template<typename...ARGS>
      void ProgramObject::_copyStringList2Vector(std::vector<std::string>&vec,std::string shader,ARGS...args){
        vec.push_back(shader);
        this->_copyStringList2Vector(vec,args...);
      }

    template<typename...>
      void ProgramObject::_copyVersionProfile(unsigned&versionOut,std::string&profileOut,unsigned version,std::string profile){
        versionOut = version;
        profileOut = profile;
      }
    template<typename...ARGS>
      void ProgramObject::_copyVersionProfile(unsigned&versionOut,std::string&profileOut,std::string,ARGS...args){
        this->_copyVersionProfile(versionOut,profileOut,args...);
      }

    template<typename...>
      void ProgramObject::_stringListConstructor(){}
    template<typename...ARGS>
      void ProgramObject::_stringListConstructor(std::string shader,ARGS...args){
        std::vector<std::string>shaderStrings;
        unsigned version;
        std::string profile;
        this->_copyStringList2Vector(shaderStrings,shader,args...);
        this->_copyVersionProfile(version,profile,args...);
        this->_sortAndCompileShaders(shaderStrings,version,profile);
      }

    template<typename...ARGS>
      void ProgramObject::_resolveConstructorArgs(GLenum type,std::string shader,ARGS...args){
        this->_createShaderProgram_Prologue();
        this->_typeStringConstructor(type,shader,args...);
        this->_createShaderProgram_Epilogue();
      }
    template<typename...ARGS>
      void ProgramObject::_resolveConstructorArgs(std::shared_ptr<ShaderObject>const&shader,ARGS...args){
        this->_createShaderProgram_Prologue();
        this->_sharedShaderConstructor(shader,args...);
        this->_createShaderProgram_Epilogue();
      }
    template<typename...ARGS>
      void ProgramObject::_resolveConstructorArgs(std::string shader,ARGS...args){
        this->_stringListConstructor(shader,args...);
      }


  }//gl
}//ge

