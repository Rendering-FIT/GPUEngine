#pragma once

#include<set>
#include<memory>
#include<geCore/Export.h>
#include<geCore/symbol.h>
#include<geCore/term.h>
#include<geCore/nonterm.h>

namespace ge{
  namespace core{
    GECORE_EXPORT bool prepareNonterms(std::set<std::shared_ptr<Nonterm>>const&allNonterms);
  }
}
