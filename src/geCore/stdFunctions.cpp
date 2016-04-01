#include<geCore/stdFunctions.h>
#include<geCore/stdNumericFunctions.h>
#include<geCore/stdRelationalFunctions.h>
#include<geCore/stdIntegerFunctions.h>

using namespace ge::core;

Nullary::Nullary(
    std::shared_ptr<ge::core::FunctionRegister>const&fr,
    std::shared_ptr<ge::core::Accessor>data):AtomicFunction(fr,fr->getFunctionId(TypeRegister::getTypeKeyword<Nullary>())){
  this->_outputData = data;
}


void ge::core::registerStdFunctions(std::shared_ptr<FunctionRegister>const&fr){
  auto tr=fr->getTypeRegister();
  fr->addFunction(tr->addType("",{TypeRegister::FCE,TypeRegister::UNREGISTERED,0}),
              TypeRegister::getTypeKeyword<Nullary>(),
              Function::factory<Nullary>());

  registerStdNumericFunctions(fr);
  registerStdRelationalFunctions(fr);
  registerStdIntegerFunctions(fr);

  ADD_BINARY_FUNCTION_SIMPLE(Add,std::string)
  ALL_LOOP(ADD_UNARY_FUNCTION_SIMPLE,Assignment)
  SIGNED_NUMERIC_LOOP(ADD_UNARY_FUNCTION_SIMPLE,UnaryMinus)
}
