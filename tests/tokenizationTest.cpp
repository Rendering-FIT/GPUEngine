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
    t.addTransition("START"         ,"("         ,"START"         ,"("                                  ,"c" );//create token
    t.addTransition("START"         ,")"         ,"START"         ,")"                                  ,"c" );//create token
    t.addTransition("START"         ,"{"         ,"START"         ,"{"                                  ,"c" );//create token
    t.addTransition("START"         ,"}"         ,"START"         ,"}"                                  ,"c" );//create token
    t.addTransition("START"         ,"["         ,"START"         ,"["                                  ,"c" );//create token
    t.addTransition("START"         ,"]"         ,"START"         ,"]"                                  ,"c" );//create token
    t.addTransition("START"         ,"~"         ,"START"         ,"~"                                  ,"c" );//create token
    t.addTransition("START"         ,";"         ,"START"         ,";"                                  ,"c" );//create token
    t.addTransition("START"         ,","         ,"START"         ,","                                  ,"c" );//create token
    t.addTransition("START"         ,identStart  ,"IDENTIFIER"    ,""                                   ,"b" );//push pos
    t.addTransition("START"         ,"\""        ,"DOUBLE_QUOTES" ,""                                   ,"b" );//push pos
    t.addTransition("START"         ,"'"         ,"QUOTES"        ,""                                   ,"b" );//push pos
    t.addTransition("START"         ,"."         ,"DOT"           ,""                                   ,"b" );//push pos
    t.addTransition("START"         ,FSA::digit  ,"DIGIT"         ,""                                   ,"b" );//push pos
    t.addTransition("START"         ,FSA::eof    ,"END"                                                      );
    t.addTransition("START"         ,""          ,""              ,"unexpected symbol"                       );//ERROR

    t.addTransition("PLUS"          ,operatorStop,"START"         ,"+"                                  ,"cg");//create token +, goBack
    t.addTransition("PLUS"          ,FSA::space  ,"START"         ,"+"                                  ,"c" );//create token +
    t.addTransition("PLUS"          ,"="         ,"START"         ,"+="                                 ,"c" );//create token += ++
    t.addTransition("PLUS"          ,"+"         ,"START"         ,"++"                                 ,"c" );//create token += ++
    t.addTransition("PLUS"          ,"/"         ,"SLASH"         ,"+"                                  ,"c" );//create token +
    t.addTransition("PLUS"          ,FSA::eof    ,"END"           ,"+"                                  ,"c" );//create token +
    t.addTransition("PLUS"          ,""          ,""              ,"expected + or ="                         );

    t.addTransition("MINUS"         ,operatorStop,"START"         ,"-"                                  ,"cg");//create token -, goBack
    t.addTransition("MINUS"         ,FSA::space  ,"START"         ,"-"                                  ,"c" );//create token -
    t.addTransition("MINUS"         ,"="         ,"START"         ,"-="                                 ,"c" );//create token -= --
    t.addTransition("MINUS"         ,"-"         ,"START"         ,"--"                                 ,"c" );//create token -= --
    t.addTransition("MINUS"         ,"/"         ,"SLASH"         ,"-"                                  ,"c" );//create token -
    t.addTransition("MINUS"         ,FSA::eof    ,"END"           ,"-"                                  ,"c" );//create token -
    t.addTransition("MINUS"         ,""          ,""              ,"expected - or ="                         );//ERROR

    t.addTransition("MULTIPLICATION",operatorStop,"START"         ,"*"                                  ,"cg");//create token *, goBack
    t.addTransition("MULTIPLICATION",FSA::space  ,"START"         ,"*"                                  ,"c" );//create token *
    t.addTransition("MULTIPLICATION","="         ,"START"         ,"*="                                 ,"c" );//create token *=
    t.addTransition("MULTIPLICATION","/"         ,"SLASH"         ,"*"                                  ,"c" );//create token *
    t.addTransition("MULTIPLICATION",FSA::eof    ,"END"           ,"*"                                  ,"c" );//create token *
    t.addTransition("MULTIPLICATION",""          ,""              ,"expected ="                         ,"c" );//ERRO);

    t.addTransition("SLASH"         ,operatorStop,"START"         ,"/"                                  ,"cg");//create token /, goBack
    t.addTransition("SLASH"         ,FSA::space  ,"START"         ,"/"                                  ,"c" );//create token /
    t.addTransition("STASH"         ,"="         ,"START"         ,"/="                                 ,"c" );//create token /=
    t.addTransition("SLASH"         ,"/"         ,"COMMENT0"                                                 );
    t.addTransition("SLASH"         ,"*"         ,"COMMENT1"                                                 );
    t.addTransition("SLASH"         ,FSA::eof    ,"END"           ,"/"                                  ,"c" );//create token /
    t.addTransition("SLASH"         ,""          ,""              ,"expected = or *"                         );//ERROR

    t.addTransition("MODULO"        ,operatorStop,"START"         ,"%"                                  ,"cg");//create token %, goBack
    t.addTransition("MODULO"        ,FSA::space  ,"START"         ,"%"                                  ,"c" );//create token %
    t.addTransition("MODULO"        ,"="         ,"START"         ,"%="                                 ,"c" );//create token %=
    t.addTransition("MODULO"        ,"/"         ,"SLASH"         ,"%"                                  ,"c" );//create token %
    t.addTransition("MODULO"        ,FSA::eof    ,"END"           ,"%"                                  ,"c" );//create token %
    t.addTransition("MODULO"        ,""          ,""              ,"expected ="                              );//ERROR

    t.addTransition("LESSER"        ,operatorStop,"START"         ,"<"                                  ,"cg");//create token <, goBack
    t.addTransition("LESSER"        ,FSA::space  ,"START"         ,"<"                                  ,"c" );//create token <
    t.addTransition("LESSER"        ,"="         ,"START"         ,"<="                                 ,"c" );//create token <=
    t.addTransition("LESSER"        ,"<"         ,"LSHIFT"                                                   );
    t.addTransition("LESSER"        ,"/"         ,"SLASH"         ,"<"                                  ,"c" );//create token <
    t.addTransition("LESSER"        ,FSA::eof    ,"END"           ,"<"                                  ,"c" );//create token <
    t.addTransition("LESSER"        ,""          ,""              ,"expected ="                              );//ERROR

    t.addTransition("GREATER"       ,operatorStop,"START"         ,">"                                  ,"cg");//create token >, goBack
    t.addTransition("GREATER"       ,FSA::space  ,"START"         ,">"                                  ,"c" );//create token >
    t.addTransition("GREATER"       ,"="         ,"START"         ,">="                                 ,"c" );//create token >=
    t.addTransition("GREATER"       ,">"         ,"RSHIFT"                                                   );
    t.addTransition("GREATER"       ,"/"         ,"SLASH"         ,">"                                  ,"c" );//create token >
    t.addTransition("GREATER"       ,FSA::eof    ,"END"           ,">"                                  ,"c" );//create token >
    t.addTransition("GREATER"       ,""          ,""              ,"expected ="                              );//ERROR

    t.addTransition("ASSIGNMENT"    ,operatorStop,"START"         ,"="                                  ,"cg");//create token =, goBack
    t.addTransition("ASSIGNMENT"    ,FSA::space  ,"START"         ,"="                                  ,"c" );//create token =
    t.addTransition("ASSIGNMENT"    ,"="         ,"START"         ,"=="                                 ,"c" );//create token ==
    t.addTransition("ASSIGNMENT"    ,"/"         ,"SLASH"         ,"="                                  ,"c" );//create token =
    t.addTransition("ASSIGNMENT"    ,FSA::eof    ,"END"           ,"="                                  ,"c" );//create token =
    t.addTransition("ASSIGNMENT"    ,""          ,""              ,"expected ="                              );//ERROR

    t.addTransition("EXCLAMATION"   ,operatorStop,"START"         ,"!"                                  ,"cg");//create token !, goBack
    t.addTransition("EXCLAMATION"   ,FSA::space  ,"START"         ,"!"                                  ,"c" );//create token !
    t.addTransition("EXCLAMATION"   ,"="         ,"START"         ,"!="                                 ,"c" );//create token !=
    t.addTransition("EXCLAMATION"   ,"!"         ,"START"         ,"!!"                                 ,"c" );//create token !!
    t.addTransition("EXCLAMATION"   ,"/"         ,"SLASH"         ,"!"                                  ,"c" );//create token !
    t.addTransition("EXCLAMATION"   ,FSA::eof    ,"END"           ,"!"                                  ,"c" );//create token !
    t.addTransition("EXCLAMATION"   ,""          ,""              ,"expected = or !"                         );//ERROR

    t.addTransition("AMPERSAND"     ,operatorStop,"START"         ,"&"                                  ,"cg");//create token &, goBack
    t.addTransition("AMPERSAND"     ,FSA::space  ,"START"         ,"&"                                  ,"c" );//create token &
    t.addTransition("AMPERSAND"     ,"="         ,"START"         ,"&="                                 ,"c" );//create token &=
    t.addTransition("AMPERSAND"     ,"&"         ,"START"         ,"&&"                                 ,"c" );//create token &&
    t.addTransition("AMPERSAND"     ,"/"         ,"SLASH"         ,"&"                                  ,"c" );//create token &
    t.addTransition("AMPERSAND"     ,FSA::eof    ,"END"           ,"&"                                  ,"c" );//create token &
    t.addTransition("AMPERSAND"     ,""          ,""              ,"expected = or &"                         );//ERROR

    t.addTransition("BAR"           ,operatorStop,"START"         ,"|"                                  ,"cg");//create token |, goBack
    t.addTransition("BAR"           ,FSA::space  ,"START"         ,"|"                                  ,"c" );//create token |
    t.addTransition("BAR"           ,"="         ,"START"         ,"|="                                 ,"c" );//create token |=
    t.addTransition("BAR"           ,"|"         ,"START"         ,"||"                                 ,"c" );//create token ||
    t.addTransition("BAR"           ,"/"         ,"SLASH"         ,"|"                                  ,"c" );//create token |
    t.addTransition("BAR"           ,FSA::eof    ,"END"           ,"|"                                  ,"c" );//create token |
    t.addTransition("BAR"           ,""          ,""              ,"expected = or |"                         );//ERROR

    t.addTransition("IDENTIFIER"    ,identBody   ,"IDENTIFIER"                                               );
    t.addTransition("IDENTIFIER"    ,FSA::space  ,"START"         ,keywords                             ,"e" );//create token identifier
    t.addTransition("IDENTIFIER"    ,FSA::els    ,"START"         ,keywords                             ,"eg");//create token identifier, goBack

    t.addTransition("DOUBLE_QUOTES" ,"\\\\"      ,"DQ_BACKSLASH"                                             );
    t.addTransition("DOUBLE_QUOTES" ,"\""        ,"START"         ,"string"                             ,"e" );//create token string
    t.addTransition("DOUBLE_QUOTES" ,FSA::els    ,"DOUBLE_QUOTES"                                            );
    t.addTransition("DOUBLE_QUOTES" ,FSA::eof    ,""              ,"unexpected end of file for string"       );//ERROR

    t.addTransition("DQ_BACKSLASH"  ,FSA::all    ,"DOUBLE_QUOTES"                                            );
    t.addTransition("DQ_BACKSLASH"  ,FSA::eof    ,""              ,"unexpected end of file for backslash"    );//ERROR

    t.addTransition("QUOTES"        ,"\\\\"      ,"Q_BACKSLASH"                                              );
    t.addTransition("QUOTES"        ,"\'"        ,"START"         ,"char"                               ,"e" );//create token char
    t.addTransition("QUOTES"        ,FSA::els    ,"QUOTES"                                                   );
    t.addTransition("QUOTES"        ,FSA::eof    ,""              ,"unexpected end of file for char"         );//ERROR
    t.addTransition("Q_BACKSLASH"   ,FSA::all    ,"QUOTES"                                                   );
    t.addTransition("Q_BACKSLASH"   ,FSA::eof    ,""              ,"unexpected end of file for backslash"    );//ERROR

    t.addTransition("DOT"           ,FSA::digit  ,"FRACTION"                                                 );
    t.addTransition("DOT"           ,FSA::eof    ,"END"           ,"."                                  ,"c" );//create token .
    t.addTransition("DOT"           ,FSA::els    ,"START"         ,"."                                  ,"cg");//create token ., goBack

    t.addTransition("DIGIT"         ,FSA::digit  ,"DIGIT"                                                    );
    t.addTransition("DIGIT"         ,"eE"        ,"EXPONENT"                                                 );
    t.addTransition("DIGIT"         ,"."         ,"FRACTION"                                                 );
    t.addTransition("DIGIT"         ,FSA::eof    ,"END"           ,"integer"                            ,"e" );//create token integer
    t.addTransition("DIGIT"         ,FSA::els    ,"START"         ,"integer"                            ,"eg");//create token integer, goBack

    t.addTransition("FRACTION"      ,FSA::digit  ,"FRACTION"                                                 );
    t.addTransition("FRACTION"      ,"eE"        ,"EXPONENT"                                                 );
    t.addTransition("FRACTION"      ,FSA::eof    ,"END"           ,"float"                              ,"e" );//create token float
    t.addTransition("FRACTION"      ,FSA::els    ,"START"         ,"float"                              ,"eg");//create token float, goBack

    t.addTransition("EXPONENT"      ,"+-"        ,"EXP_SIGN"                                                 );
    t.addTransition("EXPONENT"      ,FSA::digit  ,"EXP_DIGIT"                                                );
    t.addTransition("EXPONENT"      ,FSA::eof    ,""              ,"unexpected end of file in float exponent");//ERROR
    t.addTransition("EXPONENT"      ,FSA::els    ,""              ,"expected + or - in float exponent"       );//ERROR

    t.addTransition("EXP_SIGN"      ,FSA::digit  ,"EXP_DIGIT"                                                );
    t.addTransition("EXP_SIGN"      ,FSA::eof    ,""              ,"unexpected end of file in float exponent");//ERROR
    t.addTransition("EXP_SIGN"      ,FSA::els    ,""              ,"expected digit in float expoenent"       );//ERROR

    t.addTransition("EXP_DIGIT"     ,FSA::digit  ,"EXP_DIGIT"                                                );
    t.addTransition("EXP_DIGIT"     ,FSA::eof    ,"END"           ,"float"                              ,"e" );//create token float
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

    t.addTransition("LSHIFT"        ,operatorStop,"START"         ,"<<"                                 ,"cg");//create token <<, goBack
    t.addTransition("LSHIFT"        ,FSA::space  ,"START"         ,"<<"                                 ,"c" );//create token <<
    t.addTransition("LSHIFT"        ,"="         ,"START"         ,"<<="                                ,"c" );//create token <<=
    t.addTransition("LSHIFT"        ,"/"         ,"SLASH"         ,"<<"                                 ,"c" );//create token <<
    t.addTransition("LSHIFT"        ,FSA::eof    ,"END"           ,"<<"                                 ,"c" );//create token <<
    t.addTransition("LSHIFT"        ,""          ,""              ,"expected ="                              );//ERROR

    t.addTransition("RSHIFT"        ,operatorStop,"START"         ,">>"                                 ,"cg");//create token >>, goBack
    t.addTransition("RSHIFT"        ,FSA::space  ,"START"         ,">>"                                 ,"c" );//create token >>
    t.addTransition("RSHIFT"        ,"="         ,"START"         ,">>="                                ,"c" );//create token >>=
    t.addTransition("RSHIFT"        ,"/"         ,"SLASH"         ,">>"                                 ,"c" );//create token >>
    t.addTransition("RSHIFT"        ,FSA::eof    ,"END"           ,">>"                                 ,"c" );//create token >>
    t.addTransition("RSHIFT"        ,""          ,""              ,"expected ="                              );//ERROR


    WHEN("parsing i32 a+a;for(i32 i=0;i<32;++i)"){
      t.begin();
      t.parse("i32 a+a;for(i32 i=0;i<32;++i)");
      t.end();
      THEN("it should pass"){
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("i32"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("+"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType(";"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("for"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("("));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("i32"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("="));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("integer"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType(";"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("<"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("integer"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType(";"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("++"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType(")"));
        REQUIRE(t.empty()==true);
      }
    }
  }
   
  GIVEN("simple tokenization"){
    auto csv=std::make_shared<Tokenization>("START");
    csv->addTransition("START" ,","     ,"START" ,","    ,"c" );
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
        REQUIRE(csv->getToken().type==csv->tokenType("value"));
        REQUIRE(csv->empty()==false);
        REQUIRE(csv->getToken().type==csv->tokenType(","));
        REQUIRE(csv->empty()==false);
        REQUIRE(csv->getToken().type==csv->tokenType("value"));
        REQUIRE(csv->empty()==false);
        REQUIRE(csv->getToken().type==csv->tokenType(","));
        REQUIRE(csv->empty()==false);
        REQUIRE(csv->getToken().type==csv->tokenType("value"));
        REQUIRE(csv->empty()==true);
      }
    }
  }

  
  GIVEN("tokenization for csv"){
    auto csv=std::make_shared<Tokenization>("START");
    csv->addTransition("START"    ,","     ,"START"    ,","       ,"c"                   );
    csv->addTransition("START"    ,"\r\n"  ,"LINE-END"                                   );
    csv->addTransition("START"    ,"\\\\"  ,"BACKSLASH",""        ,"b"                   );
    csv->addTransition("START"    ,FSA::els,"STRING"   ,""        ,"b"                   );
    csv->addTransition("START"    ,FSA::eof,"END"                                        );

    csv->addTransition("LINE-END" ,"\r\n"  ,"LINE-END"                                   );
    csv->addTransition("LINE-END" ,FSA::els,"START"    ,"line-end","cg"                  );
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
      THEN("it should pass"){
        Token tok;
        REQUIRE(csv->empty()==false);
        tok = csv->getToken();
        REQUIRE(tok.type==csv->tokenType("value"));
        REQUIRE(tok.rawData == "A");
        REQUIRE(csv->empty()==false);
        tok = csv->getToken();
        REQUIRE(tok.type==csv->tokenType(","));
        REQUIRE(csv->empty()==false);
        tok = csv->getToken();
        REQUIRE(tok.type==csv->tokenType("value"));
        REQUIRE(tok.rawData == "a");
        REQUIRE(csv->empty()==false);
        REQUIRE(csv->getToken().type==csv->tokenType(","));
        REQUIRE(csv->empty()==false);
        tok = csv->getToken();
        REQUIRE(tok.type==csv->tokenType("value"));
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
      "START,^,XOR\n"
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
      "XOR,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,^,g\n"
      "XOR, \\t\\r\\n,START,^\n"
      "XOR,=,START,^=\n"
      "XOR,/,SLASH,^\n"
      "XOR,\\\\e,END,^\n"
      "XOR,,,expected =\n"
      "\n"
      "IDENTIFIER,_a\\\\-zA\\\\-Z0\\\\-9,IDENTIFIER\n"
      "IDENTIFIER, \\t\\r\\n,START,identifier for while if else bool i8 i16 i32 i64 u8 u16 u32 u64 f32 f64 void string struct typedef return,e\n"
      "IDENTIFIER,,START,identifier for while if else bool i8 i16 i32 i64 u8 u16 u32 u64 f32 f64 void string struct typedef return,eg\n"
      "\n"
      "DOUBLE_QUOTES,\\\\\\\\,DQ_BACKSLASH\n"
      "DOUBLE_QUOTES,\",START,string-value,e\n"
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
      "DIGIT,\\\\e,END,integer-value\n"
      "DIGIT,,START,integer-value,eg\n"
      "\n"
      "FRACTION,0\\\\-9,FRACTION\n"
      "FRACTION,eE,EXPONENT\n"
      "FRACTION,\\\\e,END,float-value\n"
      "FRACTION,,START,float-value,eg\n"
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
      "EXP_DIGIT,\\\\e,END,float-value\n"
      "EXP_DIGIT,,START,float-value,eg\n"
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
        REQUIRE(t.getToken().type==t.tokenType("i32"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("+"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType(";"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("for"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("("));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("i32"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("="));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("integer-value"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType(";"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("<"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("integer-value"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType(";"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("++"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType("identifier"));
        REQUIRE(t.empty()==false);
        REQUIRE(t.getToken().type==t.tokenType(")"));
        REQUIRE(t.empty()==true);
      }
    }
  }
  GIVEN("tokenization for syntax"){
    auto syn=std::make_shared<Tokenization>("START");
    syn->addTransition("START"   ," \t"   ,"SPACE"                   );
    syn->addTransition("START"   ,"\r\n"  ,"LINE-END"                );
    syn->addTransition("START"   ,FSA::els,"STRING"  ,""        ,"b" );
    syn->addTransition("START"   ,FSA::eof,"END"                     );

    syn->addTransition("SPACE"   ," \t"   ,"SPACE"                   );
    syn->addTransition("SPACE"   ,"\r\n"  ,"LINE-END"                );
    syn->addTransition("SPACE"   ,FSA::els,"STRING"  ,""        ,"b" );
    syn->addTransition("SPACE"   ,FSA::eof,"END"                     );

    syn->addTransition("LINE-END"," \t"   ,"SPACE"   ,"line-end"     );
    syn->addTransition("LINE-END","\r\n"  ,"LINE-END"                );
    syn->addTransition("LINE-END",FSA::els,"STRING"  ,"line-end","b" );
    syn->addTransition("LINE-END",FSA::eof,"END"                     );

    syn->addTransition("STRING"  ," \t"   ,"SPACE"   ,"value"   ,"e" );
    syn->addTransition("STRING"  ,"\r\n"  ,"LINE-END","value"   ,"eg");
    syn->addTransition("STRING"  ,FSA::els,"STRING"                  );
    syn->addTransition("STRING"  ,FSA::eof,"END"     ,"value"   ,"e" );

    WHEN("parsing A a B\\nC c D"){
      syn->begin();
      syn->parse("A a B\nC c D");
      syn->end();
      THEN("it should pass"){
        Token tok;
        REQUIRE(syn->empty()==false);
        tok = syn->getToken();
        REQUIRE(tok.type==syn->tokenType("value"));
        REQUIRE(tok.rawData == "A");

        REQUIRE(syn->empty()==false);
        tok = syn->getToken();
        REQUIRE(tok.type==syn->tokenType("value"));
        REQUIRE(tok.rawData == "a");

        REQUIRE(syn->empty()==false);
        tok = syn->getToken();
        REQUIRE(tok.type==syn->tokenType("value"));
        REQUIRE(tok.rawData == "B");

        REQUIRE(syn->empty()==false);
        tok = syn->getToken();
        REQUIRE(tok.type==syn->tokenType("line-end"));

        REQUIRE(syn->empty()==false);
        tok = syn->getToken();
        REQUIRE(tok.type==syn->tokenType("value"));
        REQUIRE(tok.rawData == "C");

        REQUIRE(syn->empty()==false);
        tok = syn->getToken();
        REQUIRE(tok.type==syn->tokenType("value"));
        REQUIRE(tok.rawData == "c");

        REQUIRE(syn->empty()==false);
        tok = syn->getToken();
        REQUIRE(tok.type==syn->tokenType("value"));
        REQUIRE(tok.rawData == "D");

        REQUIRE(syn->empty()==true);
      }
    }
  }
}
