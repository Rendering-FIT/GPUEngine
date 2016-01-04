#include<geCore/interpret.h>

using namespace ge::core;

Statement::Statement(Type type){
  this->_type = type;
}

Statement::~Statement(){
}

FunctionInput::FunctionInput(
    std::shared_ptr<Function>      fce        ,
    unsigned long long             updateTicks,
    bool                           changed    ,
    ge::core::TypeRegister::TypeID type       ){
  this->function    = fce        ;
  this->updateTicks = updateTicks;
  this->changed     = changed    ;
  this->type        = type       ;
}


Function::Function(unsigned n,std::string name):Statement(FUNCTION){
  for(unsigned i=0;i<n;++i)
    this->_inputs.push_back(FunctionInput());
  this->_defaultNames(n);
  this->_name = name;
}

Function::~Function(){

}

bool Function::bindInput(unsigned i,std::shared_ptr<Function>function){
  if(i>=(unsigned)(this->_inputs.size())){
    std::cerr<<"ERROR: "<<this->_name<<"::bindInput("<<i<<",";
    if(function==nullptr)std::cerr<<"nullptr";
    else std::cerr<<function->_name;
    std::cerr<<") - out of range"<<std::endl;
    return false;
  }
  if(
      function                       != nullptr                   &&
      function->getOutput()->getId() != this->_getInput(i).type   &&
      this->_getInput(i).type        != TypeRegister::UNREGISTERED){
    std::cerr<<"ERROR: "<<this->_name<<".input["<<this->getInputName(i)<<"] has different type - ";
    std::cerr<<function->getOutput()->getManager()->getTypeIdName(this->_getInput(i).type);
    std::cerr<<" != ";
    std::cerr<<function->getOutput()->getManager()->getTypeIdName(function->getOutput()->getId());
    std::cerr<<std::endl;
    return false;
  }
  this->_getInput(i).function = function;
  if(function)this->_getInput(i).updateTicks = function->_updateTicks - 1;
  this->_getInput(i).changed  = true;
  return true;
}

bool Function::bindOutput(std::shared_ptr<ge::core::Accessor>data){
  if(
      data                    != nullptr                   &&
      data->getId()           != this->_getOutput().type   &&
      this->_getOutput().type != TypeRegister::UNREGISTERED){
    std::cerr<<"ERROR: "<<this->_name<<".output has different type - ";
    std::cerr<<data->getManager()->getTypeIdName(this->_getOutput().type);
    std::cerr<<" != ";
    std::cerr<<data->getManager()->getTypeIdName(data->getId()    );
    std::cerr<<std::endl;
    return false;
  }
  this->_getOutput().data = data;
  return true;
}

bool Function::bindInput(std::string name,std::shared_ptr<Function>function){
  return this->bindInput(this->getInputIndex(name),function);
}

void Function::_setInput(unsigned i,ge::core::TypeRegister::TypeID type,std::string name){
  if(name=="")name=this->_genDefaultName(i);
  auto jj=this->_name2Input.find(name);
  if(jj!=this->_name2Input.end()&&jj->second!=i){
    std::cerr<<"ERROR: "<<this->_name<<"::setInput("<<i<<","<<type<<","<<name<<")";
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
  this->_inputs[i].type=type;
}

void Function::_setOutput(ge::core::TypeRegister::TypeID type,std::string name){
  if(name=="")name="output";
  this->_getOutput().name = name;
  this->_getOutput().type = type;
}

void Function::operator()(){
  this->_checkTicks++;
  this->_processInputs();
  if(this->_do())
    this->_updateTicks++;
}

void Function::_processInputs(){
  for(unsigned i=0;i<this->_getNofInputs();++i){
    if(!this->hasInput(i)||this->_getInput(i).function->_checkTicks>=this->_checkTicks){
      this->_getInput(i).changed = false;
      continue;
    }
    (*this->_getInput(i).function)();
    this->_getInput(i).function->_checkTicks = this->_checkTicks;
    this->_getInput(i).changed=
      this->_getInput(i).updateTicks<this->_getInput(i).function->_updateTicks;
    if(this->_getInput(i).changed)
      this->_getInput(i).updateTicks=this->_getInput(i).function->_updateTicks;
  }
}

bool Function::_do(){
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


