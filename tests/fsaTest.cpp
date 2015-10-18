#define CATCH_CONFIG_MAIN
#include"catch.hpp"

#include<geCore/fsa/fsa.h>

using namespace ge::core;

void registerStart(ge::core::FSA*fsa,void*data){
  *(unsigned*)data=fsa->getCurrentPosition();
}

struct ReadData{
  unsigned startPosition;
  std::string read;
};

void getReadData(ge::core::FSA*fsa,void*data){
  ReadData*rd=(ReadData*)data;
  rd->read=fsa->getAlreadyReadString().substr(rd->startPosition);
}

SCENARIO( "FSA float test", "[FSA]" ) {

  GIVEN( "float FSA" ) {
    unsigned startPos;
    ReadData readData;
    std::string exponent  = "eE" ;
    std::string sufix     = "f"  ;
    std::string delimiter = "."  ;
    std::string sign      = "+-" ;

    std::shared_ptr<FSA>fsa=std::make_shared<FSA>("S",
      "S",sign                ,"A",registerStart,(void*)&startPos,
      "S",delimiter           ,"B",registerStart,(void*)&startPos,
      "S",ge::core::FSA::digit,"C",registerStart,(void*)&startPos,
//      "S",ge::core::FSA::els  ,"S",
      "A",delimiter           ,"B",
      "A",ge::core::FSA::digit,"C",
      "B",ge::core::FSA::digit,"D",
      "C",ge::core::FSA::digit,"C",
      "C",delimiter           ,"D",
      "C",exponent            ,"E",
      "C",sufix               ,"H",
//      "C",ge::core::FSA::els  ,"S",getReadData,(void*)&readData,
      "C",ge::core::FSA::eof  ,"S",getReadData,(void*)&readData,
      "D",ge::core::FSA::digit,"D",
      "D",exponent            ,"E",
      "D",sufix               ,"H",
//      "D",ge::core::FSA::els  ,"S",getReadData,(void*)&readData,
      "D",ge::core::FSA::eof  ,"S",getReadData,(void*)&readData,
      "E",sign                ,"F",
      "E",ge::core::FSA::digit,"G",
      "F",ge::core::FSA::digit,"G",
      "G",ge::core::FSA::digit,"G",
      "G",sufix               ,"H",
//      "G",ge::core::FSA::els  ,"S",getReadData,(void*)&readData,
      "G",ge::core::FSA::eof  ,"S",getReadData,(void*)&readData,
//      "H",ge::core::FSA::els  ,"S",getReadData,(void*)&readData,
      "H",ge::core::FSA::eof  ,"S",getReadData,(void*)&readData);

    WHEN( "lexing \"+832.3232e32f\"" ) {
      THEN( "it should pass and read \"+832.3232e32f\"" ) {
        REQUIRE(fsa->run("+832.3232e32f")==true);
        REQUIRE(readData.read=="+832.3232e32f");
      }
    }
    WHEN( "lexing \"10\""){
      THEN( "it should pass and read \"10\""){
        REQUIRE(fsa->run("10")==true);
        REQUIRE(readData.read=="10");
      }
    }
    WHEN( "lexing \"10asd\""){
      THEN( "it should fail"){
        REQUIRE(fsa->run("10asd")==false);
      }
    }
    WHEN( "lexing \"10.10f\""){
      THEN( "it should pass and read \"10.10f\""){
        REQUIRE(fsa->run("10.10f")==true);
        REQUIRE(readData.read=="10.10f");
      }
    }
  }
}

