#include<geCore/body.h>

using namespace ge::core;

Body::Body():Statement(BODY){

}

Body::~Body(){

}

void Body::addStatement(std::shared_ptr<Statement>const&statement){
  this->_statements.push_back(statement);
}

Body::StatementIndex Body::size()const{
  return this->_statements.size();
}

std::shared_ptr<Statement>const&Body::operator[](StatementIndex index)const{
  return this->_statements[index];
}

Body::StatementIterator Body::begin()const{
  return this->_statements.begin();
}

Body::StatementIterator Body::end()const{
  return this->_statements.end();
}

void Body::operator()(){
  for(auto x:this->_statements)
    (*x)();
}

BodyFactory::BodyFactory(std::string name,unsigned maxUses):StatementFactory(name,maxUses){
}

BodyFactory::~BodyFactory(){
}

std::shared_ptr<Statement>BodyFactory::operator()(std::shared_ptr<FunctionRegister>const&fr){
  auto result = std::make_shared<Body>();
  for(auto x:this->factories)
    result->addStatement((*x)(fr));
  return result;
}


