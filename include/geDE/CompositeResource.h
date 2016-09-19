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
        virtual void*getData()const override;
        virtual void const*getDataAddress()const override;
        virtual uint8_t getByte(size_t offset)const override;
        virtual void setByte(size_t offset,uint8_t byte)override;
        virtual std::shared_ptr<Resource> operator[](size_t elem)override;
        virtual size_t getNofElements()const override;
        virtual std::string data2Str()const override;
    };
  }
}
