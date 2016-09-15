#pragma once

#include<geDE/TypeDescription.h>
#include<geDE/TypeRegister.h>

namespace ge{
  namespace de{
    class ArrayDescription: public TypeDescription{
      public:
        size_t size;
        TypeId elementType;
        ArrayDescription(
            TypeId const&elementType,
            size_t const&size       );
        ArrayDescription();
        virtual ~ArrayDescription();
        virtual bool init(
            TypeRegister*           tr         ,
            TypeDescriptionVector const&description,
            size_t                 &i          ,
            bool                    exists     )override;
        bool operator==(ArrayDescription const&other)const;
        virtual bool equal(TypeDescription const*other)const override;
        virtual std::string toStr(TypeRegister const*tr,TypeId)const override;
        virtual void copy(void*o,void*i,TypeRegister const*tr,TypeId id)const override;
        virtual void callConstructor(TypeRegister*tr,void*ptr)const override;
        virtual void callDestructor(TypeRegister*tr,void*ptr)const override;
        virtual size_t byteSize(TypeRegister const*tr)const override;
        virtual std::string data2Str(TypeRegister const*tr,void*ptr)override;
    };
  }
}
