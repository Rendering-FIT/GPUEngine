#ifndef GERG_EXPORT_
#define GERG_EXPORT_

#if defined(_MSC_VER)
   #pragma warning( disable : 4251 ) //http://msdn.microsoft.com/cs-cz/library/esew7y1w.aspx  http://support.microsoft.com/default.aspx?scid=KB;EN-US;168958
         /** I'm advising to only hide this warning. Because if we would do the work there are STL containers that can't be exported correctly by design. */
#endif

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


#endif //GE_EXPORT_
