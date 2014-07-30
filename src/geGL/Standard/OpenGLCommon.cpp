#include <geGL/Standard/OpenGLCommon.h>

namespace ge
{
  namespace ogl
  {
    EnableDisable::EnableDisable(GLenum target,bool value){
      this->target = target;
      this->value  = value;
    }
    void EnableDisable::apply(){
      if(this->value)glEnable(this->target);
      else glDisable(this->target);
    }
    EnableDisablei::EnableDisablei(GLenum target,GLuint index,bool value){
      this->target = target;
      this->index  = index;
      this->value  = value;
    }
    void EnableDisablei::apply(){
      if(this->value)glEnablei(this->target,this->index);
      else glDisablei(this->target,this->index);
    }
    Enable::Enable(GLenum target){
      this->target=target;
    }
    void Enable::apply(){
      glEnable(this->target);
    }
    Disable::Disable(GLenum target){
      this->target=target;
    }
    void Disable::apply(){
      glDisable(this->target);
    }
    Enablei::Enablei(GLenum target,GLuint buffer){
      this->target = target;
      this->buffer = buffer;
    }
    void Enablei::apply(){
      glEnablei(this->target,this->buffer);
    }
    Disablei::Disablei(GLenum target,GLuint buffer){
      this->target = target;
      this->buffer = buffer;
    }
    void Disablei::apply(){
      glDisablei(this->target,this->buffer);
    }
  }
}
