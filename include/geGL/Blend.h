#pragma once

#include<geGL/BlendCommands.h>
#include<geGL/OpenGLCommon.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT Blend
    {
      private:
        ge::core::CommandContainer   _enable;
        ge::core::CommandContainer   _disable;
        ge::core::CommandContainer * _enablei;
        ge::core::CommandContainer * _disablei;

        ge::core::Command *  _equationCommand;
        bool             _refEquationCommand;
        ge::core::Command *  _equationSeparateCommand;
        bool             _refEquationSeparateCommand;
        ge::core::Command ** _equationiCommand;
        bool          *  _refEquationiCommand;
        ge::core::Command ** _equationSeparateiCommand;
        bool          *  _refEquationSeparateiCommand;
        ge::core::Command *  _funcCommand;
        bool             _refFuncCommand;
        ge::core::Command *  _funcSeparateCommand;
        bool             _refFuncSeparateCommand;
        ge::core::Command ** _funciCommand;
        bool          *  _refFunciCommand;
        ge::core::Command ** _funcSeparateiCommand;
        bool          *  _refFuncSeparateiCommand;
        ge::core::Command *  _colorCommand;
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
        virtual void operator()();
    };
  }//ogl
}//ge

