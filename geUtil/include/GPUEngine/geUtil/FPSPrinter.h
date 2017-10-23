#pragma once

#include<GPUEngine/geUtil/geutil_export.h>
#include<GPUEngine/geUtil/Timer.h>

namespace ge{
  namespace util{
    class GEUTIL_EXPORT FPSPrinter{
      public:
        typedef void(*MSCALLBACK)(double ms,void*data);
      private:
        unsigned _framesToElapse;
        unsigned _elapsedFrames;
        Timer<float>*_timer;
        double     _lastTimePerFrame;
        double     _lastFPS;
        bool       _useSTDPrint;
        void*      _msData;
        MSCALLBACK _msCallBack;
      public:
        double getTimePerFrame();
        double getFPS();
        FPSPrinter(unsigned framesToElapse=100,bool useSTDPrint=true);
        void setMsCallBack(MSCALLBACK fce,void*data=NULL);
        ~FPSPrinter();
        void start();
        void endOfFrame();
    };
  }
}
