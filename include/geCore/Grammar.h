#pragma once

#include<set>
#include<memory>
#include<geCore/Export.h>
#include<geCore/Symbol.h>
#include<geCore/Term.h>
#include<geCore/Nonterm.h>

namespace ge{
  namespace core{
    GECORE_EXPORT bool prepareNonterms(std::set<std::shared_ptr<Nonterm>>const&allNonterms);
  }
}
