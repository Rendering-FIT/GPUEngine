#pragma once

#include<geUtil/Export.h>
#include<geUtil/ArgumentManager/ArgData.h>
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
          TYPE get(){return this->_data;}
          void set(TYPE data){this->_data = data;}
          virtual std::string toStr();
      };

    template<>BaseData<bool              >::BaseData(bool               data);
    template<>BaseData<char              >::BaseData(char               data);
    template<>BaseData<short             >::BaseData(short              data);
    template<>BaseData<int               >::BaseData(int                data);
    template<>BaseData<int long long     >::BaseData(int long long      data);
    template<>BaseData<unsigned char     >::BaseData(unsigned char      data);
    template<>BaseData<unsigned short    >::BaseData(unsigned short     data);
    template<>BaseData<unsigned          >::BaseData(unsigned           data);
    template<>BaseData<unsigned long long>::BaseData(unsigned long long data);
    template<>BaseData<float             >::BaseData(float              data);
    template<>BaseData<double            >::BaseData(double             data);
    template<>BaseData<std::string       >::BaseData(std::string        data);

    template<>std::string BaseData<bool              >::toStr();
    template<>std::string BaseData<char              >::toStr();
    template<>std::string BaseData<short             >::toStr();
    template<>std::string BaseData<int               >::toStr();
    template<>std::string BaseData<int long long     >::toStr();
    template<>std::string BaseData<unsigned char     >::toStr();
    template<>std::string BaseData<unsigned short    >::toStr();
    template<>std::string BaseData<unsigned          >::toStr();
    template<>std::string BaseData<unsigned long long>::toStr();
    template<>std::string BaseData<float             >::toStr();
    template<>std::string BaseData<double            >::toStr();
    template<>std::string BaseData<std::string       >::toStr();

  }
}

