#ifndef _SHADEROBJECTSMANAGER_H_
#define _SHADEROBJECTSMANAGER_H_

#include<iostream>

#include<geGL/OpenGL.h>
#include<geGL/ShaderObjectsCommands.h>

#include<vector>
#include<map>

//RESOLVE THESE ISSUES AND WRITE DOWN NEW
//TODO 1. maybe create new command for some action, espetially for loading of shader
//
//
//
//

namespace ge
{
  namespace gl
  {


    const unsigned    SHADER_OBJECT_MANAGER_DEFAULT_VERSION     = 0         ;
    const std::string SHADER_OBJECT_MANAGER_DEFAULT_NAME        = ""        ;
    const std::string SHADER_OBJECT_MANAGER_DEFAULT_DEFINITIONS = ""        ;
    const std::string SHADER_OBJECT_MANAGER_DEFAULT_PROFILE     = ""        ;
    const std::string SHADER_OBJECT_MANAGER_LINE_END            = "\n"      ;
    const std::string SHADER_OBJECT_MANAGER_VERSION_KEYWORD     = "#version";
    const std::string SHADER_OBJECT_MANAGER_DEFINE_KEYWORD      = "#define" ;
    const std::string SHADER_OBJECT_MANAGER_BASE_NAME           = "shader"  ;

    /**
     * @brief this class represents shader managers
     * shader manager manages shader objects
     * it can create, destroy shader objects
     * it produces commands that create or destroy shaders
     * it also implements LRU strategy for shaders TODO
     */
    class GE_EXPORT ShaderObjectManager
    {
      private:
        std::map<std::string,GLuint>_shaders;
        unsigned _shaderCount;
        GLenum   _fileToShaderType  (std::string fileName);
	      int      _fileTypeSwitch    (std::string fileName,unsigned numType,...);
	      char*    _readWholeFile     (int*length,std::string fileName);
        void     _appendAfterVersion(std::string*text,std::string definitions);
        void     _setVersion        (std::string*text,unsigned version,std::string profile);
        bool     _prepareSource     (
            GLuint       **shader,
            GLchar      ***string,
            std::string    text,
            std::string   *name,
            std::string    definitions,
            unsigned       version,
            std::string    profile);
      public:
        /**
         * @brief creates command that clears shaders inside shader manager
         *
         * @param command created command that destroys shaders
         */
        void clear(Command **command);
        /**
         * @brief creates commands that create shader
         *
         * @param command created command that creates shader
         * @param type type of shader
         * @param text source code of shader
         * @param name name of shader
         * @param definitions additional definitions
         * @param version version of shader
         * @param profile profile version of shader
         *
         * @return returns textual representation of shader
         */
        std::string insert(
            Command     **command,
            GLenum        type,
            std::string   text,
            std::string   name        = SHADER_OBJECT_MANAGER_DEFAULT_NAME,
            std::string   definitions = SHADER_OBJECT_MANAGER_DEFAULT_DEFINITIONS,
            unsigned      version     = SHADER_OBJECT_MANAGER_DEFAULT_VERSION,
            std::string   profile     = SHADER_OBJECT_MANAGER_DEFAULT_PROFILE);
        /**
         * @brief creates commands that create shader
         *
         * @param fileName file that contains source code for shader
         * @param definitions additional definitions
         * @param version version of shader
         * @param profile profile version of shader
         */
        void insert(
            Command     **command,
            std::string   fileName,
            std::string   name        = SHADER_OBJECT_MANAGER_DEFAULT_NAME,
            std::string   definitions = SHADER_OBJECT_MANAGER_DEFAULT_DEFINITIONS,
            unsigned      version     = SHADER_OBJECT_MANAGER_DEFAULT_VERSION,
            std::string   profile     = SHADER_OBJECT_MANAGER_DEFAULT_PROFILE);
        /**
         * @brief  inserts new shader to manager
         *
         * @param type type of shader
         * @param text source code of shader
         * @param name name of shader
         * @param definitions additional definitions
         * @param version version of shader
         * @param profile profile version of shader
         *
         * @return returns textual representation of shader
         */
        std::string insertNow(
            GLenum        type,
            std::string   text,
            std::string   name        = SHADER_OBJECT_MANAGER_DEFAULT_NAME,
            std::string   definitions = SHADER_OBJECT_MANAGER_DEFAULT_DEFINITIONS,
            unsigned      version     = SHADER_OBJECT_MANAGER_DEFAULT_VERSION,
            std::string   profile     = SHADER_OBJECT_MANAGER_DEFAULT_PROFILE);
        /**
         * @brief inserts new shader to manager
         *
         * @param fileName file that contains source code for shader
         * @param name name of shader
         * @param definitions additional definitions
         * @param version version of shader
         * @param profile profile version of shader
         */
        void insert(
            std::string   fileName,
            std::string   name        = SHADER_OBJECT_MANAGER_DEFAULT_NAME,
            std::string   definitions = SHADER_OBJECT_MANAGER_DEFAULT_DEFINITIONS,
            unsigned      version     = SHADER_OBJECT_MANAGER_DEFAULT_VERSION,
            std::string   profile     = SHADER_OBJECT_MANAGER_DEFAULT_PROFILE);
        /**
         * @brief creates definitions
         *
         * @param name name of definition
         *
         * @return returns "#define name"
         */
        std::string define(
            std::string name);
        /**
         * @brief 
         *
         * @param name
         * @param value
         *
         * @return 
         */
        std::string define(
            std::string name,
            unsigned    value);
        std::string define(
            std::string name,
            unsigned    value0,
            unsigned    value1);
        std::string define(
            std::string name,
            unsigned    value0,
            unsigned    value1,
            unsigned    value2);
        std::string define(
            std::string name,
            unsigned    value0,
            unsigned    value1,
            unsigned    value2,
            unsigned    value3);
        std::string define(
            std::string name,
            int         value);
        std::string define(
            std::string name,
            int         value0,
            int         value1);
        std::string define(
            std::string name,
            int         value0,
            int         value1,
            int         value2);
        std::string define(
            std::string name,
            int         value0,
            int         value1,
            int         value2,
            int         value3);
        std::string define(
            std::string name,
            float       value);
        std::string define(
            std::string name,
            float       value0,
            float       value1);
        std::string define(
            std::string name,
            float       value0,
            float       value1,
            float       value2);
        std::string define(
            std::string name,
            float       value0,
            float       value1,
            float       value2,
            float       value3);
        std::string define(std::string name,std::string value);
    };
  }//ogl
}//ge


#endif//_SHADEROBJECTSMANAGER_H_
