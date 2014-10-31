#include <iostream> // for cerr
#include <geSG/Array.h>
#include <geSG/AttribsStorage.h>
#include <geSG/AttribsReference.h>

using namespace ge::sg;
using namespace std;

shared_ptr<AttribsStorage::Factory> AttribsStorage::_factory;



AttribsStorage::AttribsStorage(const AttribsConfig &config,unsigned numVertices,unsigned numIndices)
   : _numVerticesTotal(numVertices)
   , _numVerticesAvailable(numVertices)
   , _numVerticesAvailableAtTheEnd(numVertices)
   , _firstVertexAvailableAtTheEnd(0) // all vertices are available
   , _idOfVerticesBlockAtTheEnd(0) // points to zero element
   , _numIndicesTotal(numIndices)
   , _numIndicesAvailable(numIndices)
   , _numIndicesAvailableAtTheEnd(numIndices)
   , _firstIndexAvailableAtTheEnd(0) // all indices are available
   , _idOfIndicesBlockAtTheEnd(0) // points to zero element
   , _attribsConfig(config)
   , _attribsConfigId(config.convertToId())
{
   // zero element is reserved for invalid object
   // and it serves as Null object (Null object design pattern)
   _verticesDataAllocationMap.emplace_back(0,0,nullptr,0);
   _indicesDataAllocationMap.emplace_back(0,0,nullptr,0);
}


AttribsStorage::~AttribsStorage()
{
}


/** Allocates the memory for vertices and indices inside AttribsStorage
 *  managed Vertex Array Object (VAO).
 *
 *  Returns true on success. False on failure, usually caused by absence of
 *  large enough free memory block.
 *
 *  The method does not require active graphics context.
 *
 *  @param r receives the allocation information and any further references
 *           to the allocated memory are performed using AttribsReference
 *           returned in this parameter.
 *  @param numVertices number of vertices to be allocated
 *  @param numIndices number of indices to be allocated inside associated
 *                    Element Buffer Object
 */
bool AttribsStorage::allocData(AttribsReference &r,int numVertices,int numIndices)
{
   // do we have enough space?
   if(_numVerticesAvailableAtTheEnd<numVertices || _numIndicesAvailableAtTheEnd<numIndices)
      return false;

   // allocate memory for vertices (inside AttribsStorage's preallocated memory or buffers)
   unsigned verticesDataId=_verticesDataAllocationMap.size();
   _verticesDataAllocationMap.emplace_back(_firstVertexAvailableAtTheEnd,numVertices,&r,0);
   _verticesDataAllocationMap[_idOfVerticesBlockAtTheEnd].nextRec=verticesDataId;
   _idOfVerticesBlockAtTheEnd=verticesDataId;

   // allocate memory for indices (inside AttribsStorage's preallocated memory or buffers)
   unsigned indicesDataId;
   if(numIndices==0)
      indicesDataId=0;
   else
   {
      indicesDataId=_indicesDataAllocationMap.size();
      _indicesDataAllocationMap.emplace_back(_firstIndexAvailableAtTheEnd,numIndices,&r,0);
      _indicesDataAllocationMap[_idOfIndicesBlockAtTheEnd].nextRec=indicesDataId;
      _idOfIndicesBlockAtTheEnd=indicesDataId;
   }

   // update AttribsReference
   if(r.attribsStorage!=NULL)
   {
      cerr<<"Error: calling AttribsStorage::allocData() on AttribsReference\n"
            "   that is not empty." << endl;
      r.freeData();
   }
   r.attribsStorage=this;
   r.verticesDataId=verticesDataId;
   r.indicesDataId=indicesDataId;

   // update AttribsStorage internal allocation variables
   _numVerticesAvailable-=numVertices;
   _numVerticesAvailableAtTheEnd-=numVertices;
   _firstVertexAvailableAtTheEnd+=numVertices;
   _numIndicesAvailable-=numIndices;
   _numIndicesAvailableAtTheEnd-=numIndices;
   _firstIndexAvailableAtTheEnd+=numIndices;

   return true;
}


/** Changes the number of allocated elements or indices.
 *
 *  Parameter r contains the reference to AttribsReference holding allocation information.
 *  numVertices and numIndices are the new number of elements in vertex and index arrays.
 *  If preserveContent parameter is true, the content of element and index data will be preserved.
 *  If new data are larger, the content over the size of previous data is undefined.
 *  If new data are smaller, only the data up to the new data size is preserved.
 *  If preserveContent is false, content of element and index data are undefined
 *  after reallocation.
 */
bool AttribsStorage::reallocData(AttribsReference &r,int numVertices,int numIndices,bool preserveContent)
{
   // Used strategy:
   // - if new arrays are smaller, we keep data in place and free the remaning space
   // - if new arrays are bigger and can be enlarged on the place, we do it
   // - otherwise we try to allocate new place for the data in the same AttribsStorage
   // - if we do not succeed in the current AttribsStorage, we move the data to
   //   some other AttribsStorage
   // - if no AttribsStorage accommodate us, we allocate new AttribsStorage

   // FIXME: not implemented yet
}


/** Releases the memory pointed by AttribsReference r.
 *
 *  Memory pointed by r inside internally pre-allocated Vertex Array Object (VAO)
 *  is marked free.
 *
 *  The method does not require active graphics context.
 */
void AttribsStorage::freeData(AttribsReference &r)
{
   // check whether this attribsStorage owns given AttribsReference
   if(r.attribsStorage!=this)
   {
      cerr<<"Error: calling AttribsStorage::freeData() on AttribsReference\n"
            "   that is not managed by this AttribsStorage."<<endl;
      return;
   }

   // release vertices and indices allocations
   AllocationBlock &ab=_verticesDataAllocationMap[r.verticesDataId];
   ab.owner=NULL;
   if(r.indicesDataId!=0)
   {
      ab=_indicesDataAllocationMap[r.indicesDataId];
      ab.owner=NULL;
   }

   // update AttribsReference
   r.attribsStorage=NULL;
}


void AttribsStorage::uploadVertexData(AttribsReference &r,Mesh* mesh,int fromIndex,int numVertices)
{
}


int AttribsStorage::uploadVertexData(AttribsReference &r,Mesh* mesh,unsigned &currentPosition,int bytesToUpload)
{
}


void AttribsStorage::uploadIndicesData(AttribsReference &r,Mesh* mesh,int fromIndex,int numVertices)
{
}


int AttribsStorage::uploadIndicesData(AttribsReference &r,Mesh* mesh,unsigned &currentPosition,int bytesToUpload)
{
}


// AttribsStorage::AllocationBlock::nextRec documentation
// note: brief description is with the variable declaration
/** \var unsigned AttribsStorage::AllocationBlock::nextRec
 *
 *  Order of AllocationBlocks stored in std::vector<AllocationBlock>
 *  often does not correspond with the order of their memory placements.
 *  nextRec is index to the std::vector<AllocationBlock> and points
 *  to the AllocationBlock whose allocated memory follows the current one.
 */

// AttribsStorage::_attribsConfigId documentation
// note: brief description is with the variable declaration
/** \var AttribsStorage::AttribsConfigId AttribsStorage::_attribsConfigId
 *
 *  If it is non-zero, _attribsConfig contains one of known frequently used
 *  attribute configurations. Thus, optimized routines may be used for
 *  operations with attribute configurations such as comparison or lookups,
 *  as it is just comparison of integers or lookup by integer.
 *
 *  If the value is zero, all operations with attribute configurations
 *  have to be performed using _attribsConfig. _attribsConfig is vector
 *  of values storing details about each attribute configuration.
 *
 *  If one AttribsStorage has _attribConfig zero and the second non-zero,
 *  they always contain different attribute configurations.
 */
