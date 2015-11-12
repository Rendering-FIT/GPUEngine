#include<geCore/stdFunctions.h>

using namespace ge::core;

Nullary::Nullary(std::shared_ptr<ge::core::Accessor>data):Function(0){
  this->_output = data;
}

