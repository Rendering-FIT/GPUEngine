#include<geParser/Grammar.h>

using namespace ge::parser;

bool computeMinLength(std::set<std::shared_ptr<Nonterm>>const&allNonterms){
  for(auto x:allNonterms){
    x->range.min()=std::numeric_limits<TokenIndex>::max();
    x->range.max()=std::numeric_limits<TokenIndex>::min();
  }
  std::set<std::shared_ptr<Nonterm>>terminating;
  std::set<std::shared_ptr<Nonterm>>newTerminating;
  do{
    terminating = newTerminating;
    newTerminating.clear();
    for(auto x:allNonterms){
      bool ignoreNonterm = true;
      for(auto y:x->rightSides){
        bool ignoreSide = false;
        for(auto z:std::get<Nonterm::SYMBOLS>(y)){
          auto sz = z.lock();
          if(std::dynamic_pointer_cast<Term>(sz))continue;
          if(terminating.find(std::dynamic_pointer_cast<Nonterm>(sz))!=terminating.end())continue;
          ignoreSide = true;
          break;
        }
        if(ignoreSide)continue;
        ignoreNonterm = false;
        TokenIndex len=0;
        for(auto z:std::get<Nonterm::SYMBOLS>(y)){
          auto sz = z.lock();
          if(std::dynamic_pointer_cast<Term>(sz)){
            len+=1;
            continue;
          }
          len+=std::dynamic_pointer_cast<Nonterm>(sz)->range.min();
        }
        x->range.min() = std::min(x->range.min(),len);
      }
      if(!ignoreNonterm)
        newTerminating.insert(x);
    }
  }while(terminating!=newTerminating);
  if(terminating!=allNonterms){
    std::cerr<<"ERROR: computeMinLength() these nonterms: "<<std::endl;
    for(auto x:allNonterms)
      if(terminating.find(x)==terminating.end())
        std::cerr<<x->name<<" ";
    std::cerr<<"do not produce terminating strings"<<std::endl;
    return false;
  }
  return true;
}

void computePrefixes(std::set<std::shared_ptr<Nonterm>>const&allNonterms){
  std::set<std::shared_ptr<Nonterm>>hasPrefix;
  std::set<std::shared_ptr<Nonterm>>newPrefix;
  do{
    hasPrefix = newPrefix;
    newPrefix.clear();
    for(auto x:allNonterms){
      bool ignoreNonterm = false;
      for(auto y:x->rightSides){
        auto z=std::get<Nonterm::SYMBOLS>(y)[0].lock();
        if(std::dynamic_pointer_cast<Term>(z))continue;
        if(x==std::dynamic_pointer_cast<Nonterm>(z))continue;
        if(hasPrefix.find(std::dynamic_pointer_cast<Nonterm>(z))!=hasPrefix.end())continue;
        ignoreNonterm = true;
        break;
      }
      if(ignoreNonterm)continue;
      for(auto y:x->rightSides){
        auto z=std::get<Nonterm::SYMBOLS>(y)[0].lock(); 
        if(std::dynamic_pointer_cast<Term>(z))x->prefixes.insert(std::dynamic_pointer_cast<Term>(z)->type);
        else{
          if(std::dynamic_pointer_cast<Nonterm>(z)==x)continue;
          for(auto p:std::dynamic_pointer_cast<Nonterm>(z)->prefixes)
            x->prefixes.insert(p);
        }
      }
      newPrefix.insert(x);
    }
  }while(hasPrefix!=newPrefix);
}

TokenIndex computeMaxLength(std::shared_ptr<Nonterm>const&n,std::set<std::string>&visited){
  if(visited.find(n->name)!=visited.end())return std::numeric_limits<TokenIndex>::max();
  visited.insert(n->name);
  TokenIndex longest=0;
  for(auto x:n->rightSides){
    TokenIndex currentLen = 0;
    for(auto y:std::get<Nonterm::SYMBOLS>(x)){
      auto sy=y.lock();
      if(std::dynamic_pointer_cast<Term>(sy)){
        currentLen+=1;
        continue;
      }
      currentLen = saturatedAdd(currentLen,computeMaxLength(std::dynamic_pointer_cast<Nonterm>(sy),visited));
      if(currentLen == std::numeric_limits<TokenIndex>::max())break;
    }
    longest = std::max(longest,currentLen);
    if(longest == std::numeric_limits<TokenIndex>::max())break;
  }
  return longest;
}

void computeMaxLength(std::set<std::shared_ptr<Nonterm>>const&allNonterms){
  for(auto x:allNonterms){
    std::set<std::string>visited;
    x->range.max()=computeMaxLength(x,visited);
  }
}

bool ge::parser::prepareNonterms(std::set<std::shared_ptr<Nonterm>>const&allNonterms){
  if(!computeMinLength(allNonterms))return false;
  computeMaxLength(allNonterms);
  computePrefixes(allNonterms);

  for(auto x:allNonterms)
    x->computeSideSizes();

  for(auto x:allNonterms)
    x->sortSides();

  for(auto x:allNonterms)
    x->computeTails();

  return true;
}
