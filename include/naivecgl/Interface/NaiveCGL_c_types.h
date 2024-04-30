#ifndef _NaiveCGL_Interface_NaiveCGL_c_types_HeaderFile
#define _NaiveCGL_Interface_NaiveCGL_c_types_HeaderFile

#ifndef __cplusplus
#include "stdbool.h"
#include "stdint.h"
#else
#include <cstdint>
#endif

typedef void *Naive_H;

typedef enum {
  Naive_Ok = 0,
  Naive_Err,
  Naive_Initialized,
  Naive_NullException,
  Naive_NotImplemented,
  Naive_ConvexHull_InsufficientPoint,
  Naive_ConvexHull_PointsAreCollinear,
  Naive_ConvexHull_PointsAreCoplanar,
} Naive_Code;

typedef enum {
  Naive_ConvexHull2D_Quickhull = 0,
  Naive_ConvexHull2D_Incremental,
  Naive_ConvexHull2D_GrahamScan,
} Naive_ConvexHull2D_Algorithm;

typedef enum {
  Naive_ConvexHull3D_Quickhull = 0,
  Naive_ConvexHull3D_Incremental,
  Naive_ConvexHull3D_DivideAndConquer,
} Naive_ConvexHull3D_Algorithm;

typedef struct {
  double x, y;
} Naive_XY_T;

typedef struct {
  double x, y, z;
} Naive_XYZ_T;

typedef struct {
  double t0, t1;
} Naive_Interval_T;

typedef struct {
  int32_t n0, n1, n2;
} Naive_Triangle_T;

typedef Naive_XY_T Naive_Vector2d_T;
typedef Naive_XY_T Naive_Point2d_T;
typedef Naive_XYZ_T Naive_Vector3d_T;
typedef Naive_XYZ_T Naive_Point3d_T;

#endif
