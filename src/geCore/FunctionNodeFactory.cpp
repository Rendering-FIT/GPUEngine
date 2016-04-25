#include<geCore/FunctionNodeFactory.h>
#include<geCore/function.h>

using namespace ge::core;

FunctionNodeFactory::FunctionNodeFactory(
    std::string name,Uses maxUses):FunctionFactory(name,maxUses){
}

void FunctionNodeFactory::setFactory(
    std::shared_ptr<StatementFactory>const&fac){
  assert(this!=nullptr);
  this->functionFactory = std::dynamic_pointer_cast<FunctionFactory>(fac);
}

void FunctionNodeFactory::addResourceFactory(
    std::shared_ptr<ResourceFactory>const&factory){
  assert(this!=nullptr);
  this->resourceFactories.push_back(factory);
}

void FunctionNodeFactory::addInputFactory(
    std::shared_ptr<StatementFactory>const&factory){
  assert(this!=nullptr);
  this->inputFactories.push_back(std::dynamic_pointer_cast<FunctionFactory>(factory));
}

FunctionNodeFactory::~FunctionNodeFactory(){
}

void FunctionNodeFactory::reset(){
  assert(this!=nullptr);
  this->_uses    = 0      ;
  this->_first   = true   ;
  this->_result  = nullptr;
}

std::shared_ptr<Statement>FunctionNodeFactory::_do(
    std::shared_ptr<FunctionRegister> const&tr){
  assert(this!=nullptr);
  assert(tr!=nullptr);
  this->_first = this->_uses == 0;
  if(this->resourceFactories.size()!=this->inputFactories.size()){
    std::cerr<<"ERROR: FunctionNodeFactory::operator()() - different ";
    std::cerr<<"number of input functions and input resources"<<std::endl;
    return nullptr;
  }
  if(!this->functionFactory)return nullptr;

  auto res = (*this->functionFactory)(tr);

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
    assert(inFce!=nullptr);
    inFce->bindOutput((*this->resourceFactories[i])(tr));
    assert(fce!=nullptr);
    fce->bindInput(i,inFce);
  }
  return res;
}


