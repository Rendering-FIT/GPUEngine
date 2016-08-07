#include<geDE/RegisterBasicTypes.h>
#include<geDE/TypeRegister.h>

using namespace ge::de;

void ge::de::registerBasicTypes(std::shared_ptr<TypeRegister>const&tr){
  PRINT_CALL_STACK(tr);
  assert(tr!=nullptr);
  auto any    = tr->addType<Any     >();(void)any;
  auto Void   = tr->addType<void    >();(void)Void;
  auto Bool   = tr->addType<bool    >();
  auto I8     = tr->addType<int8_t  >();
  auto I16    = tr->addType<int16_t >();
  auto I32    = tr->addType<int32_t >();
  auto I64    = tr->addType<int64_t >();
  auto U8     = tr->addType<uint8_t >();
  auto U16    = tr->addType<uint16_t>();
  auto U32    = tr->addType<uint32_t>();
  auto U64    = tr->addType<uint64_t>();
  auto F32    = tr->addType<float   >();
  auto F64    = tr->addType<double  >();
  auto String = tr->addType<std::string>([](void*ptr){new(ptr)std::string();},[](void*ptr){((std::string*)ptr)->~basic_string();});
  tr->addType<float[2]>();
  tr->addType<float[3]>();
  tr->addType<float[4]>();
  tr->addType<int32_t[]>();
  tr->addType<int32_t[]>();
  tr->addType<int32_t[]>();
  tr->addType<uint32_t[]>();
  tr->addType<uint32_t[]>();
  tr->addType<uint32_t[]>();
  tr->addType<float[3][3]>();
  tr->addType<float[4][4]>();
  tr->addToStrFunction(Bool  ,[](void*ptr){if((bool&)ptr)return std::string("true");else return std::string("false");});
  tr->addToStrFunction(I8    ,[](void*ptr){std::stringstream ss;ss<<*(int8_t  *)ptr;return ss.str();});
  tr->addToStrFunction(I16   ,[](void*ptr){std::stringstream ss;ss<<*(int16_t *)ptr;return ss.str();});
  tr->addToStrFunction(I32   ,[](void*ptr){std::stringstream ss;ss<<*(int32_t *)ptr;return ss.str();});
  tr->addToStrFunction(I64   ,[](void*ptr){std::stringstream ss;ss<<*(int64_t *)ptr;return ss.str();});
  tr->addToStrFunction(U8    ,[](void*ptr){std::stringstream ss;ss<<*(uint8_t *)ptr;return ss.str();});
  tr->addToStrFunction(U16   ,[](void*ptr){std::stringstream ss;ss<<*(uint16_t*)ptr;return ss.str();});
  tr->addToStrFunction(U32   ,[](void*ptr){std::stringstream ss;ss<<*(uint32_t*)ptr;return ss.str();});
  tr->addToStrFunction(U64   ,[](void*ptr){std::stringstream ss;ss<<*(uint64_t*)ptr;return ss.str();});
  tr->addToStrFunction(F32   ,[](void*ptr){std::stringstream ss;ss<<*(float   *)ptr;return ss.str();});
  tr->addToStrFunction(F64   ,[](void*ptr){std::stringstream ss;ss<<*(double  *)ptr;return ss.str();});
  tr->addToStrFunction(String,[](void*ptr){std::stringstream ss;ss<<"\""<<*(std::string*)ptr<<"\"";return ss.str();});

}
