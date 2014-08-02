#ifndef GE_EXPORT_H
#define GE_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
#   ifdef GE_LIBRARY_STATIC
#      define GE_EXPORT
#   elif defined(GE_LIBRARY)
#      define GE_EXPORT __declspec(dllexport)
#   else
#      define GE_EXPORT __declspec(dllimport)
#   endif
#else
#   ifdef GE_LIBRARY
#      define GE_EXPORT __attribute__ ((visibility("default")))
#   else
#      define GE_EXPORT
#   endif
#endif


#endif //GE_EXPORT_H