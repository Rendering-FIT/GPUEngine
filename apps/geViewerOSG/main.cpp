#include <string>
#include <sstream>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geGL/BufferObject.h>
#include <geGL/DebugMessage.h>
#include <geGL/geGL.h>
#include <geGL/ProgramObject.h>
#include <geRG/Model.h>
#include <geRG/RenderingContext.h>
#include <geRG/Transformation.h>
#include <geAd/OsgImport/OsgImport.h>
#include <geAd/WindowObject/WindowObject.h>
#include <geUtil/ArgumentObject.h>
#include <osg/ref_ptr>
#include <osgDB/ReadFile>

using namespace std;
using namespace ge::gl;
using namespace ge::rg;


void Init();
void Idle();
void Mouse();
void Wheel(int d);


struct SContextParam{
  unsigned    Version;
  std::string Profile;
  std::string Flag;
}ContextParam;


struct SWindowParam{
  unsigned Size[2];
  bool     Fullscreen;
}WindowParam;


bool DisableAnttweakbar=true;
ge::util::ArgumentObject *Args;
ge::util::WindowObject   *Window;

static bool useARBShaderDrawParameters=false;
static shared_ptr<ProgramObject> processInstanceProgram;
static string fileName;
static shared_ptr<Model> model;


int main(int Argc,char*Argv[])
{
  Args=new ge::util::ArgumentObject(Argc,Argv);

  DisableAnttweakbar=true;

  //window args
  WindowParam.Size[0]    = atoi(Args->getArg("-w","800").c_str());
  WindowParam.Size[1]    = atoi(Args->getArg("-h","600").c_str());
  WindowParam.Fullscreen = Args->isPresent("-f");

  //context args
  ContextParam.Version = atoi(Args->getArg("--context-version","430").c_str());
  ContextParam.Profile = Args->getArg("--context-profile","core");
  ContextParam.Flag    = Args->getArg("--context-flag","debug");

  // file name
  if(Argc>1)
  {
     int i=Argc-1;
     if(Argv[i][0]!='-')
        if(Argc==2 || Argv[i-1][0]!='-')  fileName=Argv[1];
  }

  Window=new ge::util::WindowObject(
      WindowParam.Size[0],
      WindowParam.Size[1],
      WindowParam.Fullscreen,
      Idle,
      Mouse,
      !DisableAnttweakbar,
      ContextParam.Version,
      ContextParam.Profile,
      ContextParam.Flag);

  glewExperimental=GL_TRUE;
  glewInit();
  glGetError(); // glewInit() might generate GL_INVALID_ENUM on some glew versions
                // as said on https://www.opengl.org/wiki/OpenGL_Loading_Library,
                // problem seen on CentOS 7.1 (release date 2015-03-31) with GLEW 1.9 (release date 2012-08-06)
  ge::gl::init();
  RenderingContext::setCurrent(make_shared<RenderingContext>());
  RenderingContext::current()->setUseARBShaderDrawParameters(useARBShaderDrawParameters);

  // OpenGL debugging messages
  //ge::gl::setDefaultDebugMessage();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDisable(GL_CULL_FACE);

  Init();
  Window->mainLoop();
  delete Window;
  delete Args;
  return 0;
}


void Mouse(){
}


void Wheel(int){
}


#if 0 // uncomment for debugging purposes (it is commented to kill warning of unused function)
static void printIntBufferContent(ge::gl::BufferObject *bo,unsigned numInts)
{
   cout<<"Buffer contains "<<numInts<<" int values:"<<endl;
   unsigned *p=(unsigned*)bo->map(GL_MAP_READ_BIT);
   if(p==nullptr) return;
   unsigned i;
   for(i=0; i<numInts; i++)
   {
      cout<<*(p+i)<<"  ";
      if(i%4==3)
         cout<<endl;
   }
   bo->unmap();
   if(i%4!=0)
      cout<<endl;
   cout<<endl;
}
#endif


void Idle()
{
   // clear screen
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   // compute transformation matrices
   RenderingContext::current()->evaluateTransformationGraph();
   RenderingContext::current()->matrixStorage()->unmap();

   // prepare for rendering
   RenderingContext::current()->stateSetStorage()->map(BufferStorageAccess::WRITE);
   RenderingContext::current()->setupRendering();
   RenderingContext::current()->stateSetStorage()->unmap();

   // indirect buffer update - setup and start compute shader
   processInstanceProgram->use();
   unsigned numInstances=RenderingContext::current()->drawCommandStorage()->firstItemAvailableAtTheEnd();
   processInstanceProgram->set("numToProcess",numInstances);
   RenderingContext::current()->primitiveStorage()->bufferObject()->bindBase(GL_SHADER_STORAGE_BUFFER,0);
   RenderingContext::current()->drawCommandStorage()->bufferObject()->bindBase(GL_SHADER_STORAGE_BUFFER,1);
   RenderingContext::current()->matrixListControlStorage()->bufferObject()->bindBase(GL_SHADER_STORAGE_BUFFER,2);
   RenderingContext::current()->drawIndirectBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,3);
   RenderingContext::current()->stateSetStorage()->bufferObject()->bindBase(GL_SHADER_STORAGE_BUFFER,4);
   glDispatchCompute((numInstances+63)/64,1,1);

   // wait for compute shader
   GLsync syncObj=glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE,0);
#if 0 // glWaitSync does not work on my Quadro K1000M (Keppler architecture), drivers 352.21
   //glFlush();
   //glWaitSync(syncObj,0,GL_TIMEOUT_IGNORED);
#else
   glClientWaitSync(syncObj,GL_SYNC_FLUSH_COMMANDS_BIT,1e9);
#endif
   glDeleteSync(syncObj);

   // bind buffers for rendering
   RenderingContext::current()->drawIndirectBuffer()->bind(GL_DRAW_INDIRECT_BUFFER);
   if(useARBShaderDrawParameters)
      RenderingContext::current()->matrixStorage()->bufferObject()->bindBase(GL_SHADER_STORAGE_BUFFER,0);

#if 0
   printIntBufferContent(RenderingContext::current()->drawCommandStorage()->bufferObject(),
                         RenderingContext::current()->drawCommandStorage()->firstItemAvailableAtTheEnd()*3);
   printIntBufferContent(RenderingContext::current()->primitiveStorage()->bufferObject(),
                         RenderingContext::current()->primitiveStorage()->firstItemAvailableAtTheEnd()*3);
   printIntBufferContent(RenderingContext::current()->drawIndirectBuffer(),
                         RenderingContext::current()->drawCommandStorage()->firstItemAvailableAtTheEnd()*5);
#endif

   // render ambient scene
   RenderingContext::current()->render();

   Window->swap();
}




void Init()
{
   // load model
   if(!fileName.empty())
   {
      osg::ref_ptr<osg::Node> root=osgDB::readNodeFile(fileName);
      if(root==nullptr)
         cout<<"Failed to load file "<<fileName<<endl;
      else
      {
         model=ge::osgImport::import(root);
      }

      // release OSG memory
      root=nullptr;
      osgDB::Registry::instance()->closeAllLibraries();
      osgDB::Registry::instance(true);
   }

   if(model)
   {
      // instantiate model with given transformation matrix
      shared_ptr<Transformation> t=make_shared<Transformation>();
      const float m[16] = {
         1.f, 0.f, 0.f, 0.f,
         0.f, 1.f, 0.f, 0.f,
         0.f, 0.f, 1.f, 0.f,
         0.f, 0.f,-10.f, 1.f,
      };
      t->allocTransformationGpuData();
      t->uploadMatrix(m);
      t->addChild(model->transformationRoot());
      RenderingContext::current()->addTransformationGraph(t);
   }

   // unmap buffers
   // (it has to be done before rendering)
   RenderingContext::current()->unmapBuffers();

   ge::gl::initShadersAndPrograms();
   RenderingContext::current()->init();
   glm::mat4 projection=glm::perspective(float(60.*M_PI/180.),float(WindowParam.Size[0])/WindowParam.Size[1],1.f,100.f);
   auto ambientProgram=RenderingContext::current()->getGLProgram(idof(Ambient,geRG_GLPrograms));
   ambientProgram->use();
   ambientProgram->set("globalAmbientLight",0.2f,0.2f,0.2f,1.f);
   ambientProgram->set("projection",1,GL_FALSE,glm::value_ptr(projection));
   ambientProgram->set("colorTexture",int(0));
   auto simplifiedPhongProgram=RenderingContext::current()->getGLProgram(idof(Ambient,geRG_GLPrograms));
   simplifiedPhongProgram->use();
   simplifiedPhongProgram->set("projection",1,GL_FALSE,glm::value_ptr(projection));
   simplifiedPhongProgram->set("specularAndShininess",0.33f,0.33f,0.33f,0.f); // shininess in alpha
   simplifiedPhongProgram->set("lightPosition",0.f,0.f,0.f,1.f); // in eye coordinates, w must be 0 or 1
   simplifiedPhongProgram->set("lightColor",1.f,1.f,1.f);
   simplifiedPhongProgram->set("lightAttenuation",1.f,0.f,0.f);
   simplifiedPhongProgram->set("colorTexture",int(0));

   processInstanceProgram=make_shared<ProgramObject>(
      GL_COMPUTE_SHADER,
      "#version 430\n"
      "\n"
      "layout(local_size_x=64,local_size_y=1,local_size_z=1) in;\n"
      "\n"
      "layout(std430,binding=0) restrict readonly buffer DrawCommandBuffer {\n"
      "   uint drawCommandBuffer[];\n"
      "};\n"
      "layout(std430,binding=1) restrict readonly buffer InstanceBuffer {\n"
      "   uint instanceBuffer[];\n"
      "};\n"
      "layout(std430,binding=2) restrict readonly buffer InstancingMatricesControlBuffer {\n"
      "   uint instancingMatricesControlBuffer[];\n"
      "};\n"
      "layout(std430,binding=3) restrict writeonly buffer IndirectBuffer {\n"
      "   uint indirectBuffer[];\n"
      "};\n"
      "layout(std430,binding=4) restrict buffer StateSetBuffer {\n"
      "   uint stateSetBuffer[];\n"
      "};\n"
      "\n"
      "uniform uint numToProcess;\n"
      "\n"
      "void main()\n"
      "{\n"
      "   if(gl_GlobalInvocationID.x>=numToProcess)\n"
      "      return;\n"
      "\n"
      "   // instance buffer data\n"
      "   uint instanceIndex=gl_GlobalInvocationID.x*3;\n"
      "   uint drawCommandOffset4=instanceBuffer[instanceIndex+0];\n"
      "   uint matrixControlOffset4=instanceBuffer[instanceIndex+1];\n"
      "   uint stateSetDataOffset4=instanceBuffer[instanceIndex+2];\n"
      "\n"
      "   // instancing matrices data\n"
      "   uint matrixCollectionOffset64=instancingMatricesControlBuffer[matrixControlOffset4+0];\n"
      "   uint numMatrices=instancingMatricesControlBuffer[matrixControlOffset4+1];\n"
      "\n"
      "   // compute increment and get indirectBufferOffset\n"
      "   uint countAndIndexedFlag=drawCommandBuffer[drawCommandOffset4+0];\n"
      "   uint indirectBufferIncrement=4+bitfieldExtract(countAndIndexedFlag,31,1); // make increment 4 or 5\n"
      "   uint indirectBufferOffset4=atomicAdd(stateSetBuffer[stateSetDataOffset4],indirectBufferIncrement);\n"
      "\n"
      "   // write indirect buffer data\n"
      "   indirectBuffer[indirectBufferOffset4]=countAndIndexedFlag&0x7fffffff; // indexCount or vertexCount\n"
      "   indirectBufferOffset4++;\n"
      "   indirectBuffer[indirectBufferOffset4]=numMatrices; // instanceCount\n"
      "   indirectBufferOffset4++;\n"
      "   uint first=drawCommandBuffer[drawCommandOffset4+1]; // firstIndex or firstVertex\n"
      "   uint vertexOffset=drawCommandBuffer[drawCommandOffset4+2]; // vertexOffset\n"
      "   if(countAndIndexedFlag>=0x80000000) {\n"
      "      indirectBuffer[indirectBufferOffset4]=first; // firstIndex\n"
      "      indirectBufferOffset4++;\n"
      "      indirectBuffer[indirectBufferOffset4]=vertexOffset; // vertexOffset\n"
      "      indirectBufferOffset4++;\n"
      "   } else {\n"
      "      indirectBuffer[indirectBufferOffset4]=first+vertexOffset; // firstVertex\n"
      "      indirectBufferOffset4++;\n"
      "   }\n"
      "   indirectBuffer[indirectBufferOffset4]=matrixCollectionOffset64; // base instance\n"
      "}\n");
}
