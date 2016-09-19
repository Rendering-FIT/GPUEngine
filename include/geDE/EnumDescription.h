#pragma once

#include<geDE/TypeDescription.h>
#include<geDE/TypeRegister.h>

namespace ge{
  namespace de{
    class EnumDescription: public TypeDescription{
      public:
        std::vector<EnumElementType>elements;
        EnumDescription(
            std::vector<EnumElementType>const&elements);
        EnumDescription();
        virtual ~EnumDescription();
        virtual bool init(
            TypeRegister*           tr         ,
            TypeDescriptionVector const&description,
            size_t                 &i          ,
            bool                    exists     )override;
        bool operator==(EnumDescription const&other)const;
        virtual bool equal(TypeDescription const*other)const override;
        virtual std::string toStr(TypeRegister const*tr,TypeId)const override;
        virtual void copy(void*o,void*i,TypeRegister const*tr,TypeId id)const override;
        virtual void callConstructor(TypeRegister*,void*)const override;
        virtual void callDestructor(TypeRegister*,void*)const override;
        virtual size_t byteSize(TypeRegister const*)const override;
    };
  }
}

