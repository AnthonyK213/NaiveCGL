#ifndef _NaiveCGL_Interface_NaiveCGL_c_types_Header
#define _NaiveCGL_Interface_NaiveCGL_c_types_Header

#ifndef __cplusplus
#include "stdbool.h"
#include "stdint.h"
#else
#include <cstdint>
#endif

typedef enum {
  Naive_Ok,
  Naive_Fail,
} Naive_Code;

typedef struct {
  double x, y;
} Naive_Point2d_T;

typedef struct {
  double x, y, z;
} Naive_Point3d_T;

typedef struct {
  int32_t n0, n1, n2;
} Naive_Triangle_T;

#endif
