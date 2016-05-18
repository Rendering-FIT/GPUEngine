#include<geParser/Nonterm.h>

using namespace ge::parser;

Nonterm::SideIndex Nonterm::addSide(
    SymbolList  const&side,
    std::string const&name){
  this->rightSides.push_back(Side(
        Range<TokenIndex>(),
        side,
        std::vector<Range<TokenIndex>>(),
        name));
  return this->rightSides.size()-1;
}

std::string Nonterm::str()const{
  std::stringstream ss;
  for(auto x:this->rightSides){
    ss<<"<"<<this->name<<"> ::=";
    ss<<" "<<std::get<RANGE>(x).str();
    for(auto y:std::get<SYMBOLS>(x)){
      ss<<" ";
      auto n=std::dynamic_pointer_cast<Nonterm>(y.lock());
      if(n)ss<<"<"<<n->name<<">";
      else ss<<y.lock()->str();
    }
    ss<<std::endl;
  }
  return ss.str();
}

Range<TokenIndex>Nonterm::_computeTailLength(
    SideIndex   const&side,
    SymbolIndex const&symbol)const{
  Range<TokenIndex>result;
  for(SymbolIndex i=symbol+1;i<this->nofSymbols(side);++i){
    result.min()+=this->getSymbol(side,i)->range.min();
    result.max()=saturatedAdd(
        result.max(),this->getSymbol(side,i)->range.max());
  }
  return result;
}

void Nonterm::computeSideSizes(){
  for(auto&x:this->rightSides){
    std::get<RANGE>(x).min() = 0;
    for(auto y:std::get<SYMBOLS>(x)){
      std::get<RANGE>(x).min()+=y.lock()->range.min();
      std::get<RANGE>(x).max()=saturatedAdd(
          std::get<RANGE>(x).max(),y.lock()->range.max());
    }
  }
}

void Nonterm::sortSides(){
  std::sort(
      this->rightSides.begin(),
      this->rightSides.end(),
      [](Side const&a,Side const&b){
      return std::get<RANGE>(a).min()<std::get<RANGE>(b).min();
      });
}

void Nonterm::computeTails(){
  for(SideIndex i=0;i<this->rightSides.size();++i)
    for(SymbolIndex j=0;j<this->nofSymbols(i);++j)
      std::get<TAILS>(this->rightSides[i]).push_back(
          this->_computeTailLength(i,j));
}


