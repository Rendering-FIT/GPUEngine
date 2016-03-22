#include<geUtil/LibraryLoader/RuntimeClassInterface.h>
#include<geCore/Accessor.h>
#include<sstream>

using namespace ge::util;

bool RuntimeClassInterface::_functionArgsMatch(std::vector<ge::core::Accessor>&args,unsigned fce)const{
  if(args.size()!=this->getNofFunctionArguments(fce)+int(this->getFunctionReturnTypeID(fce)!=0))
    return false;
  if(this->getFunctionReturnTypeID(fce)!=0){
    if(args[0].getId()!=this->getFunctionReturnTypeID(fce))
      return false;
    for(unsigned i=1;i<args.size();++i)
      if(args[i].getId()!=this->getFunctionArgumentTypeID(fce,i-1))
        return false;
  }else{
    for(unsigned i=0;i<args.size();++i)
      if(args[i].getId()!=this->getFunctionArgumentTypeID(fce,i))
        return false;
  }
  return true;
}

bool RuntimeClassInterface::_constructorArgsMatch(std::vector<ge::core::Accessor>&args,unsigned id)const{
  if(args.size()!=this->getNofConstructorArguments(id))
    return false;
  for(unsigned i=0;i<args.size();++i)
    if(args[i].getId()!=this->getConstructorArgumentTypeID(id,i))
      return false;
  return true;
}

RuntimeClassInterface::RuntimeClassInterface(
    std::shared_ptr<ge::core::TypeRegister>&typeRegister,
    ClassMetaData const&classMetaData){
  this->_typeRegister = typeRegister;
  this->_classMetaData = new RuntimeClassMetaData(typeRegister,classMetaData);
}

std::string RuntimeClassInterface::dir()const{
  std::stringstream ss;
  for(unsigned f=0;f<this->getNofFunctions();++f){
    ss<<this->_typeRegister->getTypeIdName(this->getFunctionReturnTypeID(f))<<" ";
    ss<<this->getClassName()<<"::"<<this->getFunctionName(f)<<"(";
    for(unsigned a=0;a<this->getNofFunctionArguments(f);++a){
      if(a!=0)ss<<",";
      ss<<this->_typeRegister->getTypeIdName(this->getFunctionArgumentTypeID(f,a))<<" ";
      ss<<this->getFunctionArgumentName(f,a);
    }
    ss<<")"<<std::endl;
  }
  for(unsigned c=0;c<this->getNofConstructors();++c){
    ss<<this->getClassName()<<"(";
    for(unsigned a=0;a<this->getNofConstructorArguments(c);++a){
      if(a!=0)ss<<",";
      ss<<this->_typeRegister->getTypeIdName(this->getConstructorArgumentTypeID(c,a))<<" ";
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

std::vector<ge::util::RuntimeFceMetaData>::size_type RuntimeClassInterface::getNofFunctions()const{
  return this->_classMetaData->getNofFces();
}

std::string RuntimeClassInterface::getFunctionName(unsigned fce)const{
  return this->_classMetaData->getFce(fce).getName();
}

ge::core::TypeRegister::TypeID RuntimeClassInterface::getFunctionReturnTypeID(unsigned fce)const{
  return this->_classMetaData->getFce(fce).getReturnType();
}

std::vector<ge::util::RuntimeArgMetaData>::size_type RuntimeClassInterface::getNofFunctionArguments(unsigned fce)const{
  return this->_classMetaData->getFce(fce).getNofArgs();
}

ge::core::TypeRegister::TypeID RuntimeClassInterface::getFunctionArgumentTypeID(unsigned fce,unsigned arg)const{
  return this->_classMetaData->getFce(fce).getArg(arg).getType();
}

std::string RuntimeClassInterface::getFunctionArgumentName(unsigned fce,unsigned arg)const{
  return this->_classMetaData->getFce(fce).getArg(arg).getName();
}

void RuntimeClassInterface::call(void*,std::string,std::vector<ge::core::Accessor>&){
}

std::vector<ge::util::RuntimeConstructorMetaData>::size_type RuntimeClassInterface::getNofConstructors()const{
  return this->_classMetaData->getNofConstructors();
}

std::vector<ge::util::RuntimeArgMetaData>::size_type RuntimeClassInterface::getNofConstructorArguments(unsigned id)const{
  return this->_classMetaData->getConstructor(id).getNofArgs();
}

ge::core::TypeRegister::TypeID RuntimeClassInterface::getConstructorArgumentTypeID(unsigned id,unsigned arg)const{
  return this->_classMetaData->getConstructor(id).getArg(arg).getType();
}

std::string RuntimeClassInterface::getConstructorArgumentName(unsigned id,unsigned arg)const{
  return this->_classMetaData->getConstructor(id).getArg(arg).getName();
}

void*RuntimeClassInterface::construct(std::vector<ge::core::Accessor>&)const{
  return nullptr;
}

void RuntimeClassInterface::destroy(void*)const{
}
