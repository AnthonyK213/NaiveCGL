#ifndef _NaiveCGL_Interface_NaiveCGL_c_types_HeaderFile
#define _NaiveCGL_Interface_NaiveCGL_c_types_HeaderFile

#ifndef __cplusplus
#include "stdbool.h"
#include "stdint.h"
typedef void Naive_Mesh;
typedef void Naive_Poly;
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
