#pragma once

#include<vector>
#include<geUtil/Export.h>
#include<geUtil/ArgumentManager/ArgData.h>

namespace ge{
  namespace util{
    class GEUTIL_EXPORT ArrayData: public ArgData{
      protected:
        ArgData::Type _innerType;
        std::vector<ArgData*>_data;
      public:
        ArrayData(ArrayData::Type innerType);
        virtual ~ArrayData();
        ArgData*operator[](unsigned i);
        void add(ArgData*item);
        unsigned size();
        ArgData::Type getInnerType();
        virtual bool sameType(ArgData*other);
        virtual std::string toStr();
    };
  }
}
