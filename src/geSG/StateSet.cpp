#include <GL/glew.h>
#include <geSG/StateSet.h>
#include <geSG/RenderingContext.h>

using namespace ge::sg;

static_assert(sizeof(StateSet::StateSetData)==4,
              "StateSet::StateSetData size is not 4 bytes.\n"
              "If it is ok, check related code and consider rewising this assert.");



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
      storageData.setIndexToRenderingData(glMode,storageData.renderingData.size());
      unsigned stateSetBufferIndex=RenderingContext::current()->allocStateSetBufferItem();
      storageData.renderingData.emplace_back(0,stateSetBufferIndex*sizeof(StateSetData)/4,glMode,newNum);
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
      RenderingContext::current()->freeStateSetBufferItem(
            storageData.renderingData[index].stateSetBufferOffset4*4/sizeof(StateSetData));

      unsigned lastIndex=storageData.renderingData.size()-1;
      if(index<lastIndex)
      {
         storageData.setIndexToRenderingData(storageData.renderingData[lastIndex].glMode,index);
         storageData.renderingData[index]=storageData.renderingData[lastIndex];
      }
      storageData.renderingData.pop_back();
   }
}


void StateSet::decrementDrawCommandModeCounter(unsigned decrementAmount,unsigned mode,const AttribStorage *storage)
{
   auto storageDataIterator=getOrCreateAttribStorageData(storage);
   decrementDrawCommandModeCounter(decrementAmount,mode,storageDataIterator->second);
   releaseAttribStorageDataIfEmpty(storageDataIterator);
}


void StateSet::setupRendering()
{
   unsigned indirectBufferOffset4=RenderingContext::current()->getPositionInIndirectBuffer4();
   unsigned *stateSetMappedBufferPtr=static_cast<unsigned*>(RenderingContext::current()->mappedStateSetBufferPtr());

   // iterate through all AttribStorageData
   for(auto it1=_attribStorageData.begin(); it1!=_attribStorageData.end(); it1++)
   {
      // there might be empty AttribStorageData
      if(it1->second.numDrawCommands==0)
         continue;

      // size of increment differs for DrawElements and DrawArrays (EBO in use or not)
      // and it is given as index to unsigned array (to be usable directly as index in shader),
      // thus it is not 20 and 16, but 5 and 4
      unsigned increment=it1->second.attribStorage->getAttribConfig()->getConfigData().ebo?5:4;

      // iterate through all RenderingData
      for(auto it2=it1->second.renderingData.begin(),e=it1->second.renderingData.end(); it2!=e; it2++)
      {
         // reserve the space in the indirect buffer for the draw calls
         // (this is done by seting indrectBufferOffset4 if StateSetBuffer and StateSet::RenderingData)
         stateSetMappedBufferPtr[it2->stateSetBufferOffset4]=indirectBufferOffset4;
         it2->indirectBufferOffset4=indirectBufferOffset4;
         indirectBufferOffset4+=increment*it2->drawCommandCount;
      }
   }

   RenderingContext::current()->setPositionInIndirectBuffer4(indirectBufferOffset4);
}


void StateSet::render()
{
   for(auto it1=_attribStorageData.begin(); it1!=_attribStorageData.end(); it1++)
   {
      if(it1->second.numDrawCommands==0)
         continue;

      it1->second.attribStorage->bind();
      if(it1->second.attribStorage->getAttribConfig()->getConfigData().ebo)
         for(auto it2=it1->second.renderingData.begin(),e=it1->second.renderingData.end(); it2!=e; it2++)
         {
            GLintptr offset=it2->indirectBufferOffset4*4;
            glMultiDrawElementsIndirect(it2->glMode,GL_UNSIGNED_INT,(const void*)offset,it2->drawCommandCount,0);
         }
      else
         for(auto it2=it1->second.renderingData.begin(),e=it1->second.renderingData.end(); it2!=e; it2++)
         {
            GLintptr offset=it2->indirectBufferOffset4*4;
            glMultiDrawArraysIndirect(it2->glMode,(const void*)offset,it2->drawCommandCount,0);
         }
   }
}
