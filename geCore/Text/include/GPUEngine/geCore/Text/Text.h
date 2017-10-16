#pragma once

#include<GPUEngine/geCore/Text/text_export.h>
#include<iostream>
#include<cstdint>

namespace ge{
  namespace core{
    TEXT_EXPORT std::string loadTextFile(std::string const&fileName);
    TEXT_EXPORT std::string processEscapeSequences(std::string const&data);
    TEXT_EXPORT bool isNan     (std::string const&text);
    TEXT_EXPORT bool isInfinity(std::string const&text);
    TEXT_EXPORT bool isFloat   (std::string const&text);
    TEXT_EXPORT bool isDouble  (std::string const&text);
    TEXT_EXPORT bool isInt     (std::string const&text);
    TEXT_EXPORT bool isUint    (std::string const&text);
    TEXT_EXPORT bool isString  (std::string const&text);
    TEXT_EXPORT bool isFloatingPoint(std::string const&text);
    TEXT_EXPORT bool isIntegral     (std::string const&text);

    template<typename TYPE>
      bool isValue(std::string const&text);

    template<>inline bool isValue<float      >(std::string const&text){return isFloat (text);}
    template<>inline bool isValue<double     >(std::string const&text){return isDouble(text);}
    template<>inline bool isValue<int8_t     >(std::string const&text){return isInt   (text);}
    template<>inline bool isValue<int16_t    >(std::string const&text){return isInt   (text);}
    template<>inline bool isValue<int32_t    >(std::string const&text){return isInt   (text);}
    template<>inline bool isValue<int64_t    >(std::string const&text){return isInt   (text);}
    template<>inline bool isValue<uint8_t    >(std::string const&text){return isUint  (text);}
    template<>inline bool isValue<uint16_t   >(std::string const&text){return isUint  (text);}
    template<>inline bool isValue<uint32_t   >(std::string const&text){return isUint  (text);}
    template<>inline bool isValue<uint64_t   >(std::string const&text){return isUint  (text);}
    template<>inline bool isValue<std::string>(std::string const&text){return isString(text);}

    template<typename TYPE>
      TYPE str2Value(std::string const&text);

    template<>inline float    str2Value<float   >(std::string const&str){return float   (std::atof (str.c_str()));}
    template<>inline double   str2Value<double  >(std::string const&str){return double  (std::atof (str.c_str()));}
    template<>inline int8_t   str2Value<int8_t  >(std::string const&str){return int8_t  (std::atoi (str.c_str()));}
    template<>inline int16_t  str2Value<int16_t >(std::string const&str){return int16_t (std::atoi (str.c_str()));}
    template<>inline int32_t  str2Value<int32_t >(std::string const&str){return int32_t (std::atoi (str.c_str()));}
    template<>inline int64_t  str2Value<int64_t >(std::string const&str){return int64_t (std::atoll(str.c_str()));}
    template<>inline uint8_t  str2Value<uint8_t >(std::string const&str){return uint8_t (std::atoi (str.c_str()));}
    template<>inline uint16_t str2Value<uint16_t>(std::string const&str){return uint16_t(std::atoi (str.c_str()));}
    template<>inline uint32_t str2Value<uint32_t>(std::string const&str){return uint32_t(std::atoi (str.c_str()));}
    template<>inline uint64_t str2Value<uint64_t>(std::string const&str){return uint64_t(std::atoll(str.c_str()));}

  }
}
