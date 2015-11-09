// some includes need to be placed before GE_RG_RENDERING_CONTEXT_H define
// to prevent problems of circular includes
#include <geRG/AttribConfig.h>
#include <geRG/MatrixList.h>
#include <geRG/Mesh.h>

#ifndef GE_RG_RENDERING_CONTEXT_H
#define GE_RG_RENDERING_CONTEXT_H

#include <memory>
#include <geRG/Export.h>
#include <geRG/AllocationManagers.h>
#include <geRG/BufferStorage.h>
#include <geRG/DrawCommand.h>
#include <geRG/Object.h>
#include <geRG/Primitive.h>
#include <geRG/StateSet.h>
#include <geCore/InitAndFinalize.h>

namespace ge
{
   namespace gl
   {
      class BufferObject;
   }
   namespace rg
   {
      class Transformation;


      class DrawCommandStorage : public BufferStorage<DrawCommandAllocationManager,
            DrawCommandGpuData> {
      public:
#if _MSC_VER<=1900
         // MSVC 2013 fails to inherit constructors according to C++11 standard
         inline DrawCommandStorage(unsigned capacity=0,unsigned flags=0x88E8/*GL_DYNAMIC_DRAW*/,void *data=nullptr) : BufferStorage(capacity,flags,data) {}
         inline DrawCommandStorage(unsigned capacity,unsigned numNullItems,unsigned flags,void *data=nullptr) : BufferStorage(capacity,numNullItems,flags,data) {}
         inline DrawCommandStorage(unsigned bufferSize,unsigned allocManagerCapacity,unsigned numNullItems,unsigned flags,void *data=nullptr) : BufferStorage(bufferSize,allocManagerCapacity,numNullItems,flags,data) {}
#else
         using BufferStorage::BufferStorage;
#endif
         inline void alloc(DrawCommand* id)  { BufferStorage<DrawCommandAllocationManager,DrawCommandGpuData>::alloc(&id->data); }  ///< \brief Allocates one draw command and stores its index in the DrawCommand pointed by id parameter.
         inline void alloc(unsigned num,DrawCommand *ids)  { BufferStorage<DrawCommandAllocationManager,DrawCommandGpuData>::alloc(num,&ids->data); }  ///< \brief Allocates number of draw commands. Array pointed by ids must be at least num DrawCommands long.
      };
      typedef BufferStorage<BlockAllocationManager<Mesh>,
            PrimitiveGpuData> PrimitiveStorage;
      typedef BufferStorage<BlockAllocationManager<MatrixList>,
            MatrixGpuData> MatrixStorage;
      typedef BufferStorage<ItemAllocationManager,
            ListControlGpuData> ListControlStorage;
      typedef BufferStorage<ItemAllocationManager,
            StateSetGpuData> StateSetStorage;


      class GERG_EXPORT RenderingContext {
      public:

         typedef AttribConfig::AttribConfigList AttribConfigList;
         enum class MappedBufferAccess : uint8_t { READ=0x1, WRITE=0x2, READ_WRITE=0x3, NO_ACCESS=0x0 };

      protected:

         AttribConfigList _attribConfigList;
         unsigned _numAttribStorages;
         //StateSetList
         typedef std::vector<std::shared_ptr<ge::rg::Transformation>> TransformationGraphList;
         TransformationGraphList _transformationGraphs;
         std::shared_ptr<MatrixList> _emptyMatrixList;
         bool _useARBShaderDrawParameters;

         mutable PrimitiveStorage _primitiveStorage;
         mutable DrawCommandStorage _drawCommandStorage;
         mutable MatrixStorage _matrixStorage;
         mutable ListControlStorage _matrixListControlStorage;
         mutable StateSetStorage _stateSetStorage;

         ge::gl::BufferObject *_drawIndirectBuffer;
         float *_cpuTransformationBuffer;
         ItemAllocationManager _transformationAllocationManager;

         unsigned _indirectBufferAllocatedSpace4;

         static void* mapBuffer(ge::gl::BufferObject *buffer,
                                MappedBufferAccess requestedAccess,
                                void* &_mappedBufferPtr,
                                MappedBufferAccess &grantedAccess);
         static void unmapBuffer(ge::gl::BufferObject *buffer,
                                 void* &mappedBufferPtr,
                                 MappedBufferAccess &currentAccess);

      public:

         static const float identityMatrix[16];
         inline const std::shared_ptr<MatrixList>& emptyMatrixList() const;

         RenderingContext();
         virtual ~RenderingContext();

         inline  const AttribConfigList& attribConfigList();
         virtual AttribConfigRef getAttribConfig(const AttribConfig::ConfigData &config);
         inline  AttribConfigRef getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo);
         inline  AttribConfigRef getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,
                                                AttribConfigId id);
         void removeAttribConfig(AttribConfigList::iterator it);

         inline bool useARBShaderDrawParameters() const;
         void setUseARBShaderDrawParameters(bool value);
         inline unsigned numAttribStorages() const;
         void onAttribStorageInit(AttribStorage *a);
         void onAttribStorageRelease(AttribStorage *a);
	 
         inline PrimitiveStorage* primitiveStorage() const;          ///< Returns BufferStorage that contains primitive set data of this graphics context. Any modification to the buffer must be done carefully to not break internal data consistency.
         inline DrawCommandStorage* drawCommandStorage() const;            ///< Returns BufferStorage that contains draw commands. Any modification to the buffer must be done carefully to not break internal data consistency.
         inline MatrixStorage* matrixStorage() const;
         inline ListControlStorage* matrixListControlStorage() const;
         inline StateSetStorage* stateSetStorage() const;                  ///< Returns BufferStorage that contains StateSet specific data.

         inline ge::gl::BufferObject* drawIndirectBuffer();  ///< Returns draw indirect buffer used for indirect rendering.
         inline float* cpuTransformationBuffer();

         void unmapBuffers();

         inline unsigned* transformationAllocation(unsigned id) const;
         inline ItemAllocationManager& transformationAllocationManager();
         inline const ItemAllocationManager& transformationAllocationManager() const;

         virtual bool allocPrimitives(Mesh &mesh,unsigned numPrimitives);
         virtual bool reallocPrimitives(Mesh &mesh,unsigned numPrimitives,
                                        bool preserveContent=true);
         virtual void freePrimitives(Mesh &mesh);

         virtual void uploadPrimitives(Mesh &mesh,const PrimitiveGpuData *bufferData,
                                       unsigned numPrimitives,unsigned dstIndex=0);
         virtual void setPrimitives(Mesh &mesh,const Primitive *primitiveList,
                                    int numPrimitives,unsigned startIndex=0,
                                    bool truncate=true);
         virtual void setAndUploadPrimitives(Mesh &mesh,PrimitiveGpuData *nonConstBufferData,
                                             const Primitive *primitiveList,int numPrimitives);
         inline void setAndUploadPrimitives(Mesh &mesh,PrimitiveGpuData *nonConstBufferData,
                                            const unsigned *modesAndOffsets4,int numPrimitives);
         static void updateVertexOffsets(Mesh &mesh,void *primitiveBuffer,
                                         const Primitive *primitiveList,int numPrimitives);
         static std::vector<Primitive> generatePrimitiveList(
                                         const unsigned *modesAndOffsets4,int numPrimitives);

         inline  void clearPrimitives(Mesh &mesh);
         virtual void setNumPrimitives(Mesh &mesh,unsigned num);

         inline ObjectId createObject(Mesh &mesh,MatrixList *ml,StateSet *stateSet);
         virtual ObjectId createObject(Mesh &mesh,
                                       const unsigned *primitiveIndices,
                                       const int primtiveCount,
                                       MatrixList *ml,StateSet *stateSet);
         virtual void deleteObject(Mesh &mesh,ObjectId id);

         inline TransformationGraphList& transformationGraphs();
         inline const TransformationGraphList& transformationGraphs() const;
         virtual void appendTransformationGraph(std::shared_ptr<Transformation>& transformation);
         virtual void removeTransformationGraph(std::shared_ptr<Transformation>& transformation);

         virtual void cancelAllAllocations();
         virtual void handleContextLost();

         inline unsigned positionInIndirectBuffer4() const;
         inline void setPositionInIndirectBuffer4(unsigned pos);

         virtual void evaluateTransformationGraph();
         virtual void setupRendering();
         virtual void render();

         static inline std::shared_ptr<RenderingContext>& current();
         static void setCurrent(const std::shared_ptr<RenderingContext>& ptr);

         static void init();
         static void finalize();

      protected:
         struct AutoInitRenderingContext {
            bool initialized; // initialized to false if struct is declared static
            bool usingNiftyCounter;
            uint8_t ptr[sizeof(std::shared_ptr<RenderingContext>)];
            inline std::shared_ptr<RenderingContext>& get()  { return reinterpret_cast<std::shared_ptr<RenderingContext>&>(ptr); }
            AutoInitRenderingContext();
            ~AutoInitRenderingContext();
         };
         struct NoExport { // workaround for MSVC 2015: thread_local can not be DLL-exported,
                           // solution: nested structures are not DLL-exported do not inherit DLL-export of parent class
            static thread_local AutoInitRenderingContext _currentContext;
         };
      };


      static ge::core::InitAndFinalize<RenderingContext> renderingContextInitAndFinalize;


      inline RenderingContext::MappedBufferAccess& operator|=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b);
      inline RenderingContext::MappedBufferAccess& operator&=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b);
      inline RenderingContext::MappedBufferAccess& operator+=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b);
      inline RenderingContext::MappedBufferAccess& operator-=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b);
   }
}



// inline methods

namespace ge
{
   namespace rg
   {
      inline const std::shared_ptr<MatrixList>& RenderingContext::emptyMatrixList() const
      { if(_emptyMatrixList==nullptr) const_cast<RenderingContext*>(this)->_emptyMatrixList=std::make_shared<MatrixList>(0,0,0); return _emptyMatrixList; }
      inline const RenderingContext::AttribConfigList& RenderingContext::attribConfigList()  { return _attribConfigList; }
      inline AttribConfigRef RenderingContext::getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo)
      { return getAttribConfig(attribTypes,ebo,AttribConfig::getId(attribTypes,ebo)); }
      inline AttribConfigRef RenderingContext::getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,AttribConfigId id)
      { return getAttribConfig(AttribConfig::ConfigData(attribTypes,ebo,id)); }
      inline bool RenderingContext::useARBShaderDrawParameters() const  { return _useARBShaderDrawParameters; }
      inline unsigned RenderingContext::numAttribStorages() const  { return _numAttribStorages; }
      inline PrimitiveStorage* RenderingContext::primitiveStorage() const  { return &_primitiveStorage; }
      inline DrawCommandStorage* RenderingContext::drawCommandStorage() const  { return &_drawCommandStorage; }
      inline MatrixStorage* RenderingContext::matrixStorage() const  { return &_matrixStorage; }
      inline ListControlStorage* RenderingContext::matrixListControlStorage() const  { return &_matrixListControlStorage; }
      inline StateSetStorage* RenderingContext::stateSetStorage() const  { return &_stateSetStorage; }
      inline ge::gl::BufferObject* RenderingContext::drawIndirectBuffer()  { return _drawIndirectBuffer; }
      inline float* RenderingContext::cpuTransformationBuffer()  { return _cpuTransformationBuffer; }
      inline unsigned* RenderingContext::transformationAllocation(unsigned id) const  { return _transformationAllocationManager[id]; }
      inline ItemAllocationManager& RenderingContext::transformationAllocationManager()  { return _transformationAllocationManager; }
      inline const ItemAllocationManager& RenderingContext::transformationAllocationManager() const  { return _transformationAllocationManager; }
      inline void RenderingContext::setAndUploadPrimitives(ge::rg::Mesh& mesh,PrimitiveGpuData* nonConstBufferData,const unsigned int* modesAndOffsets4,int numPrimitives)
      { setAndUploadPrimitives(mesh,nonConstBufferData,generatePrimitiveList(modesAndOffsets4,numPrimitives).data(),numPrimitives); }
      inline void RenderingContext::clearPrimitives(Mesh &mesh)  { setNumPrimitives(mesh,0); }
      inline ObjectId RenderingContext::createObject(Mesh &mesh,MatrixList *ml,StateSet *stateSet)
      { return createObject(mesh,nullptr,-1,ml,stateSet); }
      inline RenderingContext::TransformationGraphList& RenderingContext::transformationGraphs()  { return _transformationGraphs; }
      inline const RenderingContext::TransformationGraphList& RenderingContext::transformationGraphs() const  { return _transformationGraphs; }
      inline unsigned RenderingContext::positionInIndirectBuffer4() const  { return _indirectBufferAllocatedSpace4; }
      inline void RenderingContext::setPositionInIndirectBuffer4(unsigned pos)  { _indirectBufferAllocatedSpace4=pos; }
      inline std::shared_ptr<RenderingContext>& RenderingContext::current()
      { return NoExport::_currentContext.get(); }

      inline RenderingContext::MappedBufferAccess& operator|=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b)
      { (uint8_t&)a|=(uint8_t)b; return a; }
      inline RenderingContext::MappedBufferAccess& operator&=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b)
      { (uint8_t&)a&=(uint8_t)b; return a; }
      inline RenderingContext::MappedBufferAccess& operator+=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b)
      { (uint8_t&)a|=(uint8_t)b; return a; }
      inline RenderingContext::MappedBufferAccess& operator-=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b)
      { (uint8_t&)a&=(uint8_t)b; return a; }

   }
}

#endif // GE_RG_RENDERING_CONTEXT_H
