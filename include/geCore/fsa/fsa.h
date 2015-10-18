#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<geCore/geCore.h>

#include<geCore/fsa/transition.h>
#include<geCore/fsa/state.h>

namespace ge{
  namespace util{
    class State;
    class FSA{
      public:
        static const char*els  ;
        static const char*eof  ;
        static const char*digit;
        static const char*range;
        static const char*all  ;
        static const char*space;
      private:
        const char*                 _start           ;
        std::vector<State*>         _states          ;
        std::map<const char*,State*>_name2State      ;
        std::string                 _alreadyRead     ;
        char                        _currentChar     ;
        const char*                 _currentStateName;
        unsigned                    _currentPosition ;
        State*      _addState (const char* name);
        State*      _getState (const char* name)const;
        std::string _expandLex(const char* lex )const;

        template<typename...Args>
        void _processArgs(
            const char*  stateA            ,
            const char*  lex               ,
            const char*  stateB            ,
            RuleCallback callback = nullptr,
            void*        data     = nullptr){
          if(std::strcmp(lex,FSA::all)==0)this->addAllTransition (stateA,stateB,callback,data);
          if(std::strcmp(lex,FSA::els)==0)this->addElseTransition(stateA,stateB,callback,data);
          if(std::strcmp(lex,FSA::eof)==0)this->addEOFTransition (stateA,stateB,callback,data);
          else this->addTransition(stateA,lex,stateB,callback,data);
        }
        template<typename...Args>
        void _processArgs(
            const char*  stateA  ,
            const char*  lex     ,
            const char*  stateB  ,
            RuleCallback callback,
            void*        data    ,
            Args...      args    ){
          this->_processArgs(stateA,lex,stateB,callback,data);
          this->_processArgs(args...);
        }
        template<typename...Args>
        void _processArgs(
            const char*  stateA  ,
            const char*  lex     ,
            const char*  stateB  ,
            RuleCallback callback,
            const char*  a0      ,
            Args...      args    ){
          this->_processArgs(stateA,lex,stateB,callback);
          this->_processArgs(a0,args...);
        }

        template<typename...Args>
        void _processArgs(
            const char*  stateA,
            const char*  lex   ,
            const char*  stateB,
            const char*  a0    ,
            Args...      args  ){
          this->_processArgs(stateA,lex,stateB);
          this->_processArgs(a0,args...);
        }

      public:
        template<typename...Args>
          FSA(const char* start,Args... args){
            this->_start=start;
            this->_processArgs(args...);
          }
        FSA(const char* start);
        virtual ~FSA();
        void addTransition(
            const char*  stateA            ,
            char         lex               ,
            const char*  stateB            ,
            RuleCallback callback = nullptr,
            void*        data     = nullptr);
        void addTransition(
            const char*  stateA            ,
            const char*  lex               ,
            const char*  stateB            ,
            RuleCallback callback = nullptr,
            void*        data     = nullptr);
        void addAllTransition(
            const char*  stateA            ,
            const char*  stateB            ,
            RuleCallback callback = nullptr,
            void*        data     = nullptr);
        void addElseTransition(
            const char*  stateA            ,
            const char*  stateB            ,
            RuleCallback callback = nullptr,
            void*        data     = nullptr);
        void addEOFTransition(
            const char*  stateA            ,
            const char*  stateB            ,
            RuleCallback callback = nullptr,
            void*        data     = nullptr);

        bool run(std::string text);
        char        getCurrentChar      ()const;
        std::string getAlreadyReadString()const;
        const char* getCurrentStateName ()const;
        unsigned    getCurrentPosition  ()const;
        std::string toStr()const;
    };

  }
}
