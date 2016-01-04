#include<geCore/stdFunctions.h>

using namespace ge::core;

Nullary::Nullary(
    std::shared_ptr<ge::core::TypeRegister>const&,
    std::shared_ptr<ge::core::Accessor>data):Function(0,"Nullary"){
  this->_getOutput().data = data;
}

MacroFunction::MacroFunction(unsigned inputs,std::shared_ptr<ge::core::TypeRegister>const&):Function(inputs,"MacroFunction"){
}

MacroFunction::~MacroFunction(){
}

bool MacroFunction::_do(){
  std::cerr<<"ERROR: MacroFunction::_do() - ";
  std::cerr<<"this should not be called at all"<<std::endl;
  return false;
}


