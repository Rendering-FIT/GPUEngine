#include <iostream> // for cerr
#include <geSG/AttribObject.h>
#include <geSG/AttribDataReference.h>

using namespace ge::sg;
using namespace std;


AttribObject::AttribObject()
{
   // zero element is reserved for invalid object
   // and it serves as Null object (Null object design pattern)
   _verticesDataAllocationMap.emplace_back(0,0,nullptr,0);
   _indicesDataAllocationMap.emplace_back(0,0,nullptr,0);
}


bool AttribObject::allocData(AttribDataReference *r,int numVertices,int numIndices)
{
   // allocate memory for vertices (inside AttribObject preallocated memory or buffers)
   unsigned verticesDataId=_verticesDataAllocationMap.size();
   _verticesDataAllocationMap.emplace_back(_firstVertexAvailableAtTheEnd,numVertices,r,0);
   _verticesDataAllocationMap[_idOfVerticesBlockAtTheEnd].nextRec=verticesDataId;
   _idOfVerticesBlockAtTheEnd=verticesDataId;

   // allocate memory for indices (inside AttribObject preallocated memory or buffers)
   unsigned indicesDataId;
   if(numIndices==0)
      indicesDataId=0;
   else
   {
      indicesDataId=_indicesDataAllocationMap.size();
      _indicesDataAllocationMap.emplace_back(_firstIndexAvailableAtTheEnd,numIndices,r,0);
      _indicesDataAllocationMap[_idOfIndicesBlockAtTheEnd].nextRec=indicesDataId;
      _idOfIndicesBlockAtTheEnd=indicesDataId;
   }

   // update AttribDataReference
   if(r->attribObject!=NULL)
   {
      cerr<<"Error: calling AttribObject::allocData() on AttribDataReference\n"
            "   that is not empty." << endl;
      r->freeData();
   }
   r->attribObject=this;
   r->verticesDataId=verticesDataId;
   r->indicesDataId=indicesDataId;

   // update AttribObject internal allocation variables
   _numVerticesAvailable-=numVertices;
   _numVerticesAvailableAtTheEnd-=numVertices;
   _firstVertexAvailableAtTheEnd+=numVertices;
   _numIndicesAvailable-=numIndices;
   _numIndicesAvailableAtTheEnd-=numIndices;
   _firstIndexAvailableAtTheEnd+=numIndices;
}


/** Changes the number of allocated elements or indices.
 *
 *  Parameter r contains the reference to AttribDataReference holding allocation information.
 *  numVertices and numIndices are the new number of elements in vertex and index arrays.
 *  If preserveContent parameter is true, the content of element and index data will be preserved.
 *  If new data are larger, the content over the size of previous data is undefined.
 *  If new data are smaller, only the data up to the new data size is preserved.
 *  If preserveContent is false, content of element and index data are undefined.
 */
bool AttribObject::reallocData(AttribDataReference *r,int numVertices,int numIndices,bool preserveContent)
{
   // Used strategy:
   // - if new arrays are smaller, we keep data in place and free the remaning space
   // - if new arrays are bigger and can be enlarged on the place, we do it
   // - otherwise we try to allocate new place for the data in the same AttribObject
   // - if we do not succeed in the current AttribObject, we move the data to
   //   some other AttribObject
   // - if no AttribObject accommodate us, we allocate new AttribObject

   // FIXME: not implemented yet
}


void AttribObject::freeData(AttribDataReference *r)
{
   // check whether this attribObject owns given AttribDataReference
   if(r->attribObject!=this)
   {
      cerr<<"Error: calling AttribObject::freeData() on AttribDataReference\n"
            "   that is not managed by this AttribObject."<<endl;
      return;
   }

   // release vertices and indices allocations
   AllocationBlock &ab=_verticesDataAllocationMap[r->verticesDataId];
   ab.owner=NULL;
   if(r->indicesDataId!=0)
   {
      ab=_indicesDataAllocationMap[r->indicesDataId];
      ab.owner=NULL;
   }

   // update AttribDataReference
   r->attribObject=NULL;
}
