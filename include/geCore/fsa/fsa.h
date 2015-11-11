#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<geCore/Export.h>
#include<geCore/geCore.h>
#include<geCore/fsa/transition.h>
#include<geCore/fsa/state.h>

namespace ge{
  namespace core{
    class State;
    class GECORE_EXPORT FSA{
      public:
        static const std::string els  ;
        static const std::string eof  ;
        static const std::string digit;
        static const std::string range;
        static const std::string all  ;
        static const std::string space;
      private:
        std::string                 _start           ;
        std::vector<State*>         _states          ;
        std::map<std::string,State*>_name2State      ;
        std::string                 _alreadyRead     ;
        char                        _currentChar     ;
        std::string                 _currentStateName;
        unsigned                    _currentPosition ;
        State*      _addState (std::string name);
        State*      _getState (std::string name)const;
        std::string _expandLex(std::string lex )const;

        template<typename...Args>
        void _processArgs(
            std::string  stateA            ,
            std::string  lex               ,
            std::string  stateB            ,
            RuleCallback callback = nullptr,
            void*        data     = nullptr){
          if(lex==FSA::all)this->addAllTransition (stateA,stateB,callback,data);
          if(lex==FSA::els)this->addElseTransition(stateA,stateB,callback,data);
          if(lex==FSA::eof)this->addEOFTransition (stateA,stateB,callback,data);
          else this->addTransition(stateA,lex,stateB,callback,data);
        }
        template<typename...Args>
        void _processArgs(
            std::string  stateA  ,
            std::string  lex     ,
            std::string  stateB  ,
            RuleCallback callback,
            void*        data    ,
            Args...      args    ){
          this->_processArgs(stateA,lex,stateB,callback,data);
          this->_processArgs(args...);
        }
        template<typename...Args>
        void _processArgs(
            std::string  stateA  ,
            std::string  lex     ,
            std::string  stateB  ,
            RuleCallback callback,
            std::string  a0      ,
            Args...      args    ){
          this->_processArgs(stateA,lex,stateB,callback);
          this->_processArgs(a0,args...);
        }

        template<typename...Args>
        void _processArgs(
            std::string  stateA,
            std::string  lex   ,
            std::string  stateB,
            std::string  a0    ,
            Args...      args  ){
          this->_processArgs(stateA,lex,stateB);
          this->_processArgs(a0,args...);
        }
      public:
        template<typename...Args>
          FSA(std::string start,Args... args){
            this->_start=start;
            this->_processArgs(args...);
          }
        FSA(std::string start = "");
        virtual ~FSA();
        void addTransition(
            std::string  stateA            ,
            char         lex               ,
            std::string  stateB            ,
            RuleCallback callback = nullptr,
            void*        data     = nullptr);
        void addTransition(
            std::string  stateA            ,
            std::string  lex               ,
            std::string  stateB            ,
            RuleCallback callback = nullptr,
            void*        data     = nullptr);
        void addAllTransition(
            std::string  stateA            ,
            std::string  stateB            ,
            RuleCallback callback = nullptr,
            void*        data     = nullptr);
        void addElseTransition(
            std::string  stateA            ,
            std::string  stateB            ,
            RuleCallback callback = nullptr,
            void*        data     = nullptr);
        void addEOFTransition(
            std::string  stateA            ,
            std::string  stateB            ,
            RuleCallback callback = nullptr,
            void*        data     = nullptr);

        bool run(std::string text);
        char        getCurrentChar      ()const;
        std::string getAlreadyReadString()const;
        std::string getCurrentStateName ()const;
        unsigned    getCurrentPosition  ()const;
        std::string toStr()const;
        void removeUnreachableStates();
        void removeUndistinguishabeStates();
        FSA* operator+(FSA const&other)const;
        FSA* operator*(FSA const&other)const;
    };

  }
}
