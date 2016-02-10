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


      struct StateSetGpuData {
         unsigned drawIndirectBufferOffset;
      };


      struct GERG_EXPORT RenderingCommandData
      {
         unsigned indirectBufferOffset4;
         unsigned stateSetBufferOffset4;
         unsigned glMode;
         unsigned drawCommandCount;

#if _MSC_VER<=1900
         // MSVC 2013 (tested with Update 4 and 5) and MSVC 2015 (original release)
         // fails to embed this class into the std::vector
         // unless there is a copy constructor (this does not meet C++11 standard)
         // MSVC 2015 (original release) requires even assignment operator.
         RenderingCommandData(const RenderingCommandData&); // this must be never called
         RenderingCommandData& operator=(const RenderingCommandData&); // this must be never called
#else
         RenderingCommandData(const RenderingCommandData&) = delete;
#endif
         inline RenderingCommandData(RenderingCommandData&& rhs) { *this = std::move(rhs); }
         RenderingCommandData& operator=(RenderingCommandData&& rhs);

         inline RenderingCommandData() = default;
         inline RenderingCommandData(unsigned indirectBufferOffset4,
                                     unsigned glMode,unsigned drawCommandCount);
      };


      class GERG_EXPORT StateSet : public std::enable_shared_from_this<StateSet>
      {
      public:

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

         GERG_CHILD_LIST(std::shared_ptr<StateSet>,StateSet*)
         GERG_PARENT_LIST(StateSet*,std::shared_ptr<StateSet>)

      protected:

         unsigned _numDrawCommands;
         unsigned _drawableCounter;        ///< Number of Drawables referencing this StateSet. As long as the counter is non-zero, StateSet is prevented from being freed from memory. \sa _self
         std::shared_ptr<StateSet> _self;  ///< Reference to itself. It is used by _drawableCounter to prevent the object from being deleted as long as any drawables still reference it.

         std::map<AttribStorage*,AttribStorageData> _attribStorageData;
         std::vector<std::shared_ptr<ge::core::Command>> _commandList;

      public:

         inline StateSet();

         inline AttribStorageData* getAttribStorageData(const AttribStorage *storage) const;
         inline std::map<AttribStorage*,AttribStorageData>::iterator getOrCreateAttribStorageData(AttribStorage *storage);
         inline void releaseAttribStorageDataIfEmpty(std::map<AttribStorage*,AttribStorageData>::iterator iterator);
         inline const std::map<AttribStorage*,AttribStorageData>& getAttribStorageDataMap() const;

         inline unsigned getStateSetBufferOffset4(unsigned mode,const AttribStorage *storage) const;
         inline unsigned getStateSetBufferOffset4(unsigned mode,const AttribStorageData &storageData) const;

         inline void incrementDrawableCount();
         inline void decrementDrawableCount();
         inline unsigned drawableCount() const;

         inline void incrementDrawCommandModeCounter(unsigned incrementAmount,
                                                     unsigned mode,AttribStorage *storage);
         void decrementDrawCommandModeCounter(unsigned decrementAmount,
                                              unsigned mode,AttribStorage *storage);
         void incrementDrawCommandModeCounter(unsigned incrementAmount,unsigned mode,
                                              AttribStorageData &storageData);
         void decrementDrawCommandModeCounter(unsigned decrementAmount,unsigned mode,
                                              AttribStorageData &storageData);

         void setupRendering();
         void render();

         inline unsigned addCommand(const std::shared_ptr<ge::core::Command>& command);
         inline unsigned addRenderCommand();
         inline unsigned insertCommand(unsigned index,const std::shared_ptr<ge::core::Command>& command);
         inline void removeCommand(unsigned index);
         void removeCommand(const std::shared_ptr<ge::core::Command>& command);
         inline void clearCommands();
         inline const std::vector<std::shared_ptr<ge::core::Command>>& commandList() const;
         inline std::vector<std::shared_ptr<ge::core::Command>>& commandList();


         class GERG_EXPORT RenderCommand : public ge::core::Command {
         protected:
            StateSet *_stateSet; // not shared_ptr to avoid circular reference
         public:

            static void execute(StateSet *stateSet);
            static inline std::shared_ptr<RenderCommand> create(StateSet *owner);

            inline RenderCommand();
            inline RenderCommand(StateSet *owner);
            virtual void operator()();

            inline StateSet* stateSet() const;
            inline void setStateSet(StateSet *owner);

         };

      };

   }
}



// inline methods

namespace ge
{
   namespace rg
   {
      inline RenderingCommandData::RenderingCommandData(unsigned indirectBufferOffset4,
            unsigned glMode,unsigned drawCommandCount)
      { this->indirectBufferOffset4=indirectBufferOffset4; this->glMode=glMode; this->drawCommandCount=drawCommandCount; }
      inline StateSet::AttribStorageData::AttribStorageData(AttribStorage *storage) : attribStorage(storage), numDrawCommands(0)  { numDrawCommandsOfKindAndIndex.fill(0); }

      inline StateSet::StateSet() : _numDrawCommands(0), _drawableCounter(0) {}
      inline StateSet::AttribStorageData* StateSet::getAttribStorageData(const AttribStorage *storage) const
      { auto it=_attribStorageData.find(const_cast<AttribStorage*>(storage)); return it!=_attribStorageData.end() ? const_cast<AttribStorageData*>(&it->second) : nullptr; }
      inline std::map<AttribStorage*,StateSet::AttribStorageData>::iterator StateSet::getOrCreateAttribStorageData(AttribStorage *storage)
      { return _attribStorageData.emplace(storage,storage).first; }
      inline void StateSet::releaseAttribStorageDataIfEmpty(std::map<AttribStorage*,AttribStorageData>::iterator iterator)
      { if(iterator->second.numDrawCommands==0) _attribStorageData.erase(iterator); }
      inline const std::map<AttribStorage*,StateSet::AttribStorageData>& StateSet::getAttribStorageDataMap() const  { return _attribStorageData; }
      inline unsigned StateSet::getStateSetBufferOffset4(unsigned mode,const AttribStorage* storage) const
      { const StateSet::AttribStorageData *storageData=getAttribStorageData(storage); return storageData ? getStateSetBufferOffset4(mode,*storageData) : 0; }
      inline unsigned StateSet::getStateSetBufferOffset4(unsigned mode,const AttribStorageData &storageData) const
      { return storageData.renderingData[storageData.indexToRenderingData(mode&0x0f)].stateSetBufferOffset4; }
      inline void StateSet::incrementDrawableCount()  { if(++_drawableCounter==1) _self=shared_from_this(); }
      inline void StateSet::decrementDrawableCount()  { if(--_drawableCounter==0) _self.reset(); }
      inline unsigned StateSet::drawableCount() const  { return _drawableCounter; }
      inline void StateSet::incrementDrawCommandModeCounter(unsigned incrementAmount,unsigned mode,AttribStorage *storage)
      { if(incrementAmount!=0) incrementDrawCommandModeCounter(incrementAmount,mode,getOrCreateAttribStorageData(storage)->second); }

      inline unsigned StateSet::addCommand(const std::shared_ptr<ge::core::Command>& command)  { unsigned r=unsigned(_commandList.size()); _commandList.push_back(command); return r; }
      inline unsigned StateSet::addRenderCommand()  { return addCommand(RenderCommand::create(this)); }
      inline unsigned StateSet::insertCommand(unsigned index,const std::shared_ptr<ge::core::Command>& command)  { return unsigned(std::distance(_commandList.emplace(_commandList.begin()+index,command),_commandList.begin())); }
      inline void StateSet::removeCommand(unsigned index)  { _commandList.erase(_commandList.begin()+index); }
      inline void StateSet::clearCommands()  { _commandList.clear(); }
      inline const std::vector<std::shared_ptr<ge::core::Command>>& StateSet::commandList() const  { return _commandList; }
      inline std::vector<std::shared_ptr<ge::core::Command>>& StateSet::commandList()  { return _commandList; }

      inline std::shared_ptr<StateSet::RenderCommand> StateSet::RenderCommand::create(StateSet *owner)  { return std::make_shared<StateSet::RenderCommand>(owner); }
      inline StateSet::RenderCommand::RenderCommand() : _stateSet(nullptr)  {}
      inline StateSet::RenderCommand::RenderCommand(StateSet *owner) : _stateSet(owner)  {}
      inline StateSet* StateSet::RenderCommand::stateSet() const  { return _stateSet; }
      inline void StateSet::RenderCommand::setStateSet(StateSet *owner)  { _stateSet=owner; }

   }
}

#endif // GE_RG_STATE_SET_H
