#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <geGL/geGL.h>
#include <geGL/Program.h>
#include <geRG/FlexibleUniform.h>
#include <geRG/RenderingContext.h>
#include <geRG/Transformation.h>
#include <geUtil/ArgumentObject.h>
#include <geAd/SDLWindow/SDLWindow.h>
#include <geAd/SDLOrbitManipulator/SDLOrbitManipulator.h>
#include <typeinfo> // MSVC 2013 requires this rather at the end of headers to compile successfully
#include <typeindex>
#include <fstream>
#include <sstream>
#include "Material.h"

using namespace std;
using namespace ge::rg;


static void init(unsigned windowWidth,unsigned windowHeight);
static void idleCallback(void*);


static ge::ad::SDLMainLoop mainLoop;
static shared_ptr<ge::ad::SDLWindow> window;
static ge::ad::SDLOrbitManipulator cameraManipulator;
static shared_ptr<Transformation> cameraTransformation;

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
   cameraManipulator.connect(window,SDL_BUTTON_RMASK);
   mainLoop.operator()();

   // clean up
   delete args;

   return 0;
}


static void idleCallback(void*)
{
   // update camera
   cameraTransformation->uploadMatrix(cameraManipulator.mat());

   // render scene
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
   mesh->allocData(config,unsigned(coordBuffer.size()),0,1); // numVertices,numIndices,numPrimitives

   // upload vertices to AttribStorage
   mesh->uploadVertices(attribList.data(),
                        unsigned(attribList.size()),
                        unsigned(coordBuffer.size())); // numVertices

   // upload primitives to RenderingContext::PrimitiveStorage
   PrimitiveGpuData primitiveGpuData(unsigned(coordBuffer.size()),0,false);
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
      j=int(data.size())+j;
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

   // setup camera manipulator and clipping planes
   glm::vec3 center(0.f,0.f,0.f);
   float radius=5.f;
   float zNear=radius*0.99f;
   float zFar=radius*3.01f;
   cameraManipulator.setCenter(center);
   cameraManipulator.setEye(center+glm::vec3(0.f,0.f,radius*2.f));

   // setup shaders and prepare GLSL program
   glProgram=RenderingContext::current()->getProgram(
         RenderingContext::ProgramType::AMBIENT_AND_LIGHT_PASS,true);
   glm::mat4 projection=glm::perspective(float(60.*M_PI/180.),
                                         float(windowWidth)/float(windowHeight),zNear,zFar);
   glProgram->use();
   glProgram->setMatrix4fv("projection",glm::value_ptr(projection));
   glProgram->set("colorTexturingMode",int(0));
   glProgram->set("colorTexture",int(0));
   glProgram->set("lightPosition",0.f,0.f,0.f,1.f);
   glProgram->set("lightColor",1.f,1.f,1.f);
   glProgram->set("lightAttenuation",1.f,0.f,0.f);

   // state set
   StateSetManager::GLState *glState=RenderingContext::current()->createGLState();
   glState->set("bin",type_index(typeid(int)),reinterpret_cast<void*>(0)); // bin 0 is for ambient pass
   glState->set("glProgram",type_index(typeid(shared_ptr<ge::gl::Program>*)),&glProgram);
   shared_ptr<StateSet> rootStateSet=RenderingContext::current()->getOrCreateStateSet(glState);
   delete glState;

   // transformation
   cameraTransformation=make_shared<Transformation>();
   RenderingContext::current()->addTransformationGraph(cameraTransformation);


   // empty file name
   if(fileName.empty())
      return;

   // path
   string path;
#if defined(__WIN32__) || defined(_WIN32)
   string::size_type i=fileName.find_last_of('\\');
#else
   string::size_type i=fileName.find_last_of('/');
#endif
   if(i!=string::npos)
      path=fileName.substr(0,i+1);

   // open file
   ifstream f(fileName);
   if(!f) {
      cout<<"Failed to open file \""<<fileName<<"\"."<<endl;
      return;
   }

   // initialize variables
   stringstream line;
   string lineBuf;
   string token;
   f.imbue(locale("en_US.UTF-8"));
   line.imbue(locale("en_US.UTF-8"));
   vector<glm::vec3> coords;
   vector<glm::vec2> texCoords;
   vector<glm::vec3> normals;
   vector<int> vi;
   vector<int> ti;
   vector<int> ni;
   vector<glm::vec3> coordBuffer;
   vector<glm::vec2> texCoordBuffer;
   vector<glm::vec3> normalBuffer;
   map<string,Material> materials;
   const Material *currentMaterial=defaultMaterial();

   // parsing loop
   while(true)
   {
      // read line
      getline(f,lineBuf);
      if(!f) break;
      line.clear();
      line.str(lineBuf);

      line>>token;
      if(!line) continue;
      const char *s=token.c_str();
      switch(s[0]) {

         case '\0':
         case '#':
            // ignore empty lines and comment lines
            continue;

         case 'v':
            switch(s[1]) {
               case '\0': {
                  // coordinates are 3 or 4 floats and 3 floats might be appended as r,g,b for per-vertex color
                  // (only 3 floats coordinates implemented at the moment)
                  float x,y,z;
                  line>>x>>y>>z;
                  coords.push_back(glm::vec3(x,y,z));
                  continue;
               }
               case 'n': {
                  // normal is always 3 floats
                  float x,y,z;
                  line>>x>>y>>z;
                  normals.push_back(glm::vec3(x,y,z));
                  continue;
               }
               case 't': {
                  // texture coordinate is 2 or 3 floats
                  // (3 float support not implemented yet)
                  float u,v;
                  line>>u>>v;
                  texCoords.push_back(glm::vec2(u,v));
                  continue;
               }
               // 'p' (e.g. "vp") for parameter space vertices not implemented yet
               default:
                  cout<<"Unknown line content \""<<lineBuf<<"\"\n"<<endl;
                  continue;
            }

         // faces
         case 'f': {

            // parse all indices on the line
            while(line) {
               int i=0;
               char c;
               line>>i; // parse vertex index
               if(i!=0)
                  vi.push_back(i);
               if(line.peek()=='/') {
                  line>>c;
                  if(line.peek()=='/') {
                     i=0;
                     line>>c>>i; // parse normal index
                     if(i!=0)
                        ni.push_back(i);
                  }
                  else {
                     i=0;
                     line>>i; // parse texCoord index
                     if(i!=0)
                        ti.push_back(i);
                     if(line.peek()=='/') {
                        i=0;
                        line>>c>>i; // parse normal index
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

         // parse mtl file
         case 'm':
            if(token=="mtllib") {
               string fileName;
               line>>fileName;
               parseMtl(path+fileName,materials);
               continue;
            }
            else {
               cout<<"Unknown line content \""<<lineBuf<<"\"\n"<<endl;
               continue;
            }

         // change material
         case 'u':
            if(token=="usemtl") {
               string name;
               line>>name;
               auto it=materials.find(name);
               if(it!=materials.end()) {

                  // create mesh and drawable for parsed geometry
                  shared_ptr<Mesh> m=generateMesh(coordBuffer,texCoordBuffer,normalBuffer);
                  if(m) {
                     meshList.push_back(m);

                     auto materialCommandList=make_shared<ge::core::SharedCommandList>();
                     const glm::vec3& diffuse=currentMaterial->diffuseColor;
                     auto diffuseUniform=make_shared<FlexibleUniform4f>("color",
                           diffuse.r,diffuse.g,diffuse.b,1.f-currentMaterial->transparency);
                     materialCommandList->push_back(diffuseUniform);
                     const glm::vec3& specular=currentMaterial->specularColor;
                     auto specularUniform=make_shared<FlexibleUniform4f>("specularAndShininess",
                           specular.r,specular.g,specular.b,currentMaterial->shininess);
                     materialCommandList->push_back(specularUniform);

                     // state set
                     StateSetManager::GLState *glState=RenderingContext::current()->createGLState();
                     glState->set("bin",type_index(typeid(int)),reinterpret_cast<void*>(0)); // bin 0 is for ambient pass
                     glState->set("glProgram",type_index(typeid(shared_ptr<ge::gl::Program>*)),&glProgram);
                     glState->set("uniformList",type_index(typeid(shared_ptr<ge::core::Command>*)),&materialCommandList);
                     shared_ptr<StateSet> stateSet=RenderingContext::current()->getOrCreateStateSet(glState);
                     delete glState;

                     // create drawable
                     m->createDrawable(cameraTransformation->getOrCreateMatrixList().get(),stateSet.get());
                  }

                  // prepare buffers for new geometry
                  coordBuffer.clear();
                  texCoordBuffer.clear();
                  normalBuffer.clear();

                  // set new material
                  currentMaterial=&it->second;

               } else
                  cout<<"Unknown material \""<<name<<"\"."<<endl;
               continue;
            }
            else {
               cout<<"Unknown line content \""<<lineBuf<<"\"\n"<<endl;
               continue;
            }

         default:
            cout<<"Unknown line content \""<<lineBuf<<"\"\n"<<endl;
      }
   }

   // create mesh and drawable for parsed geometry
   shared_ptr<Mesh> m=generateMesh(coordBuffer,texCoordBuffer,normalBuffer);
   if(m) {
      meshList.push_back(m);

      auto materialCommandList=make_shared<ge::core::SharedCommandList>();
      const glm::vec3& diffuse=currentMaterial->diffuseColor;
      auto diffuseUniform=make_shared<FlexibleUniform4f>("color",
            diffuse.r,diffuse.g,diffuse.b,1.f-currentMaterial->transparency);
      materialCommandList->push_back(diffuseUniform);
      const glm::vec3& specular=currentMaterial->specularColor;
      auto specularUniform=make_shared<FlexibleUniform4f>("specularAndShininess",
            specular.r,specular.g,specular.b,currentMaterial->shininess);
      materialCommandList->push_back(specularUniform);

      // state set
      StateSetManager::GLState *glState=RenderingContext::current()->createGLState();
      glState->set("bin",type_index(typeid(int)),reinterpret_cast<void*>(0)); // bin 0 is for ambient pass
      glState->set("glProgram",type_index(typeid(shared_ptr<ge::gl::Program>*)),&glProgram);
      glState->set("uniformList",type_index(typeid(shared_ptr<ge::core::Command>*)),&materialCommandList);
      shared_ptr<StateSet> stateSet=RenderingContext::current()->getOrCreateStateSet(glState);
      delete glState;

      // create drawable
      m->createDrawable(cameraTransformation->getOrCreateMatrixList().get(),stateSet.get());
   }

   // unmap buffers
   // (it has to be done before rendering)
   RenderingContext::current()->unmapBuffers();

   // check for OpenGL errors
   int e=RenderingContext::current()->gl.glGetError();
   if(e!=GL_NO_ERROR)
      cout<<"OpenGL errror after init(): "<<e<<endl;
}
