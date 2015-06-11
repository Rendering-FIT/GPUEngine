#ifndef GE_SG_MESH_H
#define GE_SG_MESH_H

#include <geSG/Export.h>
#include <geSG/InstanceGroup.h>
#include <vector>
#include <cstdint>

namespace ge
{
   namespace sg
   {
      class AttribConfigRef;
      class AttribStorage;
      class InstancingMatrices;
      class StateSet;


      class GESG_EXPORT Mesh {
      public:

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

      protected:

         AttribStorage *_attribStorage;
         unsigned _verticesDataId;
         unsigned _indicesDataId;
         unsigned _drawCommandBlockId;
         std::vector<DrawCommandControlData> _drawCommandControlData;
         InstanceGroupList _instances;

      public:

         inline Mesh();
         inline Mesh(Mesh&& ref);
         inline Mesh& operator=(Mesh&& rhs);
         inline ~Mesh();

         Mesh(const Mesh&) = delete;
         Mesh& operator=(const Mesh&) = delete;

         inline AttribStorage* attribStorage() const;
         inline void setAttribStorage(AttribStorage *a);
         inline unsigned verticesDataId() const;
         inline void setVerticesDataId(unsigned value);
         inline unsigned indicesDataId() const;
         inline void setIndicesDataId(unsigned value);
         inline unsigned drawCommandBlockId() const;
         inline void setDrawCommandBlockId(unsigned value);
         inline const std::vector<DrawCommandControlData>& drawCommandControlData() const;
         inline std::vector<DrawCommandControlData>& drawCommandControlData();
         inline const InstanceGroupList& instances() const;
         inline InstanceGroupList& instances();
         inline bool valid() const;

         inline void allocData(const AttribConfigRef& config,int numVertices,
                               int numIndices,int drawCommandBlockSize);
         inline void reallocData(int numVertices,int numIndices,
                                 int numDrawCommands,bool preserveContent=true);
         inline void freeData();

         inline int numVertices() const;
         inline int numIndices() const;
         inline int drawCommandBlockSize() const;

         inline void uploadVertices(const void*const *attribs,int numVertices,int fromIndex=0);
         inline void uploadIndices(const void *indices,int numIndices,int fromIndex=0);

         inline void uploadPreprocessedDrawCommands(const void *drawCommandBuffer,
                                                    unsigned bytesToCopy,unsigned dstOffset=0);
         inline void setDrawCommandControlData(const DrawCommandControlData *data,
                                               int numDrawCommands,unsigned startIndex=0,
                                               bool truncate=true);
         inline void preprocessDrawCommands(void *drawCommandBuffer,
                                            const DrawCommandControlData *data,
                                            int numDrawCommands);
         inline static std::vector<DrawCommandControlData> generateDrawCommandControlData(
                                            const void *drawCommandBuffer,
                                            const unsigned *modesAndOffsets4,int numDrawCommands);

         inline void uploadDrawCommands(void *nonConstDrawCommandBuffer,unsigned bytesToCopy,
                                        const DrawCommandControlData *data,
                                        int numDrawCommands);
         inline void uploadDrawCommands(void *nonConstDrawCommandBuffer,unsigned bytesToCopy,
                                        const unsigned *modesAndOffsets4,int numDrawCommands);

         inline void clearDrawCommands();
         inline void setNumDrawCommands(unsigned num);

         inline InstanceGroupId createInstances(InstancingMatrices *im,StateSet *stateSet);
         inline InstanceGroupId createInstances(const unsigned *drawCommandIndices,
                                                const int drawCommandsCount,
                                                InstancingMatrices *im,StateSet *stateSet);
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
#include <geSG/InstancingMatrices.h>
#include <geSG/RenderingContext.h>

namespace ge
{
   namespace sg
   {
      inline Mesh::DrawCommandControlData::DrawCommandControlData(uint32_t offset4,uint16_t mode)  { set(offset4,mode); }
      inline Mesh::Mesh() : _attribStorage(NULL)  {}
      inline Mesh::Mesh(Mesh&& ref)
         : _attribStorage(ref._attribStorage)
         , _verticesDataId(ref._verticesDataId)
         , _indicesDataId(ref._indicesDataId)
         , _drawCommandBlockId(ref._drawCommandBlockId)
         , _drawCommandControlData(std::move(ref._drawCommandControlData))
         , _instances(std::move(ref._instances))
      {
         ref._attribStorage=NULL;
      }
      inline Mesh& Mesh::operator=(Mesh&& rhs)
      {
         _attribStorage=rhs._attribStorage;
         _verticesDataId=rhs._verticesDataId;
         _indicesDataId=rhs._indicesDataId;
         _drawCommandBlockId=rhs._drawCommandBlockId;
         _drawCommandControlData=std::move(rhs._drawCommandControlData);
         _instances=std::move(rhs._instances);
         rhs._attribStorage=NULL;
         return *this;
      }
      inline Mesh::~Mesh()
      {
         freeData();
      }
      inline AttribStorage* Mesh::attribStorage() const  { return _attribStorage; }
      inline void Mesh::setAttribStorage(AttribStorage *a)  { _attribStorage=a; }
      inline unsigned Mesh::verticesDataId() const  { return _verticesDataId; }
      inline void Mesh::setVerticesDataId(unsigned value)  { _verticesDataId=value; }
      inline unsigned Mesh::indicesDataId() const  { return _indicesDataId; }
      inline void Mesh::setIndicesDataId(unsigned value)  { _indicesDataId=value; }
      inline unsigned Mesh::drawCommandBlockId() const  { return _drawCommandBlockId; }
      inline void Mesh::setDrawCommandBlockId(unsigned value)  { _drawCommandBlockId=value; }
      inline const std::vector<Mesh::DrawCommandControlData>& Mesh::drawCommandControlData() const  { return _drawCommandControlData; }
      inline std::vector<Mesh::DrawCommandControlData>& Mesh::drawCommandControlData()  { return _drawCommandControlData; }
      inline const InstanceGroupList& Mesh::instances() const  { return _instances; }
      inline InstanceGroupList& Mesh::instances()  { return _instances; }
      inline bool Mesh::valid() const  { return _attribStorage!=NULL; }
      inline void Mesh::allocData(const AttribConfigRef& config,int numVertices,int numIndices,int numDrawCommands)
      { config->allocData(*this,numVertices,numIndices,numDrawCommands); }
      inline void Mesh::reallocData(int numVertices,int numIndices,int numDrawCommands,bool preserveContent)
      {
         _attribStorage->reallocData(*this,numVertices,numIndices,preserveContent);
         RenderingContext::current()->reallocDrawCommands(*this,numDrawCommands,preserveContent);
      }
      inline void Mesh::freeData()
      {
         if(_attribStorage) {
            RenderingContext::current()->freeDrawCommands(*this);
            _attribStorage->freeData(*this);
         }
      }
      inline int Mesh::numVertices() const  { return _attribStorage ? _attribStorage->vertexAllocationBlock(_verticesDataId).numElements : 0; }
      inline int Mesh::numIndices() const  { return _attribStorage ? _attribStorage->indexAllocationBlock(_indicesDataId).numElements : 0; }
      inline int Mesh::drawCommandBlockSize() const  { return RenderingContext::current()->drawCommandsAllocation(_drawCommandBlockId).size; }
      inline void Mesh::uploadVertices(const void*const *attribs,int numVertices,int fromIndex)
      {
         if(_attribStorage)
            _attribStorage->uploadVertices(*this,attribs,numVertices,fromIndex);
      }
      inline void Mesh::uploadIndices(const void *indices,int numIndices,int fromIndex)
      {
         if(_attribStorage)
            _attribStorage->uploadIndices(*this,indices,numIndices,fromIndex);
      }
      inline void Mesh::uploadPreprocessedDrawCommands(const void *drawCommandBuffer,unsigned bytesToCopy,unsigned dstOffset)
      { RenderingContext::current()->uploadPreprocessedDrawCommands(*this,drawCommandBuffer,bytesToCopy,dstOffset); }
      inline void Mesh::setDrawCommandControlData(const DrawCommandControlData *data,int numDrawCommands,unsigned startIndex,bool truncate)
      { RenderingContext::current()->setDrawCommandControlData(*this,data,numDrawCommands,startIndex,truncate); }
      inline void Mesh::preprocessDrawCommands(void *drawCommandBuffer,const DrawCommandControlData *data,int numDrawCommands)
      { RenderingContext::current()->preprocessDrawCommands(*this,drawCommandBuffer,data,numDrawCommands); }
      inline std::vector<Mesh::DrawCommandControlData> Mesh::generateDrawCommandControlData(const void *drawCommandBuffer,const unsigned *offsets4,int numDrawCommands)
      { return RenderingContext::generateDrawCommandControlData(drawCommandBuffer,offsets4,numDrawCommands); }
      inline void Mesh::uploadDrawCommands(void *nonConstDrawCommandBuffer,unsigned bytesToCopy,const DrawCommandControlData *data,int numDrawCommands)
      { RenderingContext::current()->uploadDrawCommands(*this,nonConstDrawCommandBuffer,bytesToCopy,data,numDrawCommands); }
      inline void Mesh::uploadDrawCommands(void *nonConstDrawCommandBuffer,unsigned bytesToCopy,const unsigned *offsets4,int numDrawCommands)
      { RenderingContext::current()->uploadDrawCommands(*this,nonConstDrawCommandBuffer,bytesToCopy,offsets4,numDrawCommands); }
      inline void Mesh::clearDrawCommands()  { setNumDrawCommands(0); }
      inline void Mesh::setNumDrawCommands(unsigned num)
      { RenderingContext::current()->setNumDrawCommands(*this,num); }
      inline InstanceGroupId Mesh::createInstances(InstancingMatrices *im,StateSet *stateSet)
      { return RenderingContext::current()->createInstances(*this,im,stateSet); }
      inline InstanceGroupId Mesh::createInstances(const unsigned *drawCommandIndices,const int drawCommandsCount,InstancingMatrices *im,StateSet *stateSet)
      { return RenderingContext::current()->createInstances(*this,drawCommandIndices,drawCommandsCount,im,stateSet); }
      inline void Mesh::deleteInstances(InstanceGroupId id)
      { RenderingContext::current()->deleteInstances(*this,id); }
   }
}

#endif // GE_SG_MESH_H
