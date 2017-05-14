#pragma once

#include<algorithm>
#include<set>
#include<geParser/Symbol.h>
#include<geParser/Export.h>

namespace ge{
  namespace parser{
    class Nonterm;
  }
}

class GEPARSER_EXPORT ge::parser::Nonterm: public Symbol{
  public:
    using SymbolList  = std::vector<std::weak_ptr<Symbol>>;
    using SymbolIndex = SymbolList::size_type;
    using Side        = std::tuple<
      Range<TokenIndex>             ,
      SymbolList                    ,
      std::vector<Range<TokenIndex>>,
      std::string                   >;
    using SideVector  = std::vector<Side>;
    using SideIndex   = SideVector::size_type;
    enum SideElements{
      RANGE   = 0,
      SYMBOLS = 1,
      TAILS   = 2,
      NAME    = 3,
    };
    SideVector rightSides;
    bool fresh = false;
    std::set<Token::Type>prefixes;
  protected:
    Range<TokenIndex>_computeTailLength(
        SideIndex const&side,SymbolIndex const&symbol)const;
  public:
    Nonterm(std::string const&name);
    virtual~Nonterm();
    SideIndex addSide(
        SymbolList  const&side,
        std::string const&name);
    virtual std::string str()const;
    void computeSideSizes();
    void sortSides();
    void computeTails();
    SymbolIndex nofSymbols(
        SideIndex const&side)const;
    std::shared_ptr<Symbol>getSymbol(
        SideIndex   const&side  ,
        SymbolIndex const&symbol)const;
    Range<TokenIndex>const&getTail(
        SideIndex const&side  ,
        SideIndex const&symbol)const;
    std::string const&getRuleName(
        SideIndex const&side)const;
    virtual bool prefixMatch(
        Token::Type const&term)const;
};

inline ge::parser::Nonterm::Nonterm(
    std::string const&name):Symbol(name){
  this->fresh = false;
}

inline ge::parser::Nonterm::~Nonterm(){
}

inline bool ge::parser::Nonterm::prefixMatch(
    Token::Type const&term)const{
  return this->prefixes.find(term)!=this->prefixes.end();
}

inline ge::parser::Nonterm::SymbolIndex ge::parser::Nonterm::nofSymbols(
    SideIndex const&side)const{
  return std::get<SYMBOLS>(this->rightSides[side]).size();
}

inline std::shared_ptr<ge::parser::Symbol>ge::parser::Nonterm::getSymbol(
    SideIndex   const&side  ,
    SymbolIndex const&symbol)const{
  return std::get<SYMBOLS>(this->rightSides[side])[symbol].lock();
}

inline ge::parser::Range<ge::parser::TokenIndex>const&ge::parser::Nonterm::getTail(
    SideIndex const&side  ,
    SideIndex const&symbol)const{
  return std::get<TAILS>(this->rightSides[side])[symbol];
}

inline std::string const&ge::parser::Nonterm::getRuleName(
    SideIndex const&side)const{
  return std::get<NAME>(this->rightSides[side]);
}
