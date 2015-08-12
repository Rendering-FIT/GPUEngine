#pragma once

#include<geUtil/ArgData.h>
#include<sstream>

namespace ge{
  namespace util{
    template<typename TYPE>
      class BaseData: public ArgData{
        protected:
          TYPE _data;
        public:
          BaseData(TYPE data);
          virtual ~BaseData(){}
          inline TYPE get(){return this->_data;}
          inline void set(TYPE data){this->_data = data;}
          virtual std::string toStr();
      };

    template<>BaseData<float      >::BaseData(float       data);
    template<>BaseData<int        >::BaseData(int         data);
    template<>BaseData<std::string>::BaseData(std::string data);

    template<>std::string BaseData<float      >::toStr();
    template<>std::string BaseData<int        >::toStr();
    template<>std::string BaseData<std::string>::toStr();
  }
}

