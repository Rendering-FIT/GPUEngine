#include<geCore/fsa/fsa.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;

void registerStart(ge::core::FSA*fsa,void*data){
  *(unsigned*)data=fsa->getCurrentPosition();
}

struct ReadData{
  unsigned startPosition = 0;
  std::string read = "";
};

void getReadData(ge::core::FSA*fsa,void*data){
  ReadData*rd=(ReadData*)data;
  rd->read=fsa->getAlreadyReadString().substr(rd->startPosition);
}

SCENARIO("FSA basic tests"){
  GIVEN("empty FSA with only start symbol"){
    FSA fsaa("S");
    WHEN("parsing word"){
      THEN("it should fail"){
        REQUIRE(fsaa.run("word")==false);
      }
    }
    WHEN("parsing empty word"){
      THEN("it should pass"){
        REQUIRE(fsaa.run("")==false);
      }
    }
  }
}

void createPgoBack(ge::core::FSA*fsa,void*data){
  std::vector<unsigned>*op=(std::vector<unsigned>*)(data);
  op->push_back(0);
  fsa->goBack();
}

void createP(ge::core::FSA*,void*data){
  std::vector<unsigned>*op=(std::vector<unsigned>*)(data);
  op->push_back(0);
}

void createPP(ge::core::FSA*,void*data){
  std::vector<unsigned>*op=(std::vector<unsigned>*)(data);
  op->push_back(1);
}

void createMgoBack(ge::core::FSA*fsa,void*data){
  std::vector<unsigned>*op=(std::vector<unsigned>*)(data);
  op->push_back(2);
  fsa->goBack();
}

void createM(ge::core::FSA*,void*data){
  std::vector<unsigned>*op=(std::vector<unsigned>*)(data);
  op->push_back(2);
}

void createMM(ge::core::FSA*,void*data){
  std::vector<unsigned>*op=(std::vector<unsigned>*)(data);
  op->push_back(3);
}

SCENARIO("FSA goBack tests","[FSA]"){
  GIVEN("operator FSA"){
    std::vector<unsigned>op;
    FSA fsa(
        "START",
        "START","+"               ,"PLUS" ,
        "START","-"               ,"MINUS",
        "START",ge::core::FSA::eof,"END"  ,
        "PLUS" ,"+"               ,"START",createPP     ,(void*)&op,//create ++
        "PLUS" ,"-"               ,"START",createPgoBack,(void*)&op,//create +, goBack
        "PLUS" ,ge::core::FSA::eof,"END"  ,createP      ,(void*)&op,//create +
        "MINUS","-"               ,"START",createMM     ,(void*)&op,//create -, goBack
        "MINUS","+"               ,"START",createMgoBack,(void*)&op,//create --
        "MINUS",ge::core::FSA::eof,"END"  ,createM      ,(void*)&op //create -
        );
    WHEN("lexin ++--"){
      THEN("then it should pass and parse ++ --"){
        REQUIRE(fsa.run("++--")==true);
        REQUIRE(op.size()==2);
        REQUIRE(op[0]==1);
        REQUIRE(op[1]==3);
      }
    }
    WHEN("lexin +++---"){
      THEN("then it should pass and parse ++ + -- -"){
        REQUIRE(fsa.run("+++---")==true);
        REQUIRE(op.size()==4);
        REQUIRE(op[0]==1);
        REQUIRE(op[1]==0);
        REQUIRE(op[2]==3);
        REQUIRE(op[3]==2);
      }
    }
    WHEN("lexin +-++-+---+"){
      THEN("then it should pass and parse + - ++ - + -- - +"){
        REQUIRE(fsa.run("+-++-+---+")==true);
        REQUIRE(op.size()==8);
        REQUIRE(op[0]==0);
        REQUIRE(op[1]==2);
        REQUIRE(op[2]==1);
        REQUIRE(op[3]==2);
        REQUIRE(op[4]==0);
        REQUIRE(op[5]==3);
        REQUIRE(op[6]==2);
        REQUIRE(op[7]==0);
      }
    }

  }
}

//*
SCENARIO( "FSA float test", "[FSA]" ) {
  GIVEN( "float FSA" ) {
    unsigned startPos = 0;
    ReadData readData;
    std::string exponent  = "eE" ;
    std::string sufix     = "f"  ;
    std::string delimiter = "."  ;
    std::string sign      = "+-" ;

    FSA fsa(
//    std::shared_ptr<FSA>fsa=std::make_shared<FSA>(

      "S",
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
      "C",ge::core::FSA::eof  ,"X",getReadData,(void*)&readData,
      "D",ge::core::FSA::digit,"D",
      "D",exponent            ,"E",
      "D",sufix               ,"H",
//      "D",ge::core::FSA::els  ,"S",getReadData,(void*)&readData,
      "D",ge::core::FSA::eof  ,"X",getReadData,(void*)&readData,
      "E",sign                ,"F",
      "E",ge::core::FSA::digit,"G",
      "F",ge::core::FSA::digit,"G",
      "G",ge::core::FSA::digit,"G",
      "G",sufix               ,"H",
//      "G",ge::core::FSA::els  ,"S",getReadData,(void*)&readData,
      "G",ge::core::FSA::eof  ,"X",getReadData,(void*)&readData,
//      "H",ge::core::FSA::els  ,"S",getReadData,(void*)&readData,
      "H",ge::core::FSA::eof  ,"X",getReadData,(void*)&readData);

    WHEN( "lexing \"+832.3232e32f\"" ) {
      THEN( "it should pass and read \"+832.3232e32f\"" ) {
        REQUIRE(fsa.run("+832.3232e32f")==true);
        REQUIRE(readData.read=="+832.3232e32f");
      }
    }
    WHEN( "lexing \"10\""){
      THEN( "it should pass and read \"10\""){
        REQUIRE(fsa.run("10")==true);
        REQUIRE(readData.read=="10");
      }
    }
    WHEN( "lexing \"10asd\""){
      THEN( "it should fail"){
        REQUIRE(fsa.run("10asd")==false);
      }
    }
    WHEN( "lexing \"10.10f\""){
      THEN( "it should pass and read \"10.10f\""){
        REQUIRE(fsa.run("10.10f")==true);
        REQUIRE(readData.read=="10.10f");
      }
    }
    
    WHEN( "minimalizing and lexing \"+832.3232e32f\""){
      fsa.minimalize();
      THEN( "it should pass and read \"+832.3232e32f\""){
        REQUIRE(fsa.run("+832.3232e32f")==true);
        REQUIRE(readData.read=="+832.3232e32f");
      }
    }
  }
/*
  GIVEN ("fsa with undistinguishable states"){
    FSA fsa(
    //std::shared_ptr<FSA>fsa=std::make_shared<FSA>(
        "S",
      "S","a","A",
      "S","b","B",
      "A","a","AA",
      "B","a","BB",
      "AA","c","C",
      "BB","c","C",
      "C","c","D",
      "D",ge::core::FSA::eof,"E");
    WHEN("minimalizing"){
      fsa.minimalize();
      THEN( "it should have merged states"){
        std::set<std::string>finalStates={
          "AB",
          "AABB",
          "C",
          "D",
          "E",
          "S"};
        
        for(auto x:fsa)
          std::cout<<"0- "<<x.first<<std::endl;

        for(auto x:fsa){
          std::cout<<"0 "<<x.first<<std::endl;
          REQUIRE(finalStates.find(x.second->getName())!=finalStates.end());
        }
      }
    }
  }
  GIVEN ("fsa with unreachable states"){
    FSA fsa(
    //std::shared_ptr<FSA>fsa=std::make_shared<FSA>(
        "S",
      "S","a","A",
      "S","b","B",
      "A","a","AA",
      "B","a","BB",
      "AA","c","C",
      "BB","c","C",
      "C","c","D",
      "G","r","K",
      "G","a","AA",
      "D",ge::core::FSA::eof,"E");
    WHEN("minimalizing"){
      fsa.minimalize();
      THEN( "it should have fewer states"){
        std::set<std::string>finalStates{
          "AABB",
          "AB",
          "C",
          "D",
          "E",
          "S"
        };
        for(auto x:fsa)
          std::cout<<"1- "<<x.first<<std::endl;

        for(auto x:fsa){
          std::cout<<"1 "<<x.first<<std::endl;
          REQUIRE(finalStates.find(x.second->getName())!=finalStates.end());
        }
      }
    }

  }
  */
}
// */
/*
SCENARIO( "FSA operator tests", "[FSA]" ) {
  GIVEN("two fsa"){
    std::shared_ptr<FSA>fsa0=std::make_shared<FSA>("S",
        "S","a","A",
        "A","b","B",
        "B",ge::core::FSA::eof,"E");
    std::shared_ptr<FSA>fsa1=std::make_shared<FSA>("S",
        "S","c","C",
        "C","b","B",
        "B",ge::core::FSA::eof,"E");
    WHEN("uniting"){
      auto fsa=*fsa0+*fsa1;
      THEN("it should parse words from both languages"){
        REQUIRE(fsa.run("ab")==true);
        REQUIRE(fsa.run("cb")==true);
      }
    }
  }
}
*/
