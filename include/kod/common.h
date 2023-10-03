//
// common.h
//

#ifndef KOD_COMMON_H
#define KOD_COMMON_H

#ifdef _WIN32
  #define KOD_API __declspec(dllexport)
#else
  #define KOD_API
#endif

#endif // KOD_COMMON_H
