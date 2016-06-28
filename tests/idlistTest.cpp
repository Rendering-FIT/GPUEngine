#include <sstream>
#include<geCore/idlist.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;
using namespace std;



class TestClass {
public:
   idlist_empty(TestEnum1);
   idlist(TestEnum2,FIRST=1,SECOND);
   idlist(TestEnum3,UNKNOWN=0, // comment
                    ONE=1,     ///< doxygen comment
                    SAME=1     /* comment */
                    ,BIG=100   /**< doxygen comment */
                    ,LOWER=50,WITHOUT_VALUE); // this comment should not be parsed
   idlist(TestEnum4,FIRST,);
   idlist(TestEnum5,);
};



SCENARIO("idlist test") {

   GIVEN("empty idlist") {
      WHEN("doing idof(TestClass::TestEnum1,FIRST)") {
         THEN("it should be added as item with value 0") {
            REQUIRE(unsigned(idof(TestClass::TestEnum1,FIRST))==0);
         }
      }
   }
   GIVEN("idlist with item FIRST=0") {
      WHEN("doing idof(TestClass::TestEnum1,SECOND)") {
         THEN("it should be added as item with value 1") {
            REQUIRE(unsigned(idof(TestClass::TestEnum1,SECOND))==1);
         }
      }
   }
   GIVEN("idlist with items FIRST=0,SECOND=1") {
      WHEN("doing idofstring(TestClass::TestEnum1,\"THIRD\")") {
         THEN("it should be added as item with value 2") {
            REQUIRE(unsigned(idofstring(TestClass::TestEnum1,"THIRD"))==2);
         }
      }
   }

   GIVEN("idlist with items FIRST=0,SECOND=1,THIRD=2") {
      WHEN("doing idof(TestClass::TestEnum1,[FIRST|SECOND|THIRD])") {
         THEN("value 0,1 and 2 should be returned") {
            REQUIRE((unsigned(idof(TestClass::TestEnum1,FIRST))==0 &&
                     unsigned(idof(TestClass::TestEnum1,SECOND))==1 &&
                     unsigned(idof(TestClass::TestEnum1,THIRD))==2));
         }
      }
   }
   GIVEN("idlist with items FIRST=0,SECOND=1,THIRD=2") {
      WHEN("doing idofstring(TestClass::TestEnum1,[\"FIRST\"|\"SECOND\"|\"THIRD\"])") {
         THEN("value 0,1 and 2 should be returned") {
            REQUIRE((unsigned(idofstring(TestClass::TestEnum1,"FIRST"))==0 &&
                     unsigned(idofstring(TestClass::TestEnum1,"SECOND"))==1 &&
                     unsigned(idofstring(TestClass::TestEnum1,"THIRD"))==2));
         }
      }
   }

   GIVEN("predefined idlist with items FIRST=1,SECOND") {
      WHEN("doing idof(TestClass::TestEnum2,FIRST)") {
         THEN("it should return value 1") {
            REQUIRE(unsigned(idof(TestClass::TestEnum2,FIRST))==1);
         }
      }
   }
   GIVEN("predefined idlist with items FIRST=1,SECOND") {
      WHEN("doing idof(TestClass::TestEnum2,SECOND)") {
         THEN("it should return value 2") {
            REQUIRE(unsigned(idof(TestClass::TestEnum2,SECOND))==2);
         }
      }
   }
   GIVEN("predefined idlist with items FIRST=1,SECOND") {
      WHEN("doing idof(TestClass::TestEnum2,THIRD)") {
         THEN("value 3 should be returned") {
            REQUIRE(unsigned(idof(TestClass::TestEnum2,THIRD))==3);
         }
      }
   }
   GIVEN("predefined idlist with items FIRST=1,SECOND") {
      WHEN("doing idofstring(TestClass::TestEnum2,\"FOURTH\")") {
         THEN("value 4 should be returned") {
            REQUIRE(unsigned(idofstring(TestClass::TestEnum2,"FOURTH"))==4);
         }
      }
   }

   GIVEN("predefined idlist with items UNKNOWN=0,ONE=1,SAME=1,BIG=100,LOWER=50,WITHOUT_VALUE") {
      WHEN("doing idof(TestClass::TestEnum3,[UNKNOWN|ONE|SAME|BIG|LOWER|WITHOUT_VALUE])") {
         THEN("it should return values 0,1,1,100,50,51") {
            REQUIRE((unsigned(idof(TestClass::TestEnum3,UNKNOWN))==0 &&
                     unsigned(idof(TestClass::TestEnum3,ONE))==1 &&
                     unsigned(idof(TestClass::TestEnum3,SAME))==1 &&
                     unsigned(idof(TestClass::TestEnum3,BIG))==100 &&
                     unsigned(idof(TestClass::TestEnum3,LOWER))==50 &&
                     unsigned(idof(TestClass::TestEnum3,WITHOUT_VALUE))==51));
         }
      }
   }
   GIVEN("predefined idlist with items UNKNOWN=0,ONE=1,SAME=1,BIG=100,LOWER=50,WITHOUT_VALUE") {
      WHEN("doing idof(TestClass::TestEnum3,NEXT1)") {
         THEN("value 52 should be returned") {
            REQUIRE(unsigned(idof(TestClass::TestEnum3,NEXT1))==52);
         }
      }
   }
   GIVEN("predefined idlist with items UNKNOWN=0,ONE=1,SAME=1,BIG=100,LOWER=50,WITHOUT_VALUE") {
      WHEN("doing idofstring(TestClass::TestEnum3,\"NEXT2\")") {
         THEN("value 53 should be returned") {
            REQUIRE(unsigned(idofstring(TestClass::TestEnum3,"NEXT2"))==53);
         }
      }
   }

   GIVEN("predefined idlist with items FIRST=0") {
      WHEN("doing idof(TestClass::TestEnum4,FIRST)") {
         THEN("value 0 should be returned") {
            REQUIRE(unsigned(idof(TestClass::TestEnum4,FIRST))==0);
         }
      }
   }
}
