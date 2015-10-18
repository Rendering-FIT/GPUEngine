#pragma once

#include<iostream>

namespace ge{
  namespace core{
    class FSA;
    typedef void(*RuleCallback)(FSA*,void*);
    class State;
    class Transition{
      private:
        State*       _nextState   ;
        RuleCallback _callback    ;
        void*        _callbackData;
      public:
        Transition(
            State*       state        = NULL,
            RuleCallback callback     = NULL,
            void*        callbackData = NULL);
        void setCallback(RuleCallback callback=NULL,void* callbackData=NULL);
        State*       getNextState   (           );
        void         setNextState   (State*state = NULL);
        RuleCallback getCallback    (           );
        void*        getCallbackData(           );
        void         callCallback   (FSA*fsa    );
        std::string  toStr          (           );
    };
  }
}
