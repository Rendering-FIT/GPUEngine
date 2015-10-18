#pragma once

#include<map>
#include"transition.h"

namespace ge{
  namespace util{
    class FSA;
    class State{
      private:
        const char*              _name          ;
        std::map<char,Transition>_transitions   ;
        Transition               _elseTransition;
        Transition               _eofTransition ;
      public:
        State(const char* name);
        void addTransition(
            char         lex            ,
            State*       state    = NULL,
            RuleCallback callback = NULL,
            void*        data     = NULL);
        void addElseTransition(
            State*       state    = NULL,
            RuleCallback callback = NULL,
            void*        data     = NULL);
        void addEOFTransition(
            State*       state    = NULL,
            RuleCallback callback = NULL,
            void*        data     = NULL);
        void setCallback    (char lex,RuleCallback callback = NULL,void* data = NULL);
        void setElseCallback(         RuleCallback callback = NULL,void* data = NULL);
        void setEOFCallback (         RuleCallback callback = NULL,void* data = NULL);
        Transition&getTransition    (char lex);
        Transition&getElseTransition(        );
        Transition&getEOFTransition (        );
        void       clearTransitions   ();
        void       clearElseTransition();
        void       clearEofTransition ();
        const char* getName();
        unsigned   getNofTransition();
        char       getTransitionLex(unsigned i);
        void       setEndState    (char lex,State*state = NULL);
        void       setElseEndState(         State*state = NULL);
        void       setEOFEndState (         State*state = NULL);
        State*     apply(char lex,FSA*fsa);
        std::string toStr();
    };
  }
}
