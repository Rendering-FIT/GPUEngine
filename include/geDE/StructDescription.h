#pragma once

#include<geDE/TypeDescription.h>
#include<geDE/TypeRegister.h>

namespace ge{
  namespace de{
    class StructDescription: public TypeDescription{
      public:
        std::vector<TypeId>elementTypes;
        StructDescription(
            std::vector<TypeId>const&elementTypes);
        StructDescription();
        virtual ~StructDescription();
        virtual bool init(
            TypeRegister*           tr         ,
            TypeDescriptionVector const&description,
            size_t                 &i          ,
            bool                    exists     )override;
        bool operator==(StructDescription const&other)const;
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
