#include <iostream> // for cerr
#include <memory>
#include <geRG/AttribStorage.h>
#include <geRG/Mesh.h>
#include <geRG/SeparateBuffersAttribStorage.h> // for DefaultFactory

using namespace ge::rg;
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
}


AttribStorage::~AttribStorage()
{
   cancelAllAllocations();
   _renderingContext->onAttribStorageRelease(this);
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
bool AttribStorage::allocData(Mesh &mesh,int numVertices,int numIndices)
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
   mesh.setDrawCommandBlockId(0);

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
bool AttribStorage::reallocData(Mesh &mesh,int numVertices,int numIndices,
                                bool preserveContent)
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
   if(mesh.drawCommandBlockId()!=0)
   {
      cerr<<"Error: calling AttribStorage::freeData() on Mesh\n"
            "   that has still draw commands allocated."<<endl;
      return;
   }

   // release vertices and indices allocations
   _vertexAllocationManager.free(mesh.verticesDataId());
   _indexAllocationManager.free(mesh.indicesDataId());

   // update Mesh
   mesh.setAttribStorage(nullptr);
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
   return make_shared<SeparateBuffersAttribStorage>(config,numVertices,numIndices);
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
