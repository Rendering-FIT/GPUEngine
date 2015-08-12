#pragma once

#include<iostream>

namespace ge{
  namespace util{
    class ArgData{
      public:
        enum Type{
          FLOAT = 0   ,
          INT         ,
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
