#ifndef GESG_EXPORT_H
#define GESG_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
#   ifdef GE_LIBRARY_STATIC
#      define GESG_EXPORT
#   elif defined(GESG_LIBRARY)
#      define GESG_EXPORT __declspec(dllexport)
#   else
#      define GESG_EXPORT __declspec(dllimport)
#   endif
#else
#   ifdef GE_LIBRARY
#      define GESG_EXPORT __attribute__ ((visibility("default")))
#   else
#      define GESG_EXPORT
#   endif
#endif

#endif // GESG_EXPORT_H
