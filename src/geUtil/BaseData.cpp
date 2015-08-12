#include<geUtil/BaseData.h>

using namespace ge::util;

template<>BaseData<float      >::BaseData(float       data):ArgData(ArgData::FLOAT ){this->set(data);}
template<>BaseData<int        >::BaseData(int         data):ArgData(ArgData::INT   ){this->set(data);}
template<>BaseData<std::string>::BaseData(std::string data):ArgData(ArgData::STRING){this->set(data);}

template<>std::string BaseData<float      >::toStr(){std::stringstream ss;ss<<"float " <<this->_data;return ss.str();}
template<>std::string BaseData<int        >::toStr(){std::stringstream ss;ss<<"int "   <<this->_data;return ss.str();}
template<>std::string BaseData<std::string>::toStr(){std::stringstream ss;ss<<"string "<<this->_data;return ss.str();}

