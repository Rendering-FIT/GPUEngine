#include <map>
#include <memory>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include <geGL/TextureObject.h>
#include <geRG/AttribType.h>
#include <geRG/Model.h>
#include <geRG/Transformation.h>
#include <geRG/StateSet.h>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/NodeVisitor>
#include <osg/StateSet>
#include <osg/Transform>
#include "OsgImport.h"

using namespace std;
using namespace ge::rg;



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


static GLint getInternalTextureFormat(GLenum format,GLenum type)
{
   switch(format) {
      case GL_RED:
      case GL_RED_INTEGER:
         switch(type) {
            case GL_UNSIGNED_BYTE:
            case GL_BYTE:           return GL_R8;
            case GL_UNSIGNED_SHORT:
            case GL_SHORT:          return GL_R16;
            case GL_UNSIGNED_INT:
            case GL_INT:            return GL_R16;
            case GL_FLOAT:          return GL_R16;
            default:                break;
         };
         break;
      case GL_RG:
      case GL_RG_INTEGER:
         switch(type) {
            case GL_UNSIGNED_BYTE:
            case GL_BYTE:           return GL_RG8;
            case GL_UNSIGNED_SHORT:
            case GL_SHORT:          return GL_RG16;
            case GL_UNSIGNED_INT:
            case GL_INT:            return GL_RG16;
            case GL_FLOAT:          return GL_RG16;
            default:                break;
         };
         break;
      case GL_RGB:
      case GL_BGR:
      case GL_RGB_INTEGER:
      case GL_BGR_INTEGER:
         switch(type) {
            case GL_UNSIGNED_BYTE:
            case GL_BYTE:           return GL_RGB8;
            case GL_UNSIGNED_SHORT:
            case GL_SHORT:          return GL_RGB16;
            case GL_UNSIGNED_INT:
            case GL_INT:            return GL_RGB16;
            case GL_FLOAT:          return GL_RGB16;
            case GL_UNSIGNED_BYTE_3_3_2:
            case GL_UNSIGNED_BYTE_2_3_3_REV:  return GL_R3_G3_B2;
            case GL_UNSIGNED_SHORT_5_6_5:
            case GL_UNSIGNED_SHORT_5_6_5_REV: return GL_RGB8;
            default:                          break;
         };
         break;
      case GL_RGBA:
      case GL_BGRA:
      case GL_RGBA_INTEGER:
      case GL_BGRA_INTEGER:
         switch(type) {
            case GL_UNSIGNED_BYTE:
            case GL_BYTE:           return GL_RGBA8;
            case GL_UNSIGNED_SHORT:
            case GL_SHORT:          return GL_RGBA16;
            case GL_UNSIGNED_INT:
            case GL_INT:            return GL_RGBA16;
            case GL_FLOAT:          return GL_RGBA16;
            case GL_UNSIGNED_SHORT_4_4_4_4:
            case GL_UNSIGNED_SHORT_4_4_4_4_REV:  return GL_RGBA4;
            case GL_UNSIGNED_SHORT_5_5_5_1:
            case GL_UNSIGNED_SHORT_1_5_5_5_REV:  return GL_RGB5_A1;
            case GL_UNSIGNED_INT_8_8_8_8:
            case GL_UNSIGNED_INT_8_8_8_8_REV:    return GL_RGBA8;
            case GL_UNSIGNED_INT_10_10_10_2:
            case GL_UNSIGNED_INT_2_10_10_10_REV: return GL_RGB10_A2;
            default:                             break;
         };
         break;
      default: break;
   }
   return 0;
}


static const float osg2glTransformation[16] = {
   1.f, 0.f, 0.f, 0.f,
   0.f, 0.f,-1.f, 0.f,
   0.f, 1.f, 0.f, 0.f,
   0.f, 0.f, 0.f, 1.f,
};


class BuildGpuEngineGraphVisitor : public osg::NodeVisitor {
protected:

   shared_ptr<Model> _model;
   vector<shared_ptr<Transformation>> transformationStack;
   vector<osg::ref_ptr<osg::StateSet>> osgStateSetStack;

public:

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


   inline shared_ptr<Model> model()  { return _model; }


   inline BuildGpuEngineGraphVisitor() : osg::NodeVisitor(osg::NodeVisitor::NODE_VISITOR,osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
   {
      _model=make_shared<Model>();
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

      // create new transformation
      shared_ptr<Transformation> t=make_shared<Transformation>();
      auto childIt=transformationStack.back()->addChild(t);
      transformationStack.emplace_back(t);

      // set matrix
      osg::Matrix m;
      transform.computeLocalToWorldMatrix(m,this);
      t->allocTransformationGpuData();
      t->uploadMatrix(osg::Matrixf(m).ptr());

      // traverse subgraph
      traverse(transform);

      // pop transformation
      // and remove it if it was not used
      transformationStack.pop_back();
      if(t->childList().empty() && t->matrixList()==nullptr)
         transformationStack.back()->removeChild(childIt);

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
      RenderingContext *rc=RenderingContext::current().get();

      // push new OSG stateSet on the stack
      if(drawable.getStateSet())
         pushState(*drawable.getStateSet());

      // get colorTexture
      std::shared_ptr<ge::gl::TextureObject> colorTexture;
      OsgState osgState(osgStateSetStack.back());
      if(osgState.colorTexture!=nullptr)
      {

         // get color texture name
         // FIXME: currentPath should be considered here
         string colorTexturePath;
         osg::Texture *osgTexture=osgState.colorTexture;
         if(osgTexture->getNumImages()>=1)
            colorTexturePath=osgTexture->getImage(0)->getFileName();

         // lookup texture cache
         // FIXME: path should be made canonical for cache lookup
         colorTexture=rc->cachedTextureObject(colorTexturePath);

         // create texture if not found in cache
         if(!colorTexture) {

            // create texture object
            GLenum target=osgTexture->getTextureTarget();
            osg::Image *osgImage=osgTexture->getNumImages()>0?osgTexture->getImage(0):nullptr;
            int w=osgImage?osgImage->s():osgTexture->getTextureWidth();
            int h=osgImage?osgImage->t():osgTexture->getTextureHeight();
            int d=osgImage?osgImage->r():osgTexture->getTextureDepth();
            GLenum format=osgImage?osgImage->getPixelFormat():osgTexture->getSourceFormat();
            GLenum type=osgImage?osgImage->getDataType():osgTexture->getSourceType();
            auto data=osgImage?osgImage->data():nullptr;

            // compute internalFormat;
            GLint internalFormat=getInternalTextureFormat(format,type);

            // create texture object
            colorTexture=
                  d<=1 ? make_shared<ge::gl::TextureObject>(target,internalFormat,
                                                            1+int(floor(logf(float(std::max(w,h)))/logf(2.0f))),w,h)
                       : make_shared<ge::gl::TextureObject>(target,internalFormat,
                                                            1+int(floor(logf(float(std::max(w,h)))/logf(2.0f))),w,h,d);

            // fill texture object with data
            if(data) {
               colorTexture->bind(0);
               if(d<=1) glTexSubImage2D(target,0,0,0,w,h,format,type,data);
               else     glTexSubImage3D(target,0,0,0,0,w,h,d,format,type,data);
               glGenerateMipmap(target);
            }
         }

         // update texture cache
         // FIXME: path should be made canonical for cache lookup
         rc->addCacheTextureObject(colorTexturePath,colorTexture);

      }

      // create GLState
      StateSetManager::GLState *glState=rc->createGLState();
      shared_ptr<ge::gl::ProgramObject> ambientProgram(RenderingContext::current()->getAmbientProgram());
      shared_ptr<ge::gl::ProgramObject> phongProgram(RenderingContext::current()->getPhongProgram());
      glState->set("glProgram",type_index(typeid(shared_ptr<ge::gl::ProgramObject>*)),&ambientProgram);
      glState->add("glProgram",type_index(typeid(shared_ptr<ge::gl::ProgramObject>*)),&phongProgram);
      glState->set("bin",type_index(typeid(int)),reinterpret_cast<void*>(0)); // bin 0 is for ambient pass
      glState->add("bin",type_index(typeid(int)),reinterpret_cast<void*>(1)); // bin 1 is for all light-rendering stuff
      glState->set("colorTexture",type_index(typeid(&colorTexture)),&colorTexture);

      // find (or create new) geRG StateSet
      // (StateSet is fully initialized during creation with all the rendering commands, etc.)
      shared_ptr<ge::rg::StateSet> stateSet(rc->getOrCreateStateSet(glState));
      delete glState;

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

         // generate primitives
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
                     for(size_t i=0,c=a->size(); i<c; i++)
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
         _model->meshList().emplace_back(make_shared<Mesh>());
         Mesh *m=_model->meshList().back().get();
         m->allocData(config,numVertices,numIndices,unsigned(primitiveData.size()));

         // upload primitives
         m->setAndUploadPrimitives(primitiveData.data(),
                                   primitives.data(),int(primitiveData.size()));

         // create Drawable
         const shared_ptr<MatrixList> &ml=transformationStack.back()->getOrCreateMatrixList();
         m->createDrawable(ml.get(),stateSet.get());

         // register transformation in the model
         if(_model->transformationRootList().size()==0)
            _model->addTransformationRoot(idof(scene,TransformationRoot),transformationStack.front());

         // upload vertices
         vector<void*> geArrays;
         geArrays.reserve(configData.attribTypes.size());
         for(unsigned i=0,c=unsigned(configData.attribTypes.size()); i<c; i++)
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
         m->uploadVertices(geArrays.data(),geArrays.size(),numVertices);
         for(unsigned i=0,c=unsigned(configData.attribTypes.size()); i<c; i++)
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
            m->uploadIndices(indices.data(),indices.size());
         }

      }

      if(drawable.getStateSet())
         popState();
   }

};


shared_ptr<Model> GEAD_EXPORT ge::osgImport::import(osg::Node *osgGraph)
{
   BuildGpuEngineGraphVisitor graphBuilder;
   osgGraph->ref();
   osgGraph->accept(graphBuilder);
   osgGraph->unref();
   return graphBuilder.model();
}
