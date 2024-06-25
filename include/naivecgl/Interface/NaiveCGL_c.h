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

/* Naive_Object */

Naive_API Naive_Code_t Naive_Object_free(Naive_Object_t /* Object */);

/* Naive_Geometry */

Naive_API Naive_Code_t
Naive_Geometry_is_valid(const Naive_Geometry_t /* geometry */,
                        Naive_Logical_t *const /* is_valid */);

Naive_API Naive_Code_t Naive_Geometry_clone(
    const Naive_Geometry_t /* geometry */, Naive_Geometry_t *const /* clone */);

/* Naive_Curve */

Naive_API Naive_Code_t Naive_Curve_ask_bound(
    const Naive_Curve_t /* curve */, Naive_Interval_t *const /* bound */);

Naive_API Naive_Code_t
Naive_Curve_evaluate(const Naive_Curve_t /* curve */, const double /* t */,
                     const int /* n_derivative */, int *const /* n_result */,
                     Naive_Vector3d_t *const /* result */);

Naive_API Naive_Code_t
Naive_Curve_curvature_at(const Naive_Curve_t /* curve */, const double /* t */,
                         Naive_Vector3d_t *const /* curvature */);

/* Naive_Surface */

Naive_API Naive_Code_t Naive_Surface_evaluate(
    const Naive_Surface_t /* surface */, const double /* u */,
    const double /* v */, const int /* n_derivative */,
    int *const /* n_result */, Naive_Vector3d_t *const /* result */);

/* Naive_Plane */

Naive_API Naive_Code_t Naive_Plane_new(const Naive_Plane_sf_t * /* plane_sf */,
                                       Naive_Plane_t *const /* plane */);

Naive_API Naive_Code_t Naive_Plane_ask(const Naive_Plane_t /* plane */,
                                       Naive_Plane_sf_t *const /* plane_sf */);

Naive_API Naive_Code_t Naive_Plane_distance(const Naive_Plane_t /* plane */,
                                            const Naive_Point3d_t * /* point */,
                                            double *const /* distance */);

/* Naive_Line */

Naive_API Naive_Code_t Naive_Line_new(const Naive_Line_sf_t * /* line_sf */,
                                      Naive_Line_t *const /* line */);

/* Naive_NurbsCurve */

Naive_API Naive_Code_t Naive_NurbsCurve_new(
    const int /* n_poles */, const Naive_Point3d_t * /* poles */,
    const int /* n_weights */, const double * /* weights */,
    const int /* n_knots */, const double * /* knots */,
    const int /* n_mults */, const int * /* mults */, const int /* degree */,
    Naive_NurbsCurve_t *const /* nurbs_curve */);

Naive_API Naive_Code_t Naive_NurbsCurve_ask_degree(
    const Naive_NurbsCurve_t /* nurbs_curve */, int *const /* degree */);

Naive_API Naive_Code_t Naive_NurbsCurve_ask_poles(
    const Naive_NurbsCurve_t /* nurbs_curve */, int *const /* n_poles */,
    Naive_Point3d_t *const /* poles */);

Naive_API Naive_Code_t Naive_NurbsCurve_ask_weights(
    const Naive_NurbsCurve_t /* nurbs_curve */, int *const /* n_weights */,
    double *const /* weights */);

Naive_API Naive_Code_t
Naive_NurbsCurve_ask_knots(const Naive_NurbsCurve_t /* nurbs_curve */,
                           int *const /* n_knots */, double *const /* knots */);

Naive_API Naive_Code_t
Naive_NurbsCurve_ask_mults(const Naive_NurbsCurve_t /* nurbs_curve */,
                           int *const /* n_mults */, int *const /* mults */);

Naive_API Naive_Code_t Naive_NurbsCurve_increase_degree(
    Naive_NurbsCurve_t /* nurbs_curve */, const int /* degree */);

Naive_API Naive_Code_t Naive_NurbsCurve_increase_multiplicity(
    Naive_NurbsCurve_t /* nurbs_curve */, const int /* index */,
    const int /* mult */);

Naive_API Naive_Code_t
Naive_NurbsCurve_insert_knot(Naive_NurbsCurve_t /* nurbs_curve */,
                             const double /* t */, const int /* mult */);

/* Reduces the multiplicity of the knot of index |index| to |mult|. */
Naive_API Naive_Code_t
Naive_NurbsCurve_remove_knot(Naive_NurbsCurve_t /* nurbs_curve */,
                             const int /* index */, const int /* mult */);

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
    Naive_NurbsSurface_t *const /* nurbs_surface */);

Naive_API Naive_Code_t Naive_NurbsSurface_ask_degree(
    const Naive_NurbsSurface_t /* nurbs_surface */, int *const /* degree_u */,
    int *const /* degree_v */);

/* Naive_Poly */

Naive_API Naive_Code_t Naive_Poly_new(const int /* n_vertices */,
                                      const Naive_Point3d_t * /* vertices */,
                                      const int /* n_triangles */,
                                      const Naive_Triangle_t * /* triangles */,
                                      Naive_Poly_t *const /* poly */);

Naive_API Naive_Code_t Naive_Poly_is_valid(
    const Naive_Poly_t /* poly */, Naive_Logical_t *const /* is_valid */);

Naive_API Naive_Code_t Naive_Poly_clone(const Naive_Poly_t /* poly */,
                                        Naive_Poly_t *const /* clone */);

Naive_API Naive_Code_t Naive_Poly_ask_vertices(
    const Naive_Poly_t /* poly */, int *const /* n_vertices */,
    Naive_Point3d_t *const /* vertices */);

Naive_API Naive_Code_t Naive_Poly_ask_triangles(
    const Naive_Poly_t /* poly */, int *const /* n_triangles */,
    Naive_Triangle_t *const /* triangles */);

/* Naive_BndShape_ConvexHull2D */

Naive_API Naive_Code_t Naive_BndShape_ConvexHull2D_new(
    int /* n_points */, const Naive_Point2d_t * /* points */,
    Naive_Algorithm_t /* algo */,
    Naive_ConvexHull2D_t *const /* covex_hull_2d */);

Naive_API Naive_Code_t Naive_BndShape_ConvexHull2D_set_algorithm(
    Naive_ConvexHull2D_t /* covex_hull_2d */, Naive_Algorithm_t /* algo */);

Naive_API Naive_Code_t Naive_BndShape_ConvexHull2D_perform(
    Naive_ConvexHull2D_t /* covex_hull_2d */);

Naive_API Naive_Code_t Naive_BndShape_ConvexHull2D_add_point(
    Naive_ConvexHull2D_t /* covex_hull_2d */, Naive_Point2d_t /* point */,
    Naive_Logical_t /* to_perform */);

Naive_API Naive_Code_t Naive_BndShape_ConvexHull2D_ask_result(
    const Naive_ConvexHull2D_t /* covex_hull_2d */,
    int *const /* n_convex_points */, int *const /* convex_indices */,
    Naive_Point2d_t *const /* convex_points */);

/* Naive_BndShape_EnclosingDisc */

Naive_API Naive_Code_t Naive_BndShape_EnclosingDisc_new(
    Naive_EnclosingDisc_t *const /* enclosing_disc */);

Naive_API Naive_Code_t Naive_BndShape_EnclosingDisc_rebuild(
    Naive_EnclosingDisc_t /* enclosing_disc */, const int /* n_points */,
    const Naive_Point2d_t * /* points */);

Naive_API Naive_Code_t Naive_BndShape_EnclosingDisc_ask_circle(
    const Naive_EnclosingDisc_t /* enclosing_disc */,
    Naive_Point2d_t *const /* origin */, double *const /* radius */);

/* Naive_Tessellation */

Naive_API Naive_Code_t Naive_Tessellation_Sphere_tetrasphere(
    const Naive_Point3d_t * /* center */, const double /* radius */,
    const int /* level */, Naive_Poly_t *const /* poly */);

/* Naive_Body */

Naive_API Naive_Code_t Naive_Body_ask_location(
    const Naive_Body_t /* body */, Naive_Transform3d_t *const /* location */);

Naive_API Naive_Code_t
Naive_Body_ask_orientation(const Naive_Body_t /* body */,
                           Naive_Orientation_t *const /* orientation */);

Naive_API Naive_Code_t Naive_Body_ask_edges(const Naive_Body_t /* body */,
                                            int *const /* n_edges */,
                                            Naive_Edge_t *const /* edges */);

Naive_API Naive_Code_t Naive_Body_ask_faces(const Naive_Body_t /* body */,
                                            int *const /* n_faces */,
                                            Naive_Face_t *const /* faces */);

Naive_API Naive_Code_t Naive_Body_ask_fins(const Naive_Body_t /* body */,
                                           int *const /* n_fins */,
                                           Naive_Fin_t *const /* fins */);

Naive_API Naive_Code_t Naive_Body_ask_loops(const Naive_Body_t /* body */,
                                            int *const /* n_loops */,
                                            Naive_Loop_t *const /* loops */);

Naive_API Naive_Code_t Naive_Body_ask_shells(const Naive_Body_t /* body */,
                                             int *const /* n_shells */,
                                             Naive_Shell_t *const /* shells */);

Naive_API Naive_Code_t Naive_Body_ask_vertices(
    const Naive_Body_t /* body */, int *const /* n_vertices */,
    Naive_Vertex_t *const /* vertices */);

Naive_API Naive_Code_t Naive_Body_boolean(
    const Naive_Body_t /* target */, const int /* n_tools */,
    const Naive_Body_t * /* tools */,
    const Naive_Body_boolean_o_t * /* options */
);

#undef Naive_API

#endif
