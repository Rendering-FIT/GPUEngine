#include<geDE/Interpret.h>
#include<geDE/StdFunctions.h>
#include<geDE/CompositeFunction.h>
#include<geDE/FunctionNodeFactory.h>
#include<geDE/Body.h>
#include<geDE/ResourceFactory.h>
#include<geDE/BodyFactory.h>
#include<geDE/RegisterBasicTypes.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::de;

SCENARIO("maxUses test","[StatementFactory]"){
  auto r  = std::make_shared<TypeRegister>();
  ge::de::registerBasicTypes(r);
  auto nr = std::make_shared<NameRegister>();
  auto fr = std::make_shared<FunctionRegister>(r,nr);
  registerStdFunctions(fr);
  auto resourceFactory = std::make_shared<ResourceFactory>(r->getTypeId("i32"));
  resourceFactory->setUses(2);
  auto a = (*resourceFactory)(fr);
  auto b = (*resourceFactory)(fr);
  auto c = (*resourceFactory)(fr);
  auto d = (*resourceFactory)(fr);
  REQUIRE(a==b);
  REQUIRE(c==d);
  REQUIRE(a!=c);
  REQUIRE(a!=d);
  REQUIRE(b!=c);
  REQUIRE(b!=d);
}


SCENARIO( "basic statement factory tests", "[StatementFactory]" ) {
  auto tr  = std::make_shared<TypeRegister>();
  ge::de::registerBasicTypes(tr);
  auto nr = std::make_shared<NameRegister>();
  auto fr = std::make_shared<FunctionRegister>(tr,nr);
  registerStdFunctions(fr);
  GIVEN( "basic function factory" ) {
    auto factory = fr->sharedFactory("Add<i32>");
    auto statement = (*factory)(fr);
    auto fa=tr->createResource((int32_t)10);
    auto fb=tr->createResource((int32_t)11);
    auto function = std::dynamic_pointer_cast<Function>(statement);
    function->bindInput(fr,0,fa);
    function->bindInput(fr,1,fb);
    function->bindOutput(fr,tr->sharedResource("i32"));
    WHEN("running constructed statement"){
      (*statement)();
      THEN("output should be computed correctly"){
        REQUIRE((int32_t)(*function->getOutputData())==21);
      }
    }
  }
  GIVEN("basic function node factory add(a,b)"){
    auto factory = std::make_shared<::FunctionNodeFactory>();
    factory->setFactory(fr->sharedFactory("Add<i32>"));
    factory->addResourceFactory(std::make_shared<ResourceFactory>(tr->getTypeId("i32")));
    factory->addResourceFactory(std::make_shared<ResourceFactory>(tr->getTypeId("i32")));
    factory->addInputFactory(nullptr);
    factory->addInputFactory(nullptr);
    auto statement = (*factory)(fr);
    auto function = std::dynamic_pointer_cast<Function>(statement);
    function->bindOutput(fr,tr->sharedResource("i32"));
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
    auto factory = std::make_shared<FunctionNodeFactory>();
    factory->setFactory(fr->sharedFactory("Add<i32>"));
    auto resourceFactory = std::make_shared<ResourceFactory>(tr->getTypeId("i32"));
    factory->addResourceFactory(resourceFactory);
    factory->addResourceFactory(resourceFactory);
    factory->addInputFactory(nullptr);
    factory->addInputFactory(nullptr);
    factory->setUses(1);
    REQUIRE(resourceFactory->getUses()==2);
    REQUIRE(factory->getUses()==1);

    auto statement0 = (*factory)(fr);
    auto function0 = std::dynamic_pointer_cast<Function>(statement0);
    function0->bindOutput(fr,tr->sharedResource("i32"));
    *function0->getInputData(0)=(int32_t)10;
    *function0->getInputData(1)=(int32_t)11;

    auto statement1 = (*factory)(fr);
    auto function1 = std::dynamic_pointer_cast<Function>(statement1);
    function1->bindOutput(fr,tr->sharedResource("i32"));
    *function1->getInputData(0)=(int32_t)30;
    *function1->getInputData(1)=(int32_t)31;

    REQUIRE(function0->getInputData(0) != function1->getInputData(0));
    REQUIRE(function0->getInputData(1) != function1->getInputData(1));
    REQUIRE(*(int32_t*)function0->getInputData(0)->getData() != *(int32_t*)function1->getInputData(0)->getData());
    REQUIRE(*(int32_t*)function0->getInputData(1)->getData() != *(int32_t*)function1->getInputData(1)->getData());

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
    auto factory = std::make_shared<BodyFactory>();
    auto add0 = std::make_shared<FunctionNodeFactory>();
    add0->setFactory(fr->sharedFactory("Add<i32>"));
    auto add1 = std::make_shared<FunctionNodeFactory>();
    add1->setFactory(fr->sharedFactory("Add<i32>"));
    auto aFactory = std::make_shared<ResourceFactory>(tr->getTypeId("i32"));
    auto bFactory = std::make_shared<ResourceFactory>(tr->getTypeId("i32"));
    factory->factories.push_back(add0);
    factory->factories.push_back(add1);
    add0->addResourceFactory(aFactory);
    add0->addResourceFactory(aFactory);
    add0->addInputFactory(nullptr);
    add0->addInputFactory(nullptr);
    add1->addResourceFactory(aFactory);
    add1->addResourceFactory(bFactory);
    add1->addInputFactory(nullptr);
    add1->addInputFactory(nullptr);


    auto statement0 = (*factory)(fr);
    auto body0 = std::dynamic_pointer_cast<Body>(statement0);
    auto f00 = std::dynamic_pointer_cast<Function>((*body0)[0]);
    auto f01 = std::dynamic_pointer_cast<Function>((*body0)[1]);
    *f00->getInputData(0)=(int32_t)10;
    *f00->getInputData(1)=(int32_t)11;
    *f01->getInputData(0)=(int32_t)12;
    *f01->getInputData(1)=(int32_t)80;
    f00->bindOutput(fr,tr->sharedResource("i32"));
    f01->bindOutput(fr,tr->sharedResource("i32"));

    auto statement1 = (*factory)(fr);
    auto body1 = std::dynamic_pointer_cast<Body>(statement1);
    auto f10 = std::dynamic_pointer_cast<Function>((*body1)[0]);
    auto f11 = std::dynamic_pointer_cast<Function>((*body1)[1]);
    *f10->getInputData(0)=(int32_t)1;
    *f10->getInputData(1)=(int32_t)2;
    *f11->getInputData(0)=(int32_t)3;
    *f11->getInputData(1)=(int32_t)10;
    f10->bindOutput(fr,tr->sharedResource("i32"));
    f11->bindOutput(fr,tr->sharedResource("i32"));


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
  // */
}

