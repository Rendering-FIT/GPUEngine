// some includes need to be placed before GE_RG_RENDERING_CONTEXT_H define
// to prevent problems of circular includes
#include <geRG/AttribConfig.h>
#include <geRG/Mesh.h>

#ifndef GE_RG_RENDERING_CONTEXT_H
#define GE_RG_RENDERING_CONTEXT_H

#include <memory>
#include <geRG/Export.h>
#include <geRG/AllocationManagers.h>
#include <geRG/InstanceGroup.h>
#include <geCore/InitAndFinalize.h>

namespace ge
{
   namespace gl
   {
      class BufferObject;
   }
   namespace rg
   {
      class InstancingMatrices;
      class StateSet;
      class Transformation;


      class GERG_EXPORT RenderingContext {
      public:

         typedef AttribConfig::AttribConfigList AttribConfigList;
         enum class MappedBufferAccess : uint8_t { READ=0x1, WRITE=0x2, READ_WRITE=0x3, NO_ACCESS=0x0 };

         struct DrawCommandBufferData {
            unsigned countAndIndexedFlag;
            unsigned first;
            unsigned vertexOffset;
         };

         struct Instance {
            unsigned drawCommandOffset4;
            unsigned instancingMatricesControlOffset4;
            unsigned stateSetDataOffset4;
         };

      protected:

         AttribConfigList _attribConfigList;
         unsigned _numAttribStorages;
         //StateSetList
         typedef std::vector<std::shared_ptr<ge::rg::Transformation>> TransformationGraphList;
         TransformationGraphList _transformationGraphs;
         std::shared_ptr<InstancingMatrices> _identityInstancingMatrix;
         bool _useARBShaderDrawParameters;

         ge::gl::BufferObject *_stateSetBuffer;
         ge::gl::BufferObject *_drawCommandBuffer;
         ge::gl::BufferObject *_instanceBuffer;
         ge::gl::BufferObject *_indirectCommandBuffer;
         float *_cpuTransformationBuffer;
         //ge::gl::BufferObject *_transformationBuffer;
         //ge::gl::BufferObject *_transformationGraphBuffer;
         ge::gl::BufferObject *_instancingMatricesControlBuffer;
         ge::gl::BufferObject *_transformationThreadsData;
         ge::gl::BufferObject *_instancingMatrixBuffer;

         ItemAllocationManager _stateSetBufferAllocationManager;
         ChunkAllocationManager<Mesh> _drawCommandAllocationManager;  ///< Allocation manager of blocks of draw commands.
         InstanceAllocationManager _instanceAllocationManager;  ///< Allocation manager of instances.
         ItemAllocationManager _transformationAllocationManager;
         //ChunkAllocationManager _transformationGraphAllocationManager;
         ItemAllocationManager _instancingMatricesControlAllocationManager;
         BlockAllocationManager<InstancingMatrices> _instancingMatrixAllocationManager;

         unsigned _indirectBufferAllocatedSpace4;
         void* _mappedStateSetBufferPtr;
         MappedBufferAccess _stateSetBufferMappedAccess;
         void* _mappedDrawCommandBufferPtr;
         MappedBufferAccess _drawCommandBufferMappedAccess;
         void* _mappedInstanceBufferPtr;
         MappedBufferAccess _instanceBufferMappedAccess;
         void* _mappedInstancingMatricesControlBufferPtr;
         MappedBufferAccess _instancingMatricesControlBufferMappedAccess;
         void* _mappedInstancingMatrixBufferPtr;
         MappedBufferAccess _instancingMatrixBufferMappedAccess;

         static bool _initialUseARBShaderDrawParametersValue;
         static int _initialStateSetBufferNumElements;
         static int _initialDrawCommandBufferSize;
         static int _initialInstanceBufferNumElements;
         static int _initialIndirectCommandBufferSize;
         static int _initialTransformationBufferSize;
         static int _initialInstancingMatricesControlBufferNumElements;
         static int _initialInstancingMatricesBufferSize;

         static void* mapBuffer(ge::gl::BufferObject *buffer,
                                MappedBufferAccess requestedAccess,
                                void* &_mappedBufferPtr,
                                MappedBufferAccess &grantedAccess);
         static void unmapBuffer(ge::gl::BufferObject *buffer,
                                 void* &mappedBufferPtr,
                                 MappedBufferAccess &currentAccess);

      public:

         static const float identityMatrix[16];
         inline const std::shared_ptr<InstancingMatrices>& identityInstancingMatrix() const;

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
	 
         inline ge::gl::BufferObject* drawCommandBuffer();      ///< Returns the buffer containing draw commands of this graphics context. Any modification to the buffer must be done carefully to not break internal data consistency.
         inline ge::gl::BufferObject* instanceBuffer();         ///< Returns the buffer containing instances. Any modification to the buffer must be done carefully to not break internal data consistency.
         inline ge::gl::BufferObject* indirectCommandBuffer();  ///< Returns indirect command buffer used for indirect rendering.
         inline ge::gl::BufferObject* stateSetBuffer();         ///< Returns the buffer containing StateSet specific data.
         inline float* cpuTransformationBuffer();
         inline ge::gl::BufferObject* instancingMatricesControlBuffer();
         inline ge::gl::BufferObject* transformationThreadsData();
         inline ge::gl::BufferObject* instancingMatrixBuffer();

         inline void* mapStateSetBuffer(MappedBufferAccess access=MappedBufferAccess::READ_WRITE);
         inline void* mappedStateSetBufferPtr() const;
         inline void unmapStateSetBuffer();
         inline void* mapDrawCommandBuffer(MappedBufferAccess access=MappedBufferAccess::READ_WRITE);
         inline void* mappedDrawCommandBufferPtr() const;
         inline void unmapDrawCommandBuffer();
         inline void* mapInstanceBuffer(MappedBufferAccess access=MappedBufferAccess::READ_WRITE);
         inline void* mappedInstanceBufferPtr() const;
         inline void unmapInstanceBuffer();
         inline void* mapInstancingMatricesControlBuffer(MappedBufferAccess access=MappedBufferAccess::READ_WRITE);
         inline void* mappedInstancingMatricesControlBufferPtr() const;
         inline void unmapInstancingMatricesControlBuffer();
         inline void* mapInstancingMatrixBuffer(MappedBufferAccess access=MappedBufferAccess::READ_WRITE);
         inline void* mappedInstancingMatrixBufferPtr() const;
         inline void unmapInstancingMatrixBuffer();

         inline unsigned* stateSetBufferAllocation(unsigned id) const;
         inline ItemAllocationManager& stateSetBufferAllocationManager();
         inline const ItemAllocationManager& stateSetBufferAllocationManager() const;
         unsigned allocStateSetBufferItem();
         void freeStateSetBufferItem(unsigned id);

         inline ChunkAllocation<Mesh>& drawCommandAllocation(unsigned id);
         inline const ChunkAllocation<Mesh>& drawCommandAllocation(unsigned id) const;
         inline ChunkAllocationManager<Mesh>& drawCommandAllocationManager();
         inline const ChunkAllocationManager<Mesh>& drawCommandAllocationManager() const;

         inline InstanceData* instanceAllocation(unsigned id) const;
         inline ItemAllocationManager& instanceAllocationManager();
         inline const ItemAllocationManager& instanceAllocationManager() const;

         inline unsigned* transformationAllocation(unsigned id) const;
         inline ItemAllocationManager& transformationAllocationManager();
         inline const ItemAllocationManager& transformationAllocationManager() const;

         inline unsigned* instancingMatricesControlAllocation(unsigned id) const;
         inline ItemAllocationManager& instancingMatricesControlAllocationManager();
         inline const ItemAllocationManager& instancingMatricesControlAllocationManager() const;

         inline BlockAllocation<InstancingMatrices>& instancingMatrixAllocation(unsigned id);
         inline const BlockAllocation<InstancingMatrices>& instancingMatrixAllocation(unsigned id) const;
         inline BlockAllocationManager<InstancingMatrices>& instancingMatrixAllocationManager();
         inline const BlockAllocationManager<InstancingMatrices>& instancingMatrixAllocationManager() const;

         virtual bool allocDrawCommands(Mesh &mesh,unsigned size);
         virtual bool reallocDrawCommands(Mesh &mesh,int newSize,
                                          bool preserveContent=true);
         virtual void freeDrawCommands(Mesh &mesh);

         virtual void uploadPreprocessedDrawCommands(Mesh &mesh,
                                                     const void *drawCommandBuffer,
                                                     unsigned bytesToCopy,unsigned dstOffset=0);
         virtual void setDrawCommandControlData(Mesh &mesh,
                                                const Mesh::DrawCommandControlData *data,
                                                int numDrawCommands,unsigned startIndex=0,
                                                bool truncate=true);
         static void preprocessDrawCommands(Mesh &mesh,
                                            void *drawCommandBuffer,
                                            const Mesh::DrawCommandControlData *data,
                                            int numDrawCommands);
         static std::vector<Mesh::DrawCommandControlData> generateDrawCommandControlData(
                                            const void *drawCommandBuffer,
                                            const unsigned *modesAndOffsets4,int numDrawCommands);

         virtual void uploadDrawCommands(Mesh &mesh,
                                         void *nonConstDrawCommandBuffer,unsigned bytesToCopy,
                                         const Mesh::DrawCommandControlData *data,
                                         int numDrawCommands);
         inline void uploadDrawCommands(Mesh &mesh,
                                        void *nonConstDrawCommandBuffer,unsigned bytesToCopy,
                                        const unsigned *modesAndOffsets4,int numDrawCommands);

         inline  void clearDrawCommands(Mesh &mesh);
         virtual void setNumDrawCommands(Mesh &mesh,unsigned num);

         inline InstanceGroupId createInstances(Mesh &mesh,
                                                InstancingMatrices *im,StateSet *stateSet);
         virtual InstanceGroupId createInstances(Mesh &mesh,
                                                 const unsigned *drawCommandIndices,
                                                 const int drawCommandsCount,
                                                 InstancingMatrices *im,StateSet *stateSet);
         virtual void deleteInstances(Mesh &mesh,InstanceGroupId id);

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

         static inline bool initialUseARBShaderDrawParametersValue();
         static inline void setInitialUseARBShaderDrawParametersValue(bool value);
         static inline int initialStateSetBufferNumElements();
         static inline void setInitialStateSetBufferNumElements(int value);
         static inline int initialDrawCommandBufferSize();
         static inline void setInitialDrawCommandBufferSize(int value);
         static inline int initialInstanceBufferNumElements();
         static inline void setInitialInstanceBufferNumElements(int value);
         static inline int initialIndirectCommandBufferSize();
         static inline void setInitialIndirectCommandBufferSize(int value);
         static inline int initialTransformationBufferSize();
         static inline void setInitialTransformationBufferSize(int value);
         static inline int initialInstancingMatricesControlBufferNumElements();
         static inline void setInitialInstancingMatricesControlBufferNumElements(int value);
         static inline int initialInstancingMatricesBufferSize();
         static inline void setInitialInstancingMatricesBufferSize(int value);

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
         static thread_local AutoInitRenderingContext _currentContext;
      };


      static ge::core::InitAndFinalize<RenderingContext> renderingContextInitAndFinalize;


      inline RenderingContext::MappedBufferAccess& operator|=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b);
      inline RenderingContext::MappedBufferAccess& operator&=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b);
      inline RenderingContext::MappedBufferAccess& operator+=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b);
      inline RenderingContext::MappedBufferAccess& operator-=(RenderingContext::MappedBufferAccess &a,RenderingContext::MappedBufferAccess b);
   }
}



// inline methods
//
// note: they need their own includes that can not be placed on the beginning of this file
//       as there is a circular include reference and the classes need to be defined before
//       inline methods to avoid incomplete type compiler error
#include <geRG/InstancingMatrices.h>

namespace ge
{
   namespace rg
   {
      inline const std::shared_ptr<InstancingMatrices>& RenderingContext::identityInstancingMatrix() const
      { if(_identityInstancingMatrix==nullptr) const_cast<RenderingContext*>(this)->_identityInstancingMatrix=std::make_shared<InstancingMatrices>(0,0); return _identityInstancingMatrix; }
      inline const RenderingContext::AttribConfigList& RenderingContext::attribConfigList()  { return _attribConfigList; }
      inline AttribConfigRef RenderingContext::getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo)
      { return getAttribConfig(attribTypes,ebo,AttribConfig::getId(attribTypes,ebo)); }
      inline AttribConfigRef RenderingContext::getAttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,AttribConfigId id)
      { return getAttribConfig(AttribConfig::ConfigData(attribTypes,ebo,id)); }
      inline bool RenderingContext::useARBShaderDrawParameters() const  { return _useARBShaderDrawParameters; }
      inline unsigned RenderingContext::numAttribStorages() const  { return _numAttribStorages; }
      inline ge::gl::BufferObject* RenderingContext::drawCommandBuffer()  { return _drawCommandBuffer; }
      inline ge::gl::BufferObject* RenderingContext::instanceBuffer()  { return _instanceBuffer; }
      inline ge::gl::BufferObject* RenderingContext::indirectCommandBuffer()  { return _indirectCommandBuffer; }
      inline ge::gl::BufferObject* RenderingContext::stateSetBuffer()  { return _stateSetBuffer; }
      inline float* RenderingContext::cpuTransformationBuffer()  { return _cpuTransformationBuffer; }
      inline ge::gl::BufferObject* RenderingContext::instancingMatricesControlBuffer() { return _instancingMatricesControlBuffer; }
      inline ge::gl::BufferObject* RenderingContext::transformationThreadsData()  { return _transformationThreadsData; }
      inline ge::gl::BufferObject* RenderingContext::instancingMatrixBuffer()  { return _instancingMatrixBuffer; }
      inline void* RenderingContext::mapStateSetBuffer(MappedBufferAccess access)
      { return mapBuffer(_stateSetBuffer,access,_mappedStateSetBufferPtr,_stateSetBufferMappedAccess); }
      inline void* RenderingContext::mappedStateSetBufferPtr() const  { return _mappedStateSetBufferPtr; }
      inline void RenderingContext::unmapStateSetBuffer()
      { unmapBuffer(_stateSetBuffer,_mappedStateSetBufferPtr,_stateSetBufferMappedAccess); }
      inline void* RenderingContext::mapDrawCommandBuffer(MappedBufferAccess access)
      { return mapBuffer(_drawCommandBuffer,access,_mappedDrawCommandBufferPtr,_drawCommandBufferMappedAccess); }
      inline void* RenderingContext::mappedDrawCommandBufferPtr() const  { return _mappedDrawCommandBufferPtr; }
      inline void RenderingContext::unmapDrawCommandBuffer()
      { unmapBuffer(_drawCommandBuffer,_mappedDrawCommandBufferPtr,_drawCommandBufferMappedAccess); }
      inline void* RenderingContext::mapInstanceBuffer(MappedBufferAccess access)
      { return mapBuffer(_instanceBuffer,access,_mappedInstanceBufferPtr,_instanceBufferMappedAccess); }
      inline void* RenderingContext::mappedInstanceBufferPtr() const  { return _mappedInstanceBufferPtr; }
      inline void RenderingContext::unmapInstanceBuffer()
      { unmapBuffer(_instanceBuffer,_mappedInstanceBufferPtr,_instanceBufferMappedAccess); }
      inline void* RenderingContext::mapInstancingMatricesControlBuffer(MappedBufferAccess access)
      { return mapBuffer(_instancingMatricesControlBuffer,access,_mappedInstancingMatricesControlBufferPtr,_instancingMatricesControlBufferMappedAccess); }
      inline void* RenderingContext::mappedInstancingMatricesControlBufferPtr() const  { return _mappedInstancingMatricesControlBufferPtr; }
      inline void RenderingContext::unmapInstancingMatricesControlBuffer()  { unmapBuffer(_instancingMatricesControlBuffer,_mappedInstancingMatricesControlBufferPtr,_instancingMatricesControlBufferMappedAccess); }
      inline void* RenderingContext::mapInstancingMatrixBuffer(MappedBufferAccess access)
      { return mapBuffer(_instancingMatrixBuffer,access,_mappedInstancingMatrixBufferPtr,_instancingMatrixBufferMappedAccess); }
      inline void* RenderingContext::mappedInstancingMatrixBufferPtr() const  { return _mappedInstancingMatrixBufferPtr; }
      inline void RenderingContext::unmapInstancingMatrixBuffer()  { unmapBuffer(_instancingMatrixBuffer,_mappedInstancingMatrixBufferPtr,_instancingMatrixBufferMappedAccess); }
      inline unsigned* RenderingContext::stateSetBufferAllocation(unsigned id) const  { return _stateSetBufferAllocationManager[id]; }
      inline ItemAllocationManager& RenderingContext::stateSetBufferAllocationManager()  { return _stateSetBufferAllocationManager; }
      inline const ItemAllocationManager& RenderingContext::stateSetBufferAllocationManager() const  { return _stateSetBufferAllocationManager; }
      inline ChunkAllocation<Mesh>& RenderingContext::drawCommandAllocation(unsigned id)  { return _drawCommandAllocationManager[id]; }
      inline const ChunkAllocation<Mesh>& RenderingContext::drawCommandAllocation(unsigned id) const  { return _drawCommandAllocationManager[id]; }
      inline ChunkAllocationManager<Mesh>& RenderingContext::drawCommandAllocationManager()  { return _drawCommandAllocationManager; }
      inline const ChunkAllocationManager<Mesh>& RenderingContext::drawCommandAllocationManager() const  { return _drawCommandAllocationManager; }
      inline InstanceData* RenderingContext::instanceAllocation(unsigned id) const  { return _instanceAllocationManager[id]; }
      inline ItemAllocationManager& RenderingContext::instanceAllocationManager()  { return _instanceAllocationManager; }
      inline const ItemAllocationManager& RenderingContext::instanceAllocationManager() const  { return _instanceAllocationManager; }
      inline unsigned* RenderingContext::transformationAllocation(unsigned id) const  { return _transformationAllocationManager[id]; }
      inline ItemAllocationManager& RenderingContext::transformationAllocationManager()  { return _transformationAllocationManager; }
      inline const ItemAllocationManager& RenderingContext::transformationAllocationManager() const  { return _transformationAllocationManager; }
      inline BlockAllocation<InstancingMatrices>& RenderingContext::instancingMatrixAllocation(unsigned id)  { return _instancingMatrixAllocationManager[id]; }
      inline unsigned* RenderingContext::instancingMatricesControlAllocation(unsigned id) const  { return _instancingMatricesControlAllocationManager[id]; }
      inline ItemAllocationManager& RenderingContext::instancingMatricesControlAllocationManager()  { return _instancingMatricesControlAllocationManager; }
      inline const ItemAllocationManager& RenderingContext::instancingMatricesControlAllocationManager() const  { return _instancingMatricesControlAllocationManager; }
      inline const BlockAllocation<InstancingMatrices>& RenderingContext::instancingMatrixAllocation(unsigned id) const  { return _instancingMatrixAllocationManager[id]; }
      inline BlockAllocationManager<InstancingMatrices>& RenderingContext::instancingMatrixAllocationManager()  { return _instancingMatrixAllocationManager; }
      inline const BlockAllocationManager<InstancingMatrices>& RenderingContext::instancingMatrixAllocationManager() const  { return _instancingMatrixAllocationManager; }
      inline void RenderingContext::uploadDrawCommands(Mesh &mesh,void *nonConstDrawCommandBuffer,unsigned bytesToCopy,const unsigned *modesAndOffsets4,int numDrawCommands)
      { uploadDrawCommands(mesh,nonConstDrawCommandBuffer,bytesToCopy,generateDrawCommandControlData(nonConstDrawCommandBuffer,modesAndOffsets4,numDrawCommands).data(),numDrawCommands); }
      inline void RenderingContext::clearDrawCommands(Mesh &mesh)  { setNumDrawCommands(mesh,0); }
      inline InstanceGroupId RenderingContext::createInstances(Mesh &mesh,InstancingMatrices *im,StateSet *stateSet)
      { return createInstances(mesh,nullptr,-1,im,stateSet); }
      inline RenderingContext::TransformationGraphList& RenderingContext::transformationGraphs()  { return _transformationGraphs; }
      inline const RenderingContext::TransformationGraphList& RenderingContext::transformationGraphs() const  { return _transformationGraphs; }
      inline unsigned RenderingContext::positionInIndirectBuffer4() const  { return _indirectBufferAllocatedSpace4; }
      inline void RenderingContext::setPositionInIndirectBuffer4(unsigned pos)  { _indirectBufferAllocatedSpace4=pos; }
      inline bool RenderingContext::initialUseARBShaderDrawParametersValue()  { return _initialUseARBShaderDrawParametersValue; }
      inline void RenderingContext::setInitialUseARBShaderDrawParametersValue(bool value)  { _initialUseARBShaderDrawParametersValue=value; }
      inline int RenderingContext::initialStateSetBufferNumElements()  { return _initialStateSetBufferNumElements; }
      inline void RenderingContext::setInitialStateSetBufferNumElements(int value)  { _initialStateSetBufferNumElements=value; }
      inline int RenderingContext::initialDrawCommandBufferSize()  { return _initialDrawCommandBufferSize; }
      inline void RenderingContext::setInitialDrawCommandBufferSize(int value)  { _initialDrawCommandBufferSize=value; }
      inline int RenderingContext::initialInstanceBufferNumElements()  { return _initialInstanceBufferNumElements; }
      inline void RenderingContext::setInitialInstanceBufferNumElements(int value)  { _initialInstanceBufferNumElements=value; }
      inline int RenderingContext::initialIndirectCommandBufferSize()  { return _initialIndirectCommandBufferSize; }
      inline void RenderingContext::setInitialIndirectCommandBufferSize(int value)  { _initialIndirectCommandBufferSize=value; }
      inline int RenderingContext::initialTransformationBufferSize()  { return _initialTransformationBufferSize; }
      inline void RenderingContext::setInitialTransformationBufferSize(int value)  { _initialTransformationBufferSize=value; }
      inline int RenderingContext::initialInstancingMatricesControlBufferNumElements()  { return _initialInstancingMatricesControlBufferNumElements; }
      inline void RenderingContext::setInitialInstancingMatricesControlBufferNumElements(int value)  { _initialInstancingMatricesControlBufferNumElements=value; }
      inline int RenderingContext::initialInstancingMatricesBufferSize()  { return _initialInstancingMatricesBufferSize; }
      inline void RenderingContext::setInitialInstancingMatricesBufferSize(int value)  { _initialInstancingMatricesBufferSize=value; }
      inline std::shared_ptr<RenderingContext>& RenderingContext::current()
      { return _currentContext.get(); }

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
