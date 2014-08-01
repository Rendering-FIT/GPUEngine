#include <geGL/PerFragmentOperation/Stencil.h>

namespace ge
{
  namespace gl
  {
    unsigned Stencil::_faceToIndex(GLenum face){
      return(unsigned)(face==GL_BACK);
    }
    void Stencil::_mergeFuncSeparate(){
      StencilFuncSeparate*a=(StencilFuncSeparate*)this->_funcSeparate[0].command;
      StencilFuncSeparate*b=(StencilFuncSeparate*)this->_funcSeparate[1].command;
      if(a && b && a->func == b->func && a->ref==b->ref && a->mask == b->mask)
        this->func(a->func,a->ref,a->mask);
    }
    void Stencil::_createFuncSeparate(GLenum face,GLenum func,GLint ref,GLuint mask){
      unsigned faceIndex=this->_faceToIndex(face);
      this->_funcSeparate[faceIndex].free();
      this->_funcSeparate[faceIndex].command = new StencilFuncSeparate(face,func,ref,mask);
      this->_funcSeparate[faceIndex].ref     = false;
    }
    void Stencil::_mergeOpSeparate(){
      StencilOpSeparate*a=(StencilOpSeparate*)this->_opSeparate[0].command;
      StencilOpSeparate*b=(StencilOpSeparate*)this->_opSeparate[1].command;
      if(a && b && a->sfail == b->sfail && a->dpfail == b->dpfail && a->dppass == b->dppass)
        this->op(a->sfail,a->dpfail,a->dppass);
    }
    void Stencil::_createOpSeparate(GLenum face,GLenum sfail,GLenum dpfail,GLenum dppass){
      unsigned faceIndex=this->_faceToIndex(face);
      this->_opSeparate[faceIndex].free();
      this->_opSeparate[faceIndex].command = new StencilOpSeparate(face,sfail,dpfail,dppass);
      this->_opSeparate[faceIndex].ref     = false;
    }
    Stencil::Stencil(){
      this->_enableDisable  .reset();
      this->_func           .reset();
      this->_op             .reset();
      this->_funcSeparate[0].reset();
      this->_funcSeparate[1].reset();
      this->_opSeparate  [0].reset();
      this->_opSeparate  [1].reset();
    }
    Stencil::~Stencil(){
      this->_enableDisable  .free();
      this->_func           .free();
      this->_op             .free();
      this->_funcSeparate[0].free();
      this->_funcSeparate[1].free();
      this->_opSeparate  [0].free();
      this->_opSeparate  [1].free();
    }
    void Stencil::enable(){
      this->_enableDisable.free();
      this->_enableDisable.command = new EnableDisable(GL_STENCIL,true);
      this->_enableDisable.ref     = false;
    }
    void Stencil::disable(){
      this->_enableDisable.free();
      this->_enableDisable.command = new EnableDisable(GL_STENCIL,false);
      this->_enableDisable.ref     = false;
    }
    void Stencil::enableDisable(EnableDisable*enableDisableCommand){
      this->_enableDisable.free();
      this->_enableDisable.command = enableDisableCommand;
      this->_enableDisable.ref     = true;
    }
    void Stencil::ignore(){
      this->_enableDisable.free();
    }
    void Stencil::func(
        GLenum func,
        GLint  ref,
        GLuint mask){
      this->_funcSeparate[0].free();
      this->_funcSeparate[1].free();
      this->_func.free();
      this->_func.command = new StencilFunc(func,ref,mask);
      this->_func.ref     = false;
    }
    void Stencil::func(StencilFunc*funcCommand){
      this->_funcSeparate[0].free();
      this->_funcSeparate[1].free();
      this->_func.free();
      this->_func.command = funcCommand;
      this->_func.ref     = true;
    }
    void Stencil::ignoreFunc(){
      this->_func.free();
    }
    void Stencil::funcSeparate(
        GLenum face,
        GLenum func,
        GLint  ref,
        GLuint mask){
      if(face==GL_FRONT_AND_BACK)this->func(func,ref,mask);
      else this->_createFuncSeparate(face,func,ref,mask);
      this->_mergeFuncSeparate();
    }
    void Stencil::funcSeparate(
        StencilFuncSeparate*funcSeparateCommand){ 
      unsigned faceIndex=this->_faceToIndex(funcSeparateCommand->face);
      this->_funcSeparate[faceIndex].free();
      this->_funcSeparate[faceIndex].command = funcSeparateCommand;
      this->_funcSeparate[faceIndex].ref     = true;
      if(this->_funcSeparate[0].command&&this->_funcSeparate[1].command)
        this->ignoreFunc();
    }
    void Stencil::ignoreFuncSeparate(GLenum face){
      unsigned faceIndex=this->_faceToIndex(face);
      this->_funcSeparate[faceIndex].free();
    }
    void Stencil::op(
        GLenum sfail,
        GLenum dpfail,
        GLenum dppass){
      this->_opSeparate[0].free();
      this->_opSeparate[1].free();
      this->_op.free();
      this->_op.command = new StencilOp(sfail,dpfail,dppass);
      this->_op.ref     = false;
    }
    void Stencil::op(
        StencilOp*opCommand){
      this->_opSeparate[0].free();
      this->_opSeparate[1].free();
      this->_op.free();
      this->_op.command = opCommand;
      this->_op.ref     = true;
    }
    void Stencil::ignoreOp(){
      this->_op.free();
    }
    void Stencil::opSeparate(
        GLenum face,
        GLenum sfail,
        GLenum dpfail,
        GLenum dppass){
      if(face==GL_FRONT_AND_BACK)this->op(sfail,dpfail,dppass);
      else this->_createOpSeparate(face,sfail,dpfail,dppass);
      this->_mergeOpSeparate();
    }
    void Stencil::opSeparate(
        StencilOpSeparate*opSeparateCommand){
      unsigned faceIndex=this->_faceToIndex(opSeparateCommand->face);
      this->_opSeparate[faceIndex].free();
      this->_opSeparate[faceIndex].command = opSeparateCommand;
      this->_opSeparate[faceIndex].ref     = true;
      if(this->_opSeparate[0].command&&this->_opSeparate[1].command)
        this->ignoreOp();
    }
    void Stencil::ignoreOpSeparate(GLenum face){
      unsigned faceIndex=this->_faceToIndex(face);
      this->_opSeparate[faceIndex].free();
    }
    void Stencil::apply(){
      this->_enableDisable.apply();
      this->_func.apply();
      this->_funcSeparate[0].apply();
      this->_funcSeparate[1].apply();
      this->_op.apply();
      this->_opSeparate[0].apply();
      this->_opSeparate[1].apply();
    }
  }//namespace ogl
}//namespace ge
