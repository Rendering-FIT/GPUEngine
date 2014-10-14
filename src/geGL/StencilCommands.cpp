#include <geGL/StencilCommands.h>

namespace ge
{
  namespace gl
  {
    StencilFunc::StencilFunc(
        GLenum func,
        GLint  ref,
        GLuint mask){
      this->func = func;
      this->ref  = ref;
      this->mask = mask;
    }
    void StencilFunc::apply(){
      glStencilFunc(
          this->func,
          this->ref,
          this->mask);
    }
    StencilFuncSeparate::StencilFuncSeparate(
        GLenum face,
        GLenum func,
        GLint  ref,
        GLuint Mask){
      this->face = face;
      this->func = func;
      this->ref  = ref;
      this->mask = mask;
    }
    void StencilFuncSeparate::apply(){
      glStencilFuncSeparate(
          this->face,
          this->func,
          this->ref,
          this->mask);
    }
    StencilOp::StencilOp(
        GLenum sfail,
        GLenum dpfail,
        GLenum dppass){
      this->sfail  = sfail;
      this->dpfail = dpfail;
      this->dppass = dppass;
    }
    void StencilOp::apply(){
      glStencilOp(
          this->sfail,
          this->dpfail,
          this->dppass);
    }
    StencilOpSeparate::StencilOpSeparate(
        GLenum face,
        GLenum sfail,
        GLenum dpfail,
        GLenum dppass){
      this->face   = face;
      this->sfail  = sfail;
      this->dpfail = dpfail;
      this->dppass = dppass;
    }
    void StencilOpSeparate::apply(){
      glStencilOpSeparate(
          this->face,
          this->sfail,
          this->dpfail,
          this->dppass);
    }
  }//ogl
}//ge
