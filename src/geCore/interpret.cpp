#include<geCore/interpret.h>

using namespace ge::core;

Statement::Statement(Type type){
  this->_type = type;
}

Statement::~Statement(){
}

Function::Function(unsigned n):Statement(FUNCTION){
  for(unsigned i=0;i<n;++i)
    this->_inputs.push_back(nullptr);
}

Function::~Function(){

}

unsigned long long Function::getTick()const{
  return this->_tickNumber;
}

void Function::setTick(unsigned long long tick){
  this->_tickNumber = tick;
}

void Function::updateTick(){
  this->_tickNumber++;
}

void Function::setInput(unsigned i,std::shared_ptr<Function>function){
  this->_inputs[i]=function;
}

void Function::setOutput(std::shared_ptr<ge::core::Accessor>data){
  this->_output = data;
}

std::shared_ptr<ge::core::Accessor>const&Function::getOutput()const{
  return this->_output;
}

Function::Iterator Function::begin()const{
  return this->_inputs.begin();
}

Function::Iterator Function::end  ()const{
  return this->_inputs.end();
}

void Function::operator()(){
}

void Function::resolveInputs(){
  this->updateTick();
  for(auto x:this->_inputs){
    if(x->getTick()<this->getTick()){
      (*x)();
      x->setTick(this->getTick());
    }
  }
}



Body::Body():Statement(BODY){

}

Body::~Body(){

}

void Body::addStatement(std::shared_ptr<Statement>const&statement){
  this->_statements.push_back(statement);
}

unsigned Body::size()const{
  return this->_statements.size();
}

Body::Iterator Body::begin()const{
  return this->_statements.begin();
}
Body::Iterator Body::end()const{
  return this->_statements.end();
}

void Body::operator()(){
  for(auto x:this->_statements){
//    std::cerr<<"body{";
    (*x)();
//    std::cerr<<"}"<<std::endl;
  }
}



While::While(std::shared_ptr<Function>const&condition,std::shared_ptr<Statement>const&body):Statement(WHILE){
  this->_condition = condition;
  this->_body      = body;
}

While::~While(){

}

void While::setBody(std::shared_ptr<Statement>const&body){
  this->_body = body;
}

void While::setCondition(std::shared_ptr<Function>const&condition){
  this->_condition = condition;
}

std::shared_ptr<Function>const&While::getCondition()const{
  return this->_condition;
}

std::shared_ptr<Statement>const&While::getBody()const{
  return this->_body;
}

void While::operator()(){
  for(;;){
//    std::cerr<<"cyklim"<<std::endl;
    (*this->_condition)();
//    std::cerr<<"po condition"<<std::endl;
    if(!(bool)*(this->_condition->getOutput()))return;
//    std::cerr<<"pred body"<<std::endl;
    (*this->_body)();
//    std::cerr<<"po body"<<std::endl;
  }
}

If::If(
    std::shared_ptr<Function> const&condition,
    std::shared_ptr<Statement>const&trueBody ,
    std::shared_ptr<Statement>const&falseBody):Statement(IF){
  this->_condition = condition;
  this->_trueBody  = trueBody ;
  this->_falseBody = falseBody;
}

If::~If(){

}

void If::setCondition(std::shared_ptr<Function> const&condition){
  this->_condition = condition;
}

void If::setTrueBody (std::shared_ptr<Statement>const&trueBody ){
  this->_trueBody = trueBody;
}

void If::setFalseBody(std::shared_ptr<Statement>const&falseBody){
  this->_falseBody = falseBody;
}

std::shared_ptr<Function> const&If::getCondition()const{
  return this->_condition;
}

std::shared_ptr<Statement>const&If::getTrueBody()const{
  return this->_trueBody;
}

std::shared_ptr<Statement>const&If::getFalseBody()const{
  return this->_falseBody;
}

void If::operator()(){
  (*this->_condition)();
  if((bool)*(this->_condition->getOutput()))
    (*this->_trueBody)();
  else{
    if(this->_falseBody)(*this->_falseBody)();
  }
}


