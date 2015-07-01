#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geGL/BufferObject.h>
#include <geGL/DebugMessage.h>
#include <geGL/ProgramObject.h>
#include <geRG/Mesh.h>
#include <geRG/AttribType.h>
#include <geRG/RenderingContext.h>
#include <geRG/StateSet.h>
#include <geRG/Transformation.h>
#include <geUtil/WindowObject.h>
#include <geUtil/ArgumentObject.h>
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

static ProgramObject *ambientProgram = NULL;
static ProgramObject *simplifiedPhongProgram = NULL;
static ProgramObject *processInstanceProgram = NULL;
static shared_ptr<StateSet> stateSet;
static list<Mesh> meshList;
static vector<Mesh> notUsedVector;
static string fileName;


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
  RenderingContext::setCurrent(make_shared<RenderingContext>());

  // OpenGL debugging messages
  //ge::gl::setDefaultDebugMessage();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDisable(GL_CULL_FACE);

  Init();
  Window->mainLoop();
  delete ambientProgram;
  delete simplifiedPhongProgram;
  delete processInstanceProgram;
  delete Window;
  delete Args;
  return 0;
}


void Mouse(){
}


void Wheel(int d){
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
   // prepare for rendering
   RenderingContext::current()->evaluateTransformationGraph();
   RenderingContext::current()->setupRendering();
   RenderingContext::current()->mapStateSetBuffer();
   stateSet->setupRendering();
   RenderingContext::current()->unmapStateSetBuffer();

   // indirect buffer update - setup and start compute shader
   processInstanceProgram->use();
   unsigned numInstances=RenderingContext::current()->instanceAllocationManager().firstItemAvailableAtTheEnd();
   processInstanceProgram->set("numToProcess",numInstances);
   RenderingContext::current()->drawCommandBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,0);
   RenderingContext::current()->instanceBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,1);
   RenderingContext::current()->instancingMatricesControlBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,2);
   RenderingContext::current()->indirectCommandBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,3);
   RenderingContext::current()->stateSetBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,4);
   glDispatchCompute((numInstances+63)/64,1,1);

   // draw few triangles by very low-level approach
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   // wait for compute shader
   glMemoryBarrier(GL_COMMAND_BARRIER_BIT);
   RenderingContext::current()->indirectCommandBuffer()->bind(GL_DRAW_INDIRECT_BUFFER);
   RenderingContext::current()->instancingMatrixBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,0);

#if 0
   printIntBufferContent(RenderingContext::current()->instanceBuffer(),
                         RenderingContext::current()->instanceAllocationManager().firstItemAvailableAtTheEnd()*3);
   printIntBufferContent(RenderingContext::current()->drawCommandBuffer(),
                         (RenderingContext::current()->drawCommandAllocationManager().firstByteAvailableAtTheEnd()+3)/sizeof(unsigned));
   printIntBufferContent(RenderingContext::current()->indirectCommandBuffer(),
                         RenderingContext::current()->instanceAllocationManager().firstItemAvailableAtTheEnd()*5);
#endif

   // render ambient scene
   glDisable(GL_CULL_FACE);
   ambientProgram->use();
   stateSet->render();

   // render light pass
   glEnable(GL_BLEND);
   glBlendFunc(GL_ONE,GL_ONE);
   simplifiedPhongProgram->use();
   stateSet->render();
   glDisable(GL_BLEND);

   Window->swap();
}


static map<osg::Array::Type,AttribType> osgArrayType2geArrayType = {
   { osg::Array::ByteArrayType,   AttribType::Byte },
   { osg::Array::ShortArrayType,  AttribType::Short },
   { osg::Array::IntArrayType,    AttribType::Int },
   { osg::Array::UByteArrayType,  AttribType::UByte },
   { osg::Array::UShortArrayType, AttribType::UShort },
   { osg::Array::UIntArrayType,   AttribType::UInt },
   { osg::Array::FloatArrayType,  AttribType::Float },
   { osg::Array::DoubleArrayType, AttribType::Double },
   { osg::Array::Vec2bArrayType,  AttribType::BVec2 },
   { osg::Array::Vec3bArrayType,  AttribType::BVec3 },
   { osg::Array::Vec4bArrayType,  AttribType::BVec4 },
   { osg::Array::Vec2sArrayType,  AttribType::SVec2 },
   { osg::Array::Vec3sArrayType,  AttribType::SVec3 },
   { osg::Array::Vec4sArrayType,  AttribType::SVec4 },
   { osg::Array::Vec2iArrayType,  AttribType::IVec2 },
   { osg::Array::Vec3iArrayType,  AttribType::IVec3 },
   { osg::Array::Vec4iArrayType,  AttribType::IVec4 },
   { osg::Array::Vec2ubArrayType, AttribType::UBVec2 },
   { osg::Array::Vec3ubArrayType, AttribType::UBVec3 },
   { osg::Array::Vec4ubArrayType, AttribType::UBVec4 },
   { osg::Array::Vec2usArrayType, AttribType::USVec2 },
   { osg::Array::Vec3usArrayType, AttribType::USVec3 },
   { osg::Array::Vec4usArrayType, AttribType::USVec4 },
   { osg::Array::Vec2uiArrayType, AttribType::UVec2 },
   { osg::Array::Vec3uiArrayType, AttribType::UVec3 },
   { osg::Array::Vec4uiArrayType, AttribType::UVec4 },
   { osg::Array::Vec2ArrayType,   AttribType::Vec2 },
   { osg::Array::Vec3ArrayType,   AttribType::Vec3 },
   { osg::Array::Vec4ArrayType,   AttribType::Vec4 },
   { osg::Array::Vec2dArrayType,  AttribType::DVec2 },
   { osg::Array::Vec3dArrayType,  AttribType::DVec3 },
   { osg::Array::Vec4dArrayType,  AttribType::DVec4 },
   { osg::Array::MatrixArrayType,  AttribType::Mat4 },
   { osg::Array::MatrixdArrayType, AttribType::DMat4 },
};


static AttribType convertOsgArrayType2geAttribType(osg::Array::Type osgType)
{
   return osgArrayType2geArrayType[osgType];
}


static const float osg2glTransformation[16] = {
   1.f, 0.f, 0.f, 0.f,
   0.f, 0.f,-1.f, 0.f,
   0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 1.f,
};


class BuildGpuEngineGraphVisitor : public osg::NodeVisitor {
public:

   vector<shared_ptr<Transformation>> transformationStack;

   inline BuildGpuEngineGraphVisitor() : osg::NodeVisitor(osg::NodeVisitor::NODE_VISITOR,osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
   {
      shared_ptr<Transformation> t=make_shared<Transformation>();
      transformationStack.emplace_back(t);
      t->allocTransformationGpuData();
      t->uploadMatrix(osg2glTransformation);
   }

   virtual void apply(osg::Transform& transform)
   {
      osg::Matrix m;
      transform.computeLocalToWorldMatrix(m,this);
      shared_ptr<Transformation> t=make_shared<Transformation>();
      transformationStack.back()->appendChild(t,transformationStack.back());
      transformationStack.emplace_back(t);
      t->allocTransformationGpuData();
      t->uploadMatrix(osg::Matrixf(m).ptr());
      traverse(transform);
      transformationStack.pop_back();
   }

   virtual void apply(osg::Geode& node)
   {
      for(int i=0,c=node.getNumDrawables(); i<c; i++)
         apply(*node.getDrawable(i));
   }

   virtual void apply(osg::Drawable& drawable)
   {
      osg::Geometry *g=drawable.asGeometry();
      if(g)
      {
         // will we use indices (EBO)?
         bool useIndices=false;
         const osg::Geometry::PrimitiveSetList &primitiveList=g->getPrimitiveSetList();
         for(auto it=primitiveList.begin(); it!=primitiveList.end(); it++)
         {
            auto e=(*it)->getDrawElements();
            if(e && e->getNumIndices()>0)
            {
               useIndices=true;
               break;
            }
         }

         // get numVertices of osg::Geometry
         unsigned numVertices=0;
         osg::Geometry::ArrayList arrayList;
         g->getArrayList(arrayList);
         for(osg::Geometry::ArrayList::iterator it=arrayList.begin(); it!=arrayList.end(); it++)
         {
            unsigned n=(*it)->getNumElements();
            if(n>numVertices)
               numVertices=n;
         }

         // generate draw commands
         unsigned numDrawCommands=g->getNumPrimitiveSets();
         vector<unsigned> drawCommands;
         vector<Mesh::DrawCommandControlData> drawCommandsControlData;
         drawCommands.reserve(numDrawCommands*3);
         drawCommandsControlData.reserve(numDrawCommands);
         unsigned numIndices=0;
         for(unsigned i=0; i<numDrawCommands; i++)
         {
            osg::PrimitiveSet *ps=g->getPrimitiveSet(i);
            unsigned glMode=ps->getMode();
            unsigned mode=useIndices?glMode|0x10:glMode;
            unsigned count,first;
            osg::DrawElements *e=ps->getDrawElements();
            if(e!=nullptr)
            {
               drawCommandsControlData.emplace_back(drawCommands.size(),mode);
               count=e->getNumIndices();
               first=numIndices;
               numIndices+=count;
            }
            else
            {
               switch(ps->getType()) {
                  case osg::PrimitiveSet::DrawArraysPrimitiveType:
                  {
                     drawCommandsControlData.emplace_back(drawCommands.size(),mode);
                     osg::DrawArrays *a=static_cast<osg::DrawArrays*>(ps);
                     count=a->getCount();
                     if(useIndices)
                     {
                        first=numIndices;
                        numIndices+=count;
                     }
                     else
                        first=a->getFirst();
                     break;
                  }
                  case osg::PrimitiveSet::DrawArrayLengthsPrimitiveType:
                  {
                     osg::DrawArrayLengths *a=static_cast<osg::DrawArrayLengths*>(ps);
                     first=useIndices?numIndices:a->getFirst();
                     for(unsigned i=0,c=a->size(); i<c; i++)
                     {
                        drawCommandsControlData.emplace_back(drawCommands.size(),mode);
                        unsigned count=a->operator[](i);
                        drawCommands.push_back(useIndices?count|0x80000000:count); // countAndIndexedFlag
                        drawCommands.push_back(first);
                        drawCommands.push_back(0);
                        first+=count;
                        if(useIndices)
                           numIndices+=count;
                     }
                     continue;
                  }
                  default:
                     continue;
               }
            }
            drawCommands.push_back(useIndices?count|0x80000000:count);
            drawCommands.push_back(first);
            drawCommands.push_back(0);
         }

         // create AttribConfig::ConfigData
         // and list of osg arrays
         AttribConfig::ConfigData configData;
         configData.attribTypes.reserve(arrayList.size());
         vector<const osg::Array*> osgArrays;
         osgArrays.reserve(arrayList.size());

         // convert all vertex attrib types
         // and fill configData.attribTypes and osgArrays vectors
         auto processArrayType=[&configData,&osgArrays](const osg::Array *a)
         {
            if(a)
            {
               configData.attribTypes.push_back(convertOsgArrayType2geAttribType(a->getType()));
               osgArrays.push_back(a);
            }
         };
         processArrayType(g->getVertexArray());
         processArrayType(g->getNormalArray());
         processArrayType(g->getColorArray());
         for(unsigned i=0,c=g->getNumTexCoordArrays(); i<c; i++)
            processArrayType(g->getTexCoordArray(i));
         processArrayType(g->getSecondaryColorArray());
         processArrayType(g->getFogCoordArray());
         for(unsigned i=0,c=g->getNumVertexAttribArrays(); i<c; i++)
            processArrayType(g->getVertexAttribArray(i));

         // use EBO if there are indices
         // and updateId (for optimization purposes, such as ConfigData comparison, etc.)
         configData.ebo=useIndices;
         configData.updateId();

         // create AttribConfigRef
         AttribConfigRef config(configData);

         // create Mesh
         meshList.emplace_back();
         Mesh &m=meshList.back();
         m.allocData(config,numVertices,numIndices,drawCommands.size()*sizeof(unsigned));

         // upload draw commands
         m.uploadDrawCommands(drawCommands.data(),drawCommands.size()*sizeof(unsigned),
                              drawCommandsControlData.data(),drawCommandsControlData.size());

         // create instances
         shared_ptr<InstancingMatrices> &im=transformationStack.back()->getOrCreateInstancingMatrices();
         m.createInstances(im.get(),stateSet.get());

         // upload vertices
         vector<void*> geArrays;
         geArrays.reserve(configData.attribTypes.size());
         for(int i=0,c=configData.attribTypes.size(); i<c; i++)
         {
            AttribType &t=configData.attribTypes[i];
            size_t attribBufSize=t.elementSize()*numVertices;
            size_t osgBufSize=osgArrays[i]->getTotalDataSize();
            void *p=malloc(attribBufSize);
            if(osgArrays[i]->getBinding()==osg::Array::BIND_OVERALL)
            {
               const void *src=osgArrays[i]->getDataPointer();
               uint8_t *dst=static_cast<uint8_t*>(p);
               size_t size=osgArrays[i]->getElementSize();
               for(unsigned i=0; i<numVertices; i++) {
                  memcpy(dst,src,size);
                  dst+=size;
               }
            }
            else
            {
               memcpy(p,osgArrays[i]->getDataPointer(),osgBufSize);
               if(attribBufSize!=osgBufSize)
                  memset(((uint8_t*)p)+osgBufSize,0,attribBufSize-osgBufSize);
            }
            geArrays.push_back(p);
         }
         m.uploadVertices(geArrays.data(),geArrays.size(),numVertices);
         for(int i=0,c=configData.attribTypes.size(); i<c; i++)
            free(geArrays[i]);

         // upload indices
         if(useIndices)
         {
            vector<unsigned> indices;
            indices.reserve(numVertices); // reserve some possibly large space
            for(auto it=primitiveList.begin(); it!=primitiveList.end(); it++)
            {
               osg::PrimitiveSet *ps=*it;
               auto e=ps->getDrawElements();
               if(e)
               {
                  for(unsigned i=0,c=e->getNumIndices(); i<c; i++)
                     indices.push_back(e->index(i));
               }
               else
               {
                  switch(ps->getType()) {
                     case osg::PrimitiveSet::DrawArraysPrimitiveType:
                     {
                        osg::DrawArrays *a=static_cast<osg::DrawArrays*>(ps);
                        for(unsigned i=a->getFirst(),c=i+a->getCount(); i<c; i++)
                           indices.push_back(i);
                        break;
                     }
                     case osg::PrimitiveSet::DrawArrayLengthsPrimitiveType:
                     {
                        osg::DrawArrayLengths *a=static_cast<osg::DrawArrayLengths*>(ps);
                        unsigned i=a->getFirst();
                        for(unsigned j=0,l=a->size(); j<l; j++)
                        {
                           unsigned count=a->operator[](j);
                           for(unsigned c=i+count; i<c; i++)
                              indices.push_back(i);
                        }
                        continue;
                     }
                     default:
                        continue;
                  }
               }
            }
            m.uploadIndices(indices.data(),indices.size());
         }

      }
   }

};


void Init()
{
   stateSet=make_shared<StateSet>();

   // load model
   if(!fileName.empty())
   {
      osg::Node *root=osgDB::readNodeFile(fileName);
      if(root==nullptr)
         cout<<"Failed to load file "<<fileName<<endl;
      else
      {
         BuildGpuEngineGraphVisitor graphBuilder;
         root->ref();
         root->accept(graphBuilder);
         root->unref();

#if 1
         shared_ptr<Transformation> t1=make_shared<Transformation>();
         t1->appendChild(graphBuilder.transformationStack.front(),t1);
         RenderingContext::current()->appendTransformationGraph(t1);
         const float m1[16] = {
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f,-10.f, 1.f,
         };
         t1->allocTransformationGpuData();
         t1->uploadMatrix(m1);
#else
         shared_ptr<Transformation> t1=make_shared<Transformation>();
         t1->appendChild(graphBuilder.transformationStack.front(),t1);
         RenderingContext::current()->appendTransformationGraph(t1);
         const float m1[16] = {
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f,-2.f,-10.f, 1.f,
         };
         t1->allocTransformationGpuData();
         t1->uploadMatrix(m1);

         const float m2[16] = {
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
           -3.f, 3.f,-10.f, 1.f,
         };
         shared_ptr<Transformation> t2=make_shared<Transformation>();
         t2->allocTransformationGpuData();
         t2->uploadMatrix(m2);
         t2->setInstancingMatrices(t1->getOrCreateInstancingMatrices());
         RenderingContext::current()->appendTransformationGraph(t2);

         const float m3[16] = {
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            3.f, 3.f, 0.f, 1.f,
         };
         shared_ptr<Transformation> t3=make_shared<Transformation>();
         t3->allocTransformationGpuData();
         t3->uploadMatrix(m3);
         t3->appendChild(t1,t3);
         RenderingContext::current()->appendTransformationGraph(t3);
#endif
      }

      // release OSG memory
      osgDB::Registry::instance()->closeAllLibraries();
      osgDB::Registry::instance(true);
   }


   // unmap instance buffer
   // (it has to be done before rendering, for sure always before the frame,
   // or at least when there were any modifications to the instance buffer)
   RenderingContext::current()->unmapInstanceBuffer();


   ge::gl::initShadersAndPrograms();
   ambientProgram = new ProgramObject(
      GL_VERTEX_SHADER,
      "#version 430\n"
      "#extension GL_ARB_shader_draw_parameters : enable\n"
      "\n"
      "layout(std430,binding=0) restrict readonly buffer InstancingMatrix {\n"
      "   mat4 instancingMatrixBuffer[];\n"
      "};\n"
      "\n"
      "layout(location=0) in vec4 position;\n"
      "layout(location=2) in vec4 diffuse;\n"
      //"layout(location=3) in vec2 texCoord;\n"
      "\n"
      "layout(location=0) out vec4 colorOut;\n"
      "\n"
      "uniform vec4 globalAmbientLight; // alpha should be 1\n"
      "uniform mat4 projection;\n"
      "\n"
      "void main()\n"
      "{\n"
      "   // ambient lighting\n"
      "   colorOut=globalAmbientLight*diffuse;\n"
      "\n"
      "   // vertex position\n"
      "   uint matrixOffset64=gl_BaseInstanceARB+gl_InstanceID;\n"
      "   gl_Position=projection*instancingMatrixBuffer[matrixOffset64]*position;\n"
      "}\n",
      GL_FRAGMENT_SHADER,
      "#version 330\n"
      "\n"
      "in vec4 color;\n"
      "\n"
      "layout(location=0) out vec4 fragColor;\n"
      "\n"
      "void main()\n"
      "{\n"
      "   fragColor=color;\n"
      "}\n");
   simplifiedPhongProgram = new ProgramObject(
      GL_VERTEX_SHADER,
      "#version 430\n"
      "#extension GL_ARB_shader_draw_parameters : enable\n"
      "\n"
      "layout(std430,binding=0) restrict readonly buffer InstancingMatrix {\n"
      "   mat4 instancingMatrixBuffer[];\n"
      "};\n"
      "\n"
      "layout(location=0) in vec4 position;\n"
      "layout(location=1) in vec3 normal;\n"
      "layout(location=2) in vec4 diffuse;\n"
      "layout(location=3) in vec2 texCoord;\n"
      "\n"
      "layout(location=0) out vec3 eyePosition;\n"
      "layout(location=1) out vec3 eyeNormal;\n"
      "layout(location=2) out vec4 diffuseOut;\n"
      "\n"
      "uniform mat4 projection;\n"
      "\n"
      "void main()\n"
      "{\n"
      "   diffuseOut=diffuse;\n"
      "   uint matrixOffset64=gl_BaseInstanceARB+gl_InstanceID;\n"
      "   vec4 v=instancingMatrixBuffer[matrixOffset64]*position;\n"
      "   eyePosition=v.xyz;\n"
      "   eyeNormal=transpose(inverse(mat3(instancingMatrixBuffer[matrixOffset64])))*normal;\n"
      "   gl_Position=projection*v;\n"
      "}\n",
      GL_FRAGMENT_SHADER,
      "#version 330\n"
      "\n"
      "in vec3 eyePosition;\n"
      "in vec3 eyeNormal;\n"
      "in vec4 diffuse;\n"
      "\n"
      "layout(location=0) out vec4 fragColor;\n"
      "\n"
      "uniform vec4 specularAndShininess; // shininess in alpha\n"
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
      "   if(NdotL>0.) {\n"
      "\n"
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
      "      // final sum for light-facing fragments\n"
      "      fragColor=vec4((diffuse.rgb*lightColor*NdotL+\n"
      "                      specularAndShininess.rgb*lightColor*specularEffect)/\n"
      "                      attenuation,\n"
      "                     diffuse.a);\n"
      "   }\n"
      "   else\n"
      "   {\n"
      "      // final sum for light-not-facing fragments\n"
      "      fragColor=vec4(0,0,0,diffuse.a);\n"
      "   }\n"
      "}\n");
   glm::mat4 projection=glm::perspective(float(60.*M_PI/180.),float(WindowParam.Size[0])/WindowParam.Size[1],1.f,100.f);
   ambientProgram->use();
   ambientProgram->set("globalAmbientLight",0.2f,0.2f,0.2f,1.f);
   ambientProgram->set("projection",1,GL_FALSE,glm::value_ptr(projection));
   simplifiedPhongProgram->use();
   simplifiedPhongProgram->set("projection",1,GL_FALSE,glm::value_ptr(projection));
   simplifiedPhongProgram->set("specularAndShininess",0.33f,0.33f,0.33f,0.f); // shininess in alpha
   simplifiedPhongProgram->set("lightPosition",0.f,0.f,0.f,1.f); // in eye coordinates, w must be 0 or 1
   simplifiedPhongProgram->set("lightColor",1.f,1.f,1.f);
   simplifiedPhongProgram->set("lightAttenuation",1.f,0.f,0.f);
   processInstanceProgram=new ProgramObject(
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
