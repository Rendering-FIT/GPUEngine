#include<geUtil/LibraryLoader/LibraryObjectLoader.h>

using namespace ge::util;

void*ge::util::ObjectLoader::getObject(std::string name){
  unsigned lib=this->load(name);
  void*(*objectFactory)();
  *(void**)(&objectFactory)=this->get(lib,"getObject");
  return objectFactory();
}

RuntimeClassInterface*ge::util::ObjectLoader::getInterface(
    std::string name,
    std::shared_ptr<ge::core::TypeRegister>&typeRegister){
  unsigned lib=this->load(name);
  RuntimeClassInterface*(*objectFactory)(std::shared_ptr<ge::core::TypeRegister>&);
  *(void**)(&objectFactory)=this->get(lib,"getInterface");
  return objectFactory(typeRegister);
}

