#include<GPUEngine/geUtil/FPSPrinter.h>
#include<iostream>

using namespace ge::util;

double FPSPrinter::getTimePerFrame(){
  return this->_lastTimePerFrame;
}
double FPSPrinter::getFPS(){
  return this->_lastFPS;
}
FPSPrinter::FPSPrinter(unsigned framesToElapse,bool useSTDPrint){
  this->_framesToElapse = framesToElapse;
  this->_useSTDPrint    = useSTDPrint;
  this->_msCallBack     = NULL;
  this->_msData         = NULL;
  this->_timer = new Timer<float>();
  this->start();
}
void FPSPrinter::setMsCallBack(MSCALLBACK fce,void*data){
  this->_msCallBack = fce;
  this->_msData     = data;
}
FPSPrinter::~FPSPrinter(){
  delete this->_timer;
}
void FPSPrinter::start(){
  this->_elapsedFrames=0;
  this->_lastTimePerFrame=0;
  this->_lastFPS=0;
  this->_timer->reset();
}
void FPSPrinter::endOfFrame(){
  this->_elapsedFrames++;
  if(this->_elapsedFrames==this->_framesToElapse){
    double time=this->_timer->elapsedFromLast();
    this->_lastTimePerFrame=time/this->_framesToElapse;
    this->_lastFPS=this->_framesToElapse/time;
    if(this->_useSTDPrint){
      std::cout<<"fps: "<<this->getFPS()<<std::endl;
      std::cout<<"ms:  "<<this->getTimePerFrame()<<std::endl;
    }
    if(this->_msCallBack){
      this->_msCallBack(this->getTimePerFrame(),this->_msData);
    }
    this->_elapsedFrames=0;
  }
}


