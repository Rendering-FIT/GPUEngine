#pragma once

#include<map>
#include<GPUEngine/geCore/FSA/fsa_export.h>
#include<GPUEngine/geCore/FSA/Transition.h>

namespace ge{
  namespace core{
    class FSA;
    class FSA_EXPORT FSAState{
      private:
        std::string                 _name          ;
        std::map<char,FSATransition>_transitions   ;
        FSATransition               _eofTransition ;
      public:
        FSAState(std::string name);
        virtual ~FSAState();
        void addTransition    (char lex,FSAState*state,FSAFusedCallback callback);
        void addElseTransition(         FSAState*state,FSAFusedCallback callback);
        void addEOFTransition (         FSAState*state,FSAFusedCallback callback);
        void setCallback    (char lex,FSAFusedCallback callback);
        void setElseCallback(         FSAFusedCallback callback);
        void setEOFCallback (         FSAFusedCallback callback);
        FSATransition const&getTransition    (char lex)const;
        FSATransition const&getEOFTransition (        )const;
        void       clearTransitions   ();
        void       clearEofTransition ();
        std::string getName()const;
        decltype(_transitions)::size_type getNofTransition()const;
        char       getTransitionLex(unsigned i)const;
        void       setEndState    (char lex,FSAState*state = nullptr);
        void       setEOFEndState (         FSAState*state = nullptr);
        FSAState*  apply(char lex,FSA*fsa);
        bool       hasEOFTransition (        )const;
        bool       hasTransition    (char lex)const;
        std::string toStr()const;
        typedef std::map<char,FSATransition>::const_iterator Iterator;
        Iterator begin()const;
        Iterator end  ()const;
    };
  }
}
