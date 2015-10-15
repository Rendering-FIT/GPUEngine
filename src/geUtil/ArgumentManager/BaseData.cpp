#include<geUtil/ArgumentManager/BaseData.h>

using namespace ge::util;

template<>BaseData<bool              >::BaseData(bool               data):ArgData(ArgData::BOOL  ){this->set(data);}
template<>BaseData<char              >::BaseData(char               data):ArgData(ArgData::I8    ){this->set(data);}
template<>BaseData<short             >::BaseData(short              data):ArgData(ArgData::I16   ){this->set(data);}
template<>BaseData<int               >::BaseData(int                data):ArgData(ArgData::I32   ){this->set(data);}
template<>BaseData<int long long     >::BaseData(int long long      data):ArgData(ArgData::I64   ){this->set(data);}
template<>BaseData<unsigned char     >::BaseData(unsigned char      data):ArgData(ArgData::U8    ){this->set(data);}
template<>BaseData<unsigned short    >::BaseData(unsigned short     data):ArgData(ArgData::U16   ){this->set(data);}
template<>BaseData<unsigned          >::BaseData(unsigned           data):ArgData(ArgData::U32   ){this->set(data);}
template<>BaseData<unsigned long long>::BaseData(unsigned long long data):ArgData(ArgData::U64   ){this->set(data);}
template<>BaseData<float             >::BaseData(float              data):ArgData(ArgData::F32   ){this->set(data);}
template<>BaseData<double            >::BaseData(double             data):ArgData(ArgData::F64   ){this->set(data);}
template<>BaseData<std::string       >::BaseData(std::string        data):ArgData(ArgData::STRING){this->set(data);}

template<>std::string BaseData<bool              >::toStr(){std::stringstream ss;ss<<"bool "  <<(this->_data?"true":"false");return ss.str();}
template<>std::string BaseData<char              >::toStr(){std::stringstream ss;ss<<"i8 "    <<this->_data;return ss.str();}
template<>std::string BaseData<short             >::toStr(){std::stringstream ss;ss<<"i16 "   <<this->_data;return ss.str();}
template<>std::string BaseData<int               >::toStr(){std::stringstream ss;ss<<"i32 "   <<this->_data;return ss.str();}
template<>std::string BaseData<int long long     >::toStr(){std::stringstream ss;ss<<"i64 "   <<this->_data;return ss.str();}
template<>std::string BaseData<unsigned char     >::toStr(){std::stringstream ss;ss<<"u8 "    <<this->_data;return ss.str();}
template<>std::string BaseData<unsigned short    >::toStr(){std::stringstream ss;ss<<"u16 "   <<this->_data;return ss.str();}
template<>std::string BaseData<unsigned          >::toStr(){std::stringstream ss;ss<<"u32 "   <<this->_data;return ss.str();}
template<>std::string BaseData<unsigned long long>::toStr(){std::stringstream ss;ss<<"u64 "   <<this->_data;return ss.str();}
template<>std::string BaseData<float             >::toStr(){std::stringstream ss;ss<<"f32 "   <<this->_data;return ss.str();}
template<>std::string BaseData<double            >::toStr(){std::stringstream ss;ss<<"f64 "   <<this->_data;return ss.str();}
template<>std::string BaseData<std::string       >::toStr(){std::stringstream ss;ss<<"string "<<this->_data;return ss.str();}

