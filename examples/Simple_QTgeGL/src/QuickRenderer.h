#pragma once

#include <QObject>
#include <QQuickWindow>

class QuickRenderer : public QObject
{
   Q_OBJECT
public:

   QuickRenderer(QObject * parent = 0);

   void setParentWindow(QQuickWindow * qqw);
   inline QQuickWindow *parentWindow() { return _qqw; }
public slots:
   virtual void beforeRendering();
   virtual void onOGLContextCreated(QOpenGLContext * context);
   virtual void onSceneGraphInvalidated();
   virtual void onFrameSwapped();
protected:
   QQuickWindow *_qqw;
};