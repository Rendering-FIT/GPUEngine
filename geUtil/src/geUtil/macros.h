#pragma once

#include <cstring>
#include <iostream>
#include <geCore/Dtemplates.h>

/*
#define ENUM_CLASS(name,...) \
   enum class name {__VA_ARGS__}; \
   std::ostream& operator<<(std::ostream& os, name val) \
   {\
      char s[]=#__VA_ARGS__;\
      char*ret = strtok(&s[0],",");\
      for(int i=0; i<(int)val;++i)\
      {\
         ret=strtok(NULL,",");\
      }\
      return os << ret;\
   }

#define ENUM_CLASS_FRIEND_OPERATOR(name,...) \
   enum class name {__VA_ARGS__}; \
   friend std::ostream& operator<<(std::ostream& os, name val) \
            {\
      char s[]=#__VA_ARGS__;\
      char*ret = strtok(&s[0],",");\
      for(int i=0; i<(int)val;++i)\
                  {\
         ret=strtok(NULL,",");\
                  }\
      return os << ret;\
            }
*/

#define ENUM_CLASS(name,...) \
  enum class name {__VA_ARGS__}; \
std::ostream& operator<<(std::ostream& os, name val) \
{\
  static std::map<unsigned,std::string>table = ge::core::ParseEnumArgs()(VA_ARGS_TO_STRING(__VA_ARGS__));\
  auto a=table.find(val);\
  if(a!=table.end())os << a->second;\
  return os;\
}

#define ENUM_CLASS_FRIEND_OPERATOR(name,...) \
  enum class name {__VA_ARGS__}; \
friend std::ostream& operator<<(std::ostream& os, name val) \
{\
  static std::map<unsigned,std::string>table = ge::core::ParseEnumArgs()(VA_ARGS_TO_STRING(__VA_ARGS__));\
  auto a=table.find((unsigned)val);\
  if(a!=table.end())os << a->second;\
  return os;\
}

