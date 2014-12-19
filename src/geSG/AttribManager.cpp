#include <iostream> // for cerr
#include <geSG/AttribManager.h>
#include <geSG/AttribReference.h>
#include <geSG/AttribStorage.h>

using namespace ge::sg;
using namespace std;


shared_ptr<AttribManager> AttribManager::_instance = make_shared<AttribManager>();



AttribManager::~AttribManager()
{
   for(AttribConfigList::iterator it=_attribConfigList.begin(),nextIt; it!=_attribConfigList.end(); it=nextIt)
   {
      nextIt=it;
      nextIt++;
      if(it->second)
         it->second->deleteAllAttribStorages();
   }
}


AttribConfigRef AttribManager::getAttribConfig(const AttribConfig::ConfigData &config)
{
   // find AttribConfig in _attribConfigList (std::map)
   auto r=_attribConfigList.emplace(config,nullptr);

   // if found, return reference to it
   if(r.second==false)
      return r.first->second->createReference();

   // otherwise create new AttribConfig, put it in _attribConfigList and return reference
   AttribConfig *ac=AttribConfig::getFactory()->create(config,this,r.first);
   r.first->second=ac;
   return ac->createReference();
}


void AttribManager::removeAttribConfig(AttribConfigList::iterator it)
{
   if(it->second!=NULL)
      it->second->detachFromAttribManager();
   _attribConfigList.erase(it);
}


#if 0
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
#endif


void AttribManager::setInstance(std::shared_ptr<AttribManager>& ptr)
{
   _instance = ptr;
}
