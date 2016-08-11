#include<geDE/TypeRegister.h>
#include<geDE/Resource.h>
#include<geDE/ResourceFactory.h>
#include<geDE/FunctionRegister.h>
#include<geDE/Function.h>
#include<geDE/RegisterBasicFunction.h>
#include<geDE/StdFunctions.h>
#include<geDE/CompositeFunction.h>
#include<geDE/FactoryOfFunctionFactory.h>
#include<geDE/FunctionNodeFactory.h>
#include<geDE/CompositeFunctionFactory.h>
#include<geDE/Reference.h>
#include<geDE/RegisterBasicTypes.h>
#include<geCore/Text.h>
#include<iostream>
#include<sstream>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;
using namespace ge::de;
#if 1
std::string printFce(std::shared_ptr<Function>const&fce,std::shared_ptr<FunctionRegister>const&fr){
  if(fce==nullptr)return"nullptr";
  auto tr = fr->getTypeRegister();
  std::stringstream ss;
  ss<<fr->getName(fce->getId())<<"[";
  auto outData = fce->getOutputData();
  if(outData == nullptr)
    ss<<"nullptr";
  else
    ss<<tr->getTypeIdName(outData->getId());
  ss<<"](";
  auto type = fr->getType(fce->getId());
  auto num = tr->getNofFceArgs(type);
  bool first = true;
  for(size_t i=0;i<num;++i){
    if(first)first = false;
    else ss<<",";
    ss<<printFce(fce->getInputFunction(i),fr);
  }
  ss<<")";
  return ss.str();
}

SCENARIO( "basic functionRegister tests", "[FunctionRegister]" ) {
  auto tr=std::make_shared<TypeRegister>();
  ge::de::registerBasicTypes(tr);
  auto nr=std::make_shared<NameRegister>();
  auto fr=std::make_shared<FunctionRegister>(tr,nr);
  REQUIRE(fr->getName(0)=="unregistered");
  REQUIRE(fr->getType(0)==TypeRegister::UNREGISTERED);
  auto i32 = tr->getTypeId(keyword<int32_t>());
  auto ft =       tr->addCompositeType("",{
        TypeRegister::FCE,
        i32,
        2,
        i32,
        i32});
  auto id = fr->addFunction(
      ft,
      keyword<Add<int32_t>>(),
      factoryOfFunctionFactory<Add<int32_t>>());
  fr->getNameRegister()->setFceOutputName(id,"vysledek");
  fr->getNameRegister()->setFceInputName(id,0,"a");
  fr->getNameRegister()->setFceInputName(id,1,"b");

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
  ge::de::registerBasicTypes(tr);
  auto nr=std::make_shared<NameRegister>();
  auto fr=std::make_shared<FunctionRegister>(tr,nr);
  auto i32 = tr->getTypeId(keyword<int32_t>());
  registerStdFunctions(fr);
  auto xx = fr->sharedFactory("Add<i32>");
  REQUIRE(xx!=nullptr);
  auto a0 = std::dynamic_pointer_cast<Function>((*xx)(fr));
  REQUIRE(fr->getName(a0->getId()) == "Add<i32>");
  
  REQUIRE(tr->getNofFceArgs(fr->getType(a0->getId())) == 2);
  
  REQUIRE(tr->getFceArgTypeId(fr->getType(a0->getId()),0) == i32);
  REQUIRE(tr->getFceArgTypeId(fr->getType(a0->getId()),1) == i32);
  REQUIRE(tr->getFceReturnTypeId(fr->getType(a0->getId())) == i32);
}
#endif
SCENARIO("registration of functionNode factories","[FunctionRegister]"){
  auto tr=std::make_shared<TypeRegister>();
  ge::de::registerBasicTypes(tr);
  auto nr=std::make_shared<NameRegister>();
  auto fr=std::make_shared<FunctionRegister>(tr,nr);
  auto i32 = tr->getTypeId(keyword<int32_t>());
  registerStdFunctions(fr);

  auto aaaa=
  "ra = resourceFactory(i32);"
  "rb = resourceFactory(i32);"
  "rc = resourceFactory(i32);"
  "d = nodeFactory(\"newFce_d\",\"Add<i32>\");"
  "c = nodeFactory(\"newFce_c\",\"Mul<i32>\",rc,d);"
  "b = nodeFactory(\"newFce_b\",\"Mul<i32>\",0,0,rc,d);"
  "a = nodeFactory(\"newFce_a\",\"Add<i32>\",ra,b,rb,c);"
  "registerCompositeFunction(\"newFce\",a,{b,0,d,0},{c,1,d,1});"
  "Add<i32>[\"newFce_a\"]("
  "  Mul<i32>[\"newFce_b\"](),,)"
  ;(void)aaaa;

  /*
   * def newFce = newFce_a[Add<i32>](
   *   newFce_b[Mul<i32>](
   *     a,
   *     newFce_d[Add<i32>](a,b)
   *   ),
   *   newFce_c[Mul<i32>](
   *     newFce_d[Add<i32>](a,b),
   *     b
   *   )
   * )
   *
   *
   *
   *
   *
   *
   */

  auto ra = std::make_shared<ResourceFactory>(tr->getTypeId("i32"));
  auto rb = std::make_shared<ResourceFactory>(tr->getTypeId("i32"));
  auto rc = std::make_shared<ResourceFactory>(tr->getTypeId("i32"));

  auto d = std::make_shared<FunctionNodeFactory>();
  d->setFactory(fr->sharedFactory("Add<i32>"));
  d->addResourceFactory(nullptr);
  d->addResourceFactory(nullptr);
  d->addInputFactory(nullptr);
  d->addInputFactory(nullptr);

  auto c = std::make_shared<FunctionNodeFactory>();
  c->setFactory(fr->sharedFactory("Mul<i32>"));
  c->addResourceFactory(rc);
  c->addResourceFactory(nullptr);
  c->addInputFactory(d);
  c->addInputFactory(nullptr);

  auto b = std::make_shared<FunctionNodeFactory>();
  b->setFactory(fr->sharedFactory("Mul<i32>"));
  b->addResourceFactory(nullptr);
  b->addResourceFactory(rc);
  b->addInputFactory(nullptr);
  b->addInputFactory(d);

  auto a = std::make_shared<FunctionNodeFactory>();
  a->setFactory(fr->sharedFactory("Add<i32>"));
  a->addResourceFactory(ra);
  a->addResourceFactory(rb);
  a->addInputFactory(b);
  a->addInputFactory(c);

  //newFce ::= (va+vb)va + (va+vb)vb
  auto fac = std::make_shared<CompositeFunctionFactory>();
  fac->setFactory(a);
  fac->setInputFactories({
      {CompositeFunctionFactory::FactoryInput(b,0),CompositeFunctionFactory::FactoryInput(d,0)},
      {CompositeFunctionFactory::FactoryInput(c,1),CompositeFunctionFactory::FactoryInput(d,1)}});

  fr->addFunction(tr->addCompositeType("",{TypeRegister::FCE,i32,2,i32,i32}),"newFce",fac);

  auto f=fr->sharedFunction("newFce");
#if 0
  auto ff=std::dynamic_pointer_cast<Function>(f);
  REQUIRE(fr->getName(ff->getId())=="newFce");
  REQUIRE(tr->getFceArgTypeId(fr->getType(ff->getId()),0) == tr->getTypeId("i32"));
  REQUIRE(tr->getFceArgTypeId(fr->getType(ff->getId()),1) == tr->getTypeId("i32"));
  REQUIRE(tr->getFceReturnTypeId(fr->getType(ff->getId())) == tr->getTypeId("i32"));
  ff->bindInput(fr,0,tr->createResource((int32_t)4));
  ff->bindInput(fr,1,tr->createResource((int32_t)2));
  ff->bindOutput(fr,tr->sharedResource("i32"));

//  std::cerr<<printFce(ff,fr)<<std::endl;
//  std::cerr<<fr->getName(ff->getId())<<std::endl;
//  std::cerr<<fr->getName(ff->getInputFunction(0)->getId())<<" "<<fr->getName(ff->getInputFunction(1)->getId())<<std::endl;
//  std::cerr<<tr->getTypeIdName(ff->getInputData(0)->getId())<<" "<<tr->getTypeIdName(ff->getInputData(1)->getId())<<std::endl;
  (*f)();
#endif
}

#if 1
int blb(int a,int b){
  return a+b;
}

int baba(int a,int b,int c){
  return a+b+c;
}


SCENARIO( "registration of outside function as boxes", "[FunctionRegister]" ) {
  auto tr=std::make_shared<TypeRegister>();
  ge::de::registerBasicTypes(tr);
  auto nr=std::make_shared<NameRegister>();
  auto fr=std::make_shared<FunctionRegister>(tr,nr);
  registerStdFunctions(fr);
  registerBasicFunction(fr,"blb",blb);

  auto f=fr->sharedFunction("blb");
  auto ff=std::dynamic_pointer_cast<Function>(f);
  ff->bindOutput(fr,tr->sharedResource("i32"));
  ff->bindInputAsVariable(fr,0,tr->createResource((int32_t)10));
  ff->bindInputAsVariable(fr,1,tr->createResource((int32_t)12));
  (*f)();
  REQUIRE((int32_t)(*ff->getOutputData())==10+12);

  registerBasicFunction(fr,"loadTextFile",loadTextFile);
  registerBasicFunction(fr,"baba",baba);
}

int32_t addP(int32_t const*a,int32_t const*b){
  return *a+*b;
}

SCENARIO("Reference tests","[Reference]"){
  auto tr=std::make_shared<TypeRegister>();
  ge::de::registerBasicTypes(tr);
  auto nr=std::make_shared<NameRegister>();
  auto fr=std::make_shared<FunctionRegister>(tr,nr);
  tr->addType<int32_t*>();
  registerStdFunctions(fr);
  registerBasicFunction(fr,"addP",addP);
  fr->addFunction(tr->addType<int32_t*(int32_t)>(),"Reference<i32>",factoryOfFunctionFactory<Reference>());

  auto f = fr->sharedFunction("addP");
  f->bindOutput(fr,tr->sharedResource("i32"));

  auto pa = std::make_shared<Reference>(fr,tr->getTypeId("i32"));
  auto pb = std::make_shared<Reference>(fr,tr->getTypeId("i32"));
  pa->bindInputAsVariable(fr,0,tr->createResource((int32_t)10));
  pa->bindOutput(fr,tr->sharedResource(tr->getTypeId("i32*")));
  pb->bindInputAsVariable(fr,0,tr->createResource((int32_t)12));
  pb->bindOutput(fr,tr->sharedResource(tr->getTypeId("i32*")));
  f->bindInput(fr,0,pa);
  f->bindInput(fr,1,pb);

  (*f)();

  REQUIRE((int32_t&)*f->getOutputData()==10+12);
}



class TestClass{
  public:
    int data = 1;
    TestClass(){}
    ~TestClass(){}
    TestClass(int d){this->data =d;}
    int add(int v){return this->data+v;}
};

namespace ge{
  namespace de{
    GE_DE_ADD_KEYWORD(TestClass,"TestClass")
    GE_DE_ADD_KEYWORD(std::shared_ptr<TestClass>,"SharedTestClass")
  }
}

template<typename T>T const&removeSharedPointer(std::shared_ptr<T>const&val){return *val;}
template<typename T>T*sharedPointerToPointer(std::shared_ptr<T>const&val){return &*val;}

SCENARIO( "registration of external member function as boxes", "[FunctionRegister]" ) {
  auto tr=std::make_shared<TypeRegister>();
  ge::de::registerBasicTypes(tr);
  auto nr=std::make_shared<NameRegister>();
  auto fr=std::make_shared<FunctionRegister>(tr,nr);
  registerStdFunctions(fr);

  tr->addAtomicType(
      ge::de::keyword<TestClass>(),
      sizeof(TestClass),
      [](void*ptr){new(ptr)TestClass(100);},
      [](void*ptr){((TestClass*)ptr)->~TestClass();});

  registerClassFunction(fr,"TestClass::add",&TestClass::add);
  auto f=fr->sharedFunction("TestClass::add");
  auto ff=std::dynamic_pointer_cast<Function>(f);
  ff->bindOutput(fr,tr->sharedResource("i32"));
  ff->bindInputAsVariable(fr,0,tr->sharedResource("TestClass"));
  ff->bindInputAsVariable(fr,1,tr->createResource((int32_t)12));
  ((TestClass&)*ff->getInputData(0)).data = 1000;
  (*f)();
  REQUIRE((int32_t)(*ff->getOutputData())==1000+12);

  tr->addAtomicType(
      ge::de::keyword<std::shared_ptr<TestClass>>(),
      sizeof(std::shared_ptr<TestClass>),
      [](void*ptr){
      new(ptr)std::shared_ptr<TestClass>(new TestClass());
      },
      [](void*ptr){
      ((std::shared_ptr<TestClass>*)ptr)->~shared_ptr();
      });
  tr->addType<TestClass*>();

  auto f1 = fr->sharedFunction("TestClass::add");
  auto ff1 = std::dynamic_pointer_cast<Function>(f1);
  ff1->bindOutput(fr,tr->sharedResource("i32"));
  registerBasicFunction(fr,"removeSharedPointerFromTestClass",removeSharedPointer<TestClass>);
  auto b1=fr->sharedFunction("removeSharedPointerFromTestClass");
  b1->bindInputAsVariable(fr,0,tr->sharedResource("SharedTestClass"));
  b1->bindOutput(fr,tr->sharedResource("TestClass"));
  ff1->bindInput(fr,0,b1);
  ff1->bindInputAsVariable(fr,1,tr->createResource((int32_t)32));
  ((std::shared_ptr<TestClass>&)*b1->getInputData(0))->data = 100;
  (*ff1)();
  REQUIRE((int32_t)(*ff1->getOutputData())==100+32);

  {
    registerBasicFunction(fr,"sharedPointerToPointerTestClass",sharedPointerToPointer<TestClass>);
    auto res = tr->sharedResource("SharedTestClass");
    auto val = tr->createResource<int32_t>(4);
    auto f0 = fr->sharedFunction("sharedPointerToPointerTestClass");
    auto f1 = fr->sharedFunction("TestClass::add");
    f0->bindInputAsVariable(fr,0,res);
    f0->bindOutput(fr,tr->sharedResource("TestClass*"));
    f1->bindInput(fr,0,f0);
    f1->bindInputAsVariable(fr,1,val);
    f1->bindOutput(fr,tr->sharedResource("i32"));
    (*f1)();
    REQUIRE((int32_t)(*f1->getOutputData())==4+1);
  }
  


}
#endif
