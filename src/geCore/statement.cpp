#include<geCore/statement.h>

using namespace ge::core;

Statement::Statement(Type type){
  this->_type = type;
}

Statement::~Statement(){
}

ResourceFactory::ResourceFactory(TypeRegister::TypeID type,unsigned maxUses){
  this->_uses    = 0      ;
  this->_maxUses = maxUses;
  this->_result  = nullptr;
  this->_type    = type   ;
}

std::shared_ptr<Accessor>ResourceFactory::operator()(SharedTypeRegister const&tr){
  std::shared_ptr<Accessor>res;
  if(!this->_result)this->_result = tr->sharedAccessor(this->_type);
  res=this->_result;
  this->_uses++;
  if(this->_uses==this->_maxUses){
    this->_uses   = 0      ;
    this->_result = nullptr;
  }
  return res;
}

