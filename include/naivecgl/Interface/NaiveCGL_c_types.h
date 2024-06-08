#ifndef _NaiveCGL_Interface_NaiveCGL_c_types_HeaderFile
#define _NaiveCGL_Interface_NaiveCGL_c_types_HeaderFile

typedef enum {
  Naive_Code_ok = 0,
  Naive_Code_err,
  Naive_Code_not_implemented,
  Naive_Code_initialized = 1000,
  Naive_Code_null_exception = 1500,
  Naive_Code_invalid_value,
  Naive_Code_invalid_handle,
  Naive_Code_no_intersection,
  Naive_Code_points_are_collinear = 2000,
  Naive_Code_points_are_coplanar,
  Naive_Code_index_out_of_range,
  Naive_Code_value_out_of_range,
  Naive_Code_insufficient_points,
  Naive_Code_insufficient_knots,
  Naive_Code_zero_interval,
  Naive_Code_periodic_open,
  Naive_Code_periodic_not_smooth,
  Naive_Code_cant_make_nurbs,
  Naive_Code_weight_le_0,
  Naive_Code_bad_knots,
  Naive_Code_poles_weights_not_match,
  Naive_Code_knots_mults_not_match,
  Naive_Code_invalid_mults,
} Naive_Code;

typedef enum {
  Naive_Algorithm_quick_hull = 0,
  Naive_Algorithm_incremental,
  Naive_Algorithm_graham_scan,
  Naive_Algorithm_divide_and_conquer,
} Naive_Algorithm;

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
