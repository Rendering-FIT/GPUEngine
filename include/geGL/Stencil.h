#pragma once

#include<geCore/Command.h>
#include<geGL/OpenGLCommon.h>
#include<geGL/StencilCommands.h>

namespace ge{
  namespace gl{
    /**
     * @brief This class GEGL_EXPORT represents manager of stencil commands
     */
    class GEGL_EXPORT Stencil: public ge::core::Command
    {
      private:
        ge::core::CommandContainer _enableDisable;  ///<gl{En,Dis}able(GL_STENCIL)
        ge::core::CommandContainer _func;           ///<glStencilFunc
        ge::core::CommandContainer _op;             ///<glStencilOp
        ge::core::CommandContainer _funcSeparate[2];///<glStencilFuncSeparate
        ge::core::CommandContainer _opSeparate  [2];///<glStencilOpSeparate

        unsigned _faceToIndex       (GLenum face);///<this method translate face to index
        void     _mergeFuncSeparate ();///<this method merges two glStencilFuncSeparate commands
        void     _createFuncSeparate(GLenum face,GLenum func,GLint ref,GLuint mask);
        void     _mergeOpSeparate   ();///<this method merges two glStencilOpSeparate commands
        void     _createOpSeparate  (GLenum face,GLenum sfail,GLenum dpfail,GLenum dppass);
      public:
        /**
         * @brief Constructor
         */
        Stencil();
        /**
         * @brief Destructor
         */
        ~Stencil();
        /**
         * @brief Enable stencilling
         */
        void enable();
        /**
         * @brief Disable stencilling
         */
        void disable();
        /**
         * @brief Set gl{En,Dis}able(GL_STENCIL) command
         *
         * @param enableDisableCommand gl{En,Dis}able(GL_STENCIL) command
         */
        void enableDisable(EnableDisable*enableDisableCommand);
        /**
         * @brief Ignore enabling command
         */
        void ignore();
        /**
         * @brief Set glStencilFunc command
         *
         * @param func func type
         * @param ref  ref value
         * @param mask mask value
         */
        void func(GLenum func,GLint ref,GLuint mask);
        /**
         * @brief Insert referenced glStencilFunc command
         *
         * @param func referenced glStencilFunc command
         */
        void func(StencilFunc*func);
        /**
         * @brief Ignore glStencilFunc command
         */
        void ignoreFunc();
        /**
         * @brief Set glStencilFuncSeparate command
         *
         * @param face face
         * @param func func type
         * @param ref  ref value
         * @param mask mask value
         */
        void funcSeparate(GLenum face,GLenum func,GLint ref,GLuint mask);
        /**
         * @brief Insert referenced glStencilFuncSeparate command
         *
         * @param funcSeparate glStencilFuncSeparate command
         */
        void funcSeparate(StencilFuncSeparate*funcSeparate);
        /**
         * @brief Ignore glStencilFuncSeparate command
         *
         * @param face ignored face
         */
        void ignoreFuncSeparate(GLenum face);
        /**
         * @brief Set glStencilOp command
         *
         * @param sfail  sfail  operation
         * @param dpfail dpfail operation
         * @param dppass dppass operation
         */
        void op(GLenum sfail,GLenum dpfail,GLenum dppass);
        /**
         * @brief Insert referenced glStencilOp command
         *
         * @param op glStencilOp command
         */
        void op(StencilOp*op);
        /**
         * @brief Ignore glStencilOp command
         */
        void ignoreOp();
        /**
         * @brief Set glStencilOpSeparate command
         *
         * @param face   face
         * @param sfail  sfail  operation
         * @param dpfail dpfail operation
         * @param dppass dppass operation
         */
        void opSeparate(GLenum face,GLenum sfail,GLenum dpfail,GLenum dppass);
        /**
         * @brief Insert referenced glStencilOpSeparate command
         *
         * @param opSeparate glStencilOpSeparate command
         */
        void opSeparate(StencilOpSeparate*opSeparate);
        /**
         * @brief Ignore glStencilOpSeparate command
         *
         * @param face ignored face
         */
        void ignoreOpSeparate(GLenum face);
        /**
         * @brief Apply all set commands
         */
        void apply();
        virtual void operator()();
    };
  }//namespace gl
}//namespace ge

