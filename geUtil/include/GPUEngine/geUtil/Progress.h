#pragma once

#include<GPUEngine/geUtil/geutil_export.h>
#include<iostream>

namespace ge{
  namespace util{
    class GEUTIL_EXPORT Progress{
      protected:
        unsigned long long _size       ;
        unsigned long long _chunk      ;
        unsigned long long _counter    ;
        unsigned long long _lastChunkId;
        void(*_updateCallBack)(void*,float);
        std::string _defaultName;
        bool _useDefaultCallBack;
      public:
        Progress(unsigned long long size,unsigned long long chunk = 0u);
        void setUpdateCallBack(void(*fce)(void*,float));
        void setDefaultCallBack(std::string name);
        void update(unsigned long long elements=1u,void*data=NULL);
    };
  }
}

