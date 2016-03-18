#pragma once

#include<algorithm>
#include<set>
#include<geCore/symbol.h>
#include<geCore/Export.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT Nonterm: public Symbol{
      public:
        using SymbolList  = std::vector<std::weak_ptr<Symbol>>;
        using SymbolIndex = SymbolList::size_type;
        using Side        = std::tuple<
          Range<TermIndex>,
          SymbolList,
          std::vector<Range<TermIndex>>,
          std::size_t>;
        using SideIndex   = std::vector<Side>::size_type;
        enum SideElements{
          RANGE   = 0,
          SYMBOLS = 1,
          TAILS   = 2,
          ORIGID  = 3,
        };
        std::vector<Side>rightSides;
        bool fresh = false;
        std::set<Token::Type>prefixes;
      protected:
        Range<TermIndex>_computeTailLength(
            SideIndex side,SymbolIndex symbol)const;
      public:
        inline Nonterm(std::string name);
        virtual~Nonterm();
        SideIndex addSide(SymbolList const& side);
        virtual std::string str()const;
        void computeSideSizes();
        void sortSides();
        void computeTails();
        inline SymbolIndex nofSymbols(SideIndex side)const;
        inline std::shared_ptr<Symbol>getSymbol(
            SideIndex   side  ,
            SymbolIndex symbol)const;
        inline Range<TermIndex>getTail(
            SideIndex side,
            SideIndex symbol)const;
        inline SideIndex getOriginalIndex(SideIndex side)const;
        virtual bool prefixMatch(Token::Type const&term)const;
    };

    inline Nonterm::Nonterm(std::string name){
      this->fresh = false;
      this->name = name;
    }

    inline Nonterm::~Nonterm(){
    }

    inline bool Nonterm::prefixMatch(Token::Type const&term)const{
      return this->prefixes.find(term)!=this->prefixes.end();
    }

    inline Nonterm::SymbolIndex Nonterm::nofSymbols(SideIndex side)const{
      return std::get<SYMBOLS>(this->rightSides[side]).size();
    }

    inline std::shared_ptr<Symbol>Nonterm::getSymbol(
        SideIndex   side  ,
        SymbolIndex symbol)const{
      return std::get<SYMBOLS>(this->rightSides[side])[symbol].lock();
    }

    inline Range<TermIndex>Nonterm::getTail(
        SideIndex side  ,
        SideIndex symbol)const{
      return std::get<TAILS>(this->rightSides[side])[symbol];
    }

    inline Nonterm::SideIndex Nonterm::getOriginalIndex(SideIndex side)const{
      return std::get<ORIGID>(this->rightSides[side]);
    }
  }
}
