#include<geAd/LibraryLoader/RuntimeClassMetaData.h>

using namespace ge::ad;
using namespace ge::de;

RuntimeArgMetaData::RuntimeArgMetaData(
    std::shared_ptr<TypeRegister>&typeRegister,
    ArgMetaData const&argMetaData){
  this->_name = argMetaData.name;
  this->_type = typeRegister->addCompositeType("",argMetaData.description);
}

TypeId RuntimeArgMetaData::getType()const{
  return this->_type;
}

std::string RuntimeArgMetaData::getName()const{
  return this->_name;
}


RuntimeFceMetaData::RuntimeFceMetaData(
    std::shared_ptr<TypeRegister>&typeRegister,
    FceMetaData const&fceMetaData){
  this->_name = fceMetaData.name;
  this->_returnType = typeRegister->addCompositeType("",fceMetaData.returnType);
  for(unsigned a=0;a<fceMetaData.args.size();++a)
    this->_args.push_back(RuntimeArgMetaData(typeRegister,fceMetaData.args[a]));
}

TypeId RuntimeFceMetaData::getReturnType()const{
  return this->_returnType;
}

std::string RuntimeFceMetaData::getName()const{
  return this->_name;
}

decltype(RuntimeFceMetaData::_args)::size_type RuntimeFceMetaData::getNofArgs()const{
  return this->_args.size();
}

RuntimeArgMetaData const&RuntimeFceMetaData::getArg(unsigned i)const{
  return this->_args[i];
}

RuntimeConstructorMetaData::RuntimeConstructorMetaData(
    std::shared_ptr<TypeRegister>&typeRegister,
    ConstructorMetaData const&constructorMetaData){
  for(unsigned a=0;a<constructorMetaData.args.size();++a)
    this->_args.push_back(RuntimeArgMetaData(typeRegister,constructorMetaData.args[a]));
}

decltype(RuntimeConstructorMetaData::_args)::size_type RuntimeConstructorMetaData::getNofArgs()const{
  return this->_args.size();
}

RuntimeArgMetaData const&RuntimeConstructorMetaData::getArg(unsigned i)const{
  return this->_args[i];
}


RuntimeClassMetaData::RuntimeClassMetaData(
    std::shared_ptr<TypeRegister>&typeRegister,
    ClassMetaData const&classMetaData){
  this->_name = classMetaData.name;
  for(unsigned f=0;f<classMetaData.fces.size();++f)
    this->_fces.push_back(RuntimeFceMetaData(typeRegister,classMetaData.fces[f]));
  for(unsigned c=0;c<classMetaData.constructors.size();++c)
    this->_constructors.push_back(RuntimeConstructorMetaData(typeRegister,classMetaData.constructors[c]));
}

std::string RuntimeClassMetaData::getName()const{
  return this->_name;
}

decltype(RuntimeClassMetaData::_fces)::size_type RuntimeClassMetaData::getNofFces()const{
  return this->_fces.size();
}

RuntimeFceMetaData const&RuntimeClassMetaData::getFce(unsigned i)const{
  return this->_fces[i];
}

decltype(RuntimeClassMetaData::_constructors)::size_type RuntimeClassMetaData::getNofConstructors()const{
  return this->_constructors.size();
}

RuntimeConstructorMetaData const&RuntimeClassMetaData::getConstructor(unsigned i)const{
  return this->_constructors[i];
}


