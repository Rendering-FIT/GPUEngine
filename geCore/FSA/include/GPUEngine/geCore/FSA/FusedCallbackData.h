#pragma once

#include<vector>
#include<GPUEngine/geCore/FSA/fsa_export.h>

namespace ge{
  namespace core{
    class FSA;
    class FSA_EXPORT FSACallback{
      public:
        typedef void(*Fce)(FSA*,void*);
        FSACallback(Fce fce = nullptr,void*data = nullptr);
        virtual ~FSACallback();
        Fce   const& getFce ()const;
        void* const& getData()const;
        bool operator==(FSACallback const&other)const;
        bool operator< (FSACallback const&other)const;
        void operator()(FSA*fsa);
      protected:
        Fce   _fce ;
        void* _data;
    };

    class FSAFusedCallback{
      public:
        FSAFusedCallback();
        FSAFusedCallback(FSACallback const&callback);
        FSAFusedCallback(FSAFusedCallback const&a,FSAFusedCallback const&b);
        void operator()(FSA*fsa)const;
        bool operator==(FSAFusedCallback const&other)const;
        bool operator!=(FSAFusedCallback const&other)const;
      protected:
        std::vector<FSACallback>_callbacks;
    };
  }
}
