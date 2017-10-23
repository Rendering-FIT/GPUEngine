#include<GPUEngine/geUtil/Progress.h>
#include<iostream>
#include <string>

using namespace ge::util;

Progress::Progress(unsigned long long size,unsigned long long chunk){
  this->_size = size;
  if(chunk == 0u)this->_chunk=this->_size/100u;
  if(this->_chunk==0u)this->_chunk=1u;
  this->_counter            = 0u   ;
  this->_lastChunkId        = 0u   ;
  this->_useDefaultCallBack = false;
  this->_defaultName        = ""   ;
}
void Progress::setUpdateCallBack(void(*fce)(void*,float)){
  this->_updateCallBack     = fce;
  this->_useDefaultCallBack = false;
}
void Progress::setDefaultCallBack(std::string name){
  this->_defaultName        = name;
  this->_useDefaultCallBack = true;
}
void Progress::update(unsigned long long elements,void*data){
  if(this->_counter>=this->_size)return;
  this->_counter += elements;
  if(this->_counter/this->_chunk <= this->_lastChunkId)return;
  this->_lastChunkId = this->_counter/this->_chunk;

  float percent=static_cast<float>(this->_counter)/static_cast<float>(this->_size);
  if(this->_useDefaultCallBack){
    std::cout<<this->_defaultName<<": "<<percent*100<<"%"<<std::endl;
    return;
  }

  if(this->_updateCallBack)this->_updateCallBack(data,percent);
}

