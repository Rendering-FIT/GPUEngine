#include<geAd/LibraryLoader/LibraryObjectLoader.h>

using namespace ge::ad;
using namespace ge::de;

void*ge::ad::ObjectLoader::getObject(std::string name){
  auto lib=this->load(name);
  void*(*objectFactory)();
  *(void**)(&objectFactory)=this->get(lib,"getObject");
  return objectFactory();
}

RuntimeClassInterface*ge::ad::ObjectLoader::getInterface(
    std::string name,
    std::shared_ptr<TypeRegister>&typeRegister){
  auto lib=this->load(name);
  RuntimeClassInterface*(*objectFactory)(std::shared_ptr<TypeRegister>&);
  *(void**)(&objectFactory)=this->get(lib,"getInterface");
  return objectFactory(typeRegister);
}

