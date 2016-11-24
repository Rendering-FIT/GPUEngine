#include "apprg.h"

#include <geRG/RenderingContext.h>
#include <geRG/StateSetManager.h>
#include <geRG/StateSet.h>
#include <geRG/AttribType.h>
#include <geCore/Command.h>
#include <geRG/FlexibleUniform.h>
#include <geRG/Transformation.h>

#include <typeindex>
#include <algorithm>

using namespace std;
using namespace ge;
using namespace glm;

AppRG::AppRG() :App() {
}

void AppRG::init() {
  SDL_GL_SetSwapInterval(0);
  ImGui_ImplSdlGL3_Init(windowHandle);

  createContext();
  whiteStateSet = createStateSet();
  mesh = createMesh();
 // addCubes(100);
  context->unmapBuffers();
}
void AppRG::draw() {
  updateCamera();

  ImGui_ImplSdlGL3_NewFrame(windowHandle);
  cameraTransformation->uploadMatrix(view);

  context->frame();
  context->draw();

  fpsLabel();

  ImGui::Begin("Controls");
  static bool once = true;
  if (once) {
    ImGui::SetWindowPos(ImVec2(5, 350));
    once = false;
  }

  if (ImGui::Button("Add 10 Cubes"))addCubes(10);
  if (ImGui::Button("Add 100 Cubes"))addCubes(100);
  if (ImGui::Button("Add 1000 Cubes"))addCubes(1000);
  if (ImGui::Button("Remove 10 Cubes"))removeCubes(10);
  if (ImGui::Button("Remove 100 Cubes"))removeCubes(100);
  if (ImGui::Button("Remove 1000 Cubes"))removeCubes(1000);
  if (ImGui::Button("Remove all"))removeCubes(int(drawables.size()));

  ImGui::End();

  ImGui::Render();
  window->swap();
}

void AppRG::createContext() {
  context = make_shared<ProfilingContext>();
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

std::shared_ptr<ge::rg::StateSet> AppRG::createStateSet() {
  auto materialCommandList = make_shared<core::SharedCommandList>();
  auto diffuseUniform = make_shared<rg::FlexibleUniform4f>("color", 1.f, 1.f, 1.f, 1.f);
  materialCommandList->push_back(diffuseUniform);
  auto specularUniform = make_shared<rg::FlexibleUniform4f>("specularAndShininess", 1.f, 1.f, 1.f, 32.f);
  materialCommandList->push_back(specularUniform);

  shared_ptr<ge::gl::Texture> tex;
  rg::StateSetManager::GLState *meshState = context->createGLState();
  meshState->set("bin", type_index(typeid(int)), reinterpret_cast<void*>(0));
  meshState->set("glProgram", type_index(typeid(shared_ptr<gl::Program>*)), &program);
  meshState->set("colorTexture", type_index(typeid(&tex)), &tex);
  meshState->set("uniformList", type_index(typeid(shared_ptr<core::Command>*)), &materialCommandList);
  auto stateSet = context->getOrCreateStateSet(meshState);
  delete meshState;

  return stateSet;
}

void AppRG::addCubes(int count) {
  for (int i = 0; i < count; i++) {
    int cubeId = (int)transforms.size();
    auto tr = createTransform(cubeId);
    transforms.push_back(tr);
    auto ss = whiteStateSet;
    auto id = mesh->createDrawable(tr->getOrCreateMatrixList().get(), ss.get());
    drawables.push_back(id);
  }
  //std::cout << "transforms.size() " << transforms.size() << "\n";
  //std::cout << "drawables.size() " << drawables.size() << "\n";
}

void AppRG::removeCubes(int count) {
  count = (std::min)(count, (int)drawables.size());

  for (int i = 0; i < count; i++) {
    auto dr = drawables.back();
    mesh->deleteDrawable(dr);
    drawables.pop_back();
    transforms.pop_back();
  }
  //std::cout << "transforms.size() " << transforms.size() << "\n";
  //std::cout << "drawables.size() " << drawables.size() << "\n";
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
  int side = 10;
  vec3 offset = vec3(float(side));
  int x = i % side;
  int y = (i / side) % side;
  int z = i / (side*side);
  mat4 m = translate(mat4(), vec3(x, y, z)*2.0f - offset);

  auto tr = make_shared<ge::rg::Transformation>();
  tr->uploadMatrix(m);
  cameraTransformation->addChild(tr);
  return tr;
}