#pragma once
#include<geCore/symbol.h>

namespace ge{
  namespace core{
    class Term: public Symbol{
      public:
        TermType type;
        inline Term(TermType const&type,std::string name="");
        inline virtual~Term();
        virtual std::string str()const;
        virtual bool prefixMatch(TermType const&term)const;
    };

    inline Term::Term(TermType const&type,std::string name){
      this->range.min()=1;
      this->range.max()=1;
      this->name = name;
      this->type = type;
    }

    inline Term::~Term(){
    }

    inline std::string Term::str()const{
      std::stringstream ss;
      if(this->name=="")
        ss<<"\""<<this->type<<"\"";
      else
        ss<<"\""<<this->name<<"\"";
      return ss.str();
    }

    inline bool Term::prefixMatch(TermType const&term)const{
      return this->type == term;
    }
  }
}



