#include<geDE/Interpret.h>
#include<geDE/AtomicFunction.h>
#include<geDE/StdFunctions.h>
#include<geDE/CompositeFunction.h>
#include<geDE/RegisterBasicFunction.h>
#include<geDE/If.h>
#include<geDE/RegisterBasicTypes.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::de;

int32_t addOne(int32_t i){
  return i+1;
}

int32_t addVec(int32_t*ivec3){
  return ivec3[0]+ivec3[1]+ivec3[2];
}

/*
SCENARIO("pointer cast test","Function"){
  auto tr = std::make_shared<ge::de::TypeRegister>();
  auto nr = std::make_shared<NameRegister>();
  auto fr = std::make_shared<ge::de::FunctionRegister>(tr,nr);
  ge::de::registerStdFunctions(fr);
  tr->addCompositeType("ivec3",{TypeRegister::ARRAY,3,tr->getTypeId("i32")});
  //tr->addCompositeType(TypeRegister::getTypeKeyword<int32_t*>(),{TypeRegister::PTR,tr->getTypeId("i32")});//sizeof(int32_t*));
  tr->addCompositeType(keyword<int32_t*>(),{TypeRegister::PTR,tr->getTypeId("i32")});
  auto addVecId = ge::de::registerBasicFunction(fr,"addVec",addVec);
  auto f = fr->sharedFunction(addVecId);
  auto a0 = fr->sharedFunction(fr->getFunctionId("Nullary"));//
  a0->bindOutput(fr,tr->sharedResource("ivec3"));
  ((int32_t*)(*a0->getOutputData()))[0]=1;
  ((int32_t*)(*a0->getOutputData()))[1]=2;
  ((int32_t*)(*a0->getOutputData()))[2]=3;

  f->bindInput(fr,0,a0);
  f->bindOutput(fr,tr->sharedResource("i32"));

  (*f)();

  REQUIRE((int32_t&)*f->getOutputData()==1+2+3);
}
*/
SCENARIO("fast loop binding test","[Function]"){
  auto tr = std::make_shared<ge::de::TypeRegister>();
  ge::de::registerBasicTypes(tr);
  auto nr = std::make_shared<NameRegister>();
  auto fr = std::make_shared<ge::de::FunctionRegister>(tr,nr);
  ge::de::registerStdFunctions(fr);
  auto addOneId = ge::de::registerBasicFunction(fr,"addOne",addOne);
  auto res = tr->createResource((int32_t)0);

  auto f0 = fr->sharedFunction(addOneId);
  auto f1 = fr->sharedFunction(addOneId);

  REQUIRE(f0->bindOutput(fr,res)==true);
  REQUIRE(f0->bindInputAsVariable(fr,0,res)==true);
    //#define SHOWCERR
#ifndef SHOWCERR
    std::stringstream oss;
    auto old = std::cerr.rdbuf( oss.rdbuf() );
#endif

  REQUIRE(f1->bindOutput(fr,res)==true);
  REQUIRE(f0->nofSourceResources()==1);
  REQUIRE(f0->nofTargetResources()==1);
  REQUIRE(f0->nofSignalingSources()==0);
  REQUIRE(f0->nofSignalingTargets()==0);
  REQUIRE(f0->hasSourceResource(&*res)==true);
  REQUIRE(f0->hasTargetResource(&*res)==true);
  REQUIRE(f1->nofSourceResources()==0);
  REQUIRE(f1->nofTargetResources()==1);
  REQUIRE(f1->nofSignalingSources()==0);
  REQUIRE(f1->nofSignalingTargets()==0);
  REQUIRE(f1->hasTargetResource(&*res)==true);
  REQUIRE(res->nofSignalingSources()==2);
  REQUIRE(res->nofSignalingTargets()==1);
  REQUIRE(res->hasSignalingSource(&*f0)==true);
  REQUIRE(res->hasSignalingSource(&*f1)==true);
  REQUIRE(res->hasSignalingTarget(&*f0)==true);

  REQUIRE(f1->bindInput(fr,0,f0)==false);
  REQUIRE(f0->nofSourceResources()==1);
  REQUIRE(f0->nofTargetResources()==1);
  REQUIRE(f0->nofSignalingSources()==0);
  REQUIRE(f0->nofSignalingTargets()==0);
  REQUIRE(f0->hasSourceResource(&*res)==true);
  REQUIRE(f0->hasTargetResource(&*res)==true);
  REQUIRE(f1->nofSourceResources()==0);
  REQUIRE(f1->nofTargetResources()==1);
  REQUIRE(f1->nofSignalingSources()==0);
  REQUIRE(f1->nofSignalingTargets()==0);
  REQUIRE(f1->hasTargetResource(&*res)==true);
  REQUIRE(res->nofSignalingSources()==2);
  REQUIRE(res->nofSignalingTargets()==1);
  REQUIRE(res->hasSignalingSource(&*f0)==true);
  REQUIRE(res->hasSignalingSource(&*f1)==true);
  REQUIRE(res->hasSignalingTarget(&*f0)==true);


  REQUIRE(f1->bindOutput(fr,nullptr)==true);
  REQUIRE(f0->nofSourceResources()==1);
  REQUIRE(f0->nofTargetResources()==1);
  REQUIRE(f0->nofSignalingSources()==0);
  REQUIRE(f0->nofSignalingTargets()==0);
  REQUIRE(f0->hasSourceResource(&*res)==true);
  REQUIRE(f0->hasTargetResource(&*res)==true);
  REQUIRE(f1->nofSourceResources()==0);
  REQUIRE(f1->nofTargetResources()==0);
  REQUIRE(f1->nofSignalingSources()==0);
  REQUIRE(f1->nofSignalingTargets()==0);
  REQUIRE(res->nofSignalingSources()==1);
  REQUIRE(res->nofSignalingTargets()==1);
  REQUIRE(res->hasSignalingSource(&*f0)==true);
  REQUIRE(res->hasSignalingTarget(&*f0)==true);


  REQUIRE(f1->bindInput(fr,0,f0)==true);
  REQUIRE(f0->nofSourceResources()==1);
  REQUIRE(f0->nofTargetResources()==1);
  REQUIRE(f0->nofSignalingSources()==0);
  REQUIRE(f0->nofSignalingTargets()==1);
  REQUIRE(f0->hasSourceResource(&*res)==true);
  REQUIRE(f0->hasTargetResource(&*res)==true);
  REQUIRE(f0->hasSignalingTarget(&*f1)==true);
  REQUIRE(f1->nofSourceResources()==1);
  REQUIRE(f1->nofTargetResources()==0);
  REQUIRE(f1->nofSignalingSources()==1);
  REQUIRE(f1->nofSignalingTargets()==0);
  REQUIRE(f1->hasSourceResource(&*res)==true);
  REQUIRE(f1->hasSignalingSource(&*f0)==true);
  REQUIRE(res->nofSignalingSources()==1);
  REQUIRE(res->nofSignalingTargets()==2);
  REQUIRE(res->hasSignalingSource(&*f0)==true);
  REQUIRE(res->hasSignalingTarget(&*f0)==true);
  REQUIRE(res->hasSignalingTarget(&*f1)==true);


  REQUIRE(f1->bindOutput(fr,res)==false);
  REQUIRE(f0->nofSourceResources()==1);
  REQUIRE(f0->nofTargetResources()==1);
  REQUIRE(f0->nofSignalingSources()==0);
  REQUIRE(f0->nofSignalingTargets()==1);
  REQUIRE(f0->hasSourceResource(&*res)==true);
  REQUIRE(f0->hasTargetResource(&*res)==true);
  REQUIRE(f0->hasSignalingTarget(&*f1)==true);
  REQUIRE(f1->nofSourceResources()==1);
  REQUIRE(f1->nofTargetResources()==0);
  REQUIRE(f1->nofSignalingSources()==1);
  REQUIRE(f1->nofSignalingTargets()==0);
  REQUIRE(f1->hasSourceResource(&*res)==true);
  REQUIRE(f1->hasSignalingSource(&*f0)==true);
  REQUIRE(res->nofSignalingSources()==1);
  REQUIRE(res->nofSignalingTargets()==2);
  REQUIRE(res->hasSignalingSource(&*f0)==true);
  REQUIRE(res->hasSignalingTarget(&*f0)==true);
  REQUIRE(res->hasSignalingTarget(&*f1)==true);

#ifndef SHOWCERR
    std::cerr.rdbuf(old);
#endif
}

SCENARIO("basic dirty flag tests","[Function]"){
  auto tr = std::make_shared<ge::de::TypeRegister>();
  ge::de::registerBasicTypes(tr);
  auto nr = std::make_shared<NameRegister>();
  auto fr = std::make_shared<ge::de::FunctionRegister>(tr,nr);
  ge::de::registerStdFunctions(fr);
  auto addOneId = ge::de::registerBasicFunction(fr,"addOne",addOne);

  {
    auto f = fr->sharedFunction(addOneId);
    f->bindInputAsVariable(fr,0,tr->createResource((int32_t)0));
    f->bindOutput(fr,tr->sharedResource("i32"));
    REQUIRE(f->isDirty()==true);
    (*f)();
    REQUIRE(f->isDirty()==false);
  }

  {
    auto f = fr->sharedFunction(addOneId);
    f->bindOutput(fr,tr->createResource((int32_t)0));
    f->bindInputAsVariable(fr,0,f->getOutputData());
    REQUIRE(f->isDirty()==true);
    (*f)();
    REQUIRE(f->isDirty()==true);
  }

  {
  auto res = tr->createResource((int32_t)0);
  auto f0 = fr->sharedFunction(addOneId);
  f0->bindInputAsVariable(fr,0,res);
  f0->bindOutput(fr,res);
  auto f1 = std::make_shared<ge::de::Assignment<int32_t>>(fr);
  f1->bindInputAsVariable(fr,0,res);
  f1->bindOutput(fr,tr->sharedResource("i32"));

  REQUIRE(f0->isDirty()==true);
  REQUIRE(f1->isDirty()==true);

  (*f1)();

  REQUIRE(f0->isDirty()==true );
  REQUIRE(f1->isDirty()==false);
  }
}

SCENARIO( "basic interpret tests", "[Function]" ) {
  auto tr = std::make_shared<ge::de::TypeRegister>();
  ge::de::registerBasicTypes(tr);
  auto nr=std::make_shared<NameRegister>();
  auto fr = std::make_shared<ge::de::FunctionRegister>(tr,nr);
  ge::de::registerStdFunctions(fr);
  //std::cerr<<fr->str();
  GIVEN( "basic expression" ) {
    float avalue = 101.f;
    float bvalue = 1.1f;
    float cvalue = 2.2f;
    float dvalue = 1000.f;
    auto fa=tr->createResource(avalue);
    auto fb=tr->createResource(bvalue);
    auto fc=tr->createResource(cvalue);
    auto fd=tr->createResource(dvalue);

    //f0 = fa + fb
    //f1 = f0 + fc
    //f2 = f0 + fd
    //f3 = (int)f2
    auto f0=std::make_shared<ge::de::Add<float>>(fr);
    f0->bindOutput(fr,tr->sharedResource("f32"));
    f0->bindInputAsVariable(fr,0,fa);
    f0->bindInputAsVariable(fr,1,fb);
    auto f1=std::make_shared<ge::de::Add<float>>(fr);
    f1->bindOutput(fr,tr->sharedResource("f32"));
    f1->bindInput(fr,0,f0);
    f1->bindInputAsVariable(fr,1,fc);
    auto f2=std::make_shared<ge::de::Sub<float>>(fr);
    f2->bindOutput(fr,tr->sharedResource("f32"));
    f2->bindInput(fr,0,f0);
    f2->bindInputAsVariable(fr,1,fd);
    auto f3=std::make_shared<ge::de::Cast<float,int>>(fr);
    f3->bindOutput(fr,tr->sharedResource("i32"));
    f3->bindInput(fr,0,f2);
    WHEN("running f1"){
      REQUIRE(f0->isDirty()==true);
      REQUIRE(f1->isDirty()==true);
      (*f1)();
      REQUIRE(f0->isDirty()==false);
      REQUIRE(f1->isDirty()==false);
      THEN( "output of f1 should be computed correctly" ) {
        REQUIRE((float)(*f0->getOutputData())==(avalue+bvalue));
        REQUIRE((float)(*f1->getOutputData())==((avalue+bvalue)+2.2f));
      }
    }
    WHEN("running f2"){
      REQUIRE(f2->isDirty()==true);
      (*f2)();
      REQUIRE(f2->isDirty()==false);
      THEN( "output of f2 should be computed correctly"){
        REQUIRE((float)(*f2->getOutputData())==((avalue+bvalue)-dvalue));
      }
    }
    WHEN("running f3"){
      REQUIRE(f3->isDirty()==true);
      (*f3)();
      REQUIRE(f3->isDirty()==false);
      THEN("output of f3 should be computed correctly"){
        REQUIRE((int)(*f3->getOutputData())==(int)((avalue+bvalue)-dvalue));
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
    auto fa=tr->createResource((unsigned)10);
    auto fb=tr->createResource((unsigned)12);
    auto fc=tr->createResource((unsigned)0 );

    auto cond=std::make_shared<ge::de::Less<uint32_t>>(fr);
    cond->bindOutput(fr,tr->sharedResource("bool"));
    cond->bindInputAsVariable(fr,0,fa);
    cond->bindInputAsVariable(fr,1,fb);

    auto trueBody = std::make_shared<ge::de::Assignment<uint32_t>>(fr);
    trueBody->bindOutput(fr,fc);
    trueBody->bindInputAsVariable(fr,0,fa);

    auto falseBody = std::make_shared<ge::de::Assignment<uint32_t>>(fr);
    falseBody->bindOutput(fr,fc);
    falseBody->bindInputAsVariable(fr,0,fb);

    auto iff=std::make_shared<ge::de::If>(cond,trueBody,falseBody);

    WHEN("running iff"){
      (*iff)();
      THEN("it should correctly choose lesser value"){
        REQUIRE((unsigned)(*fc)==10);
      }
    }
  }

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
    auto fi    = tr->createResource((unsigned)1u );
    auto fk    = tr->createResource((unsigned)1u );
    //auto fki   = std::make_shared<ge::de::Nullary>(fr,(unsigned)0u );
    //auto fi1   = std::make_shared<ge::de::Nullary>(fr,(unsigned)1u );
    auto fiend = tr->createResource((unsigned)10u);
    auto f1    = tr->createResource((unsigned)1u );

    auto cond=std::make_shared<ge::de::Less<uint32_t>>(fr);
    cond->bindOutput(fr,tr->sharedResource("bool"));
    cond->bindInputAsVariable(fr,0,fi   );
    cond->bindInputAsVariable(fr,1,fiend);

    auto mult=std::make_shared<ge::de::Mul<uint32_t>>(fr);
    mult->bindInputAsVariable(fr,0,fk);
    mult->bindInputAsVariable(fr,1,fi);
    mult->bindOutput(fr,tr->sharedResource("u32"));
    //mult->bindOutput(fr,fki);
    //mult->bindOutput(fr,fki->getOutputData());

    auto ass0 = std::make_shared<ge::de::Assignment<uint32_t>>(fr);
    ass0->bindInput(fr,0,mult);//fki);
    ass0->bindOutput(fr,fk);
    //ass0->bindOutput(fr,fk->getOutputData());

    auto add=std::make_shared<ge::de::Add<uint32_t>>(fr);
    add->bindInputAsVariable(fr,0,fi);
    add->bindInputAsVariable(fr,1,f1);
    add->bindOutput(fr,tr->sharedResource("u32"));//fi1);
    //add->bindOutput(fr,fi1->getOutputData());

    auto ass1 = std::make_shared<ge::de::Assignment<uint32_t>>(fr);
    ass1->bindInput(fr,0,add);//fi1);
    ass1->bindOutput(fr,fi);
    //ass1->bindOutput(fr,fi->getOutputData());

    auto body=std::make_shared<ge::de::Body>();
    //body->addStatement(mult);
    body->addStatement(ass0);
    //body->addStatement(add );
    body->addStatement(ass1);

    auto wh=std::make_shared<ge::de::While>(cond,body);
    REQUIRE(cond->hasSignalingTarget(&*wh)==true);
    REQUIRE(cond->nofSignalingTargets()==1);
    REQUIRE(cond->hasSourceResource(&*fi));
    REQUIRE(cond->hasSourceResource(&*fiend));
    REQUIRE(cond->nofSourceResources()==2);
    REQUIRE(body->hasSignalingTarget(&*wh)==true);
    REQUIRE(body->nofSignalingTargets()==1);

    REQUIRE(ass0->hasSignalingTarget(&*body)==true);
    REQUIRE(ass0->nofSignalingTargets()==1);
    REQUIRE(ass0->hasTargetResource(&*fk)==true);
    REQUIRE(ass0->hasSourceResource(&*mult->getOutputData())==true);
    REQUIRE(ass0->nofTargetResources()==1);
    REQUIRE(ass0->nofSourceResources()==1);


    REQUIRE(ass1->hasSignalingTarget(&*body)==true);
    REQUIRE(ass1->nofSignalingTargets()==1);
    REQUIRE(ass1->hasTargetResource(&*fi)==true);
    REQUIRE(ass1->hasSourceResource(&*add->getOutputData())==true);
    REQUIRE(ass1->nofTargetResources()==1);
    REQUIRE(ass1->nofSourceResources()==1);

    REQUIRE(add->hasTargetResource(&*ass1->getInputData(0))==true);
    REQUIRE(add->hasSourceResource(&*f1)==true);
    REQUIRE(add->hasSourceResource(&*fi)==true);
    REQUIRE(add->nofTargetResources()==1);
    REQUIRE(add->nofSourceResources()==2);
    REQUIRE(add->nofSignalingTargets()==1);
    REQUIRE(add->hasSignalingTarget(&*ass1)==true);

    REQUIRE(mult->hasTargetResource(&*ass0->getInputData(0))==true);
    REQUIRE(mult->hasSourceResource(&*fi)==true);
    REQUIRE(mult->hasSourceResource(&*fk)==true);
    REQUIRE(mult->nofTargetResources()==1);
    REQUIRE(mult->nofSourceResources()==2);
    REQUIRE(mult->nofSignalingTargets()==1);
    REQUIRE(mult->hasSignalingTarget(&*ass0)==true);

    REQUIRE(f1->hasSignalingTarget(&*add)==true);
    REQUIRE(f1->nofSignalingTargets()==1);
    REQUIRE(f1->nofSignalingSources()==0);

    REQUIRE(fi->hasSignalingTarget(&*add)==true);
    REQUIRE(fi->hasSignalingTarget(&*mult)==true);
    REQUIRE(fi->hasSignalingTarget(&*cond)==true);
    REQUIRE(fi->nofSignalingTargets()==3);
    REQUIRE(fi->hasSignalingSource(&*ass1)==true);
    REQUIRE(fi->nofSignalingSources()==1);

    REQUIRE(fiend->hasSignalingTarget(&*cond)==true);
    REQUIRE(fiend->nofSignalingTargets()==1);
    REQUIRE(fiend->nofSignalingSources()==0);

    REQUIRE(fk->hasSignalingTarget(&*mult)==true);
    REQUIRE(fk->hasSignalingSource(&*ass0)==true);
    REQUIRE(fk->nofSignalingTargets()==1);
    REQUIRE(fk->nofSignalingSources()==1);

    REQUIRE(add->getOutputData()->hasSignalingSource(&*add)==true);
    REQUIRE(add->getOutputData()->hasSignalingTarget(&*ass1)==true);
    REQUIRE(add->getOutputData()->nofSignalingSources()==1);
    REQUIRE(add->getOutputData()->nofSignalingTargets()==1);

    REQUIRE(mult->getOutputData()->hasSignalingSource(&*mult)==true);
    REQUIRE(mult->getOutputData()->hasSignalingTarget(&*ass0)==true);
    REQUIRE(mult->getOutputData()->nofSignalingSources()==1);
    REQUIRE(mult->getOutputData()->nofSignalingTargets()==1);

    REQUIRE(cond->getOutputData()->hasSignalingSource(&*cond)==true);
    REQUIRE(cond->getOutputData()->nofSignalingSources()==1);
    REQUIRE(cond->getOutputData()->nofSignalingTargets()==0);
      

    //fk = ass0(fki=mult(fk,fi))
    //cond(fi,fiend)
    //fi=ass1(fi1=add(fki,f1))

    /*
    //REQUIRE(fi->isDirty()==true);
    //REQUIRE(fk->isDirty()==true);
    //REQUIRE(fiend->isDirty()==false);
    //REQUIRE(f1->isDirty()==false);
    REQUIRE(cond->isDirty()==true);
    REQUIRE(mult->isDirty()==true);
    REQUIRE(ass0->isDirty()==true);
    REQUIRE(add->isDirty()==true);
    REQUIRE(ass1->isDirty()==true);
    REQUIRE(body->isDirty()==true);

    (*cond)();

    //REQUIRE(fi->isDirty()==false);
    //REQUIRE(fk->isDirty()==true);
    //REQUIRE(fiend->isDirty()==false);
    //REQUIRE(f1->isDirty()==false);
    REQUIRE(cond->isDirty()==false);
    REQUIRE(mult->isDirty()==true);
    REQUIRE(ass0->isDirty()==true);
    REQUIRE(add->isDirty()==true);
    REQUIRE(ass1->isDirty()==true);
    REQUIRE(body->isDirty()==true);

    (*ass0)();

    //REQUIRE(fi->isDirty()==false);
    //REQUIRE(fk->isDirty()==true);
    //REQUIRE(fiend->isDirty()==false);
    //REQUIRE(f1->isDirty()==false);
    REQUIRE(cond->isDirty()==false);
    REQUIRE(mult->isDirty()==true);
    REQUIRE(ass0->isDirty()==true);
    REQUIRE(add->isDirty()==true);
    REQUIRE(ass1->isDirty()==true);
    REQUIRE(body->isDirty()==true);

    (*ass1)();

    //REQUIRE(fi->isDirty()==true);
    //REQUIRE(fk->isDirty()==true);
    //REQUIRE(fiend->isDirty()==false);
    //REQUIRE(f1->isDirty()==false);
    REQUIRE(cond->isDirty()==true);
    REQUIRE(mult->isDirty()==true);
    REQUIRE(ass0->isDirty()==true);
    REQUIRE(add->isDirty()==true);
    REQUIRE(ass1->isDirty()==true);
    REQUIRE(body->isDirty()==true);

    (*cond)();

    //REQUIRE(fi->isDirty()==false);
    //REQUIRE(fk->isDirty()==true);
    //REQUIRE(fiend->isDirty()==false);
    //REQUIRE(f1->isDirty()==false);
    REQUIRE(cond->isDirty()==false);
    REQUIRE(mult->isDirty()==true);
    REQUIRE(ass0->isDirty()==true);
    REQUIRE(add->isDirty()==true);
    REQUIRE(ass1->isDirty()==true);
    REQUIRE(body->isDirty()==true);

    (*ass0)();

    //REQUIRE(fi->isDirty()==false);
    //REQUIRE(fk->isDirty()==true);
    //REQUIRE(fiend->isDirty()==false);
    //REQUIRE(f1->isDirty()==false);
    REQUIRE(cond->isDirty()==false);
    REQUIRE(mult->isDirty()==true);
    REQUIRE(ass0->isDirty()==true);
    REQUIRE(add->isDirty()==true);
    REQUIRE(ass1->isDirty()==true);
    REQUIRE(body->isDirty()==true);

    (*ass1)();

    //REQUIRE(fi->isDirty()==true);
    //REQUIRE(fk->isDirty()==true);
    //REQUIRE(fiend->isDirty()==false);
    //REQUIRE(f1->isDirty()==false);
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
        REQUIRE((unsigned)(*fk)==362880);
      }
    }// */

  }
}

SCENARIO( "ticks tests", "[Function]" ) {
  auto tr = std::make_shared<ge::de::TypeRegister>();
  auto nr=std::make_shared<NameRegister>();
  auto fr = std::make_shared<ge::de::FunctionRegister>(tr,nr);
  ge::de::registerBasicTypes(tr);
  ge::de::registerStdFunctions(fr);
  class AddTen: public ge::de::AtomicFunction{
    public:
      unsigned counter=0;
      AddTen(std::shared_ptr<ge::de::FunctionRegister>const&fr):AtomicFunction(fr,fr->getTypeRegister()->addType<float(float)>(),"AddTen",nullptr){
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
      Add(std::shared_ptr<ge::de::FunctionRegister>const&fr):AtomicFunction(fr,fr->getTypeRegister()->addType<float(float,float)>(),"Add",nullptr){
      }
    protected:
      virtual bool _do(){
        if(!this->hasInput(0)||!this->hasInput(1)||!this->hasOutput())return false;
        counter++;
        (float&)(*this->_outputData)=
          (float&)(*this->getInputData(0))+(float&)(*this->getInputData(1));
        return true;
      }
  };
  GIVEN( "basic expression" ) {
    auto fa      = tr->createResource(10.f);
    auto faddten = std::make_shared<AddTen>(fr);
    auto fadd    = std::make_shared<Add>(fr);

    faddten->bindInputAsVariable(fr,0,fa);
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

/*
SCENARIO( "macro function tests", "[CompositeFunction]" ) {
  auto tr = std::make_shared<ge::de::TypeRegister>();
  auto fr = std::make_shared<ge::de::FunctionRegister>(tr);
  ge::de::registerStdFunctions(fr);
  auto ftype = tr->addType("",{TypeRegister::FCE,TypeRegister::I32,3,TypeRegister::I32,TypeRegister::I32,TypeRegister::I32});

  auto add3 = std::shared_ptr<ge::de::CompositeFunction>(fr,)
}*/
