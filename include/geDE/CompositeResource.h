#pragma once

#include<geDE/Resource.h>

namespace ge{
  namespace de{
    class GEDE_EXPORT CompositeResource: public Resource{
      protected:
        std::vector<std::shared_ptr<Resource>>_components;
        size_t _nofElements;
      public:
        CompositeResource(
            std::shared_ptr<TypeRegister>const&         manager   = nullptr                   ,
            TypeId                                      id        = TypeRegister::UNREGISTERED,
            std::vector<std::shared_ptr<Resource>>const&accessors = {}                        );
        virtual ~CompositeResource();
        virtual void*getData()const = 0;
        virtual void const*getDataAddress()const = 0;
        virtual std::shared_ptr<Resource> operator[](size_t elem);
        virtual size_t getNofElements()const=0;
        virtual std::string data2Str()const=0;
    };


  }
}
