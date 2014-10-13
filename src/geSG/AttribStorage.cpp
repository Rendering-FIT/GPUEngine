#include <iostream> // for cerr
#include <geSG/AttribStorage.h>
#include <geSG/AttribDataReference.h>
#include <geSG/AttribObject.h>

using namespace ge::sg;
using namespace std;


bool AttribStorage::allocData(AttribDataReference *r,int numVertices,int numIndices,uint16_t attribConfigId)
{
   // get AttribStorage or AttribStorages with particular attribConfigID
   auto itRange=getAttribObjects(attribConfigId);
   AttribObjectMultiMap::iterator attribObjectIt;
   if(itRange.first==itRange.second)
   {
      // no AttribStorage with required attribConfigID in the map -> insert new one
      attribObjectIt=_attribObjectMultiMap.emplace_hint(itRange.first,attribConfigId,
            unique_ptr<AttribObject>(AttribObject::getFactory()->create()));
   }
   else
   {
      // AttribStorage (or list of AttribStorages) with the required attribConfigID found
      //
      // find AttribStorage with enough empty space
      for(auto it=itRange.first; it!=itRange.second; it++)
      {
         if(it->second->getNumVerticesAvailableAtTheEnd()>=numVertices &&
            it->second->getNumIndicesAvailableAtTheEnd()>=numIndices)
         {
            attribObjectIt=it;
            break;
         }
      }
      // not enough space in AttribStorage(s) -> insert new one
      attribObjectIt=_attribObjectMultiMap.emplace_hint(itRange.first,attribConfigId,
            unique_ptr<AttribObject>(AttribObject::getFactory()->create()));
   }

   // perform allocation in choosen AttribObject
   attribObjectIt->second->allocData(r,numVertices,numIndices);
   return true;
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
bool AttribStorage::reallocData(AttribDataReference *r,int numVertices,int numIndices,bool preserveContent)
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


void AttribStorage::freeData(AttribDataReference *r)
{
   // ignore empty AttribDataReferences
   if(r->attribObject==NULL)
      return;

   // free data
   r->attribObject->freeData(r);
}


void AttribStorage::setInstance(std::shared_ptr<AttribStorage>& ptr)
{
   _instance = ptr;
}
