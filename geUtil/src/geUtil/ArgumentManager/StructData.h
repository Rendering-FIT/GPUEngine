#pragma once

#include<vector>
#include<geUtil/Export.h>
#include<geUtil/ArgumentManager/ArgData.h>

namespace ge{
  namespace util{
    class GEUTIL_EXPORT StructData: public ArgData{
      protected:
        std::vector<ArgData*>_data;
      public:
        StructData();
        virtual ~StructData();
        ArgData*operator[](unsigned i);
        void add(ArgData*item);
        decltype(_data)::size_type size();
        virtual bool sameType(ArgData*other);
        virtual std::string toStr();
    };
  }
}

