#include<geCore/interpret.h>

using namespace ge::core;

Statement::Statement(Type type){
  this->_type = type;
}

Statement::~Statement(){
}

Function::Function(unsigned n):Statement(FUNCTION){
  for(unsigned i=0;i<n;++i){
    this->_inputs.push_back(nullptr);
    this->_inputsTicks.push_back(0);//this has to be less than this->_tickNumber
    this->_lazy.push_back(false);
  }
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

void Function::setInput(unsigned i,std::shared_ptr<Function>function,bool lazy){
  this->_inputs[i]=function;
  this->_lazy[i]=lazy;
  if(lazy)
    this->_inputsTicks[i]=function->getTick()-1;
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

void Function::beginOperator(){
  this->updateTick();
  for(unsigned i=0;i<this->_inputs.size();++i){
    if(!this->_lazy[i]){
      if(this->_inputs[i]->getTick()<this->getTick()){
        (*this->_inputs[i])();
        this->_inputs[i]->setTick(this->getTick());
      }
    }
  }
  /*
  for(auto x:this->_inputs){
    if(x->getTick()<this->getTick()){
      (*x)();
      x->setTick(this->getTick());
    }
  }*/
}

void Function::endOperator(){
  for(unsigned i=0;i<this->_inputs.size();++i)
    if(this->_lazy[i])
      this->_inputsTicks[i]=this->_inputs[i]->getTick();
}

bool Function::inputChanged(unsigned i)const{
  if(this->_lazy[i])
    return this->_inputsTicks[i]<this->_inputs[i]->getTick();
  return true;
}

/* jsme scitacka:
 * chci secist sve vstupy a dat je na vystup
 * musis zazadat sve vstupy aby se obnovily
 * vstupy se obnovi
 * reknou mi jestli maji novou hodnotu
 * pokud nemaji novou hodnotu, nemusis pocitat vystup a dale budu rikat ze nemam novou hodnotu
 * nechci vypocitavat vstup pokud jeho hodna je jiz aktualni kvuli vypoctu jineho vstupu
 *
 * pokud je inputA.tick < this.tick je input stary a je jej potreba vypocitat
 * pokud je inputA.tick == this.inputs[inputA].tick input se nezmenil a neni potreba jej vyvolavat
 * pokud je inputA.tick > this.tick je input novejsi a nepotrebuji jej vyhodnotit?
 * pokud je inputA.tick > this.inputs[inputA].tick, input je novejsi musis se podle tohoto zaridit a pote si poznaci this.inputs[inputA].tick = inputA.tick
 *
 * jsou tu asi dva pristupy:
 * 1. vynucovat vyhodnoceni vstupu pokud nejsou alespon tak stare jako ja
 * 2. nevynucovat vyhodnoceni vstupu, pouze se zaridi podle toho jetli je novejsi nez jak si jej pamatuji
 *
 * f0 = a+b
 * f1 = f0 + c
 * f2 = f0 + d
 * f3 = f1 + f2
 *
 * f3() => f1(), f2()
 * f3() => f0() + d, f2
 *
 *
 *
 *
 *
 */


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


