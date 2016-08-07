#include<geDE/Kernel.h>
#include<geDE/Function.h>
#include<geDE/StdFunctions.h>
#include<geDE/RegisterBasicTypes.h>

using namespace ge::de;

Kernel::Kernel(){
  assert(this!=nullptr);
  this->typeRegister     = std::make_shared<TypeRegister>();
  this->nameRegister     = std::make_shared<NameRegister>();
  this->functionRegister = std::make_shared<FunctionRegister>(this->typeRegister,this->nameRegister);
  this->variableRegister = std::make_shared<VariableRegister>("*");
  registerBasicTypes(this->typeRegister);
  registerStdFunctions(this->functionRegister);
}

Kernel::~Kernel(){
  assert(this!=nullptr);
  this->variableRegister = nullptr;
  this->functionRegister = nullptr;
  this->nameRegister = nullptr;
  this->typeRegister = nullptr;
}

bool Kernel::addEmptyVariable(std::string const&name,std::string const&type){
  assert(this!=nullptr);
  assert(this->typeRegister!=nullptr);
  assert(this->functionRegister!=nullptr);
  auto id = this->typeRegister->getTypeId(type);
  if(id == TypeRegister::UNREGISTERED){
    return false;
  }
  if(this->variableRegister->hasVariable(name)){
    return false;
  }
  auto sac = this->typeRegister->sharedResource(id);
  assert(this->variableRegister!=nullptr);
  this->variableRegister->insert(name,sac);
  return true;
}

void Kernel::removeVariable(std::string const&name){
  assert(this!=nullptr);
  this->variableRegister->erase(name);
}

void Kernel::addCommand(std::shared_ptr<Statement>const&command){
  this->commands.push_back(command);
}

void Kernel::run(){
  while(this->currentCommand<this->commands.size()){
    (*this->commands.at(this->currentCommand))();
    this->currentCommand++;
  }
}

void Kernel::restart(){
  this->currentCommand = 0;
}

std::shared_ptr<Resource>Kernel::createResource(std::string const&name){
  return this->typeRegister->sharedResource(name);
}

std::shared_ptr<Function>Kernel::createFunction2(
    std::string                           const&name  ,
    std::vector<std::shared_ptr<Resource>>const&inputs,
    std::shared_ptr<Resource>             const&output){
  assert(this!=nullptr);
  auto result = this->functionRegister->sharedFunction(name);
  this->bindInput(result,inputs);
  this->bindOutput(result,output);
  return result;
}

std::shared_ptr<Function>Kernel::createFunction2(
    std::string                           const&name        ,
    std::vector<std::shared_ptr<Resource>>const&inputs      ,
    std::string                           const&variableName){
  assert(this!=nullptr);
  if(!this->variableRegister->hasVariable(variableName)){
    ge::core::printError("Kernel::createFunction","there is no such variable",name,variableName);
    return nullptr;
  }
  auto result = this->functionRegister->sharedFunction(name);
  this->bindInput(result,inputs);
  auto var = this->variableRegister->getVariable(variableName);
  this->bindOutput(result,var);
  return result;
}

std::shared_ptr<Function>Kernel::createFunction2(
    std::string                           const&name  ,
    std::vector<std::shared_ptr<Resource>>const&inputs){
  assert(this!=nullptr);
  auto result = this->functionRegister->sharedFunction(name);
  this->bindInput(result,inputs);
  auto type = this->functionRegister->getOutputType(this->functionRegister->getFunctionId(name));
  this->bindOutput(result,this->typeRegister->sharedResource(type));
  return result;
}

std::shared_ptr<Function>Kernel::createFunction(
    std::string             const&name        ,
    std::vector<std::string>const&inputNames  ,
    std::string             const&variableName){
  assert(this!=nullptr);
  std::vector<std::shared_ptr<Resource>>inputs;
  for(auto const&x:inputNames)
    inputs.push_back(this->variableRegister->getVariable(x));
  return this->createFunction2(name,inputs,variableName);
}

std::shared_ptr<Function>Kernel::createFunction(
    std::string              const&name      ,
    std::vector<std::string> const&inputNames,
    std::shared_ptr<Resource>const&output    ){
  assert(this!=nullptr);
  std::vector<std::shared_ptr<Resource>>inputs;
  for(auto const&x:inputNames)
    inputs.push_back(this->variableRegister->getVariable(x));
  return this->createFunction2(name,inputs,output);
}

std::shared_ptr<Function>Kernel::createFunction(
    std::string              const&name      ,
    std::vector<std::string> const&inputNames){
  assert(this!=nullptr);
  std::vector<std::shared_ptr<Resource>>inputs;
  for(auto const&x:inputNames)
    inputs.push_back(this->variableRegister->getVariable(x));
  return this->createFunction2(name,inputs);
}


std::shared_ptr<Resource>const&Kernel::variable(std::string const&name)const{
  assert(this!=nullptr);
  return this->variableRegister->getVariable(name);
}

void Kernel::bindInput(
    std::shared_ptr<Function>const&fce,
    std::vector<std::shared_ptr<Resource>>const&inputs){
  assert(this!=nullptr);
  for(size_t i=0;i<inputs.size();++i)
    fce->bindInput(this->functionRegister,i,inputs[i]);
}

void Kernel::bindOutput(
    std::shared_ptr<Function>const&fce,
    std::shared_ptr<Resource>const&output){
  assert(this!=nullptr);
  fce->bindOutput(this->functionRegister,output);
}

void Kernel::bindOutputAsVariable(
    std::shared_ptr<Function>const&fce,
    std::shared_ptr<Resource>const&var){
  assert(this!=nullptr);
  fce->bindOutputAsVariable(this->functionRegister,var);
}

TypeId Kernel::addAtomicType(
    std::string const&name       ,
    size_t      const&size       ,
    CDPtr       const&constructor,
    CDPtr       const&destructor ){
  return this->typeRegister->addAtomicType(name,size,constructor,destructor);
}

TypeId Kernel::addCompositeType(
    std::string           const&name       ,
    TypeDescriptionVector const&description){
  return this->typeRegister->addCompositeType(name,description);
}

TypeId Kernel::addStructType(
    std::string                     const&name,
    TypeDescriptionVector const&typeids){
  TypeDescriptionVector d;
  d.push_back(TypeRegister::STRUCT);
  d.push_back(typeids.size());
  d.insert(d.end(),typeids.begin(),typeids.end());
  return this->addCompositeType(name,d);
}

TypeId Kernel::addStructType(
    std::string             const&name     ,
    std::vector<std::string>const&typeNames){
  TypeDescriptionVector d;
  d.push_back(TypeRegister::STRUCT);
  d.push_back(typeNames.size());
  for(auto const&x:typeNames)
    d.push_back(this->typeRegister->getTypeId(x));
  return this->addCompositeType(name,d);
}

TypeId Kernel::addArrayType(
    std::string          const&name     ,
    size_t                     size     ,
    TypeId       innerType){
  TypeDescriptionVector d;
  d.push_back(TypeRegister::ARRAY);
  d.push_back(size);
  d.push_back(innerType);
  return this->addCompositeType(name,d);
}

TypeId Kernel::addArrayType(
    std::string const&name     ,
    size_t            size     ,
    std::string const&innerType){
  TypeDescriptionVector d;
  d.push_back(TypeRegister::ARRAY);
  d.push_back(size);
  d.push_back(this->typeRegister->getTypeId(innerType));
  return this->addCompositeType(name,d);
}



/*
   std::shared_ptr<FunctionNodeFactory>Kernel::createFunctionNodeFactory(
   std::string name,
   std::string functionName,
   std::vector<std::shared_ptr<StatementFactory>>const&inputFunctionFactories,
   std::vector<std::string>const&inputResourceFactoryNames){
   std::vector<std::shared_ptr<ResourceFactory>>inputResourceFactories;
   for(auto const&x:inputResourceFactoryNames){
   if(x=="")
   inputResourceFactories.push_back(nullptr);
   else
   inputResourceFactories.push_back(this->createResourceFactory(x));
   }
   return this->createFunctionNodeFactory(name,functionName,inputFunctionFactories,inputResourceFactories);
   }
   */

std::shared_ptr<FunctionNodeFactory>Kernel::createFunctionNodeFactory(
    std::string name,
    std::string functionName,
    std::vector<std::shared_ptr<StatementFactory>>const&inputFunctionFactories){//,
  //std::vector<std::shared_ptr<ResourceFactory>>const&inputResourceFactories){
  auto result = std::make_shared<FunctionNodeFactory>(name);
  result->setFactory(this->functionRegister->sharedFactory(functionName));
  auto id = this->functionRegister->getFunctionId(functionName);
  size_t nof = this->functionRegister->getNofInputs(id);
  for(size_t i =0;i<nof;++i){
    if(i<inputFunctionFactories.size()){
      result->addInputFactory(inputFunctionFactories.at(i));
      result->addResourceFactory(std::make_shared<ResourceFactory>(this->functionRegister->getInputType(id,i)));
    }else{
      result->addInputFactory(nullptr);
      result->addResourceFactory(nullptr);
    }
  }
  return result;

}

std::shared_ptr<ResourceFactory>Kernel::createResourceFactory(
    std::string name){
  return std::make_shared<ResourceFactory>(this->typeRegister->getTypeId(name));
}

FunctionId Kernel::addCompositeFunction(
    std::vector<std::string>const&names,
    std::shared_ptr<CompositeFunctionFactory>const&factory){
  TypeDescriptionVector dv;
  dv.push_back(TypeRegister::FCE);
  dv.push_back(factory->getOutputType(this->functionRegister));
  size_t n=factory->getNofInputs(this->functionRegister);
  dv.push_back(n);
  for(size_t i=0;i<n;++i)
    dv.push_back(factory->getInputType(this->functionRegister,i));
  auto ret = this->functionRegister->addFunction(this->typeRegister->addCompositeType("",dv),factory->getName(),factory);
  if(names.size()>0)
    this->nameRegister->setFceOutputName(ret,names[0]);
  for(size_t i=1;i<names.size();++i)
    this->nameRegister->setFceInputName(ret,i-1,names[i]);
  return ret;
}


std::shared_ptr<CompositeFunctionFactory>Kernel::createCompositeFunctionFactory(
    std::string const&name,
    std::shared_ptr<FunctionNodeFactory>const&root,
    std::vector<std::vector<std::shared_ptr<FunctionNodeFactory>>>const&inputs,
    std::vector<std::vector<size_t>>const&inputIndices){
  if(inputs.size()!=inputIndices.size()){
    ge::core::printError("Kernel::createCompositeFunctionFactory","invalid inputs");
    return nullptr;
  }
  for(size_t i=0;i<inputs.size();++i){
    if(inputs.at(i).size()!=inputIndices.at(i).size()){
      ge::core::printError("Kernel::createCompositeFunctionFactory","invalid inputs");
      return nullptr;
    }
  }
  auto fac = std::make_shared<CompositeFunctionFactory>(name);
  fac->setFactory(root);
  std::vector<std::vector<CompositeFunctionFactory::FactoryInput>>in;
  for(size_t i=0;i<inputs.size();++i){
    in.push_back(std::vector<CompositeFunctionFactory::FactoryInput>());
    for(size_t j=0;j<inputs.at(i).size();++j)
      in[i].push_back(CompositeFunctionFactory::FactoryInput(inputs.at(i).at(j),inputIndices.at(i).at(j)));
  }
  fac->setInputFactories(in);
  return fac;
}

