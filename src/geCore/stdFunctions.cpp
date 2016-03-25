#include<geCore/stdFunctions.h>

using namespace ge::core;

Nullary::Nullary(
    std::shared_ptr<ge::core::TypeRegister>const&tr,
    std::shared_ptr<ge::core::Accessor>data):AtomicFunction(tr,{TypeRegister::FCE,TypeRegister::UNREGISTERED,0},"Nullary"){
  this->_outputData = data;
}


