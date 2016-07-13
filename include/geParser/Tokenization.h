#pragma once

#include<geParser/Export.h>
#include<iostream>
#include<memory>
#include<map>
#include<geParser/Token.h>
#include<geCore/fsa/Fsa.h>

namespace ge{
  namespace parser{
    class GEPARSER_EXPORT Tokenization{
      public:
        using Name2Term  = std::map<std::string,Token::Type>;
        using TokenIndex = Name2Term::size_type;
        static const std::string config_bit_begin ;
        static const std::string config_bit_end   ;
        static const std::string config_bit_goback;
        static const std::string config_bit_create;
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
        std::string tokenName(Token::Type term )const;
        Token::Type tokenType(std::string token)const;
        TokenIndex  nofTokens()const;
        void begin();
        void parse(std::string data);
        void end();
        Token getToken();
        bool empty()const;
        void clear();
      protected:
        enum ConfigBits{
          EMPTY  = 0u   ,
          GOBACK = 1u<<0,
          BEGIN  = 1u<<1,
          END    = 1u<<2,
          CREATE = 1u<<3,
        };
        using Config = int;
        class Data;
        class CallbackData{
          public:
            Config conf;
            Token::Type term;
            Data*data;
            CallbackData(Config conf,Token::Type term,Data*data){
              this->conf = conf;
              this->term = term;
              this->data = data;
            }
        };
        class Data{
          public:
            Name2Term                                  name2term    ;
            std::map<Token::Type,std::string>          term2name    ;
            std::shared_ptr<core::FSA>                 fsa          ;
            std::vector<Token>                         tokens       ;
            std::vector<Token>::size_type              currentToken ;
            std::set<Token::Type>                      hasKeywords  ;
            std::vector<std::shared_ptr<CallbackData>> callbackData ;
            std::vector<std::string>                   errorMessages;
            unsigned                                   charPosition ;
            Data();
        }_data;
        Token::Type _registerToken(std::string token);
        static void _callback(ge::core::FSA*fsa,void*data);
        static void _errorCallback(ge::core::FSA*fsa,void*data);
    };
  }
}
