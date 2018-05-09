#ifndef GE_RG_STATE_SET_MANAGER_H
#define GE_RG_STATE_SET_MANAGER_H

#include <list>
#include <map>
#include <memory>
#include <vector>
#include <glm/vec4.hpp>
#include <geRG/Export.h>

namespace std
{
   class type_index;
}
namespace ge
{
   namespace gl
   {
      class Program;
      class Texture;
   }
   namespace rg
   {
      template<class ...ARGS> class FlexibleUniform;
      typedef FlexibleUniform<float,float,float,float> FlexibleUniform4f;
      class MatrixList;
      class StateSet;


      class GERG_EXPORT StateSetManager {
      public:
         class GERG_EXPORT GLState {
         public:
            virtual void set(const std::string& name,const std::type_index& typeIndex,void* data) = 0;
            virtual void add(const std::string& name,const std::type_index& typeIndex,void* data) = 0;
            virtual void clear(const std::string& name) = 0;
            virtual void init(const std::shared_ptr<StateSet>& ss,StateSetManager *m) = 0;
            virtual ~GLState()  {}
         };
         class Light {
         protected:
            glm::vec4 _position;
            std::shared_ptr<ge::core::SharedCommandList> _uniformList;
            std::shared_ptr<FlexibleUniform4f> _positionUniform;
            MatrixList *_matrixList;
         public:
            inline const glm::vec4& position() const;
            inline const std::shared_ptr<ge::core::SharedCommandList>& uniformList() const;
            inline const std::shared_ptr<FlexibleUniform4f>& positionUniform() const;
            inline MatrixList* matrixList() const;
            inline Light(const glm::vec4& position,
                         const std::shared_ptr<FlexibleUniform4f>& positionUniform,
                         const std::shared_ptr<ge::core::SharedCommandList>& uniformList,
                         MatrixList *matrixList);
            inline Light(const Light& other); ///< Copy constructor. Provides shallow object copy, e.g. objects referenced by shared_ptr are not duplicated but shared.
            inline ~Light();

            Light() = delete;
            Light& operator=(const Light&) = delete;
         };
         typedef std::list<Light> LightList;
      protected:
         std::shared_ptr<StateSet> _root;
         LightList _lightList;
      public:
         inline StateSetManager();
         inline StateSetManager(const std::shared_ptr<StateSet>& root);
         virtual void render() = 0;
         inline const std::shared_ptr<StateSet>& root() const;
         inline std::shared_ptr<StateSet>& root();
         inline void setRoot(std::shared_ptr<StateSet>& root);
         virtual std::shared_ptr<StateSet> getOrCreateStateSet(const GLState* state) = 0;
         virtual std::shared_ptr<StateSet> findStateSet(const GLState* state) = 0;
         virtual const std::shared_ptr<StateSet>& getBinStateSet(int bin) = 0;
         virtual GLState* createGLState() = 0;
         virtual GLState* createGLState(const GLState* s) = 0;
         virtual GLState* createGLState(const GLState* s,unsigned internalLevel) = 0;
         inline LightList::iterator addLight(const glm::vec4& position,
                                             const std::shared_ptr<FlexibleUniform4f>& positionUniform,
                                             const std::shared_ptr<ge::core::SharedCommandList>& uniformList,
                                             MatrixList *matrixList);
         inline void removeLight(LightList::iterator it);
         inline LightList& lightList();
         inline const LightList& lightList() const;
      };


      template<typename StateT>
      class StateSetManagerTemplate : public StateSetManager {
      public:
         typedef std::map<StateT,std::weak_ptr<ge::rg::StateSet>> StateSetMap;
         typedef std::map<int,StateSet::ChildList::iterator> BinMap;
      protected:
         StateSetMap _stateSetMap;
         BinMap _binMap;
      public:
         virtual void render() override;
         virtual std::shared_ptr<StateSet> getOrCreateStateSet(const StateSetManager::GLState* state) override;
         inline  std::shared_ptr<StateSet> getOrCreateStateSet(const StateT* state);
         std::shared_ptr<StateSet> getOrCreateStateSet_optimized(StateSetManager::GLState* state);
         virtual std::shared_ptr<StateSet> findStateSet(const GLState* state) override;
         inline  std::shared_ptr<StateSet> findStateSet(const StateT* state);
         virtual const std::shared_ptr<StateSet>& getBinStateSet(int bin) override;
         virtual GLState* createGLState() override;
         virtual GLState* createGLState(const GLState* s) override;
         virtual GLState* createGLState(const GLState* s,unsigned internalLevel) override;
         inline StateSetMap& stateSetMap();
         inline const StateSetMap& stateSetMap() const;
         inline BinMap& binMap();
         inline const BinMap& binMap() const;
      };


      class GERG_EXPORT StateSetDefaultGLState : public StateSetManager::GLState {
      public:
         unsigned internalLevel;
         std::vector<int> binList;
         std::vector<std::weak_ptr<ge::gl::Program>> glProgramList;
         std::vector<std::weak_ptr<ge::gl::Texture>> colorTextureList;
         std::vector<std::list<std::weak_ptr<ge::core::Command>>> uniformSetList;
         inline StateSetDefaultGLState();
         StateSetDefaultGLState(const StateSetDefaultGLState& s,unsigned internalLevel);
         virtual void set(const std::string& name,const std::type_index& typeIndex,void* data) override;
         virtual void add(const std::string& name,const std::type_index& typeIndex,void* data) override;
         virtual void clear(const std::string& name) override;
         bool operator<(const StateSetDefaultGLState& rhs) const;
         virtual void init(const std::shared_ptr<StateSet>& ss,StateSetManager *m) override;
         static void render(StateSet *ambientSs,StateSet *lightPassSs,
                            StateSetManager::LightList &lightList);
      };


      typedef StateSetManagerTemplate<StateSetDefaultGLState> StateSetDefaultManager;

   }
}



// inline and template methods

#include <geRG/MatrixList.h>

namespace ge
{
   namespace rg
   {
      inline const glm::vec4& StateSetManager::Light::position() const  { return _position; }
      inline const std::shared_ptr<ge::core::SharedCommandList>& StateSetManager::Light::uniformList() const  { return _uniformList; }
      inline const std::shared_ptr<FlexibleUniform4f>& StateSetManager::Light::positionUniform() const  { return _positionUniform; }
      inline MatrixList* StateSetManager::Light::matrixList() const  { return _matrixList; }
      inline StateSetManager::Light::Light(const glm::vec4& position,
            const std::shared_ptr<FlexibleUniform4f>& positionUniform,
            const std::shared_ptr<ge::core::SharedCommandList>& uniformList,MatrixList *matrixList)
         : _position(position), _uniformList(uniformList), _positionUniform(positionUniform), _matrixList(matrixList)
      { if(_matrixList) _matrixList->incrementReferenceCounter(); }
      inline StateSetManager::Light::Light(const Light& other)
         : _position(other._position), _uniformList(other._uniformList), _positionUniform(other._positionUniform), _matrixList(other._matrixList)
      { if(_matrixList) _matrixList->incrementReferenceCounter(); }
      inline StateSetManager::Light::~Light()  { if(_matrixList) _matrixList->decrementReferenceCounter(); }

      inline StateSetManager::StateSetManager() : _root(std::make_shared<StateSet>())  { _root->addChild(std::make_shared<StateSet>()); _root->addChild(std::make_shared<StateSet>()); }
      inline StateSetManager::StateSetManager(const std::shared_ptr<StateSet>& root) : _root(root)  {}
      inline const std::shared_ptr<StateSet>& StateSetManager::root() const  { return _root; }
      inline std::shared_ptr<StateSet>& StateSetManager::root()  { return _root; }
      inline void StateSetManager::setRoot(std::shared_ptr<StateSet>& root)  { _root=root; }
      inline StateSetManager::LightList::iterator StateSetManager::addLight(const glm::vec4& position,
            const std::shared_ptr<FlexibleUniform4f>& positionUniform,const std::shared_ptr<ge::core::SharedCommandList>& uniformList,MatrixList *matrixList)
      { return _lightList.emplace(_lightList.end(),position,positionUniform,uniformList,matrixList); }
      inline void StateSetManager::removeLight(LightList::iterator it)  { _lightList.erase(it); }
      inline StateSetManager::LightList& StateSetManager::lightList()  { return _lightList; }
      inline const StateSetManager::LightList& StateSetManager::lightList() const  { return _lightList; }

      template<typename StateT>
      inline std::shared_ptr<StateSet> StateSetManagerTemplate<StateT>::getOrCreateStateSet(const StateT* state)
      { return getOrCreateStateSet(static_cast<StateSetManager::GLState*>(state)); }
      template<typename StateT>
      std::shared_ptr<StateSet> StateSetManagerTemplate<StateT>::getOrCreateStateSet(const StateSetManager::GLState* state)
      {
         StateT tmp(*static_cast<const StateT*>(state));
         return getOrCreateStateSet_optimized(&tmp);
      }
      template<typename StateT>
      std::shared_ptr<StateSet> StateSetManagerTemplate<StateT>::getOrCreateStateSet_optimized(StateSetManager::GLState* state)
      {
         std::weak_ptr<StateSet>& w=_stateSetMap[*static_cast<const StateT*>(state)];
         std::shared_ptr<StateSet> r=w.lock();
         if(!r) {
            r=std::make_shared<StateSet>();
            w=r;
            state->init(r,this);
         }
         return r;
      }
      template<typename StateT>
      inline std::shared_ptr<StateSet> StateSetManagerTemplate<StateT>::findStateSet(const StateT* state)
      { return findStateSet(static_cast<StateSetManager::GLState*>(state)); }
      template<typename StateT>
      std::shared_ptr<StateSet> StateSetManagerTemplate<StateT>::findStateSet(const GLState* state)
      {
         auto it=_stateSetMap.find(*static_cast<const StateT*>(state));
         if(it==_stateSetMap.end())
            return std::shared_ptr<StateSet>();
         auto r=it->second.lock();
         if(!r)
            const_cast<StateSetManagerTemplate<StateT>*>(this)->_stateSetMap.erase(it);
         return r;
      }
      template<typename StateT>
      const std::shared_ptr<StateSet>& StateSetManagerTemplate<StateT>::getBinStateSet(int bin)
      {
#if 1
         return (bin<=0)?_root->childList().front():_root->childList().back();
#else
         auto it=_binMap.find(bin);
         if(it==_binMap.end())
            return std::shared_ptr<StateSet>();
         return *(it->second);
#endif
      }
      template<typename StateT>
      StateSetManager::GLState* StateSetManagerTemplate<StateT>::createGLState()  { return new StateT; }
      template<typename StateT>
      StateSetManager::GLState* StateSetManagerTemplate<StateT>::createGLState(const StateSetManager::GLState* s)  { return new StateT(*dynamic_cast<const StateT*>(s)); }
      template<typename StateT>
      StateSetManager::GLState* StateSetManagerTemplate<StateT>::createGLState(const StateSetManager::GLState* s,unsigned internalLevel)  { return new StateT(*dynamic_cast<const StateT*>(s),internalLevel); }
      template<typename StateT> inline typename StateSetManagerTemplate<StateT>::StateSetMap&
      StateSetManagerTemplate<StateT>::stateSetMap()  { return _stateSetMap; }
      template<typename StateT> inline const typename StateSetManagerTemplate<StateT>::StateSetMap&
      StateSetManagerTemplate<StateT>::stateSetMap() const  { return _stateSetMap; }
      template<typename StateT> inline typename StateSetManagerTemplate<StateT>::BinMap&
      StateSetManagerTemplate<StateT>::binMap()  { return _binMap; }
      template<typename StateT> inline const typename StateSetManagerTemplate<StateT>::BinMap&
      StateSetManagerTemplate<StateT>::binMap() const  { return _binMap; }
      template<typename StateT> void StateSetManagerTemplate<StateT>::render()
      { StateT::render(getBinStateSet(0).get(),getBinStateSet(1).get(),_lightList); }
      inline StateSetDefaultGLState::StateSetDefaultGLState() : internalLevel(0)  {}
   }
}

#endif /* GE_RG_STATE_SET_MANAGER_H */
