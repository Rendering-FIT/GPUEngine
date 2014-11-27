#include <iostream> // for cerr
#include <geSG/AttribsManager.h>
#include <geSG/AttribsReference.h>
#include <geSG/AttribsStorage.h>

using namespace ge::sg;
using namespace std;


shared_ptr<AttribsManager> AttribsManager::_instance = make_shared<AttribsManager>();



AttribsManager::~AttribsManager()
{
}


bool AttribsManager::allocData(AttribsReference &r,const AttribsConfig& attribsConfig,
                               int numVertices,int numIndices)
{
   // get AttribsStorage or AttribsStorages with particular attribConfigID
   auto itRange=getAttribsStorages(attribsConfig);
   AttribsStorageMultiMap::iterator attribsStorageIt=_attribsStorageMultiMap.end();

   // iterate possibly empty list of AttribsStorages
   // with the required attribConfig
   // and look if there is one with enough empty space
   for(auto it=itRange.first; it!=itRange.second; it++)
   {
      if(it->second->getNumVerticesAvailableAtTheEnd()>=numVertices &&
         it->second->getNumIndicesAvailableAtTheEnd()>=numIndices)
      {
         attribsStorageIt=it;
         break;
      }
   }

   // do we have AttribsStorage?
   if(attribsStorageIt==_attribsStorageMultiMap.end())
   {
      // create a new AttribsStorage
      attribsStorageIt=_attribsStorageMultiMap.emplace_hint(itRange.first,attribsConfig,
            AttribsStorage::getFactory()->create(attribsConfig,
            _defaultStorageNumVertices,attribsConfig.ebo?_defaultStorageNumIndices:0));

      // update _id2IteratorMap for faster lookups
      if(attribsConfig.configId!=0)
         _id2IteratorMap[attribsConfig.configId].first=attribsStorageIt;
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


std::shared_ptr<AttribsStorage> AttribsManager::allocStorage(const AttribsConfig &config,
                                                             unsigned numVertices,unsigned numIndices,
                                                             bool privateFlag)
{
   // create new AttribsStorage
   shared_ptr<AttribsStorage> a = AttribsStorage::getFactory()->create(config,
         _defaultStorageNumVertices,_defaultStorageNumIndices);

   if(privateFlag)
   {
      // insert it to the "private" list
      _privateAttribsStorages.push_back(a);
   }
   else
   {
      // insert it to the multimap
      auto attribsStorageIt=_attribsStorageMultiMap.emplace(config,a);

      // update _id2IteratorMap for faster lookups
      if(config.configId!=0)
         _id2IteratorMap[config.configId].first=attribsStorageIt;
   }

   return a;
}


void AttribsManager::setInstance(std::shared_ptr<AttribsManager>& ptr)
{
   _instance = ptr;
}
