#include <QOpenGLContext>
#include <QuickRendererBase.h>
#include <QDebug>

/**
 * If parent is a QQuickWindow or subclas then calls setParentWindow().
 * @see setParentWindow()
 */
QuickRendererBase::QuickRendererBase(QObject * parent /*= 0*/)
   : QObject(parent)
   , _qqw(nullptr)
{
   QQuickWindow* qqw = dynamic_cast<QQuickWindow *>(parent);
   if (NULL != qqw)
   {
      setParentWindow(qqw);      
   }
}

/**
 * Reimplement to make your rendering. Opengl context should be active here.
 */
void QuickRendererBase::beforeRendering()
{
   qDebug() << "beforeRendering";
   if (!_qqw)
   {
      qDebug() << "Set parent QQuickWindow with setParentWindow().";
      return;
   }

   //when you change the opengl state you must call this at the end.
   //_qqw->resetOpenGLState();
}

/**
 * Reimplement to make you gl initialization here. Context context was just created.
 * It is not current and \b needs to be released at the end of the function.
 */
void QuickRendererBase::onOGLContextCreated(QOpenGLContext * context)
{
   qDebug() << "Context created";
}

/**
 * Make connection with QQuickWindow rendering related signals.
 * \li beforeRendering()
 * \li openglContextCreated(QOpenGLContext *)
 * \li sceneGraphInvalidated()
 * \li frameSwapped()
 * If called with the same window that it is already connected to then nothing will happen. If called with null
 * the signals get disconnected. When called with another window then signals get reconnected.
 */
void QuickRendererBase::setParentWindow(QQuickWindow * qqw)
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
   if(qqw != NULL)
   {
      connect(qqw, SIGNAL(beforeRendering()), this, SLOT(beforeRendering()), Qt::DirectConnection);
      connect(qqw, SIGNAL(openglContextCreated(QOpenGLContext *)), this, SLOT(onOGLContextCreated(QOpenGLContext *)), Qt::DirectConnection);
      connect(qqw, SIGNAL(sceneGraphInvalidated()), this, SLOT(onSceneGraphInvalidated()), Qt::DirectConnection);
      connect(qqw, SIGNAL(frameSwapped()), this, SLOT(onFrameSwapped()), Qt::DirectConnection);
      _qqw->setClearBeforeRendering(false);
   }
}

/**
 * Reimplement to react to opengl context invalidation. Possible cleanup
 */
void QuickRendererBase::onSceneGraphInvalidated()
{
   qDebug() << "Context will be released";
}

/**
 * Reimplement to react on frame swap.
 */
void QuickRendererBase::onFrameSwapped()
{
   qDebug() << "Frame Swapped";
}

