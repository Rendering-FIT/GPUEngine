#pragma once

#include<geDE/TypeDescription.h>
#include<geDE/TypeRegister.h>

namespace ge{
  namespace de{
    class AtomicDescription: public TypeDescription{
      public:
        size_t size;
        CDPtr destructor;
        CDPtr constructor;
        AtomicDescription(
            size_t const&size                 ,
            CDPtr  const&constructor = nullptr,
            CDPtr  const&destructor  = nullptr);
        virtual ~AtomicDescription();
        virtual bool init(
            TypeRegister*               ,
            TypeDescriptionVector const&,
            size_t                     &,
            bool                        )override;
        bool operator==(AtomicDescription const&other)const;
        virtual bool equal(TypeDescription const*other)const override;
        virtual std::string toStr(TypeRegister const*tr,TypeId id)const override;
        virtual void copy(void*o,void*i,TypeRegister const*tr,TypeId id)const override;
        virtual void callConstructor(TypeRegister*,void*ptr)const override;
        virtual void callDestructor(TypeRegister*,void*ptr)const override;
        virtual size_t byteSize(TypeRegister const*)const override;
    };

  }
}
