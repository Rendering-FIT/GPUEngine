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
        Program(ShaderPointers const&shaders);
        Program(
            FunctionTablePointer const&table       ,
            ShaderPointers       const&shaders = {});
        Program(Program const&) = delete;
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
        GLint getInterfaceParam(GLenum interf,GLenum pname)const;
        std::string getResourceName(GLenum interf,GLuint index)const;
        GLint getResourceParam(GLenum interf,GLenum pname,GLuint index)const;
        void set1f(std::string const&name,float v0                           );
        void set2f(std::string const&name,float v0,float v1                  );
        void set3f(std::string const&name,float v0,float v1,float v2         );
        void set4f(std::string const&name,float v0,float v1,float v2,float v3);
        void set1i(std::string const&name,int32_t v0                                 );
        void set2i(std::string const&name,int32_t v0,int32_t v1                      );
        void set3i(std::string const&name,int32_t v0,int32_t v1,int32_t v2           );
        void set4i(std::string const&name,int32_t v0,int32_t v1,int32_t v2,int32_t v3);
        void set1ui(std::string const&name,uint32_t v0                                    );
        void set2ui(std::string const&name,uint32_t v0,uint32_t v1                        );
        void set3ui(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2            );
        void set4ui(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2,uint32_t v3);
        void set1fv(std::string const&name,float const*v0,GLsizei count = 1);
        void set2fv(std::string const&name,float const*v0,GLsizei count = 1);
        void set3fv(std::string const&name,float const*v0,GLsizei count = 1);
        void set4fv(std::string const&name,float const*v0,GLsizei count = 1);
        void set1iv(std::string const&name,int32_t const*v0,GLsizei count = 1);
        void set2iv(std::string const&name,int32_t const*v0,GLsizei count = 1);
        void set3iv(std::string const&name,int32_t const*v0,GLsizei count = 1);
        void set4iv(std::string const&name,int32_t const*v0,GLsizei count = 1);
        void set1uiv(std::string const&name,uint32_t const*v0,GLsizei count = 1);
        void set2uiv(std::string const&name,uint32_t const*v0,GLsizei count = 1);
        void set3uiv(std::string const&name,uint32_t const*v0,GLsizei count = 1);
        void set4uiv(std::string const&name,uint32_t const*v0,GLsizei count = 1);
        void setMatrix4fv(std::string const&name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix3fv(std::string const&name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix2fv(std::string const&name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix4x3fv(std::string const&name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix4x2fv(std::string const&name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix3x4fv(std::string const&name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix3x2fv(std::string const&name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix2x4fv(std::string const&name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix2x3fv(std::string const&name,float const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix4dv(std::string const&name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix3dv(std::string const&name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix2dv(std::string const&name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix4x3dv(std::string const&name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix4x2dv(std::string const&name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix3x4dv(std::string const&name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix3x2dv(std::string const&name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix2x4dv(std::string const&name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void setMatrix2x3dv(std::string const&name,double const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE);
        void set(std::string const&name,float v0                           );
        void set(std::string const&name,float v0,float v1                  );
        void set(std::string const&name,float v0,float v1,float v2         );
        void set(std::string const&name,float v0,float v1,float v2,float v3);
        void set(std::string const&name,int32_t v0                                 );
        void set(std::string const&name,int32_t v0,int32_t v1                      );
        void set(std::string const&name,int32_t v0,int32_t v1,int32_t v2           );
        void set(std::string const&name,int32_t v0,int32_t v1,int32_t v2,int32_t v3);
        void set(std::string const&name,uint32_t v0                                    );
        void set(std::string const&name,uint32_t v0,uint32_t v1                        );
        void set(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2            );
        void set(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2,uint32_t v3);
        void set1v(std::string const&name,float const*v0,GLsizei count = 1);
        void set2v(std::string const&name,float const*v0,GLsizei count = 1);
        void set3v(std::string const&name,float const*v0,GLsizei count = 1);
        void set4v(std::string const&name,float const*v0,GLsizei count = 1);
        void set1v(std::string const&name,int32_t const*v0,GLsizei count = 1);
        void set2v(std::string const&name,int32_t const*v0,GLsizei count = 1);
        void set3v(std::string const&name,int32_t const*v0,GLsizei count = 1);
        void set4v(std::string const&name,int32_t const*v0,GLsizei count = 1);
        void set1v(std::string const&name,uint32_t const*v0,GLsizei count = 1);
        void set2v(std::string const&name,uint32_t const*v0,GLsizei count = 1);
        void set3v(std::string const&name,uint32_t const*v0,GLsizei count = 1);
        void set4v(std::string const&name,uint32_t const*v0,GLsizei count = 1);

        std::shared_ptr<ProgramInfo> const&getInfo()const{return this->_info;}
        static void setNonexistingUniformWarning(bool enableWarning = true);
        static bool isNonexistingUniformWarningEnabled();
      public:
        template<typename...ARGS>
          Program(ARGS...shaders);
        template<typename...ARGS>
          Program(
              FunctionTablePointer const&table  ,
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
          FunctionTablePointer const&table  ,
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
    inline void Program::set(std::string const&name,float v0                           ){assert(this!=nullptr);this->set1f(name,v0);}
    inline void Program::set(std::string const&name,float v0,float v1                  ){assert(this!=nullptr);this->set2f(name,v0,v1);}
    inline void Program::set(std::string const&name,float v0,float v1,float v2         ){assert(this!=nullptr);this->set3f(name,v0,v1,v2);}
    inline void Program::set(std::string const&name,float v0,float v1,float v2,float v3){assert(this!=nullptr);this->set4f(name,v0,v1,v2,v3);}
    inline void Program::set(std::string const&name,int32_t v0                                 ){assert(this!=nullptr);this->set1i(name,v0);}
    inline void Program::set(std::string const&name,int32_t v0,int32_t v1                      ){assert(this!=nullptr);this->set2i(name,v0,v1);}
    inline void Program::set(std::string const&name,int32_t v0,int32_t v1,int32_t v2           ){assert(this!=nullptr);this->set3i(name,v0,v1,v2);}
    inline void Program::set(std::string const&name,int32_t v0,int32_t v1,int32_t v2,int32_t v3){assert(this!=nullptr);this->set4i(name,v0,v1,v2,v3);}
    inline void Program::set(std::string const&name,uint32_t v0                                    ){assert(this!=nullptr);this->set1ui(name,v0);}
    inline void Program::set(std::string const&name,uint32_t v0,uint32_t v1                        ){assert(this!=nullptr);this->set2ui(name,v0,v1);}
    inline void Program::set(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2            ){assert(this!=nullptr);this->set3ui(name,v0,v1,v2);}
    inline void Program::set(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2,uint32_t v3){assert(this!=nullptr);this->set4ui(name,v0,v1,v2,v3);}
    inline void Program::set1v(std::string const&name,float const*v0,GLsizei count){assert(this!=nullptr);this->set1fv(name,v0,count);}
    inline void Program::set2v(std::string const&name,float const*v0,GLsizei count){assert(this!=nullptr);this->set2fv(name,v0,count);}
    inline void Program::set3v(std::string const&name,float const*v0,GLsizei count){assert(this!=nullptr);this->set3fv(name,v0,count);}
    inline void Program::set4v(std::string const&name,float const*v0,GLsizei count){assert(this!=nullptr);this->set4fv(name,v0,count);}
    inline void Program::set1v(std::string const&name,int32_t const*v0,GLsizei count){assert(this!=nullptr);this->set1iv(name,v0,count);}
    inline void Program::set2v(std::string const&name,int32_t const*v0,GLsizei count){assert(this!=nullptr);this->set2iv(name,v0,count);}
    inline void Program::set3v(std::string const&name,int32_t const*v0,GLsizei count){assert(this!=nullptr);this->set3iv(name,v0,count);}
    inline void Program::set4v(std::string const&name,int32_t const*v0,GLsizei count){assert(this!=nullptr);this->set4iv(name,v0,count);}
    inline void Program::set1v(std::string const&name,uint32_t const*v0,GLsizei count){assert(this!=nullptr);this->set1uiv(name,v0,count);}
    inline void Program::set2v(std::string const&name,uint32_t const*v0,GLsizei count){assert(this!=nullptr);this->set2uiv(name,v0,count);}
    inline void Program::set3v(std::string const&name,uint32_t const*v0,GLsizei count){assert(this!=nullptr);this->set3uiv(name,v0,count);}
    inline void Program::set4v(std::string const&name,uint32_t const*v0,GLsizei count){assert(this!=nullptr);this->set4uiv(name,v0,count);}
  }
}
