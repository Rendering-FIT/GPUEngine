#ifndef _CBLEND_HPP_
#define _CBLEND_HPP_

#include <geGL/Standard/OpenGL.h>
#include <geGL/PerFragmentOperation/BlendCommands.h>
#include <geGL/Standard/OpenGLCommon.h>

namespace ge
{
  namespace ogl{
    class GE_EXPORT Blend
    {
      private:
        CommandContainer   _enable;
        CommandContainer   _disable;
        CommandContainer * _enablei;
        CommandContainer * _disablei;

        Command *  _equationCommand;
        bool             _refEquationCommand;
        Command *  _equationSeparateCommand;
        bool             _refEquationSeparateCommand;
        Command ** _equationiCommand;
        bool          *  _refEquationiCommand;
        Command ** _equationSeparateiCommand;
        bool          *  _refEquationSeparateiCommand;
        Command *  _funcCommand;
        bool             _refFuncCommand;
        Command *  _funcSeparateCommand;
        bool             _refFuncSeparateCommand;
        Command ** _funciCommand;
        bool          *  _refFunciCommand;
        Command ** _funcSeparateiCommand;
        bool          *  _refFuncSeparateiCommand;
        Command *  _colorCommand;
        bool             _refColorCommand;
        unsigned _maxBuffers;
        void _init();
        void _mergeEnableDisableSeparate();
        void _setEnable(GLuint buffer,bool enable);
        void _deleteEnablei();
        void _deleteEquationi();
        void _deleteEquationSeparatei();
        void _deleteFunci();
        void _deleteFuncSeparatei();
      public:
        Blend();
        Blend(unsigned MaxBuffers);
        ~Blend();
        void enable();
        void enable(Enable*enableCommand);
        void disable();
        void disable(Disable*disableCommand);
        void ignore();

        void enable(GLuint  buffer);
        void enable(Enablei*enableCommand);
        void disable(GLuint buffer);
        void disable(Disablei*disableCommand);
        void ignore(GLuint  buffer);

        void blendEquation(GLenum mode);
        void ignoreBlendEquation();

        void blendEquationSeparate(GLenum modeRGB,GLenum modeAlpha);
        void ignoreBlendEquationSeparate();

        void blendEquation(GLuint buffer,GLenum mode);
        void ignoreBlendEquation(GLuint buffer);

        void blendEquationSeparate(GLuint buffer,GLenum modeRGB,GLenum modeAlpha);
        void ignoreBlendEquationSeparate(GLuint buffer);

        void blendFunc(GLenum src,GLenum dst);
        void ignoreBlendFunc();

        void blendFuncSeparate(GLenum srcRGB,GLenum dstRGB,GLenum srcAlpha,GLenum dstAlpha);
        void ignoreBlendFuncSeparate();

        void blendFunc(GLuint buffer,GLenum src,GLenum dst);
        void ignoreBlendFunc(GLuint buffer);

        void blendFuncSeparate(GLuint buffer,GLenum srcRGB,GLenum dstRGB,GLenum srcAlpha,GLenum dstAlpha);
        void ignoreBlendFuncSeparate(GLuint buffer);

        void blendColor(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha);
        void ignoreBlendColor();

        void apply();
    };
  }//ogl
}//ge

#endif//_CBLEND_HPP_
