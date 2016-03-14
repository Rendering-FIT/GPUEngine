#pragma once

#include<iostream>
#include<memory>
#include<map>

namespace ge{
  namespace core{
    class Tokenization{
      public:
        enum Config{
          EMPTY           = 0u   ;
          GOBACK          = 1u<<0;
          RECORD_POSITION = 1u<<1;
        };
        Tokenization(std::string start);
        ~Tokenization();
        void addTransition(
            std::string start        ,
            std::string lex          ,
            std::string end          ,
            std::string token = ""   ,
            Config      conf  = EMPTY);
      protected:
        std::map<std::string,size_t>_name2term;
        std::map<size_t,std::string>_term2name;
        std::shared_ptr<FSA>_fsa;
    };
  }
}
