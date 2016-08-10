#include <algorithm>
#include <geRG/StateSet.h>
#include <geRG/RenderingContext.h>
#if _MSC_VER<1900
# include <cstdlib>
#endif

using namespace ge::rg;

static_assert(sizeof(StateSetGpuData)==4,
              "StateSet::StateSetData size is not 4 bytes.\n"
              "If it is ok, check related code and consider rewising this assert.");



#if defined(_MSC_VER) && _MSC_VER<=1900
// MSVC 2013 (tested with Update 4 and 5) and MSVC 2015 (original release)
// fails to embed this class into the std::vector
// unless there is a copy constructor (this does not meet C++11 standard)
// MSVC 2015 (original release) requires assignment operator as well.
RenderingCommandData::RenderingCommandData(const RenderingCommandData&) // this must be never called
{
   std::cout<<"RenderingCommandData copy constructor fatal error: this constructor should be\n"
              "   never called. Application will be terminated."<<std::endl;
   exit(-1);
}
RenderingCommandData& RenderingCommandData::operator=(const RenderingCommandData&) // this must be never called
{
   std::cout << "RenderingCommandData assigment operator fatal error: this operator should be\n"
                "   never called. Application will be terminated." << std::endl;
   exit(-1);
}
#endif


RenderingCommandData& RenderingCommandData::operator=(RenderingCommandData&& rhs)
{
   indirectBufferOffset4=rhs.indirectBufferOffset4;
   glMode=rhs.glMode;
   drawCommandCount=rhs.drawCommandCount;

   auto sss=RenderingContext::current()->stateSetStorage();
   stateSetBufferOffset4=rhs.stateSetBufferOffset4;
   sss->operator[](rhs.stateSetBufferOffset4)=&stateSetBufferOffset4;
   rhs.stateSetBufferOffset4=0;

   return *this;
}


void StateSet::incrementDrawCommandModeCounter(unsigned incrementAmount,unsigned mode,
                                               AttribStorageData &storageData)
{
   // increment internal StateSet counters
   // and allocate RenderingData and StateSet buffer data on the first appearance of a given primitive kind
   _numDrawCommands+=incrementAmount;
   storageData.numDrawCommands+=incrementAmount;
   unsigned glMode=mode&0x0f;
   unsigned num=storageData.numDrawCommandsOfKind(glMode);
   unsigned newNum=num+incrementAmount;
   storageData.setNumDrawCommandsOfKind(glMode,newNum);

   if(num==0)
   {
      // allocate StateSet buffer data
      // and create RenderingData
      storageData.setIndexToRenderingData(glMode,unsigned(storageData.renderingData.size()));
      storageData.renderingData.emplace_back(0,glMode,newNum);
      RenderingContext::current()->stateSetStorage()->alloc(&storageData.renderingData.back().stateSetBufferOffset4);
   }
   else
   {
      // update draw command counter
      storageData.renderingData[storageData.indexToRenderingData(glMode)].drawCommandCount=newNum;
   }
}


void StateSet::decrementDrawCommandModeCounter(unsigned decrementAmount,unsigned mode,
                                               AttribStorageData &storageData)
{
   // decrement internal StateSetCounters
   // and free StateSet buffer data on the removal of the last primitive of a particular kind
   _numDrawCommands-=decrementAmount;
   storageData.numDrawCommands-=decrementAmount;
   unsigned glMode=mode&0x0f;
   unsigned num=storageData.numDrawCommandsOfKind(glMode);
   num-=decrementAmount;

   if(num!=0)
   {
      // update draw command counter
      storageData.setNumDrawCommandsOfKind(glMode,num);
      storageData.renderingData[storageData.indexToRenderingData(glMode)].drawCommandCount=num;
   }
   else
   {
      // release StateSet buffer data
      // and delete RenderingData
      unsigned index=storageData.indexToRenderingData(glMode);
      storageData.numDrawCommandsOfKindAndIndex[glMode]=0;
      RenderingContext::current()->stateSetStorage()->free(storageData.renderingData[index].stateSetBufferOffset4);

      unsigned lastIndex=unsigned(storageData.renderingData.size())-1;
      if(index<lastIndex)
      {
         storageData.setIndexToRenderingData(storageData.renderingData[lastIndex].glMode,index);
         storageData.renderingData[index]=std::move(storageData.renderingData[lastIndex]);
      }
      storageData.renderingData.pop_back();
   }
}


void StateSet::decrementDrawCommandModeCounter(unsigned decrementAmount,unsigned mode,AttribStorage *storage)
{
   auto storageDataIterator=getOrCreateAttribStorageData(storage);
   decrementDrawCommandModeCounter(decrementAmount,mode,storageDataIterator->second);
   releaseAttribStorageDataIfEmpty(storageDataIterator);
}


void StateSet::removeCommand(const std::shared_ptr<ge::core::Command>& command)
{
   auto it=std::find(_commandList.begin(),_commandList.end(),command);
   if(it!=_commandList.end())
      _commandList.erase(it);
}


/** The method updates internal data structures and buffers and
 *  makes them ready for indirect rendering.
 *
 *  The method requires RenderingContext::stateSetStorage() buffer to
 *  be mapped for writing.
 */
void StateSet::setupRendering()
{
   // process StateSet once per frame (even if it is visited by multiple paths)
   RenderingContext *rc=RenderingContext::current().get();
   if(rc->progressStamp()==_progressStamp)
      return;
   _progressStamp=rc->progressStamp();

   // initialize variables
   unsigned indirectBufferOffset4=rc->bufferPosition();
   unsigned *stateSetBufferPtr=reinterpret_cast<unsigned*>(rc->stateSetStorage()->ptr());

   // iterate through all AttribStorageData
   for(auto it1=_attribStorageData.begin(); it1!=_attribStorageData.end(); it1++)
   {
      // skip empty AttribStorages
      if(it1->second.numDrawCommands==0)
         continue;

      // size of increment differs for DrawElements and DrawArrays (EBO in use or not)
      // and it is given as index to unsigned array (to be usable directly as index in shader),
      // thus it is not 20 and 16, but 5 and 4
      unsigned increment=it1->second.attribStorage->attribConfig()->configData().ebo?5:4;

      // iterate through all RenderingData
      for(auto it2=it1->second.renderingData.begin(),e=it1->second.renderingData.end(); it2!=e; it2++)
      {
         // reserve the space in the indirect buffer for the draw calls
         // (this is done by seting indrectBufferOffset4 if StateSetBuffer and StateSet::RenderingData)
         stateSetBufferPtr[it2->stateSetBufferOffset4]=indirectBufferOffset4;
         it2->indirectBufferOffset4=indirectBufferOffset4;
         indirectBufferOffset4+=increment*it2->drawCommandCount;
      }
   }

   // update bufferPosition variable
   rc->setBufferPosition(indirectBufferOffset4);

   // process child StateSets
   for(auto& child : _childList)
      child->setupRendering();
}


void StateSet::render()
{
   if(_commandList.empty())
   {
      // if command list is empty, execute default render command
      StateSet::RenderCommand::execute(this);
   }
   else
   {
      // process command list
      for(auto& it : _commandList)
         it->operator()();
   }
}


void StateSet::RenderCommand::execute(StateSet *stateSet)
{
   // render all attached geometry
   for(auto& i : stateSet->_attribStorageData)
      if(i.second.numDrawCommands!=0)
         i.second.attribStorage->render(i.second.renderingData);

   // render all child StateSets
   for(auto& child : stateSet->_childList)
      child->render();
}


void StateSet::RenderCommand::operator()()
{
   execute(_stateSet);
}
