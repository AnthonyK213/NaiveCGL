#ifndef _NaiveCGL_Interface_NaiveCGL_c_HeaderFile
#define _NaiveCGL_Interface_NaiveCGL_c_HeaderFile

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

/* Naive_Math_Constant */

Naive_API double Naive_Math_Constant_pi(void);

Naive_API double Naive_Math_Constant_epsilon(void);

Naive_API double Naive_Math_Constant_min_real(void);

Naive_API double Naive_Math_Constant_max_real(void);

Naive_API double Naive_Math_Constant_unset_real(void);

/* Naive_Math_Util */

Naive_API Naive_Logical_t
Naive_Math_Util_is_valid_real(const double /* real */);

/* Naive_Transient */

Naive_API Naive_Code_t Naive_Transient_release(Naive_Handle_t /* handle */);

/* Naive_Geometry */

Naive_API Naive_Code_t Naive_Geometry_is_valid(
    const Naive_Handle_t /* handle */, Naive_Logical_t *const /* is_valid */);

Naive_API Naive_Code_t Naive_Geometry_clone(const Naive_Handle_t /* handle */,
                                            Naive_Handle_t *const /* clone */);

/* Naive_Plane */

Naive_API Naive_Code_t Naive_Plane_new(const Naive_Plane_t * /* plane_sf */,
                                       Naive_Handle_t *const /* plane */);

Naive_API Naive_Code_t Naive_Plane_ask(const Naive_Handle_t /* handle */,
                                       Naive_Plane_t *const /* plane_sf */);

Naive_API Naive_Code_t Naive_Plane_distance(const Naive_Handle_t /* handle */,
                                            const Naive_Point3d_t * /* point */,
                                            double *const /* distance */);

/* Naive_Line */

Naive_API Naive_Code_t Naive_Line_new(const Naive_Line_t * /* line_sf */,
                                      Naive_Handle_t *const /* line */);

/* Naive_NurbsCurve */

Naive_API Naive_Code_t Naive_NurbsCurve_new(
    const int /* n_poles */, const Naive_Point3d_t * /* poles */,
    const int /* n_weights */, const double * /* weights */,
    const int /* n_knots */, const double * /* knots */,
    const int /* n_mults */, const int * /* mults */, const int /* degree */,
    Naive_Handle_t *const /* nurbs_curve */);

Naive_API Naive_Code_t Naive_NurbsCurve_ask_degree(
    const Naive_Handle_t /* handle */, int *const /* degree */);

Naive_API Naive_Code_t Naive_NurbsCurve_ask_poles(
    const Naive_Handle_t /* handle */, int *const /* n_poles */,
    Naive_Point3d_t *const /* poles */);

Naive_API Naive_Code_t Naive_NurbsCurve_ask_weights(
    const Naive_Handle_t /* handle */, int *const /* n_weights */,
    double *const /* weights */);

Naive_API Naive_Code_t
Naive_NurbsCurve_ask_knots(const Naive_Handle_t /* handle */,
                           int *const /* n_knots */, double *const /* knots */);

Naive_API Naive_Code_t
Naive_NurbsCurve_ask_mults(const Naive_Handle_t /* handle */,
                           int *const /* n_mults */, int *const /* mults */);

Naive_API Naive_Code_t Naive_NurbsCurve_ask_bound(
    const Naive_Handle_t /* handle */, Naive_Interval_t *const /* bound */);

Naive_API Naive_Code_t Naive_NurbsCurve_evaluate(
    const Naive_Handle_t /* handle */, const double /* t */,
    const int /* n_derivative */, int *const /* n_result */,
    Naive_Vector3d_t *const /* result */);

Naive_API Naive_Code_t Naive_NurbsCurve_curvature_at(
    const Naive_Handle_t /* handle */, const double /* t */,
    Naive_Vector3d_t *const /* curvature */);

Naive_API Naive_Code_t Naive_NurbsCurve_increase_degree(
    Naive_Handle_t /* handle */, const int /* degree */);

Naive_API Naive_Code_t Naive_NurbsCurve_increase_multiplicity(
    Naive_Handle_t /* handle */, const int /* index */, const int /* mult */);

Naive_API Naive_Code_t Naive_NurbsCurve_insert_knot(Naive_Handle_t /* handle */,
                                                    const double /* t */,
                                                    const int /* mult */);

/* Reduces the multiplicity of the knot of index |index| to |mult|. */
Naive_API Naive_Code_t Naive_NurbsCurve_remove_knot(Naive_Handle_t /* handle */,
                                                    const int /* index */,
                                                    const int /* mult */);

/* Naive_NurbsSurface */

Naive_API Naive_Code_t Naive_NurbsSurface_new(
    const int /* n_poles_u */, const int /* n_poles_v */,
    const Naive_Point3d_t * /* poles */, const int /* n_weights_u */,
    const int /* n_weights_v */, const double * /* weights */,
    const int /* n_knots_u */, const double * /* knots_u */,
    const int /* n_knots_v */, const double * /* knots_v */,
    const int /* n_mults_u */, const int * /* mults_u */,
    const int /* n_mults_v */, const int * /* mults_v */,
    const int /* degree_u */, const int /* degree_v */,
    Naive_Handle_t *const /* nurbs_surface */);

Naive_API Naive_Code_t Naive_NurbsSurface_ask_degree(
    const Naive_Handle_t /* handle */, int *const /* degree_u */,
    int *const /* degree_v */);

Naive_API Naive_Code_t Naive_NurbsSurface_evaluate(
    const Naive_Handle_t /* handle */, const double /* u */,
    const double /* v */, int /* n_derivative */, int *const /* n_result */,
    Naive_Vector3d_t *const /* result */);

/* Naive_Poly */

Naive_API Naive_Code_t Naive_Poly_new(const int /* n_vertices */,
                                      const Naive_Point3d_t * /* vertices */,
                                      const int /* n_triangles */,
                                      const Naive_Triangle_t * /* triangles */,
                                      Naive_Handle_t *const /* poly */);

Naive_API Naive_Code_t Naive_Poly_is_valid(
    const Naive_Handle_t /* handle */, Naive_Logical_t *const /* is_valid */);

Naive_API Naive_Code_t Naive_Poly_clone(const Naive_Handle_t /* handle */,
                                        Naive_Handle_t *const /* clone */);

Naive_API Naive_Code_t Naive_Poly_ask_vertices(
    const Naive_Handle_t /* handle */, int *const /* n_vertices */,
    Naive_Point3d_t *const /* vertices */);

Naive_API Naive_Code_t Naive_Poly_ask_triangles(
    const Naive_Handle_t /* handle */, int *const /* n_triangles */,
    Naive_Triangle_t *const /* triangles */);

/* Naive_BndShape_ConvexHull2D */

Naive_API Naive_Code_t Naive_BndShape_ConvexHull2D_new(
    int /* n_points */, const Naive_Point2d_t * /* points */,
    Naive_Algorithm /* algo */, Naive_Handle_t *const /* covex_hull_2d */);

Naive_API Naive_Code_t Naive_BndShape_ConvexHull2D_set_algorithm(
    Naive_Handle_t /* handle */, Naive_Algorithm /* algo */);

Naive_API Naive_Code_t
    Naive_BndShape_ConvexHull2D_perform(Naive_Handle_t /* handle */);

Naive_API Naive_Code_t Naive_BndShape_ConvexHull2D_add_point(
    Naive_Handle_t /* handle */, Naive_Point2d_t /* point */,
    Naive_Logical_t /* to_perform */);

Naive_API Naive_Code_t Naive_BndShape_ConvexHull2D_ask_result(
    const Naive_Handle_t /* handle */, int *const /* n_convex_points */,
    int *const /* convex_indices */,
    Naive_Point2d_t *const /* convex_points */);

/* Naive_BndShape_EnclosingDisc */

Naive_API Naive_Code_t
Naive_BndShape_EnclosingDisc_new(Naive_Handle_t *const /* enclosing_disc */);

Naive_API Naive_Code_t Naive_BndShape_EnclosingDisc_rebuild(
    Naive_Handle_t /* handle */, int /* n_points */,
    const Naive_Point2d_t * /* points */);

Naive_API Naive_Code_t Naive_BndShape_EnclosingDisc_ask_circle(
    const Naive_Handle_t /* handle */, Naive_Point2d_t *const /* origin */,
    double *const /* radius */);

/* Naive_Intersect_Intersection */

Naive_API Naive_Code_t Naive_Intersect_Intersection_line_plane(
    const Naive_Handle_t /* line */, const Naive_Handle_t /* plane */,
    double *const /* t_line */);

/* Naive_Tessellation */

Naive_API Naive_Code_t Naive_Tessellation_tetrasphere(
    const Naive_Point3d_t * /* center */, const double /* radius */,
    const int /* level */, Naive_Handle_t *const /* poly */);

#undef Naive_API

#endif
