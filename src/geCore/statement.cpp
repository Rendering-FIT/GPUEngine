#include<geCore/statement.h>

using namespace ge::core;

Statement::Statement(Type type){
  this->_type = type;
}

Statement::~Statement(){
}

ResourceFactory::ResourceFactory(TypeRegister::TypeID type,unsigned maxUses){
  this->_type    = type   ;
  this->_maxUses = maxUses;
  this->reset();
}

ResourceFactory::~ResourceFactory(){
}

void ResourceFactory::reset(){
  this->_uses    = 0      ;
  this->_result  = nullptr;
  this->_first   = true   ;
}

std::shared_ptr<Accessor>ResourceFactory::operator()(std::shared_ptr<FunctionRegister> const&fr){
  this->_first=this->_uses==0;
  std::shared_ptr<Accessor>res;
  if(!this->_result)this->_result = fr->getTypeRegister()->sharedAccessor(this->_type);
  res=this->_result;
  this->_uses++;
  if(this->_uses==this->_maxUses){
    this->_uses   = 0      ;
    this->_result = nullptr;
  }
  return res;
}

bool ResourceFactory::firstConstruction()const{
  return this->_first;
}
