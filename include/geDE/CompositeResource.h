#pragma once

#include<geDE/Resource.h>

namespace ge{
  namespace de{
    class GECORE_EXPORT CompositeResource: public Resource{
      protected:
        std::vector<std::shared_ptr<Resource>>_components;
        TypeRegister::DescriptionElement _nofElements;
      public:
        CompositeResource(
            std::shared_ptr<TypeRegister>const&         manager   = nullptr                   ,
            TypeRegister::TypeID                        id        = TypeRegister::UNREGISTERED,
            std::vector<std::shared_ptr<Resource>>const&accessors = {}                        );
        virtual void*getData()const = 0;
        virtual void const*getDataAddress()const = 0;
        virtual std::shared_ptr<Resource> operator[](TypeRegister::DescriptionIndex elem);
        virtual TypeRegister::DescriptionElement getNofElements()const=0;
        virtual std::string data2Str()const=0;
    };


  }
}
