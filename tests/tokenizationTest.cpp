#include<geCore/tokenization.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;

SCENARIO("Tokenization basic tests"){
  GIVEN("c++ tokenization"){
    std::string identStart = "_a\\-zA\\-Z";
    std::string identBody  = identStart+ge::core::FSA::digit;
    std::string operatorStop = identStart+ge::core::FSA::digit+".,!(){}[]~;\"\'";// /
    std::string keywords="identifier for while if else bool i8 i16 i32 i64 u8 u16 u32 u64 f32 f64 void struct typedef return";

    Tokenization t("START");
    t.addTransition("START"         ,FSA::space  ,"START"                                                    );
    t.addTransition("START"         ,"+"         ,"PLUS"                                                     );
    t.addTransition("START"         ,"-"         ,"MINUS"                                                    );
    t.addTransition("START"         ,"*"         ,"MULTIPLICATION"                                           );
    t.addTransition("START"         ,"/"         ,"SLASH"                                                    );
    t.addTransition("START"         ,"%"         ,"MODULO"                                                   );
    t.addTransition("START"         ,"<"         ,"LESSER"                                                   );
    t.addTransition("START"         ,">"         ,"GREATER"                                                  );
    t.addTransition("START"         ,"="         ,"ASSIGNMENT"                                               );
    t.addTransition("START"         ,"!"         ,"EXCLAMATION"                                              );
    t.addTransition("START"         ,"&"         ,"AMPERSAND"                                                );
    t.addTransition("START"         ,"|"         ,"BAR"                                                      );
    t.addTransition("START"         ,"("         ,"START"         ,"("                                       );//create token
    t.addTransition("START"         ,")"         ,"START"         ,")"                                       );//create token
    t.addTransition("START"         ,"{"         ,"START"         ,"{"                                       );//create token
    t.addTransition("START"         ,"}"         ,"START"         ,"}"                                       );//create token
    t.addTransition("START"         ,"["         ,"START"         ,"["                                       );//create token
    t.addTransition("START"         ,"]"         ,"START"         ,"]"                                       );//create token
    t.addTransition("START"         ,"~"         ,"START"         ,"~"                                       );//create token
    t.addTransition("START"         ,";"         ,"START"         ,";"                                       );//create token
    t.addTransition("START"         ,","         ,"START"         ,","                                       );//create token
    t.addTransition("START"         ,identStart  ,"IDENTIFIER"    ,""                                   , "b");//push pos
    t.addTransition("START"         ,"\""        ,"DOUBLE_QUOTES" ,""                                   , "b");//push pos
    t.addTransition("START"         ,"'"         ,"QUOTES"        ,""                                   , "b");//push pos
    t.addTransition("START"         ,"."         ,"DOT"           ,""                                   , "b");//push pos
    t.addTransition("START"         ,FSA::digit  ,"DIGIT"         ,""                                   , "b");//push pos
    t.addTransition("START"         ,FSA::eof    ,"END"                                                      );
    t.addTransition("START"         ,""          ,""              ,"unexpected symbol"                       );//ERROR

    t.addTransition("PLUS"          ,operatorStop,"START"         ,"+"                                  , "g");//create token +, goBack
    t.addTransition("PLUS"          ,FSA::space  ,"START"         ,"+"                                       );//create token +
    t.addTransition("PLUS"          ,"="         ,"START"         ,"+="                                      );//create token += ++
    t.addTransition("PLUS"          ,"+"         ,"START"         ,"++"                                      );//create token += ++
    t.addTransition("PLUS"          ,"/"         ,"SLASH"         ,"+"                                       );//create token +
    t.addTransition("PLUS"          ,FSA::eof    ,"END"           ,"+"                                       );//create token +
    t.addTransition("PLUS"          ,""          ,""              ,"expected + or ="                         );

    t.addTransition("MINUS"         ,operatorStop,"START"         ,"-"                                  , "g");//create token -, goBack
    t.addTransition("MINUS"         ,FSA::space  ,"START"         ,"-"                                       );//create token -
    t.addTransition("MINUS"         ,"="         ,"START"         ,"-="                                      );//create token -= --
    t.addTransition("MINUS"         ,"-"         ,"START"         ,"--"                                      );//create token -= --
    t.addTransition("MINUS"         ,"/"         ,"SLASH"         ,"-"                                       );//create token -
    t.addTransition("MINUS"         ,FSA::eof    ,"END"           ,"-"                                       );//create token -
    t.addTransition("MINUS"         ,""          ,""              ,"expected - or ="                         );//ERROR

    t.addTransition("MULTIPLICATION",operatorStop,"START"         ,"*"                                  , "g");//create token *, goBack
    t.addTransition("MULTIPLICATION",FSA::space  ,"START"         ,"*"                                       );//create token *
    t.addTransition("MULTIPLICATION","="         ,"START"         ,"*="                                      );//create token *=
    t.addTransition("MULTIPLICATION","/"         ,"SLASH"         ,"*"                                       );//create token *
    t.addTransition("MULTIPLICATION",FSA::eof    ,"END"           ,"*"                                       );//create token *
    t.addTransition("MULTIPLICATION",""          ,""              ,"expected ="                              );//ERRO);

    t.addTransition("SLASH"         ,operatorStop,"START"         ,"/"                                  , "g");//create token /, goBack
    t.addTransition("SLASH"         ,FSA::space  ,"START"         ,"/"                                       );//create token /
    t.addTransition("STASH"         ,"="         ,"START"         ,"/="                                      );//create token /=
    t.addTransition("SLASH"         ,"/"         ,"COMMENT0"                                                 );
    t.addTransition("SLASH"         ,"*"         ,"COMMENT1"                                                 );
    t.addTransition("SLASH"         ,FSA::eof    ,"END"           ,""                                        );//create token /
    t.addTransition("SLASH"         ,""          ,""              ,"expected = or *"                         );//ERROR

    t.addTransition("MODULO"        ,operatorStop,"START"         ,"%"                                  , "g");//create token %, goBack
    t.addTransition("MODULO"        ,FSA::space  ,"START"         ,"%"                                       );//create token %
    t.addTransition("MODULO"        ,"="         ,"START"         ,"%="                                      );//create token %=
    t.addTransition("MODULO"        ,"/"         ,"SLASH"         ,"%"                                       );//create token %
    t.addTransition("MODULO"        ,FSA::eof    ,"END"           ,"%"                                       );//create token %
    t.addTransition("MODULO"        ,""          ,""              ,"expected ="                              );//ERROR

    t.addTransition("LESSER"        ,operatorStop,"START"         ,"<"                                  , "g");//create token <, goBack
    t.addTransition("LESSER"        ,FSA::space  ,"START"         ,"<"                                       );//create token <
    t.addTransition("LESSER"        ,"="         ,"START"         ,"<="                                      );//create token <=
    t.addTransition("LESSER"        ,"<"         ,"LSHIFT"                                                   );
    t.addTransition("LESSER"        ,"/"         ,"SLASH"         ,"<"                                       );//create token <
    t.addTransition("LESSER"        ,FSA::eof    ,"END"           ,"<"                                       );//create token <
    t.addTransition("LESSER"        ,""          ,""              ,"expected ="                              );//ERROR

    t.addTransition("GREATER"       ,operatorStop,"START"         ,">"                                  , "g");//create token >, goBack
    t.addTransition("GREATER"       ,FSA::space  ,"START"         ,">"                                       );//create token >
    t.addTransition("GREATER"       ,"="         ,"START"         ,">="                                      );//create token >=
    t.addTransition("GREATER"       ,">"         ,"RSHIFT"                                                   );
    t.addTransition("GREATER"       ,"/"         ,"SLASH"         ,">"                                       );//create token >
    t.addTransition("GREATER"       ,FSA::eof    ,"END"           ,">"                                       );//create token >
    t.addTransition("GREATER"       ,""          ,""              ,"expected ="                              );//ERROR

    t.addTransition("ASSIGNMENT"    ,operatorStop,"START"         ,"="                                  , "g");//create token =, goBack
    t.addTransition("ASSIGNMENT"    ,FSA::space  ,"START"         ,"="                                       );//create token =
    t.addTransition("ASSIGNMENT"    ,"="         ,"START"         ,"=="                                      );//create token ==
    t.addTransition("ASSIGNMENT"    ,"/"         ,"SLASH"         ,"="                                       );//create token =
    t.addTransition("ASSIGNMENT"    ,FSA::eof    ,"END"           ,"="                                       );//create token =
    t.addTransition("ASSIGNMENT"    ,""          ,""              ,"expected ="                              );//ERROR

    t.addTransition("EXCLAMATION"   ,operatorStop,"START"         ,"!"                                  , "g");//create token !, goBack
    t.addTransition("EXCLAMATION"   ,FSA::space  ,"START"         ,"!"                                       );//create token !
    t.addTransition("EXCLAMATION"   ,"="         ,"START"         ,"!="                                      );//create token !=
    t.addTransition("EXCLAMATION"   ,"!"         ,"START"         ,"!!"                                      );//create token !!
    t.addTransition("EXCLAMATION"   ,"/"         ,"SLASH"         ,"!"                                       );//create token !
    t.addTransition("EXCLAMATION"   ,FSA::eof    ,"END"           ,"!"                                       );//create token !
    t.addTransition("EXCLAMATION"   ,""          ,""              ,"expected = or !"                         );//ERROR

    t.addTransition("AMPERSAND"     ,operatorStop,"START"         ,"&"                                  , "g");//create token &, goBack
    t.addTransition("AMPERSAND"     ,FSA::space  ,"START"         ,"&"                                       );//create token &
    t.addTransition("AMPERSAND"     ,"="         ,"START"         ,"&="                                      );//create token &=
    t.addTransition("AMPERSAND"     ,"&"         ,"START"         ,"&&"                                      );//create token &&
    t.addTransition("AMPERSAND"     ,"/"         ,"SLASH"         ,"&"                                       );//create token &
    t.addTransition("AMPERSAND"     ,FSA::eof    ,"END"           ,"&"                                       );//create token &
    t.addTransition("AMPERSAND"     ,""          ,""              ,"expected = or &"                         );//ERROR

    t.addTransition("BAR"           ,operatorStop,"START"         ,"|"                                  , "g");//create token |, goBack
    t.addTransition("BAR"           ,FSA::space  ,"START"         ,"|"                                       );//create token |
    t.addTransition("BAR"           ,"="         ,"START"         ,"|="                                      );//create token |=
    t.addTransition("BAR"           ,"|"         ,"START"         ,"||"                                      );//create token ||
    t.addTransition("BAR"           ,"/"         ,"SLASH"         ,"|"                                       );//create token |
    t.addTransition("BAR"           ,FSA::eof    ,"END"           ,"|"                                       );//create token |
    t.addTransition("BAR"           ,""          ,""              ,"expected = or |"                         );//ERROR

    t.addTransition("IDENTIFIER"    ,identBody   ,"IDENTIFIER"                                               );
    t.addTransition("IDENTIFIER"    ,FSA::space  ,"START"         ,keywords                             , "e");//create token identifier
    t.addTransition("IDENTIFIER"    ,FSA::els    ,"START"         ,keywords                             ,"eg");//create token identifier, goBack

    t.addTransition("DOUBLE_QUOTES" ,"\\\\"      ,"DQ_BACKSLASH"                                             );
    t.addTransition("DOUBLE_QUOTES" ,"\""        ,"START"         ,"string"                             , "e");//create token string
    t.addTransition("DOUBLE_QUOTES" ,FSA::els    ,"DOUBLE_QUOTES"                                            );
    t.addTransition("DOUBLE_QUOTES" ,FSA::eof    ,""              ,"unexpected end of file for string"       );//ERROR

    t.addTransition("DQ_BACKSLASH"  ,FSA::all    ,"DOUBLE_QUOTES"                                            );
    t.addTransition("DQ_BACKSLASH"  ,FSA::eof    ,""              ,"unexpected end of file for backslash"    );//ERROR

    t.addTransition("QUOTES"        ,"\\\\"      ,"Q_BACKSLASH"                                              );
    t.addTransition("QUOTES"        ,"\'"        ,"START"         ,"char"                               , "e");//create token char
    t.addTransition("QUOTES"        ,FSA::els    ,"QUOTES"                                                   );
    t.addTransition("QUOTES"        ,FSA::eof    ,""              ,"unexpected end of file for char"         );//ERROR
    t.addTransition("Q_BACKSLASH"   ,FSA::all    ,"QUOTES"                                                   );
    t.addTransition("Q_BACKSLASH"   ,FSA::eof    ,""              ,"unexpected end of file for backslash"    );//ERROR

    t.addTransition("DOT"           ,FSA::digit  ,"FRACTION"                                                 );
    t.addTransition("DOT"           ,FSA::eof    ,"END"           ,"."                                       );//create token .
    t.addTransition("DOT"           ,FSA::els    ,"START"         ,"."                                  , "g");//create token ., goBack

    t.addTransition("DIGIT"         ,FSA::digit  ,"DIGIT"                                                    );
    t.addTransition("DIGIT"         ,"eE"        ,"EXPONENT"                                                 );
    t.addTransition("DIGIT"         ,"."         ,"FRACTION"                                                 );
    t.addTransition("DIGIT"         ,FSA::eof    ,"END"           ,"integer"                                 );//create token integer
    t.addTransition("DIGIT"         ,FSA::els    ,"START"         ,"integer"                            ,"eg");//create token integer, goBack

    t.addTransition("FRACTION"      ,FSA::digit  ,"FRACTION"                                                 );
    t.addTransition("FRACTION"      ,"eE"        ,"EXPONENT"                                                 );
    t.addTransition("FRACTION"      ,FSA::eof    ,"END"           ,"float"                                   );//create token float
    t.addTransition("FRACTION"      ,FSA::els    ,"START"         ,"float"                              ,"eg");//create token float, goBack

    t.addTransition("EXPONENT"      ,"+-"        ,"EXP_SIGN"                                                 );
    t.addTransition("EXPONENT"      ,FSA::digit  ,"EXP_DIGIT"                                                );
    t.addTransition("EXPONENT"      ,FSA::eof    ,""              ,"unexpected end of file in float exponent");//ERROR
    t.addTransition("EXPONENT"      ,FSA::els    ,""              ,"expected + or - in float exponent"       );//ERROR

    t.addTransition("EXP_SIGN"      ,FSA::digit  ,"EXP_DIGIT"                                                );
    t.addTransition("EXP_SIGN"      ,FSA::eof    ,""              ,"unexpected end of file in float exponent");//ERROR
    t.addTransition("EXP_SIGN"      ,FSA::els    ,""              ,"expected digit in float expoenent"       );//ERROR

    t.addTransition("EXP_DIGIT"     ,FSA::digit  ,"EXP_DIGIT"                                                );
    t.addTransition("EXP_DIGIT"     ,FSA::eof    ,"END"           ,"float"                                   );//create token float
    t.addTransition("EXP_DIGIT"     ,FSA::els    ,"START"         ,"float"                              ,"eg");//create token float, goBack

    t.addTransition("COMMENT0"      ,"\r\n"      ,"START"                                                    );
    t.addTransition("COMMENT0"      ,FSA::eof    ,"END"                                                      );
    t.addTransition("COMMENT0"      ,FSA::els    ,"COMMENT0"                                                 );

    t.addTransition("COMMENT1"      ,"*"         ,"COMMENT1_STAR"                                            );
    t.addTransition("COMMENT1"      ,FSA::eof    ,"END"                                                      );
    t.addTransition("COMMENT1"      ,FSA::els    ,"COMMENT1"                                                 );

    t.addTransition("COMMENT1_STAR" ,"/"         ,"START"                                                    );
    t.addTransition("COMMENT1_STAR" ,"*"         ,"COMMENT1_STAR"                                            );
    t.addTransition("COMMENT1_STAR" ,FSA::eof    ,"END"                                                      );
    t.addTransition("COMMENT1_STAR" ,FSA::els    ,"COMMENT1"                                                 );

    t.addTransition("LSHIFT"        ,operatorStop,"START"         ,"<<"                                 , "g");//create token <<, goBack
    t.addTransition("LSHIFT"        ,FSA::space  ,"START"         ,"<<"                                      );//create token <<
    t.addTransition("LSHIFT"        ,"="         ,"START"         ,"<<="                                     );//create token <<=
    t.addTransition("LSHIFT"        ,"/"         ,"SLASH"         ,"<<"                                      );//create token <<
    t.addTransition("LSHIFT"        ,FSA::eof    ,"END"           ,"<<"                                      );//create token <<
    t.addTransition("LSHIFT"        ,""          ,""              ,"expected ="                              );//ERROR

    t.addTransition("RSHIFT"        ,operatorStop,"START"         ,">>"                                 , "g");//create token >>, goBack
    t.addTransition("RSHIFT"        ,FSA::space  ,"START"         ,">>"                                      );//create token >>
    t.addTransition("RSHIFT"        ,"="         ,"START"         ,">>="                                     );//create token >>=
    t.addTransition("RSHIFT"        ,"/"         ,"SLASH"         ,">>"                                      );//create token >>
    t.addTransition("RSHIFT"        ,FSA::eof    ,"END"           ,">>"                                      );//create token >>
    t.addTransition("RSHIFT"        ,""          ,""              ,"expected ="                              );//ERROR


    WHEN("parsing i32 a+a;for(i32 i=0;i<32;++i)"){
      t.begin();
      t.parse("i32 a+a;for(i32 i=0;i<32;++i)");
      t.end();
      THEN("it should pass"){
        REQUIRE(t.getToken().term==t.tokenType("i32"));
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.getToken().term==t.tokenType("+"));
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.getToken().term==t.tokenType(";"));
        REQUIRE(t.getToken().term==t.tokenType("for"));
        REQUIRE(t.getToken().term==t.tokenType("("));
        REQUIRE(t.getToken().term==t.tokenType("i32"));
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.getToken().term==t.tokenType("="));
        REQUIRE(t.getToken().term==t.tokenType("integer"));
        REQUIRE(t.getToken().term==t.tokenType(";"));
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.getToken().term==t.tokenType("<"));
        REQUIRE(t.getToken().term==t.tokenType("integer"));
        REQUIRE(t.getToken().term==t.tokenType(";"));
        REQUIRE(t.getToken().term==t.tokenType("++"));
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.getToken().term==t.tokenType(")"));
      }
    }
  }
}
