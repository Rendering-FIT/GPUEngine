#ifndef GE_RG_MESH_H
#define GE_RG_MESH_H

#include <vector>
#include <cstdint>
#include <geRG/Basics.h>
#include <geRG/Export.h>
#include <geRG/Drawable.h>
#include <geRG/Primitive.h>

namespace ge
{
   namespace rg
   {
      class AttribConfig;
      class AttribStorage;
      class MatrixList;
      class StateSet;


      class GERG_EXPORT Mesh {
      protected:

         AttribStorage *_attribStorage;
         unsigned _verticesDataId;
         unsigned _indicesDataId;
         unsigned _primitivesDataId;
         PrimitiveList _primitiveList;
         DrawableList _drawables;

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
         inline unsigned primitivesDataId() const;
         inline void setPrimitivesDataId(unsigned value);
         inline const PrimitiveList& primitiveList() const;
         inline PrimitiveList& primitiveList();
         inline const DrawableList& drawables() const;
         inline DrawableList& drawables();
         inline bool valid() const;

         inline void allocData(const AttribConfig& config,unsigned numVertices,
                               unsigned numIndices,unsigned numPrimitives);
         inline void reallocData(unsigned numVertices,unsigned numIndices,
                                 unsigned numPrimitives,bool preserveContent=true);
         inline void freeData();

         inline unsigned numVertices() const;
         inline unsigned numIndices() const;
         inline unsigned numPrimitives() const;

         inline void uploadVertices(const void*const *attribList,unsigned attribListSize,
                                    unsigned numVertices,unsigned fromIndex=0);
         inline void uploadIndices(const void *indices,unsigned numIndices,unsigned fromIndex=0);

         inline void uploadPrimitives(const PrimitiveGpuData *bufferData,
                                      unsigned numPrimitives,unsigned dstIndex=0);
         inline void setPrimitives(const Primitive *primitiveList,
                                   unsigned numPrimitives,unsigned startIndex=0,
                                   bool truncate=true);
         inline void setAndUploadPrimitives(PrimitiveGpuData *nonConstBufferData,
                                            const Primitive *primitiveList,unsigned numPrimitives);
         inline void setAndUploadPrimitives(PrimitiveGpuData *nonConstBufferData,
                                            const unsigned *modesAndOffsets4,unsigned numPrimitives);
         inline void updateVertexOffsets(void *primitiveBuffer,
                                         const Primitive *primitiveList,unsigned numPrimitives);
         inline static std::vector<Primitive> generatePrimitiveList(
                                         const unsigned *modesAndOffsets4,unsigned numPrimitives);

         inline void clearPrimitives();
         inline void setNumPrimitives(unsigned num);

         inline DrawableId createDrawable(MatrixList *matrixList,StateSet *stateSet);
         inline DrawableId createDrawable(const unsigned *primitiveIndices,
                                          const unsigned primitiveCount,
                                          MatrixList *matrixList,StateSet *stateSet);
         inline void deleteDrawable(DrawableId id);
      };

   }
}



// inline methods
//
// note: they need their own includes that can not be placed on the beginning of this file
//       as there are circular header includes and the classes need to be defined before
//       inline methods to avoid incomplete type compiler error

#include <geRG/AttribStorage.h>
#include <geRG/MatrixList.h>
#include <geRG/RenderingContext.h>

namespace ge
{
   namespace rg
   {
      inline Mesh::Mesh() : _attribStorage(NULL)  {}
      inline Mesh::Mesh(Mesh&& ref)
         : _attribStorage(ref._attribStorage)
         , _verticesDataId(ref._verticesDataId)
         , _indicesDataId(ref._indicesDataId)
         , _primitivesDataId(ref._primitivesDataId)
         , _primitiveList(std::move(ref._primitiveList))
         , _drawables(std::move(ref._drawables))
      {
         ref._attribStorage=NULL;
      }
      inline Mesh& Mesh::operator=(Mesh&& rhs)
      {
         _attribStorage=rhs._attribStorage;
         _verticesDataId=rhs._verticesDataId;
         _indicesDataId=rhs._indicesDataId;
         _primitivesDataId=rhs._primitivesDataId;
         _primitiveList=std::move(rhs._primitiveList);
         _drawables=std::move(rhs._drawables);
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
      inline unsigned Mesh::primitivesDataId() const  { return _primitivesDataId; }
      inline void Mesh::setPrimitivesDataId(unsigned value)  { _primitivesDataId=value; }
      inline const PrimitiveList& Mesh::primitiveList() const  { return _primitiveList; }
      inline PrimitiveList& Mesh::primitiveList()  { return _primitiveList; }
      inline const DrawableList& Mesh::drawables() const  { return _drawables; }
      inline DrawableList& Mesh::drawables()  { return _drawables; }
      inline bool Mesh::valid() const  { return _attribStorage!=NULL; }
      inline void Mesh::allocData(const ge::rg::AttribConfig& attribConfig,unsigned numVertices,unsigned numIndices,unsigned numPrimitives)
         { attribConfig.renderingContext()->allocVertexData(*this,attribConfig,numVertices,numIndices); attribConfig.renderingContext()->allocPrimitives(*this,numPrimitives); }
      inline void Mesh::reallocData(unsigned numVertices,unsigned numIndices,unsigned numPrimitives,bool preserveContent)
         { _attribStorage->renderingContext()->reallocVertexData(*this,numVertices,numIndices,preserveContent); _attribStorage->renderingContext()->reallocPrimitives(*this,numPrimitives,preserveContent); }
      inline void Mesh::freeData()
      {
         if(_attribStorage) {
            _attribStorage->renderingContext()->freePrimitives(*this);
            _attribStorage->freeData(*this);
         }
      }
      inline unsigned Mesh::numVertices() const  { return _attribStorage ? _attribStorage->vertexArrayAllocation(_verticesDataId).numItems : 0; }
      inline unsigned Mesh::numIndices() const  { return _attribStorage ? _attribStorage->indexArrayAllocation(_indicesDataId).numItems : 0; }
      inline unsigned Mesh::numPrimitives() const  { return RenderingContext::current()->primitiveStorage()->operator[](_primitivesDataId).numItems; }
      inline void Mesh::uploadVertices(const void*const* attribList,unsigned attribListSize,unsigned numVertices,unsigned fromIndex)
      {
         if(_attribStorage)
            _attribStorage->uploadVertices(*this,attribList,attribListSize,numVertices,fromIndex);
      }
      inline void Mesh::uploadIndices(const void *indices,unsigned numIndices,unsigned fromIndex)
      {
         if(_attribStorage)
            _attribStorage->uploadIndices(*this,indices,numIndices,fromIndex);
      }
      inline void Mesh::uploadPrimitives(const PrimitiveGpuData* bufferData,unsigned numPrimitives,unsigned dstIndex)
      { RenderingContext::current()->uploadPrimitives(*this,bufferData,numPrimitives,dstIndex); }
      inline void Mesh::setPrimitives(const ge::rg::Primitive* primitiveList,unsigned numPrimitives,unsigned startIndex,bool truncate)
      { RenderingContext::current()->setPrimitives(*this,primitiveList,numPrimitives,startIndex,truncate); }
      inline void Mesh::setAndUploadPrimitives(ge::rg::PrimitiveGpuData* nonConstBufferData,const ge::rg::Primitive* primitiveList,unsigned numPrimitives)
      { RenderingContext::current()->setAndUploadPrimitives(*this,nonConstBufferData,primitiveList,numPrimitives); }
      inline void Mesh::setAndUploadPrimitives(PrimitiveGpuData* nonConstBufferData,const unsigned* modesAndOffsets4,unsigned numPrimitives)
      { RenderingContext::current()->setAndUploadPrimitives(*this,nonConstBufferData,modesAndOffsets4,numPrimitives); }
      inline void Mesh::updateVertexOffsets(void* primitiveBuffer,const ge::rg::Primitive* primitiveList,unsigned numPrimitives)
      { RenderingContext::current()->updateVertexOffsets(*this,primitiveBuffer,primitiveList,numPrimitives); }
      inline std::vector<Primitive> Mesh::generatePrimitiveList(const unsigned* modesAndOffsets4,unsigned numPrimitives)
      { return RenderingContext::generatePrimitiveList(modesAndOffsets4,numPrimitives); }
      inline void Mesh::clearPrimitives()  { setNumPrimitives(0); }
      inline void Mesh::setNumPrimitives(unsigned num)
      { RenderingContext::current()->setNumPrimitives(*this,num); }
      inline DrawableId Mesh::createDrawable(MatrixList *matrixList,StateSet *stateSet)
      { return RenderingContext::current()->createDrawable(*this,matrixList,stateSet); }
      inline DrawableId Mesh::createDrawable(const unsigned *primitiveIndices,const unsigned primitiveCount,MatrixList *matrixList,StateSet *stateSet)
      { return RenderingContext::current()->createDrawable(*this,primitiveIndices,primitiveCount,matrixList,stateSet); }
      inline void Mesh::deleteDrawable(DrawableId id)
      { RenderingContext::current()->deleteDrawable(*this,id); }
   }
}

#endif // GE_RG_MESH_H
