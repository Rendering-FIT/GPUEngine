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
#include <geSG/AttribReference.h>
#include <geSG/AttribType.h>
#include <geSG/RenderingContext.h>
#include <geSG/StateSet.h>
#include <geSG/Transformation.h>
#include <geUtil/WindowObject.h>
#include <geUtil/ArgumentObject.h>
#include <osgDB/ReadFile>

using namespace std;
using namespace ge::gl;
using namespace ge::sg;


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

static ProgramObject *glProgram = NULL;
static ProgramObject *processInstanceProgram = NULL;
static shared_ptr<StateSet> stateSet;
static list<AttribReference> attribRefList;
static vector<AttribReference> notUsedVector;
static AttribReference attribsRefNI;
static AttribReference attribsRefI;
static AttribReference attribsRefInstNI;
static AttribReference attribsRefInstI;
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
  delete glProgram;
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
   RenderingContext::current()->setupRendering();
   RenderingContext::current()->mapStateSetBuffer();
   stateSet->setupRendering();
   RenderingContext::current()->unmapStateSetBuffer();

   // indirect buffer update - setup and start compute shader
   processInstanceProgram->use();
   unsigned numInstances=RenderingContext::current()->getFirstInstanceAvailableAtTheEnd();
   processInstanceProgram->set("numToProcess",numInstances);
   RenderingContext::current()->getDrawCommandBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,0);
   RenderingContext::current()->getInstanceBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,1);
   RenderingContext::current()->getIndirectCommandBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,2);
   RenderingContext::current()->getStateSetBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,3);
   glDispatchCompute((numInstances+63)/64,1,1);

   // draw few triangles by very low-level approach
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glProgram->use();
   RenderingContext::current()->getInstancingMatrixCollectionBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,0);
   RenderingContext::current()->getInstancingMatrixBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,1);
   attribsRefNI.attribStorage->bind();
   unsigned baseIndex=attribsRefNI.attribStorage->getVertexAllocationBlock(attribsRefNI.verticesDataId).startIndex;
   glDrawArrays(GL_TRIANGLES,baseIndex+0,3);
   glDrawArrays(GL_TRIANGLES,baseIndex+3,3);
   attribsRefI.attribStorage->bind();
   baseIndex=attribsRefI.attribStorage->getIndexAllocationBlock(attribsRefI.indicesDataId).startIndex;
   glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)(intptr_t(baseIndex)*4+0));
   glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)(intptr_t(baseIndex)*4+12));

   // wait for compute shader
   glMemoryBarrier(GL_COMMAND_BARRIER_BIT);
   RenderingContext::current()->getIndirectCommandBuffer()->bind(GL_DRAW_INDIRECT_BUFFER);

   // render two triangles indirectly
   /*attribsRefInstNI.attribStorage->bind();
   glMultiDrawArraysIndirect(GL_TRIANGLES,(GLvoid*)intptr_t(attribsRefInstNI.instances.front()->items[0].index()*16),2,0);

   // render loaded model
   if(!attribRefList.empty())
   {
      for(auto it=attribRefList.begin(); it!=attribRefList.end(); it++)
      {
         it->attribStorage->bind();
         glMultiDrawArraysIndirect(GL_TRIANGLES,(GLvoid*)intptr_t(it->instances.front()->items[0].index()*16),
                                   it->instances.front()->count,0);
      }
   }*/
   /*printIntBufferContent(RenderingContext::current()->getInstanceBuffer(),
                         RenderingContext::current()->getFirstInstanceAvailableAtTheEnd()*3);
   printIntBufferContent(RenderingContext::current()->getDrawCommandBuffer(),
                         (RenderingContext::current()->getFirstDrawCommandAvailableAtTheEnd()+3)/sizeof(unsigned));
   printIntBufferContent(RenderingContext::current()->getIndirectCommandBuffer(),
                         RenderingContext::current()->getFirstInstanceAvailableAtTheEnd()*5);*/
   RenderingContext::current()->getInstancingMatrixCollectionBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,0);
   RenderingContext::current()->getInstancingMatrixBuffer()->bindBase(GL_SHADER_STORAGE_BUFFER,1);
   stateSet->render();

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


class BuildGpuEngineGraphVisitor : public osg::NodeVisitor {
public:

   vector<shared_ptr<Transformation>> transformationStack;

   inline BuildGpuEngineGraphVisitor() : osg::NodeVisitor(osg::NodeVisitor::NODE_VISITOR,osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
   {
      transformationStack.push_back(make_shared<Transformation>());
   }

   inline BuildGpuEngineGraphVisitor(shared_ptr<Transformation> &parentTransformation) : osg::NodeVisitor(osg::NodeVisitor::NODE_VISITOR,osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
   {
      transformationStack.push_back(parentTransformation);
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
         vector<AttribReference::DrawCommandControlData> drawCommandsControlData;
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

         // create AttribReference
         attribRefList.emplace_back();
         AttribReference &r=attribRefList.back();
         r.allocData(config,numVertices,numIndices,drawCommands.size()*sizeof(unsigned));

         // upload draw commands
         r.uploadDrawCommands(drawCommands.data(),drawCommands.size()*sizeof(unsigned),
                              drawCommandsControlData.data(),drawCommandsControlData.size());

         // create instances
         shared_ptr<InstancingMatrixCollection> &imc=transformationStack.back()->getOrCreateInstancingMatrixCollection();
         r.createInstances(imc.get(),stateSet.get());

         // upload vertices
         vector<void*> geArrays;
         geArrays.reserve(configData.attribTypes.size());
         for(int i=0,c=configData.attribTypes.size(); i<c; i++)
         {
            AttribType &t=configData.attribTypes[i];
            size_t attribBufSize=t.elementSize()*numVertices;
            size_t osgBufSize=osgArrays[i]->getTotalDataSize();
            void *p=malloc(attribBufSize);
            memcpy(p,osgArrays[i]->getDataPointer(),osgBufSize);
            if(attribBufSize!=osgBufSize)
               memset(((uint8_t*)p)+osgBufSize,0,attribBufSize-osgBufSize);
            geArrays.push_back(p);
         }
         r.uploadVertices(geArrays.data(),geArrays.size());
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
            r.uploadIndices(indices.data(),indices.size());
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
         InstancingMatrixCollection *imc=graphBuilder.transformationStack.front()->getOrCreateInstancingMatrixCollection().get();
         imc->updateGpuData(1);
         const float m[16] = {
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f,-2.f,-10.f, 1.f,
         };
         imc->uploadMatrices(m,1);
      }

      // release OSG memory
      osgDB::Registry::instance()->closeAllLibraries();
      osgDB::Registry::instance(true);
   }


   AttribConfig::ConfigData config;
   config.attribTypes.push_back(AttribType::Vec3);

   // top-left geometry
   config.ebo=false;
   config.updateId();

   constexpr float z=-10.f;
   constexpr float niShiftX=-1.5f;
   constexpr float shiftY=3.0f;
   const vector<glm::vec3> twoTrianglesNI = {
      glm::vec3(niShiftX+0,shiftY+0,z),
      glm::vec3(niShiftX+0,shiftY+1,z),
      glm::vec3(niShiftX+1,shiftY+0,z),
      glm::vec3(niShiftX+0,shiftY+0,z),
      glm::vec3(niShiftX+0,shiftY-1,z),
      glm::vec3(niShiftX-1,shiftY+0,z),
   };
   vector<const void*> a;
   a.reserve(1);
   a.emplace_back(twoTrianglesNI.data());

   attribsRefNI.allocData(config,6,0,0);
   attribsRefNI.uploadVertices(a.data(),twoTrianglesNI.size());

   // top-right geometry
   config.ebo=true;
   config.updateId();

   constexpr float iShiftX=1.5f;
   const vector<glm::vec3> twoTrianglesI = {
      glm::vec3(iShiftX+0,shiftY+0,z),
      glm::vec3(iShiftX+0,shiftY+1,z),
      glm::vec3(iShiftX+1,shiftY+0,z),
      glm::vec3(iShiftX+0,shiftY+0.1f,z),
      glm::vec3(iShiftX+0,shiftY-1,z),
      glm::vec3(iShiftX-1,shiftY+0,z),
   };
   a[0]=twoTrianglesI.data();

   attribsRefI.allocData(config,6,6,0);
   attribsRefI.uploadVertices(a.data(),twoTrianglesI.size());
   const vector<unsigned> indices = { 5, 1, 2, 3, 4, 5 };
   attribsRefI.uploadIndices(indices.data(),indices.size());

   // bottom-left geometry
   constexpr float instanceShiftY=shiftY-3.0f;
   const vector<glm::vec3> twoTriangleInstancesNI = {
      glm::vec3(niShiftX+0,instanceShiftY+0,z),
      glm::vec3(niShiftX+0,instanceShiftY+1,z),
      glm::vec3(niShiftX+1,instanceShiftY+0,z),
      glm::vec3(niShiftX+0,instanceShiftY+0,z),
      glm::vec3(niShiftX+0,instanceShiftY-1,z),
      glm::vec3(niShiftX-1,instanceShiftY+0,z),
   };
   vector<unsigned> drawCommands = {
      3,0,0,
      3,3,3,
   };
   const vector<unsigned> modesAndOffsets4 = {
      GL_TRIANGLES,0,
      GL_TRIANGLES,3,
   };
   a[0]=twoTriangleInstancesNI.data();
   config.ebo=false;
   config.updateId();
   attribsRefInstNI.allocData(config,6,0,drawCommands.size()*sizeof(unsigned));
   attribsRefInstNI.uploadVertices(a.data(),twoTriangleInstancesNI.size());
   attribsRefInstNI.uploadDrawCommands(drawCommands.data(),drawCommands.size()*sizeof(unsigned),
                                       modesAndOffsets4.data(),modesAndOffsets4.size()/2);
   attribsRefInstNI.createInstances(0u,stateSet.get());


   // unmap instance buffer
   // (it has to be done before rendering, for sure always before the frame,
   // or at least when there were any modifications to the instance buffer)
   RenderingContext::current()->unmapInstanceBuffer();


   ge::gl::initShadersAndPrograms();
   glProgram = new ProgramObject(
      GL_VERTEX_SHADER,
      "#version 430\n"
      "#extension GL_ARB_shader_draw_parameters : enable\n"
      "\n"
      "layout(location=0) in vec3 coords;\n"
      "\n"
      "layout(std430,binding=0) restrict readonly buffer InstancingMatrixCollection {\n"
      "   uint instancingMatrixCollectionBuffer[];\n"
      "};\n"
      "layout(std430,binding=1) restrict readonly buffer InstancingMatrices {\n"
      "   mat4 instancingMatricesBuffer[];\n"
      "};\n"
      "\n"
      "uniform mat4 mvp;\n"
      "\n"
      "void main()\n"
      "{\n"
      "   uint matrixOffset64=instancingMatrixCollectionBuffer[gl_BaseInstanceARB];\n"
      "   gl_Position = mvp*instancingMatricesBuffer[matrixOffset64]*vec4(coords,1.f);\n"
      "}\n",
      GL_FRAGMENT_SHADER,
      "#version 330\n"
      "layout(location=0) out vec4 fragColor;\n"
      "void main()\n"
      "{\n"
      "   fragColor=vec4(1.f,1.f,0.,1.);\n"
      "}\n");
   glm::mat4 modelView(1.f); // identity
   glm::mat4 projection=glm::perspective(float(60.*M_PI/180.),float(WindowParam.Size[0])/WindowParam.Size[1],1.f,100.f);
   glm::mat4 mvp=modelView*projection;
   glProgram->use();
   glProgram->set("mvp",1,GL_FALSE,glm::value_ptr(mvp));
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
      "layout(std430,binding=2) restrict writeonly buffer IndirectBuffer {\n"
      "   uint indirectBuffer[];\n"
      "};\n"
      "layout(std430,binding=3) restrict buffer StateSetBuffer {\n"
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
      "   uint matrixCollectionOffset4=instanceBuffer[instanceIndex+1];\n"
      "   uint stateSetDataOffset4=instanceBuffer[instanceIndex+2];\n"
      "\n"
      "   // compute increment and get indirectBufferOffset\n"
      "   uint countAndIndexedFlag=drawCommandBuffer[drawCommandOffset4+0];\n"
      "   uint indirectBufferIncrement=4+bitfieldExtract(countAndIndexedFlag,31,1); // make increment 4 or 5\n"
      "   uint indirectBufferOffset4=atomicAdd(stateSetBuffer[stateSetDataOffset4],indirectBufferIncrement);\n"
      "\n"
      "   // write indirect buffer data\n"
      "   indirectBuffer[indirectBufferOffset4]=countAndIndexedFlag&0x7fffffff; // indexCount or vertexCount\n"
      "   indirectBufferOffset4++;\n"
      "   indirectBuffer[indirectBufferOffset4]=1; // instanceCount\n"
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
      "   indirectBuffer[indirectBufferOffset4]=matrixCollectionOffset4; // base instance\n"
      "}\n");
}
