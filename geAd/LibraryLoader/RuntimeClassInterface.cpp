#include<geAd/LibraryLoader/RuntimeClassInterface.h>
#include<geDE/Resource.h>
#include<sstream>

using namespace ge::ad;
using namespace ge::de;

bool RuntimeClassInterface::_functionArgsMatch(std::vector<Resource>&args,unsigned fce)const{
  if(args.size()!=this->getNofFunctionArguments(fce)+int(this->getFunctionReturnTypeId(fce)!=0))
    return false;
  if(this->getFunctionReturnTypeId(fce)!=0){
    if(args[0].getId()!=this->getFunctionReturnTypeId(fce))
      return false;
    for(unsigned i=1;i<args.size();++i)
      if(args[i].getId()!=this->getFunctionArgumentTypeId(fce,i-1))
        return false;
  }else{
    for(unsigned i=0;i<args.size();++i)
      if(args[i].getId()!=this->getFunctionArgumentTypeId(fce,i))
        return false;
  }
  return true;
}

bool RuntimeClassInterface::_constructorArgsMatch(std::vector<Resource>&args,unsigned id)const{
  if(args.size()!=this->getNofConstructorArguments(id))
    return false;
  for(unsigned i=0;i<args.size();++i)
    if(args[i].getId()!=this->getConstructorArgumentTypeId(id,i))
      return false;
  return true;
}

RuntimeClassInterface::RuntimeClassInterface(
    std::shared_ptr<TypeRegister>&typeRegister,
    ClassMetaData const&classMetaData){
  this->_typeRegister = typeRegister;
  this->_classMetaData = new RuntimeClassMetaData(typeRegister,classMetaData);
}

std::string RuntimeClassInterface::dir()const{
  std::stringstream ss;
  for(unsigned f=0;f<this->getNofFunctions();++f){
    ss<<this->_typeRegister->getTypeIdName(this->getFunctionReturnTypeId(f))<<" ";
    ss<<this->getClassName()<<"::"<<this->getFunctionName(f)<<"(";
    for(unsigned a=0;a<this->getNofFunctionArguments(f);++a){
      if(a!=0)ss<<",";
      ss<<this->_typeRegister->getTypeIdName(this->getFunctionArgumentTypeId(f,a))<<" ";
      ss<<this->getFunctionArgumentName(f,a);
    }
    ss<<")"<<std::endl;
  }
  for(unsigned c=0;c<this->getNofConstructors();++c){
    ss<<this->getClassName()<<"(";
    for(unsigned a=0;a<this->getNofConstructorArguments(c);++a){
      if(a!=0)ss<<",";
      ss<<this->_typeRegister->getTypeIdName(this->getConstructorArgumentTypeId(c,a))<<" ";
      ss<<this->getConstructorArgumentName(c,a);
    }
    ss<<")"<<std::endl;
  }
  return ss.str();
}

RuntimeClassInterface::~RuntimeClassInterface(){
  delete this->_classMetaData;
}

std::string RuntimeClassInterface::getClassName()const{
  return this->_classMetaData->getName();
}

std::vector<ge::ad::RuntimeFceMetaData>::size_type RuntimeClassInterface::getNofFunctions()const{
  return this->_classMetaData->getNofFces();
}

std::string RuntimeClassInterface::getFunctionName(unsigned fce)const{
  return this->_classMetaData->getFce(fce).getName();
}

TypeId RuntimeClassInterface::getFunctionReturnTypeId(unsigned fce)const{
  return this->_classMetaData->getFce(fce).getReturnType();
}

std::vector<ge::ad::RuntimeArgMetaData>::size_type RuntimeClassInterface::getNofFunctionArguments(unsigned fce)const{
  return this->_classMetaData->getFce(fce).getNofArgs();
}

TypeId RuntimeClassInterface::getFunctionArgumentTypeId(unsigned fce,unsigned arg)const{
  return this->_classMetaData->getFce(fce).getArg(arg).getType();
}

std::string RuntimeClassInterface::getFunctionArgumentName(unsigned fce,unsigned arg)const{
  return this->_classMetaData->getFce(fce).getArg(arg).getName();
}

void RuntimeClassInterface::call(void*,std::string,std::vector<Resource>&){
}

std::vector<ge::ad::RuntimeConstructorMetaData>::size_type RuntimeClassInterface::getNofConstructors()const{
  return this->_classMetaData->getNofConstructors();
}

std::vector<ge::ad::RuntimeArgMetaData>::size_type RuntimeClassInterface::getNofConstructorArguments(unsigned id)const{
  return this->_classMetaData->getConstructor(id).getNofArgs();
}

TypeId RuntimeClassInterface::getConstructorArgumentTypeId(unsigned id,unsigned arg)const{
  return this->_classMetaData->getConstructor(id).getArg(arg).getType();
}

std::string RuntimeClassInterface::getConstructorArgumentName(unsigned id,unsigned arg)const{
  return this->_classMetaData->getConstructor(id).getArg(arg).getName();
}

void*RuntimeClassInterface::construct(std::vector<Resource>&)const{
  return nullptr;
}

void RuntimeClassInterface::destroy(void*)const{
}
