#include<geCore/interpret.h>
#include<geCore/stdFunctions.h>
#include<geCore/macroFunction.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;

SCENARIO( "basic statement factory tests", "[StatementFactory]" ) {
  auto r = std::make_shared<ge::core::TypeRegister>();
  GIVEN( "basic function factory" ) {
    auto factory = ge::core::Add<int32_t>::factory();
    auto statement = (*factory)(r);
    auto fa=std::make_shared<ge::core::Nullary>(r,(int32_t)10);
    auto fb=std::make_shared<ge::core::Nullary>(r,(int32_t)11);
    auto function = std::dynamic_pointer_cast<Function>(statement);
    function->bindInput(0,fa);
    function->bindInput(1,fb);
    function->bindOutput(r->sharedAccessor("i32"));
    WHEN("running constructed statement"){
      (*statement)();
      THEN("output should be computed correctly"){
        REQUIRE((int32_t)(*function->getOutput())==21);
      }
    }
  }
  GIVEN("basic function node factory add(a,b)"){
    auto factory = std::make_shared<ge::core::FunctionNodeFactory>(ge::core::Add<int32_t>::factory());
    factory->addResourceFactory(std::make_shared<ge::core::ResourceFactory>(r->getTypeId("i32")));
    factory->addResourceFactory(std::make_shared<ge::core::ResourceFactory>(r->getTypeId("i32")));
    factory->addInputFactory(ge::core::Nullary::factory());
    factory->addInputFactory(ge::core::Nullary::factory());
    auto statement = (*factory)(r);
    auto function = std::dynamic_pointer_cast<Function>(statement);
    function->bindOutput(r->sharedAccessor("i32"));
    *function->getInputData(0)=(int32_t)10;
    *function->getInputData(1)=(int32_t)11;
    WHEN("running constructed statement"){
      (*statement)();
      THEN("output should be computed correctly"){
        REQUIRE((int32_t)(*function->getOutput())==21);
      }
    }
  }
  GIVEN("basic function node factory add(a,a)"){
    auto factory = std::make_shared<ge::core::FunctionNodeFactory>(ge::core::Add<int32_t>::factory());
    auto inputFactory = std::make_shared<ge::core::FunctionNodeFactory>(ge::core::Nullary::factory(),2);
    auto resourceFactory = std::make_shared<ge::core::ResourceFactory>(r->getTypeId("i32"),2);
    factory->addResourceFactory(resourceFactory);
    factory->addResourceFactory(resourceFactory);
    factory->addInputFactory(inputFactory);
    factory->addInputFactory(inputFactory);
    auto statement = (*factory)(r);
    auto function = std::dynamic_pointer_cast<Function>(statement);
    function->bindOutput(r->sharedAccessor("i32"));
    *function->getInputData(0)=(int32_t)10;
    *function->getInputData(1)=(int32_t)11;
    WHEN("running constructed statement"){
      (*statement)();
      THEN("output should be computed correctly"){
        REQUIRE((int32_t)(*function->getOutput())==22);
      }
    }
  }

}


