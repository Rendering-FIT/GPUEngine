#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <geGL/geGL.h>
#include <geGL/Program.h>
#include <geRG/RenderingContext.h>
#include <geRG/Transformation.h>
#include <geUtil/ArgumentObject.h>
#include <geAd/SDLWindow/SDLWindow.h>
#include <typeinfo> // MSVC 2013 requires this rather at the end of headers to compile successfully
#include <typeindex>
#include <fstream>
#include <sstream>

using namespace std;
using namespace ge::rg;


static void init(unsigned windowWidth,unsigned windowHeight);
static void idleCallback(void*);


static ge::ad::SDLMainLoop mainLoop;
static shared_ptr<ge::ad::SDLWindow> window;

static string fileName;
static shared_ptr<ge::gl::Program> glProgram;
static list<shared_ptr<Mesh>> meshList;


int main(int argc,char* argv[])
{
   // argument parser
   ge::util::ArgumentObject* args=new ge::util::ArgumentObject(argc,argv);

   // file name
   if(argc>1)
   {
      for(int i=1; i<argc; i++)
         if(argv[i][0]!='-') {
            fileName=argv[i];
            break;
         }
   }

   // window
   window=std::make_shared<ge::ad::SDLWindow>(atoi(args->getArg("-w","800").c_str()),
                                              atoi(args->getArg("-h","600").c_str()));
   if(args->isPresent("-f"))
      window->setFullscreen(ge::ad::SDLWindow::FULLSCREEN);
   if(!window->createContext("rendering",430,ge::ad::SDLWindow::CORE)) {
      std::cout<<"Error: Can not create OpenGL context."<<std::endl;
      return EXIT_FAILURE;
   }
   mainLoop.addWindow("primaryWindow",window);
   mainLoop.setIdleCallback(idleCallback);

   // rendering context
   ge::gl::init(SDL_GL_GetProcAddress);
   RenderingContext::setCurrent(make_shared<RenderingContext>());

   // init scene and main loop
   init(window->getWidth(),window->getHeight());
   mainLoop.operator()();

   // clean up
   delete args;

   return 0;
}


static void idleCallback(void*)
{
   RenderingContext::current()->frame();
   window->swap();

   // check for OpenGL errors
   int e=RenderingContext::current()->gl.glGetError();
   if(e!=GL_NO_ERROR)
      cout<<"OpenGL errror after frame rendering: "<<e<<endl;
}


shared_ptr<Mesh> generateMesh(const vector<glm::vec3>& coordBuffer,
                              const vector<glm::vec2>& texCoordBuffer,
                              const vector<glm::vec3>& normalBuffer)
{
   if(coordBuffer.empty())
      return shared_ptr<Mesh>();
   if(texCoordBuffer.size()!=0 && texCoordBuffer.size()!=coordBuffer.size()) {
      cout<<"Error: faces do not have consistent structure."<<endl;
      return shared_ptr<Mesh>();
   }
   if(normalBuffer.size()!=0 && normalBuffer.size()!=coordBuffer.size()) {
      cout<<"Error: faces do not have consistent structure."<<endl;
      return shared_ptr<Mesh>();
   }

   // attribute configuration
   AttribConfig::ConfigData config;
   config.attribTypes.push_back(AttribType::Vec3);
   if(normalBuffer.size()!=0)
      config.attribTypes.push_back(AttribType::Vec3);
   if(texCoordBuffer.size()!=0)
      config.attribTypes.push_back(AttribType::Vec2);
   config.ebo=false;
   config.updateId();

   // temporary list of attributes
   vector<const void*> attribList;
   attribList.emplace_back(coordBuffer.data());
   if(normalBuffer.size()!=0)
      attribList.emplace_back(normalBuffer.data());
   if(texCoordBuffer.size()!=0)
      attribList.emplace_back(texCoordBuffer.data());

   // alloc space for vertices and indices in AttribStorage
   // and for primitives in RenderingContext::PrimitiveStorage
   shared_ptr<Mesh> mesh=make_shared<Mesh>();
   mesh->allocData(config,coordBuffer.size(),0,1); // numVertices,numIndices,numPrimitives

   // upload vertices to AttribStorage
   mesh->uploadVertices(attribList.data(),
                        attribList.size(),
                        coordBuffer.size()); // numVertices

   // upload primitives to RenderingContext::PrimitiveStorage
   PrimitiveGpuData primitiveGpuData(coordBuffer.size(),0,false);
   Primitive primitive(GL_TRIANGLES,0);
   mesh->setAndUploadPrimitives(&primitiveGpuData,
                                &primitive,
                                1); // numPrimitives

   return mesh;
}


template<typename T>
bool checkDataAndPush(const std::vector<T>& data,std::vector<T>& buffer,const vector<int>& indices,int i)
{
   // data might not be present (normals or texture coordinates can be missing) -> return true
   if(data.size()==0)
      return true;

   // not enought indices -> return false
   if(i>=int(indices.size()))
      return false;

   int j=indices[i];
   if(j>0) {
      j--;
      // test positive vertex index for out of range
      if(unsigned(j)>=data.size())
         return false;
   }
   else if(j<0) {
      // test negative vertex index for out of range
      j=data.size()+j;
      if(j<0)
         return false;
   }
   else
      // index zero is not allowed
      return false;

   // push data to buffer
   buffer.push_back(data[j]);
   return true;
}


static void init(unsigned windowWidth,unsigned windowHeight)
{
   // setup OpenGL
   auto& gl=RenderingContext::current()->gl;
   gl.glEnable(GL_DEPTH_TEST);
   gl.glDepthFunc(GL_LEQUAL);
   gl.glEnable(GL_CULL_FACE);

   // setup shaders and prepare GLSL program
   glProgram=make_shared<ge::gl::Program>(
      make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,
         "#version 330\n"
         "layout(location=0)  in vec3 coords;\n"
         "layout(location=12) in mat4 instancingMatrix;\n"
         "uniform mat4 mvp;\n"
         "void main()\n"
         "{\n"
         "   gl_Position = mvp*instancingMatrix*vec4(coords,1.f);\n"
         "}\n"),
      make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,
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
   //glProgram->set("mvp",1,GL_FALSE,glm::value_ptr(mvp));
   glProgram->setMatrix4fv("mvp",glm::value_ptr(mvp));

   // state set
   StateSetManager::GLState *glState=RenderingContext::current()->createGLState();
   glState->set("bin",type_index(typeid(int)),reinterpret_cast<void*>(0)); // bin 0 is for ambient pass
   glState->set("glProgram",type_index(typeid(shared_ptr<ge::gl::Program>*)),&glProgram);
   shared_ptr<StateSet> stateSet=RenderingContext::current()->getOrCreateStateSet(glState);
   delete glState;

   // transformation
   shared_ptr<Transformation> transformation=make_shared<Transformation>();
   transformation->uploadMatrix(glm::translate(glm::vec3(0.f,0.f,-10.f)));
   RenderingContext::current()->addTransformationGraph(transformation);


   if(fileName.empty())
      return;

   // open file
   ifstream f(fileName);

   vector<glm::vec3> coords;
   vector<glm::vec2> texCoords;
   vector<glm::vec3> normals;
   vector<int> vi;
   vector<int> ti;
   vector<int> ni;
   vector<glm::vec3> coordBuffer;
   vector<glm::vec2> texCoordBuffer;
   vector<glm::vec3> normalBuffer;
   while(f)
   {
      string token;
      f>>token;
      if(!f) break;

      const char *s=token.c_str();
      switch(s[0]) {

         case '#':
            f.ignore(0xffffffff,'\n');
            continue;

         case 'f': {

            // read the whole line
            string line;
            getline(f,line);

            // parse all vertices on the line
            stringstream ss(line);
            while(ss) {
               int i=0;
               char c;
               ss>>i; // parse vertex index
               if(i!=0)
                  vi.push_back(i);
               if(ss.peek()=='/') {
                  ss>>c;
                  if(ss.peek()=='/') {
                     i=0;
                     ss>>c>>i; // parse normal index
                     if(i!=0)
                        ni.push_back(i);
                  }
                  else {
                     i=0;
                     ss>>i; // parse texCoord index
                     if(i!=0)
                        ti.push_back(i);
                     if(ss.peek()=='/') {
                        i=0;
                        ss>>c>>i; // parse normal index
                        if(i!=0)
                           ni.push_back(i);
                     }
                  }
               }
            }

            // process the vertices of the line
            if((ti.size()==0 || ti.size()==vi.size()) &&
               (ni.size()==0 || ni.size()==vi.size()))
            {
               if(vi.size()==3)
               {
                  bool r=true;
                  for(int i=0; i<3; i++)
                     r&=checkDataAndPush(coords,coordBuffer,vi,i) &&
                        checkDataAndPush(texCoords,texCoordBuffer,ti,i) &&
                        checkDataAndPush(normals,normalBuffer,ni,i);
                  if(!r) {
                     cout<<"Error: invalid face indices."<<endl;
                     coordBuffer.clear();
                     texCoordBuffer.clear();
                     normalBuffer.clear();
                  }
               }
               else {
                  cout<<"Error: only 3 vertices are supported per face."<<endl;
               }
            }
            else {
               cout<<"Error: Face indices error. Model data are broken."<<endl;
            }

            // prepare for the next face
            vi.clear();
            ti.clear();
            ni.clear();
            continue;
         }

         case 'v':
            switch(s[1]) {
               case '\0': {
                  // coordinates are 3 or 4 floats and 3 floats might be appended as r,g,b for per-vertex color
                  // (only 3 floats coordinates implemented at the moment)
                  float x,y,z;
                  f>>x>>y>>z;
                  coords.push_back(glm::vec3(x,y,z));
                  continue;
               }
               case 'n': {
                  // normal is always 3 floats
                  float x,y,z;
                  f>>x>>y>>z;
                  normals.push_back(glm::vec3(x,y,z));
                  continue;
               }
               case 't': {
                  // texture coordinate is 2 or 3 floats
                  // (3 float support not implemented yet)
                  float u,v;
                  f>>u>>v;
                  texCoords.push_back(glm::vec2(u,v));
                  continue;
               }
               // 'p' (e.g. "vp") for parameter space vertices not implemented yet
            }
         default:
            cout<<"Unknown token \""<<token<<"\"\n"<<endl;
            f.ignore(0xffffffff,'\n');
      }
   }

   shared_ptr<Mesh> m=generateMesh(coordBuffer,texCoordBuffer,normalBuffer);
   if(m) {
      meshList.push_back(m);

      // create drawable
      m->createDrawable(transformation->getOrCreateMatrixList().get(),stateSet.get());
   }

   // unmap buffers
   // (it has to be done before rendering)
   RenderingContext::current()->unmapBuffers();

   // check for OpenGL errors
   int e=RenderingContext::current()->gl.glGetError();
   if(e!=GL_NO_ERROR)
      cout<<"OpenGL errror after init(): "<<e<<endl;
}
