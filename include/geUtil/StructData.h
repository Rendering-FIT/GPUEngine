#pragma once

#include<vector>
#include<geUtil/ArgData.h>

namespace ge{
  namespace util{
    class StructData: public ArgData{
      protected:
        std::vector<ArgData*>_data;
      public:
        StructData();
        virtual ~StructData();
        ArgData*operator[](unsigned i);
        void add(ArgData*item);
        unsigned size();
        virtual bool sameType(ArgData*other);
        virtual std::string toStr();
    };
  }
}

