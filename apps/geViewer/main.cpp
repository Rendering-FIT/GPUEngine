#include <string>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geGL/BufferObject.h>
#include <geGL/DebugMessage.h>
#include <geGL/geGL.h>
#include <geGL/OpenGLCommands.h>
#include <geGL/ProgramObject.h>
#include <geRG/Mesh.h>
#include <geRG/AttribType.h>
#include <geRG/RenderingContext.h>
#include <geRG/StateSet.h>
#include <geRG/Transformation.h>
#include <geAd/WindowObject/WindowObject.h>
#include <geUtil/ArgumentObject.h>
#include <osg/ref_ptr>
#include <osg/StateSet>
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
static ProgramObject *ambientProgram = NULL;
static ProgramObject *simplifiedPhongProgram = NULL;
static ProgramObject *processInstanceProgram = NULL;
static list<shared_ptr<StateSet>> stateSetList;
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
  delete ambientProgram;
  delete simplifiedPhongProgram;
  delete processInstanceProgram;
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
   // compute transformation matrices
   RenderingContext::current()->evaluateTransformationGraph();
   RenderingContext::current()->matrixStorage()->unmap();

   // prepare for rendering
   RenderingContext::current()->setupRendering();
   RenderingContext::current()->stateSetStorage()->map(BufferStorageAccess::WRITE);
   for(auto it=stateSetList.begin(); it!=stateSetList.end(); it++)
      (*it)->setupRendering();
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

   // clear screen
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   // wait for compute shader
   glMemoryBarrier(GL_COMMAND_BARRIER_BIT);

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
   ambientProgram->use();
   ambientProgram->set("colorTexture",0);
   for(auto it=stateSetList.begin(); it!=stateSetList.end(); it++)
   {
      if((*it)->commandList().size()==0)
         ambientProgram->set("colorTexturingMode",int(0)); // no texturing
      else
         ambientProgram->set("colorTexturingMode",int(1)); // modulate
      for_each((*it)->commandList().begin(),(*it)->commandList().end(),
               [](shared_ptr<ge::core::Command>& c){ (*c.get())(); });
      (*it)->render();
   }

   // render light pass
   glEnable(GL_BLEND);
   glBlendFunc(GL_ONE,GL_ONE);
   simplifiedPhongProgram->use();
   simplifiedPhongProgram->set("colorTexture",int(0));
   for(auto it=stateSetList.begin(); it!=stateSetList.end(); it++)
   {
      if((*it)->commandList().size()==0)
         simplifiedPhongProgram->set("colorTexturingMode",int(0)); // no texturing
      else
         simplifiedPhongProgram->set("colorTexturingMode",int(1)); // modulate
      for_each((*it)->commandList().begin(),(*it)->commandList().end(),
               [](shared_ptr<ge::core::Command>& c){ (*c.get())(); });
      (*it)->render();
   }
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
   vector<osg::ref_ptr<osg::StateSet>> osgStateSetStack;

   struct OsgState {

      osg::Texture* colorTexture;

      inline bool operator<(const OsgState& rhs) const
      {
         return colorTexture<rhs.colorTexture;
      }

      OsgState(osg::StateSet *ss)
      {
         colorTexture=static_cast<osg::Texture*>(ss->getNumTextureAttributeLists()>=1?
               ss->getTextureAttribute(0,osg::Texture::TEXTURE):nullptr);
      }

   };

   map<OsgState,shared_ptr<ge::rg::StateSet>> stateSetMap;

   inline BuildGpuEngineGraphVisitor() : osg::NodeVisitor(osg::NodeVisitor::NODE_VISITOR,osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
   {
      shared_ptr<Transformation> t=make_shared<Transformation>();
      transformationStack.emplace_back(t);
      t->allocTransformationGpuData();
      t->uploadMatrix(osg2glTransformation);
      osgStateSetStack.push_back(new osg::StateSet);
   }

   void pushState(osg::StateSet& stateSet)
   {
      // combine with previous state set
      osg::StateSet *ss=new osg::StateSet(*osgStateSetStack.back(),osg::CopyOp::SHALLOW_COPY);
      ss->merge(stateSet);
      osgStateSetStack.push_back(ss);
   }

   void popState()
   {
      osgStateSetStack.pop_back();
   }

   virtual void apply(osg::Node& node)
   {
      if(node.getStateSet())
         pushState(*node.getStateSet());

      traverse(node);

      if(node.getStateSet())
         popState();
   }

   virtual void apply(osg::Transform& transform)
   {
      if(transform.getStateSet())
         pushState(*transform.getStateSet());

      osg::Matrix m;
      transform.computeLocalToWorldMatrix(m,this);
      shared_ptr<Transformation> t=make_shared<Transformation>();
      transformationStack.back()->appendChild(t,transformationStack.back());
      transformationStack.emplace_back(t);

      t->allocTransformationGpuData();
      t->uploadMatrix(osg::Matrixf(m).ptr());
      traverse(transform);

      transformationStack.pop_back();

      if(transform.getStateSet())
         popState();
   }

   virtual void apply(osg::Geode& node)
   {
      if(node.getStateSet())
         pushState(*node.getStateSet());

      for(int i=0,c=node.getNumDrawables(); i<c; i++)
         apply(*node.getDrawable(i));

      if(node.getStateSet())
         popState();
   }

   virtual void apply(osg::Drawable& drawable)
   {
      // push new OSG stateSet on the stack
      if(drawable.getStateSet())
         pushState(*drawable.getStateSet());

      // find (or create new) geRG StateSet
      shared_ptr<ge::rg::StateSet> stateSet;
      OsgState osgState(osgStateSetStack.back());
      auto it=stateSetMap.find(osgState);
      if(it!=stateSetMap.end())
      {
         // reuse StateSet
         stateSet=it->second;
      }
      else
      {
         // create new StateSet
         stateSet=make_shared<ge::rg::StateSet>();
         stateSetMap.emplace(make_pair(osgState,stateSet));
         stateSetList.push_back(stateSet);

         if(osgState.colorTexture==nullptr)
         {
            // leave commandList empty
         }
         else
         {
            // create texture object
            osg::Texture *osgTexture=osgState.colorTexture;
            GLenum target=osgTexture->getTextureTarget();
            osg::Image *osgImage=osgTexture->getNumImages()>0?osgTexture->getImage(0):nullptr;
            int w=osgImage?osgImage->s():osgTexture->getTextureWidth();
            int h=osgImage?osgImage->t():osgTexture->getTextureHeight();
            int d=osgImage?osgImage->r():osgTexture->getTextureDepth();
            GLenum format=osgImage?osgImage->getPixelFormat():osgTexture->getSourceFormat();
            GLenum type=osgImage?osgImage->getDataType():osgTexture->getSourceType();
            auto data=osgImage?osgImage->data():nullptr;

            // compute internalFormat;
            GLint internalFormat=0;
            switch(format) {
               case GL_RED:
               case GL_RED_INTEGER:
                  switch(type) {
                     case GL_UNSIGNED_BYTE:
                     case GL_BYTE:           internalFormat=GL_R8; break;
                     case GL_UNSIGNED_SHORT:
                     case GL_SHORT:          internalFormat=GL_R16; break;
                     case GL_UNSIGNED_INT:
                     case GL_INT:            internalFormat=GL_R16; break;
                     case GL_FLOAT:          internalFormat=GL_R16; break;
                     default:                break;
                  };
                  break;
               case GL_RG:
               case GL_RG_INTEGER:
                  switch(type) {
                     case GL_UNSIGNED_BYTE:
                     case GL_BYTE:           internalFormat=GL_RG8; break;
                     case GL_UNSIGNED_SHORT:
                     case GL_SHORT:          internalFormat=GL_RG16; break;
                     case GL_UNSIGNED_INT:
                     case GL_INT:            internalFormat=GL_RG16; break;
                     case GL_FLOAT:          internalFormat=GL_RG16; break;
                     default:                break;
                  };
                  break;
               case GL_RGB:
               case GL_BGR:
               case GL_RGB_INTEGER:
               case GL_BGR_INTEGER:
                  switch(type) {
                     case GL_UNSIGNED_BYTE:
                     case GL_BYTE:           internalFormat=GL_RGB8; break;
                     case GL_UNSIGNED_SHORT:
                     case GL_SHORT:          internalFormat=GL_RGB16; break;
                     case GL_UNSIGNED_INT:
                     case GL_INT:            internalFormat=GL_RGB16; break;
                     case GL_FLOAT:          internalFormat=GL_RGB16; break;
                     case GL_UNSIGNED_BYTE_3_3_2:
                     case GL_UNSIGNED_BYTE_2_3_3_REV:  internalFormat=GL_R3_G3_B2; break;
                     case GL_UNSIGNED_SHORT_5_6_5:
                     case GL_UNSIGNED_SHORT_5_6_5_REV: internalFormat=GL_RGB8; break;
                     default:                          break;
                  };
                  break;
               case GL_RGBA:
               case GL_BGRA:
               case GL_RGBA_INTEGER:
               case GL_BGRA_INTEGER:
                  switch(type) {
                     case GL_UNSIGNED_BYTE:
                     case GL_BYTE:           internalFormat=GL_RGBA8; break;
                     case GL_UNSIGNED_SHORT:
                     case GL_SHORT:          internalFormat=GL_RGBA16; break;
                     case GL_UNSIGNED_INT:
                     case GL_INT:            internalFormat=GL_RGBA16; break;
                     case GL_FLOAT:          internalFormat=GL_RGBA16; break;
                     case GL_UNSIGNED_SHORT_4_4_4_4:
                     case GL_UNSIGNED_SHORT_4_4_4_4_REV:  internalFormat=GL_RGBA4; break;
                     case GL_UNSIGNED_SHORT_5_5_5_1:
                     case GL_UNSIGNED_SHORT_1_5_5_5_REV:  internalFormat=GL_RGB5_A1; break;
                     case GL_UNSIGNED_INT_8_8_8_8:
                     case GL_UNSIGNED_INT_8_8_8_8_REV:    internalFormat=GL_RGBA8; break;
                     case GL_UNSIGNED_INT_10_10_10_2:
                     case GL_UNSIGNED_INT_2_10_10_10_REV: internalFormat=GL_RGB10_A2; break;
                     default:                             break;
                  };
                  break;
               default: break;
            }

            // create texture object
            shared_ptr<ge::gl::TextureObject> textureObject=
                  d<=1 ? make_shared<ge::gl::TextureObject>(target,internalFormat,
                                                            1+int(floor(logf(std::max(w,h))/logf(2.0f))),w,h)
                       : make_shared<ge::gl::TextureObject>(target,internalFormat,
                                                            1+int(floor(logf(std::max(w,h))/logf(2.0f))),w,h,d);

            // fill texture object with data
            if(data) {
               textureObject->bind(0);
               if(d<=1) glTexSubImage2D(target,0,0,0,w,h,format,type,data);
               else     glTexSubImage3D(target,0,0,0,0,w,h,d,format,type,data);
               glGenerateMipmap(target);
            }

            // create ActiveTexture command
            stateSet->addCommand(ge::gl::sharedActiveTexture(GL_TEXTURE0));

            // create BindTexture command
            auto bindTexture=ge::gl::sharedBindTexture(GL_TEXTURE_2D,textureObject);
            stateSet->addCommand(bindTexture);
         }
      }

      // process geometry
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
         unsigned numPrimitives=g->getNumPrimitiveSets();
         vector<PrimitiveGpuData> primitiveData;
         vector<Primitive> primitives;
         primitiveData.reserve(numPrimitives);
         primitives.reserve(numPrimitives);
         unsigned numIndices=0;
         for(unsigned i=0; i<numPrimitives; i++)
         {
            osg::PrimitiveSet *ps=g->getPrimitiveSet(i);
            unsigned glMode=ps->getMode();
            unsigned mode=useIndices?glMode|0x10:glMode;
            unsigned count,first;
            osg::DrawElements *e=ps->getDrawElements();
            if(e!=nullptr)
            {
               primitives.emplace_back(primitiveData.size()*sizeof(PrimitiveGpuData)/4, // offset4
                                       mode);
               count=e->getNumIndices();
               first=numIndices;
               numIndices+=count;
            }
            else
            {
               switch(ps->getType()) {
                  case osg::PrimitiveSet::DrawArraysPrimitiveType:
                  {
                     primitives.emplace_back(primitiveData.size()*sizeof(PrimitiveGpuData)/4, // offset4
                                             mode);
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
                        primitives.emplace_back(primitiveData.size()*sizeof(PrimitiveGpuData)/4, // offset4
                                                mode);
                        unsigned count=a->operator[](i);
                        primitiveData.emplace_back(useIndices?count|0x80000000:count, // countAndIndexedFlag
                                                   first,0);
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
            primitiveData.emplace_back(useIndices?count|0x80000000:count, // countAndIndexedFlag
                                       first,0);
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
         m.allocData(config,numVertices,numIndices,primitiveData.size());

         // upload primitives
         m.setAndUploadPrimitives(primitiveData.data(),
                                  primitives.data(),primitiveData.size());

         // create instances
         shared_ptr<MatrixList> &ml=transformationStack.back()->getOrCreateMatrixList();
         m.createObject(ml.get(),stateSet.get());

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

      if(drawable.getStateSet())
         popState();
   }

};


void Init()
{
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
      }

      // release OSG memory
      osgDB::Registry::instance()->closeAllLibraries();
      osgDB::Registry::instance(true);
   }


   // unmap buffers
   // (it has to be done before rendering)
   RenderingContext::current()->unmapBuffers();


   ge::gl::initShadersAndPrograms();
   ambientProgram = new ProgramObject(
      GL_VERTEX_SHADER,
      static_cast<std::stringstream&>(stringstream()<<
      "#version 430\n"
      <<(useARBShaderDrawParameters
      ? "#extension GL_ARB_shader_draw_parameters : enable\n"
        "\n"
        "layout(std430,binding=0) restrict readonly buffer InstancingMatrix {\n"
        "   mat4 instancingMatrixBuffer[];\n"
        "};\n"
      : ""
      )<<
      "\n"
      "layout(location=0) in vec4 position;\n"
      "layout(location=2) in vec4 color;\n"
      "layout(location=3) in vec2 texCoord;\n"
      <<(useARBShaderDrawParameters
      ? ""
      : "layout(location=12) in mat4 instancingMatrix;\n"
      )<<
      "\n"
      "layout(location=0) out vec4 colorOut;\n"
      "layout(location=1) out vec2 texCoordOut;\n"
      "\n"
      "uniform vec4 globalAmbientLight; // alpha must be 1\n"
      "uniform mat4 projection;\n"
      "\n"
      "void main()\n"
      "{\n"
      "   // ambient lighting\n"
      "   colorOut=globalAmbientLight*color;\n"
      "   texCoordOut=texCoord;\n"
      "\n"
      "   // vertex position\n"
      <<(useARBShaderDrawParameters
      ? "   uint matrixOffset64=gl_BaseInstanceARB+gl_InstanceID;\n"
        "   gl_Position=projection*instancingMatrixBuffer[matrixOffset64]*position;\n"
      : "   gl_Position=projection*instancingMatrix*position;\n"
      )<<
      "}\n").str(),
      GL_FRAGMENT_SHADER,
      "#version 330\n"
      "\n"
      "in vec4 color;\n"
      "in vec2 texCoord;\n"
      "\n"
      "layout(location=0) out vec4 fragColor;\n"
      "\n"
      "uniform int colorTexturingMode; // 0 - no texturing, 1 - modulate, 2 - replace\n"
      "uniform sampler2D colorTexture;\n"
      "\n"
      "void main()\n"
      "{\n"
      "   // texturing and final color\n"
      "   if(colorTexturingMode==0) // no texturing\n"
      "      fragColor=color;\n"
      "   else if(colorTexturingMode==1) // modulate\n"
      "      fragColor=color*texture(colorTexture,texCoord);\n"
      "   else // replace\n"
      "      fragColor=texture(colorTexture,texCoord);\n"
      "}\n");
   simplifiedPhongProgram = new ProgramObject(
      GL_VERTEX_SHADER,
      static_cast<std::stringstream&>(stringstream()<<
      "#version 430\n"
      <<(useARBShaderDrawParameters
      ? "#extension GL_ARB_shader_draw_parameters : enable\n"
        "\n"
        "layout(std430,binding=0) restrict readonly buffer InstancingMatrix {\n"
        "   mat4 instancingMatrixBuffer[];\n"
        "};\n"
      : ""
      )<<
      "\n"
      "layout(location=0) in vec4 position;\n"
      "layout(location=1) in vec3 normal;\n"
      "layout(location=2) in vec4 color;\n"
      "layout(location=3) in vec2 texCoord;\n"
      <<(useARBShaderDrawParameters
      ? ""
      : "layout(location=12) in mat4 instancingMatrix;\n"
      )<<
      "\n"
      "layout(location=0) out vec3 eyePosition;\n"
      "layout(location=1) out vec3 eyeNormal;\n"
      "layout(location=2) out vec4 colorOut;\n"
      "layout(location=3) out vec2 texCoordOut;\n"
      "\n"
      "uniform mat4 projection;\n"
      "\n"
      "void main()\n"
      "{\n"
      "   colorOut=color;\n"
      "   texCoordOut=texCoord;\n"
      <<(useARBShaderDrawParameters
      ? "   uint matrixOffset64=gl_BaseInstanceARB+gl_InstanceID;\n"
        "   mat4 instancingMatrix=instancingMatrixBuffer[matrixOffset64];\n"
        "   vec4 v=instancingMatrix*position;\n"
      : "   vec4 v=instancingMatrix*position;\n"
      )<<
      "   eyePosition=v.xyz;\n"
      "   eyeNormal=transpose(inverse(mat3(instancingMatrix)))*normal;\n"
      "   gl_Position=projection*v;\n"
      "}\n").str(),
      GL_FRAGMENT_SHADER,
      "#version 330\n"
      "\n"
      "in vec3 eyePosition;\n"
      "in vec3 eyeNormal;\n"
      "in vec4 color;\n"
      "in vec2 texCoord;\n"
      "\n"
      "layout(location=0) out vec4 fragColor;\n"
      "\n"
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
