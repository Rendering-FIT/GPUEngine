#include <iostream> // for cerr
#include <memory>
#include <geRG/AttribStorage.h>
#include <geRG/Mesh.h>
#include <geRG/StateSet.h>
#include <geGL/VertexArray.h>

using namespace ge::rg;
using namespace ge::gl;
using namespace std;


shared_ptr<AttribStorage::Factory> AttribStorage::_factory = make_shared<AttribStorage::Factory>();



AttribStorage::AttribStorage(const AttribConfigRef &config,unsigned numVertices,
                             unsigned numIndices)
   : _vertexAllocationManager(numVertices)
   , _indexAllocationManager(numIndices)
   , _attribConfig(config)
   , _renderingContext(config->renderingContext())
{
   _renderingContext->onAttribStorageInit(this);

   // get ConfigData
   const AttribConfig::ConfigData &configData=config->configData();

   // create VAO
   _va=make_shared<VertexArray>();

   // create buffer objects
   _bufferList.reserve(configData.attribTypes.size());
   unsigned i=0;
   for(auto it=configData.attribTypes.begin(); it!=configData.attribTypes.end(); it++,i++)
   {
      AttribType t=*it;
      auto b=make_shared<Buffer>(numVertices*t.elementSize(),nullptr,GL_DYNAMIC_DRAW);
      _va->addAttrib(b,i,t.numComponents(),t.glTypeAsInt(),t.elementSize(),0,
                     t.typeHandling()==AttribType::INTEGER_NORMALIZE,t.divisor());
      _bufferList.push_back(b);
   }

   // create EBO
   if(configData.ebo)
   {
      _eb=make_shared<Buffer>(numIndices*4,nullptr,GL_DYNAMIC_DRAW);
      _va->addElementBuffer(_eb);
   }
   else
   {
      if(numIndices>0)
         cout<<"Warning in AttribStorage constructor: If config parameter\n"
               "   specifies to not use indices (AttribConfig::ebo),\n"
               "   numIndices parameter must be zero.\n"<<endl;
      _eb=nullptr;
   }

   // append transformation matrix to VAO
   if(_renderingContext->useARBShaderDrawParameters()==false) {
      _va->bind();
      _renderingContext->matrixStorage()->buffer()->bind(GL_ARRAY_BUFFER);
      const GLuint index=12;
      auto& gl=_va->getContext();
      gl.glEnableVertexAttribArray(index+0);
      gl.glEnableVertexAttribArray(index+1);
      gl.glEnableVertexAttribArray(index+2);
      gl.glEnableVertexAttribArray(index+3);
      gl.glVertexAttribPointer(index+0,4,GL_FLOAT,GL_FALSE,int(sizeof(float)*16),(void*)(sizeof(float)*0));
      gl.glVertexAttribPointer(index+1,4,GL_FLOAT,GL_FALSE,int(sizeof(float)*16),(void*)(sizeof(float)*4));
      gl.glVertexAttribPointer(index+2,4,GL_FLOAT,GL_FALSE,int(sizeof(float)*16),(void*)(sizeof(float)*8));
      gl.glVertexAttribPointer(index+3,4,GL_FLOAT,GL_FALSE,int(sizeof(float)*16),(void*)(sizeof(float)*12));
      gl.glVertexAttribDivisor(index+0,1);
      gl.glVertexAttribDivisor(index+1,1);
      gl.glVertexAttribDivisor(index+2,1);
      gl.glVertexAttribDivisor(index+3,1);
      _va->unbind();
   }
}


AttribStorage::~AttribStorage()
{
   // invalidate all allocations and clean up
   cancelAllAllocations();
   _renderingContext->onAttribStorageRelease(this);
}


void AttribStorage::bind() const
{
   _va->bind();
}


/** Allocates the memory for vertices and indices
 *  inside AttribStorage managed Vertex Array Object (VAO).
 *
 *  Returns true on success. False on failure, usually caused by absence of
 *  large enough free memory block.
 *
 *  The method does not require active graphics context.
 *
 *  @param mesh object that receives the allocation information.
 *           Any further references to the allocated memory are
 *           performed using the mesh passed in this parameter.
 *           The mesh must not have any allocated vertices or
 *           indices in the time of call of this method.
 *  @param numVertices number of vertices to be allocated
 *  @param numIndices number of indices to be allocated inside associated
 *                    Element Buffer Object
 */
bool AttribStorage::allocData(Mesh &mesh,unsigned numVertices,unsigned numIndices)
{
   // do we have enough space?
   if(!_vertexAllocationManager.canAllocate(numVertices) ||
      !_indexAllocationManager.canAllocate(numIndices))
      return false;

   // allocate memory for vertices (inside AttribStorage's preallocated memory or buffers)
   unsigned verticesDataId=_vertexAllocationManager.alloc(numVertices,mesh);

   // allocate memory for indices (inside AttribStorage's preallocated memory or buffers)
   unsigned indicesDataId;
   if(numIndices==0)
      indicesDataId=0;
   else
      indicesDataId=_indexAllocationManager.alloc(numIndices,mesh);

   // update Mesh
   if(mesh.attribStorage()!=NULL)
   {
      cerr<<"Warning: calling AttribStorage::allocData() on Mesh\n"
            "   that is not empty." << endl;
      mesh.freeData();
   }
   mesh.setAttribStorage(this);
   mesh.setVerticesDataId(verticesDataId);
   mesh.setIndicesDataId(indicesDataId);
   mesh.setPrimitivesDataId(0);

   return true;
}


/** Changes the number of allocated vertices and indices.
 *
 *  Parameter mesh contains the reference to Mesh holding allocation information.
 *  numVertices and numIndices are the new number of elements in vertex and index arrays.
 *  If preserveContent parameter is true, the content of element and index data will be preserved.
 *  If new data are larger, the content over the size of previous data is undefined.
 *  If new data are smaller, only the data up to the new data size is preserved.
 *  If preserveContent is false, content of element and index data are undefined
 *  after reallocation.
 */
bool AttribStorage::reallocData(Mesh &/*mesh*/,unsigned /*numVertices*/,unsigned /*numIndices*/,
                                bool /*preserveContent*/)
{
   // Used strategy:
   // - if new arrays are smaller, we keep data in place and free the remaning space
   // - if new arrays are bigger and can be enlarged on the place, we do it
   // - otherwise we try to allocate new place for the data in the same AttribStorage
   // - if we do not succeed in the current AttribStorage, we move the data to
   //   some other AttribStorage
   // - if no AttribStorage accommodate us, we allocate new AttribStorage

   // FIXME: not implemented yet
   return false;
}


/** Releases the memory pointed by mesh.
 *
 *  Memory pointed by r inside internally pre-allocated Vertex Array Object (VAO)
 *  is marked free.
 *
 *  The method does not require active graphics context.
 */
void AttribStorage::freeData(Mesh &mesh)
{
   // check whether this attribStorage owns the given Mesh
   if(mesh.attribStorage()!=this)
   {
      cerr<<"Error: calling AttribStorage::freeData() on Mesh\n"
            "   that is not managed by this AttribStorage."<<endl;
      return;
   }

   // make sure that there are no draw commands
   // (draw commands has to be freed first, otherwise we can not mark
   // Mesh as empty by setting attribStorage member to NULL)
   if(mesh.primitivesDataId()!=0)
   {
      cerr<<"Error: calling AttribStorage::freeData() on Mesh\n"
            "   that still has primitive sets allocated.\n"
            "   Free primitive sets of associated Mesh first."<<endl;
      return;
   }

   // release vertices and indices allocations
   _vertexAllocationManager.free(mesh.verticesDataId());
   _indexAllocationManager.free(mesh.indicesDataId());

   // update Mesh
   mesh.setAttribStorage(nullptr);
}


void AttribStorage::uploadVertices(Mesh &mesh,const void*const *attribList,
                                   unsigned attribListSize,
                                   unsigned numVertices,unsigned fromIndex)
{
   const AttribConfig::ConfigData &configData=_attribConfig->configData();
   unsigned c = unsigned(_bufferList.size());
   assert(c==attribListSize && "Number of attributes passed in parameters and stored inside "
                               "AttribStorage must match.");
   for(unsigned i=0; i<c; i++)
   {
      AttribType t=configData.attribTypes[i];
      unsigned elementSize=t.elementSize();
      unsigned srcOffset=fromIndex*elementSize;
      unsigned dstOffset=(_vertexAllocationManager[mesh.verticesDataId()].startIndex+fromIndex)*elementSize;
      const void *data=attribList[i];
      _bufferList[i]->setData(((uint8_t*)data)+srcOffset,
                              numVertices*elementSize,dstOffset);
   }
}


void AttribStorage::uploadIndices(Mesh &mesh,const void *indices,
                                  unsigned numIndices,unsigned fromIndex)
{
   if(_eb==nullptr) {
      cout<<"Error in AttribStorage::uploadIndices(): ebo is null.\n"
            "   AttribStorage was probably created with AttribConfig\n"
            "   without ebo member set to true." << endl;
      return;
   }
   const unsigned elementSize=4;
   unsigned srcOffset=fromIndex*elementSize;
   unsigned dstOffset=(_indexAllocationManager[mesh.indicesDataId()].startIndex+fromIndex)*elementSize;
   _eb->setData((uint8_t*)indices+srcOffset,numIndices*elementSize,dstOffset);
}


void AttribStorage::render(const std::vector<RenderingCommandData>& renderingDataList)
{
   // bind VAO
   bind();

   // perform indirect draw calls
   auto& gl=_va->getContext();
   if(attribConfig()->configData().ebo)
      for(auto it2=renderingDataList.begin(),e=renderingDataList.end(); it2!=e; it2++)
      {
         // call MultiDrawElementsIndirect
         GLintptr offset=it2->indirectBufferOffset4*4;
         gl.glMultiDrawElementsIndirect(it2->glMode,GL_UNSIGNED_INT,(const void*)offset,GLsizei(it2->drawCommandCount),0);
      }
   else
      for(auto it2=renderingDataList.begin(),e=renderingDataList.end(); it2!=e; it2++)
      {
         // call MultiDrawArraysIndirect
         GLintptr offset=it2->indirectBufferOffset4*4;
         gl.glMultiDrawArraysIndirect(it2->glMode,(const void*)offset,GLsizei(it2->drawCommandCount),0);
      }
}


void AttribStorage::cancelAllAllocations()
{
   // break Mesh references to this AttribStorage
   for(auto it=_vertexAllocationManager.begin(); it!=_vertexAllocationManager.end(); it++)
      if(it->owner)
         it->owner->setAttribStorage(nullptr);
   for(auto it=_indexAllocationManager.begin(); it!=_indexAllocationManager.end(); it++)
      if(it->owner)
         it->owner->setAttribStorage(nullptr);

   // empty allocation maps
   _vertexAllocationManager.clear();
   _indexAllocationManager.clear();
}


shared_ptr<AttribStorage> AttribStorage::Factory::create(const AttribConfigRef &config,
        unsigned numVertices,unsigned numIndices)
{
   return make_shared<AttribStorage>(config,numVertices,numIndices);
}


// AttribStorage documentation
// note: brief description is with the class declaration
/** \class ge::rg::AttribStorage
 *
 *  It is benefical to store all the vertex attributes in only few AttribStorage
 *  objects because only few OpenGL vertex array objects (VAO) are required,
 *  number of culling and rendering optimizations can be deployed
 *  and the whole scene can be drawn using only few draw calls.
 *
 *  Each AttribStorage object can store vertex attributes of the same format only.
 *  For instance, vertex attributes composed of coordinates and colors are
 *  stored in different AttribStorage than vertex attributes composed of
 *  coordinates, normals and texture coordinates. Format of a particular
 *  attribute must be the same too. For instance, colors stored as RGBA8
 *  are stored in different AttribStorage than colors stored as three floats.
 *
 *  AttribStorage is expected to be used with one graphics context only and
 *  that context is expected to be current when working with the AttribStorage.
 *  The easiest rule is that whenever you are processing your scene graph
 *  and perform any changes that may change the scene geometry, including adding
 *  and removing objects, have your graphics context current.
 *
 *  Constructor require graphics context current to allocate internal VAO
 *  and other OpenGL objects. Destructor requires it to delete these OpenGL objects.
 *  However, there is a difficulty as the graphics context may be destroyed because of
 *  various reasons, including closing of the window or power-saving reasons
 *  on mobile devices. In such cases, the user is expected to call
 *  RenderingContext::contextLost() before any further scene graph processing.
 *  RenderingContext::contextLost() will forward the call to all AttribStorages,
 *  calling their contextLost(). This will clear all internal structures
 *  as if no data would be uploaded to graphics context yet. This could be performed
 *  even without active graphics context, after it was lost or destroyed.
 *  Depending on user choose, he might decide to recreate the graphics
 *  context and reinitialize attribute data, for instance, by reloading
 *  model files, or he might safely start to tear down the application that
 *  is in consistent state after calling RenderingContext::contextLost().
 *
 *  For more details, which methods can be called without active graphics context
 *  refer to the documentation to each of the object's methods.
 *
 *  \sa RenderingContext, Mesh, Mesh::getAttribConfig()
 */
