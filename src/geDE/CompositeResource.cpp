#include<geDE/CompositeResource.h>
#include<geCore/ErrorPrinter.h>

using namespace ge::de;


CompositeResource::CompositeResource(
    std::shared_ptr<TypeRegister>const&         manager  ,
    TypeId                                      id       ,
    std::vector<std::shared_ptr<Resource>>const&accessors):Resource(manager,id){
  PRINT_CALL_STACK(manager,id,accessors);
  assert(this!=nullptr);
  assert(manager!=nullptr);
  this->_nofElements = 0;
  switch(manager->getTypeIdType(id)){
    case TypeRegister::ARRAY:
      if(manager->getArraySize(id)!=accessors.size()){
        ge::core::printError(GE_CORE_FCENAME,
            "number of components does not match array size - "+
            ge::core::value2str(std::cerr<<manager->getArraySize(id))+" != "+ge::core::value2str(accessors.size()),manager,id,accessors);
        return;
      }
      for(auto x:accessors){
        if(manager->getArrayElementTypeId(id)!=x->getId()){
          ge::core::printError(GE_CORE_FCENAME,
              std::string("one of components differs from arrays inner type - ")+
              manager->getTypeIdName(manager->getArrayElementTypeId(id))+" != "+manager->getTypeIdName(x->getId()),manager,id,accessors);
          return;
        }
      }
      break;
    case TypeRegister::STRUCT:
      if(manager->getNofStructElements(id)!=accessors.size()){
        ge::core::printError(GE_CORE_FCENAME,"number of components differs from structs number of components - "+
        ge::core::value2str(manager->getNofStructElements(id))+" != "+ge::core::value2str(accessors.size()),manager,id,accessors);
        return;
      }
      for(std::vector<std::shared_ptr<Resource>>::size_type i=0;i<accessors.size();++i){
        if(manager->getStructElementTypeId(id,i)!=accessors[i]->getId()){
          ge::core::printError(GE_CORE_FCENAME,"one of components differs from structs element type - "+
          manager->getTypeIdName(manager->getStructElementTypeId(id,i))+" != "+
          manager->getTypeIdName(accessors[i]->getId()),manager,id,accessors);
          return;
        }
      }
      break;
    default                  :
      ge::core::printError(GE_CORE_FCENAME,"cannot composite Resources into non composable type - "+manager->getTypeIdName(id),manager,id,accessors);
      return;
  }
  this->_components = accessors;
  for(auto const&x:accessors)
    this->_nofElements += x->getNofElements();
}

void*CompositeResource::getData()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  assert(this->_components.size()>0);
  assert(this->_components[0]!=nullptr);
  return this->_components[0]->getData();
}

void const*CompositeResource::getDataAddress()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  assert(this->_components.size()>0);
  assert(this->_components[0]!=nullptr);
  return this->_components[0]->getDataAddress();
}

std::shared_ptr<Resource> CompositeResource::operator[](size_t elem){
  PRINT_CALL_STACK(elem);
  assert(this!=nullptr);
  size_t offset=0;
  decltype(this->_components)::size_type i=0;
  while(elem>offset+this->_components[i]->getNofElements()){
    offset+=this->_components[i]->getNofElements();
    ++i;
  }
  return this->_components[i]->operator[](elem-offset);

}

size_t CompositeResource::getNofElements()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  return this->_nofElements;
}

std::string CompositeResource::data2Str()const{
  PRINT_CALL_STACK();
  assert(this!=nullptr);
  assert(this->_manager!=nullptr);
  std::stringstream ss;
  bool first;
  switch(this->_manager->getTypeIdType(this->_id)){
    case TypeRegister::ARRAY:
      ss<<"[";
      first=true;
      for(size_t i=0;i<this->_manager->getArraySize(this->_id);++i){
        if(first)first=false;
        else ss<<",";
        ss<<((*(CompositeResource*)this)[i])->data2Str();
      }
      ss<<"]";
      break;
    case TypeRegister::STRUCT:
      ss<<"{";
      first=true;
      for(size_t e=0;e<this->_manager->getNofStructElements(this->_id);++e){
        if(first)first=false;
        else ss<<",";
        ss<<((*(CompositeResource*)this)[e])->data2Str();
      }
      ss<<"}";
      break;
    default:
      break;
  }
  return ss.str();
}

