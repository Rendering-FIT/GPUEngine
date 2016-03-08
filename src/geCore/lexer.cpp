#include<geCore/lexer.h>
#include<geCore/fsa/fsa.h>

using namespace ge::core;

Lexer::Lexer(){
  this->_firstRun = true;
}

Lexer::~Lexer(){
}

void Lexer::parse(std::string data,bool stop){
  static struct ParserData{
    std::vector<Token>tokens;
    unsigned pos;
    static void createToken(ge::core::FSA*fsa,void*data){
      ParserData*pd=(ParserData*)data;
      if     (fsa->getCurrentChar()=='(')pd->tokens.push_back(Token(Token::LEFT_BRACKET       ,"("));
      else if(fsa->getCurrentChar()==')')pd->tokens.push_back(Token(Token::RIGHT_BRACKET      ,")"));
      else if(fsa->getCurrentChar()=='{')pd->tokens.push_back(Token(Token::LEFT_SET_BRACKET   ,"{"));
      else if(fsa->getCurrentChar()=='}')pd->tokens.push_back(Token(Token::RIGHT_SET_BRACKET  ,"}"));
      else if(fsa->getCurrentChar()=='[')pd->tokens.push_back(Token(Token::LEFT_INDEX_BRACKET ,"["));
      else if(fsa->getCurrentChar()==']')pd->tokens.push_back(Token(Token::RIGHT_INDEX_BRACKET,"]"));
      else if(fsa->getCurrentChar()=='~')pd->tokens.push_back(Token(Token::NEGATION           ,"~"));
      else if(fsa->getCurrentChar()==';')pd->tokens.push_back(Token(Token::SEMICOLON          ,";"));
      else if(fsa->getCurrentChar()==',')pd->tokens.push_back(Token(Token::COMMA              ,","));
    };

    static void pushPos(ge::core::FSA*fsa,void*data){
      ParserData*pd=(ParserData*)data;
      pd->pos = fsa->getCurrentPosition();
    };

#define LAMBDA(TOKEN)\
    (ge::core::FSA*,void*data){\
      ParserData*pd=(ParserData*)data;\
      pd->tokens.push_back(Token(Token::TOKEN,""));\
    }

#define LAMBDA_GOBACK(callback)\
    (ge::core::FSA*fsa,void*data){\
      ParserData*pd=(ParserData*)data;\
      pd->callback(fsa,data);\
      fsa->goBack();\
    }

#define LAMBDA_IF(TOKEN0,TOKEN1,IFCHAR)\
    (ge::core::FSA*fsa,void*data){\
      ParserData*pd=(ParserData*)data;\
      if(fsa->getCurrentChar()==IFCHAR)\
        pd->tokens.push_back(Token(Token::TOKEN0,""));\
      else\
        pd->tokens.push_back(Token(Token::TOKEN1,""));\
    }

#define LAMBDA_DATA(TOKEN)\
    (ge::core::FSA*fsa,void*data){\
      auto pd = (ParserData*)data;\
      /*std::cerr<<"pd->pos: "<<pd->pos<<std::endl;*/\
      /*std::cerr<<"#"<<fsa->getAlreadyReadString()<<"#"<<std::endl;*/\
      pd->tokens.push_back(Token(Token::TOKEN,fsa->getAlreadyReadString().substr(pd->pos)));\
    }

#define Type static void

    Type createPlus                     LAMBDA(PLUS);
    Type createPlusGoBack               LAMBDA_GOBACK(createPlus);
    Type createPlus2                    LAMBDA_IF(PLUS_ASSIGNMENT,INCREMENT,'=');

    Type createMinus                    LAMBDA(MINUS);
    Type createMinusGoBack              LAMBDA_GOBACK(createMinus);
    Type createMinus2                   LAMBDA_IF(MINUS_ASSIGNMENT,DECREMENT,'=');

    Type createMultiplication           LAMBDA(MULTIPLICATION);
    Type createMultiplicationGoBack     LAMBDA_GOBACK(createMultiplication);
    Type createMultiplicationAssigment  LAMBDA(MULTIPLICATION_ASSIGNMENT);

    Type createDivision                 LAMBDA(DIVISION);
    Type createDivisionGoBack           LAMBDA_GOBACK(createDivision);
    Type createDivisionAssigment        LAMBDA(DIVISION_ASSIGNMENT);

    Type createModulo                   LAMBDA(MODULO);
    Type createModuloGoBack             LAMBDA_GOBACK(createModulo);
    Type createModuloAssigment          LAMBDA(MODULO_ASSIGNMENT);

    Type createLess                     LAMBDA(LESS);
    Type createLessGoBack               LAMBDA_GOBACK(createLess);
    Type createLessEqual                LAMBDA(LESS_EQUAL);

    Type createGreater                  LAMBDA(GREATER);
    Type createGreaterGoBack            LAMBDA_GOBACK(createGreater);
    Type createGreaterEqual             LAMBDA(GREATER_EQUAL);

    Type createAssigment                LAMBDA(ASSIGNMENT);
    Type createAssigmentGoBack          LAMBDA_GOBACK(createAssigment);
    Type createEqual                    LAMBDA(EQUAL);

    Type createNot                      LAMBDA(NOT);
    Type createNotGoBack                LAMBDA_GOBACK(createNot);
    Type createNotEqual                 LAMBDA(NOT_EQAUL);

    Type createBinaryAnd                LAMBDA(BINARY_AND);
    Type createBinaryAndGoBack          LAMBDA_GOBACK(createBinaryAnd);
    Type createBinaryAndAssigment       LAMBDA(BINARY_AND_ASSIGNMENT);
    Type createAnd                      LAMBDA(AND);

    Type createBinaryOr                 LAMBDA(BINARY_OR);
    Type createBinaryOrGoBack           LAMBDA_GOBACK(createBinaryOr);
    Type createBinaryOrAssigment        LAMBDA(BINARY_OR_ASSIGNMENT);
    Type createOr                       LAMBDA(OR);

    Type createIdentifier               LAMBDA_DATA(IDENTIFIER);
    Type createIdentifierGoBack         LAMBDA_GOBACK(createIdentifier);

    Type createString                   LAMBDA_DATA(STRING);
    Type createChar                     LAMBDA_DATA(CHAR);

    Type createDot                      LAMBDA(DOT);
    Type createDotGoBack                LAMBDA_GOBACK(createDot);

    Type createInteger                  LAMBDA_DATA(INTEGER);
    Type createIntegerGoBack            LAMBDA_GOBACK(createInteger);

    Type createFloat                    LAMBDA_DATA(FLOAT);
    Type createFloatGoBack              LAMBDA_GOBACK(createFloat);

    Type createLeftShift                LAMBDA(LEFT_SHIFT);
    Type createLeftShiftGoBack          LAMBDA_GOBACK(createLeftShift);
    Type createLeftShiftAssigment       LAMBDA(LEFT_SHIFT_ASSIGNMENT);

    Type createRightShift               LAMBDA(RIGHT_SHIFT);
    Type createRightShiftGoBack         LAMBDA_GOBACK(createRightShift);
    Type createRightShiftAssigment      LAMBDA(RIGHT_SHIFT_ASSIGNMENT);

    Type error (ge::core::FSA*fsa,void*){
      //if(fsa->getCurrentStateName()=="START"){
        std::cerr<<"ERROR: unrecognised symbol "<<fsa->getCurrentStateName()<<" "<<fsa->getCurrentChar()<<std::endl;
      //}

    };

#undef Type
#undef LAMBDA
#undef LAMBDA_GOBACK
#undef LAMBDA_IF
  }pData;
  
  std::string identStart = "_a\\-zA\\-Z";
  std::string identBody  = identStart+ge::core::FSA::digit;
  std::string operatorStop = identStart+ge::core::FSA::digit+".,!(){}[]~;\"\'";// /

  static auto fsa = ge::core::FSA("START");
  static bool notInitialized=true;
  if(notInitialized){
    fsa.addTransition("START"         ,ge::core::FSA::space,"START"                                                    );
    fsa.addTransition("START"         ,"+"                 ,"PLUS"                                                     );
    fsa.addTransition("START"         ,"-"                 ,"MINUS"                                                    );
    fsa.addTransition("START"         ,"*"                 ,"MULTIPLICATION"                                           );
    fsa.addTransition("START"         ,"/"                 ,"SLASH"                                                    );
    fsa.addTransition("START"         ,"%"                 ,"MODULO"                                                   );
    fsa.addTransition("START"         ,"<"                 ,"LESSER"                                                   );
    fsa.addTransition("START"         ,">"                 ,"GREATER"                                                  );
    fsa.addTransition("START"         ,"="                 ,"ASSIGNMENT"                                               );
    fsa.addTransition("START"         ,"!"                 ,"EXCLAMATION"                                              );
    fsa.addTransition("START"         ,"&"                 ,"AMPERSAND"                                                );
    fsa.addTransition("START"         ,"|"                 ,"BAR"                                                      );
    fsa.addTransition("START"         ,"(){}[]~;,"         ,"START"         ,pData.createToken                  ,&pData);//create token
    fsa.addTransition("START"         ,identStart          ,"IDENTIFIER"    ,pData.pushPos                      ,&pData);//push pos
    fsa.addTransition("START"         ,"\""                ,"DOUBLE_QUOTES" ,pData.pushPos                      ,&pData);//push pos
    fsa.addTransition("START"         ,"'"                 ,"QUOTES"        ,pData.pushPos                      ,&pData);//push pos
    fsa.addTransition("START"         ,"."                 ,"DOT"           ,pData.pushPos                      ,&pData);//push pos
    fsa.addTransition("START"         ,ge::core::FSA::digit,"DIGIT"         ,pData.pushPos                      ,&pData);//push pos
    fsa.addTransition("START"         ,ge::core::FSA::eof  ,"END"                                                      );
    fsa.addTransition("START"         ,""                  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("PLUS"          ,operatorStop        ,"START"         ,pData.createPlusGoBack             ,&pData);//create token +, goBack
    fsa.addTransition("PLUS"          ,ge::core::FSA::space,"START"         ,pData.createPlus                   ,&pData);//create token +
    fsa.addTransition("PLUS"          ,"=+"                ,"START"         ,pData.createPlus2                  ,&pData);//create token += ++
    fsa.addTransition("PLUS"          ,"/"                 ,"SLASH"         ,pData.createPlus                   ,&pData);//create token +
    fsa.addTransition("PLUS"          ,ge::core::FSA::eof  ,"END"           ,pData.createPlus                   ,&pData);//create token +
    fsa.addTransition("PLUS"          ,""                  ,""              ,pData.error                               );

    fsa.addTransition("MINUS"         ,operatorStop        ,"START"         ,pData.createMinusGoBack            ,&pData);//create token -, goBack
    fsa.addTransition("MINUS"         ,ge::core::FSA::space,"START"         ,pData.createMinus                  ,&pData);//create token -
    fsa.addTransition("MINUS"         ,"=-"                ,"START"         ,pData.createMinus2                 ,&pData);//create token -= --
    fsa.addTransition("MINUS"         ,"/"                 ,"SLASH"         ,pData.createMinus                  ,&pData);//create token -
    fsa.addTransition("MINUS"         ,ge::core::FSA::eof  ,"END"           ,pData.createMinus                  ,&pData);//create token -
    fsa.addTransition("MINUS"         ,""                  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("MULTIPLICATION",operatorStop        ,"START"         ,pData.createMultiplicationGoBack   ,&pData);//create token *, goBack
    fsa.addTransition("MULTIPLICATION",ge::core::FSA::space,"START"         ,pData.createMultiplication         ,&pData);//create token *
    fsa.addTransition("MULTIPLICATION","="                 ,"START"         ,pData.createMultiplicationAssigment,&pData);//create token *=
    fsa.addTransition("MULTIPLICATION","/"                 ,"SLASH"         ,pData.createMultiplication         ,&pData);//create token *
    fsa.addTransition("MULTIPLICATION",ge::core::FSA::eof  ,"END"           ,pData.createMultiplication         ,&pData);//create token *
    fsa.addTransition("MULTIPLICATION",""                  ,""              ,pData.error                               );//ERRO);

    fsa.addTransition("SLASH"         ,operatorStop        ,"START"         ,pData.createDivisionGoBack         ,&pData);//create token /, goBack
    fsa.addTransition("SLASH"         ,ge::core::FSA::space,"START"         ,pData.createDivision               ,&pData);//create token /
    fsa.addTransition("STASH"         ,"="                 ,"START"         ,pData.createDivisionAssigment      ,&pData);//create token /=
    fsa.addTransition("SLASH"         ,"/"                 ,"COMMENT0"                                                 );
    fsa.addTransition("SLASH"         ,"*"                 ,"COMMENT1"                                                 );
    fsa.addTransition("SLASH"         ,ge::core::FSA::eof  ,"END"           ,pData.createDivision               ,&pData);//create token /
    fsa.addTransition("SLASH"         ,""                  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("MODULO"        ,operatorStop        ,"START"         ,pData.createModuloGoBack           ,&pData);//create token %, goBack
    fsa.addTransition("MODULO"        ,ge::core::FSA::space,"START"         ,pData.createModulo                 ,&pData);//create token %
    fsa.addTransition("MODULO"        ,"="                 ,"START"         ,pData.createModuloAssigment        ,&pData);//create token %=
    fsa.addTransition("MODULO"        ,"/"                 ,"SLASH"         ,pData.createModulo                 ,&pData);//create token %
    fsa.addTransition("MODULO"        ,ge::core::FSA::eof  ,"END"           ,pData.createModulo                 ,&pData);//create token %
    fsa.addTransition("MODULO"        ,""                  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("LESSER"        ,operatorStop        ,"START"         ,pData.createLessGoBack             ,&pData);//create token <, goBack
    fsa.addTransition("LESSER"        ,ge::core::FSA::space,"START"         ,pData.createLess                   ,&pData);//create token <
    fsa.addTransition("LESSER"        ,"="                 ,"START"         ,pData.createLessEqual              ,&pData);//create token <=
    fsa.addTransition("LESSER"        ,"<"                 ,"LSHIFT"                                                   );
    fsa.addTransition("LESSER"        ,"/"                 ,"SLASH"         ,pData.createLess                   ,&pData);//create token <
    fsa.addTransition("LESSER"        ,ge::core::FSA::eof  ,"END"           ,pData.createLess                   ,&pData);//create token <
    fsa.addTransition("LESSER"        ,""                  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("GREATER"       ,operatorStop        ,"START"         ,pData.createGreaterGoBack          ,&pData);//create token >, goBack
    fsa.addTransition("GREATER"       ,ge::core::FSA::space,"START"         ,pData.createGreater                ,&pData);//create token >
    fsa.addTransition("GREATER"       ,"="                 ,"START"         ,pData.createGreaterEqual           ,&pData);//create token >=
    fsa.addTransition("GREATER"       ,">"                 ,"RSHIFT"                                                   );
    fsa.addTransition("GREATER"       ,"/"                 ,"SLASH"         ,pData.createGreater                ,&pData);//create token >
    fsa.addTransition("GREATER"       ,ge::core::FSA::eof  ,"END"           ,pData.createGreater                ,&pData);//create token >
    fsa.addTransition("GREATER"       ,""                  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("ASSIGNMENT"    ,operatorStop        ,"START"         ,pData.createAssigmentGoBack        ,&pData);//create token =, goBack
    fsa.addTransition("ASSIGNMENT"    ,ge::core::FSA::space,"START"         ,pData.createAssigment              ,&pData);//create token =
    fsa.addTransition("ASSIGNMENT"    ,"="                 ,"START"         ,pData.createEqual                  ,&pData);//create token ==
    fsa.addTransition("ASSIGNMENT"    ,"/"                 ,"SLASH"         ,pData.createAssigment              ,&pData);//create token =
    fsa.addTransition("ASSIGNMENT"    ,ge::core::FSA::eof  ,"END"           ,pData.createAssigment              ,&pData);//create token =
    fsa.addTransition("ASSIGNMENT"    ,""                  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("EXCLAMATION"   ,operatorStop        ,"START"         ,pData.createNotGoBack              ,&pData);//create token !, goBack
    fsa.addTransition("EXCLAMATION"   ,ge::core::FSA::space,"START"         ,pData.createNot                    ,&pData);//create token !
    fsa.addTransition("EXCLAMATION"   ,"="                 ,"START"         ,pData.createNotEqual               ,&pData);//create token !=
    fsa.addTransition("EXCLAMATION"   ,"!"                 ,"START"         ,pData.createNot                    ,&pData);//create token !!
    fsa.addTransition("EXCLAMATION"   ,"/"                 ,"SLASH"         ,pData.createNot                    ,&pData);//create token !
    fsa.addTransition("EXCLAMATION"   ,ge::core::FSA::eof  ,"END"           ,pData.createNot                    ,&pData);//create token !
    fsa.addTransition("EXCLAMATION"   ,""                  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("AMPERSAND"     ,operatorStop        ,"START"         ,pData.createBinaryAndGoBack        ,&pData);//create token &, goBack
    fsa.addTransition("AMPERSAND"     ,ge::core::FSA::space,"START"         ,pData.createBinaryAnd              ,&pData);//create token &
    fsa.addTransition("AMPERSAND"     ,"="                 ,"START"         ,pData.createBinaryAndAssigment     ,&pData);//create token &=
    fsa.addTransition("AMPERSAND"     ,"&"                 ,"START"         ,pData.createAnd                    ,&pData);//create token &&
    fsa.addTransition("AMPERSAND"     ,"/"                 ,"SLASH"         ,pData.createBinaryAnd              ,&pData);//create token &
    fsa.addTransition("AMPERSAND"     ,ge::core::FSA::eof  ,"END"           ,pData.createBinaryAnd              ,&pData);//create token &
    fsa.addTransition("AMPERSAND"     ,""                  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("BAR"           ,operatorStop        ,"START"         ,pData.createBinaryOrGoBack         ,&pData);//create token |, goBack
    fsa.addTransition("BAR"           ,ge::core::FSA::space,"START"         ,pData.createBinaryOr               ,&pData);//create token |
    fsa.addTransition("BAR"           ,"="                 ,"START"         ,pData.createBinaryOrAssigment      ,&pData);//create token |=
    fsa.addTransition("BAR"           ,"|"                 ,"START"         ,pData.createOr                     ,&pData);//create token ||
    fsa.addTransition("BAR"           ,"/"                 ,"SLASH"         ,pData.createBinaryOr               ,&pData);//create token |
    fsa.addTransition("BAR"           ,ge::core::FSA::eof  ,"END"           ,pData.createBinaryOr               ,&pData);//create token |
    fsa.addTransition("BAR"           ,""                  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("IDENTIFIER"    ,identBody           ,"IDENTIFIER"                                               );
    fsa.addTransition("IDENTIFIER"    ,ge::core::FSA::space,"START"         ,pData.createIdentifier             ,&pData);//create token identifier
    fsa.addTransition("IDENTIFIER"    ,ge::core::FSA::els  ,"START"         ,pData.createIdentifierGoBack       ,&pData);//create token identifier, goBack

    fsa.addTransition("DOUBLE_QUOTES" ,"\\\\"              ,"DQ_BACKSLASH"                                             );
    fsa.addTransition("DOUBLE_QUOTES" ,"\""                ,"START"         ,pData.createString                 ,&pData);//create token string
    fsa.addTransition("DOUBLE_QUOTES" ,ge::core::FSA::els  ,"DOUBLE_QUOTES"                                            );
    fsa.addTransition("DOUBLE_QUOTES" ,ge::core::FSA::eof  ,""              ,pData.error                               );//ERROR
    fsa.addTransition("DQ_BACKSLASH"  ,ge::core::FSA::all  ,"DOUBLE_QUOTES"                                            );
    fsa.addTransition("DQ_BACKSLASH"  ,ge::core::FSA::eof  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("QUOTES"        ,"\\\\"              ,"Q_BACKSLASH"                                              );
    fsa.addTransition("QUOTES"        ,"\'"                ,"START"         ,pData.createChar                   ,&pData);//create token char
    fsa.addTransition("QUOTES"        ,ge::core::FSA::els  ,"QUOTES"                                                   );
    fsa.addTransition("QUOTES"        ,ge::core::FSA::eof  ,""              ,pData.error                               );//ERROR
    fsa.addTransition("Q_BACKSLASH"   ,ge::core::FSA::all  ,"QUOTES"                                                   );
    fsa.addTransition("Q_BACKSLASH"   ,ge::core::FSA::eof  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("DOT"           ,ge::core::FSA::digit,"FRACTION"                                                 );
    fsa.addTransition("DOT"           ,ge::core::FSA::eof  ,"END"           ,pData.createDot                    ,&pData);//create token .
    fsa.addTransition("DOT"           ,ge::core::FSA::els  ,"START"         ,pData.createDotGoBack              ,&pData);//create token ., goBack

    fsa.addTransition("DIGIT"         ,ge::core::FSA::digit,"DIGIT"                                                    );
    fsa.addTransition("DIGIT"         ,"eE"                ,"EXPONENT"                                                 );
    fsa.addTransition("DIGIT"         ,"."                 ,"FRACTION"                                                 );
    fsa.addTransition("DIGIT"         ,ge::core::FSA::eof  ,"END"           ,pData.createInteger                ,&pData);//create token integer
    fsa.addTransition("DIGIT"         ,ge::core::FSA::els  ,"START"         ,pData.createIntegerGoBack          ,&pData);//create token integer, goBack

    fsa.addTransition("FRACTION"      ,ge::core::FSA::digit,"FRACTION"                                                 );
    fsa.addTransition("FRACTION"      ,"eE"                ,"EXPONENT"                                                 );
    fsa.addTransition("FRACTION"      ,ge::core::FSA::eof  ,"END"           ,pData.createFloat                  ,&pData);//create token float
    fsa.addTransition("FRACTION"      ,ge::core::FSA::els  ,"START"         ,pData.createFloatGoBack            ,&pData);//create token float, goBack

    fsa.addTransition("EXPONENT"      ,"+-"                ,"EXP_SIGN"                                                 );
    fsa.addTransition("EXPONENT"      ,ge::core::FSA::digit,"EXP_DIGIT"                                                );
    fsa.addTransition("EXPONENT"      ,ge::core::FSA::eof  ,""              ,pData.error                               );//ERROR
    fsa.addTransition("EXPONENT"      ,ge::core::FSA::els  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("EXP_SIGN"      ,ge::core::FSA::digit,"EXP_DIGIT"                                                );
    fsa.addTransition("EXP_SIGN"      ,ge::core::FSA::eof  ,""              ,pData.error                               );//ERROR
    fsa.addTransition("EXP_SIGN"      ,ge::core::FSA::els  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("EXP_DIGIT"     ,ge::core::FSA::digit,"EXP_DIGIT"                                                );
    fsa.addTransition("EXP_DIGIT"     ,ge::core::FSA::eof  ,"END"           ,pData.createFloat                  ,&pData);//create token float
    fsa.addTransition("EXP_DIGIT"     ,ge::core::FSA::els  ,"START"         ,pData.createFloatGoBack            ,&pData);//create token float, goBack

    fsa.addTransition("COMMENT0"      ,"\r\n"              ,"START"                                                    );
    fsa.addTransition("COMMENT0"      ,ge::core::FSA::eof  ,"END"                                                      );
    fsa.addTransition("COMMENT0"      ,ge::core::FSA::els  ,"COMMENT0"                                                 );

    fsa.addTransition("COMMENT1"      ,"*"                 ,"COMMENT1_STAR"                                            );
    fsa.addTransition("COMMENT1"      ,ge::core::FSA::eof  ,"END"                                                      );
    fsa.addTransition("COMMENT1"      ,ge::core::FSA::els  ,"COMMENT1"                                                 );

    fsa.addTransition("COMMENT1_STAR" ,"/"                 ,"START"                                                    );
    fsa.addTransition("COMMENT1_STAR" ,"*"                 ,"COMMENT1_STAR"                                            );
    fsa.addTransition("COMMENT1_STAR" ,ge::core::FSA::eof  ,"END"                                                      );
    fsa.addTransition("COMMENT1_STAR" ,ge::core::FSA::els  ,"COMMENT1"                                                 );

    fsa.addTransition("LSHIFT"        ,operatorStop        ,"START"         ,pData.createLeftShiftGoBack        ,&pData);//create token <<, goBack
    fsa.addTransition("LSHIFT"        ,ge::core::FSA::space,"START"         ,pData.createLeftShift              ,&pData);//create token <<
    fsa.addTransition("LSHIFT"        ,"="                 ,"START"         ,pData.createLeftShiftAssigment     ,&pData);//create token <<=
    fsa.addTransition("LSHIFT"        ,"/"                 ,"SLASH"         ,pData.createLeftShift              ,&pData);//create token <<
    fsa.addTransition("LSHIFT"        ,ge::core::FSA::eof  ,"END"           ,pData.createLeftShift              ,&pData);//create token <<
    fsa.addTransition("LSHIFT"        ,""                  ,""              ,pData.error                               );//ERROR

    fsa.addTransition("RSHIFT"        ,operatorStop        ,"START"         ,pData.createRightShiftGoBack       ,&pData);//create token >>, goBack
    fsa.addTransition("RSHIFT"        ,ge::core::FSA::space,"START"         ,pData.createRightShift             ,&pData);//create token >>
    fsa.addTransition("RSHIFT"        ,"="                 ,"START"         ,pData.createRightShiftAssigment    ,&pData);//create token >>=
    fsa.addTransition("RSHIFT"        ,"/"                 ,"SLASH"         ,pData.createRightShift             ,&pData);//create token >>
    fsa.addTransition("RSHIFT"        ,ge::core::FSA::eof  ,"END"           ,pData.createRightShift             ,&pData);//create token >>
    fsa.addTransition("RSHIFT"        ,""                  ,""              ,pData.error                               );//ERROR
    notInitialized=false;
  }

  pData.tokens.clear();

  if(stop){
    if(!this->_firstRun)
      fsa.stop(data);
  }else{
    if(this->_firstRun){
      this->_firstRun = false;
      pData.pos = 0;
      fsa.runWithPause(data);
    }else{
      fsa.unpause(data);
    }
  }
  for(auto x:pData.tokens)
    this->_tokens.push_back(x);
}

Token Lexer::get(){
  if(this->_currentToken>=this->_tokens.size())
    return Token(Token::WAITING,"");
  return this->_tokens[this->_currentToken++];
}

