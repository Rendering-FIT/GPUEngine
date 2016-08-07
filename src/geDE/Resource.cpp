#include<geDE/Resource.h>
#include<geDE/Function.h>

using namespace ge::de;

Resource::~Resource(){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  if(this->_producer)
    this->_producer->_removeTargetResource(this);
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

void Resource::setProducer(std::shared_ptr<Function>const&f){
  PRINT_CALL_STACK(f);
  assert(this!=nullptr);
  if(this->_producer==f)return;
  if(this->_producer){
    this->_producer->_removeTargetResource(this);
    this->_removeSignalingSource(&*this->_producer);
  }
  this->_producer = f;
  if(this->_producer){
    this->_producer->_addTargetResource(this);
    this->_addSignalingSource(&*this->_producer);
  }
}

void Resource::operator()(){
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  if(this->_producer)
    (*this->_producer)();
}
