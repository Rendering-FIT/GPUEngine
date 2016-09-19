#pragma once

#include<geDE/TypeRegister.h>

namespace ge{
  namespace de{
    class TypeDescription{
      public:
        TypeRegister::TypeType type;
        TypeRegister::ToStr data2StrPtr = nullptr;
        TypeRegister::Copy copyData = nullptr;
        TypeDescription(TypeRegister::TypeType const&type);
        virtual ~TypeDescription(){}
        virtual bool init(
            TypeRegister               *tr         ,
            TypeDescriptionVector const&description,
            size_t                     &i          ,
            bool                        exists     ) = 0;
        virtual std::string toStr(TypeRegister const*,TypeId)const = 0;
        virtual void copy(void*o,void*i,TypeRegister const*,TypeId)const = 0;
        virtual bool equal(TypeDescription const*other)const = 0;
        virtual void callConstructor(TypeRegister*tr,void*ptr)const = 0;
        virtual void callDestructor(TypeRegister*tr,void*ptr)const = 0;
        virtual size_t byteSize(TypeRegister const*tr)const = 0;
        TypeId findInRegister(
            TypeRegister               *tr         ,
            TypeDescriptionVector const&description,
            size_t                     &i          );
        virtual std::string data2Str(TypeRegister const*,void*ptr);
        static TypeId checkAndBindType(
            TypeRegister               *tr         ,
            std::string           const&name       ,
            TypeDescriptionVector const&description,
            TypeDescription            *d          ,
            size_t                     &i          );
    };
  }
}



