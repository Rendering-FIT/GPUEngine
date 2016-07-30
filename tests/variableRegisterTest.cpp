#include<geDE/TypeRegister.h>
#include<geDE/FunctionRegister.h>
#include<geDE/VariableRegister.h>
#include<geDE/NameRegister.h>
#include<geDE/StdFunctions.h>
#include<iostream>
#include<sstream>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::de;

SCENARIO( "variableRegister tests", "[VariableRegister]" ) {
//#define SHOWCERR
#ifndef SHOWCERR
    std::stringstream oss;
    auto old = std::cerr.rdbuf( oss.rdbuf() );
#endif

  auto tr=std::make_shared<TypeRegister>();
  auto nr=std::make_shared<NameRegister>();
  auto fr=std::make_shared<FunctionRegister>(tr,nr);
  auto vr=std::make_shared<VariableRegister>("*");
  registerStdFunctions(fr);
  WHEN("adding variable a of type i32"){
    THEN("variableRegister should contain it"){
      vr->insert("a",std::dynamic_pointer_cast<Nullary>(fr->sharedFunction("Nullary")));
      REQUIRE(vr->hasVariable("a")==true);
    }
    THEN("setting value of variable a should be doable"){
      vr->insert("a",std::dynamic_pointer_cast<Nullary>(fr->sharedFunction("Nullary")));
      vr->getVariable("a")->bindOutput(fr,tr->sharedResource("i32"));
      (int32_t&)(*vr->getVariable("a")->getOutputData())=32;
      REQUIRE((int32_t&)(*vr->getVariable("a")->getOutputData())==32);
    }
  }
  WHEN("adding variables a.var0 a.var1 a.var2 b.var0 b.var1 c.var0 c.var2"){
    vr->insert("a.var0",std::dynamic_pointer_cast<Nullary>(fr->sharedFunction("Nullary")));
    vr->insert("a.var1",std::dynamic_pointer_cast<Nullary>(fr->sharedFunction("Nullary")));
    vr->insert("a.var2",std::dynamic_pointer_cast<Nullary>(fr->sharedFunction("Nullary")));
    vr->insert("b.var0",std::dynamic_pointer_cast<Nullary>(fr->sharedFunction("Nullary")));
    vr->insert("b.var1",std::dynamic_pointer_cast<Nullary>(fr->sharedFunction("Nullary")));
    vr->insert("c.var0",std::dynamic_pointer_cast<Nullary>(fr->sharedFunction("Nullary")));
    vr->insert("c.var2",std::dynamic_pointer_cast<Nullary>(fr->sharedFunction("Nullary")));
    REQUIRE(vr->hasVariableRegister("a")==true);
    REQUIRE(vr->hasVariableRegister("b")==true);
    REQUIRE(vr->hasVariableRegister("c")==true);
    REQUIRE(vr->hasVariable("x")==false);
    REQUIRE(vr->hasVariable("a.var0")==true);
    REQUIRE(vr->hasVariable("a.var1")==true);
    REQUIRE(vr->hasVariable("a.var2")==true);
    REQUIRE(vr->hasVariable("b.var0")==true);
    REQUIRE(vr->hasVariable("b.var1")==true);
    REQUIRE(vr->hasVariable("c.var0")==true);
    REQUIRE(vr->hasVariable("c.var2")==true);
    REQUIRE(vr->getVariableRegister("a")->hasVariable("var0")==true);
    REQUIRE(vr->getVariableRegister("a")->hasVariable("var1")==true);
    REQUIRE(vr->getVariableRegister("a")->hasVariable("var2")==true);
    REQUIRE(vr->getVariableRegister("b")->hasVariable("var0")==true);
    REQUIRE(vr->getVariableRegister("b")->hasVariable("var1")==true);
    REQUIRE(vr->getVariableRegister("c")->hasVariable("var0")==true);
    REQUIRE(vr->getVariableRegister("c")->hasVariable("var2")==true);
    REQUIRE(vr->hasVariable("b.var2")==false);
    REQUIRE(vr->hasVariable("c.var1")==false);

    vr->erase("a.var0");
    REQUIRE(vr->hasVariable("a.var0")==false);
    REQUIRE(vr->getVariableRegister("a")->hasVariable("var0")==false);
    vr->getVariableRegister("a")->erase("var1");
    REQUIRE(vr->hasVariable("a.var1")==false);
    REQUIRE(vr->getVariableRegister("a")->hasVariable("var1")==false);
    vr->erase("a.var2");
    REQUIRE(vr->hasVariable("a.var2")==false);
    REQUIRE(vr->hasVariableRegister("a")==false);
    vr->eraseVariableRegister("b");
    REQUIRE(vr->hasVariable("b.var0")==false);
    REQUIRE(vr->hasVariable("b.var1")==false);
    REQUIRE(vr->hasVariableRegister("b")==false);
    vr->eraseVariableRegister("c");
    REQUIRE(vr->empty()==true);
    vr->insert(".a",std::dynamic_pointer_cast<Nullary>(fr->sharedFactory("Nullary")));
    REQUIRE(vr->empty()==true);
    vr->insert("a..a",std::dynamic_pointer_cast<Nullary>(fr->sharedFactory("Nullary")));
    REQUIRE(vr->empty()==true);
    vr->insert("a.b..a",std::dynamic_pointer_cast<Nullary>(fr->sharedFactory("Nullary")));
    REQUIRE(vr->empty()==true);
    vr->insert("a.b.a.",std::dynamic_pointer_cast<Nullary>(fr->sharedFactory("Nullary")));
    REQUIRE(vr->empty()==true);

#ifndef SHOWCERR
    std::cerr.rdbuf(old);
#endif

  }
}

