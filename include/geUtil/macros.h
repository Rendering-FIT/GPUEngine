#pragma once

#include <cstring>
#include <iostream>

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
