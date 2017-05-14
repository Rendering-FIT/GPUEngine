#pragma once

#include<iostream>
#include<limits>
#include<sstream>
#include<memory>
#include<vector>
#include<tuple>
#include<geParser/Export.h>
#include<geParser/Token.h>
#include<geParser/Range.h>

namespace ge{
  namespace parser{
    using TokenList = std::vector<Token>;
    using TokenIndex = TokenList::size_type;

    class Term;

    class GEPARSER_EXPORT Symbol: public std::enable_shared_from_this<Symbol>{
      public:
        std::string name = "";
        Range<TokenIndex>range;
        Symbol(std::string const&name);
        virtual std::string str()const = 0;
        virtual bool prefixMatch(Token::Type const&term)const = 0;
    };
  }
}

inline ge::parser::Symbol::Symbol(std::string const&name):name(name){
}

