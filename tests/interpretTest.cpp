#include<geCore/interpret.h>
#include<geCore/stdFunctions.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;

SCENARIO( "basic interpret tests", "[Function]" ) {
  std::shared_ptr<ge::core::TypeRegister>typeRegister = std::make_shared<ge::core::TypeRegister>();
  GIVEN( "basic expression" ) {
    auto fa=std::make_shared<ge::core::Nullary>(typeRegister,101.f );
    auto fb=std::make_shared<ge::core::Nullary>(typeRegister,1.1f  );
    auto fc=std::make_shared<ge::core::Nullary>(typeRegister,2.2f  );
    auto fd=std::make_shared<ge::core::Nullary>(typeRegister,1000.f);

    auto f0=std::make_shared<ge::core::Add<float>>(typeRegister,typeRegister->sharedAccessor("f32"));
    f0->bindInput(0,fa);
    f0->bindInput(1,fb);
    auto f1=std::make_shared<ge::core::Add<float>>(typeRegister,typeRegister->sharedAccessor("f32"));
    f1->bindInput(0,f0);
    f1->bindInput(1,fc);
    auto f2=std::make_shared<ge::core::Sub<float>>(typeRegister,typeRegister->sharedAccessor("f32"));
    f2->bindInput(0,f0);
    f2->bindInput(1,fd);
    auto f3=std::make_shared<ge::core::Cast<float,int>>(typeRegister,typeRegister->sharedAccessor("i32"));
    f3->bindInput(0,f2);
    WHEN("running f1"){
      (*f1)();
      THEN( "output of f1 should be computed correctly" ) {
        REQUIRE((float)(*f1->getOutput())==((101.f+1.1f)+2.2f));
      }
    }
    WHEN("running f2"){
      (*f2)();
      THEN( "output of f2 should be computed correctly"){
        REQUIRE((float)(*f2->getOutput())==((101.f+1.1f)-1000.f));
      }
    }
    WHEN("running f3"){
      (*f3)();
      THEN("output of f3 should be computed correctly"){
        REQUIRE((int)(*f3->getOutput())==(int)((101.f+1.1f)-1000.f));
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
    auto fa=std::make_shared<ge::core::Nullary>(typeRegister,(unsigned)10);
    auto fb=std::make_shared<ge::core::Nullary>(typeRegister,(unsigned)12);
    auto fc=std::make_shared<ge::core::Nullary>(typeRegister,(unsigned)0 );

    auto cond=std::make_shared<ge::core::Less<unsigned>>(typeRegister,typeRegister->sharedAccessor("bool"));
    cond->bindInput(0,fa);
    cond->bindInput(1,fb);

    auto trueBody = std::make_shared<ge::core::Ass<unsigned>>(typeRegister);
    trueBody->bindInput(0,fc);
    trueBody->bindInput(1,fa);

    auto falseBody = std::make_shared<ge::core::Ass<unsigned>>(typeRegister);
    falseBody->bindInput(0,fc);
    falseBody->bindInput(1,fb);

    auto iff=std::make_shared<ge::core::If>(cond,trueBody,falseBody);

    WHEN("running iff"){
      (*iff)();
      THEN("it should correctly choose lesser value"){
        REQUIRE((unsigned)(*fc->getOutput())==10);
      }
    }
  }
  GIVEN("while statement"){
    /*
     * unsigned i=1;
     * unsigned k=1;
     * while(i<10){
     *  k*=i;
     *  i++;
     * }
     */
    auto fi    = std::make_shared<ge::core::Nullary>(typeRegister,(unsigned)1u );
    auto fk    = std::make_shared<ge::core::Nullary>(typeRegister,(unsigned)1u );
    auto fiend = std::make_shared<ge::core::Nullary>(typeRegister,(unsigned)10u);

    auto cond=std::make_shared<ge::core::Less<unsigned>>(typeRegister,typeRegister->sharedAccessor("bool"));
    cond->bindInput(0,fi   );
    cond->bindInput(1,fiend);

    auto mult=std::make_shared<ge::core::Muls<unsigned>>(typeRegister);
    mult->bindInput(0,fk);
    mult->bindInput(1,fi);

    auto inc=std::make_shared<ge::core::IncrPost<unsigned>>(typeRegister);
    inc->bindInput(0,fi);

    auto body=std::make_shared<ge::core::Body>();
    body->addStatement(mult);
    body->addStatement(inc );

    auto wh=std::make_shared<ge::core::While>(cond,body);
    WHEN("running wh"){
      (*wh)();
      THEN("it should compute factorial of 9"){
        REQUIRE((unsigned)(*fk->getOutput())==362880);
      }
    }

  }
}

SCENARIO( "ticks tests", "[Function]" ) {
  std::shared_ptr<ge::core::TypeRegister>typeRegister = std::make_shared<ge::core::TypeRegister>();
  class AddTen: public ge::core::Function{
    public:
      unsigned counter=0;
      AddTen(std::shared_ptr<ge::core::TypeRegister>const&tr):Function(tr,{TypeRegister::FCE,TypeRegister::F32,1,TypeRegister::F32},"AddTen"){
        //this->_setInput(0,tr->getTypeId("f32"));
        //this->_setOutput(tr->getTypeId("f32"));
      }
    protected:
      virtual bool _do(){
        if(!this->hasInput(0)||!this->hasOutput())return false;
        if(!this->_inputChanged(0))return false;
        counter++;
        (float&)(*this->_getOutput().data)=
          (float&)(*this->getInputData(0))+10.f;
        return true;
      }
  };
  class Add: public ge::core::Function{
    public:
      unsigned counter=0;
      Add(std::shared_ptr<ge::core::TypeRegister>const&tr):Function(tr,{TypeRegister::FCE,TypeRegister::F32,2,TypeRegister::F32,TypeRegister::F32},"Add"){
        //this->_setInput(0,tr->getTypeId("f32"));
        //this->_setInput(1,tr->getTypeId("f32"));
        //this->_setOutput(tr->getTypeId("f32"));
      }
    protected:
      virtual bool _do(){
        if(!this->hasInput(0)||!this->hasInput(1)||!this->hasOutput())return false;
        if(!this->_inputChanged(0)&&!this->_inputChanged(1))return false;
        counter++;
        (float&)(*this->_getOutput().data)=
          (float&)(*this->getInputData(0))+(float&)(*this->getInputData(1));
        return true;
      }
  };

  GIVEN( "basic expression" ) {
    auto fa      = std::make_shared<ge::core::Nullary>(typeRegister,10.f);
    auto faddten = std::make_shared<AddTen>(typeRegister);
    auto fadd    = std::make_shared<Add>(typeRegister);

    faddten->bindInput(0,fa);
    faddten->bindOutput(typeRegister->sharedAccessor("f32"));
    fadd->bindInput(0,faddten);
    fadd->bindInput(1,faddten);
    fadd->bindOutput(typeRegister->sharedAccessor("f32"));


    WHEN("running fadd"){
      (*fadd)();
      THEN( "output of fadd should be 40.f" ) {
        REQUIRE((float&)*fadd->getOutput() == 40.f);
      }
      THEN( "faddten should be called only once"){
        REQUIRE(faddten->counter == 1);
      }
    }
  }

}


