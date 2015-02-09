#ifndef GE_SG_ATTRIB_REFERENCE_H
#define GE_SG_ATTRIB_REFERENCE_H

#include <geSG/Export.h>
#include <geSG/FlexibleArrayList.h>
#include <list>

namespace ge
{
   namespace sg
   {
      class Array;
      class AttribConfigRef;
      class AttribStorage;


      class GE_EXPORT AttribReference {
      public:

         typedef FlexibleArray<unsigned,ListItemBase> InstanceGroup;
         typedef FlexibleArrayList<InstanceGroup> InstanceGroupList;
         typedef InstanceGroupList::iterator InstanceGroupId;

         AttribStorage *attribStorage;
         unsigned verticesDataId;
         unsigned indicesDataId;
         unsigned drawCommandBlockId;
         std::vector<unsigned> drawCommandOffsets;
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
                                     const unsigned *offsets,int numDrawCommands);
         inline void setDrawCommandsOptimized(void *drawCommandBuffer,unsigned bytesToCopy,
                                              const unsigned *offsets,int numDrawCommands);
         inline void updateDrawCommandsBufferData(void *drawCommandBuffer,
                                                  const unsigned *offsets,int numDrawCommands);
         inline void uploadDrawCommands(const void *drawCommandBuffer,
                                        unsigned bytesToCopy,unsigned dstOffset=0);
         inline void updateDrawCommandOffsets(const unsigned *offsets,int numDrawCommands,
                                              unsigned startIndex=0,bool truncate=true);
         inline void clearDrawCommands();
         inline void setNumDrawCommands(unsigned num);

         inline InstanceGroupId createInstances(unsigned matrixOffset,unsigned stateSetOffset);
         inline InstanceGroupId createInstances(const unsigned *drawCommandIndices,
                                                const unsigned drawCommandsCount,
                                                unsigned matrixOffset,unsigned stateSetOffset);
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
      inline AttribReference::AttribReference() : attribStorage(NULL)  {}
      inline AttribReference::AttribReference(AttribReference&& ref)
         : attribStorage(ref.attribStorage)
         , verticesDataId(ref.verticesDataId)
         , indicesDataId(ref.indicesDataId)
         , drawCommandBlockId(ref.drawCommandBlockId)
         , drawCommandOffsets(std::move(ref.drawCommandOffsets))
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
         drawCommandOffsets=std::move(rhs.drawCommandOffsets);
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
      inline void AttribReference::setDrawCommands(const void *drawCommandBuffer,unsigned bytesToCopy,const unsigned *offsets,int numDrawCommands)
      { RenderingContext::current()->setDrawCommands(*this,drawCommandBuffer,bytesToCopy,offsets,numDrawCommands); }
      inline void AttribReference::setDrawCommandsOptimized(void *drawCommandBuffer,unsigned bytesToCopy,const unsigned *offsets,int numDrawCommands)
      { RenderingContext::current()->setDrawCommandsOptimized(*this,drawCommandBuffer,bytesToCopy,offsets,numDrawCommands); }
      inline void AttribReference::updateDrawCommandsBufferData(void *drawCommandBuffer,const unsigned *offsets,int numDrawCommands)
      { RenderingContext::current()->updateDrawCommandsBufferData(*this,drawCommandBuffer,offsets,numDrawCommands); }
      inline void AttribReference::uploadDrawCommands(const void *drawCommandBuffer,unsigned bytesToCopy,unsigned dstOffset)
      { RenderingContext::current()->uploadDrawCommands(*this,drawCommandBuffer,bytesToCopy,dstOffset); }
      inline void AttribReference::updateDrawCommandOffsets(const unsigned *offsets,int numDrawCommands,unsigned startIndex,bool truncate)
      { RenderingContext::current()->updateDrawCommandOffsets(*this,offsets,numDrawCommands,startIndex,truncate); }
      inline void AttribReference::clearDrawCommands()  { setNumDrawCommands(0); }
      inline void AttribReference::setNumDrawCommands(unsigned num)
      { RenderingContext::current()->setNumDrawCommands(*this,num); }
      inline AttribReference::InstanceGroupId AttribReference::createInstances(unsigned matrixOffset,unsigned stateSetOffset)
      { return RenderingContext::current()->createInstances(*this,matrixOffset,stateSetOffset); }
      inline AttribReference::InstanceGroupId AttribReference::createInstances(const unsigned *drawCommandIndices,const unsigned drawCommandsCount,unsigned matrixOffset,unsigned stateSetOffset)
      { return RenderingContext::current()->createInstances(*this,drawCommandIndices,drawCommandsCount,matrixOffset,stateSetOffset); }
      inline void AttribReference::deleteInstances(AttribReference::InstanceGroupId id)
      { RenderingContext::current()->deleteInstances(*this,id); }
   }
}

#endif // GE_SG_ATTRIB_REFERENCE_H
