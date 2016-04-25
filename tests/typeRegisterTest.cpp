#include<geCore/TypeRegister.h>
#include<geCore/Resource.h>
#include<iostream>
#include<sstream>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;

int32_t counter=0;
SCENARIO( "arrays can be registered using typeRegister", "[TypeRegister]" ) {

  GIVEN( "empty typeRegister" ) {
    std::shared_ptr<TypeRegister>r=std::make_shared<TypeRegister>();
    auto nofDefaultTypes=r->getNofTypes();

    WHEN( "adding new type int5 that is registered using TypeRegister::ARRAY 5 TypeRegister::I32" ) {
      auto t=r->addType("int5",TypeRegister::ARRAY,5,TypeRegister::I32);

      THEN( "the nof types inside typeRegister increased and new array type has correct size and inner type" ) {
        REQUIRE(r->getNofTypes()==nofDefaultTypes+1);
        REQUIRE(r->getArraySize(t)==5);
        REQUIRE(r->getArrayInnerTypeId(t)==r->getTypeId("i32"));
      }
    }
    WHEN( "creating string accessor"){
      auto s=r->sharedResource("string");
      *s=std::string("ahoj svete");
      THEN("it should contain string"){
        REQUIRE(((std::string&)*s)=="ahoj svete");
      }
    }
//#define SHOWCERR
#ifndef SHOWCERR
    std::stringstream oss;
    auto old = std::cerr.rdbuf( oss.rdbuf() );
#endif

    WHEN("adding wrong array descriptions"){
      r->addType("a",TypeRegister::ARRAY,300,2000);
      r->addType("b",TypeRegister::ARRAY,300);
      r->addType("c",TypeRegister::ARRAY);
      r->addType("d");
      THEN("they should not be added"){
        REQUIRE(r->getTypeId("a")==ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("b")==ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("c")==ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("d")==ge::core::TypeRegister::UNREGISTERED);
      }
    }

    WHEN("adding wrong recursive array descriptions"){
      r->addType("a2",TypeRegister::ARRAY,80,TypeRegister::ARRAY,8,2000);
      r->addType("a3",TypeRegister::ARRAY,80,TypeRegister::ARRAY,8);
      r->addType("a4",TypeRegister::ARRAY,80,TypeRegister::ARRAY);
      THEN("they should not be added"){
        REQUIRE(r->getTypeId("a2")==ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a3")==ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a4")==ge::core::TypeRegister::UNREGISTERED);
      }
    }

    WHEN("adding correct array descriptions"){
      r->addType("a0",TypeRegister::ARRAY,100,TypeRegister::I32);
      r->addType("a1",TypeRegister::ARRAY,90,"i32");
      r->addType("a5",TypeRegister::ARRAY,80,TypeRegister::ARRAY,80,TypeRegister::I32);
      THEN("they should be added"){
        REQUIRE(r->getTypeId("a0")!=ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a1")!=ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a5")!=ge::core::TypeRegister::UNREGISTERED);
      }
    }
    WHEN("adding wrong struct descriptions"){
      r->addType("a0",TypeRegister::STRUCT,1,2000);
      r->addType("a1",TypeRegister::STRUCT,1);
      r->addType("a22",TypeRegister::STRUCT,2,TypeRegister::STRUCT,2,TypeRegister::I32);
      r->addType("a3",TypeRegister::STRUCT,0,"i32");
      r->addType("a6",TypeRegister::STRUCT,1,TypeRegister::STRUCT,1,2000);
      r->addType("a7",TypeRegister::STRUCT,1,TypeRegister::STRUCT,300);
      r->addType("a8",TypeRegister::STRUCT,1,TypeRegister::STRUCT);
      THEN("they should not be added"){
        REQUIRE(r->getTypeId("a0")==ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a1")==ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a22")==ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a3")==ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a6")==ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a7")==ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a8")==ge::core::TypeRegister::UNREGISTERED);
      }
    }

    WHEN("adding correct struct descriptions"){
      r->addType("a4",TypeRegister::STRUCT,1,"i32");
      r->addType("a5",TypeRegister::STRUCT,1,TypeRegister::I8);
      r->addType("a9",TypeRegister::STRUCT,1,TypeRegister::STRUCT,1,TypeRegister::I32);
      THEN("they should be added"){
        REQUIRE(r->getTypeId("a4")!=ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a5")!=ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a9")!=ge::core::TypeRegister::UNREGISTERED);
      }
    }

    WHEN("adding mujTyp = ARRAY 2 I32"){
      r->addType("mujTyp",ge::core::TypeRegister::ARRAY,2,ge::core::TypeRegister::I32);
      auto dat=r->sharedResource("mujTyp");
      *(*dat)[0]=12;
      *(*dat)[1]=32;
      THEN("TypeRegister should be able to create shared Resource of it"){
        REQUIRE(dat->getNofElements()==2);
        REQUIRE((int32_t)*(*dat)[0]==12);
        REQUIRE((int32_t)*(*dat)[1]==32);
      }
    }

    WHEN("adding mujTyp2 = STRUCT ARRAY 2 I32 F32"){
      r->addType("mujTyp",ge::core::TypeRegister::ARRAY,2,ge::core::TypeRegister::I32);
      r->addType("mujTyp2",ge::core::TypeRegister::STRUCT,2,"mujTyp","f32");
      auto dat2=r->sharedResource("mujTyp2");
      *(*(*dat2)[0])[0]=32;
      *(*(*dat2)[0])[1]=10;
      *(*dat2)[1]=13.3f;
      THEN("TypeRegister should be able to create shared Resource of it"){
        REQUIRE(dat2->getNofElements()==2);
        REQUIRE((*dat2)[0]->getNofElements()==2);
        REQUIRE((int32_t)*(*(*dat2)[0])[0]==32);
        REQUIRE((int32_t)*(*(*dat2)[0])[1]==10);
        REQUIRE((float_t)*(*dat2)[1]==13.3f);
      }
    }

    WHEN("adding custom class"){
      class Class0{
        public:
          Class0(){
            counter++;
          }
          ~Class0(){
            counter--;
          }
      };
      r->addClassCD<Class0>("Class0");
      r->addClassC <Class0>("Class1");
      r->addClassD <Class0>("Class2");
      r->addClass  <Class0>("Class3");
      THEN("creating Resource with addClassCD should correctly incr and decr counter"){
        counter=0;
        auto a0=r->sharedResource("Class0");
        REQUIRE(counter==1);
        a0=nullptr;
        REQUIRE(counter==0);
      }

      THEN("creating Resource with addClassC should correctly incr and decr counter"){
        counter=0;
        auto a1=r->sharedResource("Class1");
        REQUIRE(counter==1);
        a1=nullptr;
        REQUIRE(counter==1);
      }

      THEN("creating Resource with addClassD should correctly incr and decr counter"){
        counter=1;
        auto a2=r->sharedResource("Class2");
        REQUIRE(counter==1);
        a2=nullptr;
        REQUIRE(counter==0);
      }

      THEN("creating Resource with addClass should correctly incr and decr counter"){
        counter=0;
        auto a3=r->sharedResource("Class3");
        REQUIRE(counter==0);
        a3=nullptr;
        REQUIRE(counter==0);
      }

      THEN("create empty Resource and filling it later should be doable"){
        counter=0;
        auto a0=r->sharedEmptyResource("Class0");
        auto alloc=[](Class0**d){*d=new Class0;};
        alloc(*a0);
        REQUIRE(counter==1);
        a0=nullptr;
        REQUIRE(counter==0);
      }
    }

    WHEN("adding two same types with different names"){
      auto a=r->addType("ivec10",ge::core::TypeRegister::ARRAY,10,ge::core::TypeRegister::I32);
      auto b=r->addType("int10",ge::core::TypeRegister::ARRAY,10,ge::core::TypeRegister::I32);
      THEN("they should be synonyms"){
        REQUIRE(r->hasSynonyms(a)==true);
        REQUIRE(r->areSynonyms("ivec10","int10")==true);
      }

    }

    WHEN("adding nullary function"){
      auto a=r->addType("nul",ge::core::TypeRegister::FCE,ge::core::TypeRegister::F32,0);
      THEN("it should be registered"){
        REQUIRE(a!=ge::core::TypeRegister::UNREGISTERED);
        REQUIRE(r->getNofFceArgs(a)==0);
      }
    }

    WHEN("adding unspecified nullary function"){
      auto a=r->addType("nul0",ge::core::TypeRegister::FCE,ge::core::TypeRegister::UNREGISTERED,0);
      THEN("it should be registered"){
        REQUIRE(a!=ge::core::TypeRegister::UNREGISTERED);
      }
    }



#ifndef SHOWCERR
    std::cerr.rdbuf(old);
#endif
  }
}

