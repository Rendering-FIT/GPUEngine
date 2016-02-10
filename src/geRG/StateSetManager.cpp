#include <cassert>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <geRG/FlexibleUniform.h>
#include <geRG/StateSet.h>
#include <geRG/StateSetManager.h>

using namespace std;
using namespace ge::rg;


void StateSetDefaultGLState::set(const string& name,const type_index& typeIndex,void* data)
{
   if(name=="colorTexture") {
      if(typeIndex==type_index(typeid(shared_ptr<ge::gl::TextureObject>*)))
         colorTexture=*static_cast<shared_ptr<ge::gl::TextureObject>*>(data);
      else if(typeIndex==type_index(typeid(weak_ptr<ge::gl::TextureObject>*)))
         colorTexture=*static_cast<weak_ptr<ge::gl::TextureObject>*>(data);
      else
         cout<<"StateSetDefaultGLState::set() error: Unsupported parameter typeIndex for\n"
               "   \"colorTexture\" name."<<endl;
   }
   else if(name=="internal") {
      if(typeIndex==type_index(typeid(bool)))
         internal=(data!=nullptr);
      else
         cout<<"StateSetDefaultGLState::set() error: Unsupported parameter typeIndex for\n"
               "   \"internal\" name."<<endl;
   }
   else
      cout<<"StateSetDefaultGLState::set() error: Unknown parameter name \""<<name<<"\"."<<endl;
}


void StateSetDefaultGLState::init(const std::shared_ptr<StateSet>& ss,StateSetManager *m) const
{
   // test colorTexture for null
   // (expired() is not really testing for expiring here, it tests just for null or non-null value)
   if(colorTexture.expired())
   {
      // append as a child of the root state set
      m->root()->addChild(ss);

      // append uniform indicating "no texturing"
      ss->clearCommands();
      ss->addCommand(make_shared<FlexibleUniform1i>("colorTexturingMode",int(0)));
      ss->addRenderCommand();
   }
   else
   {
      if(internal)
      {
         // append "internal" state set as child of root state set
         m->root()->addChild(ss);

         // append uniform indicating "do texturing"
         // to the internal state set
         ss->clearCommands();
         ss->addCommand(make_shared<FlexibleUniform1i>("colorTexturingMode",int(1)));
         ss->addRenderCommand();
      }
      else
      {
         // get internal state set
         // (internal state set role is to switch texturing on)
         auto state=m->createGLState(this);
         state->set("internal",type_index(typeid(bool)),(void*)1);
         auto internalStateSet=m->getOrCreateStateSet(state);
         delete state;

         // append the state set as child of internal state set
         internalStateSet->addChild(ss);

         // create ActiveTexture and BindTexture commands
         ss->clearCommands();
         ss->addCommand(ge::gl::sharedActiveTexture(GL_TEXTURE0));
         auto t=colorTexture.lock();
         assert(t && "StateSetDefaultGLState error: colorTexture was destroyed.");
         ss->addCommand(ge::gl::sharedBindTexture(GL_TEXTURE_2D,t));
      }
   }
}
