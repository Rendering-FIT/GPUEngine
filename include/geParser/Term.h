/*!
 * @file
 * @brief This file contains class Term.
 */
#pragma once

#include<geParser/Symbol.h>

namespace ge{
  namespace parser{
    class Term;///<A forward declaration
  }
}


class ge::parser::Term: public Symbol{
  public:
    Token::Type type;///<A terms type.
    /**
     * @brief A constructor
     *
     * @param type a type of term
     * @param name a name of term
     */
    Term(
        Token::Type const&type     ,
        std::string const&name = "");
    /**
     * @brief A desctructor
     */
    virtual~Term();
    /**
     * @brief This function converts term into string.
     *
     * @return A string representation of term.
     */
    virtual std::string str()const;
    /**
     * @brief This function tries to match of term with head of term list.
     *
     * @param term a head of term list.
     *
     * @return This function return true, if head of term list is this term.
     */
    virtual bool prefixMatch(
        Token::Type const&term)const;
};

inline ge::parser::Term::Term(
    Token::Type const&type,
    std::string const&name):Symbol(name){
  this->range.min()=1;
  this->range.max()=1;
  this->type = type;
}

inline ge::parser::Term::~Term(){
}

inline std::string ge::parser::Term::str()const{
  std::stringstream ss;
  if(this->name=="")
    ss<<"\""<<this->type<<"\"";
  else
    ss<<"\""<<this->name<<"\"";
  return ss.str();
}

inline bool ge::parser::Term::prefixMatch(
    Token::Type const&term)const{
  return this->type == term;
}

