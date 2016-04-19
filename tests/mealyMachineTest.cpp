#include<geCore/dtemplates.h>
#include<geCore/fsa/MealyMachine.h>
#include<geCore/fsa/TransitionChooser.h>
#include<geCore/fsa/MapTransitionChooser.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;

struct Data{
  size_t plusCounter       = 0;
  size_t plusPlusCounter   = 0;
  size_t minusCounter      = 0;
  size_t minusMinusCounter = 0;
  size_t position          = 0;
  size_t length            = 0;
};

void addPP(MealyMachine*,void* const&data){
  Data*d = (Data*)data;
  d->plusPlusCounter++;
}

void addP(MealyMachine*,void* const&data){
  Data*d = (Data*)data;
  d->plusCounter++;
}

void addMM(MealyMachine*,void* const&data){
  Data*d = (Data*)data;
  d->minusMinusCounter++;
}

void addM(MealyMachine*,void* const&data){
  Data*d = (Data*)data;
  d->minusCounter++;
}

void startNonPM(MealyMachine*mm,void* const&data){
  Data*d = (Data*)data;
  //getReadingPosition() is offset in bytes from beginning of reading
  //it return current number of read bytes
  d->position = mm->getReadingPosition();
  d->length++;
}

void countNonPM(MealyMachine*,void* const&data){
  Data*d = (Data*)data;
  d->length++;
}

void addPDontMove(MealyMachine*mm,void* const&data){
  Data*d = (Data*)data;
  d->plusCounter++;
  //dontMove will tell Mealy Machine to not update reading position
  mm->dontMove();
}

void addMDontMove(MealyMachine*mm,void* const&data){
  Data*d = (Data*)data;
  d->minusCounter++;
  mm->dontMove();
}




SCENARIO("Basic Mealy Machine tests"){
  //This machine reads + - ++ -- and count their appereances 
  //When other symbol is recived, the machine reads everything and remember
  //first position of non +,- symbol and count number of characters
  size_t largestState = 1;
  MealyMachine mm(largestState);

  Data data;

  //all states, each has size 1
  //every transition will consume 1 sizeof(BasicUnit) of bytes (1*sizeof(uint8_t))
  auto S = mm.addState(std::make_shared<MapTransitionChooser<1>>());
  auto P = mm.addState(std::make_shared<MapTransitionChooser<1>>());
  auto M = mm.addState(std::make_shared<MapTransitionChooser<1>>());
  auto E = mm.addState(std::make_shared<MapTransitionChooser<1>>());

  mm.addTransition(S,std::vector<MealyMachine::BasicUnit>{'+'}.data(),P);
  mm.addTransition(S,std::vector<MealyMachine::BasicUnit>{'-'}.data(),M);
  mm.addElseTransitions(S,E,startNonPM,&data);
  mm.addEOFTransition(S);

  mm.addTransition(P,std::vector<MealyMachine::BasicUnit>{'+'}.data(),S,addPP,&data);
  mm.addTransition(P,std::vector<MealyMachine::BasicUnit>{'-'}.data(),M,addP ,&data);
  mm.addElseTransitions(P,S,addPDontMove,&data);
  mm.addEOFTransition(P,addP,&data);

  mm.addTransition(M,std::vector<MealyMachine::BasicUnit>{'-'}.data(),S,addMM,&data);
  mm.addTransition(M,std::vector<MealyMachine::BasicUnit>{'+'}.data(),P,addM ,&data);
  mm.addElseTransitions(M,S,addMDontMove,&data);
  mm.addEOFTransition(M,addM,&data);

  //if there are no other transitions, ElseTransition behaves as AllTransition
  mm.addElseTransitions(E,E,countNonPM,&data);
  mm.addEOFTransition(E);

  auto str0 = "++--+-+-++-a++-+";
  mm.begin();
  auto result = mm.parse((MealyMachine::BasicUnit const*)str0,std::strlen(str0));
  mm.end();

  REQUIRE(result == true);
  REQUIRE(data.plusCounter       == 2 );
  REQUIRE(data.plusPlusCounter   == 2 );
  REQUIRE(data.minusCounter      == 3 );
  REQUIRE(data.minusMinusCounter == 1 );
  REQUIRE(data.position          == 11);
  REQUIRE(data.length            == 5 );
}
