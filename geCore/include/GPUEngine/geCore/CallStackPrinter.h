#pragma once

#if defined(ENABLE_PRINT_CALL_STACK)

#define HIDDEN_VARIABLE_NAME superduperhidden
#define OUTPUT cout

#include<geCore/Defines.h>
#include<geCore/ValuePrinter.h>

namespace ge{
  namespace core{
    template<typename...ARGS>
      std::string argsToStr(ARGS...);

    template<typename F,typename...ARGS>
      inline std::string argsToStr_help(F const&a,ARGS...args){
        std::stringstream ss;
        ss<<value2str(a);
        if(sizeof...(args)>0)
          ss<<","<<argsToStr(args...);
        return ss.str();
      }

    template<typename...ARGS>
      inline std::string argsToStr(ARGS...args){
        return argsToStr_help(args...);
      }

    template<>inline std::string argsToStr(){
      return "";
    }

    class CallStackPrinter{
      public:
        int&indentCounter(){
          static int counter = 0;
          return counter;
        }
        std::string&indent(){
          static std::string s = "";
          return s;
        }
        std::string argsData="";
        template<typename...ARGS>
          CallStackPrinter(ARGS...args){
            this->argsData = argsToStr(args...);
          }
        void print(std::string const&fceName){
          std::OUTPUT<<indent()<<fceName<<"("<<this->argsData<<"){"<<std::endl;
          indentCounter()+=2;
          indent()="";
          for(int i=0;i<indentCounter();++i)
            indent()+=" ";
        }
        ~CallStackPrinter(){
          indentCounter()-=2;
          if(indentCounter()<0)
            indentCounter()=0;
          indent()="";
          for(int i=0;i<indentCounter();++i)
            indent()+=" ";
          std::OUTPUT<<indent()<<"}"<<std::endl;
        }
    };


  }
}

#define PRINT_CALL_STACK(...)\
  ge::core::CallStackPrinter HIDDEN_VARIABLE_NAME{__VA_ARGS__};\
  HIDDEN_VARIABLE_NAME.print(GE_CORE_FCENAME)

#else
#define PRINT_CALL_STACK(...)
#endif


