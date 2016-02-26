#include <cassert>
#include <cstdint>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <geRG/FlexibleUniform.h>
#include <geRG/StateSet.h>
#include <geRG/StateSetManager.h>
#include <geCore/Command.h>

using namespace std;
using namespace ge::rg;


void StateSetDefaultGLState::set(const string& name,const type_index& typeIndex,void* data)
{
   clear(name);
   add(name,typeIndex,data);
}


void StateSetDefaultGLState::add(const string& name,const type_index& typeIndex,void* data)
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
         binList.push_back(reinterpret_cast<intptr_t>(data));
      else
         cout<<"StateSetDefaultGLState::set() error: Unsupported parameter typeIndex for\n"
               "   \"bin\" name."<<endl;
   }
   else if(name=="glProgram") {
      if(typeIndex==type_index(typeid(shared_ptr<ge::gl::ProgramObject>*)))
         glProgramList.push_back(*static_cast<shared_ptr<ge::gl::ProgramObject>*>(data));
      else if(typeIndex==type_index(typeid(weak_ptr<ge::gl::ProgramObject>*)))
         glProgramList.push_back(*static_cast<weak_ptr<ge::gl::ProgramObject>*>(data));
      else
         cout<<"StateSetDefaultGLState::set() error: Unsupported parameter typeIndex for\n"
               "   \"glProgram\" name."<<endl;
   }
   else if(name=="colorTexture") {
      if(typeIndex==type_index(typeid(shared_ptr<ge::gl::TextureObject>*)))
         colorTextureList.push_back(*static_cast<shared_ptr<ge::gl::TextureObject>*>(data));
      else if(typeIndex==type_index(typeid(weak_ptr<ge::gl::TextureObject>*)))
         colorTextureList.push_back(*static_cast<weak_ptr<ge::gl::TextureObject>*>(data));
      else
         cout<<"StateSetDefaultGLState::set() error: Unsupported parameter typeIndex for\n"
               "   \"colorTexture\" name."<<endl;
   }
   else if(name=="uniformList") {
      if(typeIndex==type_index(typeid(list<weak_ptr<ge::core::Command>>*))) {
         uniformSetList.emplace_back();
         uniformSetList.back().swap(*static_cast<list<weak_ptr<ge::core::Command>>*>(data));
      } else if(typeIndex==type_index(typeid(weak_ptr<ge::core::Command>*))) {
         uniformSetList.emplace_back();
         uniformSetList.back().push_back(*static_cast<weak_ptr<ge::core::Command>*>(data));
      } else
         cout<<"StateSetDefaultGLState::set() error: Unsupported parameter typeIndex for\n"
               "   \"uniformList\" name."<<endl;
   }
   else
      cout<<"StateSetDefaultGLState::set() error: Unknown parameter name \""<<name<<"\"."<<endl;
}


void StateSetDefaultGLState::clear(const string& name)
{
   if(name=="internalLevel")
      internalLevel=0;
   else if(name=="bin")
      binList.clear();
   else if(name=="glProgram")
      glProgramList.clear();
   else if(name=="colorTexture")
      colorTextureList.clear();
   else if(name=="uniformList")
      uniformSetList.clear();
   else
      cout<<"StateSetDefaultGLState::set() error: Unknown parameter name \""<<name<<"\"."<<endl;
}


StateSetDefaultGLState::StateSetDefaultGLState(const StateSetDefaultGLState& s,unsigned internalLevel)
{
   this->internalLevel=internalLevel;
   binList=s.binList;
   if(internalLevel<=3)
      glProgramList=s.glProgramList;
   if(internalLevel<=2)
      colorTextureList=s.colorTextureList;
   if(internalLevel<=1)
      uniformSetList=s.uniformSetList;
}


void StateSetDefaultGLState::init(const std::shared_ptr<StateSet>& ss,StateSetManager *m)
{
   if(internalLevel==0)
   {
      if(uniformSetList.size()==0) {
         // jump to internalLevel 2 (texture assignment)
         internalLevel=2;
         init(ss,m);
      }
      else if(uniformSetList.size()==1) {
         // skip to internalLevel 1 (uniform assignment)
         internalLevel=1;
         init(ss,m);
      }
      else
      {
         // append to the appropriate uniform state sets
         internalLevel=1;
         decltype(uniformSetList) tmp;
         uniformSetList.swap(tmp);
         uniformSetList.emplace_back();
         for(size_t i=0,c=tmp.size(); i<c; i++)
         {
            // find parent state set
            uniformSetList.front().swap(tmp[i]);
            auto parent=static_cast<StateSetManagerTemplate<StateSetDefaultGLState>*>(m)->
                  getOrCreateStateSet_optimized(this);
            uniformSetList.front().swap(tmp[i]);

            // append the state set as a child of the internal state set
            parent->addChild(ss);
         }
         uniformSetList.swap(tmp);
      }
   }
   else if(internalLevel==1)
   {
      if(uniformSetList.size()==0) {
         internalLevel=2;
         init(ss,m);
      }
      else
      {
         // append uniforms
         ss->clearCommands();
         for(auto& u : uniformSetList.front()) {
            auto uniformCommand=u.lock();
            assert(uniformCommand && "StateSetDefaultGLState error: uniform was destroyed.");
            ss->addCommand(uniformCommand);
         }
         ss->addRenderCommand();

         // store uniformSetList in temporary variable and leave it empty
         // as it should not influence further lookups for parents
         decltype(uniformSetList) savedUniformSetList;
         uniformSetList.swap(savedUniformSetList);

         // get parent state set
         internalLevel=2;
         if(colorTextureList.size()==0) {
            // jump to internalLevel 2
            init(ss,m);
         }
         else if(colorTextureList.size()==1) {
            // append to the parent state set
            auto parent=static_cast<StateSetManagerTemplate<StateSetDefaultGLState>*>(m)->
                  getOrCreateStateSet_optimized(this);
            parent->addChild(ss);
         }
         else
         {
            // append to the appropriate texture state sets
            decltype(colorTextureList) tmp;
            colorTextureList.swap(tmp);
            colorTextureList.emplace_back();
            for(size_t i=0,c=tmp.size(); i<c; i++)
            {
               // find parent state set
               colorTextureList.front().swap(tmp[i]);
               auto parent=static_cast<StateSetManagerTemplate<StateSetDefaultGLState>*>(m)->
                     getOrCreateStateSet_optimized(this);
               colorTextureList.front().swap(tmp[i]);

               // append the state set as a child of the internal state set
               parent->addChild(ss);
            }
            colorTextureList.swap(tmp);
         }

         // restore uniformSetList
         uniformSetList.swap(savedUniformSetList);
      }
   }
   else if(internalLevel==2)
   {
      // (colorTextureList.front().expired() is not really testing for expiring here,
      // it tests just for null value)
      if(colorTextureList.size()==0 || colorTextureList.front().expired()) {
         internalLevel=3;
         init(ss,m);
      }
      else
      {
         // create BindTexture command
         ss->clearCommands();
         auto t=colorTextureList.front().lock();
         assert(t && "StateSetDefaultGLState error: colorTexture was destroyed.");
         ss->addCommand(ge::gl::sharedBindTexture(GL_TEXTURE_2D,t));
         ss->addRenderCommand();

         // store colorTextureList in temporary variable and leave it empty
         // as it should not influence further lookups for parents
         decltype(colorTextureList) savedColorTextureList;
         colorTextureList.swap(savedColorTextureList);

         // get parent state set
         internalLevel=3;
         if(glProgramList.size()==0) {
            // jump to internalLevel 3
            init(ss,m);
         }
         else if(glProgramList.size()==1) {
            // append to the parent state set
            auto parent=static_cast<StateSetManagerTemplate<StateSetDefaultGLState>*>(m)->
                  getOrCreateStateSet_optimized(this);
            parent->addChild(ss);
         }
         else
         {
            // append to the appropriate glProgram state sets
            decltype(glProgramList) tmp;
            glProgramList.swap(tmp);
            glProgramList.emplace_back();
            for(size_t i=0,c=tmp.size(); i<c; i++)
            {
               // find parent state set
               glProgramList.front().swap(tmp[i]);
               auto parent=static_cast<StateSetManagerTemplate<StateSetDefaultGLState>*>(m)->
                     getOrCreateStateSet_optimized(this);
               glProgramList.front().swap(tmp[i]);

               // append the state set as a child of the internal state set
               parent->addChild(ss);
            }
            glProgramList.swap(tmp);
         }

         // restore colorTextureList
         colorTextureList.swap(savedColorTextureList);
      }
   }
   else if(internalLevel==3)
   {
      // (glProgramList.front().expired() is not really testing for expiring here,
      // it tests just for null value)
      if(glProgramList.size()==0 || glProgramList.front().expired()) {
         internalLevel=4;
         init(ss,m);
      }
      else
      {
         // create FlexibleUseProgram command
         ss->clearCommands();
         auto p=glProgramList.front().lock();
         assert(p && "StateSetDefaultGLState error: glProgram was destroyed.");
         ss->addCommand(make_shared<FlexibleUseProgram>(p));
         ss->addRenderCommand();

         // store glProgramList in temporary variable and leave it empty
         // as it should not influence further lookups for parents
         decltype(glProgramList) savedGLProgramList;
         glProgramList.swap(savedGLProgramList);

         // get parent state set
         internalLevel=4;
         if(binList.size()==0) {
            // jump to internalLevel 4
            init(ss,m);
         }
         else if(binList.size()==1) {
            // append to the parent state set
            auto parent=static_cast<StateSetManagerTemplate<StateSetDefaultGLState>*>(m)->
                  getOrCreateStateSet_optimized(this);
            parent->addChild(ss);
         }
         else
         {
            // append to the appropriate bin state sets
            decltype(binList) tmp;
            binList.swap(tmp);
            binList.emplace_back();
            for(size_t i=0,c=tmp.size(); i<c; i++)
            {
               // find parent state set
               binList.front()=tmp[i];
               auto parent=static_cast<StateSetManagerTemplate<StateSetDefaultGLState>*>(m)->
                     getOrCreateStateSet_optimized(this);

               // append the state set as a child of the internal state set
               parent->addChild(ss);
            }
            binList.swap(tmp);
         }

         // restore glProgramList
         glProgramList.swap(savedGLProgramList);
      }
   }
   else if(internalLevel==4)
   {
      if(binList.size()==0) {
         binList.emplace_back(0);
         init(ss,m);
         binList.clear();
      }
      else if(binList.size()==1) {
         // append the state set as a child of the root state set
         // while ordering state sets according to their bin number (lowest first)
         auto& binMap=static_cast<StateSetDefaultManager*>(m)->binMap();
         auto it=binMap.lower_bound(binList.front());
         auto insertIt=it!=binMap.end()?it->second:m->root()->childList().end();
         auto childIt=m->root()->insertChild(insertIt,ss);
         static_cast<StateSetDefaultManager*>(m)->binMap().emplace_hint(it,binList.front(),childIt);
      }
      else
      {
         // append to the appropriate bin state sets
         decltype(binList) tmp;
         binList.swap(tmp);
         binList.emplace_back();
         for(size_t i=0,c=tmp.size(); i<c; i++)
         {
            // find parent state set
            binList.front()=tmp[i];
            auto parent=static_cast<StateSetManagerTemplate<StateSetDefaultGLState>*>(m)->
                  getOrCreateStateSet_optimized(this);

            // append the state set as a child of the internal state set
            parent->addChild(ss);
         }
         binList.swap(tmp);
      }
   }
}


#define COMPARE_LISTS(_l1_,_l2_) \
{ \
   if(_l1_.size()<_l2_.size())  return true; \
   if(_l2_.size()<_l1_.size())  return false; \
   for(auto it1=_l1_.begin(),it2=_l2_.begin(),e1=_l1_.end(); it1!=e1; it1++, it2++) \
   { \
      if((*it1)<(*it2))  return true; \
      if((*it2)<(*it1))  return false; \
   } \
}

#define COMPARE_PTR_LISTS(_l1_,_l2_) \
{ \
   if(_l1_.size()<_l2_.size())  return true; \
   if(_l2_.size()<_l1_.size())  return false; \
   for(auto it1=_l1_.begin(),it2=_l2_.begin(),e1=_l1_.end(); it1!=e1; it1++, it2++) \
   { \
      if(it1->owner_before(*it2))  return true; \
      if(it2->owner_before(*it1))  return false; \
   } \
}

bool StateSetDefaultGLState::operator<(const StateSetDefaultGLState& rhs) const
{
   COMPARE_LISTS(binList,rhs.binList)
   COMPARE_PTR_LISTS(glProgramList,rhs.glProgramList)
   COMPARE_PTR_LISTS(colorTextureList,rhs.colorTextureList)
   if(uniformSetList.size()<rhs.uniformSetList.size())  return true;
   if(rhs.uniformSetList.size()<uniformSetList.size())  return false;
   for(auto it1=uniformSetList.begin(),it2=rhs.uniformSetList.begin(),e1=uniformSetList.end();
       it1!=e1; it1++, it2++)
   {
      if(it1->size()<it2->size())  return true;
      if(it2->size()<it1->size())  return false;
      for(auto it3=it1->begin(),it4=it2->begin(),e3=it1->end();
          it3!=e3; it3++,it4++)
      {
         if(it3->owner_before(*it4))  return true;
         if(it4->owner_before(*it3))  return false;
      }
   }
   return internalLevel<rhs.internalLevel;
}
