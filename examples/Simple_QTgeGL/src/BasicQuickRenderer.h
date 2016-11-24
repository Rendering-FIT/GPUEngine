#pragma once

#include <QuickRendererBase.h>

#include <memory>

namespace ge
{
   namespace gl
   {
      class Program;
      class VertexArray;
      class Context;
   }
}

namespace fsg
{
   /**
    *  Basic example of renderer class. It loads external shaders and draw simple triangle.
    */
   class BasicQuickRenderer : public QuickRendererBase
   {
      Q_OBJECT
   public:
      BasicQuickRenderer(QObject * parent = 0);

   protected:
      void update();
      void setupGLstate();
      void draw();

      std::shared_ptr<ge::gl::Context> gl;
      std::shared_ptr<ge::gl::Program> triagProgram;
      std::shared_ptr<ge::gl::VertexArray> dummyVAO;


   public slots:
      virtual void beforeRendering() override;
      virtual void onOGLContextCreated(QOpenGLContext * context) override;
   };
}