#include<geCore/CompositeResource.h>

using namespace ge::core;


CompositeResource::CompositeResource(
    std::shared_ptr<TypeRegister>const&         manager  ,
    TypeRegister::TypeID                        id       ,
    std::vector<std::shared_ptr<Resource>>const&accessors):Resource(manager,id){
  this->_nofElements = 0;
  switch(manager->getTypeIdType(id)){
    case TypeRegister::ARRAY:
      if(manager->getArraySize(id)!=accessors.size()){
        std::cerr<<"ERROR - CompositeResource::CompositeResource - number of components does not match array size - ";
        std::cerr<<manager->getArraySize(id)<<" != "<<accessors.size();
        std::cerr<<std::endl;
        return;
      }
      for(auto x:accessors){
        if(manager->getArrayInnerTypeId(id)!=x->getId()){
          std::cerr<<"ERROR - CompositeResource::CompositeResource - one of components differs from arrays inner type - ";
          std::cerr<<manager->getTypeIdName(manager->getArrayInnerTypeId(id))<<" != ";
          std::cerr<<manager->getTypeIdName(x->getId());
          std::cerr<<std::endl;
          return;
        }
      }
      break;
    case TypeRegister::STRUCT:
      if(manager->getNofStructElements(id)!=accessors.size()){
        std::cerr<<"ERROR - CompositeResource::CompositeResource() - number of components differs from structs number of components - ";
        std::cerr<<manager->getNofStructElements(id)<<" != "<<accessors.size();
        std::cerr<<std::endl;
        return;
      }
      for(std::vector<std::shared_ptr<Resource>>::size_type i=0;i<accessors.size();++i){
        if(manager->getStructElementTypeId(id,i)!=accessors[i]->getId()){
          std::cerr<<"ERROR - CompositeResource::CompositeResource() - one of components differs from structs element type - ";
          std::cerr<<manager->getTypeIdName(manager->getStructElementTypeId(id,i))<<" != ";
          std::cerr<<manager->getTypeIdName(accessors[i]->getId());
          std::cerr<<std::endl;
          return;
        }
      }
      break;
    default                  :
      std::cerr<<"ERROR - CompositeResource::CompositeResource() - cannot composite Resources into non composable type - ";
      std::cerr<<manager->getTypeIdName(id)<<std::endl;;
      return;
  }
  this->_components = accessors;
  for(auto x:accessors)
    this->_nofElements += x->getNofElements();
}

void*CompositeResource::getData()const{
  return this->_components[0]->getData();
}

void const*CompositeResource::getDataAddress()const{
  return this->_components[0]->getDataAddress();
}

std::shared_ptr<Resource> CompositeResource::operator[](TypeRegister::DescriptionIndex elem)const{
  TypeRegister::DescriptionElement offset=0;
  decltype(this->_components)::size_type i=0;
  while(elem>offset+this->_components[i]->getNofElements()){
    offset+=this->_components[i]->getNofElements();
    ++i;
  }
  return this->_components[i]->operator[](elem-offset);

}

TypeRegister::DescriptionElement CompositeResource::getNofElements()const{
  return this->_nofElements;
}

std::string CompositeResource::data2Str()const{
  std::stringstream ss;
  bool first;
  switch(this->_manager->getTypeIdType(this->_id)){
    case TypeRegister::ARRAY:
      ss<<"[";
      first=true;
      for(TypeRegister::DescriptionElement i=0;i<this->_manager->getArraySize(this->_id);++i){
        if(first)first=false;
        else ss<<",";
        ss<<((*this)[i])->data2Str();
      }
      ss<<"]";
      break;
    case TypeRegister::STRUCT:
      ss<<"{";
      first=true;
      for(TypeRegister::DescriptionElement e=0;e<this->_manager->getNofStructElements(this->_id);++e){
        if(first)first=false;
        else ss<<",";
        ss<<((*this)[e])->data2Str();
      }
      ss<<"}";
      break;
    default:
      break;
  }
  return ss.str();
}

