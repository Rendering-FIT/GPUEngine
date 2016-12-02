#include "apprg.h"

#include <geRG/RenderingContext.h>
#include <geRG/StateSetManager.h>
#include <geRG/StateSet.h>
#include <geRG/AttribType.h>
#include <geCore/Command.h>
#include <geRG/FlexibleUniform.h>
#include <geRG/Transformation.h>

#include <typeindex>

using namespace std;
using namespace ge;
using namespace glm;

#define log() if(options.verbose) std::cout

AppRG::AppRG(Options const & o) :App(o) {
}

void AppRG::init() {
  SDL_GL_SetSwapInterval(0);
  ImGui_ImplSdlGL3_Init(windowHandle);

  prepareRgContext();

  createTextures();
  createStateSets();
  mesh = createMesh();


  context->unmapBuffers();
}
void AppRG::draw() {
  updateState();
  updateCamera();

  ImGui_ImplSdlGL3_NewFrame(windowHandle);
  stats->startFrame();


  cameraTransformation->uploadMatrix(view);

  context->frame();


  stats->endFrame();
  stats->draw();
  ImGui::Render();
  window->swap();
}

void AppRG::prepareRgContext() {
  log() << "AppRG::prepareRgContext()\n";

  context = make_shared<rg::RenderingContext>();
  rg::RenderingContext::setCurrent(context);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_CULL_FACE);

  program = context->getProgram(rg::RenderingContext::ProgramType::AMBIENT_AND_LIGHT_PASS, true);

  updateCamera();
  program->use();
  program->setMatrix4fv("projection", value_ptr(projection));
  program->set("lightPosition", 0.f, 0.f, 0.f, 1.f);
  program->set("lightColor", 1.f, 1.f, 1.f);
  program->set("lightAttenuation", 1.f, 0.f, 0.f);


  cameraTransformation = make_shared<rg::Transformation>();
  context->addTransformationGraph(cameraTransformation);
}

void AppRG::createTextures() {
  log() << "AppRG::createTextures\n";
  int size = options.textureSize;
  for (int i = 0; i < options.textureCount; i++) {
    auto tex = make_shared<gl::Texture>();
    tex->create(GL_TEXTURE_2D, GL_RGBA, 0, size, size);
    uint* data = generateTextureData(size);
    tex->setData2D(data, GL_RGBA, GL_UNSIGNED_BYTE);
    tex->generateMipmap();
    tex->texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    tex->texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    tex->texParameteri(GL_TEXTURE_WRAP_R, GL_REPEAT);
    tex->texParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    textures.push_back(tex);
  }
}

std::shared_ptr<ge::rg::StateSet> AppRG::createStateSet(std::shared_ptr<ge::gl::Texture> tex) {
  auto materialCommandList = make_shared<core::SharedCommandList>();
  auto diffuseUniform = make_shared<rg::FlexibleUniform4f>("color", 1.f, 1.f, 1.f, 1.f);
  materialCommandList->push_back(diffuseUniform);
  auto specularUniform = make_shared<rg::FlexibleUniform4f>("specularAndShininess", 1.f, 1.f, 1.f, 32.f);
  materialCommandList->push_back(specularUniform);

  rg::StateSetManager::GLState *meshState = context->createGLState();
  meshState->set("bin", type_index(typeid(int)), reinterpret_cast<void*>(0));
  meshState->set("glProgram", type_index(typeid(shared_ptr<gl::Program>*)), &program);
  meshState->set("colorTexture", type_index(typeid(&tex)), &tex);
  meshState->set("uniformList", type_index(typeid(shared_ptr<core::Command>*)), &materialCommandList);
  auto stateSet = context->getOrCreateStateSet(meshState);
  delete meshState;

  return stateSet;
}

void AppRG::createStateSets() {
  log() << "AppRG::createStateSets\n";
  whiteStateSet = createStateSet(nullptr);
  for (int i = 0; i < options.textureCount; i++) {
    auto ss = createStateSet(textures[i]);
    texStateSets.push_back(ss);
  }
}

void AppRG::interactive(int cubes, int textures, DrawMode mode) {
  log() << "AppRG::interactive\n";
  App::interactive(cubes, textures, mode);
  prepareDrawables();

}

void AppRG::calibrate(int cubes, int textures, DrawMode mode) {
  log() << "AppRG::interactive\n";
  App::calibrate(cubes, textures, mode);
  prepareDrawables();
}

void AppRG::test(int cubes, int textures, DrawMode mode) {
  log() << "AppRG::test\n";
  App::test(cubes, textures, mode);
  prepareDrawables();
}

void AppRG::addCubes(int count) {
  log() << "AppRG::addCubes " << count << "\n";

  if (count > 0) {
    for (int i = 0; i < count; i++) {
      int cubeId = (int)transforms.size();
      auto tr = createTransform(cubeId);
      transforms.push_back(tr);
      auto ss = currentTextures ? texStateSets[cubeId%currentTextures] : whiteStateSet;
      auto id = mesh->createDrawable(tr->getOrCreateMatrixList().get(), ss.get());
      drawables.push_back(id);
    }
    currentCubes += count;
  } else {
    for (int i = 0; i < -count; i++) {
      auto &id = drawables.back();      
      mesh->deleteDrawable(id);
      drawables.pop_back();
      transforms.pop_back();
    }
    currentCubes += count;
  }
  context->unmapBuffers();
}

void AppRG::clear() {
  log() << "AppRG::clear\n";
  for (auto &dr : drawables) {
    mesh->deleteDrawable(dr);
  }
  drawables.clear();
  transforms.clear();
  log() << "AppRG::clear end\n";
}

std::shared_ptr<ge::rg::Mesh> AppRG::createMesh() {
  vector<Vertex> vertices;
  generateCubeVertices(vertices);

  vector<vec3> positions;
  vector<vec3> normals;
  vector<vec2> texCoords;
  for (auto& v : vertices) {
    positions.push_back(v.pos);
    normals.push_back(v.norm);
    texCoords.push_back(v.tc);
  }

  uint vertexCount = (uint)vertices.size();

  rg::AttribConfig::AttribTypeList attribTypeList;
  attribTypeList.push_back(rg::AttribType::Vec3);
  attribTypeList.push_back(rg::AttribType::Vec3);
  attribTypeList.push_back(rg::AttribType::Empty);
  attribTypeList.push_back(rg::AttribType::Vec2);

  rg::AttribConfig attribConfig(attribTypeList, false, context.get());

  vector<const void*> attribList;
  attribList.emplace_back(positions.data());
  attribList.emplace_back(normals.data());
  attribList.emplace_back(nullptr);
  attribList.emplace_back(texCoords.data());


  shared_ptr<rg::Mesh> mesh = make_shared<rg::Mesh>();
  mesh->allocData(attribConfig, vertexCount, 0, 1);
  mesh->uploadVertices(attribList.data(), unsigned(attribList.size()), vertexCount);

  rg::PrimitiveGpuData primitiveGpuData(vertexCount, 0, false);
  rg::Primitive primitive(GL_TRIANGLES, 0);
  mesh->setAndUploadPrimitives(&primitiveGpuData, &primitive, 1);

  return mesh;
}

std::shared_ptr<ge::rg::Transformation> AppRG::createTransform(int i) {
  mat4 m = getMatrix(i);
  auto tr = make_shared<ge::rg::Transformation>();
  tr->uploadMatrix(m);
  cameraTransformation->addChild(tr);
  return tr;
}

void AppRG::prepareDrawables() {
  log() << "AppRG::prepareDrawables\n";
  clear();

  switch (currentDrawMode) {
  case INSTANCED: {
    for (int i = 0; i < currentCubes; i++) {
      // one transform per cube
      auto tr = createTransform(i);
      transforms.push_back(tr);
      auto ss = currentTextures ? texStateSets[i%currentTextures] : whiteStateSet;
      auto id = mesh->createDrawable(tr->getOrCreateMatrixList().get(), ss.get());
      drawables.push_back(id);
    }

    context->unmapBuffers();
    break;
  }

  default:
    if (options.verbose) {
      cout << "geRG-" << drawModeToString(currentDrawMode) << " not supported\n";
    }
    currentState = IDLE;
  }


}

void AppRG::recomputeMatrices(int count) {
  for (int i = 0; i < count; i++) {
    auto &tr = transforms[i];
    tr->uploadMatrix(getMatrix(i));
  }
}


