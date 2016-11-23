
#include <QOpenGLContext>
#include <QuickRenderer.h>
#include <QDebug>

QuickRenderer::QuickRenderer(QObject * parent /*= 0*/)
   : QObject(parent)
   , _qqw(nullptr)
{
   QQuickWindow* qqw = dynamic_cast<QQuickWindow *>(parent);
   if (NULL != qqw)
   {
      setParentWindow(qqw);      
   }
}

void QuickRenderer::beforeRendering()
{
   qDebug() << "beforeRendering";
   if (!_qqw)
   {
      qDebug() << "Set parent QQuickWindow with setParentWindow().";
      return;
   }

   //_qqw->resetOpenGLState();
}

void QuickRenderer::onOGLContextCreated(QOpenGLContext * context)
{
   qDebug() << "Context created";
}

void QuickRenderer::setParentWindow(QQuickWindow * qqw)
{
   if (_qqw !=NULL)
   {
      if (_qqw == qqw) return;

      disconnect(qqw, SIGNAL(beforeRendering()), this, SLOT(beforeRendering()));
      disconnect(qqw, SIGNAL(openglContextCreated(QOpenGLContext *)), this, SLOT(onOGLContextCreated(QOpenGLContext *)));
      disconnect(qqw, SIGNAL(sceneGraphInvalidated()), this, SLOT(onSceneGraphInvalidated()));
      disconnect(qqw, SIGNAL(frameSwapped()), this, SLOT(onFrameSwapped()));
   }
   _qqw = qqw;
   connect(qqw, SIGNAL(beforeRendering()), this, SLOT(beforeRendering()), Qt::DirectConnection);
   connect(qqw, SIGNAL(openglContextCreated(QOpenGLContext *)), this, SLOT(onOGLContextCreated(QOpenGLContext *)), Qt::DirectConnection);
   connect(qqw, SIGNAL(sceneGraphInvalidated()), this, SLOT(onSceneGraphInvalidated()), Qt::DirectConnection);
   connect(qqw, SIGNAL(frameSwapped()), this, SLOT(onFrameSwapped()), Qt::DirectConnection);
   _qqw->setClearBeforeRendering(false);
}

void QuickRenderer::onSceneGraphInvalidated()
{
   qDebug() << "Context will be released";
}

void QuickRenderer::onFrameSwapped()
{
   qDebug() << "Frame Swapped";
}

