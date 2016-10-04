#include <string>
#include <typeinfo>
#include <typeindex>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geGL/Buffer.h>
#include <geGL/geGL.h>
#include <geGL/Program.h>
#include <geRG/Mesh.h>
#include <geRG/RenderingContext.h>
#include <geRG/StateSet.h>
#include <geAd/SDLWindow/SDLWindow.h>
#include <geUtil/ArgumentObject.h>

using namespace std;
using namespace ge::gl;
using namespace ge::rg;


static void init(unsigned windowWidth,unsigned windowHeight);
static void idleCallback();


static ge::ad::SDLMainLoop mainLoop;
static shared_ptr<ge::ad::SDLWindow> window;

static shared_ptr<Program> glProgram;
static Mesh meshDirectNI;
static Mesh meshDirectI;
static Mesh meshIndirectNI;
static Mesh meshIndirectI;


int main(int,char*[])
{
   window=std::make_shared<ge::ad::SDLWindow>();
   if(!window->createContext("rendering",430,ge::ad::SDLWindow::CORE)) {
      std::cout<<"Error: Can not create OpenGL context."<<std::endl;
      return EXIT_FAILURE;
   }

   mainLoop.addWindow("primaryWindow",window);
   mainLoop.setIdleCallback(idleCallback);

   ge::gl::init(SDL_GL_GetProcAddress);
   RenderingContext::setCurrent(make_shared<RenderingContext>());
   init(window->getWidth(),window->getHeight());
   mainLoop.operator()();

   return 0;
}


static void idleCallback()
{
   RenderingContext::current()->frame();

   // draw meshDirectNI
   glProgram->use();
   auto& gl=glProgram->getContext();
   meshDirectNI.attribStorage()->bind();
   unsigned baseIndex=meshDirectNI.attribStorage()->vertexArrayAllocation(meshDirectNI.verticesDataId()).startIndex;
   gl.glDrawArrays(GL_TRIANGLES,baseIndex+0,3);
   gl.glDrawArrays(GL_TRIANGLES,baseIndex+3,3);

   // draw meshDirectI
   meshDirectI.attribStorage()->bind();
   baseIndex=meshDirectI.attribStorage()->indexArrayAllocation(meshDirectI.indicesDataId()).startIndex;
   gl.glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)(intptr_t(baseIndex)*4+0));
   gl.glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)(intptr_t(baseIndex)*4+12));

   window->swap();
}


static void init(unsigned windowWidth,unsigned windowHeight)
{
   // setup OpenGL
   auto rc=RenderingContext::current().get();
   auto& gl=rc->gl;
   gl.glEnable(GL_DEPTH_TEST);
   gl.glDepthFunc(GL_LEQUAL);
   gl.glDisable(GL_CULL_FACE);

   // setup shaders and scene
   glProgram=make_shared<Program>(
      make_shared<Shader>(GL_VERTEX_SHADER,
         "#version 330\n"
         "layout(location=0) in vec3 coords;\n"
         "uniform mat4 mvp;\n"
         "void main()\n"
         "{\n"
         "   gl_Position = mvp*vec4(coords,1.f);\n"
         "}\n"),
      make_shared<Shader>(GL_FRAGMENT_SHADER,
         "#version 330\n"
         "layout(location=0) out vec4 fragColor;\n"
         "void main()\n"
         "{\n"
         "   fragColor=vec4(1.f,1.f,0.,1.);\n"
         "}\n"));
   glm::mat4 modelView(1.f); // identity
   glm::mat4 projection=glm::perspective(float(60.*M_PI/180.),
                                         float(windowWidth)/float(windowHeight),1.f,100.f);
   glm::mat4 mvp=modelView*projection;
   glProgram->use();
   glProgram->setMatrix4fv("mvp",glm::value_ptr(mvp));

   StateSetManager::GLState *glState=rc->createGLState();
   glState->set("bin",type_index(typeid(int)),reinterpret_cast<void*>(0)); // bin 0 is for ambient pass
   glState->set("glProgram",type_index(typeid(shared_ptr<ge::gl::Program>*)),&glProgram);
   shared_ptr<StateSet> stateSet=rc->getOrCreateStateSet(glState);
   delete glState;


   AttribConfig::AttribTypeList attribTypes;
   attribTypes.push_back(AttribType::Vec3);

   // top-left geometry - raw rendering, not using indirect draw optimization
   // (only coordinates in AttribStorage while manual OpenGL setup and draw calls are required)
   // (non-indexed, not indirect draw)
   constexpr float z=-10.f;
   constexpr float niShiftX=-1.5f;
   constexpr float directShiftY=3.0f;
   const vector<glm::vec3> twoTrianglesNI = {
      glm::vec3(niShiftX+0,directShiftY+0,z),
      glm::vec3(niShiftX+0,directShiftY+1,z),
      glm::vec3(niShiftX+1,directShiftY+0,z),
      glm::vec3(niShiftX+0,directShiftY+0,z),
      glm::vec3(niShiftX+0,directShiftY-1,z),
      glm::vec3(niShiftX-1,directShiftY+0,z),
   };

   vector<const void*> attribList;
   attribList.reserve(1);
   attribList.emplace_back(twoTrianglesNI.data());
   meshDirectNI.allocData(AttribConfig(attribTypes,false,rc),6,0,0);
   meshDirectNI.uploadVertices(attribList.data(),(uint32_t)attribList.size(),(uint32_t)twoTrianglesNI.size());

   // top-right geometry - the same as above but using indexing
   constexpr float iShiftX=1.5f;
   const vector<glm::vec3> twoTrianglesI = {
      glm::vec3(iShiftX+0,directShiftY+0,z),
      glm::vec3(iShiftX+0,directShiftY+1,z),
      glm::vec3(iShiftX+1,directShiftY+0,z),
      glm::vec3(iShiftX+0,directShiftY+0,z),
      glm::vec3(iShiftX+0,directShiftY-1,z),
      glm::vec3(iShiftX-1,directShiftY+0,z),
   };
   const vector<unsigned> indices = { 3, 1, 2, 3, 4, 5 };

   attribList[0]=twoTrianglesI.data();
   meshDirectI.allocData(AttribConfig(attribTypes,true,rc),6,6,0);
   meshDirectI.uploadVertices(attribList.data(),(uint32_t)attribList.size(),(uint32_t)twoTrianglesI.size());
   meshDirectI.uploadIndices(indices.data(),(uint32_t)indices.size());

   // bottom-left geometry - high level, using indirect rendering optimization
   // (non-indexed, using optimized rendering, using identity transformation matrix)
   constexpr float indirectShiftY=directShiftY-3.0f;
   const vector<glm::vec3> twoTrianglesIndirectNI = {
      glm::vec3(niShiftX+0,indirectShiftY+0,z),
      glm::vec3(niShiftX+0,indirectShiftY+1,z),
      glm::vec3(niShiftX+1,indirectShiftY+0,z),
      glm::vec3(niShiftX+0,indirectShiftY+0,z),
      glm::vec3(niShiftX+0,indirectShiftY-1,z),
      glm::vec3(niShiftX-1,indirectShiftY+0,z),
   };
   vector<PrimitiveGpuData> primitiveDataNI = {
      { 3,0,false },
      { 3,3,false }
   };
   const vector<unsigned> modesAndOffsets4 = {
      GL_TRIANGLES,0,
      GL_TRIANGLES,3,
   };

   attribList[0]=twoTrianglesIndirectNI.data();
   meshIndirectNI.allocData(AttribConfig(attribTypes,false,rc),6,0,(uint32_t)primitiveDataNI.size());
   meshIndirectNI.uploadVertices(attribList.data(),(uint32_t)attribList.size(),(uint32_t)twoTrianglesIndirectNI.size());
   meshIndirectNI.setAndUploadPrimitives(primitiveDataNI.data(),
                                         modesAndOffsets4.data(),(uint32_t)primitiveDataNI.size());
   shared_ptr<MatrixList> identity=make_shared<MatrixList>();
   identity->setNumMatrices(1);
   identity->setStartIndex(0);
   identity->uploadListControlData();
   identity->uploadMatrixData(RenderingContext::identityMatrix,0,1);
   meshIndirectNI.createDrawable(identity.get(),stateSet.get());

   // bottom-right geometry - high level, using indirect rendering optimization
   // (indexed, using optimized rendering)
   const vector<glm::vec3> twoTrianglesIndirectI = {
      glm::vec3(iShiftX+0,indirectShiftY+0,z),
      glm::vec3(iShiftX+0,indirectShiftY+1,z),
      glm::vec3(iShiftX+1,indirectShiftY+0,z),
      glm::vec3(iShiftX+0,indirectShiftY+0,z),
      glm::vec3(iShiftX+0,indirectShiftY-1,z),
      glm::vec3(iShiftX-1,indirectShiftY+0,z),
   };
   vector<PrimitiveGpuData> primitiveDataI = {
      { 3,0,true },
      { 3,3,true }
   };

   attribList[0]=twoTrianglesIndirectI.data();
   meshIndirectI.allocData(AttribConfig(attribTypes,true,rc),6,6,(uint32_t)primitiveDataI.size());
   meshIndirectI.uploadVertices(attribList.data(),(uint32_t)attribList.size(),(uint32_t)twoTrianglesIndirectI.size());
   meshIndirectI.uploadIndices(indices.data(),(uint32_t)indices.size());
   meshIndirectI.setAndUploadPrimitives(primitiveDataI.data(),
                                        modesAndOffsets4.data(),(uint32_t)primitiveDataI.size());
   meshIndirectI.createDrawable(identity.get(),stateSet.get());


   // unmap buffers
   // (it has to be done before rendering)
   rc->unmapBuffers();
}
