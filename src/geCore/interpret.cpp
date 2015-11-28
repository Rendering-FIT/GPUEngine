#include<geCore/interpret.h>

using namespace ge::core;

Statement::Statement(Type type){
  this->_type = type;
}

Statement::~Statement(){
}

FunctionInput::FunctionInput(std::shared_ptr<Function>const&function,bool lazy,ge::core::TypeRegister::TypeID type){
  this->_function = function;
  this->_lazy     = lazy    ;
  this->_type     = type    ;
  this->_ticks    = 0       ;
}

std::shared_ptr<Function>const&FunctionInput::getFunction()const{
  return this->_function;
}

bool FunctionInput::getLazy()const{
  return this->_lazy;
}

ge::core::TypeRegister::TypeID FunctionInput::getType()const{
  return this->_type;
}

unsigned long long FunctionInput::getTicks()const{
  return this->_ticks;
}

void FunctionInput::setFunction(std::shared_ptr<Function>const&function){
  this->_function = function;
}

void FunctionInput::setLazy(bool lazy){
  this->_lazy = lazy;
}

void FunctionInput::setType(ge::core::TypeRegister::TypeID type){
  this->_type = type;
}

void FunctionInput::setTicks(unsigned long long ticks){
  this->_ticks = ticks;
}

void FunctionInput::updateTicks(){
  this->_ticks++;
}

Function::Function(unsigned n):Statement(FUNCTION){
  for(unsigned i=0;i<n;++i)
    this->_inputs.push_back(FunctionInput(nullptr,false,0));
  this->_defaultNames(n);
}

Function::~Function(){

}

unsigned long long Function::getTicks()const{
  return this->_tickNumber;
}

void Function::setTick(unsigned long long tick){
  this->_tickNumber = tick;
}

void Function::updateTick(){
  this->_tickNumber++;
}

void Function::bindInput(unsigned i,std::shared_ptr<Function>function,bool lazy){
  if(function!=nullptr&&function->getOutput()->getId()!=(*this)[i].getType()){
    std::cerr<<"ERROR: input: "<<i<<" has diferrent type - ";
    std::cerr<<function->getOutput()->getManager()->getTypeIdName((*this)[i].getType());
    std::cerr<<" != ";
    std::cerr<<function->getOutput()->getManager()->getTypeIdName(function->getOutput()->getId());
    std::cerr<<std::endl;
    return;
  }
  (*this)[i].setFunction(function);
  (*this)[i].setLazy(lazy);
  if(lazy)(*this)[i].setTicks(function->getTicks()-1);
}

void Function::bindOutput(std::shared_ptr<ge::core::Accessor>data){
  this->_output = data;
}

std::shared_ptr<ge::core::Accessor>const&Function::getOutput()const{
  return this->_output;
}

void Function::bindInput(std::string name,std::shared_ptr<Function>function,bool lazy){
  this->bindInput(this->_name2Input[name],function,lazy);
}

void Function::setInput(unsigned i,ge::core::TypeRegister::TypeID type,std::string name){
  if(name=="")name=this->_genDefaultName(i);
  auto jj=this->_name2Input.find(name);
  if(jj!=this->_name2Input.end()&&jj->second!=i){
    std::cerr<<"ERROR: Function::setInput("<<i<<","<<type<<","<<name<<")";
    std::cerr<<" - name "<<name<<" is already used for input number: ";
    std::cerr<<jj->second<<std::endl;
    return;
  }
  auto ii=this->_input2Name.find(i);
  if(ii!=this->_input2Name.end()){
    if(this->_name2Input.find(ii->second)!=this->_name2Input.end())
      this->_name2Input.erase(ii->second);
    this->_input2Name.erase(i);
  }
  this->_name2Input[name] = i   ;
  this->_input2Name[i   ] = name;
  this->_inputs[i].setType(type);
}

void Function::setOutput(ge::core::TypeRegister::TypeID type){
  this->_outputType = type;
}

bool Function::hasInput(unsigned i)const{
  return this->_inputs[i].getFunction()!=nullptr;
}

bool Function::hasInput(std::string name)const{
  return this->_name2Input.find(name)!=this->_name2Input.end();
}

bool Function::hasOutput()const{
  return this->_output!=nullptr;
}


void Function::setOutputType(ge::core::TypeRegister::TypeID type){
  this->_outputType = type;
}

ge::core::TypeRegister::TypeID Function::getOutputType()const{
  return this->_outputType;
}

FunctionInput&Function::operator[](unsigned i){
  return this->_inputs[i];
}

FunctionInput&Function::operator[](std::string input){
  return this->_inputs[this->_name2Input[input]];
}

void Function::operator()(){
}

void Function::beginOperator(){
  this->updateTick();
  for(unsigned i=0;i<this->_inputs.size();++i){
    if(!this->hasInput(i))continue;
    if(!(*this)[i].getLazy()){
      if((*this)[i].getTicks()<this->getTicks()){
        (*(*this)[i].getFunction())();
        (*this)[i].setTicks(this->getTicks());
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
  for(unsigned i=0;i<this->_inputs.size();++i){
    if(!this->hasInput(i))continue;
    if((*this)[i].getLazy())
      (*this)[i].setTicks((*this)[i].getFunction()->getTicks());
  }
}

bool Function::inputChanged(unsigned i)const{
  if(!this->hasInput(i))return false;
  if(this->_inputs[i].getLazy())
    return this->_inputs[i].getTicks()<this->_inputs[i].getFunction()->getTicks();
  return true;
}

std::string Function::_genDefaultName(unsigned i)const{
  std::stringstream ss;
  ss<<"input"<<i;
  return ss.str();
}

void Function::_defaultNames(unsigned n){
  for(unsigned i=0;i<n;++i){
    std::string name=this->_genDefaultName(i);
    this->_name2Input[name]=i;
    this->_input2Name[i]=name;
  }
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


