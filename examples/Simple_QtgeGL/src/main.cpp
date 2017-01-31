#include <BasicQuickRenderer.h>

#include <QGuiApplication>

int main(int argc, char** argv)
{
   QGuiApplication app(argc, argv);

   QQuickWindow qw;
   qw.resize(800, 600);

   /* The ownership is transfered to QQuickWindow in the constructor
    * and to Qt's are responsible for deleting it.
    * http://doc.qt.io/qt-5/qobject.html#dtor.QObject
    */
   new fsg::BasicQuickRenderer(&qw);


   qw.show();

   return app.exec();
}