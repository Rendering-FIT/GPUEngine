#pragma once

#include<algorithm>
#include<set>
#include<geParser/Symbol.h>
#include<geParser/Export.h>

namespace ge{
  namespace parser{
    class GEPARSER_EXPORT Nonterm: public Symbol{
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
        inline Nonterm(std::string const&name);
        virtual~Nonterm();
        SideIndex addSide(SymbolList const&side,std::string const&name);
        virtual std::string str()const;
        void computeSideSizes();
        void sortSides();
        void computeTails();
        inline SymbolIndex nofSymbols(SideIndex const&side)const;
        inline std::shared_ptr<Symbol>getSymbol(
            SideIndex   const&side  ,
            SymbolIndex const&symbol)const;
        inline Range<TokenIndex>const&getTail(
            SideIndex const&side  ,
            SideIndex const&symbol)const;
        inline std::string const&getRuleName(SideIndex const&side)const;
        virtual bool prefixMatch(Token::Type const&term)const;
    };

    inline Nonterm::Nonterm(std::string const&name){
      this->fresh = false;
      this->name = name;
    }

    inline Nonterm::~Nonterm(){
    }

    inline bool Nonterm::prefixMatch(Token::Type const&term)const{
      return this->prefixes.find(term)!=this->prefixes.end();
    }

    inline Nonterm::SymbolIndex Nonterm::nofSymbols(SideIndex const&side)const{
      return std::get<SYMBOLS>(this->rightSides[side]).size();
    }

    inline std::shared_ptr<Symbol>Nonterm::getSymbol(
        SideIndex   const&side  ,
        SymbolIndex const&symbol)const{
      return std::get<SYMBOLS>(this->rightSides[side])[symbol].lock();
    }

    inline Range<TokenIndex>const&Nonterm::getTail(
        SideIndex const&side  ,
        SideIndex const&symbol)const{
      return std::get<TAILS>(this->rightSides[side])[symbol];
    }

    inline std::string const&Nonterm::getRuleName(SideIndex const&side)const{
      return std::get<NAME>(this->rightSides[side]);
    }
  }
}
