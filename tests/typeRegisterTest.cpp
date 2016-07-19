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

SCENARIO("keyword tests","[TypeRegister]"){
  REQUIRE(TypeRegister::getTypeKeyword<int32_t>()=="i32");
  REQUIRE(TypeRegister::getTypeKeyword<int32_t&>()=="i32");
  REQUIRE(TypeRegister::getTypeKeyword<int32_t const>()=="i32");
  REQUIRE(TypeRegister::getTypeKeyword<int32_t const&>()=="i32");
  REQUIRE(TypeRegister::getTypeKeyword<int32_t*>()=="i32*");
  REQUIRE(TypeRegister::getTypeKeyword<int32_t const*>()=="i32*");

}

SCENARIO( "arrays can be registered using typeRegister", "[TypeRegister]" ) {
  GIVEN( "empty typeRegister" ) {
    std::shared_ptr<TypeRegister>r=std::make_shared<TypeRegister>();
    auto nofDefaultTypes=r->getNofTypes();
    auto i32 = r->getTypeId(TypeRegister::getTypeKeyword<int32_t>());
#if 1
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
//#define SHOWCERR
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
#endif
    WHEN("adding pointer"){
      auto i32p = r->addAtomicType("i32*",sizeof(int32_t*));
      auto s = r->construct(i32p);
      int32_t a=32;
      *(int32_t**)s=&a;
      a=100;
      REQUIRE(*(*(int32_t**)s)==100);
      r->destroy(s,i32p);
    }
#if 1
    WHEN("adding mujTyp = ARRAY 2 I32"){
      auto i32 = r->getTypeId(TypeRegister::getTypeKeyword<int32_t>());
      r->addCompositeType("mujTyp",{TypeRegister::ARRAY,2,i32});
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
      auto i32 = r->getTypeId(TypeRegister::getTypeKeyword<int32_t>());
      auto f32 = r->getTypeId(TypeRegister::getTypeKeyword<float>());
      auto mt = r->addCompositeType("mujTyp",{TypeRegister::ARRAY,2,i32});
      r->addCompositeType("mujTyp2",{TypeRegister::STRUCT,2,mt,f32});
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
      r->addAtomicType("Class0",sizeof(Class0),[](void*ptr){new(ptr)Class0;},[](void*ptr){((Class0*)ptr)->~Class0();});
      r->addAtomicType("Class1",sizeof(Class0),[](void*ptr){new(ptr)Class0;});
      r->addAtomicType("Class2",sizeof(Class0),nullptr,[](void*ptr){((Class0*)ptr)->~Class0();});
      r->addAtomicType("Class3",sizeof(Class0));
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
        alloc((Class0**)a0->getDataAddress());
        REQUIRE(counter==1);
        a0=nullptr;
        REQUIRE(counter==0);
      }
    }

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
      auto a=r->addCompositeType("nul0",{TypeRegister::FCE,TypeRegister::AUTO,0});
      THEN("it should be registered"){
        REQUIRE(a!=TypeRegister::UNREGISTERED);
      }
    }

    WHEN("adding structure with extern init and free functions"){
      auto id = r->addAtomicType(
          "StructData",
          sizeof(StructData),
          [](void*ptr){init_StructData((StructData*)ptr);},
          [](void*ptr){free_StructData((StructData*)ptr);});
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
          [](void*ptr){init_StructData((StructData*)ptr);},
          [](void*ptr){free_StructData((StructData*)ptr);});
      counter = 0;
      auto data = r->sharedEmptyResource("StructData");
      auto alloc=[](StructData**d){*d=new StructData;init_StructData(*d);};
      alloc((StructData**)data->getDataAddress());

      REQUIRE(counter == 1);
      data = nullptr;
      REQUIRE(counter == 0);
    }

    WHEN("adding structure with extern init and free functions and using it as shared ptr"){
      auto id = r->addAtomicType(
          "SharedStructData",
          sizeof(std::shared_ptr<StructData>),
          [](void*ptr){new(ptr)std::shared_ptr<StructData>();init_StructData((StructData*)ptr);},
          [](void*ptr){free_StructData((StructData*)ptr);((std::shared_ptr<StructData>*)ptr)->~shared_ptr();});

      counter = 0;
      auto data = r->sharedResource("SharedStructData");

      REQUIRE(counter == 1);
      data = nullptr;
      REQUIRE(counter == 0);
    }

#ifndef SHOWCERR
    std::cerr.rdbuf(old);
#endif

#endif
  }
}



