#pragma once

#include<iostream>
#include<memory>
#include<set>
#include<map>

#include<geGL/Shader.h>
#include<geGL/ProgramInfo.h>

class GEGL_EXPORT ge::gl::Program: public OpenGLObject{
  public:
    using ShaderPointer  = std::shared_ptr<Shader>;
    using ShaderPointers = std::vector<ShaderPointer>;
	Program(ShaderPointers const&shaders);
	Program(
        FunctionTablePointer const&table       ,
        ShaderPointers       const&shaders = {});
	~Program();
	void create       ();
	void attachShaders(ShaderPointers const&shaders = {});
	void detachShaders(ShaderPointers const&shaders = {});
	void link         (ShaderPointers const&shaders = {});
	GLboolean isProgram()const;
	void use ()const;
	void validate()const;
	GLboolean   getDeleteStatus                     ()const;
	GLboolean   getLinkStatus                       ()const;
	GLboolean   getValidateStatus                   ()const;
	GLuint      getInfoLogLength                    ()const;
	GLuint      getNofShaders                       ()const;
	GLuint      getNofActiveAtomicCounterBuffers    ()const;
	GLuint      getNofActiveAttributes              ()const;
	GLuint      getActiveAttributeMaxLength         ()const;
	GLuint      getNofActiveUniforms                ()const;
	GLuint      getActiveUniformMaxLength           ()const;
	GLuint      getBinaryLength                     ()const;
	GLenum      getTransformFeedbackBufferMode      ()const;
	GLuint      getNofTransfromFeedbackVaryings     ()const;
	GLuint      getTransformFeedbackVaryingMaxLength()const;
	GLuint      getNofGeometryVerticesOut           ()const;
	GLenum      getGeometryInputType                ()const;
	GLenum      getGeometryOutputType               ()const;
	std::string getInfoLog                          ()const;
	void        getComputeWorkGroupSize(GLint*x                                )const;
	GLint       getUniformLocation     (std::string const&name                 )const;
	GLint       getAttribLocation      (std::string const&name                 )const;
	GLint       getInterfaceParam      (GLenum interf,GLenum pname             )const;
	std::string getResourceName        (GLenum interf,GLuint index             )const;
	GLint       getResourceParam       (GLenum interf,GLenum pname,GLuint index)const;
	Program const*set1f         (std::string const&name,float    v0                                                       )const;
	Program const*set2f         (std::string const&name,float    v0,float    v1                                           )const;
	Program const*set3f         (std::string const&name,float    v0,float    v1,float    v2                               )const;
	Program const*set4f         (std::string const&name,float    v0,float    v1,float    v2,float    v3                   )const;
	Program const*set1i         (std::string const&name,int32_t  v0                                                       )const;
	Program const*set2i         (std::string const&name,int32_t  v0,int32_t  v1                                           )const;
	Program const*set3i         (std::string const&name,int32_t  v0,int32_t  v1,int32_t  v2                               )const;
	Program const*set4i         (std::string const&name,int32_t  v0,int32_t  v1,int32_t  v2,int32_t  v3                   )const;
	Program const*set1ui        (std::string const&name,uint32_t v0                                                       )const;
	Program const*set2ui        (std::string const&name,uint32_t v0,uint32_t v1                                           )const;
	Program const*set3ui        (std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2                               )const;
	Program const*set4ui        (std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2,uint32_t v3                   )const;
  Program const*set1fv        (std::string const&name,float    const*v0,GLsizei count = 1                               )const;
  Program const*set2fv        (std::string const&name,float    const*v0,GLsizei count = 1                               )const;
  Program const*set3fv        (std::string const&name,float    const*v0,GLsizei count = 1                               )const;
  Program const*set4fv        (std::string const&name,float    const*v0,GLsizei count = 1                               )const;
  Program const*set1iv        (std::string const&name,int32_t  const*v0,GLsizei count = 1                               )const;
  Program const*set2iv        (std::string const&name,int32_t  const*v0,GLsizei count = 1                               )const;
  Program const*set3iv        (std::string const&name,int32_t  const*v0,GLsizei count = 1                               )const;
  Program const*set4iv        (std::string const&name,int32_t  const*v0,GLsizei count = 1                               )const;
  Program const*set1uiv       (std::string const&name,uint32_t const*v0,GLsizei count = 1                               )const;
  Program const*set2uiv       (std::string const&name,uint32_t const*v0,GLsizei count = 1                               )const;
  Program const*set3uiv       (std::string const&name,uint32_t const*v0,GLsizei count = 1                               )const;
  Program const*set4uiv       (std::string const&name,uint32_t const*v0,GLsizei count = 1                               )const;
  Program const*setMatrix4fv  (std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix3fv  (std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix2fv  (std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix4x3fv(std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix4x2fv(std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix3x4fv(std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix3x2fv(std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix2x4fv(std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix2x3fv(std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix4dv  (std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix3dv  (std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix2dv  (std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix4x3dv(std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix4x2dv(std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix3x4dv(std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix3x2dv(std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix2x4dv(std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  Program const*setMatrix2x3dv(std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
  void set(std::string const&name,float    v0                                    );
  void set(std::string const&name,float    v0,float    v1                        );
  void set(std::string const&name,float    v0,float    v1,float    v2            );
  void set(std::string const&name,float    v0,float    v1,float    v2,float    v3);
  void set(std::string const&name,int32_t  v0                                    );
  void set(std::string const&name,int32_t  v0,int32_t  v1                        );
  void set(std::string const&name,int32_t  v0,int32_t  v1,int32_t  v2            );
  void set(std::string const&name,int32_t  v0,int32_t  v1,int32_t  v2,int32_t  v3);
  void set(std::string const&name,uint32_t v0                                    );
  void set(std::string const&name,uint32_t v0,uint32_t v1                        );
  void set(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2            );
  void set(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2,uint32_t v3);
  void set1v(std::string const&name,float    const*v0,GLsizei count = 1);
  void set2v(std::string const&name,float    const*v0,GLsizei count = 1);
  void set3v(std::string const&name,float    const*v0,GLsizei count = 1);
  void set4v(std::string const&name,float    const*v0,GLsizei count = 1);
  void set1v(std::string const&name,int32_t  const*v0,GLsizei count = 1);
  void set2v(std::string const&name,int32_t  const*v0,GLsizei count = 1);
  void set3v(std::string const&name,int32_t  const*v0,GLsizei count = 1);
  void set4v(std::string const&name,int32_t  const*v0,GLsizei count = 1);
  void set1v(std::string const&name,uint32_t const*v0,GLsizei count = 1);
  void set2v(std::string const&name,uint32_t const*v0,GLsizei count = 1);
  void set3v(std::string const&name,uint32_t const*v0,GLsizei count = 1);
  void set4v(std::string const&name,uint32_t const*v0,GLsizei count = 1);
  Program const*bindBuffer(std::string const&name,std::shared_ptr<Buffer>const&buffer)const;
  Program const*bindBuffer(std::string const&name,Buffer*const&buffer)const;
  Program const*dispatch(GLuint nofWorkGroupsX = 1,GLuint nofWorkGroupsY = 1,GLuint nofWorkGroupsZ = 1)const;

  std::shared_ptr<ProgramInfo> const&getInfo()const;
	static void setNonexistingUniformWarning(bool enableWarning = true);
	static bool isNonexistingUniformWarningEnabled();

	GLuint static const nonExistingBufferBinding;
	GLuint getBufferBinding(std::string const&name)const;
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
	ProgramImpl*impl = nullptr;
	GLint _getUniform(std::string name);
	GLint _getParam(GLenum pname)const;
    void _fillUniformInfo();
    void _fillAttribInfo();
    void _fillBufferInfo();
    void _fillInfo();
    std::string _chopIndexingInPropertyName(std::string name)const;
    friend class Shader;
};

template<typename...ARGS>
ge::gl::Program::Program(ARGS...shaders):Program(ShaderPointers({shaders...})){}
template<typename...ARGS>
ge::gl::Program::Program(
    FunctionTablePointer const&table  ,
    ARGS...                            shaders):Program(table,ShaderPointers({shaders...})){}
template<typename...ARGS>
void ge::gl::Program::attachShaders(ARGS... shaders){
  assert(this!=nullptr);
  this->attachShaders(ShaderPointers({shaders...}));
}
template<typename...ARGS>
void ge::gl::Program::detachShaders(ARGS... shaders){
  assert(this!=nullptr);
  this->detachShaders(ShaderPointers({shaders...}));
}
template<typename...ARGS>
void ge::gl::Program::link(ARGS... shaders){
  assert(this!=nullptr);
  this->link(ShaderPointers({shaders...}));
}
inline void ge::gl::Program::set(std::string const&name,float v0                           ){assert(this!=nullptr);this->set1f(name,v0);}
inline void ge::gl::Program::set(std::string const&name,float v0,float v1                  ){assert(this!=nullptr);this->set2f(name,v0,v1);}
inline void ge::gl::Program::set(std::string const&name,float v0,float v1,float v2         ){assert(this!=nullptr);this->set3f(name,v0,v1,v2);}
inline void ge::gl::Program::set(std::string const&name,float v0,float v1,float v2,float v3){assert(this!=nullptr);this->set4f(name,v0,v1,v2,v3);}
inline void ge::gl::Program::set(std::string const&name,int32_t v0                                 ){assert(this!=nullptr);this->set1i(name,v0);}
inline void ge::gl::Program::set(std::string const&name,int32_t v0,int32_t v1                      ){assert(this!=nullptr);this->set2i(name,v0,v1);}
inline void ge::gl::Program::set(std::string const&name,int32_t v0,int32_t v1,int32_t v2           ){assert(this!=nullptr);this->set3i(name,v0,v1,v2);}
inline void ge::gl::Program::set(std::string const&name,int32_t v0,int32_t v1,int32_t v2,int32_t v3){assert(this!=nullptr);this->set4i(name,v0,v1,v2,v3);}
inline void ge::gl::Program::set(std::string const&name,uint32_t v0                                    ){assert(this!=nullptr);this->set1ui(name,v0);}
inline void ge::gl::Program::set(std::string const&name,uint32_t v0,uint32_t v1                        ){assert(this!=nullptr);this->set2ui(name,v0,v1);}
inline void ge::gl::Program::set(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2            ){assert(this!=nullptr);this->set3ui(name,v0,v1,v2);}
inline void ge::gl::Program::set(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2,uint32_t v3){assert(this!=nullptr);this->set4ui(name,v0,v1,v2,v3);}
inline void ge::gl::Program::set1v(std::string const&name,float const*v0,GLsizei count){assert(this!=nullptr);this->set1fv(name,v0,count);}
inline void ge::gl::Program::set2v(std::string const&name,float const*v0,GLsizei count){assert(this!=nullptr);this->set2fv(name,v0,count);}
inline void ge::gl::Program::set3v(std::string const&name,float const*v0,GLsizei count){assert(this!=nullptr);this->set3fv(name,v0,count);}
inline void ge::gl::Program::set4v(std::string const&name,float const*v0,GLsizei count){assert(this!=nullptr);this->set4fv(name,v0,count);}
inline void ge::gl::Program::set1v(std::string const&name,int32_t const*v0,GLsizei count){assert(this!=nullptr);this->set1iv(name,v0,count);}
inline void ge::gl::Program::set2v(std::string const&name,int32_t const*v0,GLsizei count){assert(this!=nullptr);this->set2iv(name,v0,count);}
inline void ge::gl::Program::set3v(std::string const&name,int32_t const*v0,GLsizei count){assert(this!=nullptr);this->set3iv(name,v0,count);}
inline void ge::gl::Program::set4v(std::string const&name,int32_t const*v0,GLsizei count){assert(this!=nullptr);this->set4iv(name,v0,count);}
inline void ge::gl::Program::set1v(std::string const&name,uint32_t const*v0,GLsizei count){assert(this!=nullptr);this->set1uiv(name,v0,count);}
inline void ge::gl::Program::set2v(std::string const&name,uint32_t const*v0,GLsizei count){assert(this!=nullptr);this->set2uiv(name,v0,count);}
inline void ge::gl::Program::set3v(std::string const&name,uint32_t const*v0,GLsizei count){assert(this!=nullptr);this->set3uiv(name,v0,count);}
inline void ge::gl::Program::set4v(std::string const&name,uint32_t const*v0,GLsizei count){assert(this!=nullptr);this->set4uiv(name,v0,count);}
