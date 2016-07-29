#pragma once

#include<iostream>
#include<memory>
#include<set>
#include<map>

#include<geGL/Shader.h>
#include<geGL/ProgramInfo.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT Program: 
      public OpenGLObject,
      public std::enable_shared_from_this<Program>{
      friend class Shader;
      public:
        using ShaderPointer  = std::shared_ptr<Shader>;
        using ShaderPointers = std::vector<ShaderPointer>;
        Program(ShaderPointers const&shaders = {});
        Program(
            opengl::FunctionTablePointer const&table       ,
            ShaderPointers               const&shaders = {});
        ~Program();
        void create       ();
        void attachShaders(ShaderPointers const&shaders = {});
        void detachShaders(ShaderPointers const&shaders = {});
        void link         (ShaderPointers const&shaders = {});
        GLboolean isProgram()const;
        void use ()const;
        void validate()const;
        GLboolean getDeleteStatus()const;
        GLboolean getLinkStatus()const;
        GLboolean getValidateStatus()const;
        GLuint    getInfoLogLength()const;
        GLuint    getNofShaders()const;
        GLuint    getNofActiveAtomicCounterBuffers()const;
        GLuint    getNofActiveAttributes()const;
        GLuint    getActiveAttributeMaxLength()const;
        GLuint    getNofActiveUniforms()const;
        GLuint    getActiveUniformMaxLength()const;
        GLuint    getBinaryLength()const;
        void      getComputeWorkGroupSize(GLint*x);
        GLenum    getTransformFeedbackBufferMode()const;
        GLuint    getNofTransfromFeedbackVaryings()const;
        GLuint    getTransformFeedbackVaryingMaxLength()const;
        GLuint    getNofGeometryVerticesOut()const;
        GLenum    getGeometryInputType()const;
        GLenum    getGeometryOutputType()const;
        std::string getInfoLog()const;
        GLint getUniformLocation(std::string const&name)const;
        GLint getAttribLocation (std::string const&name)const;
        GLint getInterfaceParam(GLenum interface,GLenum pname)const;
        std::string getResourceName(GLenum interface,GLuint index)const;
        GLint getResourceParam(GLenum interface,GLenum pname,GLuint index)const;
        void set1f(std::string name,float v0                           ){glProgramUniform1f(this->_id,this->_getUniform(name),v0         );}
        void set2f(std::string name,float v0,float v1                  ){glProgramUniform2f(this->_id,this->_getUniform(name),v0,v1      );}
        void set3f(std::string name,float v0,float v1,float v2         ){glProgramUniform3f(this->_id,this->_getUniform(name),v0,v1,v2   );}
        void set4f(std::string name,float v0,float v1,float v2,float v3){glProgramUniform4f(this->_id,this->_getUniform(name),v0,v1,v2,v3);}
        void set1i(std::string name,int32_t v0                                 ){glProgramUniform1i(this->_id,this->_getUniform(name),v0         );}
        void set2i(std::string name,int32_t v0,int32_t v1                      ){glProgramUniform2i(this->_id,this->_getUniform(name),v0,v1      );}
        void set3i(std::string name,int32_t v0,int32_t v1,int32_t v2           ){glProgramUniform3i(this->_id,this->_getUniform(name),v0,v1,v2   );}
        void set4i(std::string name,int32_t v0,int32_t v1,int32_t v2,int32_t v3){glProgramUniform4i(this->_id,this->_getUniform(name),v0,v1,v2,v3);}
        void set1ui(std::string name,uint32_t v0                                    ){glProgramUniform1ui(this->_id,this->_getUniform(name),v0         );}
        void set2ui(std::string name,uint32_t v0,uint32_t v1                        ){glProgramUniform2ui(this->_id,this->_getUniform(name),v0,v1      );}
        void set3ui(std::string name,uint32_t v0,uint32_t v1,uint32_t v2            ){glProgramUniform3ui(this->_id,this->_getUniform(name),v0,v1,v2   );}
        void set4ui(std::string name,uint32_t v0,uint32_t v1,uint32_t v2,uint32_t v3){glProgramUniform4ui(this->_id,this->_getUniform(name),v0,v1,v2,v3);}
        void set1fv(std::string name,float const*v0,GLsizei count = 1){glProgramUniform1fv(this->_id,this->_getUniform(name),count,v0);}
        void set2fv(std::string name,float const*v0,GLsizei count = 1){glProgramUniform2fv(this->_id,this->_getUniform(name),count,v0);}
        void set3fv(std::string name,float const*v0,GLsizei count = 1){glProgramUniform3fv(this->_id,this->_getUniform(name),count,v0);}
        void set4fv(std::string name,float const*v0,GLsizei count = 1){glProgramUniform4fv(this->_id,this->_getUniform(name),count,v0);}
        void set1iv(std::string name,int32_t const*v0,GLsizei count = 1){glProgramUniform1iv(this->_id,this->_getUniform(name),count,v0);}
        void set2iv(std::string name,int32_t const*v0,GLsizei count = 1){glProgramUniform2iv(this->_id,this->_getUniform(name),count,v0);}
        void set3iv(std::string name,int32_t const*v0,GLsizei count = 1){glProgramUniform3iv(this->_id,this->_getUniform(name),count,v0);}
        void set4iv(std::string name,int32_t const*v0,GLsizei count = 1){glProgramUniform4iv(this->_id,this->_getUniform(name),count,v0);}
        void set1uiv(std::string name,uint32_t const*v0,GLsizei count = 1){glProgramUniform1uiv(this->_id,this->_getUniform(name),count,v0);}
        void set2uiv(std::string name,uint32_t const*v0,GLsizei count = 1){glProgramUniform2uiv(this->_id,this->_getUniform(name),count,v0);}
        void set3uiv(std::string name,uint32_t const*v0,GLsizei count = 1){glProgramUniform3uiv(this->_id,this->_getUniform(name),count,v0);}
        void set4uiv(std::string name,uint32_t const*v0,GLsizei count = 1){glProgramUniform4uiv(this->_id,this->_getUniform(name),count,v0);}
        void setMatrix4fv(std::string name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix4fv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix3fv(std::string name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix3fv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix2fv(std::string name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix2fv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix4x3fv(std::string name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix4x3fv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix4x2fv(std::string name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix4x2fv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix3x4fv(std::string name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix3x4fv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix3x2fv(std::string name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix3x2fv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix2x4fv(std::string name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix2x4fv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix2x3fv(std::string name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix2x3fv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix4dv(std::string name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix4dv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix3dv(std::string name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix3dv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix2dv(std::string name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix2dv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix4x3dv(std::string name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix4x3dv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix4x2dv(std::string name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix4x2dv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix3x4dv(std::string name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix3x4dv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix3x2dv(std::string name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix3x2dv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix2x4dv(std::string name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix2x4dv(this->_id,this->_getUniform(name),count,transpose,v0);}
        void setMatrix2x3dv(std::string name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE){glProgramUniformMatrix2x3dv(this->_id,this->_getUniform(name),count,transpose,v0);}
        std::shared_ptr<ProgramInfo> const&getInfo()const{return this->_info;}
      public:
        template<typename...ARGS>
          Program(ARGS...shaders);
        template<typename...ARGS>
          Program(
              opengl::FunctionTablePointer const&table  ,
              ARGS...                            shaders);
        template<typename...ARGS>
          void attachShaders(ARGS... shaders);
        template<typename...ARGS>
          void detachShaders(ARGS... shaders);
        template<typename...ARGS>
          void link         (ARGS... shaders);
      protected:
        std::set<ShaderPointer>_shaders;
        GLint _getParam(GLenum pname)const;
        std::map<std::string,GLint>_name2Uniform;
        GLint _getUniform(std::string name);
        std::shared_ptr<ProgramInfo> _info;
        void _fillUniformInfo();
        void _fillAttribInfo();
        void _fillBufferInfo();
        void _fillInfo();
        std::string _chopIndexingInPropertyName(std::string name)const;
      };

    template<typename...ARGS>
      Program::Program(ARGS...shaders):Program(ShaderPointers({shaders...})){}
    template<typename...ARGS>
      Program::Program(
          opengl::FunctionTablePointer const&table  ,
          ARGS...                            shaders):Program(table,ShaderPointers({shaders...})){}
    template<typename...ARGS>
      void Program::attachShaders(ARGS... shaders){
        assert(this!=nullptr);
        this->attachShaders(ShaderPointers({shaders...}));
      }
    template<typename...ARGS>
      void Program::detachShaders(ARGS... shaders){
        assert(this!=nullptr);
        this->detachShaders(ShaderPointers({shaders...}));
      }
    template<typename...ARGS>
      void Program::link(ARGS... shaders){
        assert(this!=nullptr);
        this->link(ShaderPointers({shaders...}));
      }

  }
}
