#pragma once

#include<iostream>
#include<geCore/Export.h>

namespace ge{
  namespace core{
    class FSA;
    typedef void(*RuleCallback)(FSA*,void*);
    class State;
    class GECORE_EXPORT Transition{
      private:
        State*       _nextState    = nullptr;
        RuleCallback _callback     = nullptr;
        void*        _callbackData = nullptr;
      public:
        Transition(
            State*       state        = nullptr,
            RuleCallback callback     = nullptr,
            void*        callbackData = nullptr);
        virtual ~Transition();
        void setCallback(RuleCallback callback = nullptr,void* callbackData = nullptr);
        State*       getNextState   (           )const;
        RuleCallback getCallback    (           )const;
        void*        getCallbackData(           )const;
        void         callCallback   (FSA*fsa    )const;
        std::string  toStr          (           )const;
        void         setNextState   (State*state = nullptr);
    };
  }
}
