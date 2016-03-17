#include<geCore/tokenization.h>
#include<geCore/text.h>

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
    t.addTransition("SLASH"         ,FSA::eof    ,"END"           ,"/"                                       );//create token /
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
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("i32"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("+"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType(";"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("for"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("("));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("i32"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("="));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("integer"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType(";"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("<"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("integer"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType(";"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("++"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType(")"));
        REQUIRE(t.empty()==true);
      }
    }
  }
  
  GIVEN("simple tokenization"){
    auto csv=std::make_shared<Tokenization>("START");
    csv->addTransition("START" ,","     ,"START" ,","         );
    csv->addTransition("START" ,FSA::els,"STRING",""     ,"b" );
    csv->addTransition("START" ,FSA::eof,"END"                );

    csv->addTransition("STRING",","     ,"START" ,"value","eg");
    csv->addTransition("STRING",FSA::els,"STRING"             );
    csv->addTransition("STRING",FSA::eof,"END"   ,"value","e" );

    WHEN("parsing A,a,B"){
      csv->begin();
      csv->parse("A,a,B");
      csv->end();
      THEN("it sould pass"){
        REQUIRE(csv->empty()==false);
        REQUIRE(csv->getToken().term==csv->tokenType("value"));
        REQUIRE(csv->empty()==false);
        REQUIRE(csv->getToken().term==csv->tokenType(","));
        REQUIRE(csv->empty()==false);
        REQUIRE(csv->getToken().term==csv->tokenType("value"));
        REQUIRE(csv->empty()==false);
        REQUIRE(csv->getToken().term==csv->tokenType(","));
        REQUIRE(csv->empty()==false);
        REQUIRE(csv->getToken().term==csv->tokenType("value"));
        REQUIRE(csv->empty()==true);
      }
    }
  }

  GIVEN("tokenization for csv"){
    auto csv=std::make_shared<Tokenization>("START");
    csv->addTransition("START"    ,","     ,"START"    ,","                              );
    csv->addTransition("START"    ,"\r\n"  ,"LINE-END"                                   );
    csv->addTransition("START"    ,"\\\\"  ,"BACKSLASH",""        ,"b"                   );
    csv->addTransition("START"    ,FSA::els,"STRING"   ,""        ,"b"                   );
    csv->addTransition("START"    ,FSA::eof,"END"                                        );

    csv->addTransition("LINE-END" ,"\r\n"  ,"LINE-END"                                   );
    csv->addTransition("LINE-END" ,FSA::els,"START"    ,"line-end","g"                   );
    csv->addTransition("LINE-END" ,FSA::eof,"END"                                        );

    csv->addTransition("BACKSLASH",FSA::all,"STRING"                                     );
    csv->addTransition("BACKSLASH",FSA::eof,""         ,"unexpected end of file after \\");

    csv->addTransition("STRING"   ,"\r\n"  ,"LINE-END" ,"value"   ,"e"                   );
    csv->addTransition("STRING"   ,"\\\\"  ,"BACKSLASH"                                  );
    csv->addTransition("STRING"   ,","     ,"START"    ,"value"   ,"eg"                  );
    csv->addTransition("STRING"   ,FSA::els,"STRING"                                     );
    csv->addTransition("STRING"   ,FSA::eof,"END"      ,"value"   ,"e"                   );

    WHEN("parsing A,a,B"){
      csv->begin();
      csv->parse("A,a,B");
      csv->end();
      THEN("it sould pass"){
        Tokenization::Token tok;
        REQUIRE(csv->empty()==false);
        tok = csv->getToken();
        REQUIRE(tok.term==csv->tokenType("value"));
        REQUIRE(tok.rawData == "A");
        REQUIRE(csv->empty()==false);
        tok = csv->getToken();
        REQUIRE(tok.term==csv->tokenType(","));
        REQUIRE(csv->empty()==false);
        tok = csv->getToken();
        REQUIRE(tok.term==csv->tokenType("value"));
        REQUIRE(tok.rawData == "a");
        REQUIRE(csv->empty()==false);
        REQUIRE(csv->getToken().term==csv->tokenType(","));
        REQUIRE(csv->empty()==false);
        tok = csv->getToken();
        REQUIRE(tok.term==csv->tokenType("value"));
        REQUIRE(tok.rawData == "B");
        REQUIRE(csv->empty()==true);
      }
    }
  }

  GIVEN("tokenization initialized using file"){
    Tokenization t;
    std::string source=
      "START, \\t\\r\\n,START\n"
      "START,+,PLUS\n"
      "START,-,MINUS\n"
      "START,*,MULTIPLICATION\n"
      "START,/,SLASH\n"
      "START,%,MODULO\n"
      "START,<,LESSER\n"
      "START,>,GREATER\n"
      "START,=,ASSIGNMENT\n"
      "START,!,EXCLAMATION\n"
      "START,&,AMPERSAND\n"
      "START,|,BAR\n"
      "START,(,START,(\n"
      "START,),START,)\n"
      "START,{,START,{\n"
      "START,},START,}\n"
      "START,[,START,[\n"
      "START,],START,]\n"
      "START,~,START,~\n"
      "START,;,START,;\n"
      "START,\\,,START,\\,\n"
      "START,_a\\\\-zA\\\\-Z,IDENTIFIER,,b\n"
      "START,\",DOUBLE_QUOTES,,b\n"
      "START,\',QUOTES,,b\n"
      "START,.,DOT,,b\n"
      "START,0\\\\-9,DIGIT,,b\n"
      "START,\\\\e,END\n"
      "START,,,unexpected symbol\n"
      "\n"
      "PLUS,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,+,g\n"
      "PLUS, \\t\\r\\n,START,+\n"
      "PLUS,=,START,+=\n"
      "PLUS,+,START,++\n"
      "PLUS,/,SLASH,+\n"
      "PLUS,\\\\e,END,+\n"
      "PLUS,,,expected + or =\n"
      "\n"
      "MINUS,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,-,g\n"
      "MINUS, \\t\\r\\n,START,-\n"
      "MINUS,=,START,-=\n"
      "MINUS,-,START,--\n"
      "MINUS,/,SLASH,-\n"
      "MINUS,\\\\e,END,-\n"
      "MINUS,,,expected - or =\n"
      "\n"
      "MULTIPLICATION,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,*,g\n"
      "MULTIPLICATION, \\t\\r\\n,START,*\n"
      "MULTIPLICATION,=,START,*=\n"
      "MULTIPLICATION,/,SLASH,*\n"
      "MULTIPLICATION,\\\\e,END,*\n"
      "MULTIPLICATION,,,expected =\n"
      "\n"
      "SLASH,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,/,g\n"
      "SLASH, \\t\\r\\n,START,/\n"
      "STASH,=,START,/=\n"
      "SLASH,/,COMMENT0\n"
      "SLASH,*,COMMENT1\n"
      "SLASH,\\\\e,END,/\n"
      "SLASH,,,expected = or *\n"
      "\n"
      "MODULO,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,%,g\n"
      "MODULO, \\t\\r\\n,START,%\n"
      "MODULO,=,START,%=\n"
      "MODULO,/,SLASH,%\n"
      "MODULO,\\\\e,END,%\n"
      "MODULO,,,expected =\n"
      "\n"
      "LESSER,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,<,g\n"
      "LESSER, \\t\\r\\n,START,<\n"
      "LESSER,=,START,<=\n"
      "LESSER,<,LSHIFT\n"
      "LESSER,/,SLASH,<\n"
      "LESSER,\\\\e,END,<\n"
      "LESSER,,,expected =\n"
      "\n"
      "GREATER,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,>,g\n"
      "GREATER, \\t\\r\\n,START,>\n"
      "GREATER,=,START,>=\n"
      "GREATER,>,RSHIFT\n"
      "GREATER,/,SLASH,>\n"
      "GREATER,\\\\e,END,>\n"
      "GREATER,,,expected =\n"
      "\n"
      "ASSIGNMENT,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,=,g\n"
      "ASSIGNMENT, \\t\\r\\n,START,= \n"
      "ASSIGNMENT,=,START,==\n"
      "ASSIGNMENT,/,SLASH,=\n"
      "ASSIGNMENT,\\\\e,END,=\n"
      "ASSIGNMENT,,,expected =\n"
      "\n"
      "EXCLAMATION,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,!,g\n"
      "EXCLAMATION, \\t\\r\\n,START,!\n"
      "EXCLAMATION,=,START,!=\n"
      "EXCLAMATION,!,START,!!\n"
      "EXCLAMATION,/,SLASH,!\n"
      "EXCLAMATION,\\\\e,END,!\n"
      "EXCLAMATION,,,expected = or !\n"
      "\n"
      "AMPERSAND,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,&,g\n"
      "AMPERSAND, \\t\\r\\n,START,&\n"
      "AMPERSAND,=,START,&=\n"
      "AMPERSAND,&,START,&&\n"
      "AMPERSAND,/,SLASH,&\n"
      "AMPERSAND,\\\\e,END,&\n"
      "AMPERSAND,,,expected = or &\n"
      "\n"
      "BAR,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,|,g\n"
      "BAR, \\t\\r\\n,START,|\n"
      "BAR,=,START,|=\n"
      "BAR,|,START,||\n"
      "BAR,/,SLASH,|\n"
      "BAR,\\\\e,END,|\n"
      "BAR,,,expected = or |\n"
      "\n"
      "IDENTIFIER,_a\\\\-zA\\\\-Z0\\\\-9,IDENTIFIER\n"
      "IDENTIFIER, \\t\\r\\n,START,identifier for while if else bool i8 i16 i32 i64 u8 u16 u32 u64 f32 f64 void struct typedef return,e\n"
      "IDENTIFIER,,START,identifier for while if else bool i8 i16 i32 i64 u8 u16 u32 u64 f32 f64 void struct typedef return,eg\n"
      "\n"
      "DOUBLE_QUOTES,\\\\\\\\,DQ_BACKSLASH\n"
      "DOUBLE_QUOTES,\",START,string,e\n"
      "DOUBLE_QUOTES,,DOUBLE_QUOTES\n"
      "DOUBLE_QUOTES,\\\\e,,unexpected end of file in string\n"
      "\n"
      "DQ_BACKSLASH,\\\\.,DOUBLE_QUOTES\n"
      "DQ_BACKSLASH,\\\\e,,unexpected end of file after backslash\n"
      "\n"
      "QUOTES,\\\\\\\\,Q_BACKSLASH\n"
      "QUOTES,\',START,char,e\n"
      "QUOTES,,QUOTES\n"
      "QUOTES,\\\\e,,unexpected end of file in char\n"
      "Q_BACKSLASH,\\\\.,QUOTES\n"
      "Q_BACKSLASH,\\\\e,,unexpected end of file after backslash\n"
      "\n"
      "DOT,0\\\\-9,FRACTION\n"
      "DOT,\\\\e,END,.\n"
      "DOT,,START,.,g\n"
      "\n"
      "DIGIT,0\\\\-9,DIGIT\n"
      "DIGIT,eE,EXPONENT\n"
      "DIGIT,.,FRACTION\n"
      "DIGIT,\\\\e,END,integer\n"
      "DIGIT,,START,integer,eg\n"
      "\n"
      "FRACTION,0\\\\-9,FRACTION\n"
      "FRACTION,eE,EXPONENT\n"
      "FRACTION,\\\\e,END,float\n"
      "FRACTION,,START,float,eg\n"
      "\n"
      "EXPONENT,+-,EXP_SIGN\n"
      "EXPONENT,0\\\\-9,EXP_DIGIT\n"
      "EXPONENT,\\\\e,,unexpected end of file in float exponent\n"
      "EXPONENT,,,expected + or - or digit in float exponent\n"
      "\n"
      "EXP_SIGN,0\\\\-9,EXP_DIGIT\n"
      "EXP_SIGN,\\\\e,,unexpected end of file in float exponent\n"
      "EXP_SIGN,,,expected digit in float exponent\n"
      "\n"
      "EXP_DIGIT,0\\\\-9,EXP_DIGIT\n"
      "EXP_DIGIT,\\\\e,END,float\n"
      "EXP_DIGIT,,START,float,eg\n"
      "\n"
      "COMMENT0,\\r\\n,START\n"
      "COMMENT0,\\\\e,END\n"
      "COMMENT0,,COMMENT0\n"
      "\n"
      "COMMENT1,*,COMMENT1_STAR\n"
      "COMMENT1,\\\\e,END\n"
      "COMMENT1,,COMMENT1\n"
      "\n"
      "COMMENT1_STAR,/,START\n"
      "COMMENT1_STAR,*,COMMENT1_STAR\n"
      "COMMENT1_STAR,\\\\e,END\n"
      "COMMENT1_STAR,,COMMENT1\n"
      "\n"
      "LSHIFT,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,<<,g\n"
      "LSHIFT, \\t\\r\\n,START,<<\n"
      "LSHIFT,=,START,<<=\n"
      "LSHIFT,/,SLASH,<<\n"
      "LSHIFT,\\\\e,END,<<\n"
      "LSHIFT,,,expected =\n"
      "\n"
      "RSHIFT,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,>>,g\n"
      "RSHIFT, \\t\\r\\n,START,>>\n"
      "RSHIFT,=,START,>>=\n"
      "RSHIFT,/,SLASH,>>\n"
      "RSHIFT,\\\\e,END,>>\n"
      "RSHIFT,,,expected =\n";

    t.load(source);
    WHEN("parsing i32 a+a;for(i32 i=0;i<32;++i)"){
      t.begin();
      t.parse("i32 a+a;for(i32 i=0;i<32;++i)");
      t.end();
      THEN("it should pass"){
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("i32"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("+"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType(";"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("for"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("("));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("i32"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("="));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("integer"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType(";"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("<"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("integer"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType(";"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("++"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().term==t.tokenType(")"));
        REQUIRE(t.empty()==true);
      }
    }
  }
}
