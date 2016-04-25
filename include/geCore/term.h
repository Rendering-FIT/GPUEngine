#pragma once
#include<geCore/symbol.h>

namespace ge{
  namespace core{
    class Term: public Symbol{
      public:
        Token::Type type;
        inline Term(Token::Type const&type,std::string const&name="");
        inline virtual~Term();
        virtual std::string str()const;
        virtual bool prefixMatch(Token::Type const&term)const;
    };

    inline Term::Term(Token::Type const&type,std::string const& name){
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

    inline bool Term::prefixMatch(Token::Type const&term)const{
      return this->type == term;
    }
  }
}



