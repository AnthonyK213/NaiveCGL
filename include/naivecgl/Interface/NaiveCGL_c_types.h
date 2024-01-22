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

typedef void *Naive_Handle;

typedef enum {
  Naive_Ok,
  Naive_Err,
} Naive_Code;

typedef enum {
  Naive_ConvexHull2D_Quickhull,
  Naive_ConvexHull2D_Incremental,
  Naive_ConvexHull2D_GrahamScan,
} Naive_ConvexHull2D_Algorithm;

typedef enum {
  Naive_ConvexHull2D_Done,
  Naive_ConvexHull2D_InitDone,
  Naive_ConvexHull2D_Failed,
  Naive_ConvexHull2D_InsufficientPoint,
  Naive_ConvexHull2D_PointsAreCollinear,
  Naive_ConvexHull2D_AlgoNotImplemented,
} Naive_ConvexHull2D_Status;

typedef enum {
  Naive_ConvexHull3D_Quickhull,
  Naive_ConvexHull3D_Incremental,
  Naive_ConvexHull3D_DivideAndConquer,
} Naive_ConvexHull3D_Algorithm;

typedef enum {
  Naive_ConvexHull3D_Done,
  Naive_ConvexHull3D_InitDone,
  Naive_ConvexHull3D_Failed,
  Naive_ConvexHull3D_InsufficientPoint,
  Naive_ConvexHull3D_PointsAreCollinear,
  Naive_ConvexHull3D_PointsAreCoplanar,
  Naive_ConvexHull3D_AlgoNotImplemented,
} Naive_ConvexHull3D_Status;

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
