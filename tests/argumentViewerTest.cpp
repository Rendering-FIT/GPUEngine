#include<geUtil/ArgumentViewer.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::util;
using namespace std;

SCENARIO("Basic ArgumentViewer tests"){
  char const*args[] = {"test"};
  auto a = make_shared<ArgumentViewer>(1,(char**)args);
  REQUIRE(a->getApplicationName()=="test");
}

