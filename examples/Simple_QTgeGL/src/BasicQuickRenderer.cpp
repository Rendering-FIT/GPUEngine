#define WIN32_LEAN_AND_MEAN
#include <geGL/geGL.h>
#include <geCore/Text.h>
#include <BasicQuickRenderer.h>
#include <QOpenGLContext>
#include <QDebug>

using namespace ge::gl;
using namespace std;


fsg::BasicQuickRenderer::BasicQuickRenderer(QObject* parent)
   : QuickRenderer(parent)
   , triagProgram(nullptr)
   , gl(nullptr)
{
}

/**
 * Update scene. Advance animations, react to user input etc.
 * Here you do the simulation step.
 */
void fsg::BasicQuickRenderer::update()
{

}

/**
 * Setup common basic OGL state for your vizualization. Beware, the
 * Qt has its own setup due to gui rendering. For example blending
 * function may be set differently.
 */
void fsg::BasicQuickRenderer::setupGLstate()
{
   gl->glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
   gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   gl->glBindTexture(GL_TEXTURE_2D, 0);
   gl->glEnable(GL_DEPTH_TEST);
   gl->glViewport(0, 0, _qqw->width(), _qqw->height());
}

/**
 * Here do your drawing.
 */
void fsg::BasicQuickRenderer::draw()
{
   qDebug() << "draw";
   triagProgram->use();
   dummyVAO->bind();
   gl->glDrawArrays(GL_TRIANGLES, 0, 3);
}

void fsg::BasicQuickRenderer::beforeRendering()
{
   qDebug() << "before rendering";
   update(); //update scene (nothing needed so far)
   setupGLstate(); //setup OGL state - be mindfull that we are using someone elses (QtQuick) context so we have no guarantees about the incoming state
   draw(); //draw the scene
   _qqw->resetOpenGLState(); // as stated above we are not owning the context, so wee need to return it in expected state
}

/**
 * This function is called when the context is created. Here you should
 * do the general init of things that have the application wide lifetime.
*/
void fsg::BasicQuickRenderer::onOGLContextCreated(QOpenGLContext* context)
{
   qDebug() << "onOGLContextCreated";
   context->makeCurrent(_qqw);

   
   //init geGL gl context
   ge::gl::init();
   gl = make_shared<Context>();

   string shaders_dir(APP_RESOURCES + std::string("/shaders/"));

   //load shaders
   std::shared_ptr<ge::gl::Shader>simple_vs(new ge::gl::Shader(GL_VERTEX_SHADER, ge::core::loadTextFile(shaders_dir + "triag_vs.glsl")));
   std::shared_ptr<ge::gl::Shader>simple_fs(new ge::gl::Shader(GL_FRAGMENT_SHADER, ge::core::loadTextFile(shaders_dir + "red_fs.glsl")));
   triagProgram = make_shared<ge::gl::Program>(simple_vs, simple_fs);
   
   //create empty VAO, need because of OGL spec
   dummyVAO = make_shared<ge::gl::VertexArray>();

   context->doneCurrent();
}