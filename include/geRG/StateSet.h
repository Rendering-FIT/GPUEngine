#ifndef GE_RG_STATE_SET_H
#define GE_RG_STATE_SET_H

#include <array>
#include <map>
#include <memory>
#include <vector>
#include <geRG/Export.h>
#include <geRG/ParentChildList.h>
#include <geGL/OpenGL.h>
#include <geCore/Command.h>

namespace ge
{
   namespace rg
   {
      class AttribStorage;


      struct GERG_EXPORT RenderingCommandData
      {
         unsigned indirectBufferOffset4;
         unsigned stateSetBufferOffset4;
         unsigned glMode;
         unsigned drawCommandCount;
         inline RenderingCommandData(unsigned indirectBufferOffset,unsigned stateSetBufferOffset4,
                                     unsigned glMode,unsigned drawCommandCount);
      };


      class GERG_EXPORT StateSet : public std::enable_shared_from_this<StateSet>
      {
      public:

         typedef ChildListTemplate<StateSet> ChildList;
         typedef ParentListTemplate<StateSet> ParentList;

         struct GERG_EXPORT AttribStorageData
         {
            AttribStorage *attribStorage;
            unsigned numDrawCommands;
            std::array<unsigned,16> numDrawCommandsOfKindAndIndex;
            std::vector<RenderingCommandData> renderingData;

            inline unsigned numDrawCommandsOfKind(unsigned mode) const  { return numDrawCommandsOfKindAndIndex[mode]&0x0fffffff; }
            inline void setNumDrawCommandsOfKind(unsigned mode,unsigned value)  { numDrawCommandsOfKindAndIndex[mode]=(numDrawCommandsOfKindAndIndex[mode]&0xf0000000)|value; }
            inline unsigned indexToRenderingData(unsigned mode) const  { return numDrawCommandsOfKindAndIndex[mode]>>28; }
            inline void setIndexToRenderingData(unsigned mode,unsigned value)  { numDrawCommandsOfKindAndIndex[mode]=(numDrawCommandsOfKindAndIndex[mode]&0x0fffffff)|(value<<28); }

            inline AttribStorageData(AttribStorage *storage);
         };

         struct GERG_EXPORT StateSetData {
            unsigned indirectBufferOffset;
         };

      protected:

         ChildList _children;
         ParentList _parents;

         unsigned _numDrawCommands;
         std::map<AttribStorage*,AttribStorageData> _attribStorageData;

         std::vector<std::shared_ptr<ge::core::Command>> _commandList;

      public:

         inline AttribStorageData* getAttribStorageData(const AttribStorage *storage) const;
         inline std::map<AttribStorage*,AttribStorageData>::iterator getOrCreateAttribStorageData(AttribStorage *storage);
         inline void releaseAttribStorageDataIfEmpty(std::map<AttribStorage*,AttribStorageData>::iterator iterator);

         inline unsigned getStateSetBufferOffset4(unsigned mode,const AttribStorage *storage) const;
         inline unsigned getStateSetBufferOffset4(unsigned mode,const AttribStorageData &storageData) const;

         inline void incrementDrawCommandModeCounter(unsigned incrementAmount,
                                                     unsigned mode,AttribStorage *storage);
         void decrementDrawCommandModeCounter(unsigned decrementAmount,
                                              unsigned mode,AttribStorage *storage);
         void incrementDrawCommandModeCounter(unsigned incrementAmount,unsigned mode,
                                              AttribStorageData &storageData);
         void decrementDrawCommandModeCounter(unsigned decrementAmount,unsigned mode,
                                              AttribStorageData &storageData);

         inline unsigned addCommand(const std::shared_ptr<ge::core::Command>& command);
         inline unsigned insertCommand(unsigned index,const std::shared_ptr<ge::core::Command>& command);
         inline void removeCommand(unsigned index);
         void removeCommand(const std::shared_ptr<ge::core::Command>& command);
         inline void clearCommands();
         inline const std::vector<std::shared_ptr<ge::core::Command>>& commandList() const;
         inline std::vector<std::shared_ptr<ge::core::Command>>& commandList();

         void setupRendering();
         void render();

      };



      inline RenderingCommandData::RenderingCommandData(unsigned indirectBufferOffset4,unsigned stateSetBufferOffset4,unsigned glMode,unsigned drawCommandCount)
      { this->indirectBufferOffset4=indirectBufferOffset4; this->stateSetBufferOffset4=stateSetBufferOffset4; this->glMode=glMode; this->drawCommandCount=drawCommandCount; }
      inline StateSet::AttribStorageData::AttribStorageData(AttribStorage *storage) : attribStorage(storage), numDrawCommands(0)  { numDrawCommandsOfKindAndIndex.fill(0); }
      inline StateSet::AttribStorageData* StateSet::getAttribStorageData(const AttribStorage *storage) const
      { auto it=_attribStorageData.find(const_cast<AttribStorage*>(storage)); return it!=_attribStorageData.end() ? const_cast<AttribStorageData*>(&it->second) : nullptr; }
      inline std::map<AttribStorage*,StateSet::AttribStorageData>::iterator StateSet::getOrCreateAttribStorageData(AttribStorage *storage)
      { return _attribStorageData.emplace(storage,storage).first; }
      inline void StateSet::releaseAttribStorageDataIfEmpty(std::map<AttribStorage*,AttribStorageData>::iterator iterator)
      { if(iterator->second.numDrawCommands==0) _attribStorageData.erase(iterator); }
      inline unsigned StateSet::getStateSetBufferOffset4(unsigned mode,const AttribStorage* storage) const
      { const StateSet::AttribStorageData *storageData=getAttribStorageData(storage); return storageData ? getStateSetBufferOffset4(mode,*storageData) : 0; }
      inline unsigned StateSet::getStateSetBufferOffset4(unsigned mode,const AttribStorageData &storageData) const
      { return storageData.renderingData[storageData.indexToRenderingData(mode&0x0f)].stateSetBufferOffset4; }
      inline void StateSet::incrementDrawCommandModeCounter(unsigned incrementAmount,unsigned mode,AttribStorage *storage)
      { if(incrementAmount!=0) incrementDrawCommandModeCounter(incrementAmount,mode,getOrCreateAttribStorageData(storage)->second); }
      inline unsigned StateSet::addCommand(const std::shared_ptr<ge::core::Command>& command)  { unsigned r=unsigned(_commandList.size()); _commandList.push_back(command); return r; }
      inline unsigned StateSet::insertCommand(unsigned index,const std::shared_ptr<ge::core::Command>& command)  { return unsigned(std::distance(_commandList.emplace(_commandList.begin()+index,command),_commandList.begin())); }
      inline void StateSet::removeCommand(unsigned index)  { _commandList.erase(_commandList.begin()+index); }
      inline void StateSet::clearCommands()  { _commandList.clear(); }
      inline const std::vector<std::shared_ptr<ge::core::Command>>& StateSet::commandList() const  { return _commandList; }
      inline std::vector<std::shared_ptr<ge::core::Command>>& StateSet::commandList()  { return _commandList; }

   }
}

#endif // GE_RG_STATE_SET_H
