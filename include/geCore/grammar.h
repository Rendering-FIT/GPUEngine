#pragma once

#include<set>
#include<memory>
#include<geCore/symbol.h>
#include<geCore/term.h>
#include<geCore/nonterm.h>

namespace ge{
  namespace core{
    bool prepareNonterms(std::set<std::shared_ptr<Nonterm>>const&allNonterms);
  }
}
