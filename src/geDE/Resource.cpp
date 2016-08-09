#include<geDE/Resource.h>
#include<geDE/Function.h>

using namespace ge::de;

Resource::~Resource(){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  for(auto const&x:this->_signalingSources)
    x->_removeTargetResource(this);
  for(auto const&x:this->_signalingTargets)
    x->_removeSourceResource(this);
}

void Resource::_setSignalingDirty(){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  for(auto const&x:this->_signalingTargets)
    if(!x->isDirty())
      x->setDirty();
}

