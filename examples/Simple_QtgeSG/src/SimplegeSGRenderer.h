#pragma once

#include <QuickRendererBase.h>

#include <memory>


namespace ge{
   namespace glsg{
      class GLScene;
   }

   namespace gl{
   class Context;
   }
   namespace sg
   {
      class Scene;
   }
}

namespace fsg
{
   class SimpleVT;

   class SimplegeSGRenderer : public QuickRendererBase
   {
      Q_OBJECT
   public:
      SimplegeSGRenderer(QObject * parent = 0);
      void setupGLState();
   public slots:
      virtual void beforeRendering() override;
      virtual void onOGLContextCreated(QOpenGLContext * context) override;
      virtual void setScene(std::shared_ptr<ge::sg::Scene>& loadedScene);

   protected:
      virtual void update();


      std::shared_ptr<ge::gl::Context> gl;
      std::shared_ptr<ge::sg::Scene> scene;
      std::shared_ptr<ge::glsg::GLScene> glscene;
      std::shared_ptr<fsg::SimpleVT> VT;
      bool _needToProcessScene;
   };

}