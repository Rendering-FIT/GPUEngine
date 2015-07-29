#ifndef _PROGRAMOBJECT_H_
#define _PROGRAMOBJECT_H_

#include<geGL/OpenGL.h>
#include<geGL/OpenGLObject.h>
#include<stdarg.h>
#include<vector>
#include<map>
#include<geGL/ShaderObject.h>
#include<geGL/ShaderObjectParameter.h>
#include<geGL/ShaderObjectSubroutine.h>
#include<geGL/ProgramObjectMacro.h>
#include<geGL/BufferObject.h>
#include<geGL/TextureObject.h>
#include<geCore/dtemplates.h>

namespace ge{
  namespace gl{
    /**
     * @brief Initialise shader manager
     */
    GEGL_EXPORT void initShadersAndPrograms();
    /**
     * @brief Function converts complex type (GL_FLOAT_VEC3 to GL_FLOAT)
     *
     * @param Type OpenGL Type GL_FLOAT_VEC2, ...
     *
     * @return GL_FLOAT, ...
     */
    GEGL_EXPORT GLenum complexType2SimpleType(GLenum Type);
    /**
     * @brief Function converts complex type (GL_FLOAT_VEC3 to 3)
     *
     * @param Type OpenGL Type GL_FLOAT_VEC2, ...
     *
     * @return 2, ...
     */
    GEGL_EXPORT GLint complexType2Size(GLenum Type);
    /**
     * @brief This class represents shader program
     */
    class GEGL_EXPORT ProgramObject: public OpenGLObject
    {
      private:
        int _floatMatrixType2Index(GLenum type);
        int _doubleMatrixType2Index(GLenum type);
      protected:
        std::vector<GLuint>                        _shaderList    ;///<list of shader object
        std::vector<ShaderObject*>                 _shaders       ;///<list of shaders
        std::map<std::string,ShaderObjectParameter>_attributeList ;///<list of attributes
        std::map<std::string,ShaderObjectParameter>_uniformList   ;///<list of uniforms
        std::map<std::string,BufferParams>         _bufferList    ;///<list of buffers
        std::vector<std::string>                   _bufferNames   ;///<list of buffer names
        ShaderObjectSubroutine                     _subroutines[6];///<subroutines in shaders
        std::map<std::string,SamplerParam>         _samplerList   ;///<sampler parameters
        void createShaderProgram_Prologue();  ///<prologue of creating of shader prg.
        void createShaderProgram_Epilogue();  ///<epilogue of creating of shader prg.
        void getParameterList();              ///<obtain shader parameters
        void getSubroutineUniformList();      ///<obtain shader subroutines
        void getBufferList();                 ///<obtain shader buffers
        std::string getProgramInfo(GLuint ID);///<obtain program info log
        void deleteProgram();                 ///<delete shader program
        void compileShaders(
            unsigned     numShaders,
            std::string *shaders,
            std::string *defs,
            unsigned     version,
            std::string  profile);
        void sortAndCompileShaders(
            unsigned     numStrings,
            std::string *strings,
            unsigned     version,
            std::string  profile);
        /*
        void _createProgram(
            std::vector<std::string>& data         ,
            unsigned                  version = 0  ,
            std::string               profile = "" );
        bool        _isShader       (std::string data);///<has to contain void main() in some form
        bool        _isFile         (std::string data);///<has to exist
        std::string _composeShaderSource(std::vector<std::string>&data,unsigned version=0,std::string profile="");
        std::string _getShaderSource(std::string data);///<if its file open it and return its content
        unsigned    _getShaderSourceTypeMask(std::string data);///if it can be vs gp or fs it returns 0x1|0x8|0x10
        */
      public:
        std::string uniformsToStr();
        GLint workGroupSize[3];///< work group size
        void setSeparable    ();
        void resetSeparable  ();
        void setRetrievable  ();
        void resetRetrievable();
        /**
         * Constructor
         * @param shader list of shaders
         * @param num number of shaders
         */
        ProgramObject(ShaderObject**shader,unsigned num);
        /**
         * Constructor
         * @param num number of shaders
         */
        ProgramObject(unsigned num,...);
        /**
         * @brief Constructor
         *
         * @param shader0 shader 0
         * @param version version of shader
         * @param profile profile version of shader
         */
        ProgramObject(
            std::string shader0,
            unsigned    version=0,
            std::string profile="");
        /**
         * @brief Constructor
         *
         * @param shader0 shader 0
         * @param shader1 shader 1
         * @param version version of shader
         * @param profile profile version of shader
         */
        ProgramObject(
            std::string shader0,
            std::string shader1,
            unsigned    version=0,
            std::string profile="");
        /**
         * @brief Constructor
         *
         * @param shader0 shader 0
         * @param shader1 shader 1
         * @param shader2 shader 2
         * @param version version of shader
         * @param profile profile version of shader
         */
        ProgramObject(
            std::string shader0,
            std::string shader1,
            std::string shader2,
            unsigned    version=0,
            std::string profile="");
        /**
         * @brief Constructor
         *
         * @param shader0 shader 0
         * @param shader1 shader 1
         * @param shader2 shader 2
         * @param shader3 shader 3
         * @param version version of shader
         * @param profile profile version of shader
         */
        ProgramObject(
            std::string shader0,
            std::string shader1,
            std::string shader2,
            std::string shader3,
            unsigned    version=0,
            std::string profile="");
        /**
         * @brief Constructor
         *
         * @param shader0 shader 0
         * @param shader1 shader 1
         * @param shader2 shader 2
         * @param shader3 shader 3
         * @param shader4 shader 4
         * @param version version of shader
         * @param profile profile version of shader
         */
        ProgramObject(
            std::string shader0,
            std::string shader1,
            std::string shader2,
            std::string shader3,
            std::string shader4,
            unsigned    version=0,
            std::string profile="");
        ProgramObject(
            std::string shader0,
            std::string shader1,
            std::string shader2,
            std::string shader3,
            std::string shader4,
            std::string shader5,
            unsigned    version=0,
            std::string profile="");
        ProgramObject(
            std::string shader0,
            std::string shader1,
            std::string shader2,
            std::string shader3,
            std::string shader4,
            std::string shader5,
            std::string shader6,
            unsigned    version=0,
            std::string profile="");
        ProgramObject(
            std::string shader0,
            std::string shader1,
            std::string shader2,
            std::string shader3,
            std::string shader4,
            std::string shader5,
            std::string shader6,
            std::string shader7,
            unsigned    version=0,
            std::string profile="");
        ProgramObject(
            std::string shader0,
            std::string shader1,
            std::string shader2,
            std::string shader3,
            std::string shader4,
            std::string shader5,
            std::string shader6,
            std::string shader7,
            std::string shader8,
            unsigned    version=0,
            std::string profile="");
        ProgramObject(
            std::string shader0,
            std::string shader1,
            std::string shader2,
            std::string shader3,
            std::string shader4,
            std::string shader5,
            std::string shader6,
            std::string shader7,
            std::string shader8,
            std::string shader9,
            unsigned    version=0,
            std::string profile="");
        /*
        template<typename... Args>
        ProgramObject(Args... args,unsigned version=430,std::string profile=""){
          std::vector<std::string>sources;
          ge::core::argsToVector(sources,args...);
          this->_createProgram(sources,version,profile);
        }*/

        /**
         * @brief Constructor
         *
         * @param type0 type of shader0
         * @param shader0 text of shader0
         */
        ProgramObject(
            GLenum type0,std::string shader0);
        /**
         * @brief Constructor
         *
         * @param type0 type of shader0
         * @param shader0 text of shader0
         * @param type1 type of shader1
         * @param shader1 test of shader1
         */
        ProgramObject(
            GLenum type0,std::string shader0,
            GLenum type1,std::string shader1);
        /**
         * @brief Constructor
         *
         * @param type0 type of shader0
         * @param shader0 text of shader0
         * @param type1 type of shader1
         * @param shader1 test of shader1
         * @param type2 type of shader2
         * @param shader2 text of shader2
         */
        ProgramObject(
            GLenum type0,std::string shader0,
            GLenum type1,std::string shader1,
            GLenum type2,std::string shader2);
        /**
         * @brief Constructor
         *
         * @param type0 type of shader0
         * @param shader0 text of shader0
         * @param type1 type of shader1
         * @param shader1 test of shader1
         * @param type2 type of shader2
         * @param shader2 text of shader2
         * @param type3 type of shader3
         * @param shader3 text of shader3
         */
        ProgramObject(
            GLenum type0,std::string shader0,
            GLenum type1,std::string shader1,
            GLenum type2,std::string shader2,
            GLenum type3,std::string shader3);
        /**
         * @brief Constructor
         *
         * @param type0 type of shader0
         * @param shader0 text of shader0
         * @param type1 type of shader1
         * @param shader1 test of shader1
         * @param type2 type of shader2
         * @param shader2 text of shader2
         * @param type3 type of shader3
         * @param shader3 text of shader3
         * @param type4 type of shader4
         * @param shader4 text of shader4
         */
        ProgramObject(
            GLenum type0,std::string shader0,
            GLenum type1,std::string shader1,
            GLenum type2,std::string shader2,
            GLenum type3,std::string shader3,
            GLenum type4,std::string shader4);

        /**
         * @brief Sets version of every shader in shader program
         *
         * @param version version
         * @param profile profile
         */
        void setVersion(unsigned version,std::string profile);
        /**
         * @brief Sets version in specific shader of shader program 
         *
         * @param type shader type
         * @param version version
         * @param profile profile
         */
        void setVersion(GLenum type,unsigned version,std::string profile);
        /**
         * @brief Appends definitions after version in every shader of program
         *
         * @param defs definitions
         */
        void appendAfterVersion(std::string defs);
        /**
         * @brief Appends definitions after version in specific shader
         *
         * @param type type of shader
         * @param defs definitions
         */
        void appendAfterVersion(GLenum type,std::string defs);
        /**
         * @brief Relink program
         */
        void relink();
        /**
         * @brief Destructor
         */
        ~ProgramObject();
        /**
         * @brief Return shader program uniform location
         *
         * @param name name of uniform
         *
         * @return returns parameter ID
         */
        GLint operator[](std::string name);
        /**
         * Ziska identifikator atributu
         * @param attributeName jmeno atributu
         * @return vracu identifikator atributu
         */
        GLint getAttribute(std::string attributeName);
        /**
         * @brief Returns attribute type
         *
         * @param attributeName attribute name
         *
         * @return type of attribute
         */
        GLenum getAttributeType(std::string attributeName);
        /**
         * @brief Returns size of attribute's array
         *
         * @param attributeName attribute name
         *
         * @return size of attribute's array
         */
        GLint getAttributeSize(std::string attributeName);
        /**
         * Ziska identifikator uniformni promenne
         * @param uniformName jmeno uniformni promenne
         * @return vracu identifikator uniformni promenne
         */
        GLint getUniform(std::string uniformName);
        /**
         * @brief Returns uniform type
         *
         * @param uniformName uniform name
         *
         * @return type of uniform
         */
        GLenum getUniformType(std::string uniformName);
        /**
         * @brief Returns size of uniform's array
         *
         * @param uniformName uniform name
         *
         * @return size of uniform's array
         */
        GLint getUniformSize(std::string uniformName);
        /**
         * @brief gets buffer binding index
         *
         * @param name name of buffer
         *
         * @return binding index
         */
        GLuint getBuffer(std::string name);
        /**
         * @brief gets number of buffers
         *
         * @return number of buffers
         */
        unsigned getNofBuffers();
        /**
         * @brief gets name of buffer
         *
         * @param i index of buffer
         *
         * @return name of buffer
         */
        std::string getBufferName(unsigned i);
        /**
         * @brief gets buffer property
         *
         * @param name name of buffer
         * @param property property type
         *
         * @return value of buffer property
         */
        GLint getBufferProperty(std::string name,BufferParams::Properties property);
        /**
         * @brief gets buffer params
         *
         * @param name name of buffer
         *
         * @return buffer params
         */
        BufferParams getBufferParams(std::string name);
        /**
         * @brief Sets this shader as active
         */
        void use();
        void bindSSBO(std::string name,ge::gl::BufferObject*buffer);
        void bindSSBO(std::string name,ge::gl::BufferObject*buffer,GLintptr offset,GLsizeiptr size);
        GLenum getSamplerBinding(std::string uniform);
        void bindTexture(std::string uniform,ge::gl::TextureObject*texture);
        void bindImage(
            std::string           uniform                ,
            ge::gl::TextureObject*texture                ,
            GLint                 level   = 0            ,
            GLenum                format  = 0            ,
            GLenum                access  = GL_READ_WRITE,
            GLboolean             layered = GL_FALSE     ,
            GLint                 layer   = 0            );

        /**
         * @brief Sets subroutine with name SubroutineName as active in Uniform
         *
         * @param shaderType type of shader
         * @param uniform uniform name
         * @param subroutineName subroutine name
         */
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
    };
  }//gl
}//ge

#endif//_PROGRAMOBJECT_H_
