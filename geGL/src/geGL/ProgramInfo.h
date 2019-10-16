#pragma once

#include<geGL/OpenGL.h>
#include<vector>
#include<map>
#include<set>
#include<tuple>
#include<iostream>

namespace ge{
  namespace gl{
    class ProgramInfo;
  }
}

class ge::gl::ProgramInfo{
  public:
    using Properties = 
      std::tuple<
      GLint      ,
      GLenum     ,
      std::string,
      GLint      >;
    enum PropertiesParts{
      LOCATION = 0,
      TYPE     = 1,
      NAME     = 2,
      SIZE     = 3,
    };

    using BufferProperties = std::tuple<
      std::string,
      GLint      ,
      GLint      ,
      GLint      ,
      GLint      ,
      GLint      ,
      GLint      ,
      GLint      ,
      GLint      ,
      GLint      >;
    enum BufferPropertiesParts{
      BUFFER_NAME                                 = 0,
      BUFFER_BINDING                              = 1, 
      BUFFER_DATA_SIZE                            = 2,
      BUFFER_NOF_ACTIVE_VARIABLES                 = 3,
      BUFFER_REFERENCED_BY_VERTEX_SHADER          = 4,
      BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER    = 5,
      BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER = 6,
      BUFFER_REFERENCED_BY_GEOMETRY_SHADER        = 7,
      BUFFER_REFERENCED_BY_FRAGMENT_SHADER        = 8,
      BUFFER_REFERENCED_BY_COMPUTE_SHADER         = 9,
    };

    using SubroutineUniformProperties = std::tuple<
      GLint      ,
                 GLint      ,
                 GLint      ,
                 std::string,
                 GLuint     >;
    enum SubroutineUniformPropertiesParts{
      SUBROUTINE_UNIFORM_LOCATION   = 0,
      SUBROUTINE_UNIFORM_SIZE       = 1,
      SUBROUTINE_UNIFORM_COMPATIBLE = 2,
      SUBROUTINE_UNIFORM_NAME       = 3,
      SUBROUTINE_UNIFORM_INDEX      = 4,
    };

    std::map<std::string,Properties                 >attribs           ;
    std::map<std::string,Properties                 >uniforms          ;
    std::map<std::string,BufferProperties           >buffers           ;
    std::map<std::string,SubroutineUniformProperties>subroutineUniforms;

};
