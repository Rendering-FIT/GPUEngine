#pragma once

#ifndef _MSC_VER
  #define SIZED_VARIADIC_PARAMS(NAME,SIZE)\
              typename...NAME, typename std::enable_if<sizeof...(NAME) == SIZE, unsigned>::type = 0
#else
  #define SIZED_VARIADIC_PARAMS(NAME)\
              typename...NAME
#endif//immature Visual Studio compiler...

