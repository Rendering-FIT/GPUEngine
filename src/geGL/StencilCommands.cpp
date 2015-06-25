#include <geGL/StencilCommands.h>

using namespace ge::gl;

StencilFunc::StencilFunc(
    GLenum func,
    GLint  ref,
    GLuint mask){
  this->func = func;
  this->ref  = ref;
  this->mask = mask;
}
void StencilFunc::operator()(){
  glStencilFunc(
      this->func,
      this->ref,
      this->mask);
}

StencilFuncSeparate::StencilFuncSeparate(
    GLenum face,
    GLenum func,
    GLint  ref,
    GLuint mask){
  this->face = face;
  this->func = func;
  this->ref  = ref;
  this->mask = mask;
}
void StencilFuncSeparate::operator()(){
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
void StencilOp::operator()(){
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
void StencilOpSeparate::operator()(){
  glStencilOpSeparate(
      this->face,
      this->sfail,
      this->dpfail,
      this->dppass);
}

