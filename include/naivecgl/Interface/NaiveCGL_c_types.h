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
} Naive_Vector2d_T;

typedef struct {
  double x, y, z;
} Naive_Vector3d_T;

typedef Naive_Vector2d_T Naive_Point2d_T;
typedef Naive_Vector3d_T Naive_Point3d_T;

typedef struct {
  double t0, t1;
} Naive_Interval_T;

typedef struct {
  Naive_Point3d_T origin;
  Naive_Vector3d_T xAxis, yAxis;
} Naive_Plane_T;

typedef struct {
  Naive_Plane_T plane;
  double radius;
} Naive_Circle_T;

typedef struct {
  Naive_Point3d_T from, to;
} Naive_Line_T;

typedef struct {
  Naive_Plane_T plane;
  Naive_Interval_T x, y;
} Naive_Rectangle_T;

typedef struct {
  int32_t n0, n1, n2;
} Naive_Triangle_T;

#endif
