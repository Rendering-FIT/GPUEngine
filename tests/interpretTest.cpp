#define CATCH_CONFIG_MAIN
#include"catch.hpp"

#include<geCore/interpret.h>
#include<geCore/stdFunctions.h>

using namespace ge::core;

SCENARIO( "basic interpret tests", "[Function]" ) {
  std::shared_ptr<ge::core::TypeRegister>typeRegister = std::make_shared<ge::core::TypeRegister>();
  GIVEN( "basic expression" ) {
    auto va=typeRegister->sharedAccessor<float>(101.f  );
    auto vb=typeRegister->sharedAccessor<float>(1.1f   );
    auto vc=typeRegister->sharedAccessor<float>(2.2f   );
    auto vd=typeRegister->sharedAccessor<float>(1000.f );

    auto fa=std::make_shared<ge::core::Nullary>(va);
    auto fb=std::make_shared<ge::core::Nullary>(vb);
    auto fc=std::make_shared<ge::core::Nullary>(vc);
    auto fd=std::make_shared<ge::core::Nullary>(vd);

    auto f0=std::make_shared<ge::core::Add<float>>(typeRegister->sharedAccessor("f32"));
    f0->setInput(0,fa);
    f0->setInput(1,fb);
    auto f1=std::make_shared<ge::core::Add<float>>(typeRegister->sharedAccessor("f32"));
    f1->setInput(0,f0);
    f1->setInput(1,fc);
    auto f2=std::make_shared<ge::core::Sub<float>>(typeRegister->sharedAccessor("f32"));
    f2->setInput(0,f0);
    f2->setInput(1,fd);
    auto f3=std::make_shared<ge::core::Cast<float,int>>(typeRegister->sharedAccessor("i32"));
    f3->setInput(0,f2);

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
    auto fa=std::make_shared<ge::core::Nullary>((unsigned)10,typeRegister);
    auto fb=std::make_shared<ge::core::Nullary>((unsigned)12,typeRegister);
    auto fc=std::make_shared<ge::core::Nullary>((unsigned)0 ,typeRegister);

    auto cond=std::make_shared<ge::core::Less<unsigned>>(typeRegister->sharedAccessor("bool"));
    cond->setInput(0,fa);
    cond->setInput(1,fb);

    auto trueBody = std::make_shared<ge::core::Ass<unsigned>>();
    trueBody->setInput(0,fc);
    trueBody->setInput(1,fa);

    auto falseBody = std::make_shared<ge::core::Ass<unsigned>>();
    falseBody->setInput(0,fc);
    falseBody->setInput(1,fb);

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
    auto fi    = std::make_shared<ge::core::Nullary>((unsigned)1u ,typeRegister);
    auto fk    = std::make_shared<ge::core::Nullary>((unsigned)1u ,typeRegister);
    auto fiend = std::make_shared<ge::core::Nullary>((unsigned)10u,typeRegister);

    auto cond=std::make_shared<ge::core::Less<unsigned>>(typeRegister->sharedAccessor("bool"));
    cond->setInput(0,fi   );
    cond->setInput(1,fiend);

    auto mult=std::make_shared<ge::core::Muls<unsigned>>();
    mult->setInput(0,fk);
    mult->setInput(1,fi);

    auto inc=std::make_shared<ge::core::IncrPost<unsigned>>();
    inc->setInput(0,fi);

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



