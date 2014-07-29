#include"ConditionalRenderingCommands.h"

namespace ge
{
  namespace ogl{
    BeginConditionalRender::BeginConditionalRender(GLuint id,GLenum mode){
      this->id   = id;
      this->mode = mode;
    }
    void BeginConditionalRender::apply(){
      glBeginConditionalRender(
          this->id,
          this->mode);
    }
    EndConditionalRender::EndConditionalRender(){
    }
    void EndConditionalRender::apply(){
      glEndConditionalRender();
    }
  }//ogl
}//ge
