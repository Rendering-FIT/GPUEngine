#include <iostream> // for cerr
#include <geSG/AttribManager.h>
#include <geSG/AttribReference.h>
#include <geSG/AttribStorage.h>

using namespace ge::sg;
using namespace std;


shared_ptr<AttribManager> AttribManager::_instance = make_shared<AttribManager>();



AttribManager::~AttribManager()
{
}


bool AttribManager::allocData(AttribReference &r,const AttribConfig& attribConfig,
                              int numVertices,int numIndices)
{
   // get AttribStorage or AttribStorages with particular attribConfigID
   auto itRange=getAttribStorages(attribConfig);
   AttribStorageMultiMap::iterator attribStorageIt=_attribStorageMultiMap.end();

   // iterate possibly empty list of AttribStorages
   // with the required attribConfig
   // and look if there is one with enough empty space
   for(auto it=itRange.first; it!=itRange.second; it++)
   {
      if(it->second->getNumVerticesAvailableAtTheEnd()>=numVertices &&
         it->second->getNumIndicesAvailableAtTheEnd()>=numIndices)
      {
         attribStorageIt=it;
         break;
      }
   }

   // do we have AttribStorage?
   if(attribStorageIt==_attribStorageMultiMap.end())
   {
      // create a new AttribStorage
      attribStorageIt=_attribStorageMultiMap.emplace_hint(itRange.first,attribConfig,
            AttribStorage::getFactory()->create(attribConfig,
            _defaultStorageNumVertices,attribConfig.ebo?_defaultStorageNumIndices:0));

      // update _id2IteratorMap for faster lookups
      if(attribConfig.configId!=0)
         _id2IteratorMap[attribConfig.configId].first=attribStorageIt;
   }

   // perform allocation in the choosen AttribStorage
   attribStorageIt->second->allocData(r,numVertices,numIndices);
   return true;
}


/** Changes the number of allocated elements or indices.
 *
 *  Parameter r contains the reference to AttribReference holding allocation information.
 *  numVertices and numIndices are the new number of elements in vertex and index arrays.
 *  If preserveContent parameter is true, the content of element and index data will be preserved.
 *  If new data are larger, the content over the size of previous data is undefined.
 *  If new data are smaller, only the data up to the new data size is preserved.
 *  If preserveContent is false, content of element and index data are undefined.
 */
bool AttribManager::reallocData(AttribReference &r,int numVertices,int numIndices,bool preserveContent)
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


void AttribManager::freeData(AttribReference &r)
{
   // ignore empty AttribReferences
   if(r.attribStorage==NULL)
      return;

   // free data
   r.attribStorage->freeData(r);
}


std::shared_ptr<AttribStorage> AttribManager::allocStorage(const AttribConfig &config,
                                                           unsigned numVertices,unsigned numIndices,
                                                           bool privateFlag)
{
   // create new AttribStorage
   shared_ptr<AttribStorage> a = AttribStorage::getFactory()->create(config,
         _defaultStorageNumVertices,_defaultStorageNumIndices);

   if(privateFlag)
   {
      // insert it to the "private" list
      _privateAttribStorages.push_back(a);
   }
   else
   {
      // insert it to the multimap
      auto attribStorageIt=_attribStorageMultiMap.emplace(config,a);

      // update _id2IteratorMap for faster lookups
      if(config.configId!=0)
         _id2IteratorMap[config.configId].first=attribStorageIt;
   }

   return a;
}


void AttribManager::setInstance(std::shared_ptr<AttribManager>& ptr)
{
   _instance = ptr;
}
