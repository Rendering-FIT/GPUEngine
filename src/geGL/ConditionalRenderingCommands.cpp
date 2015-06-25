#include <geGL/ConditionalRenderingCommands.h>

namespace ge
{
  namespace gl{
    BeginConditionalRender::BeginConditionalRender(GLuint id,GLenum mode){
      this->id   = id;
      this->mode = mode;
    }
    void BeginConditionalRender::operator()(){
      glBeginConditionalRender(
          this->id,
          this->mode);
    }
    EndConditionalRender::EndConditionalRender(){
    }
    void EndConditionalRender::operator()(){
      glEndConditionalRender();
    }
  }//ogl
}//ge
