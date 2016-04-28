#include<geCore/Interpret.h>
#include<geCore/AtomicFunction.h>
#include<geCore/StdFunctions.h>
#include<geCore/CompositeFunction.h>
#include<geCore/If.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;

SCENARIO( "basic interpret tests", "[Function]" ) {
  auto typeRegister = std::make_shared<ge::core::TypeRegister>();
  auto nr=std::make_shared<NameRegister>();
  auto fr = std::make_shared<ge::core::FunctionRegister>(typeRegister,nr);
  ge::core::registerStdFunctions(fr);
  //std::cerr<<fr->str();
  GIVEN( "basic expression" ) {
    auto fa=std::make_shared<ge::core::Nullary>(fr,101.f );
    auto fb=std::make_shared<ge::core::Nullary>(fr,1.1f  );
    auto fc=std::make_shared<ge::core::Nullary>(fr,2.2f  );
    auto fd=std::make_shared<ge::core::Nullary>(fr,1000.f);

    auto f0=std::make_shared<ge::core::Add<float>>(fr,typeRegister->sharedResource("f32"));
    f0->bindInput(fr,0,fa);
    f0->bindInput(fr,1,fb);
    auto f1=std::make_shared<ge::core::Add<float>>(fr,typeRegister->sharedResource("f32"));
    f1->bindInput(fr,0,f0);
    f1->bindInput(fr,1,fc);
    auto f2=std::make_shared<ge::core::Sub<float>>(fr,typeRegister->sharedResource("f32"));
    f2->bindInput(fr,0,f0);
    f2->bindInput(fr,1,fd);
    auto f3=std::make_shared<ge::core::Cast<float,int>>(fr,typeRegister->sharedResource("i32"));
    f3->bindInput(fr,0,f2);
    WHEN("running f1"){
      (*f1)();
      THEN( "output of f1 should be computed correctly" ) {
        REQUIRE((float)(*f1->getOutputData())==((101.f+1.1f)+2.2f));
      }
    }
    WHEN("running f2"){
      (*f2)();
      THEN( "output of f2 should be computed correctly"){
        REQUIRE((float)(*f2->getOutputData())==((101.f+1.1f)-1000.f));
      }
    }
    WHEN("running f3"){
      (*f3)();
      THEN("output of f3 should be computed correctly"){
        REQUIRE((int)(*f3->getOutputData())==(int)((101.f+1.1f)-1000.f));
      }
    }
  }

  GIVEN("if statement"){
    /*
     * unsigned a=10;
     * unsigned b=12;
     * unsigned c=0;
     * if(a<b)
     *  c=a;
     * else
     *  c=b;
     */
    auto fa=std::make_shared<ge::core::Nullary>(fr,(unsigned)10);
    auto fb=std::make_shared<ge::core::Nullary>(fr,(unsigned)12);
    auto fc=std::make_shared<ge::core::Nullary>(fr,(unsigned)0 );

    auto cond=std::make_shared<ge::core::Less<uint32_t>>(fr,typeRegister->sharedResource("bool"));
    cond->bindInput(fr,0,fa);
    cond->bindInput(fr,1,fb);

    auto trueBody = std::make_shared<ge::core::Assignment<uint32_t>>(fr);
    trueBody->bindOutput(fr,fc->getOutputData());
    trueBody->bindInput(fr,0,fa);

    auto falseBody = std::make_shared<ge::core::Assignment<uint32_t>>(fr);
    falseBody->bindOutput(fr,fc->getOutputData());
    falseBody->bindInput(fr,0,fb);

    auto iff=std::make_shared<ge::core::If>(cond,trueBody,falseBody);

    WHEN("running iff"){
      (*iff)();
      THEN("it should correctly choose lesser value"){
        REQUIRE((unsigned)(*fc->getOutputData())==10);
      }
    }
  }
  GIVEN("while statement"){
    /*
     * unsigned i=1;
     * unsigned k=1;
     * unsigned ki;
     * unsigned i1;
     * while(i<10){
     *  ki=k*i;
     *  k=ki;
     *  i1=i+1;
     *  i=i1;
     * }
     */
    auto fi    = std::make_shared<ge::core::Nullary>(fr,(unsigned)1u );
    auto fk    = std::make_shared<ge::core::Nullary>(fr,(unsigned)1u );
    auto fki   = std::make_shared<ge::core::Nullary>(fr,(unsigned)0u );
    auto fi1   = std::make_shared<ge::core::Nullary>(fr,(unsigned)1u );
    auto fiend = std::make_shared<ge::core::Nullary>(fr,(unsigned)10u);
    auto f1    = std::make_shared<ge::core::Nullary>(fr,(unsigned)1u );

    auto cond=std::make_shared<ge::core::Less<uint32_t>>(fr,typeRegister->sharedResource("bool"));
    cond->bindInput(fr,0,fi   );
    cond->bindInput(fr,1,fiend);

    auto mult=std::make_shared<ge::core::Mul<uint32_t>>(fr);
    mult->bindInput(fr,0,fk);
    mult->bindInput(fr,1,fi);
    mult->bindOutput(fr,fki->getOutputData());

    auto ass0 = std::make_shared<ge::core::Assignment<uint32_t>>(fr);
    ass0->bindInput(fr,0,fki);
    ass0->bindOutput(fr,fk->getOutputData());

    auto add=std::make_shared<ge::core::Add<uint32_t>>(fr);
    add->bindInput(fr,0,fi);
    add->bindInput(fr,1,f1);
    add->bindOutput(fr,fi1->getOutputData());

    auto ass1 = std::make_shared<ge::core::Assignment<uint32_t>>(fr);
    ass1->bindInput(fr,0,fi1);
    ass1->bindOutput(fr,fi->getOutputData());

    auto body=std::make_shared<ge::core::Body>();
    body->addStatement(mult);
    body->addStatement(ass0);
    body->addStatement(add );
    body->addStatement(ass1);

    auto wh=std::make_shared<ge::core::While>(cond,body);
    WHEN("running wh"){
      (*wh)();
      THEN("it should compute factorial of 9"){
        REQUIRE((unsigned)(*fk->getOutputData())==362880);
      }
    }

  }
}


SCENARIO( "ticks tests", "[Function]" ) {
  auto typeRegister = std::make_shared<ge::core::TypeRegister>();
  auto nr=std::make_shared<NameRegister>();
  auto fr = std::make_shared<ge::core::FunctionRegister>(typeRegister,nr);
  ge::core::registerStdFunctions(fr);
  class AddTen: public ge::core::AtomicFunction{
    public:
      unsigned counter=0;
      AddTen(std::shared_ptr<ge::core::FunctionRegister>const&fr):AtomicFunction(fr,{TypeRegister::FCE,TypeRegister::F32,1,TypeRegister::F32},"AddTen",nullptr){
        //this->_setInput(0,tr->getTypeId("f32"));
        //this->_setOutput(tr->getTypeId("f32"));
      }
    protected:
      virtual bool _do(){
        if(!this->hasInput(0)||!this->hasOutput())return false;
        if(!this->_inputChanged(0))return false;
        counter++;
        (float&)(*this->_outputData)=
          (float&)(*this->getInputData(0))+10.f;
        return true;
      }
  };
  class Add: public ge::core::AtomicFunction{
    public:
      unsigned counter=0;
      Add(std::shared_ptr<ge::core::FunctionRegister>const&fr):AtomicFunction(fr,{TypeRegister::FCE,TypeRegister::F32,2,TypeRegister::F32,TypeRegister::F32},"Add",nullptr){
        //this->_setInput(0,tr->getTypeId("f32"));
        //this->_setInput(1,tr->getTypeId("f32"));
        //this->_setOutput(tr->getTypeId("f32"));
      }
    protected:
      virtual bool _do(){
        if(!this->hasInput(0)||!this->hasInput(1)||!this->hasOutput())return false;
        if(!this->_inputChanged(0)&&!this->_inputChanged(1))return false;
        counter++;
        (float&)(*this->_outputData)=
          (float&)(*this->getInputData(0))+(float&)(*this->getInputData(1));
        return true;
      }
  };
  GIVEN( "basic expression" ) {
    auto fa      = std::make_shared<ge::core::Nullary>(fr,10.f);
    auto faddten = std::make_shared<AddTen>(fr);
    auto fadd    = std::make_shared<Add>(fr);

    faddten->bindInput(fr,0,fa);
    faddten->bindOutput(fr,typeRegister->sharedResource("f32"));
    fadd->bindInput(fr,0,faddten);
    fadd->bindInput(fr,1,faddten);
    fadd->bindOutput(fr,typeRegister->sharedResource("f32"));

    WHEN("running fadd"){
      (*fadd)();
      THEN( "output of fadd should be 40.f" ) {
        REQUIRE((float&)*fadd->getOutputData() == 40.f);
      }
      THEN( "faddten should be called only once"){
        REQUIRE(faddten->counter == 1);
      }
    }
  }

}

/*
SCENARIO( "macro function tests", "[CompositeFunction]" ) {
  auto tr = std::make_shared<ge::core::TypeRegister>();
  auto fr = std::make_shared<ge::core::FunctionRegister>(tr);
  ge::core::registerStdFunctions(fr);
  auto ftype = tr->addType("",{TypeRegister::FCE,TypeRegister::I32,3,TypeRegister::I32,TypeRegister::I32,TypeRegister::I32});

  auto add3 = std::shared_ptr<ge::core::CompositeFunction>(fr,)
}*/
