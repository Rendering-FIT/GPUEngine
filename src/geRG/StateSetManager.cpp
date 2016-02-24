#include <cassert>
#include <cstdint>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <geRG/FlexibleUniform.h>
#include <geRG/StateSet.h>
#include <geRG/StateSetManager.h>

using namespace std;
using namespace ge::rg;


StateSetDefaultGLState::StateSetDefaultGLState(const StateSetDefaultGLState& s,unsigned internalLevel)
{
   this->internalLevel=internalLevel;
   bin=s.bin;
   if(internalLevel<=2)
      glProgram=s.glProgram;
   if(internalLevel<=1)
      colorTexture=s.colorTexture;
   if(internalLevel==0)
      uniformList=s.uniformList;
}


void StateSetDefaultGLState::set(const string& name,const type_index& typeIndex,void* data)
{
   if(name=="internalLevel") {
      if(typeIndex==type_index(typeid(unsigned)))
         internalLevel=reinterpret_cast<uintptr_t>(data);
      else
         cout<<"StateSetDefaultGLState::set() error: Unsupported parameter typeIndex for\n"
               "   \"internal\" name."<<endl;
   }
   else if(name=="bin") {
      if(typeIndex==type_index(typeid(int)))
         bin=reinterpret_cast<intptr_t>(data);
      else
         cout<<"StateSetDefaultGLState::set() error: Unsupported parameter typeIndex for\n"
               "   \"bin\" name."<<endl;
   }
   else if(name=="glProgram") {
      if(typeIndex==type_index(typeid(shared_ptr<ge::gl::ProgramObject>*)))
         glProgram=*static_cast<shared_ptr<ge::gl::ProgramObject>*>(data);
      else if(typeIndex==type_index(typeid(weak_ptr<ge::gl::ProgramObject>*)))
         glProgram=*static_cast<weak_ptr<ge::gl::ProgramObject>*>(data);
      else
         cout<<"StateSetDefaultGLState::set() error: Unsupported parameter typeIndex for\n"
               "   \"glProgram\" name."<<endl;
   }
   else if(name=="colorTexture") {
      if(typeIndex==type_index(typeid(shared_ptr<ge::gl::TextureObject>*)))
         colorTexture=*static_cast<shared_ptr<ge::gl::TextureObject>*>(data);
      else if(typeIndex==type_index(typeid(weak_ptr<ge::gl::TextureObject>*)))
         colorTexture=*static_cast<weak_ptr<ge::gl::TextureObject>*>(data);
      else
         cout<<"StateSetDefaultGLState::set() error: Unsupported parameter typeIndex for\n"
               "   \"colorTexture\" name."<<endl;
   }
   else if(name=="uniformList") {
      if(typeIndex==type_index(typeid(list<weak_ptr<ge::core::Command>>*)))
         uniformList.swap(*static_cast<list<weak_ptr<ge::core::Command>>*>(data));
      else if(typeIndex==type_index(typeid(weak_ptr<ge::core::Command>*))) {
         uniformList.clear();
         uniformList.push_back(*static_cast<weak_ptr<ge::core::Command>*>(data));
      } else
         cout<<"StateSetDefaultGLState::set() error: Unsupported parameter typeIndex for\n"
               "   \"uniformList\" name."<<endl;
   }
   else
      cout<<"StateSetDefaultGLState::set() error: Unknown parameter name \""<<name<<"\"."<<endl;
}


void StateSetDefaultGLState::init(const std::shared_ptr<StateSet>& ss,StateSetManager *m) const
{
   if(internalLevel==0)
   {
      // append uniforms
      ss->clearCommands();
      for(auto& u : uniformList) {
         auto uniformCommand=u.lock();
         assert(uniformCommand && "StateSetDefaultGLState error: uniform was destroyed.");
         ss->addCommand(uniformCommand);
      }
      ss->addRenderCommand();

      // get parent state set
      // (the one of internalLevel==1, if there is no texture we ask for internalLevel 2)
      // (colorTexture.expired() is not really testing for expiring here,
      // it tests just for null or non-null value)
      bool hasTexture=colorTexture.expired();
      auto state=m->createGLState(this,hasTexture?2:1);
      auto parent=m->getOrCreateStateSet(state);
      delete state;

      // append the state set as a child of the internal state set (internalLevel 1)
      parent->addChild(ss);
   }
   else if(internalLevel==1)
   {
      // create BindTexture command
      ss->clearCommands();
      if(colorTexture.expired()) {
         auto t=colorTexture.lock();
         assert(t && "StateSetDefaultGLState error: colorTexture was destroyed.");
         ss->addCommand(ge::gl::sharedBindTexture(GL_TEXTURE_2D,t));
      }
      ss->addRenderCommand();

      // get parent state set
      // (the one of internalLevel==2)
      auto state=m->createGLState(this,2);
      auto parent=m->getOrCreateStateSet(state);
      delete state;

      // append the state set as a child of the internal state set (internalLevel 2)
      parent->addChild(ss);
   }
   else if(internalLevel==2)
   {
      // create FlexibleUseProgram command
      ss->clearCommands();
      auto p=glProgram.lock();
      assert(p && "StateSetDefaultGLState error: glProgram was destroyed.");
      ss->addCommand(make_shared<FlexibleUseProgram>(p));
      ss->addRenderCommand();

      // get parent state set
      // (the one of internalLevel==3)
      auto state=m->createGLState(this,3);
      auto parent=m->getOrCreateStateSet(state);
      delete state;

      // append the state set as a child of the internal state set (internalLevel 3)
      parent->addChild(ss);
   }
   else if(internalLevel==3)
   {
      // append the state set as a child of the root state set
      // while ordering state sets according to their bin number (lowest first)
      auto& binMap=static_cast<StateSetDefaultManager*>(m)->binMap();
      auto it=binMap.lower_bound(bin);
      auto insertIt=it!=binMap.end()?it->second:m->root()->childList().end();
      auto childIt=m->root()->insertChild(insertIt,ss);
      static_cast<StateSetDefaultManager*>(m)->binMap().emplace_hint(it,bin,childIt);
   }
}


bool StateSetDefaultGLState::operator<(const StateSetDefaultGLState& rhs) const
{
   if(bin<rhs.bin)  return true;
   if(rhs.bin<bin)  return false;
   if(glProgram.owner_before(rhs.glProgram)) return true;
   if(rhs.glProgram.owner_before(glProgram))  return false;
   if(colorTexture.owner_before(rhs.colorTexture))  return true;
   if(rhs.colorTexture.owner_before(colorTexture))  return false;
   if(uniformList.size()<rhs.uniformList.size())  return true;
   if(rhs.uniformList.size()<uniformList.size())  return false;
   for(auto it1=uniformList.begin(),it2=rhs.uniformList.begin(),e1=uniformList.end();
       it1!=e1; it1++, it2++)
   {
      if(it1->owner_before(*it2))  return true;
      if(it2->owner_before(*it1))  return false;
   }
   return internalLevel<rhs.internalLevel;
}
