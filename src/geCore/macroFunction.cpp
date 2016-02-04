#include<geCore/macroFunction.h>

using namespace ge::core;

MacroFunction::MacroFunction(
    unsigned inputs,
    std::shared_ptr<TypeRegister>const&):
  Function(inputs,"MacroFunction"){
  }

MacroFunction::~MacroFunction(){
}

bool MacroFunction::_do(){
  std::cerr<<"ERROR: MacroFunction::_do() - ";
  std::cerr<<"this should not be called at all"<<std::endl;
  return false;
}


