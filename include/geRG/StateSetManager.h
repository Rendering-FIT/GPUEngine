#ifndef GE_RG_STATE_SET_MANAGER_H
#define GE_RG_STATE_SET_MANAGER_H

#include <map>
#include <memory>
#include <geRG/Export.h>

namespace std
{
   class type_index;
}
namespace ge
{
   namespace gl
   {
      class TextureObject;
   }
   namespace rg
   {
      class StateSet;


      class GERG_EXPORT StateSetManager {
      public:
         class GERG_EXPORT GLState {
         public:
            virtual void set(const std::string& name,const std::type_index& typeIndex,void* data) = 0;
            virtual void init(const std::shared_ptr<StateSet>& ss,StateSetManager *m) const = 0;
            virtual ~GLState()  {}
         };
      protected:
         std::shared_ptr<StateSet> _root;
      public:
         inline StateSetManager();
         inline StateSetManager(const std::shared_ptr<StateSet>& root);
         inline const std::shared_ptr<StateSet>& root() const;
         inline std::shared_ptr<StateSet>& root();
         inline void setRoot(std::shared_ptr<StateSet>& root);
         virtual std::shared_ptr<StateSet> getOrCreateStateSet(const GLState* state) = 0;
         virtual std::shared_ptr<StateSet> findStateSet(const GLState* state) = 0;
         virtual GLState* createGLState() = 0;
         virtual GLState* createGLState(const GLState* s) = 0;
      };


      template<typename StateT>
      class StateSetManagerTemplate : public StateSetManager {
      public:
         typedef std::map<StateT,std::weak_ptr<ge::rg::StateSet>> StateSetMap;
      protected:
         StateSetMap _stateSetMap;
      public:
         virtual std::shared_ptr<StateSet> getOrCreateStateSet(const StateSetManager::GLState* state) override;
         inline  std::shared_ptr<StateSet> getOrCreateStateSet(const StateT* state);
         virtual std::shared_ptr<StateSet> findStateSet(const GLState* state) override;
         inline  std::shared_ptr<StateSet> findStateSet(const StateT* state);
         virtual GLState* createGLState() override;
         virtual GLState* createGLState(const GLState* s) override;
         inline StateSetMap& stateSetMap();
         inline const StateSetMap& stateSetMap() const;
      };


      class GERG_EXPORT StateSetDefaultGLState : public StateSetManager::GLState {
      public:
         bool internal;
         std::weak_ptr<ge::gl::TextureObject> colorTexture;
         inline StateSetDefaultGLState();
         inline StateSetDefaultGLState(const StateSetDefaultGLState& s);
         virtual void set(const std::string& name,const std::type_index& typeIndex,void* data) override;
         inline bool operator<(const StateSetDefaultGLState& rhs) const;
         virtual void init(const std::shared_ptr<StateSet>& ss,StateSetManager *m) const override;
      };


      typedef StateSetManagerTemplate<StateSetDefaultGLState> StateSetDefaultManager;

   }
}



// inline and template methods

namespace ge
{
   namespace rg
   {
      inline StateSetManager::StateSetManager() : _root(std::make_shared<StateSet>())  {}
      inline StateSetManager::StateSetManager(const std::shared_ptr<StateSet>& root) : _root(root)  {}
      inline const std::shared_ptr<StateSet>& StateSetManager::root() const  { return _root; }
      inline std::shared_ptr<StateSet>& StateSetManager::root()  { return _root; }
      inline void StateSetManager::setRoot(std::shared_ptr<StateSet>& root)  { _root=root; }
      template<typename StateT>
      inline std::shared_ptr<StateSet> StateSetManagerTemplate<StateT>::getOrCreateStateSet(const StateT* state)
      { return getOrCreateStateSet(static_cast<StateSetManager::GLState*>(state)); }
      template<typename StateT>
      std::shared_ptr<StateSet> StateSetManagerTemplate<StateT>::getOrCreateStateSet(const StateSetManager::GLState* state)
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
      StateSetManager::GLState* StateSetManagerTemplate<StateT>::createGLState()  { return new StateT; }
      template<typename StateT>
      StateSetManager::GLState* StateSetManagerTemplate<StateT>::createGLState(const StateSetManager::GLState* s)  { return new StateT(*dynamic_cast<const StateT*>(s)); }
      template<typename StateT> inline typename StateSetManagerTemplate<StateT>::StateSetMap&
      StateSetManagerTemplate<StateT>::stateSetMap()  { return _stateSetMap; }
      template<typename StateT> inline const typename StateSetManagerTemplate<StateT>::StateSetMap&
      StateSetManagerTemplate<StateT>::stateSetMap() const  { return _stateSetMap; }
      inline StateSetDefaultGLState::StateSetDefaultGLState() : internal(false)  {}
      inline StateSetDefaultGLState::StateSetDefaultGLState(const StateSetDefaultGLState& s)
         : internal(s.internal), colorTexture(s.colorTexture)  {}
      inline bool StateSetDefaultGLState::operator<(const StateSetDefaultGLState& rhs) const
      {
         return (colorTexture.owner_before(rhs.colorTexture)) ? true :
                (rhs.colorTexture.owner_before(colorTexture)) ? false :
                internal<rhs.internal;
      }
   }
}

#endif /* GE_RG_STATE_SET_MANAGER_H */
