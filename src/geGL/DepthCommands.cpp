#include <geGL/DepthCommands.h>

using namespace ge::gl;

DepthFunc::DepthFunc(GLenum func){
  this->set(func);
}
void DepthFunc::operator()(){
  glDepthFunc(this->_func);
}
void DepthFunc::set(GLenum func){
  this->_func = func;
}
GLenum DepthFunc::get(){
  return this->_func;
}

DepthMask::DepthMask(GLboolean mask){
  this->set(mask);
}
void DepthMask::operator()(){
  glDepthMask(this->_mask);
}
void DepthMask::set(GLboolean mask){
  this->_mask = mask;
}
GLboolean DepthMask::get(){
  return this->_mask;
}

ClearDepth::ClearDepth(GLdouble value){
  this->set(value);
}
void ClearDepth::operator()(){
  glClearDepth(this->_value);
}
void ClearDepth::set(GLdouble value){
  this->_value = value;
}
GLdouble ClearDepth::get(){
  return this->_value;
}

ClearDepthf::ClearDepthf(GLfloat value){
  this->set(value);
}
void ClearDepthf::operator()(){
  glClearDepthf(this->_value);
}
void ClearDepthf::set(GLfloat value){
  this->_value = value;
}
GLfloat ClearDepthf::get(){
  return this->_value;
}


DepthFuncR::DepthFuncR(GLenum*func){
  this->set(func);
}
void DepthFuncR::operator()(){
  if(this->_func)glDepthFunc(*this->_func);
}
void DepthFuncR::set(GLenum*func){
  this->_func = func;
}
GLenum*DepthFuncR::get(){
  return this->_func;
}

DepthMaskR::DepthMaskR(GLboolean*mask){
  this->set(mask);
}
void DepthMaskR::operator()(){
  if(this->_mask)glDepthMask(*this->_mask);
}
void DepthMaskR::set(GLboolean*mask){
  this->_mask = mask;
}
GLboolean*DepthMaskR::get(){
  return this->_mask;
}

ClearDepthR::ClearDepthR(GLdouble*value){
  this->set(value);
}
void ClearDepthR::operator()(){
  if(this->_value)glClearDepth(*this->_value);
}
void ClearDepthR::set(GLdouble*value){
  this->_value = value;
}
GLdouble*ClearDepthR::get(){
  return this->_value;
}

ClearDepthfR::ClearDepthfR(GLfloat*value){
  this->set(value);
}
void ClearDepthfR::operator()(){
  if(this->_value)glClearDepthf(*this->_value);
}
void ClearDepthfR::set(GLfloat*value){
  this->_value = value;
}
GLfloat*ClearDepthfR::get(){
  return this->_value;
}

