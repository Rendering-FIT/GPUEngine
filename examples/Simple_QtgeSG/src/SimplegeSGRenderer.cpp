#include <SimplegeSGRenderer.h>
#include <geGL/geGL.h>
#include <geCore/Text.h>
#include <QOpenGLContext>
#include <glsg/GLSceneProcessor.h>
#include <glsg/GLScene.h>
#include <SimpleVT.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;
using namespace fsg;

fsg::SimplegeSGRenderer::SimplegeSGRenderer(QObject* parent)
   : QuickRendererBase(parent)
   , _needToProcessScene(false)
   , VT(new SimpleVT())
   , gl(nullptr)
   , scene(nullptr)
   , glscene(nullptr)
{
}

void SimplegeSGRenderer::setupGLState()
{
   gl->glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
   gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   gl->glEnable(GL_DEPTH_TEST);
   gl->glViewport(0, 0, 800, 600);
}

void fsg::SimplegeSGRenderer::beforeRendering()
{
   update();
   setupGLState();

   VT->draw();
   _qqw->resetOpenGLState();
}

void fsg::SimplegeSGRenderer::onOGLContextCreated(QOpenGLContext* context)
{
   context->makeCurrent(_qqw);

   //init geGL gl context
   ge::gl::init();
   gl = make_shared<ge::gl::Context>();
   VT->gl = gl;

   //load shaders
   string shaderDir(APP_RESOURCES"/shaders/");
   shared_ptr<ge::gl::Shader> simple_vs(make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::core::loadTextFile(shaderDir + "simple_vs.glsl")));
   shared_ptr<ge::gl::Shader> simple_fs(make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::core::loadTextFile(shaderDir + "simple_fs.glsl")));
   shared_ptr<ge::gl::Program> prog = make_shared<ge::gl::Program>(simple_vs, simple_fs);
   VT->program = prog;

   //setup perspective
   glm::mat4 perpective = glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 1000.f);
   glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, -1, -5));
   prog->setMatrix4fv("projection", glm::value_ptr(perpective));
   prog->setMatrix4fv("model", glm::value_ptr(model));

   context->doneCurrent();
}

void fsg::SimplegeSGRenderer::setScene(std::shared_ptr<ge::sg::Scene>& loadedScene)
{
   if(loadedScene == scene) return;
   scene = loadedScene;
   _needToProcessScene = true;
}

void fsg::SimplegeSGRenderer::update()
{
   if(_needToProcessScene)
   {
      glscene = ge::glsg::GLSceneProcessor::processScene(scene,gl);
      VT->setScene(glscene);
      VT->processScene();
      _needToProcessScene = false;
   }
}