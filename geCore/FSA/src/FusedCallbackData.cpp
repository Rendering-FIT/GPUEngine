#include<GPUEngine/geCore/FSA/FusedCallbackData.h>

using namespace ge::core;

FSACallback::FSACallback(FSACallback::Fce fce,void*data){
  this->_fce  = fce;
  this->_data = data;
}

FSACallback::~FSACallback(){}

FSACallback::Fce const& FSACallback::getFce()const{
  return this->_fce;
}

void* const& FSACallback::getData()const{
  return this->_data;
}

bool FSACallback::operator==(FSACallback const&other)const{
  return this->_fce==other._fce && this->_data == other._data;
}

bool FSACallback::operator<(FSACallback const&other)const{
  return this->_fce<other._fce;
}

void FSACallback::operator()(FSA*fsa){
  if(this->_fce)this->_fce(fsa,this->_data);
}

FSAFusedCallback::FSAFusedCallback(){

}

FSAFusedCallback::FSAFusedCallback(FSACallback const&callback){
  this->_callbacks.push_back(callback);
}

FSAFusedCallback::FSAFusedCallback(FSAFusedCallback const&a,FSAFusedCallback const&b){
  unsigned ai=0,bi=0;
  while(ai<a._callbacks.size()||bi<b._callbacks.size()){
    if(a._callbacks[ai]==b._callbacks[bi]){
      this->_callbacks.push_back(a._callbacks[ai]);
      ai++;
      bi++;
    }else if(a._callbacks[ai]<b._callbacks[bi])
      this->_callbacks.push_back(a._callbacks[ai++]);
    else
      this->_callbacks.push_back(b._callbacks[bi++]);
  }
}

void FSAFusedCallback::operator()(FSA*fsa)const{
  for(auto x:this->_callbacks)
    x(fsa);
}

bool FSAFusedCallback::operator==(FSAFusedCallback const&other)const{
  if(this->_callbacks.size()!=other._callbacks.size())return false;
  for(unsigned i=0;i<this->_callbacks.size();++i)
    if(!(this->_callbacks[i]==other._callbacks[i]))return false;
  return true;
}

bool FSAFusedCallback::operator!=(FSAFusedCallback const&other)const{
  return !(*this==other);
}
