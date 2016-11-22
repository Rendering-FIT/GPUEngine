#include<geCore/Dtemplates.h>
#include<geCore/fsa/MealyMachine.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;

SCENARIO("Basic Mealy Machine tests"){
  //This machine reads + - ++ -- and count their appereances 
  //When other symbol is recived, the machine reads everything and remember
  //first position of non +,- symbol and count number of characters
  MealyMachine mm;
  size_t plusCounter       = 0;
  size_t plusPlusCounter   = 0;
  size_t minusCounter      = 0;
  size_t minusMinusCounter = 0;
  size_t position          = 0;
  size_t length            = 0;

  auto S = mm.addState();
  auto P = mm.addState();
  auto M = mm.addState();
  auto E = mm.addState();

  mm.addTransition    (S,"+",P);
  mm.addTransition    (S,"-",M);
  mm.addElseTransition(S    ,E,[&](MealyMachine*){position = mm.getReadingPosition();length++;});
  mm.addEOFTransition (S);

  mm.addTransition    (P,"+",S,[&](MealyMachine*){plusPlusCounter++;});
  mm.addTransition    (P,"-",M,[&](MealyMachine*){plusCounter++;});
  mm.addElseTransition(P,    S,[&](MealyMachine*){mm.dontMove();plusCounter++;});
  mm.addEOFTransition (P,      [&](MealyMachine*){plusCounter++;});

  mm.addTransition    (M,"-",S,[&](MealyMachine*){minusMinusCounter++;});
  mm.addTransition    (M,"+",P,[&](MealyMachine*){minusCounter++;});
  mm.addElseTransition(M,    S,[&](MealyMachine*){mm.dontMove();minusCounter++;});
  mm.addEOFTransition (M,      [&](MealyMachine*){minusCounter++;});

  //if there are no other transitions, ElseTransition behaves as AllTransition
  mm.addElseTransition(E,E,[&](MealyMachine*){length++;});
  mm.addEOFTransition (E);

  auto str0 = "++--+-+-++-a++-+";
  mm.begin();
  auto result = mm.parse(str0);
  mm.end();

  REQUIRE(result == true);
  REQUIRE(plusCounter       == 2 );
  REQUIRE(plusPlusCounter   == 2 );
  REQUIRE(minusCounter      == 3 );
  REQUIRE(minusMinusCounter == 1 );
  REQUIRE(position          == 11);
  REQUIRE(length            == 5 );
}

SCENARIO("mealyMachine transition test"){
  MealyMachine mm;
  mm.setQuiet(true);
  auto start = mm.addState();
  auto end   = mm.addState();
  mm.addTransition(start,"+-",end);
  mm.addTransition(start,"0","9",end);
  mm.addEOFTransition(end);
  mm.begin();
  REQUIRE(mm.parse("+")==true);
  REQUIRE(mm.end()==true);
  mm.begin();
  REQUIRE(mm.parse("-")==true);
  REQUIRE(mm.end()==true);
  mm.begin();
  REQUIRE(mm.parse("a")==false);
  REQUIRE(mm.end()==false);
  mm.begin();
  REQUIRE(mm.parse("0")==true);
  REQUIRE(mm.end()==true);
  mm.begin();
  REQUIRE(mm.parse("9")==true);
  REQUIRE(mm.end()==true);
  mm.begin();
  REQUIRE(mm.parse("5")==true);
  REQUIRE(mm.end()==true);
}

SCENARIO("isFloat Mealy Machine test"){
  MealyMachine mm;
  auto start            = mm.addState("start"           );
  auto sign             = mm.addState("sign"            );
  auto immediateDot     = mm.addState("immediateDot"    );
  auto fractionalNumber = mm.addState("fractionalNumber");
  auto wholeNumber      = mm.addState("whileNumber"     );
  auto exponent         = mm.addState("exponent"        );
  auto postfix          = mm.addState("postfix"         );
  auto exponentSign     = mm.addState("exponentSign"    );
  auto exponentNumber   = mm.addState("exponentNumber"  );
  mm.addTransition   (start           ,"+-"   ,sign            );
  mm.addTransition   (start           ,"."    ,immediateDot    );
  mm.addTransition   (start           ,"0","9",wholeNumber     );
  mm.addTransition   (sign            ,"."    ,immediateDot    );
  mm.addTransition   (sign            ,"0","9",wholeNumber     );
  mm.addTransition   (immediateDot    ,"0","9",fractionalNumber);
  mm.addTransition   (wholeNumber     ,"0","9",wholeNumber     );
  mm.addTransition   (wholeNumber     ,"."    ,fractionalNumber);
  mm.addTransition   (wholeNumber     ,"fF"   ,postfix         );
  mm.addTransition   (wholeNumber     ,"eE"   ,exponent        );
  mm.addEOFTransition(wholeNumber                              );
  mm.addTransition   (fractionalNumber,"0","9",fractionalNumber);
  mm.addTransition   (fractionalNumber,"fF"   ,postfix         );
  mm.addTransition   (fractionalNumber,"eE"   ,exponent        );
  mm.addEOFTransition(fractionalNumber                         );
  mm.addEOFTransition(postfix                                  );
  mm.addTransition   (exponent        ,"+-"   ,exponentSign    );
  mm.addTransition   (exponent        ,"0","9",exponentNumber  );
  mm.addTransition   (exponentSign    ,"0","9",exponentNumber  );
  mm.addTransition   (exponentNumber  ,"0","9",exponentNumber  );
  mm.addTransition   (exponentNumber  ,"fF"   ,postfix         );
  mm.addEOFTransition(exponentNumber                           );
  mm.setQuiet(true);

  mm.begin();
  REQUIRE(mm.parse("1")==true);
  REQUIRE(mm.end());
  mm.begin();
  REQUIRE(mm.parse("1f")==true);
  REQUIRE(mm.end());
  mm.begin();
  REQUIRE(mm.parse("1.")==true);
  REQUIRE(mm.end());
  mm.begin();
  REQUIRE(mm.parse("1.f")==true);
  REQUIRE(mm.end());
  mm.begin();
  REQUIRE(mm.parse(".1f")==true);
  REQUIRE(mm.end());
  mm.begin();
  REQUIRE(mm.parse("1e1")==true);
  REQUIRE(mm.end());
  mm.begin();
  REQUIRE(mm.parse("1e+1")==true);
  REQUIRE(mm.end());
  mm.begin();
  REQUIRE(mm.parse("1e-12f")==true);
  REQUIRE(mm.end());
  mm.begin();
  REQUIRE(mm.parse("+1.1e+1f")==true);
  REQUIRE(mm.end());
  mm.begin();
  REQUIRE(mm.parse("-.1E-31F")==true);
  REQUIRE(mm.end());
  mm.begin();
  REQUIRE(mm.parse("1000")==true);
  REQUIRE(mm.end());
  mm.begin();
  REQUIRE(mm.parse(".F")==false);
  REQUIRE(mm.end()==false);
}
