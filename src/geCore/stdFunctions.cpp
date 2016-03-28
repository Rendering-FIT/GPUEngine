#include<geCore/stdFunctions.h>

using namespace ge::core;

Nullary::Nullary(
    std::shared_ptr<ge::core::FunctionRegister>const&fr,
    std::shared_ptr<ge::core::Accessor>data):AtomicFunction(fr,{TypeRegister::FCE,TypeRegister::UNREGISTERED,0},Nullary::name(),Nullary::factory()){
  this->_outputData = data;
}


