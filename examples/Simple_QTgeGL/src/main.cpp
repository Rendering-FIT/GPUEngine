#define WIN32_LEAN_AND_MEAN

#include <BasicQuickRenderer.h>

#include <QGuiApplication>

int main(int argc, char** argv)
{
   QGuiApplication app(argc, argv);

   QQuickWindow qw;
   qw.resize(800, 600);
   fsg::BasicQuickRenderer basicRenderer = new fsg::BasicQuickRenderer(&qw);
   //QuickRenderer basicRenderer(&qw);


   qw.show();

   return app.exec();
}