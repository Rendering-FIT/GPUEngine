#ifndef GERG_EXPORT_H
#define GERG_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
#   ifdef GE_LIBRARY_STATIC
#      define GERG_EXPORT
#   elif defined(GERG_LIBRARY)
#      define GERG_EXPORT __declspec(dllexport)
#   else
#      define GERG_EXPORT __declspec(dllimport)
#   endif
#else
#   ifdef GE_LIBRARY
#      define GERG_EXPORT __attribute__ ((visibility("default")))
#   else
#      define GERG_EXPORT
#   endif
#endif

#endif // GERG_EXPORT_H
