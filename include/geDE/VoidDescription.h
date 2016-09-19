#pragma once

#include<geDE/TypeDescription.h>
#include<geDE/TypeRegister.h>

namespace ge{
  namespace de{
    class VoidDescription: public TypeDescription{
      public:
        VoidDescription();
        virtual ~VoidDescription();
        virtual bool init(
            TypeRegister               *           ,
            TypeDescriptionVector const&description,
            size_t                     &i          ,
            bool                                   )override;
        bool operator==(VoidDescription const&)const;
        virtual bool equal(TypeDescription const*other)const override;
        virtual std::string toStr(TypeRegister const*tr,TypeId id)const override;
        virtual void copy(void*o,void*i,TypeRegister const*tr,TypeId id)const override;
        virtual void callConstructor(TypeRegister*,void*)const override;
        virtual void callDestructor(TypeRegister*,void*)const override;
        virtual size_t byteSize(TypeRegister const*)const override;
    };
  }
}
