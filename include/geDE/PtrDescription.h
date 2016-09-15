#pragma once

#include<geDE/TypeDescription.h>
#include<geDE/TypeRegister.h>

namespace ge{
  namespace de{
    class PtrDescription: public TypeDescription{
      public:
        TypeId innerType;
        PtrDescription(TypeId id);
        PtrDescription();
        virtual ~PtrDescription();
        virtual bool init(
            TypeRegister*           tr         ,
            TypeDescriptionVector const&description,
            size_t                 &i          ,
            bool                    exists     )override;
        bool operator==(PtrDescription const&other)const;
        virtual bool equal(TypeDescription const*other)const override;
        virtual std::string toStr(TypeRegister const*tr,TypeId)const override;
        virtual void copy(void*o,void*i,TypeRegister const*tr,TypeId id)const override;
        virtual void callConstructor(TypeRegister*,void*ptr)const override;
        virtual void callDestructor(TypeRegister*,void*ptr)const override;
        virtual size_t byteSize(TypeRegister const*)const override;
    };
  }
}
