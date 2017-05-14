/*!
 * @file
 * @brief This file contains token class.
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */

#pragma once

#include<iostream>

namespace ge{
  namespace parser{
    class Token;///<a forward declaration
  }
}

/**
 * @brief A token represents one lexem.
 * Tokens are produced by lexical analysis.
 */
class ge::parser::Token{
  public:
    using Type = size_t     ;///<type of tokens type
    using Data = std::string;///<type of tokens data
    /**
     * @brief A constructor
     *
     * @param type    type of token
     * @param rawData data of token
     */
    Token(
        Type const&type    = 0 ,
        Data const&rawData = "");
    Type type   ;///<a type of token - identifier, floatConstant, ...
    Data rawData;///<a data of token - identifier name, float digits, ...
};

inline ge::parser::Token::Token(
    Type const&type   ,
    Data const&rawData):
  type   (type   ),
  rawData(rawData)
{
}
