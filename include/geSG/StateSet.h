#ifndef GE_SG_STATE_SET_H
#define GE_SG_STATE_SET_H

#include <array>
#include <map>
#include <memory>
#include <geSG/Export.h>
#include <geSG/ParentChildList.h>

namespace ge
{
   namespace sg
   {
      class AttribStorage;


      class GESG_EXPORT StateSet : public std::enable_shared_from_this<StateSet>
      {
      public:

         typedef ChildListTemplate<StateSet> ChildList;
         typedef ParentListTemplate<StateSet> ParentList;

         struct AttribStorageData
         {
            unsigned _numPrimitives;
            std::array<unsigned,32> _numPrimitivesOfKind;
            std::array<unsigned,32> _stateSetBufferIndex;
            inline AttribStorageData();
         };

         struct StateSetData {
            unsigned indirectBufferOffset;
            unsigned atomicCounterOffset;
         };

      protected:

         ChildList _children;
         ParentList _parents;

         unsigned _numPrimitives;
         std::map<const AttribStorage*,AttribStorageData> _attribStorageData;

         //uniforms

      public:

         inline AttribStorageData* getAttribStorageData(const AttribStorage *storage);
         inline const AttribStorageData* getAttribStorageData(const AttribStorage *storage) const;
         inline std::map<const AttribStorage*,AttribStorageData>::iterator getOrCreateAttribStorageData(const AttribStorage *storage);
         inline void releaseAttribStorageDataIfEmpty(std::map<const AttribStorage*,AttribStorageData>::iterator iterator);
         inline unsigned getStateSetBufferIndex(uint16_t mode,const AttribStorage *storage) const;
         inline unsigned getStateSetBufferIndex(uint16_t mode,const AttribStorageData &storageData) const;
         inline void incrementDrawCommandModeCounter(unsigned incrementAmount,
                                                     uint16_t mode,const AttribStorage *storage);
         void decrementDrawCommandModeCounter(unsigned decrementAmount,
                                              uint16_t mode,const AttribStorage *storage);
         void incrementDrawCommandModeCounter(unsigned incrementAmount,uint16_t mode,
                                              AttribStorageData &storageData);
         void decrementDrawCommandModeCounter(unsigned decrementAmount,uint16_t mode,
                                              AttribStorageData &storageData);

      };



      inline StateSet::AttribStorageData::AttribStorageData() : _numPrimitives(0)  { _numPrimitivesOfKind.fill(0); }
      inline StateSet::AttribStorageData* StateSet::getAttribStorageData(const AttribStorage *storage)
      { auto it=_attribStorageData.find(storage); return it!=_attribStorageData.end() ? &it->second : nullptr; }
      inline const StateSet::AttribStorageData* StateSet::getAttribStorageData(const AttribStorage *storage) const
      { auto it=_attribStorageData.find(storage); return it!=_attribStorageData.end() ? &it->second : nullptr; }
      inline std::map<const AttribStorage*,StateSet::AttribStorageData>::iterator StateSet::getOrCreateAttribStorageData(const AttribStorage *storage)
      { return _attribStorageData.emplace(std::piecewise_construct,std::forward_as_tuple(storage),std::forward_as_tuple()).first; }
      inline void StateSet::releaseAttribStorageDataIfEmpty(std::map<const AttribStorage*,AttribStorageData>::iterator iterator)
      { if(iterator->second._numPrimitives==0) _attribStorageData.erase(iterator); }
      inline unsigned StateSet::getStateSetBufferIndex(uint16_t mode,const AttribStorage* storage) const
      { const StateSet::AttribStorageData *storageData=getAttribStorageData(storage); return storageData ? getStateSetBufferIndex(mode,*storageData) : 0; }
      inline unsigned StateSet::getStateSetBufferIndex(uint16_t mode,const AttribStorageData &storageData) const
      { return storageData._stateSetBufferIndex[mode]; }
      inline void StateSet::incrementDrawCommandModeCounter(unsigned incrementAmount,uint16_t mode,const AttribStorage *storage)
      { if(incrementAmount!=0) incrementDrawCommandModeCounter(incrementAmount,mode,getOrCreateAttribStorageData(storage)->second); }

   }
}

#endif // GE_SG_STATE_SET_H
