#pragma once

#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<GPUEngine/geCore/FSA/fsa_export.h>
#include<GPUEngine/geCore/FSA/Transition.h>
#include<GPUEngine/geCore/FSA/State.h>

namespace ge{
  namespace core{
    class FSAState;
    class FSA_EXPORT FSA{
      public:
        template<typename...Args>
          FSA(std::string start,Args... args);
        FSA(std::string start = "");
        virtual ~FSA();
        void addTransition(
            std::string      stateA            ,
            std::string      lex               ,
            std::string      stateB            ,
            FSACallback::Fce callback = nullptr,
            void*            data     = nullptr);
        bool run              (std::string text);
        bool runWithPause     (std::string text);
        bool unpause          (std::string text);
        bool stop             (std::string text);
        bool runDebug         (std::string text);
        bool runWithPauseDebug(std::string text);
        bool unpauseDebug     (std::string text);
        bool stopDebug        (std::string text);

        char        getCurrentChar      ()const;
        std::string getAlreadyReadString()const;
        std::string getCurrentStateName ()const;
        unsigned    getCurrentPosition  ()const;
        void        goBack();
        std::string toStr()const;
        void minimalize();
        void removeUnreachableStates();
        void removeUndistinguishabeStates();
        FSA operator+(FSA const&other)const;
        FSA operator*(FSA const&other)const;
        typedef std::map<std::string,FSAState*>::const_iterator Iterator;
        Iterator begin()const;
        Iterator end  ()const;
        static const std::string els  ;
        static const std::string eof  ;
        static const std::string digit;
        static const std::string range;
        static const std::string all  ;
        static const std::string space;
      private:
        std::string                    _start            = "";
        std::set<FSAState*>            _endStates            ;
        std::map<std::string,FSAState*>_name2State           ;
        std::map<std::string,FSACallback::Fce>_state2MessageFce ;
        std::map<std::string,void*>           _state2MessageData;
        std::string                    _alreadyRead      = "";
        char                           _currentChar      = 0 ;
        FSAState*                      _currentState     = nullptr;
        unsigned                       _currentPosition  = 0 ;
        std::string::size_type         _previousLength   = 0 ;
        std::string                    _previousString   = "";

        void _initRun();
        FSAState*_addState (std::string name,bool end=false);
        FSAState*_getState (std::string name)const;
        std::string _expandLex(std::string lex )const;
        bool _createStates(FSAState**sa,FSAState**sb,std::string nameA,std::string nameB,bool end = false);
        void _computeEndStates();

        void _addTransition(
            std::string      stateA            ,
            char             lex               ,
            std::string      stateB            ,
            FSACallback::Fce callback = nullptr,
            void*            data     = nullptr);
        void _addAllTransition(
            std::string      stateA            ,
            std::string      stateB            ,
            FSACallback::Fce callback = nullptr,
            void*            data     = nullptr);
        void _addElseTransition(
            std::string      stateA            ,
            std::string      stateB            ,
            FSACallback::Fce callback = nullptr,
            void*            data     = nullptr);
        void _addEOFTransition(
            std::string      stateA            ,
            std::string      stateB            ,
            FSACallback::Fce callback = nullptr,
            void*            data     = nullptr);
        void _addTransition(
            std::string            stateA  ,
            char                   lex     ,
            std::string            stateB  ,
            FSAFusedCallback const&callback);
        void _addTransition(
            std::string            stateA  ,
            std::string            lex     ,
            std::string            stateB  ,
            FSAFusedCallback const&callback);
        void _addAllTransition(
            std::string            stateA  ,
            std::string            stateB  ,
            FSAFusedCallback const&callback);
        void _addElseTransition(
            std::string            stateA  ,
            std::string            stateB  ,
            FSAFusedCallback const&callback);
        void _addEOFTransition(
            std::string            stateA  ,
            std::string            stateB  ,
            FSAFusedCallback const&callback);

        template<typename...Args>
        void _processArgs(std::string,std::string,std::string,FSACallback::Fce c=nullptr,void*d=nullptr);
        template<typename...Args>
        void _processArgs(std::string,std::string,std::string,FSACallback::Fce,void*,Args...);
        template<typename...Args>
        void _processArgs(std::string,std::string,std::string,FSACallback::Fce,std::string,Args...);
        template<typename...Args>
        void _processArgs(std::string,std::string,std::string,std::string,Args...);
    };

    template<typename...Args>
      FSA::FSA(std::string start,Args... args){
        this->_start=start;
        this->_processArgs(args...);
      }
    template<typename...Args>
      void FSA::_processArgs(
          std::string      stateA  ,
          std::string      lex     ,
          std::string      stateB  ,
          FSACallback::Fce callback,
          void*            data    ){
        this->addTransition(stateA,lex,stateB,callback,data);
      }
    template<typename...Args>
      void FSA::_processArgs(
          std::string      stateA  ,
          std::string      lex     ,
          std::string      stateB  ,
          FSACallback::Fce callback,
          void*            data    ,
          Args...          args    ){
        this->_processArgs(stateA,lex,stateB,callback,data);
        this->_processArgs(args...);
      }
    template<typename...Args>
      void FSA::_processArgs(
          std::string      stateA  ,
          std::string      lex     ,
          std::string      stateB  ,
          FSACallback::Fce callback,
          std::string      a0      ,
          Args...          args    ){
        this->_processArgs(stateA,lex,stateB,callback);
        this->_processArgs(a0,args...);
      }
    template<typename...Args>
      void FSA::_processArgs(
          std::string  stateA,
          std::string  lex   ,
          std::string  stateB,
          std::string  a0    ,
          Args...      args  ){
        this->_processArgs(stateA,lex,stateB);
        this->_processArgs(a0,args...);
      }
  }
}
