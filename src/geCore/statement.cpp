#include<geCore/statement.h>
#include<geCore/functionRegister.h>

using namespace ge::core;

ObjectFactory::ObjectFactory(Uses const&maxUses){
  this->_maxUses = maxUses;
  this->_uses    = 0      ;
  this->_first   = true   ;
}

ObjectFactory::~ObjectFactory(){
}


Statement::Statement(Type const&type){
  this->_type = type;
}

Statement::~Statement(){
}

StatementFactory::StatementFactory(
    std::string const&name   ,
    Uses        const&maxUses): ObjectFactory(maxUses){
  this->_name = name;
}

StatementFactory::~StatementFactory(){
}

void StatementFactory::reset(){
}

std::shared_ptr<Statement>StatementFactory::operator()(
    std::shared_ptr<FunctionRegister>const&tr){
  this->_first = this->_uses == 0;
  std::shared_ptr<Statement>res;
  if(!this->_result)this->_result = this->_do(tr);
  res = this->_result;
  this->_uses++;
  if(this->_uses==this->_maxUses){
    this->_uses = 0;
    this->_result = nullptr;
  }
  return res;
}

ResourceFactory::ResourceFactory(
    TypeRegister::TypeID const&type   ,
    Uses                 const&maxUses){
  this->_type    = type   ;
  this->_maxUses = maxUses;
  this->reset();
}

ResourceFactory::~ResourceFactory(){
}

void ResourceFactory::reset(){
  this->_uses   = 0      ;
  this->_result = nullptr;
  this->_first  = true   ;
}

std::shared_ptr<Accessor>ResourceFactory::operator()(
    std::shared_ptr<FunctionRegister>const&fr){
  this->_first=this->_uses==0;
  std::shared_ptr<Accessor>res;
  if(!this->_result)
    this->_result = fr->getTypeRegister()->sharedAccessor(this->_type);
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
