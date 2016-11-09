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
  mm.addElseTransition(S    ,E,[&](){position = mm.getReadingPosition();length++;});
  mm.addEOFTransition (S);

  mm.addTransition    (P,"+",S,[&](){plusPlusCounter++;});
  mm.addTransition    (P,"-",M,[&](){plusCounter++;});
  mm.addElseTransition(P,    S,[&](){mm.dontMove();plusCounter++;});
  mm.addEOFTransition (P,      [&](){plusCounter++;});

  mm.addTransition    (M,"-",S,[&](){minusMinusCounter++;});
  mm.addTransition    (M,"+",P,[&](){minusCounter++;});
  mm.addElseTransition(M,    S,[&](){mm.dontMove();minusCounter++;});
  mm.addEOFTransition (M,      [&](){minusCounter++;});

  //if there are no other transitions, ElseTransition behaves as AllTransition
  mm.addElseTransition(E,E,[&](){length++;});
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

SCENARIO("isFloat Mealy Machine test"){
  MealyMachine mm;
  auto Start        = mm.addState();
  auto Sign         = mm.addState();
  auto ImmediateDot = mm.addState();
  auto Dot          = mm.addState();
  auto WholeNumber  = mm.addState();
  mm.addTransition(Start,"+",Sign);
  mm.addTransition(Start,"-",Sign);
  mm.addTransition(Start,".",ImmediateDot);
}
