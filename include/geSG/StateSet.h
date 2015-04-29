#ifndef GE_SG_STATE_SET_H
#define GE_SG_STATE_SET_H

#include <array>
#include <map>
#include <memory>
#include <vector>
#include <geSG/Export.h>
#include <geSG/ParentChildList.h>
#include <geGL/OpenGL.h>

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

         struct RenderingData
         {
            unsigned indirectBufferOffset4;
            unsigned stateSetBufferOffset4;
            unsigned glMode;
            unsigned drawCommandCount;
            inline RenderingData(unsigned indirectBufferOffset,unsigned stateSetBufferOffset4,
                                 unsigned glMode,unsigned drawCommandCount);
         };

         struct AttribStorageData
         {
            const AttribStorage *attribStorage;
            unsigned numDrawCommands;
            std::array<unsigned,16> numDrawCommandsOfKindAndIndex;
            std::vector<RenderingData> renderingData;

            inline unsigned numDrawCommandsOfKind(unsigned mode) const  { return numDrawCommandsOfKindAndIndex[mode]&0x0fffffff; }
            inline void setNumDrawCommandsOfKind(unsigned mode,unsigned value)  { numDrawCommandsOfKindAndIndex[mode]=(numDrawCommandsOfKindAndIndex[mode]&0xf0000000)|value; }
            inline unsigned indexToRenderingData(unsigned mode) const  { return numDrawCommandsOfKindAndIndex[mode]>>28; }
            inline void setIndexToRenderingData(unsigned mode,unsigned value)  { numDrawCommandsOfKindAndIndex[mode]=(numDrawCommandsOfKindAndIndex[mode]&0x0fffffff)|(value<<28); }

            inline AttribStorageData(const AttribStorage *storage);
         };

         struct StateSetData {
            unsigned indirectBufferOffset;
         };

      protected:

         ChildList _children;
         ParentList _parents;

         unsigned _numDrawCommands;
         std::map<const AttribStorage*,AttribStorageData> _attribStorageData;

         std::vector<std::shared_ptr<ge::gl::Command>> _commandList;

      public:

         inline AttribStorageData* getAttribStorageData(const AttribStorage *storage);
         inline const AttribStorageData* getAttribStorageData(const AttribStorage *storage) const;
         inline std::map<const AttribStorage*,AttribStorageData>::iterator getOrCreateAttribStorageData(const AttribStorage *storage);
         inline void releaseAttribStorageDataIfEmpty(std::map<const AttribStorage*,AttribStorageData>::iterator iterator);

         inline unsigned getStateSetBufferOffset4(unsigned mode,const AttribStorage *storage) const;
         inline unsigned getStateSetBufferOffset4(unsigned mode,const AttribStorageData &storageData) const;

         inline void incrementDrawCommandModeCounter(unsigned incrementAmount,
                                                     unsigned mode,const AttribStorage *storage);
         void decrementDrawCommandModeCounter(unsigned decrementAmount,
                                              unsigned mode,const AttribStorage *storage);
         void incrementDrawCommandModeCounter(unsigned incrementAmount,unsigned mode,
                                              AttribStorageData &storageData);
         void decrementDrawCommandModeCounter(unsigned decrementAmount,unsigned mode,
                                              AttribStorageData &storageData);

         inline unsigned addCommand(std::shared_ptr<ge::gl::Command> command);
         inline void removeCommand(unsigned index);
         inline void removeCommand(std::shared_ptr<ge::gl::Command> command);
         inline void clearCommands();
         inline const std::vector<std::shared_ptr<ge::gl::Command>>& commandList() const;
         inline std::vector<std::shared_ptr<ge::gl::Command>>& commandList();

         void setupRendering();
         void render();

      };



      inline StateSet::RenderingData::RenderingData(unsigned indirectBufferOffset4,unsigned stateSetBufferOffset4,unsigned glMode,unsigned drawCommandCount)
      { this->indirectBufferOffset4=indirectBufferOffset4; this->stateSetBufferOffset4=stateSetBufferOffset4; this->glMode=glMode; this->drawCommandCount=drawCommandCount; }
      inline StateSet::AttribStorageData::AttribStorageData(const AttribStorage *storage) : attribStorage(storage), numDrawCommands(0)  { numDrawCommandsOfKindAndIndex.fill(0); }
      inline StateSet::AttribStorageData* StateSet::getAttribStorageData(const AttribStorage *storage)
      { auto it=_attribStorageData.find(storage); return it!=_attribStorageData.end() ? &it->second : nullptr; }
      inline const StateSet::AttribStorageData* StateSet::getAttribStorageData(const AttribStorage *storage) const
      { auto it=_attribStorageData.find(storage); return it!=_attribStorageData.end() ? &it->second : nullptr; }
      inline std::map<const AttribStorage*,StateSet::AttribStorageData>::iterator StateSet::getOrCreateAttribStorageData(const AttribStorage *storage)
      { return _attribStorageData.emplace(storage,storage).first; }
      inline void StateSet::releaseAttribStorageDataIfEmpty(std::map<const AttribStorage*,AttribStorageData>::iterator iterator)
      { if(iterator->second.numDrawCommands==0) _attribStorageData.erase(iterator); }
      inline unsigned StateSet::getStateSetBufferOffset4(unsigned mode,const AttribStorage* storage) const
      { const StateSet::AttribStorageData *storageData=getAttribStorageData(storage); return storageData ? getStateSetBufferOffset4(mode,*storageData) : 0; }
      inline unsigned StateSet::getStateSetBufferOffset4(unsigned mode,const AttribStorageData &storageData) const
      { return storageData.renderingData[storageData.indexToRenderingData(mode&0x0f)].stateSetBufferOffset4; }
      inline void StateSet::incrementDrawCommandModeCounter(unsigned incrementAmount,unsigned mode,const AttribStorage *storage)
      { if(incrementAmount!=0) incrementDrawCommandModeCounter(incrementAmount,mode,getOrCreateAttribStorageData(storage)->second); }

   }
}

#endif // GE_SG_STATE_SET_H
