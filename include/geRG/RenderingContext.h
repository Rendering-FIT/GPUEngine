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
#include <geRG/Basics.h>
#include <geRG/BufferStorage.h>
#include <geRG/Drawable.h>
#include <geRG/DrawCommand.h>
#include <geRG/Primitive.h>
#include <geRG/StateSet.h>
#include <geRG/StateSetManager.h>
#include <geCore/InitAndFinalize.h>
#include <geCore/idof.h>

namespace ge
{
   namespace gl
   {
      class BufferObject;
      class ProgramObject;
      class TextureObject;
   }
   namespace rg
   {
      class Transformation;


      class DrawCommandStorage : public BufferStorage<DrawCommandAllocationManager,
            DrawCommandGpuData> {
      public:
#if _MSC_VER<1900
         // MSVC 2013 (tested with Update 4 and 5) fails to inherit constructors according to C++11 standard
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
         typedef std::vector<std::shared_ptr<Transformation>> TransformationGraphList;
         enum class MappedBufferAccess : uint8_t { READ=0x1, WRITE=0x2, READ_WRITE=0x3, NO_ACCESS=0x0 };

      protected:

         AttribConfigList _attribConfigList;
         unsigned _numAttribStorages;
         std::shared_ptr<StateSetManager> _stateSetManager;
         std::map<std::string,std::weak_ptr<ge::gl::TextureObject>> _textureCache;
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

         std::vector<std::shared_ptr<StateSet>> _superStateSets;
         std::vector<std::shared_ptr<ge::gl::ProgramObject>> _glPrograms;

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

         inline DrawableId createDrawable(Mesh &mesh,
                                          MatrixList *matrixList,StateSet *stateSet);
         virtual DrawableId createDrawable(Mesh &mesh,
                                           const unsigned *primitiveIndices,
                                           const int primtiveCount,
                                           MatrixList *matrixList,StateSet *stateSet);
         virtual void deleteDrawable(Mesh &mesh,DrawableId id);

         inline TransformationGraphList& transformationGraphs();
         inline const TransformationGraphList& transformationGraphs() const;
         virtual void addTransformationGraph(std::shared_ptr<Transformation>& transformation);
         virtual void removeTransformationGraph(std::shared_ptr<Transformation>& transformation);

         virtual void cancelAllAllocations();
         virtual void handleContextLost();

         inline unsigned positionInIndirectBuffer4() const;
         inline void setPositionInIndirectBuffer4(unsigned pos);

         virtual void init();
         virtual void initDefaultShaders();
         virtual void configureRenderingPipeline();

         virtual void evaluateTransformationGraph();
         virtual void setupRendering();
         virtual void processDrawCommands();
         virtual void fenceSyncGpuComputation();
         virtual void render();
         virtual void frame();

         inline std::shared_ptr<StateSet> getOrCreateStateSet(const StateSetManager::GLState* state);
         inline std::shared_ptr<StateSet> findStateSet(const StateSetManager::GLState* state);
         inline StateSetManager::GLState* createGLState();
         inline const std::shared_ptr<StateSetManager>& stateSetManager();
         void setStateSetManager(const std::shared_ptr<StateSetManager>& stateSetManager);

         inline const std::shared_ptr<StateSet>& getSuperStateSet(idof_t id) const;
         inline void setSuperStateSet(idof_t id,const std::shared_ptr<StateSet>& ss);
         inline const std::shared_ptr<ge::gl::ProgramObject>& getGLProgram(idof_t id) const;
         inline void setGLProgram(idof_t id,const std::shared_ptr<ge::gl::ProgramObject>& p);

         std::shared_ptr<ge::gl::TextureObject> cachedTextureObject(const std::string& path) const;
         inline void addCacheTextureObject(const std::string &path,const std::shared_ptr<ge::gl::TextureObject>& texture);

         static inline const std::shared_ptr<RenderingContext>& current();
         static void setCurrent(const std::shared_ptr<RenderingContext>& ptr);

         static void global_init();
         static void global_finalize();

      protected:
         struct AutoInitRenderingContext {
            bool initialized; // initialized to false if struct is declared static
            bool usingNiftyCounter;
            uint8_t ptr[sizeof(std::shared_ptr<RenderingContext>)];
            inline std::shared_ptr<RenderingContext>& get()  { return reinterpret_cast<std::shared_ptr<RenderingContext>&>(ptr); }
            AutoInitRenderingContext();
            ~AutoInitRenderingContext();
         };
         struct NoExport { // workaround for MSVC 2015: thread_local variables can not have DLL-export interface,
                           // solution: nested structures are not DLL-exported and do not inherit DLL-export of parent class
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
      inline DrawableId RenderingContext::createDrawable(Mesh &mesh,MatrixList *matrixList,StateSet *stateSet)
      { return createDrawable(mesh,nullptr,-1,matrixList,stateSet); }
      inline RenderingContext::TransformationGraphList& RenderingContext::transformationGraphs()  { return _transformationGraphs; }
      inline const RenderingContext::TransformationGraphList& RenderingContext::transformationGraphs() const  { return _transformationGraphs; }
      inline unsigned RenderingContext::positionInIndirectBuffer4() const  { return _indirectBufferAllocatedSpace4; }
      inline void RenderingContext::setPositionInIndirectBuffer4(unsigned pos)  { _indirectBufferAllocatedSpace4=pos; }
      inline const std::shared_ptr<RenderingContext>& RenderingContext::current()
      { return NoExport::_currentContext.get(); }

      inline std::shared_ptr<StateSet> RenderingContext::getOrCreateStateSet(const StateSetManager::GLState* state)
      { return _stateSetManager->getOrCreateStateSet(state); }
      inline std::shared_ptr<StateSet> RenderingContext::findStateSet(const StateSetManager::GLState* state)
      { return _stateSetManager->findStateSet(state); }
      inline StateSetManager::GLState* RenderingContext::createGLState()  { return _stateSetManager->createGLState(); }
      inline const std::shared_ptr<StateSetManager>& RenderingContext::stateSetManager()  { return _stateSetManager; }

      inline const std::shared_ptr<StateSet>& RenderingContext::getSuperStateSet(idof_t id) const  { return (id<_superStateSets.size())?_superStateSets[id]:nullSharedPtr<ge::rg::StateSet>(); }
      inline void RenderingContext::setSuperStateSet(idof_t id,const std::shared_ptr<StateSet>& ss)  { if(_superStateSets.size()<=id) _superStateSets.resize(id+1); _superStateSets[id]=ss; }
      inline const std::shared_ptr<ge::gl::ProgramObject>& RenderingContext::getGLProgram(idof_t id) const  { return (id<_glPrograms.size())?_glPrograms[id]:nullSharedPtr<ge::gl::ProgramObject>(); }
      inline void RenderingContext::setGLProgram(idof_t id,const std::shared_ptr<ge::gl::ProgramObject>& p)  { if(_glPrograms.size()<=id) _glPrograms.resize(id+1); _glPrograms[id]=p; }

      inline void RenderingContext::addCacheTextureObject(const std::string &path,const std::shared_ptr<ge::gl::TextureObject>& texture)  { _textureCache[path]=texture; }

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
