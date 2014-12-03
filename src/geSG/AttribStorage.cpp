#include <iostream> // for cerr
#include <memory>
#include <geSG/Array.h>
#include <geSG/AttribStorage.h>
#include <geSG/AttribReference.h>
#include <geSG/SeparateBuffersAttribStorage.h> // for DefaultFactory

using namespace ge::sg;
using namespace std;


class DefaultFactory : public AttribStorage::Factory {
public:
   virtual shared_ptr<AttribStorage> create(const AttribConfig &config,
                                            unsigned numVertices,unsigned numIndices)
   {
      return make_shared<SeparateBuffersAttribStorage>(config,numVertices,numIndices);
   }
};

shared_ptr<AttribStorage::Factory> AttribStorage::_factory = make_shared<DefaultFactory>();



AttribStorage::AttribStorage(const AttribConfig &config,unsigned numVertices,unsigned numIndices)
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
   , _attribConfig(config)
{
   // zero element is reserved for invalid object
   // and it serves as Null object (Null object design pattern)
   _verticesDataAllocationMap.emplace_back(0,0,nullptr,0);
   _indicesDataAllocationMap.emplace_back(0,0,nullptr,0);
}


AttribStorage::~AttribStorage()
{
   cancelAllAllocations();
}


/** Allocates the memory for vertices and indices inside AttribStorage
 *  managed Vertex Array Object (VAO).
 *
 *  Returns true on success. False on failure, usually caused by absence of
 *  large enough free memory block.
 *
 *  The method does not require active graphics context.
 *
 *  @param r receives the allocation information and any further references
 *           to the allocated memory are performed using AttribReference
 *           returned in this parameter.
 *  @param numVertices number of vertices to be allocated
 *  @param numIndices number of indices to be allocated inside associated
 *                    Element Buffer Object
 */
bool AttribStorage::allocData(AttribReference &r,int numVertices,int numIndices)
{
   // do we have enough space?
   if(_numVerticesAvailableAtTheEnd<numVertices || _numIndicesAvailableAtTheEnd<numIndices)
      return false;

   // allocate memory for vertices (inside AttribStorage's preallocated memory or buffers)
   unsigned verticesDataId=_verticesDataAllocationMap.size();
   _verticesDataAllocationMap.emplace_back(_firstVertexAvailableAtTheEnd,numVertices,&r,0);
   _verticesDataAllocationMap[_idOfVerticesBlockAtTheEnd].nextRec=verticesDataId;
   _idOfVerticesBlockAtTheEnd=verticesDataId;

   // allocate memory for indices (inside AttribStorage's preallocated memory or buffers)
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

   // update AttribReference
   if(r.attribStorage!=NULL)
   {
      cerr<<"Error: calling AttribStorage::allocData() on AttribReference\n"
            "   that is not empty." << endl;
      r.freeData();
   }
   r.attribStorage=this;
   r.verticesDataId=verticesDataId;
   r.indicesDataId=indicesDataId;

   // update AttribStorage internal allocation variables
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
 *  Parameter r contains the reference to AttribReference holding allocation information.
 *  numVertices and numIndices are the new number of elements in vertex and index arrays.
 *  If preserveContent parameter is true, the content of element and index data will be preserved.
 *  If new data are larger, the content over the size of previous data is undefined.
 *  If new data are smaller, only the data up to the new data size is preserved.
 *  If preserveContent is false, content of element and index data are undefined
 *  after reallocation.
 */
bool AttribStorage::reallocData(AttribReference &r,int numVertices,int numIndices,bool preserveContent)
{
   // Used strategy:
   // - if new arrays are smaller, we keep data in place and free the remaning space
   // - if new arrays are bigger and can be enlarged on the place, we do it
   // - otherwise we try to allocate new place for the data in the same AttribStorage
   // - if we do not succeed in the current AttribStorage, we move the data to
   //   some other AttribStorage
   // - if no AttribStorage accommodate us, we allocate new AttribStorage

   // FIXME: not implemented yet
}


/** Releases the memory pointed by AttribReference r.
 *
 *  Memory pointed by r inside internally pre-allocated Vertex Array Object (VAO)
 *  is marked free.
 *
 *  The method does not require active graphics context.
 */
void AttribStorage::freeData(AttribReference &r)
{
   // check whether this attribStorage owns given AttribReference
   if(r.attribStorage!=this)
   {
      cerr<<"Error: calling AttribStorage::freeData() on AttribReference\n"
            "   that is not managed by this AttribStorage."<<endl;
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

   // update AttribReference
   r.attribStorage=NULL;
}


void AttribStorage::cancelAllAllocations()
{
   // break references from AttribReferences
   for(auto it=_verticesDataAllocationMap.begin(); it!=_verticesDataAllocationMap.end(); it++)
      if(it->owner)
         it->owner->attribStorage=nullptr;
   for(auto it=_indicesDataAllocationMap.begin(); it!=_indicesDataAllocationMap.end(); it++)
      if(it->owner)
         it->owner->attribStorage=nullptr;

   // empty allocation maps
   _verticesDataAllocationMap.clear();
   _indicesDataAllocationMap.clear();

   // reinitialize variables
   _numVerticesAvailable=_numVerticesTotal;
   _numVerticesAvailableAtTheEnd=_numVerticesTotal;
   _firstVertexAvailableAtTheEnd=0;
   _idOfVerticesBlockAtTheEnd=0;
   _numIndicesAvailable=_numIndicesTotal;
   _numIndicesAvailableAtTheEnd=_numIndicesTotal;
   _firstIndexAvailableAtTheEnd=0;
   _idOfIndicesBlockAtTheEnd=0;
}


// AttribStorage::AllocationBlock::nextRec documentation
// note: brief description is with the variable declaration
/** \var unsigned AttribStorage::AllocationBlock::nextRec
 *
 *  Order of AllocationBlocks stored in std::vector<AllocationBlock>
 *  often does not correspond with the order of their memory placements.
 *  nextRec is index to the std::vector<AllocationBlock> and points
 *  to the AllocationBlock whose allocated memory follows the current one.
 */
