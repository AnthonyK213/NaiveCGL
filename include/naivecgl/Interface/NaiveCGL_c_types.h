#ifndef _NaiveCGL_Interface_NaiveCGL_c_types_HeaderFile
#define _NaiveCGL_Interface_NaiveCGL_c_types_HeaderFile

typedef enum {
  Naive_Ok = 0,
  Naive_Err,
  Naive_NotImplemented,
  Naive_Initialized = 1000,
  Naive_NullException = 1500,
  Naive_InvalidValue,
  Naive_InvalidHandle,
  Naive_NoIntersection,
  Naive_ConvexHull_InsufficientPoint = 2000,
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

/* Naive_H */

typedef void *Naive_Handle_t;

/* Naive_Code_t */

typedef int Naive_Code_t;

/* Naive_Logical_t */

typedef unsigned char Naive_Logical_t;

#define Naive_Logical_true ((Naive_Logical_t)1)
#define Naive_Logical_false ((Naive_Logical_t)0)

/* Naive_XY_t */

typedef struct {
  double x, y;
} Naive_XY_t;

/* Naive_XYZ_t */

typedef struct {
  double x, y, z;
} Naive_XYZ_t;

/* Naive_Vector2d_t */

typedef Naive_XY_t Naive_Vector2d_t;

/* Naive_Point2d_t */

typedef Naive_XY_t Naive_Point2d_t;

/* Naive_Vector3d_t */

typedef Naive_XYZ_t Naive_Vector3d_t;

/* Naive_Point3d_t */

typedef Naive_XYZ_t Naive_Point3d_t;

/* Naive_Interval_t */

typedef struct {
  double t0, t1;
} Naive_Interval_t;

/* Naive_Triangle_t */

typedef struct {
  int n0, n1, n2;
} Naive_Triangle_t;

/* Naive_Axis1_t */

typedef struct {
  Naive_Point3d_t location;
  Naive_Vector3d_t axis;
} Naive_Axis1_t;

/* Naive_Axis2_t */

typedef struct {
  Naive_Point3d_t location;
  Naive_Vector3d_t axis;
  Naive_Vector3d_t ref_direction;
} Naive_Axis2_t;

/* Naive_Line_t */

typedef struct {
  Naive_Axis1_t basis_set;
} Naive_Line_t;

/* Naive_Plane_t */

typedef struct {
  Naive_Axis2_t basis_set;
} Naive_Plane_t;

#endif
