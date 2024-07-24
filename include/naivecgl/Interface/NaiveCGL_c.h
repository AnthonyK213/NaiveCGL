#ifndef _NAIVECGL_C_H
#define _NAIVECGL_C_H

#include "NaiveCGL_c_macros.h"
#include "NaiveCGL_c_types.h"

#ifndef __cplusplus
#define Naive_API
#else
#ifdef _WIN32
#define Naive_API extern "C" __declspec(dllexport)
#else
#define Naive_API extern "C"
#endif
#endif

/* Naive_Body */

Naive_API Naive_Code_t Naive_Body_ask_edges(Naive_Body_t /* body */,
                                            int *const /* n_edges */,
                                            Naive_Edge_t **const /* edges */);

Naive_API Naive_Code_t Naive_Body_ask_faces(Naive_Body_t /* body */,
                                            int *const /* n_faces */,
                                            Naive_Face_t **const /* faces */);

Naive_API Naive_Code_t Naive_Body_ask_fins(Naive_Body_t /* body */,
                                           int *const /* n_fins */,
                                           Naive_Fin_t **const /* fins */);

Naive_API Naive_Code_t Naive_Body_ask_location(
    Naive_Body_t /* body */, Naive_Transform3d_t *const /* location */);

Naive_API Naive_Code_t Naive_Body_ask_loops(Naive_Body_t /* body */,
                                            int *const /* n_loops */,
                                            Naive_Loop_t **const /* loops */);

Naive_API Naive_Code_t Naive_Body_ask_orient(
    Naive_Body_t /* body */, Naive_Orientation_t *const /* orientation */);

Naive_API Naive_Code_t
Naive_Body_ask_shells(Naive_Body_t /* body */, int *const /* n_shells */,
                      Naive_Shell_t **const /* shells */);

Naive_API Naive_Code_t
Naive_Body_ask_vertices(Naive_Body_t /* body */, int *const /* n_vertices */,
                        Naive_Vertex_t **const /* vertices */);

Naive_API Naive_Code_t Naive_Body_boolean(
    Naive_Body_t /* target */, int /* n_tools */,
    const Naive_Body_t * /* tools */,
    const Naive_Body_boolean_o_t * /* options */
);

/* Naive_Class */

Naive_API Naive_Code_t Naive_Class_ask_superclass(
    Naive_Class_t /* class */, Naive_Class_t *const /* superclass */);

Naive_API Naive_Code_t Naive_Class_is_subclass(
    Naive_Class_t /* may_be_subclass */, Naive_Class_t /* class */,
    Naive_Logical_t *const /* is_subclass */);

/* Naive_Curve */

Naive_API Naive_Code_t Naive_Curve_ask_bound(
    Naive_Curve_t /* curve */, Naive_Interval_t *const /* bound */);

Naive_API Naive_Code_t Naive_Curve_eval(Naive_Curve_t /* curve */,
                                        double /* t */, int /* n_deriv */,
                                        Naive_Vec3d_t /* p */[]);

Naive_API Naive_Code_t
Naive_Curve_eval_curvature(Naive_Curve_t /* curve */, double /* t */,
                           Naive_Vec3d_t *const /* curvature */);

Naive_API Naive_Code_t Naive_Curve_make_wire_body(
    int /* n_curves */, const Naive_Curve_t /* curves */[],
    const Naive_Interval_t /* bounds */[],
    const Naive_Curve_make_wire_body_o_t * /* options */,
    Naive_Body_t *const /* body */, int *const /* n_new_edges */,
    Naive_Edge_t **const /* new_edges */, int **const /* edge_index */);

/* Naive_Geom2dAPI */

Naive_API Naive_Code_t Naive_Geom2dAPI_convex_hull(
    int /* n_points */, const Naive_Pnt2d_t * /* points */,
    Naive_Algorithm_t /* algo */, int *const /* n_convex_points */,
    int **const /* convex_indices */,
    Naive_Pnt2d_t **const /* convex_points */);

Naive_API Naive_Code_t Naive_Geom2dAPI_enclosing_disc(
    int /* n_points */, const Naive_Pnt2d_t * /* points */,
    Naive_Pnt2d_t *const /* origin */, double *const /* radius */);

/* Naive_Geometry */

Naive_API Naive_Code_t Naive_Geometry_clone(
    Naive_Geometry_t /* geometry */, Naive_Geometry_t *const /* clone */);

Naive_API Naive_Code_t Naive_Geometry_is_valid(
    Naive_Geometry_t /* geometry */, Naive_Logical_t *const /* is_valid */);

/* Naive_Line */

Naive_API Naive_Code_t Naive_Line_create(const Naive_Line_sf_t * /* line_sf */,
                                         Naive_Line_t *const /* line */);

/* Naive_Memory */

Naive_API Naive_Code_t Naive_Memory_alloc(size_t /* nbytes */,
                                          void **const /* pointer */);

Naive_API Naive_Code_t Naive_Memory_free(void * /* pointer */);

/* Naive_NurbsCurve */

Naive_API Naive_Code_t Naive_NurbsCurve_ask_degree(
    Naive_NurbsCurve_t /* nurbs_curve */, int *const /* degree */);

Naive_API Naive_Code_t Naive_NurbsCurve_ask_knots(
    Naive_NurbsCurve_t /* nurbs_curve */, int *const /* n_knots */,
    double **const /* knots */);

Naive_API Naive_Code_t
Naive_NurbsCurve_ask_mults(Naive_NurbsCurve_t /* nurbs_curve */,
                           int *const /* n_mults */, int **const /* mults */);

Naive_API Naive_Code_t Naive_NurbsCurve_ask_poles(
    Naive_NurbsCurve_t /* nurbs_curve */, int *const /* n_poles */,
    Naive_Pnt3d_t **const /* poles */);

Naive_API Naive_Code_t Naive_NurbsCurve_ask_weights(
    Naive_NurbsCurve_t /* nurbs_curve */, int *const /* n_weights */,
    double **const /* weights */);

Naive_API Naive_Code_t Naive_NurbsCurve_create(
    int /* n_poles */, const Naive_Pnt3d_t * /* poles */, int /* n_weights */,
    const double * /* weights */, int /* n_knots */, const double * /* knots */,
    int /* n_mults */, const int * /* mults */, int /* degree */,
    Naive_NurbsCurve_t *const /* nurbs_curve */);

Naive_API Naive_Code_t Naive_NurbsCurve_increase_degree(
    Naive_NurbsCurve_t /* nurbs_curve */, int /* degree */);

Naive_API Naive_Code_t Naive_NurbsCurve_increase_multiplicity(
    Naive_NurbsCurve_t /* nurbs_curve */, int /* index */, int /* mult */);

Naive_API Naive_Code_t Naive_NurbsCurve_insert_knot(
    Naive_NurbsCurve_t /* nurbs_curve */, double /* t */, int /* mult */);

/* Reduces the multiplicity of the knot of index |index| to |mult|. */
Naive_API Naive_Code_t Naive_NurbsCurve_remove_knot(
    Naive_NurbsCurve_t /* nurbs_curve */, int /* index */, int /* mult */);

/* Naive_NurbsSurface */

Naive_API Naive_Code_t Naive_NurbsSurface_ask_degree(
    Naive_NurbsSurface_t /* nurbs_surface */, int *const /* degree_u */,
    int *const /* degree_v */);

Naive_API Naive_Code_t Naive_NurbsSurface_create(
    int /* n_poles_u */, int /* n_poles_v */, const Naive_Pnt3d_t * /* poles */,
    int /* n_weights_u */, int /* n_weights_v */, const double * /* weights */,
    int /* n_knots_u */, const double * /* knots_u */, int /* n_knots_v */,
    const double * /* knots_v */, int /* n_mults_u */,
    const int * /* mults_u */, int /* n_mults_v */, const int * /* mults_v */,
    int /* degree_u */, int /* degree_v */,
    Naive_NurbsSurface_t *const /* nurbs_surface */);

/* Naive_Object */

Naive_API Naive_Code_t Naive_Object_ask_class(Naive_Object_t /* object */,
                                              Naive_Class_t *const /* class */);

Naive_API Naive_Code_t Naive_Object_delete(Naive_Object_t /* object */);

/* Naive_Plane */

Naive_API Naive_Code_t Naive_Plane_ask(Naive_Plane_t /* plane */,
                                       Naive_Plane_sf_t *const /* plane_sf */);

Naive_API Naive_Code_t Naive_Plane_create(
    const Naive_Plane_sf_t * /* plane_sf */, Naive_Plane_t *const /* plane */);

Naive_API Naive_Code_t Naive_Plane_distance(Naive_Plane_t /* plane */,
                                            const Naive_Pnt3d_t * /* point */,
                                            double *const /* distance */);

/* Naive_Surface */

Naive_API Naive_Code_t Naive_Surface_eval(Naive_Surface_t /* surface */,
                                          double /* u */, double /* v */,
                                          int /* n_u_deriv */,
                                          int /* n_v_deriv */,
                                          Naive_Vec3d_t /* p */[]);

/* Naive_Tessellation */

Naive_API Naive_Code_t Naive_Tessellation_make_tetrasphere(
    const Naive_Pnt3d_t * /* center */, double /* radius */, int /* level */,
    Naive_Triangulation_t *const /* triangulation */);

/* Naive_Triangulation */

Naive_API Naive_Code_t Naive_Triangulation_ask_triangles(
    Naive_Triangulation_t /* triangulation */, int *const /* n_triangles */,
    Naive_Triangle_t **const /* triangles */);

Naive_API Naive_Code_t Naive_Triangulation_ask_vertices(
    Naive_Triangulation_t /* triangulation */, int *const /* n_vertices */,
    Naive_Pnt3d_t **const /* vertices */);

Naive_API Naive_Code_t Naive_Triangulation_create(
    int /* n_vertices */, const Naive_Pnt3d_t * /* vertices */,
    int /* n_triangles */, const Naive_Triangle_t * /* triangles */,
    int /* i_offset */, Naive_Triangulation_t *const /* triangulation */);

#undef Naive_API

#endif
