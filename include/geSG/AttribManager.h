// some includes need to be placed before GE_SG_ATTRIBS_MANAGER_H define
// to prevent problems of circular includes
#include <geSG/AttribConfig.h>

#ifndef GE_SG_ATTRIBS_MANAGER_H
#define GE_SG_ATTRIBS_MANAGER_H

#include <memory>
#include <set>
#include <geSG/Export.h>

namespace ge
{
   namespace sg
   {
      class Array;
      class AttribReference;
      class AttribStorage;


      class GE_EXPORT AttribManager {
      public:

         typedef AttribConfig::AttribConfigList AttribConfigList;

      protected:

         AttribConfigList _attribConfigList;

      public:

         inline AttribManager();
         virtual ~AttribManager();

         inline const AttribConfigList& getAttribConfigList();
         virtual AttribConfigRef getAttribConfig(const AttribConfig::ConfigData &config);
         inline AttribConfigRef getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo);
         inline AttribConfigRef getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,
                                                AttribConfigId id);
         void removeAttribConfig(AttribConfigList::iterator it);

#if 0
         static inline void uploadVertexData(AttribReference &r,const std::vector<Array>& attribs,
                                             int fromIndex=0,int numVertices=-1);
         static inline void uploadIndices(AttribReference &r,const Array& indices,
                                          int fromIndex=0,int numIndices=-1);

         virtual std::shared_ptr<AttribStorage> allocStorage(const AttribConfig &config,
                                                             unsigned numVertices,unsigned numIndices,
                                                             bool privateFlag);
#endif

         static inline std::shared_ptr<AttribManager>& instance();
         static void setInstance(std::shared_ptr<AttribManager>& ptr);

      protected:
         static std::shared_ptr<AttribManager> _instance;
      };

   }
}



// inline methods
//
// note: they need their own includes that can not be placed on the beginning of this file
//       as there is a circular include reference and the classes need to be defined before
//       inline methods to avoid incomplete type compiler error

#include <geSG/AttribReference.h>

namespace ge
{
   namespace sg
   {
      inline AttribManager::AttribManager()  {}
      inline const AttribManager::AttribConfigList& AttribManager::getAttribConfigList()  { return _attribConfigList; }
      inline AttribConfigRef AttribManager::getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo)
      { return getAttribConfig(attribTypes,ebo,AttribConfig::getId(attribTypes,ebo)); }
      inline AttribConfigRef AttribManager::getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,AttribConfigId id)
      { return getAttribConfig(AttribConfig::ConfigData(attribTypes,ebo,id)); }
      /*inline void AttribManager::uploadVertexData(AttribReference &r,
                                                  const std::vector<Array>& attribs,
                                                  int fromIndex,int numVertices)
      {
         if(r.attribStorage)
            r.attribStorage->uploadVertexData(r,attribs,fromIndex,numVertices);
      }
      inline void AttribManager::uploadIndices(AttribReference &r,const Array& indices,
                                               int fromIndex,int numIndices)
      {
         if(r.attribStorage)
            r.attribStorage->uploadIndices(r,indices,fromIndex,numIndices);
      }*/
      inline std::shared_ptr<AttribManager>& AttribManager::instance()
      { return _instance; }

   }
}

#endif // GE_SG_ATTRIBS_MANAGER_H
