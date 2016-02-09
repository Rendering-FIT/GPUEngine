#include<geCore/body.h>

using namespace ge::core;

Body::Body():Statement(BODY){

}

Body::~Body(){

}

void Body::addStatement(std::shared_ptr<Statement>const&statement){
  this->_statements.push_back(statement);
}

std::vector<std::shared_ptr<Statement>>::size_type Body::size()const{
  return this->_statements.size();
}

Body::Iterator Body::begin()const{
  return this->_statements.begin();
}

Body::Iterator Body::end()const{
  return this->_statements.end();
}

void Body::operator()(){
  for(auto x:this->_statements)
    (*x)();
}


BodyFactory::~BodyFactory(){
}

std::shared_ptr<Statement>BodyFactory::operator()(SharedTypeRegister const&tr){
  auto result = std::make_shared<Body>();
  for(auto x:this->factories)
    result->addStatement((*x)(tr));
  return result;
}


