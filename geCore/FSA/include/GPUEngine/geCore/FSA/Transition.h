#pragma once

#include<iostream>
#include<GPUEngine/geCore/FSA/fsa_export.h>
#include<GPUEngine/geCore/FSA/FusedCallbackData.h>

namespace ge{
  namespace core{
    class FSA;
    class FSAState;
    class FSA_EXPORT FSATransition{
      public:
        FSATransition(FSAState*state = nullptr,FSAFusedCallback const& callback = FSAFusedCallback());
        virtual ~FSATransition();
        bool operator==(FSATransition const&other)const;
        bool operator!=(FSATransition const&other)const;
        void setCallback(FSAFusedCallback const& callback = FSAFusedCallback());
        FSAState*getNextState()const;
        FSAFusedCallback const&getCallback()const;
        void         callCallback   (FSA*fsa    )const;
        std::string  toStr          (           )const;
        void         setNextState   (FSAState*state = nullptr);
      private:
        FSAState*        _nextState = nullptr;
        FSAFusedCallback _callback           ;
    };
  }
}
