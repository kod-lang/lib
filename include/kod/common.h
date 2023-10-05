//
// common.h
//

#ifndef KOD_COMMON_H
#define KOD_COMMON_H

#ifndef KOD_API
  #if defined(_MSC_VER) && defined(KOD_API_DLLEXPORT)
    #define KOD_API __declspec(dllexport)
  #else
    #define KOD_API
  #endif
#endif

#endif // KOD_COMMON_H
