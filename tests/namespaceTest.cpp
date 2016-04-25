#include<geCore/Namespace.h>
#include<iostream>
#include<sstream>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;

SCENARIO( "namespace tests", "[Namespace]" ) {
  auto r=std::make_shared<TypeRegister>();
  auto n=std::make_shared<ge::core::sim::Namespace>("*");
  WHEN("adding variable a of type i32"){
    THEN("namespace should contain it"){
      n->insert("a",r->sharedResource("i32"));
      REQUIRE(n->contain("a")==true);
    }
    THEN("setting value of variable a should be doable"){
      n->insert("a",r->sharedResource("i32"));
      n->get<int32_t&>("a")=32;
      REQUIRE(n->get<int32_t>("a")==32);
    }
  }
}

