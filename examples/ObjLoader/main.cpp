#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <geGL/geGL.h>
#include <geGL/Program.h>
#include <geRG/RenderingContext.h>
#include <geRG/Transformation.h>
#include <geUtil/ArgumentObject.h>
#include <geAd/SDLWindow/SDLWindow.h>
#include <geAd/SDLWindow/SDLOrbitManipulator.h>
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
   glProgram=make_shared<ge::gl::Program>(
      make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,
         "#version 330\n"
         "\n"
         "layout(location=0)  in vec4 position;\n"
         "layout(location=1)  in vec3 normal;\n"
         "layout(location=3)  in vec2 texCoord;\n"
         "layout(location=12) in mat4 instancingMatrix;\n"
         "\n"
         "out VertexData {\n" // interfaces are supported since GLSL 1.5 (OpenGL 3.2)
         "   vec3 eyePosition;\n"
         "   vec3 eyeNormal;\n"
         "   vec2 texCoord;\n"
         "} o;\n"
         "\n"
         "uniform mat4 projection;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   o.texCoord=texCoord;\n"
         "   vec4 v=instancingMatrix*position;\n"
         "   o.eyePosition=v.xyz;\n"
         "   o.eyeNormal=transpose(inverse(mat3(instancingMatrix)))*normal;\n"
         "   gl_Position=projection*v;\n"
         "}\n"),
      make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,
         "#version 330\n"
         "\n"
         "in VertexData {\n"
         "   vec3 eyePosition;\n"
         "   vec3 eyeNormal;\n"
         "   vec2 texCoord;\n"
         "};\n"
         "\n"
         "layout(location=0) out vec4 fragColor;\n"
         "\n"
         "uniform vec4 color;\n"
         "uniform vec4 specularAndShininess; // shininess in alpha\n"
         "uniform int colorTexturingMode; // 0 - no texturing, 1 - modulate, 2 - replace\n"
         "uniform sampler2D colorTexture;\n"
         "uniform vec4 lightPosition; // in eye coordinates, w must be 0 or 1\n"
         "uniform vec3 lightColor;\n"
         "uniform vec3 lightAttenuation;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   // compute VL - vertex to light vector, in eye coordinates\n"
         "   vec3 VL=lightPosition.xyz;\n"
         "   if(lightPosition.w!=0.)\n"
         "      VL-=eyePosition;\n"
         "   float VLlen=length(VL);\n"
         "   vec3 VLdir=VL/VLlen;\n"
         "\n"
         "   // invert normals on back facing triangles\n"
         "   vec3 N=gl_FrontFacing?eyeNormal:-eyeNormal;\n"
         "\n"
         "   // Lambert's diffuse reflection\n"
         "   float NdotL=dot(N,VLdir);\n"
         "\n"
         "   // fragments facing the light get all the lighting\n"
         "   // while those not facing the light get only ambient lighting\n"
         "   if(NdotL<=0.)\n"
         "   {\n"
         "      // final sum for light-not-facing fragments\n"
         "      // (This can be computed as fragColor=vec4(0,0,0,diffuse.a)\n"
         "      // or we can simply drop the fragment.)\n"
         "      discard;\n"
         "   }\n"
         "   else\n"
         "   {\n"
         "      // specular effect\n"
         "      float specularEffect;\n"
         "      vec3 R=reflect(-VLdir,N);\n"
         "      vec3 Vdir=normalize(eyePosition.xyz);\n"
         "      float RdotV=dot(R,-Vdir);\n"
         "      if(RdotV>0.)\n"
         "         specularEffect=pow(RdotV,specularAndShininess.a);\n"
         "      else\n"
         "         specularEffect = 0.;\n"
         "\n"
         "      // attenuation\n"
         "      float attenuation=lightAttenuation[0]+\n"
         "                        lightAttenuation[1]*VLlen+\n"
         "                        lightAttenuation[2]*VLlen*VLlen;\n"
         "\n"
         "      // texturing\n"
         "      vec4 c;\n;"
         "      if(colorTexturingMode==0) // no texturing\n"
         "         c=color;\n"
         "      else if(colorTexturingMode==1) // modulate\n"
         "         c=texture(colorTexture,texCoord)*color;\n"
         "      else // replace\n"
         "         c=texture(colorTexture,texCoord);\n"
         "\n"
         "      // final sum for light-facing fragments\n"
         "      fragColor=vec4((c.rgb*lightColor*NdotL+\n"
         "                      specularAndShininess.rgb*lightColor*specularEffect)/\n"
         "                      attenuation,\n"
         "                     c.a);\n"
         "   }\n"
         "}\n"));
   glm::mat4 projection=glm::perspective(float(60.*M_PI/180.),
                                         float(windowWidth)/float(windowHeight),zNear,zFar);
   glProgram->use();
   glProgram->setMatrix4fv("projection",glm::value_ptr(projection));
   glProgram->set("color",0.8f,0.8f,0.8f,1.f);
   glProgram->set("specularAndShininess",0.2f,0.2f,0.2f,1.f);
   glProgram->set("colorTexturingMode",int(0));
   glProgram->set("colorTexture",int(0));
   glProgram->set("lightPosition",0.f,0.f,0.f,1.f);
   glProgram->set("lightColor",1.f,1.f,1.f);
   glProgram->set("lightAttenuation",1.f,0.f,0.f);

   // state set
   StateSetManager::GLState *glState=RenderingContext::current()->createGLState();
   glState->set("bin",type_index(typeid(int)),reinterpret_cast<void*>(0)); // bin 0 is for ambient pass
   glState->set("glProgram",type_index(typeid(shared_ptr<ge::gl::Program>*)),&glProgram);
   shared_ptr<StateSet> stateSet=RenderingContext::current()->getOrCreateStateSet(glState);
   delete glState;

   // transformation
   cameraTransformation=make_shared<Transformation>();
   RenderingContext::current()->addTransformationGraph(cameraTransformation);


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
