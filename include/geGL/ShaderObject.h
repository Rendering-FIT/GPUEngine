#pragma once

#include<geGL/Shader.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT ShaderObject: public Shader{
      protected:
        static std::string _readShader(std::string const& file);
        static std::string _appendAfterVersion(std::string source,std::string defs);
        static std::string _setVersion(std::string source,unsigned version,std::string profile);
      public:
        ShaderObject(GLenum type,std::string source);
        ShaderObject(std::string file);
        ShaderObject(std::string file,GLenum type);
        ShaderObject(std::string file,std::string defs);
        ShaderObject(std::string file,std::string defs,unsigned version,std::string profile);
        ShaderObject(std::string file,unsigned version,std::string profile);
        virtual ~ShaderObject();
        void setVersion(unsigned version,std::string profile);
        void appendAfterVersion(std::string defs);
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
    };
    GLenum GEGL_EXPORT file2ShaderType(std::string fileName);
    int    GEGL_EXPORT fileTypeSwitch(std::string fileName,unsigned numType,...);
  }//gl
}//ge
