#include<geDE/TypeRegister.h>
#include<geDE/Resource.h>
#include<iostream>
#include<sstream>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::de;

int32_t counter=0;

struct StructData{
  int*data;
};
void init_StructData(StructData*sd){
  counter++;
  sd->data = new int[10];
}
void free_StructData(StructData*sd){
  counter--;
  delete[]sd->data;
}


SCENARIO( "arrays can be registered using typeRegister", "[TypeRegister]" ) {

  GIVEN( "empty typeRegister" ) {
    std::shared_ptr<TypeRegister>r=std::make_shared<TypeRegister>();
    auto nofDefaultTypes=r->getNofTypes();
    auto i32 = r->getTypeId(TypeRegister::getTypeKeyword<int32_t>());
    WHEN( "adding new type int5 that is registered using TypeRegister::ARRAY 5 TypeRegister::I32" ) {
      auto t=r->addCompositeType("int5",{TypeRegister::ARRAY,5,i32});

      THEN( "the nof types inside typeRegister increased and new array type has correct size and inner type" ) {
        REQUIRE(r->getNofTypes()==nofDefaultTypes+1);
        REQUIRE(r->getArraySize(t)==5);
        REQUIRE(r->getArrayElementTypeId(t)==r->getTypeId("i32"));
      }
    }

    WHEN( "creating string accessor"){
      auto s=r->sharedResource("string");
      *s=std::string("ahoj svete");
      THEN("it should contain string"){
        REQUIRE(((std::string&)*s)=="ahoj svete");
      }
    }
    #define SHOWCERR
#ifndef SHOWCERR
    std::stringstream oss;
    auto old = std::cerr.rdbuf( oss.rdbuf() );
#endif
    WHEN("adding wrong array descriptions"){
      r->addCompositeType("a",{TypeRegister::ARRAY,300,2000});
      r->addCompositeType("b",{TypeRegister::ARRAY,300});
      r->addCompositeType("c",{TypeRegister::ARRAY});
      THEN("they should not be added"){
        REQUIRE(r->getTypeId("a")==TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("b")==TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("c")==TypeRegister::UNREGISTERED);
      }
    }
    WHEN("adding wrong recursive array descriptions"){
      r->addCompositeType("a2",{TypeRegister::ARRAY,80,TypeRegister::ARRAY,8,2000});
      r->addCompositeType("a3",{TypeRegister::ARRAY,80,TypeRegister::ARRAY,8});
      r->addCompositeType("a4",{TypeRegister::ARRAY,80,TypeRegister::ARRAY});
      THEN("they should not be added"){
        REQUIRE(r->getTypeId("a2")==TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a3")==TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a4")==TypeRegister::UNREGISTERED);
      }
    }

    WHEN("adding correct array descriptions"){
      r->addCompositeType("a0",{TypeRegister::ARRAY,100,r->getTypeId(TypeRegister::getTypeKeyword<int32_t>())});
      r->addCompositeType("a5",{TypeRegister::ARRAY,80,TypeRegister::ARRAY,80,r->getTypeId(TypeRegister::getTypeKeyword<int32_t>())});
      THEN("they should be added"){
        REQUIRE(r->getTypeId("a0")!=TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a5")!=TypeRegister::UNREGISTERED);
      }
    }
    WHEN("adding wrong struct descriptions"){
      r->addCompositeType("a0" ,{TypeRegister::STRUCT,1,2000});
      r->addCompositeType("a1" ,{TypeRegister::STRUCT,1});
      r->addCompositeType("a22",{TypeRegister::STRUCT,2,TypeRegister::STRUCT,2,r->getTypeId(TypeRegister::getTypeKeyword<int32_t>())});
      r->addCompositeType("a6" ,{TypeRegister::STRUCT,1,TypeRegister::STRUCT,1,2000});
      r->addCompositeType("a7" ,{TypeRegister::STRUCT,1,TypeRegister::STRUCT,300});
      r->addCompositeType("a8" ,{TypeRegister::STRUCT,1,TypeRegister::STRUCT});
      THEN("they should not be added"){
        REQUIRE(r->getTypeId("a0")==TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a1")==TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a22")==TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a6")==TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a7")==TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a8")==TypeRegister::UNREGISTERED);
      }
    }

    WHEN("adding correct struct descriptions"){
      r->addCompositeType("a5",{TypeRegister::STRUCT,1,r->getTypeId(TypeRegister::getTypeKeyword<int32_t>())});
      r->addCompositeType("a9",{TypeRegister::STRUCT,1,TypeRegister::STRUCT,1,r->getTypeId(TypeRegister::getTypeKeyword<int32_t>())});
      THEN("they should be added"){
        REQUIRE(r->getTypeId("a5")!=TypeRegister::UNREGISTERED);
        REQUIRE(r->getTypeId("a9")!=TypeRegister::UNREGISTERED);
      }
    }

    WHEN("adding mujTyp = ARRAY 2 I32"){
      ___;
      auto i32 = r->getTypeId(TypeRegister::getTypeKeyword<int32_t>());
      r->addCompositeType("mujTyp",{TypeRegister::ARRAY,2,i32});
      ___;
      std::cerr<<r->getTypeId("mujType")<<std::endl;
      for(size_t i=0;i<r->getNofTypes();++i)
        std::cerr<<r->type2Str(i)<<std::endl;
      auto dat=r->sharedResource("mujTyp");
      ___;
      *(*dat)[0]=12;
      ___;
      *(*dat)[1]=32;
      ___;
      THEN("TypeRegister should be able to create shared Resource of it"){
        REQUIRE(dat->getNofElements()==2);
        REQUIRE((int32_t)*(*dat)[0]==12);
        REQUIRE((int32_t)*(*dat)[1]==32);
      }
    }

    WHEN("adding mujTyp2 = STRUCT ARRAY 2 I32 F32"){
      auto mt = r->addCompositeType("mujTyp",{TypeRegister::ARRAY,2,r->getTypeId(TypeRegister::getTypeKeyword<int32_t>())});
      r->addCompositeType("mujTyp2",{TypeRegister::STRUCT,2,mt,r->getTypeId(TypeRegister::getTypeKeyword<float>())});
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

#if 0
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
#endif
    WHEN("adding two same types with different names"){
      auto a=r->addCompositeType("ivec10",{TypeRegister::ARRAY,10,r->getTypeId(TypeRegister::getTypeKeyword<int32_t>())});
      auto b=r->addCompositeType("int10",{TypeRegister::ARRAY,10,r->getTypeId(TypeRegister::getTypeKeyword<int32_t>())});
      THEN("they should be synonyms"){
        REQUIRE(r->hasSynonyms(a)==true);
        REQUIRE(r->areSynonyms("ivec10","int10")==true);
      }

    }

    WHEN("adding nullary function"){
      auto a=r->addCompositeType("nul",{TypeRegister::FCE,r->getTypeId(TypeRegister::getTypeKeyword<float>()),0});
      THEN("it should be registered"){
        REQUIRE(a!=TypeRegister::UNREGISTERED);
        REQUIRE(r->getNofFceArgs(a)==0);
      }
    }

    WHEN("adding unspecified nullary function"){
      auto a=r->addCompositeType("nul0",{TypeRegister::FCE,TypeRegister::UNREGISTERED,0});
      THEN("it should be registered"){
        REQUIRE(a!=TypeRegister::UNREGISTERED);
      }
    }

    WHEN("adding structure with extern init and free functions"){
      auto id = r->addAtomicType(
          "StructData",
          sizeof(StructData),
          [](uint8_t*ptr){free_StructData((StructData*)ptr);},
          [](int8_t*ptr){init_StructData((StructData*)ptr);});
      counter = 0;
      auto data = r->sharedResource("StructData");
      REQUIRE(counter == 1);
      data = nullptr;
      REQUIRE(counter == 0);
    }

    WHEN("adding structure with extern init and free functions and using it as EmptyResource"){
      auto id = r->addAtomicType(
          "StructData",
          sizeof(StructData),
          [](uint8_t*ptr){free_StructData((StructData*)ptr);},
          [](int8_t*ptr){init_StructData((StructData*)ptr);});
      counter = 0;
      auto data = r->sharedEmptyResource("StructData");
      auto alloc=[](StructData**d){*d=new StructData;init_StructData(*d);};
      alloc(*data);

      REQUIRE(counter == 1);
      data = nullptr;
      REQUIRE(counter == 0);
    }

    WHEN("adding structure with extern init and free functions and using it as shared ptr"){
      auto id = r->addAtomicType(
          "StructData",
          sizeof(StructData),
          [](uint8_t*ptr){free_StructData((StructData*)ptr);((std::shared_ptr<StructData>*)ptr)->~shared_ptr();},
          [](int8_t*ptr){new(ptr)std::shared_ptr<StructData>();init_StructData((StructData*)ptr);});

      counter = 0;
      auto data = r->sharedResource("SharedStructData");

      REQUIRE(counter == 1);
      data = nullptr;
      REQUIRE(counter == 0);
    }

#ifndef SHOWCERR
    std::cerr.rdbuf(old);
#endif
  }
}



