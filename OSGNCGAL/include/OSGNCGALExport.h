#pragma once

#if defined(_MSC_VER)
#pragma warning( disable : 4244 )
#pragma warning( disable : 4251 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4275 )
#pragma warning( disable : 4290 )
#pragma warning( disable : 4786 )
#pragma warning( disable : 4305 )
#pragma warning( disable : 4996 )
#endif

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__) || defined( __MWERKS__)
#  if defined( USE_OSGNCGAL_STATIC )
#    define OSGNCGAL_EXPORT
#  elif defined( USE_OSGNCGAL_DYN )
#    define OSGNCGAL_EXPORT   __declspec(dllexport)
#  else
#    define OSGNCGAL_EXPORT   __declspec(dllimport)
#endif
#else
#   define OSGNCGAL_EXPORT
#endif 