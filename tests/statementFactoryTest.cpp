#include<geCore/interpret.h>
#include<geCore/stdFunctions.h>
#include<geCore/macroFunction.h>
#include<geCore/body.h>

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
        REQUIRE((int32_t)(*function->getOutputData())==21);
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
        REQUIRE((int32_t)(*function->getOutputData())==21);
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

    auto statement0 = (*factory)(r);
    auto function0 = std::dynamic_pointer_cast<Function>(statement0);
    function0->bindOutput(r->sharedAccessor("i32"));
    *function0->getInputData(0)=(int32_t)10;
    *function0->getInputData(1)=(int32_t)11;

    auto statement1 = (*factory)(r);
    auto function1 = std::dynamic_pointer_cast<Function>(statement1);
    function1->bindOutput(r->sharedAccessor("i32"));
    *function1->getInputData(0)=(int32_t)30;
    *function1->getInputData(1)=(int32_t)31;

    WHEN("running constructed statement0 and statement1"){
      (*statement0)();
      (*statement1)();
      THEN("output should be computed correctly"){
        REQUIRE((int32_t)(*function0->getOutputData())==22);
        REQUIRE((int32_t)(*function1->getOutputData())==62);
      }
    }
  }

  GIVEN("basic body factory add(a,a) add(a,b)"){
    //{
    //  a+a;
    //  a+b;
    //}
    auto factory = std::make_shared<ge::core::BodyFactory>();
    auto add0 = std::make_shared<ge::core::FunctionNodeFactory>(ge::core::Add<int32_t>::factory());
    auto add1 = std::make_shared<ge::core::FunctionNodeFactory>(ge::core::Add<int32_t>::factory());
    auto anFactory = std::make_shared<ge::core::FunctionNodeFactory>(ge::core::Nullary::factory(),3);
    auto aFactory = std::make_shared<ge::core::ResourceFactory>(r->getTypeId("i32"),3);
    auto bnFactory = std::make_shared<ge::core::FunctionNodeFactory>(ge::core::Nullary::factory(),1);
    auto bFactory = std::make_shared<ge::core::ResourceFactory>(r->getTypeId("i32"),1);
    factory->factories.push_back(add0);
    factory->factories.push_back(add1);
    add0->addResourceFactory(aFactory);
    add0->addResourceFactory(aFactory);
    add0->addInputFactory(anFactory);
    add0->addInputFactory(anFactory);
    add1->addResourceFactory(aFactory);
    add1->addResourceFactory(bFactory);
    add1->addInputFactory(anFactory);
    add1->addInputFactory(bnFactory);


    auto statement0 = (*factory)(r);
    auto body0 = std::dynamic_pointer_cast<Body>(statement0);
    auto f00 = std::dynamic_pointer_cast<Function>((*body0)[0]);
    auto f01 = std::dynamic_pointer_cast<Function>((*body0)[1]);
    *f00->getInputData(0)=(int32_t)10;
    *f00->getInputData(1)=(int32_t)11;
    *f01->getInputData(0)=(int32_t)12;
    *f01->getInputData(1)=(int32_t)80;
    f00->bindOutput(r->sharedAccessor("i32"));
    f01->bindOutput(r->sharedAccessor("i32"));

    auto statement1 = (*factory)(r);
    auto body1 = std::dynamic_pointer_cast<Body>(statement1);
    auto f10 = std::dynamic_pointer_cast<Function>((*body1)[0]);
    auto f11 = std::dynamic_pointer_cast<Function>((*body1)[1]);
    *f10->getInputData(0)=(int32_t)1;
    *f10->getInputData(1)=(int32_t)2;
    *f11->getInputData(0)=(int32_t)3;
    *f11->getInputData(1)=(int32_t)10;
    f10->bindOutput(r->sharedAccessor("i32"));
    f11->bindOutput(r->sharedAccessor("i32"));


    WHEN("running constructed body containing two function"){
      (*statement0)();
      (*statement1)();
      THEN("output of two function should be computed correctly"){
        REQUIRE((int32_t)(*f00->getOutputData())==24);
        REQUIRE((int32_t)(*f01->getOutputData())==92);
        REQUIRE((int32_t)(*f10->getOutputData())==6);
        REQUIRE((int32_t)(*f11->getOutputData())==13);

      }
    }
  }

}


