﻿#ifndef _NaiveCGL_Interface_NaiveCGL_c_types_HeaderFile
#define _NaiveCGL_Interface_NaiveCGL_c_types_HeaderFile

/* Naive_Code */

typedef enum {
  Naive_Code_ok = 0,
  Naive_Code_err,
  Naive_Code_not_implemented,
  Naive_Code_initialized = 1000,
  Naive_Code_null_arg_address = 1500,
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

typedef int Naive_Code_t;

/* TYPEDEFS */

typedef void *Naive_Body_t;
typedef void *Naive_ConvexHull2D_t;
typedef void *Naive_Curve_t;
typedef void *Naive_Edge_t;
typedef void *Naive_EnclosingDisc_t;
typedef void *Naive_Face_t;
typedef void *Naive_Fin_t;
typedef void *Naive_Geometry_t;
typedef void *Naive_Line_t;
typedef void *Naive_Loop_t;
typedef void *Naive_NurbsCurve_t;
typedef void *Naive_NurbsSurface_t;
typedef void *Naive_Plane_t;
typedef void *Naive_Poly_t;
typedef void *Naive_Shell_t;
typedef void *Naive_Surface_t;
typedef void *Naive_Transient_t;
typedef void *Naive_Vertex_t;

/* Naive_Logical_t */

typedef unsigned char Naive_Logical_t;

#define Naive_Logical_true ((Naive_Logical_t)1)
#define Naive_Logical_false ((Naive_Logical_t)0)

/* Naive_XY_t */

typedef struct Naive_XY_s {
  double x, y;
} Naive_XY_t;

/* Naive_XYZ_t */

typedef struct Naive_XYZ_s {
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

typedef struct Naive_Interval_s {
  double t0, t1;
} Naive_Interval_t;

/* Naive_Triangle_t */

typedef struct Naive_Triangle_s {
  int n0, n1, n2;
} Naive_Triangle_t;

/* Naive_Axis1_sf_t */

typedef struct Naive_Axis1_sf_s {
  Naive_Point3d_t location;
  Naive_Vector3d_t axis;
} Naive_Axis1_sf_t;

/* Naive_Axis2_sf_t */

typedef struct Naive_Axis2_sf_s {
  Naive_Point3d_t location;
  Naive_Vector3d_t axis;
  Naive_Vector3d_t ref_direction;
} Naive_Axis2_sf_t;

/* Naive_Line_sf_t */

typedef struct Naive_Line_sf_s {
  Naive_Axis1_sf_t basis_set;
} Naive_Line_sf_t;

/* Naive_Plane_sf_t */

typedef struct Naive_Plane_sf_s {
  Naive_Axis2_sf_t basis_set;
} Naive_Plane_sf_t;

/* Naive_Algorithm */

typedef enum {
  Naive_Algorithm_quick_hull = 0,
  Naive_Algorithm_incremental,
  Naive_Algorithm_graham_scan,
  Naive_Algorithm_divide_and_conquer,
} Naive_Algorithm;

typedef int Naive_Algorithm_t;

/* Naive_boolean_function */

typedef enum {
  Naive_boolean_intersect_c = 0,
  Naive_boolean_subtract_c,
  Naive_boolean_unite_c,
} Naive_boolean_function;

typedef int Naive_boolean_function_t;

/* Naive_Body_boolean_o_t */

typedef struct Naive_Body_boolean_o_s {
  Naive_boolean_function_t function;
} Naive_Body_boolean_o_t;

/* Naive_Body_boolean_o_m */

#define Naive_Body_boolean_o_m(options)                                        \
  ((options).function = Naive_boolean_unite_c)

#endif
