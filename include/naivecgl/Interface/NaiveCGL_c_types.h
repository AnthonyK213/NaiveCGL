#ifndef _NAIVECGL_C_TYPES_H
#define _NAIVECGL_C_TYPES_H

#include "NaiveCGL_c_enums.h"
#include "stddef.h"

/* TYPEDEFS */

typedef int Naive_Body_t;
typedef int Naive_Curve_t;
typedef int Naive_Edge_t;
typedef int Naive_Face_t;
typedef int Naive_Fin_t;
typedef int Naive_Geometry_t;
typedef int Naive_Line_t;
typedef int Naive_Loop_t;
typedef int Naive_Mesh_t;
typedef int Naive_NurbsCurve_t;
typedef int Naive_NurbsSurface_t;
typedef int Naive_Object_t;
typedef int Naive_Plane_t;
typedef int Naive_Point_t;
typedef int Naive_Shell_t;
typedef int Naive_Solid_t;
typedef int Naive_Surface_t;
typedef int Naive_Transform3d_t;
typedef int Naive_Triangulation_t;
typedef int Naive_Vertex_t;

typedef int Naive_Algorithm_t;
typedef int Naive_Class_t;
typedef int Naive_Code_t;
typedef int Naive_Loop_type_t;
typedef int Naive_NurbsCurve_form_t;
typedef int Naive_NurbsSurface_form_t;
typedef int Naive_Orientation_t;
typedef int Naive_boolean_function_t;

/* Naive_Logical_t */

typedef unsigned char Naive_Logical_t;

/* Naive_XY_t */

typedef struct Naive_XY_s {
  double x, y;
} Naive_XY_t;

/* Naive_XYZ_t */

typedef struct Naive_XYZ_s {
  double x, y, z;
} Naive_XYZ_t;

/* Naive_Pnt2d_t */

typedef Naive_XY_t Naive_Pnt2d_t;

/* Naive_Vec2d_t */

typedef Naive_XY_t Naive_Vec2d_t;

/* Naive_Pnt3d_t */

typedef Naive_XYZ_t Naive_Pnt3d_t;

/* Naive_Vec3d_t */

typedef Naive_XYZ_t Naive_Vec3d_t;

/* Naive_Interval_t */

typedef struct Naive_Interval_s {
  double t0, t1;
} Naive_Interval_t;

/* Naive_Triangle_t */

typedef struct Naive_Triangle_s {
  int n0, n1, n2;
} Naive_Triangle_t;

/* Naive_Ax2d_sf_t */

typedef struct Naive_Ax2d_sf_s {
  Naive_Pnt2d_t location;
  Naive_Vec2d_t axis;
} Naive_Ax2d_sf_t;

/* Naive_Ax22d_sf_t */

typedef struct Naive_Ax22d_sf_s {
  Naive_Pnt2d_t location;
  Naive_Vec2d_t x_axis;
  Naive_Vec2d_t y_axis;
} Naive_Ax22d_sf_t;

/* Naive_Ax1_sf_t */

typedef struct Naive_Ax1_sf_s {
  Naive_Pnt3d_t location;
  Naive_Vec3d_t axis;
} Naive_Ax1_sf_t;

/* Naive_Ax2_sf_t */

typedef struct Naive_Ax2_sf_s {
  Naive_Pnt3d_t location;
  Naive_Vec3d_t axis;
  Naive_Vec3d_t ref_direction;
} Naive_Ax2_sf_t;

/* Naive_Circle2d_sf_t */

typedef struct Naive_Circle2d_sf_s {
  Naive_Ax22d_sf_t basis_set;
  double radius;
} Naive_Circle2d_sf_t;

/* Naive_Line2d_sf_t */

typedef struct Naive_Line2d_sf_s {
  Naive_Ax2d_sf_t basis_set;
} Naive_Line2d_sf_t;

/* Naive_Circle_sf_t */

typedef struct Naive_Circle_sf_s {
  Naive_Ax2_sf_t basis_set;
  double radius;
} Naive_Circle_sf_t;

/* Naive_Line_sf_t */

typedef struct Naive_Line_sf_s {
  Naive_Ax1_sf_t basis_set;
} Naive_Line_sf_t;

/* Naive_NurbsCurve_sf_t */

typedef struct Naive_NurbsCurve_sf_s {
  int degree;
  int n_vertices;
  int vertex_dim;
  Naive_Logical_t is_rational;
  double *vertex;
  Naive_NurbsCurve_form_t form;
  int n_knots;
  int *knot_mult;
  double *knot;
  Naive_Logical_t is_periodic;
  Naive_Logical_t is_closed;
} Naive_NurbsCurve_sf_t;

/* Naive_NurbsSurface_sf_t */

typedef struct Naive_NurbsSurface_sf_s {
  int u_degree;
  int v_degree;
  int n_u_vertices;
  int n_v_vertices;
  int vertex_dim;
  Naive_Logical_t is_rational;
  double *vertex;
  Naive_NurbsSurface_form_t form;
  int n_u_knots;
  int n_v_knots;
  int *u_knot_mult;
  int *v_knot_mult;
  double *u_knot;
  double *v_knot;
  Naive_Logical_t is_u_periodic;
  Naive_Logical_t is_v_periodic;
  Naive_Logical_t is_u_closed;
  Naive_Logical_t is_v_closed;
} Naive_NurbsSurface_sf_t;

/* Naive_Point_sf_t */

typedef struct Naive_Point_sf_s {
  Naive_Pnt3d_t position;
} Naive_Point_sf_t;

/* Naive_Plane_sf_t */

typedef struct Naive_Plane_sf_s {
  Naive_Ax2_sf_t basis_set;
} Naive_Plane_sf_t;

/* Naive_Transform3d_sf_t */

typedef struct Naive_Transform3d_sf_s {
  double matrix[3][4];
} Naive_Transform3d_sf_t;

/* Naive_Curve_make_wire_body_o_t */

typedef struct Naive_Curve_make_wire_body_o_s {
  double tolerance;
} Naive_Curve_make_wire_body_o_t;

/* Naive_Body_boolean_o_t */

typedef struct Naive_Body_boolean_o_s {
  Naive_boolean_function_t function;
} Naive_Body_boolean_o_t;

#endif
