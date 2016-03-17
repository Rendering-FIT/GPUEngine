#pragma once

#include<geCore/Export.h>
#include<iostream>
#include<memory>
#include<map>
#include<geCore/symbol.h>
#include<geCore/fsa/fsa.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT Tokenization{
      public:
        class GECORE_EXPORT Token{
          public:
            Token(TermType term,std::string rawData = "");
            std::string rawData;
            TermType    term;
            Token();
        };
      public:
        static const std::string config_bit_begin ;
        static const std::string config_bit_end   ;
        static const std::string config_bit_goback;
        static const std::string config_bit_empty ;
        Tokenization(std::string start);
        Tokenization();
        ~Tokenization();
        void load(std::string source);
        void addTransition(
            std::string start     ,
            std::string lex       ,
            std::string end       ,
            std::string token = "",
            std::string conf  = "");
        std::string tokenName(TermType    term )const;
        TermType    tokenType(std::string token)const;
        void begin();
        void parse(std::string data);
        void end();
        Token getToken();
        bool empty()const;
        void clear();
      protected:
        enum ConfigBits{
          EMPTY           = 0u   ,
          GOBACK          = 1u<<0,
          BEGIN           = 1u<<1,
          END             = 1u<<2,
        };
        using Config = int;
        class Data;
        class CallbackData{
          public:
            Config conf;
            TermType term;
            Data*data;
            CallbackData(Config conf,TermType term,Data*data){
              this->conf = conf;
              this->term = term;
              this->data = data;
            }
        };
        class Data{
          public:
            std::map<std::string,TermType>             name2term    ;
            std::map<TermType,std::string>             term2name    ;
            std::shared_ptr<FSA>                       fsa          ;
            std::vector<Token>                         tokens       ;
            std::vector<Token>::size_type              currentToken ;
            std::set<TermType>                         hasKeywords  ;
            std::vector<std::shared_ptr<CallbackData>> callbackData ;
            std::vector<std::string>                   errorMessages;
            unsigned                                   charPosition = 0;
            Data();
        }_data;
        TermType _registerToken(std::string token);
        static void _callback(ge::core::FSA*fsa,void*data);
        static void _errorCallback(ge::core::FSA*fsa,void*data);
    };
  }
}
