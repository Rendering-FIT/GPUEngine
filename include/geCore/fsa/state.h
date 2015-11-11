#pragma once

#include<map>
#include<geCore/Export.h>
#include<geCore/fsa/transition.h>

namespace ge{
  namespace core{
    class FSA;
    class GECORE_EXPORT State{
      private:
        std::string              _name          ;
        std::map<char,Transition>_transitions   ;
        Transition               _elseTransition;
        Transition               _eofTransition ;
      public:
        State(std::string name);
        virtual ~State();
        void addTransition(
            char         lex               ,
            State*       state    = nullptr,
            RuleCallback callback = nullptr,
            void*        data     = nullptr);
        void addElseTransition(
            State*       state    = nullptr,
            RuleCallback callback = nullptr,
            void*        data     = nullptr);
        void addEOFTransition(
            State*       state    = nullptr,
            RuleCallback callback = nullptr,
            void*        data     = nullptr);
        void setCallback    (char lex,RuleCallback callback = nullptr,void* data = nullptr);
        void setElseCallback(         RuleCallback callback = nullptr,void* data = nullptr);
        void setEOFCallback (         RuleCallback callback = nullptr,void* data = nullptr);
        Transition const&getTransition    (char lex)const;
        Transition const&getElseTransition(        )const;
        Transition const&getEOFTransition (        )const;
        void       clearTransitions   ();
        void       clearElseTransition();
        void       clearEofTransition ();
        std::string getName()const;
        unsigned   getNofTransition()const;
        char       getTransitionLex(unsigned i)const;
        void       setEndState    (char lex,State*state = nullptr);
        void       setElseEndState(         State*state = nullptr);
        void       setEOFEndState (         State*state = nullptr);
        State*     apply(char lex,FSA*fsa);
        bool       hasElseTransition()const;
        bool       hasEOFTransition()const;
        bool       hasTransition(char lex)const;
        std::string toStr()const;
        typedef std::map<char,Transition>::const_iterator Iterator;
        Iterator begin()const;
        Iterator end  ()const;
    };
  }
}
