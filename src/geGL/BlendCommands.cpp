#include <geGL/BlendCommands.h>

using namespace ge::gl;

BlendEnablei::BlendEnablei(GLuint buffer,bool enable){
  this->buffer = buffer;
  this->enable = enable;
}
void BlendEnablei::operator()(){
  if(this->enable)glEnablei(GL_BLEND,this->buffer);
  else glDisablei(GL_BLEND,this->buffer);
}

BlendEquation::BlendEquation(GLenum mode){
  this->mode=mode;
}
void BlendEquation::operator()(){
  glBlendEquation(this->mode);
}

BlendEquationSeparate::BlendEquationSeparate(
    GLenum modeRGB,
    GLenum modeAlpha){
  this->modeRGB   = modeRGB;
  this->modeAlpha = modeAlpha;
}
void BlendEquationSeparate::operator()(){
  glBlendEquationSeparate(this->modeRGB,this->modeAlpha);
}

BlendEquationi::BlendEquationi(
    GLuint buffer,
    GLenum mode){
  this->buffer = buffer;
  this->mode   = mode;
}
void BlendEquationi::operator()(){
  glBlendEquationi(this->buffer,this->mode);
}

BlendEquationSeparatei::BlendEquationSeparatei(
    GLuint buffer,
    GLenum modeRGB,
    GLenum modeAlpha){
  this->buffer    = buffer;
  this->modeRGB   = modeRGB;
  this->modeAlpha = modeAlpha;
}
void BlendEquationSeparatei::operator()(){
  glBlendEquationSeparatei(
      this->buffer,
      this->modeRGB,
      this->modeAlpha);
}

BlendFunc::BlendFunc(GLenum src,GLenum dst){
  this->src = src;
  this->dst = dst;
}
void BlendFunc::operator()(){
  glBlendFunc(this->src,this->dst);
}

BlendFuncSeparate::BlendFuncSeparate(
    GLenum srcRGB,
    GLenum dstRGB,
    GLenum srcAlpha,
    GLenum dstAlpha){
  this->srcRGB   = srcRGB;
  this->dstRGB   = dstRGB;
  this->srcAlpha = srcAlpha;
  this->dstAlpha = dstAlpha;
}
void BlendFuncSeparate::operator()(){
  glBlendFuncSeparate(
      this->srcRGB,
      this->dstRGB,
      this->srcAlpha,
      this->dstAlpha);
}

BlendFunci::BlendFunci(
    GLuint buffer,
    GLenum src,
    GLenum dst){
  this->buffer = buffer;
  this->src    = src;
  this->dst    = dst;
}
void BlendFunci::operator()(){
  glBlendFunci(this->buffer,this->src,this->dst);
}

BlendFuncSeparatei::BlendFuncSeparatei(
    GLuint buffer,
    GLenum srcRGB,
    GLenum dstRGB,
    GLenum srcAlpha,
    GLenum dstAlpha){
  this->buffer   = buffer;
  this->srcRGB   = srcRGB;
  this->dstRGB   = dstRGB;
  this->srcAlpha = srcAlpha;
  this->dstAlpha = dstAlpha;
}
void BlendFuncSeparatei::operator()(){
  glBlendFuncSeparatei(
      this->buffer,
      this->srcRGB,
      this->dstRGB,
      this->srcAlpha,
      this->dstAlpha);
}

BlendColor::BlendColor(
    GLfloat red,
    GLfloat green,
    GLfloat blue,
    GLfloat alpha){
  this->red   = red;
  this->green = green;
  this->blue  = blue;
  this->alpha = alpha;
}
void BlendColor::operator()(){
  glBlendColor(this->red,this->green,this->blue,this->alpha);
}

