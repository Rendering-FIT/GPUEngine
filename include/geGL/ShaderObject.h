#ifndef _SHADEROBJECT_H_
#define _SHADEROBJECT_H_

#include <geGL/OpenGL.h>
#include <geGL/OpenGLObject.h>
#include <geCore/dtemplates.h>
#include<iostream>

namespace ge{
  namespace gl{

    class GEGL_EXPORT Shader: public OpenGLObject{
      protected:
        GLint _getParam(GLenum pname);
      public:
        Shader(GLenum type,std::string source="");
        void        setSource(std::string source);
        void        compile(std::string source="");
        GLboolean   isShader        ();
        GLenum      getType         ();
        GLboolean   getDeleteStatus ();
        GLboolean   getCompileStatus();
        GLuint      getInfoLogLength();
        GLuint      getSourceLength ();
        std::string getInfoLog      ();
        std::string getSource       ();
    };

    /*
    Shader*createShader(GLenum type,std::string source="");
    Shader*createShader(std::string file,GLenum type=ge::core::nonof(
          GL_VERTEX_SHADER,GL_FRAGMENT_SHADER,GL_TESS_CONTROL_SHADER,GL_TESS_EVALUATION_SHADER,
          ))
          */

    /**
     * This class represents shader
     */
    class GEGL_EXPORT ShaderObject: public OpenGLObject
    {
      protected:
        std::string _text; ///<contains shader test
        GLenum      _type; ///<type of shader (vertex,fragment,geometry,...)
        void        _compileShader();            ///<compile shader
        std::string _getShaderInfo(GLuint id);   ///<gets shader info
        void        _loadFile(std::string file); ///<load file with shader
        static int            fileTypeSwitch(std::string fileName,unsigned numType,...);
        static unsigned char *readWholeFile(int*len,std::string file);
      public:
        /**
         * @brief Converts filename to type of shader
         *
         * @param FileName filename with extension
         *
         * @return return GL_VERTEX_SHADER, ..., or 0
         */
        static GLenum file2ShaderType(std::string fileName);
        static std::string define(std::string name);
        static std::string define(std::string name,unsigned value);
        static std::string define(std::string name,unsigned value0,unsigned value1);
        static std::string define(std::string name,unsigned value0,unsigned value1,unsigned value2);
        static std::string define(std::string name,unsigned value0,unsigned value1,unsigned value2,unsigned value3);
        static std::string define(std::string name,unsigned vectorSize,unsigned*values);
        static std::string define(std::string name,int value);
        static std::string define(std::string name,int value0,int value1);
        static std::string define(std::string name,int value0,int value1,int value2);
        static std::string define(std::string name,int value0,int value1,int value2,int value3);
        static std::string define(std::string name,unsigned vectorSize,int*values);
        static std::string define(std::string name,float value);
        static std::string define(std::string name,float value0,float value1);
        static std::string define(std::string name,float value0,float value1,float value2);
        static std::string define(std::string name,float value0,float value1,float value2,float value3);
        static std::string define(std::string name,unsigned vectorSize,float*values);
        static std::string define(std::string name,std::string value);
        static std::string include(std::string file);

        /**
         * Constructor
         * @param Type Type of shader
         * @param Text Text of shader
         */
        ShaderObject(GLenum type,std::string text);
        /**
         * Constructor
         * @param FileName name of file which contains shader
         */
        ShaderObject(std::string fileName);
        ShaderObject(std::string fileName, GLenum type);
        /**
         * @brief Constructor
         *
         * @param FileName name of file that contains shader
         * @param Defs additional definitions, empty definitions are ommited
         */
        ShaderObject(std::string fileName,std::string defs);
        /**
         * @brief Constructor
         *
         * @param FileName name of file that contains shader
         * @param Defs additional definitions, empty definitions are ommited
         * @param version version of shader, if the version is 0 it is not used
         */
        ShaderObject(std::string fileName,std::string defs,unsigned version,std::string profile);
        /**
         * @brief Constructor
         *
         * @param FileName name of file that contains shader
         * @param version version of shader, if the version is 0 it is not used
         */
        ShaderObject(std::string fileName,unsigned version,std::string profile);
        /**
         * @brief Destructor
         */
        ~ShaderObject();
        /**
         * @brief Sets version and profile of shader
         *
         * @param version version
         * @param profile profile
         */
        void setVersion(unsigned version,std::string profile);
        /**
         * @brief Appends some definitions after version definition
         *
         * @param Defs string containing definitions
         */
        void appendAfterVersion(std::string defs);
        /**
         * @brief Recompiles shader
         */
        void recompile();
        /**
         * @brief Gets type of shader
         *
         * @return type of shader
         */
        GLenum getType();
        /**
         * @brief Gets text representation of shader
         *
         * @return text of shader
         */
        std::string getText();
    };
  }//gl
}//ge

#endif//_SHADEROBJECT_H_
