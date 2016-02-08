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



FunctionNodeFactory::FunctionNodeFactory(std::shared_ptr<FunctionFactory>const&fac,unsigned maxUses){
  this->functionFactory = fac;
  this->_maxUses = maxUses;
  this->reset();
}

FunctionNodeFactory::~FunctionNodeFactory(){
}

void FunctionNodeFactory::reset(){
  this->_uses    = 0      ;
  this->_first   = true   ;
  this->_result  = nullptr;
}

std::shared_ptr<Statement>FunctionNodeFactory::operator()(
    SharedTypeRegister const&tr){
  this->_first = this->_uses == 0;
  if(this->resourceFactories.size()!=this->inputFactories.size()){
    std::cerr<<"ERROR: FunctionNodeFactory::operator()() - different ";
    std::cerr<<"number of input functions and input resources"<<std::endl;
    return nullptr;
  }
  if(!this->functionFactory)return nullptr;

  std::shared_ptr<Statement>res;
  if(!this->_result)this->_result = (*this->functionFactory)(tr);
  res = this->_result;
  this->_uses++;
  if(this->_uses==this->_maxUses){
    this->_uses = 0;
    this->_result = nullptr;
  }
  auto fce=std::dynamic_pointer_cast<Function>(res);
  using Iter=decltype(this->resourceFactories)::size_type;
  for(Iter i=0;i<this->resourceFactories.size();++i){
    if(!this->resourceFactories[i]!=!this->inputFactories[i]){
      std::cerr<<"ERROR: FunctionNodeFactory::operator()() - input factory ";
      std::cerr<<"and input resource does not correspond"<<std::endl;
      return nullptr;
    }
    if(!this->resourceFactories[i])continue;
    auto in=(*this->inputFactories[i])(tr);
    auto inFce = std::dynamic_pointer_cast<Function>(in);
    inFce->bindOutput((*this->resourceFactories[i])(tr));
    fce->bindInput((unsigned)i,inFce);
  }
  return res;
}
