#include<geDE/Interpret.h>
#include<geDE/AtomicFunction.h>
#include<geDE/StdFunctions.h>
#include<geDE/CompositeFunction.h>
#include<geDE/RegisterBasicFunction.h>
#include<geDE/If.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::de;

int32_t addOne(int32_t i){
  return i+1;
}

SCENARIO("basic dirty flag tests","[Function]"){
  auto tr = std::make_shared<ge::de::TypeRegister>();
  auto nr=std::make_shared<NameRegister>();
  auto fr = std::make_shared<ge::de::FunctionRegister>(tr,nr);
  ge::de::registerStdFunctions(fr);
  auto addOneId = ge::de::registerBasicFunction(fr,"addOne",addOne);
  auto a0 = std::make_shared<ge::de::Nullary>(fr,(int32_t)0);

  auto b0 = fr->sharedFunction(addOneId);
  b0->bindInput(fr,0,a0);
  b0->bindOutput(fr,tr->sharedResource("i32"));

  REQUIRE(a0->isDirty()==false);
  REQUIRE(b0->isDirty()==true);
  (*b0)();
  REQUIRE(a0->isDirty()==false);
  REQUIRE(b0->isDirty()==false);

  auto a1 = std::make_shared<ge::de::Nullary>(fr,(int32_t)0);
  auto b1 = fr->sharedFunction(addOneId);
  b1->bindInput(fr,0,a1);
  b1->bindOutput(fr,a1);

  REQUIRE(a1->isDirty()==true);
  REQUIRE(b1->isDirty()==true);
  (*b1)();
  REQUIRE(a1->isDirty()==true);
  REQUIRE(b1->isDirty()==true);

  auto a2 = std::make_shared<ge::de::Nullary>(fr,(int32_t)0);
  auto b2 = fr->sharedFunction(addOneId);
  b2->bindInput(fr,0,a2);
  b2->bindOutput(fr,a2);
  auto c2 = std::make_shared<ge::de::Assignment<int32_t>>(fr);
  c2->bindInput(fr,0,a2);
  c2->bindOutput(fr,tr->sharedResource("i32"));

  REQUIRE(a2->isDirty()==true);
  REQUIRE(b2->isDirty()==true);
  REQUIRE(c2->isDirty()==true);

  (*c2)();

  REQUIRE(a2->isDirty()==false);
  REQUIRE(b2->isDirty()==true );
  REQUIRE(c2->isDirty()==false);
}

SCENARIO( "basic interpret tests", "[Function]" ) {
  auto tr = std::make_shared<ge::de::TypeRegister>();
  auto nr=std::make_shared<NameRegister>();
  auto fr = std::make_shared<ge::de::FunctionRegister>(tr,nr);
  ge::de::registerStdFunctions(fr);
  ___;
  //std::cerr<<fr->str();
  GIVEN( "basic expression" ) {
    auto fa=std::make_shared<ge::de::Nullary>(fr,101.f );
    auto fb=std::make_shared<ge::de::Nullary>(fr,1.1f  );
    auto fc=std::make_shared<ge::de::Nullary>(fr,2.2f  );
    auto fd=std::make_shared<ge::de::Nullary>(fr,1000.f);

    //f0 = fa + fb
    //f1 = f0 + fc
    //f2 = f0 + fd
    //f3 = (int)f2
    auto f0=std::make_shared<ge::de::Add<float>>(fr,tr->sharedResource("f32"));
    f0->bindInput(fr,0,fa);
    f0->bindInput(fr,1,fb);
    auto f1=std::make_shared<ge::de::Add<float>>(fr,tr->sharedResource("f32"));
    f1->bindInput(fr,0,f0);
    f1->bindInput(fr,1,fc);
    auto f2=std::make_shared<ge::de::Sub<float>>(fr,tr->sharedResource("f32"));
    f2->bindInput(fr,0,f0);
    f2->bindInput(fr,1,fd);
    auto f3=std::make_shared<ge::de::Cast<float,int>>(fr,tr->sharedResource("i32"));
    f3->bindInput(fr,0,f2);
    WHEN("running f1"){
      REQUIRE(fa->isDirty()==false);
      REQUIRE(fb->isDirty()==false);
      REQUIRE(fc->isDirty()==false);
      REQUIRE(f0->isDirty()==true);
      REQUIRE(f1->isDirty()==true);
      (*f1)();
      REQUIRE(fa->isDirty()==false);
      REQUIRE(fb->isDirty()==false);
      REQUIRE(fc->isDirty()==false);
      REQUIRE(f0->isDirty()==false);
      REQUIRE(f1->isDirty()==false);
      THEN( "output of f1 should be computed correctly" ) {
        REQUIRE((float)(*f1->getOutputData())==((101.f+1.1f)+2.2f));
      }
    }
    WHEN("running f2"){
      REQUIRE(f2->isDirty()==true);
      (*f2)();
      REQUIRE(f2->isDirty()==false);
      THEN( "output of f2 should be computed correctly"){
        REQUIRE((float)(*f2->getOutputData())==((101.f+1.1f)-1000.f));
      }
    }
    WHEN("running f3"){
      REQUIRE(f3->isDirty()==true);
      (*f3)();
      REQUIRE(f3->isDirty()==false);
      THEN("output of f3 should be computed correctly"){
        REQUIRE((int)(*f3->getOutputData())==(int)((101.f+1.1f)-1000.f));
      }
    }
  }

  ___;
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
    auto fa=std::make_shared<ge::de::Nullary>(fr,(unsigned)10);
    auto fb=std::make_shared<ge::de::Nullary>(fr,(unsigned)12);
    auto fc=std::make_shared<ge::de::Nullary>(fr,(unsigned)0 );

    auto cond=std::make_shared<ge::de::Less<uint32_t>>(fr,tr->sharedResource("bool"));
    cond->bindInput(fr,0,fa);
    cond->bindInput(fr,1,fb);

    auto trueBody = std::make_shared<ge::de::Assignment<uint32_t>>(fr);
    trueBody->bindOutput(fr,fc->getOutputData());
    trueBody->bindInput(fr,0,fa);

    auto falseBody = std::make_shared<ge::de::Assignment<uint32_t>>(fr);
    falseBody->bindOutput(fr,fc->getOutputData());
    falseBody->bindInput(fr,0,fb);

    auto iff=std::make_shared<ge::de::If>(cond,trueBody,falseBody);

    WHEN("running iff"){
      (*iff)();
      THEN("it should correctly choose lesser value"){
        REQUIRE((unsigned)(*fc->getOutputData())==10);
      }
    }
  }

  ___;
  GIVEN("while statement"){
    /*
     * unsigned i=1;
     * unsigned k=1;
     * unsigned ki=0;
     * unsigned i1=1;
     * while(i<10){
     *  ki=k*i;
     *  k=ki;
     *  i1=i+1;
     *  i=i1;
     * }
     */
    /*
     
      
    ┌────────────────────┐ 
    │┌──┐                │
    ││1 ├─▢ ┌──┐   ┌──┐  │
    │└──┘ └─▷+ ├─▢─▷=1├─▢┘
    └──┐  ┌─▷  │   └──┘
     ┌─▽┐ │ └──┘
     │i ├─▢─────────┐
     └──┘ │ ┌──┐    │ ┌──┐    ┌──┐ 
     ┌──┐ └─▷< ├▷─▢ └─▷* ├▷─▢─▷=0├─▢
     │10├─▢─▷  │    ┌─▷  │    └──┘ │
     └──┘   └──┘    │ └──┘         │
    ┌──┐            │              │ 
    │┌─▽┐           │              │
    ││k ├─▢─────────┘              │
    │└──┘                          │
    └──────────────────────────────┘




     */
    auto fi    = std::make_shared<ge::de::Nullary>(fr,(unsigned)1u );
    REQUIRE(fi->isDirty()==false);
    auto fk    = std::make_shared<ge::de::Nullary>(fr,(unsigned)1u );
    //auto fki   = std::make_shared<ge::de::Nullary>(fr,(unsigned)0u );
    //auto fi1   = std::make_shared<ge::de::Nullary>(fr,(unsigned)1u );
    auto fiend = std::make_shared<ge::de::Nullary>(fr,(unsigned)10u);
    auto f1    = std::make_shared<ge::de::Nullary>(fr,(unsigned)1u );

    auto cond=std::make_shared<ge::de::Less<uint32_t>>(fr,tr->sharedResource("bool"));
    cond->bindInput(fr,0,fi   );
    cond->bindInput(fr,1,fiend);

    REQUIRE(fi->isDirty()==false);
    auto mult=std::make_shared<ge::de::Mul<uint32_t>>(fr);
    mult->bindInput(fr,0,fk);
    mult->bindInput(fr,1,fi);
    mult->bindOutput(fr,tr->sharedResource("u32"));
    //mult->bindOutput(fr,fki);
    //mult->bindOutput(fr,fki->getOutputData());

    REQUIRE(fi->isDirty()==false);
    auto ass0 = std::make_shared<ge::de::Assignment<uint32_t>>(fr);
    ass0->bindInput(fr,0,mult);//fki);
    ass0->bindOutput(fr,fk);
    //ass0->bindOutput(fr,fk->getOutputData());

    auto add=std::make_shared<ge::de::Add<uint32_t>>(fr);
    add->bindInput(fr,0,fi);
    add->bindInput(fr,1,f1);
    add->bindOutput(fr,tr->sharedResource("u32"));//fi1);
    //add->bindOutput(fr,fi1->getOutputData());

    REQUIRE(fi->isDirty()==false);
    auto ass1 = std::make_shared<ge::de::Assignment<uint32_t>>(fr);
    ass1->bindInput(fr,0,add);//fi1);
    ass1->bindOutput(fr,fi);
    //ass1->bindOutput(fr,fi->getOutputData());

    REQUIRE(fi->isDirty()==true);
    auto body=std::make_shared<ge::de::Body>();
    //body->addStatement(mult);
    body->addStatement(ass0);
    //body->addStatement(add );
    body->addStatement(ass1);

    auto wh=std::make_shared<ge::de::While>(cond,body);
    REQUIRE(cond->hasSignaling(&*wh)==true);
    REQUIRE(cond->nofSignaling()==1);
    REQUIRE(body->hasSignaling(&*wh)==true);
    REQUIRE(body->nofSignaling()==1);

    REQUIRE(ass0->hasSignaling(&*body)==true);
    REQUIRE(ass0->hasSignaling(&*fk)==true);
    REQUIRE(ass0->nofSignaling()==2);

    REQUIRE(ass1->hasSignaling(&*body)==true);
    REQUIRE(ass1->hasSignaling(&*fi)==true);
    REQUIRE(ass1->nofSignaling()==2);

    REQUIRE(add->hasSignaling(&*ass1)==true);
    REQUIRE(add->nofSignaling()==1);

    REQUIRE(mult->hasSignaling(&*ass0)==true);
    REQUIRE(mult->nofSignaling()==1);

    REQUIRE(f1->hasSignaling(&*add)==true);
    REQUIRE(f1->nofSignaling()==1);

    REQUIRE(fi->hasSignaling(&*add)==true);
    REQUIRE(fi->hasSignaling(&*mult)==true);
    REQUIRE(fi->hasSignaling(&*cond)==true);
    REQUIRE(fi->nofSignaling()==3);

    REQUIRE(fiend->hasSignaling(&*cond)==true);
    REQUIRE(fiend->nofSignaling()==1);

    REQUIRE(fk->hasSignaling(&*mult));
    REQUIRE(fk->nofSignaling()==1);
        

    //fk = ass0(fki=mult(fk,fi))
    //cond(fi,fiend)
    //fi=ass1(fi1=add(fki,f1))

    /*
    ___;
    REQUIRE(fi->isDirty()==true);
    REQUIRE(fk->isDirty()==true);
    REQUIRE(fiend->isDirty()==false);
    REQUIRE(f1->isDirty()==false);
    REQUIRE(cond->isDirty()==true);
    REQUIRE(mult->isDirty()==true);
    REQUIRE(ass0->isDirty()==true);
    REQUIRE(add->isDirty()==true);
    REQUIRE(ass1->isDirty()==true);
    REQUIRE(body->isDirty()==true);

    (*cond)();

    REQUIRE(fi->isDirty()==false);
    REQUIRE(fk->isDirty()==true);
    REQUIRE(fiend->isDirty()==false);
    REQUIRE(f1->isDirty()==false);
    REQUIRE(cond->isDirty()==false);
    REQUIRE(mult->isDirty()==true);
    REQUIRE(ass0->isDirty()==true);
    REQUIRE(add->isDirty()==true);
    REQUIRE(ass1->isDirty()==true);
    REQUIRE(body->isDirty()==true);

    (*ass0)();

    REQUIRE(fi->isDirty()==false);
    REQUIRE(fk->isDirty()==true);
    REQUIRE(fiend->isDirty()==false);
    REQUIRE(f1->isDirty()==false);
    REQUIRE(cond->isDirty()==false);
    REQUIRE(mult->isDirty()==true);
    REQUIRE(ass0->isDirty()==true);
    REQUIRE(add->isDirty()==true);
    REQUIRE(ass1->isDirty()==true);
    REQUIRE(body->isDirty()==true);

    (*ass1)();

    REQUIRE(fi->isDirty()==true);
    REQUIRE(fk->isDirty()==true);
    REQUIRE(fiend->isDirty()==false);
    REQUIRE(f1->isDirty()==false);
    REQUIRE(cond->isDirty()==true);
    REQUIRE(mult->isDirty()==true);
    REQUIRE(ass0->isDirty()==true);
    REQUIRE(add->isDirty()==true);
    REQUIRE(ass1->isDirty()==true);
    REQUIRE(body->isDirty()==true);

    (*cond)();

    REQUIRE(fi->isDirty()==false);
    REQUIRE(fk->isDirty()==true);
    REQUIRE(fiend->isDirty()==false);
    REQUIRE(f1->isDirty()==false);
    REQUIRE(cond->isDirty()==false);
    REQUIRE(mult->isDirty()==true);
    REQUIRE(ass0->isDirty()==true);
    REQUIRE(add->isDirty()==true);
    REQUIRE(ass1->isDirty()==true);
    REQUIRE(body->isDirty()==true);

    (*ass0)();

    REQUIRE(fi->isDirty()==false);
    REQUIRE(fk->isDirty()==true);
    REQUIRE(fiend->isDirty()==false);
    REQUIRE(f1->isDirty()==false);
    REQUIRE(cond->isDirty()==false);
    REQUIRE(mult->isDirty()==true);
    REQUIRE(ass0->isDirty()==true);
    REQUIRE(add->isDirty()==true);
    REQUIRE(ass1->isDirty()==true);
    REQUIRE(body->isDirty()==true);

    (*ass1)();

    REQUIRE(fi->isDirty()==true);
    REQUIRE(fk->isDirty()==true);
    REQUIRE(fiend->isDirty()==false);
    REQUIRE(f1->isDirty()==false);
    REQUIRE(cond->isDirty()==true);
    REQUIRE(mult->isDirty()==true);
    REQUIRE(ass0->isDirty()==true);
    REQUIRE(add->isDirty()==true);
    REQUIRE(ass1->isDirty()==true);
    REQUIRE(body->isDirty()==true);


    // */

    //*

    WHEN("running wh"){
      (*wh)();
      THEN("it should compute factorial of 9"){
        REQUIRE((unsigned)(*fk->getOutputData())==362880);
      }
    }// */

  }
}

/*
SCENARIO( "ticks tests", "[Function]" ) {
  auto tr = std::make_shared<ge::de::TypeRegister>();
  auto nr=std::make_shared<NameRegister>();
  auto fr = std::make_shared<ge::de::FunctionRegister>(tr,nr);
  ge::de::registerStdFunctions(fr);
  class AddTen: public ge::de::AtomicFunction{
    public:
      unsigned counter=0;
      AddTen(std::shared_ptr<ge::de::FunctionRegister>const&fr):AtomicFunction(fr,{TypeRegister::FCE,fr->getTypeRegister()->getTypeId(TypeRegister::getTypeKeyword<float>()),1,fr->getTypeRegister()->getTypeId(TypeRegister::getTypeKeyword<float>())},"AddTen",nullptr){
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
  class Add: public ge::de::AtomicFunction{
    public:
      unsigned counter=0;
      Add(std::shared_ptr<ge::de::FunctionRegister>const&fr):AtomicFunction(fr,{TypeRegister::FCE,fr->getTypeRegister()->getTypeId(TypeRegister::getTypeKeyword<float>()),2,fr->getTypeRegister()->getTypeId(TypeRegister::getTypeKeyword<float>()),fr->getTypeRegister()->getTypeId(TypeRegister::getTypeKeyword<float>())},"Add",nullptr){
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
    auto fa      = std::make_shared<ge::de::Nullary>(fr,10.f);
    auto faddten = std::make_shared<AddTen>(fr);
    auto fadd    = std::make_shared<Add>(fr);

    faddten->bindInput(fr,0,fa);
    faddten->bindOutput(fr,tr->sharedResource("f32"));
    fadd->bindInput(fr,0,faddten);
    fadd->bindInput(fr,1,faddten);
    fadd->bindOutput(fr,tr->sharedResource("f32"));

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
*/
/*
SCENARIO( "macro function tests", "[CompositeFunction]" ) {
  auto tr = std::make_shared<ge::de::TypeRegister>();
  auto fr = std::make_shared<ge::de::FunctionRegister>(tr);
  ge::de::registerStdFunctions(fr);
  auto ftype = tr->addType("",{TypeRegister::FCE,TypeRegister::I32,3,TypeRegister::I32,TypeRegister::I32,TypeRegister::I32});

  auto add3 = std::shared_ptr<ge::de::CompositeFunction>(fr,)
}*/
