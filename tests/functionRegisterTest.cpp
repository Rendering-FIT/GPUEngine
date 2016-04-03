#include<geCore/TypeRegister.h>
#include<geCore/Accessor.h>
#include<geCore/functionRegister.h>
#include<geCore/function.h>
#include<geCore/stdFunctions.h>
#include<iostream>
#include<sstream>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;

SCENARIO( "basic functionRegister tests", "[FunctionRegister]" ) {
  auto tr=std::make_shared<TypeRegister>();
  auto fr=std::make_shared<FunctionRegister>(tr);
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
      ge::core::Function::factory<ge::core::Add<int32_t>>(ge::core::TypeRegister::getTypeKeyword<ge::core::Add<int32_t>>()));
  fr->setOutputName(id,"vysledek");
  fr->setInputName(id,0,"a");
  fr->setInputName(id,1,"b");
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

int blb(int a,int b){
  return a+b;
}

SCENARIO( "registration of outside function as boxes", "[FunctionRegister]" ) {
  auto tr=std::make_shared<TypeRegister>();
  auto fr=std::make_shared<FunctionRegister>(tr);
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

}
