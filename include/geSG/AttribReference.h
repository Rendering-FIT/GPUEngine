#ifndef GE_SG_ATTRIB_REFERENCE_H
#define GE_SG_ATTRIB_REFERENCE_H

#include <geSG/Export.h>

namespace ge
{
   namespace sg
   {
      class Array;
      class AttribConfigRef;
      class AttribStorage;
      struct DrawCommandData;


      class GE_EXPORT AttribReference {
      public:

         AttribStorage *attribStorage;
         unsigned verticesDataId;
         unsigned indicesDataId;
         unsigned drawCommandsId;

         inline AttribReference() : attribStorage(NULL) {}
         inline AttribReference(AttribReference&& ref);
         inline AttribReference& operator=(AttribReference&& rhs);
         inline ~AttribReference();

         AttribReference(const AttribReference&) = delete;
         AttribReference& operator=(const AttribReference&) = delete;

         inline bool valid() const;

         inline void allocData(const AttribConfigRef& config,int numVertices,
                               int numIndices,int numDrawCommands);
         inline void reallocData(int numVertices,int numIndices,
                                 int numDrawCommands,bool preserveContent=true);
         inline void freeData();

         inline void uploadVertexData(const std::vector<Array>& attribs,
                                      int fromIndex=0,int numVertices=-1);
         inline void uploadIndices(const Array& indices,int fromIndex=0,int numIndices=-1);
         inline void uploadDrawCommands(const DrawCommandData *drawCommands,
                                        int fromIndex,int numDrawCommands);
         inline void uploadDrawCommands(const DrawCommandData *drawCommands,
                                        int numDrawCommands);
         inline void uploadDrawCommands(const std::vector<DrawCommandData> &drawCommands,
                                        int fromIndex=0);

      };

   }
}



// inline methods
//
// note: they need their own includes that can not be placed on the beginning of this file
//       as there are circular header includes and the classes need to be defined before
//       inline methods to avoid incomplete type compiler error

#include <geSG/AttribStorage.h>
#include <geSG/AttribManager.h>

namespace ge
{
   namespace sg
   {
      inline AttribReference::AttribReference(AttribReference&& ref)
         : attribStorage(ref.attribStorage)
         , verticesDataId(ref.verticesDataId)
         , indicesDataId(ref.indicesDataId)
         , drawCommandsId(ref.drawCommandsId)
      {
         ref.attribStorage=NULL;
      }
      inline AttribReference& AttribReference::operator=(AttribReference&& rhs)
      {
         attribStorage=rhs.attribStorage;
         verticesDataId=rhs.verticesDataId;
         indicesDataId=rhs.indicesDataId;
         drawCommandsId=rhs.drawCommandsId;
         rhs.attribStorage=NULL;
      }
      AttribReference::~AttribReference()
      {
         freeData();
      }
      inline bool AttribReference::valid() const  { return attribStorage!=NULL; }
      inline void AttribReference::allocData(const AttribConfigRef& config,int numVertices,
                                             int numIndices,int numDrawCommands)
      { config->allocData(*this,numVertices,numIndices,numDrawCommands); }
      inline void AttribReference::reallocData(int numVertices,int numIndices,
                                               int numDrawCommands,bool preserveContent)
      { attribStorage->reallocData(*this,numVertices,numIndices,numDrawCommands,preserveContent); }
      inline void AttribReference::freeData()  { if(attribStorage) attribStorage->freeData(*this); }
      inline void AttribReference::uploadVertexData(const std::vector<Array>& attribs,
                                                    int fromIndex,int numVertices)
      {
         if(attribStorage)
            attribStorage->uploadVertexData(*this,attribs,fromIndex,numVertices);
      }
      inline void AttribReference::uploadIndices(const Array& indices,int fromIndex,int numIndices)
      {
         if(attribStorage)
            attribStorage->uploadIndices(*this,indices,fromIndex,numIndices);
      }
      inline void AttribReference::uploadDrawCommands(const DrawCommandData *drawCommands,int fromIndex,int numDrawCommands)
      {
         if(attribStorage)
            attribStorage->uploadDrawCommands(*this,drawCommands,fromIndex,numDrawCommands);
      }
      inline void AttribReference::uploadDrawCommands(const DrawCommandData *drawCommands,int numDrawCommands)
      { uploadDrawCommands(drawCommands,0,numDrawCommands); }
      inline void AttribReference::uploadDrawCommands(const std::vector<DrawCommandData> &drawCommands,int fromIndex)
      { uploadDrawCommands(drawCommands.data(),drawCommands.size(),fromIndex); }

   }
}

#endif // GE_SG_ATTRIB_REFERENCE_H
