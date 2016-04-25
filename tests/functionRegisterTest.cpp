#include<geCore/TypeRegister.h>
#include<geCore/Accessor.h>
#include<geCore/functionRegister.h>
#include<geCore/function.h>
#include<geCore/RegisterBasicFunction.h>
#include<geCore/stdFunctions.h>
#include<geCore/macroFunction.h>
#include<geCore/FactoryOfFunctionFactory.h>
#include<geCore/FunctionNodeFactory.h>
#include<geCore/MacroFunctionFactory.h>
#include<geCore/text.h>
#include<iostream>
#include<sstream>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;

SCENARIO( "basic functionRegister tests", "[FunctionRegister]" ) {
  auto tr=std::make_shared<TypeRegister>();
  auto nr=std::make_shared<Namer>();
  auto fr=std::make_shared<FunctionRegister>(tr,nr);
  REQUIRE(fr->getName(0)=="unregistered");
  REQUIRE(fr->getType(0)==TypeRegister::getTypeTypeId<TypeRegister::Unregistered>());
  auto ft =       tr->addType("",{
        TypeRegister::FCE,
        TypeRegister::getTypeTypeId<int32_t>(),
        2,
        TypeRegister::getTypeTypeId<int32_t>(),
        TypeRegister::getTypeTypeId<int32_t>()});
  auto id = fr->addFunction(
      ft,
      ge::core::TypeRegister::getTypeKeyword<ge::core::Add<int32_t>>(),//::name(),
      ge::core::factoryOfFunctionFactory<ge::core::Add<int32_t>>(ge::core::TypeRegister::getTypeKeyword<ge::core::Add<int32_t>>()));
  fr->getNamer()->setFceOutputName(id,"vysledek");
  fr->getNamer()->setFceInputName(id,0,"a");
  fr->getNamer()->setFceInputName(id,1,"b");

  REQUIRE(fr->getName(id)=="Add<i32>");
  REQUIRE(fr->getType(id)==ft);
  REQUIRE(fr->getNofInputs(id)==tr->getNofFceArgs(ft));
  REQUIRE(fr->getOutputType(id)==tr->getFceReturnTypeId(ft));
  REQUIRE(fr->getOutputName(id)=="vysledek");
  std::vector<std::string>names = {"a","b"};
  for(FunctionRegister::InputIndex i=0;i<fr->getNofInputs(id);++i){
    REQUIRE(fr->getInputType(id,i)==tr->getFceArgTypeId(ft,i));
    REQUIRE(fr->getInputName(id,i)==names[i]);
  }
}

SCENARIO("registration of stdFunction","[FunctionRegister]"){
  auto tr=std::make_shared<TypeRegister>();
  auto nr=std::make_shared<Namer>();
  auto fr=std::make_shared<FunctionRegister>(tr,nr);
  registerStdFunctions(fr);
  auto a0 = std::dynamic_pointer_cast<Function>((*fr->sharedFactory("Add<i32>"))(fr));
  REQUIRE(a0->getFunctionRegister()->getName(a0->getId()) == "Add<i32>");
  REQUIRE(std::dynamic_pointer_cast<Function>((*fr->sharedFactory("Add<i32>"))(fr))->getNofInputs() == 2);
  REQUIRE(std::dynamic_pointer_cast<Function>((*fr->sharedFactory("Add<i32>"))(fr))->getInputType(0) == TypeRegister::getTypeTypeId<int32_t>());
  REQUIRE(std::dynamic_pointer_cast<Function>((*fr->sharedFactory("Add<i32>"))(fr))->getInputType(1) == TypeRegister::getTypeTypeId<int32_t>());
  REQUIRE(std::dynamic_pointer_cast<Function>((*fr->sharedFactory("Add<i32>"))(fr))->getOutputType() == TypeRegister::getTypeTypeId<int32_t>());
}

SCENARIO("registration of functionNode factories","[FunctionRegister]"){
  auto tr=std::make_shared<TypeRegister>();
  auto nr=std::make_shared<Namer>();
  auto fr=std::make_shared<FunctionRegister>(tr,nr);
  registerStdFunctions(fr);

  auto ra = std::make_shared<ResourceFactory>(tr->getTypeId("i32"),1);
  auto rb = std::make_shared<ResourceFactory>(tr->getTypeId("i32"),1);
  auto rc = std::make_shared<ResourceFactory>(tr->getTypeId("i32"),2);

  auto d = std::make_shared<ge::core::FunctionNodeFactory>("newFce_d",2);
  d->setFactory(fr->sharedFactory("Add<i32>"));
  d->addResourceFactory(nullptr);
  d->addResourceFactory(nullptr);
  d->addInputFactory(nullptr);
  d->addInputFactory(nullptr);

  auto c = std::make_shared<ge::core::FunctionNodeFactory>("newFce_c",1);
  c->setFactory(fr->sharedFactory("Mul<i32>"));
  c->addResourceFactory(rc);
  c->addResourceFactory(nullptr);
  c->addInputFactory(d);
  c->addInputFactory(nullptr);

  auto b = std::make_shared<ge::core::FunctionNodeFactory>("newFce_b",1);
  b->setFactory(fr->sharedFactory("Mul<i32>"));
  b->addResourceFactory(nullptr);
  b->addResourceFactory(rc);
  b->addInputFactory(nullptr);
  b->addInputFactory(d);

  auto a = std::make_shared<ge::core::FunctionNodeFactory>("newFce_a",1);
  a->setFactory(fr->sharedFactory("Add<i32>"));
  a->addResourceFactory(ra);
  a->addResourceFactory(rb);
  a->addInputFactory(b);
  a->addInputFactory(c);


  //newFce ::= (va+vb)va + (va+vb)vb
  auto fac = std::make_shared<ge::core::MacroFunctionFactory>("newFce");
  fac->setFactory(a);
  fac->setInputFactories({
      {MacroFunctionFactory::FactoryInput(b,0),MacroFunctionFactory::FactoryInput(d,0)},
      {MacroFunctionFactory::FactoryInput(c,1),MacroFunctionFactory::FactoryInput(d,1)}});

  fr->addFunction(tr->addType("",{TypeRegister::FCE,TypeRegister::I32,2,TypeRegister::I32,TypeRegister::I32}),"newFce",fac);


  auto f=fr->sharedFunction("newFce");
  auto ff=std::dynamic_pointer_cast<Function>(f);
  REQUIRE(ff->getFunctionRegister()->getName(ff->getId())=="newFce");
  REQUIRE(ff->getInputType(0) == tr->getTypeId("i32"));
  REQUIRE(ff->getInputType(1) == tr->getTypeId("i32"));
  REQUIRE(ff->getOutputType() == tr->getTypeId("i32"));
  ff->bindInput(0,std::make_shared<Nullary>(fr,(int32_t)4));
  ff->bindInput(1,std::make_shared<Nullary>(fr,(int32_t)2));
  ff->bindOutput(tr->sharedAccessor("i32"));
  (*f)();
}

int blb(int a,int b){
  return a+b;
}

SCENARIO( "registration of outside function as boxes", "[FunctionRegister]" ) {
  auto tr=std::make_shared<TypeRegister>();
  auto nr=std::make_shared<Namer>();
  auto fr=std::make_shared<FunctionRegister>(tr,nr);
  registerStdFunctions(fr);
  registerBasicFunction(fr,"blb",blb);

  auto f=fr->sharedFunction("blb");
  auto ff=std::dynamic_pointer_cast<Function>(f);
  ff->bindOutput(tr->sharedAccessor("i32"));
  auto a=std::make_shared<ge::core::Nullary>(fr,(int32_t)10);
  auto b=std::make_shared<ge::core::Nullary>(fr,(int32_t)12);
  ff->bindInput(0,a);
  ff->bindInput(1,b);
  (*f)();
  REQUIRE((int32_t)(*ff->getOutputData())==10+12);

  ge::core::registerBasicFunction(fr,"loadTextFile",ge::core::loadTextFile);
}
