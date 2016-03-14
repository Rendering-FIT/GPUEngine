#pragma once

#include<iostream>
#include<memory>
#include<map>
#include<geCore/symbol.h>
#include<geCore/fsa/fsa.h>

namespace ge{
  namespace core{
    class Tokenization{
      public:
        enum Config{
          EMPTY           = 0u   ,
          GOBACK          = 1u<<0,
          BEGIN           = 1u<<1,
          END             = 1u<<2,
        };
        Tokenization(std::string start);
        ~Tokenization();
        void addTransition(
            std::string start        ,
            std::string lex          ,
            std::string end          ,
            std::string token = ""   ,
            Config      conf  = EMPTY);
        std::string tokenName(TermType    term )const;
        TermType    tokenType(std::string token)const;
      protected:
        std::map<std::string,TermType   >_name2term;
        std::map<TermType   ,std::string>_term2name;
        std::shared_ptr<FSA>_fsa;
        class CallbackData{
          public:
            Config conf;
            TermType term;
            unsigned*position;
            CallbackData(Config conf,TermType term,unsigned*position){
              this->conf     = conf    ;
              this->term     = term    ;
              this->position = position;
            }
        };
        std::vector<CallbackData>_data;
        unsigned _position;
        TermType _registerToken(std::string token);
        static void _callback(ge::core::FSA*fsa,void*data);
    };
  }
}
