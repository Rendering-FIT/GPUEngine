#include<geCore/TypeRegister.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;

SCENARIO( "arrays can be registered using typeRegister", "[TypeRegister]" ) {

  GIVEN( "empty typeRegister" ) {
    std::shared_ptr<TypeRegister>r=std::make_shared<TypeRegister>();
    unsigned nofDefaultTypes=r->getNofTypes();

    WHEN( "adding new type int5 that is registered using TypeRegister::ARRAY 5 TypeRegister::I32" ) {
      auto t=r->addType("int5",TypeRegister::ARRAY,5,TypeRegister::I32);

      THEN( "the nof types inside typeRegister increased and new array type has correct size and inner type" ) {
        REQUIRE(r->getNofTypes()==nofDefaultTypes+1);
        REQUIRE(r->getArraySize(t)==5);
        REQUIRE(r->getArrayInnerTypeId(t)==r->getTypeId("i32"));
      }
    }
    WHEN( "creating string accessor"){
      auto s=r->sharedAccessor("string");
      *s=std::string("ahoj svete");
      THEN("it should contain string"){
        REQUIRE(((std::string&)*s)=="ahoj svete");
      }

    }
  }
}

