#pragma once

#include<set>
#include<memory>
#include<geParser/Export.h>
#include<geParser/Symbol.h>
#include<geParser/Term.h>
#include<geParser/Nonterm.h>

namespace ge{
  namespace parser{
    GEPARSER_EXPORT bool prepareNonterms(std::set<std::shared_ptr<Nonterm>>const&allNonterms);
  }
}
