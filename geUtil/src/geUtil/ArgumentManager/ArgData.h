#pragma once

#include<iostream>
#include<geUtil/Export.h>

namespace ge{
  namespace util{
    class GEUTIL_EXPORT ArgData{
      public:
        enum Type{
          BOOL = 0    ,
          I8          ,
          I16         ,
          I32         ,
          I64         ,
          U8          ,
          U16         ,
          U32         ,
          U64         ,
          F32         ,
          F64         ,
          STRING      ,
          ARRAY       ,
          STRUCT      ,
        };
      protected:
        Type _type;
      public:
        ArgData(Type type);
        virtual ~ArgData();
        Type getType();
        virtual bool sameType(ArgData*other);
        virtual std::string toStr();
    };
  }
}
