#ifndef GE_SG_ATTRIB_REFERENCE_H
#define GE_SG_ATTRIB_REFERENCE_H

#include <geSG/Export.h>
#include <geSG/FlexibleArrayList.h>
#include <vector>
#include <cstdint>

namespace ge
{
   namespace sg
   {
      class Array;
      class AttribConfigRef;
      class AttribStorage;
      class StateSet;


      class GE_EXPORT AttribReference {
      public:

         typedef FlexibleArray<unsigned,ListItemBase> InstanceGroup;
         typedef FlexibleArrayList<InstanceGroup> InstanceGroupList;
         typedef InstanceGroupList::iterator InstanceGroupId;

         /** DrawCommandControlData carries offset and mode of particular draw command.
          *
          *  Offset is given in multiple of 4 (shaders access memory as int array,
          *  thus index is memory address divided by four). Real memory offset is
          *  computed as offset4()*4.
          *
          *  Mode is OpenGL mode, such as GL_TRIANGLES, GL_PATCH, GL_LINE_STRIP. The upmost
          *  bit is used to distinguish between glDrawArrays and glDrawElements draw commands,
          *  e.g. whether EBO is used or not.
          *
          *  Implementation note: The structure provides setters and getters as we want to
          *  make sure the structure occupies only 4 bytes. (Bit fields are known to not be
          *  always tightly packed on MSVC.)
          */
         struct DrawCommandControlData {
         protected:
            uint32_t data;
         public:
            inline uint32_t offset4() const  { return data&0x07ffffff; } // return lowest 27 bits
            inline uint16_t mode() const     { return data>>27; } // return upmost 5 bits
            inline void setOffset4(uint32_t value)  { data=(data&0xf8000000)|value; } // set lowest 27 bits, value must fit to 27 bits
            inline void setMode(uint16_t value)     { data=(data&0x07ffffff)|(uint32_t(value)<<27); } // set upmost 5 bits
            inline void set(uint32_t offset4,uint16_t mode)  { data=offset4|(uint32_t(mode)<<27); } // set data, offset4 must fit to 27 bits

            inline DrawCommandControlData() {}
            inline DrawCommandControlData(uint32_t offset4,uint16_t mode);
         };

         AttribStorage *attribStorage;
         unsigned verticesDataId;
         unsigned indicesDataId;
         unsigned drawCommandBlockId;
         std::vector<DrawCommandControlData> drawCommandControlData;
         InstanceGroupList instances;

         inline AttribReference();
         inline AttribReference(AttribReference&& ref);
         inline AttribReference& operator=(AttribReference&& rhs);
         inline ~AttribReference();

         AttribReference(const AttribReference&) = delete;
         AttribReference& operator=(const AttribReference&) = delete;

         inline bool valid() const;

         inline void allocData(const AttribConfigRef& config,int numVertices,
                               int numIndices,int drawCommandBlockSize);
         inline void reallocData(int numVertices,int numIndices,
                                 int numDrawCommands,bool preserveContent=true);
         inline void freeData();

         inline int getNumVertices() const;
         inline int getNumIndices() const;
         inline int getDrawCommandBlockSize() const;

         inline void uploadVertices(const std::vector<Array>& attribs,
                                    int fromIndex=0,int numVertices=-1);
         inline void uploadIndices(const Array& indices,int fromIndex=0,int numIndices=-1);

         inline void setDrawCommands(const void *drawCommandBuffer,unsigned bytesToCopy,
                                     const unsigned *offsets4,int numDrawCommands);
         inline void setDrawCommandsOptimized(void *drawCommandBuffer,unsigned bytesToCopy,
                                              const unsigned *offsets4,int numDrawCommands);
         inline void setDrawCommandsOptimized(void *drawCommandBuffer,unsigned bytesToCopy,
                                              const DrawCommandControlData *data,
                                              int numDrawCommands);
         inline static std::vector<DrawCommandControlData> generateDrawCommandControlData(
                                              const void *drawCommandBuffer,
                                              const unsigned *offsets4,int numDrawCommands);
         inline void prepareDrawCommandsBufferData(void *drawCommandBuffer,
                                                   const DrawCommandControlData *data,
                                                   int numDrawCommands);
         inline void uploadDrawCommandBufferData(const void *drawCommandBuffer,
                                                 unsigned bytesToCopy,unsigned dstOffset=0);
         inline void updateDrawCommandControlData(const DrawCommandControlData *data,
                                                  int numDrawCommands,unsigned startIndex=0,
                                                  bool truncate=true);
         inline void clearDrawCommands();
         inline void setNumDrawCommands(unsigned num);

         inline InstanceGroupId createInstances(unsigned matrixIndex,StateSet *stateSet);
         inline InstanceGroupId createInstances(const unsigned *drawCommandIndices,
                                                const unsigned drawCommandsCount,
                                                unsigned matrixIndex,StateSet *stateSet);
         inline void deleteInstances(InstanceGroupId id);
      };

   }
}



// inline methods
//
// note: they need their own includes that can not be placed on the beginning of this file
//       as there are circular header includes and the classes need to be defined before
//       inline methods to avoid incomplete type compiler error

#include <geSG/AttribStorage.h>
#include <geSG/RenderingContext.h>

namespace ge
{
   namespace sg
   {
      inline AttribReference::DrawCommandControlData::DrawCommandControlData(uint32_t offset4,uint16_t mode)  { set(offset4,mode); }
      inline AttribReference::AttribReference() : attribStorage(NULL)  {}
      inline AttribReference::AttribReference(AttribReference&& ref)
         : attribStorage(ref.attribStorage)
         , verticesDataId(ref.verticesDataId)
         , indicesDataId(ref.indicesDataId)
         , drawCommandBlockId(ref.drawCommandBlockId)
         , drawCommandControlData(std::move(ref.drawCommandControlData))
         , instances(std::move(ref.instances))
      {
         ref.attribStorage=NULL;
      }
      inline AttribReference& AttribReference::operator=(AttribReference&& rhs)
      {
         attribStorage=rhs.attribStorage;
         verticesDataId=rhs.verticesDataId;
         indicesDataId=rhs.indicesDataId;
         drawCommandBlockId=rhs.drawCommandBlockId;
         drawCommandControlData=std::move(rhs.drawCommandControlData);
         instances=std::move(rhs.instances);
         rhs.attribStorage=NULL;
      }
      AttribReference::~AttribReference()
      {
         freeData();
      }
      inline bool AttribReference::valid() const  { return attribStorage!=NULL; }
      inline void AttribReference::allocData(const AttribConfigRef& config,int numVertices,int numIndices,int numDrawCommands)
      { config->allocData(*this,numVertices,numIndices,numDrawCommands); }
      inline void AttribReference::reallocData(int numVertices,int numIndices,int numDrawCommands,bool preserveContent)
      {
         attribStorage->reallocData(*this,numVertices,numIndices,preserveContent);
         RenderingContext::current()->reallocDrawCommands(*this,numDrawCommands,preserveContent);
      }
      inline void AttribReference::freeData()  { if(attribStorage) attribStorage->freeData(*this); }
      inline void AttribReference::uploadVertices(const std::vector<Array>& attribs,
                                                  int fromIndex,int numVertices)
      {
         if(attribStorage)
            attribStorage->uploadVertices(*this,attribs,fromIndex,numVertices);
      }
      inline void AttribReference::uploadIndices(const Array& indices,int fromIndex,int numIndices)
      {
         if(attribStorage)
            attribStorage->uploadIndices(*this,indices,fromIndex,numIndices);
      }
      inline void AttribReference::setDrawCommands(const void *drawCommandBuffer,unsigned bytesToCopy,const unsigned *offsets4,int numDrawCommands)
      { RenderingContext::current()->setDrawCommands(*this,drawCommandBuffer,bytesToCopy,offsets4,numDrawCommands); }
      inline void AttribReference::setDrawCommandsOptimized(void *drawCommandBuffer,unsigned bytesToCopy,const unsigned *offsets4,int numDrawCommands)
      { RenderingContext::current()->setDrawCommandsOptimized(*this,drawCommandBuffer,bytesToCopy,offsets4,numDrawCommands); }
      inline void AttribReference::setDrawCommandsOptimized(void *drawCommandBuffer,unsigned bytesToCopy,const AttribReference::DrawCommandControlData *data,int numDrawCommands)
      { RenderingContext::current()->setDrawCommandsOptimized(*this,drawCommandBuffer,bytesToCopy,data,numDrawCommands); }
      inline std::vector<AttribReference::DrawCommandControlData> AttribReference::generateDrawCommandControlData(const void *drawCommandBuffer,const unsigned *offsets4,int numDrawCommands)
      { RenderingContext::generateDrawCommandControlData(drawCommandBuffer,offsets4,numDrawCommands); }
      inline void AttribReference::prepareDrawCommandsBufferData(void *drawCommandBuffer,const AttribReference::DrawCommandControlData *data,int numDrawCommands)
      { RenderingContext::prepareDrawCommandsBufferData(*this,drawCommandBuffer,data,numDrawCommands); }
      inline void AttribReference::uploadDrawCommandBufferData(const void *drawCommandBuffer,unsigned bytesToCopy,unsigned dstOffset)
      { RenderingContext::current()->uploadDrawCommandBufferData(*this,drawCommandBuffer,bytesToCopy,dstOffset); }
      inline void AttribReference::updateDrawCommandControlData(const DrawCommandControlData *data,int numDrawCommands,unsigned startIndex,bool truncate)
      { RenderingContext::current()->updateDrawCommandControlData(*this,data,numDrawCommands,startIndex,truncate); }
      inline void AttribReference::clearDrawCommands()  { setNumDrawCommands(0); }
      inline void AttribReference::setNumDrawCommands(unsigned num)
      { RenderingContext::current()->setNumDrawCommands(*this,num); }
      inline AttribReference::InstanceGroupId AttribReference::createInstances(unsigned matrixIndex,StateSet *stateSet)
      { return RenderingContext::current()->createInstances(*this,matrixIndex,stateSet); }
      inline AttribReference::InstanceGroupId AttribReference::createInstances(const unsigned *drawCommandIndices,const unsigned drawCommandsCount,unsigned matrixIndex,StateSet *stateSet)
      { return RenderingContext::current()->createInstances(*this,drawCommandIndices,drawCommandsCount,matrixIndex,stateSet); }
      inline void AttribReference::deleteInstances(AttribReference::InstanceGroupId id)
      { RenderingContext::current()->deleteInstances(*this,id); }
   }
}

#endif // GE_SG_ATTRIB_REFERENCE_H
