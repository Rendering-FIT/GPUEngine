#include<geCore/function.h>
#include<geCore/Accessor.h>

using namespace ge::core;

FunctionInput::FunctionInput(
    std::shared_ptr<Function>fce        ,
    unsigned long long       updateTicks,
    bool                     changed    ){//,
//    TypeRegister::TypeID     type       ){
  this->function    = fce        ;
  this->updateTicks = updateTicks;
  this->changed     = changed    ;
//  this->type        = type       ;
}



//Function::Function(unsigned n,std::string name):Statement(FUNCTION){
//  for(unsigned i=0;i<n;++i)
//    this->_inputs.push_back(FunctionInput());
//  this->_defaultNames(n);
//  this->_name = name;
//}

Function::Function(
    std::shared_ptr<TypeRegister>const&tr,
    TypeRegister::TypeID type,
    std::string name):Statement(FUNCTION){
  this->_typeRegister = tr;
  this->_fceType = type;
  auto nofInputs = this->_typeRegister->getNofFceArgs(this->_fceType);
  for(decltype(nofInputs)i=0;i<nofInputs;++i)
    this->_inputs.push_back(FunctionInput());
  this->_defaultNames((unsigned)nofInputs);
  this->_name = name;
}

Function::Function(
    std::shared_ptr<TypeRegister>const&tr,
    TypeRegister::DescriptionList const&typeDescription,
    std::string name):Function(tr,tr->addType("",typeDescription),name){
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
      function->getOutput()->getId() != this->getInputType(i)     &&
      this->getInputType(i)          != TypeRegister::UNREGISTERED){
    std::cerr<<"ERROR: "<<this->_name<<".input["<<this->getInputName(i)<<"] has different type - ";
    std::cerr<<function->getOutput()->getManager()->getTypeIdName(this->getInputType(i));
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

bool Function::bindOutput(std::shared_ptr<Accessor>data){
  if(
      data                    != nullptr                   &&
      data->getId()           != this->getOutputType()     &&
      this->getOutputType()   != TypeRegister::UNREGISTERED){
    std::cerr<<"ERROR: "<<this->_name<<".output has different type - ";
    std::cerr<<data->getManager()->getTypeIdName(this->getOutputType());
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

void Function::_setInput(unsigned i,//TypeRegister::TypeID type,
    std::string name){
  if(name=="")name=this->_genDefaultName(i);
  auto jj=this->_name2Input.find(name);
  if(jj!=this->_name2Input.end()&&jj->second!=i){
    std::cerr<<"ERROR: "<<this->_name<<"::setInput("<<i<<","//<<type<<","
      <<name<<")";
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
  //this->_inputs[i].type=type;
}

void Function::_setOutput(//TypeRegister::TypeID type,
    std::string name){
  if(name=="")name="output";
  this->_getOutput().name = name;
  //this->_getOutput().type = type;
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

FunctionFactory::~FunctionFactory(){}
