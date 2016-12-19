#include<geUtil/ArgumentViewer.h>
#include<iostream>
#include<fstream>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::util;
using namespace std;

SCENARIO("Basic ArgumentViewer implicit cast tests"){
  char const*args[] = {"test","a","1.3f","b","+1.1e1f","c","-.2e2f","d","12","e","+13","f","-122","g","1.4","h","+1.5","i","-1.6"};
  int const nofArgs = sizeof(args)/sizeof(char const*);
  auto a = make_shared<ArgumentViewer>(nofArgs,(char**)args);
  REQUIRE(a->getApplicationName()=="test");
  REQUIRE(a->getNofArguments()==nofArgs-1);
  REQUIRE(a->getf32("a",0.f)==1.3f);
  REQUIRE(a->getf32("b",0.f)==1.1e1f);
  REQUIRE(a->getf32("c",0.f)==-.2e2f);
  REQUIRE(a->getf32("d",0.f)==12.f);
  REQUIRE(a->getf32("e",0.f)==13.f);
  REQUIRE(a->getf32("f",0.f)==-122.f);
  REQUIRE(a->getf32("g",0.f)==1.4f);
  REQUIRE(a->getf32("h",0.f)==1.5f);
  REQUIRE(a->getf32("i",0.f)==-1.6f);
}

SCENARIO("ArgumentViewer - default value tests"){
  char const*args[] = {"test"};
  int const nofArgs = sizeof(args)/sizeof(char const*);
  auto a = make_shared<ArgumentViewer>(nofArgs,(char**)args);
  REQUIRE(a->getApplicationName()=="test");
  REQUIRE(a->getf32("a",1.1f)==1.1f);
  REQUIRE(a->getf64("a",1.1 )==1.1 );
  REQUIRE(a->geti32("a",-111)==-111);
  REQUIRE(a->geti64("a",-222)==-222);
  REQUIRE(a->getu32("a",1212)==1212);
  REQUIRE(a->getu64("a",3212)==3212);
  REQUIRE(a->gets  ("a","ah")=="ah");
  REQUIRE(a->getf32v("a",{1.1f})==std::vector<float      >({1.1f}));
  REQUIRE(a->getf64v("a",{1.1 })==std::vector<double     >({1.1 }));
  REQUIRE(a->geti32v("a",{-111})==std::vector<int32_t    >({-111}));
  REQUIRE(a->geti64v("a",{-222})==std::vector<int64_t    >({-222}));
  REQUIRE(a->getu32v("a",{1212})==std::vector<uint32_t   >({1212}));
  REQUIRE(a->getu64v("a",{3212})==std::vector<uint64_t   >({3212}));
  REQUIRE(a->getsv  ("a",{"ah"})==std::vector<std::string>({"ah"}));
}

SCENARIO("Basic ArgumentViewer tests"){
  char const*args[] = {"test","a","13.3f","b","1","2","c","14.4","13.3","word","hello","types","{","GL_RGB","GL_GBR","GL_RGBA32UI","}"};
  int const nofArgs = sizeof(args)/sizeof(char const*);
  auto a = make_shared<ArgumentViewer>(nofArgs,(char**)args);
  REQUIRE(a->getApplicationName()=="test");
  REQUIRE(a->getNofArguments()==nofArgs-1);
  REQUIRE(a->getArgument(2)=="b");
  REQUIRE(a->getf32("a",10.f)==13.3f);
  REQUIRE(a->geti32v("b",{0,0,0})==std::vector<int32_t>({1,2,0}));
  REQUIRE(a->getf32("b",3.f)==1.f);
  REQUIRE(a->getf64v("c",{0.,0.,0.})==std::vector<double>({14.4,13.3,0.}));
  REQUIRE(a->isPresent("a")==true);
  REQUIRE(a->isPresent("d")==false);
  REQUIRE(a->gets("word","none")=="hello");
  REQUIRE(a->gets("word2","none")=="none");
  REQUIRE(a->getsv("types",{"a","b","c","d"})==std::vector<std::string>({"GL_RGB","GL_GBR","GL_RGBA32UI","d"}));
}

SCENARIO("Basic ArgumentViewer context tests"){
  char const*args[] = {"test","a","b","light","{","a","b","c","}","d"};
  int const nofArgs = sizeof(args)/sizeof(char const*);
  auto a = make_shared<ArgumentViewer>(nofArgs,(char**)args);
  REQUIRE(a->getApplicationName()=="test");
  REQUIRE(a->isPresent("a")==true );
  REQUIRE(a->isPresent("b")==true );
  REQUIRE(a->isPresent("c")==false);
  REQUIRE(a->isPresent("d")==true );
  REQUIRE(a->getContext("light")->isPresent("a")==true);
  REQUIRE(a->getContext("light")->isPresent("b")==true);
  REQUIRE(a->getContext("light")->isPresent("c")==true);
}

SCENARIO("Complex ArgumentViewer context tests"){
  char const*args[] = {"test","a","b","light","{","a","b","position","{","a","b","}","c","}"};
  int const nofArgs = sizeof(args)/sizeof(char const*);
  auto a = make_shared<ArgumentViewer>(nofArgs,(char**)args);
  REQUIRE(a->getApplicationName()=="test");
  REQUIRE(a->isPresent("a")==true );
  REQUIRE(a->isPresent("b")==true );
  REQUIRE(a->isPresent("c")==false);
  REQUIRE(a->getContext("light")->isPresent("a")==true);
  REQUIRE(a->getContext("light")->isPresent("b")==true);
  REQUIRE(a->getContext("light")->isPresent("c")==true);
  REQUIRE(a->getContext("light")->getContext("position")->isPresent("a")==true);
  REQUIRE(a->getContext("light")->getContext("position")->isPresent("b")==true);
}

SCENARIO("ArgumentViewer file tests"){
  std::ofstream("args0")<<"a b c < args1.txt"<<std::endl;
  std::ofstream("args1.txt")<<"#ahoj \nposition { a b }\n #dormon\n"<<std::endl;
  char const*args[] = {"test","a","light","{","<","args0.txt","}","b"};
  int const nofArgs = sizeof(args)/sizeof(char const*);
  auto a = make_shared<ArgumentViewer>(nofArgs,(char**)args);
  REQUIRE(a->getApplicationName()=="test");
  REQUIRE(a->isPresent("a")==true );
  REQUIRE(a->isPresent("b")==true );
  REQUIRE(a->getContext("light")->isPresent("a")==true);
  REQUIRE(a->getContext("light")->isPresent("b")==true);
  REQUIRE(a->getContext("light")->isPresent("c")==true);
  REQUIRE(a->getContext("light")->getContext("position")->isPresent("a")==true);
  REQUIRE(a->getContext("light")->getContext("position")->isPresent("b")==true);
}






