#include <iostream> // for cerr
#include <geSG/AttribsManager.h>
#include <geSG/AttribsReference.h>
#include <geSG/AttribsStorage.h>

using namespace ge::sg;
using namespace std;


shared_ptr<AttribsManager> AttribsManager::_instance;



AttribsManager::~AttribsManager()
{
}


bool AttribsManager::allocData(AttribsReference &r,int numVertices,int numIndices,uint16_t attribConfigId)
{
   // get AttribsStorage or AttribsStorages with particular attribConfigID
   auto itRange=getAttribsStorages(attribConfigId);
   AttribsStorageMultiMap::iterator attribsStorageIt;
   if(itRange.first==itRange.second)
   {
      // no AttribsStorage with required attribConfigID in the map -> insert new one
      attribsStorageIt=_attribsStorageMultiMap.emplace_hint(itRange.first,attribConfigId,
            unique_ptr<AttribsStorage>(AttribsStorage::getFactory()->create()));
   }
   else
   {
      // AttribsStorage (or list of AttribsStorages) with the required attribConfigID found
      //
      // find AttribsStorage with enough empty space
      for(auto it=itRange.first; it!=itRange.second; it++)
      {
         if(it->second->getNumVerticesAvailableAtTheEnd()>=numVertices &&
            it->second->getNumIndicesAvailableAtTheEnd()>=numIndices)
         {
            attribsStorageIt=it;
            break;
         }
      }
      // not enough space in AttribsStorage(s) -> insert new one
      attribsStorageIt=_attribsStorageMultiMap.emplace_hint(itRange.first,attribConfigId,
            unique_ptr<AttribsStorage>(AttribsStorage::getFactory()->create()));
   }

   // perform allocation in the choosen AttribsStorage
   attribsStorageIt->second->allocData(r,numVertices,numIndices);
   return true;
}


/** Changes the number of allocated elements or indices.
 *
 *  Parameter r contains the reference to AttribsReference holding allocation information.
 *  numVertices and numIndices are the new number of elements in vertex and index arrays.
 *  If preserveContent parameter is true, the content of element and index data will be preserved.
 *  If new data are larger, the content over the size of previous data is undefined.
 *  If new data are smaller, only the data up to the new data size is preserved.
 *  If preserveContent is false, content of element and index data are undefined.
 */
bool AttribsManager::reallocData(AttribsReference &r,int numVertices,int numIndices,bool preserveContent)
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


void AttribsManager::freeData(AttribsReference &r)
{
   // ignore empty AttribsReferences
   if(r.attribsStorage==NULL)
      return;

   // free data
   r.attribsStorage->freeData(r);
}


void AttribsManager::uploadVertexData(AttribsReference &r,Mesh *mesh,int fromIndex,int numVertices)
{
}


int AttribsManager::uploadVertexData(AttribsReference &r,Mesh *mesh,unsigned &currentPosition,int bytesToUpload)
{
}


void AttribsManager::uploadIndicesData(AttribsReference &r,Mesh *mesh,int fromIndex,int numIndices)
{
}


int AttribsManager::uploadIndicesData(AttribsReference &r,Mesh *mesh,unsigned &currentPosition,int bytesToUpload)
{
}


void AttribsManager::setInstance(std::shared_ptr<AttribsManager>& ptr)
{
   _instance = ptr;
}
