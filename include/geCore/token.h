#pragma once

#include<geCore/dtemplates.h>

namespace ge{
  namespace core{
    class Token{
      public:
        DEF_ENUM(Type,
            LEFT_BRACKET,
            RIGHT_BRACKET,
            LEFT_SET_BRACKET,
            RIGHT_SET_BRACKET,
            LEFT_INDEX_BRACKET,
            RIGHT_INDEX_BRACKET,
            PLUS,
            MINUS,
            MULTIPLICATION,
            DIVISION,
            MODULO,
            LESS,
            GREATER,
            ASSIGNMENT,
            NOT,
            BINARY_AND,
            BINARY_OR,
            NEGATION,
            XOR,
            PLUS_ASSIGNMENT,
            MINUS_ASSIGNMENT,
            MULTIPLICATION_ASSIGNMENT,
            DIVISION_ASSIGNMENT,
            MODULO_ASSIGNMENT,
            LESS_EQUAL,
            GREATER_EQUAL,
            EQUAL,
            NOT_EQUAL,
            LEFT_SHIFT,
            RIGHT_SHIFT,
            AND,
            OR,
            BINARY_AND_ASSIGNMENT,
            BINARY_OR_ASSIGNMENT,
            LEFT_SHIFT_ASSIGNMENT,
            RIGHT_SHIFT_ASSIGNMENT,
            INCREMENT,
            DECREMENT,
            SEMICOLON,
            COMMA,
            IDENTIFIER,
            STRING,
            CHAR,
            DOT,
            INTEGER,
            FLOAT,
            KEY_FOR,
            KEY_WHILE,
            KEY_IF,
            KEY_ELSE,
            KEY_BOOL,
            KEY_I8,
            KEY_I16,
            KEY_I32,
            KEY_I64,
            KEY_U8,
            KEY_U16,
            KEY_U32,
            KEY_U64,
            KEY_F32,
            KEY_F64,
            KEY_VOID,
            KEY_STRUCT,
            KEY_TYPEDEF,
            KEY_RETURN,
            WAITING,
            STOP);
        Token(
            Type type,
            std::string rawData,
            unsigned linePosition = 0,
            unsigned charPositionInLine = 0,
            unsigned charPositionInFile = 0);
        ~Token(){}
        inline Type getType()const;
        inline std::string getRawData()const;
        inline std::string getStringData()const;
        inline double getDoubleData()const;
        inline signed long long getIntegerData()const;
        inline unsigned long long getUnsignedData()const;
        inline unsigned getLine()const;
        inline unsigned getCharPositionInLine()const;
        inline unsigned getCharPositionInFile()const;
        std::string str()const;
      protected:
        Type _type;
        unsigned _linePosition = 0;
        unsigned _charPositionInLine = 0;
        unsigned _charPositionInFile = 0;
        std::string _rawData;
        float _fData;
        signed long long _iData;
        char _cData;
        std::string _sData;
    };

    Token::Type Token::getType()const{
      return this->_type;
    }

    std::string Token::getRawData()const{
      return this->_rawData;
    }

    std::string Token::getStringData()const{
      return this->_sData;
    }

    double Token::getDoubleData()const{
      return this->_fData;
    }

    signed long long Token::getIntegerData()const{
      return this->_iData;
    }

    unsigned Token::getLine()const{
      return this->_linePosition;
    }

    unsigned Token::getCharPositionInLine()const{
      return this->_charPositionInLine;
    }

    unsigned Token::getCharPositionInFile()const{
      return this->_charPositionInFile;
    }
  }
}
