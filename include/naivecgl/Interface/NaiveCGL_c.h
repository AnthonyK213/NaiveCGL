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

Naive_API double Naive_Math_Constant_PI(void);

Naive_API double Naive_Math_Constant_Epsilon(void);

Naive_API double Naive_Math_Constant_MinReal(void);

Naive_API double Naive_Math_Constant_MaxReal(void);

Naive_API double Naive_Math_Constant_UnsetReal(void);

/* Naive_Math_Util */

Naive_API Naive_Logical_t Naive_Math_Util_IsValidReal(const double /* real */);

/* Naive_Transient */

Naive_API Naive_Code_t Naive_Transient_Release(Naive_Handle_t /* handle */);

/* Naive_Geometry */

Naive_API Naive_Code_t Naive_Geometry_IsValid(
    const Naive_Handle_t /* handle */, Naive_Logical_t *const /* is_valid */);

Naive_API Naive_Code_t Naive_Geometry_Clone(const Naive_Handle_t /* handle */,
                                            Naive_Handle_t *const /* clone */);

/* Naive_Plane */

Naive_API Naive_Code_t Naive_Plane_New(const Naive_Plane_t * /* plane_sf */,
                                       Naive_Handle_t *const /* plane */);

Naive_API Naive_Code_t Naive_Plane_Location(
    const Naive_Handle_t /* handle */, Naive_Point3d_t *const /* location */);

Naive_API Naive_Code_t Naive_Plane_XAxis(const Naive_Handle_t /* handle */,
                                         Naive_Point3d_t *const /* x_axis */);

Naive_API Naive_Code_t Naive_Plane_YAxis(const Naive_Handle_t /* handle */,
                                         Naive_Point3d_t *const /* y_axis */);

Naive_API Naive_Code_t Naive_Plane_Axis(const Naive_Handle_t /* handle */,
                                        Naive_Point3d_t *const /* axis */);

Naive_API Naive_Code_t Naive_Plane_Distance(const Naive_Handle_t /* handle */,
                                            const Naive_Point3d_t * /* point */,
                                            double *const /* distance */);

/* Naive_Line */

Naive_API Naive_Code_t Naive_Line_New(const Naive_Line_t * /* line_sf */,
                                      Naive_Handle_t *const /* line */);

/* Naive_NurbsCurve */

Naive_API Naive_Code_t Naive_NurbsCurve_New(
    const int /* n_poles */, const Naive_Point3d_t * /* poles */,
    const int /* n_weights */, const double * /* weights */,
    const int /* n_knots */, const double * /* knots */,
    const int /* n_mults */, const int * /* mults */, const int /* degree */,
    Naive_Handle_t *const /* nurbs_curve */);

Naive_API Naive_Code_t Naive_NurbsCurve_Degree(
    const Naive_Handle_t /* handle */, int *const /* degree */);

Naive_API Naive_Code_t Naive_NurbsCurve_NbPoles(
    const Naive_Handle_t /* handle */, int *const /* n_poles */);

Naive_API Naive_Code_t Naive_NurbsCurve_Pole(const Naive_Handle_t /* handle */,
                                             const int /* index */,
                                             Naive_Point3d_t *const /* pole */);

Naive_API Naive_Code_t
Naive_NurbsCurve_Weight(const Naive_Handle_t /* handle */,
                        const int /* index */, double *const /* weight */);

Naive_API Naive_Code_t Naive_NurbsCurve_NbKnots(
    const Naive_Handle_t /* handle */, int *const /* n_knots */);

Naive_API Naive_Code_t Naive_NurbsCurve_Knot(const Naive_Handle_t /* handle */,
                                             const int /* index */,
                                             double *const /* knot */);

Naive_API Naive_Code_t
Naive_NurbsCurve_Multiplicity(const Naive_Handle_t /* handle */,
                              const int /* index */, int *const /* mult */);

Naive_API Naive_Code_t Naive_NurbsCurve_Bound(
    const Naive_Handle_t /* handle */, Naive_Interval_t *const /* bound */);

Naive_API Naive_Code_t Naive_NurbsCurve_Evaluate(
    const Naive_Handle_t /* handle */, const double /* t */,
    const int /* n_derivative */, int *const /* n_result */,
    Naive_Vector3d_t *const /* result */);

Naive_API Naive_Code_t Naive_NurbsCurve_CurvatureAt(
    const Naive_Handle_t /* handle */, const double /* t */,
    Naive_Vector3d_t *const /* curvature */);

Naive_API Naive_Code_t Naive_NurbsCurve_IncreaseDegree(
    Naive_Handle_t /* handle */, const int /* degree */);

Naive_API Naive_Code_t Naive_NurbsCurve_IncreaseMultiplicity(
    Naive_Handle_t /* handle */, const int /* index */, const int /* mult */);

Naive_API Naive_Code_t Naive_NurbsCurve_InsertKnot(Naive_Handle_t /* handle */,
                                                   const double /* t */,
                                                   const int /* mult */);

/* Reduces the multiplicity of the knot of index |index| to |mult|. */
Naive_API Naive_Code_t Naive_NurbsCurve_RemoveKnot(Naive_Handle_t /* handle */,
                                                   const int /* index */,
                                                   const int /* mult */);

/* Naive_NurbsSurface */

Naive_API Naive_Code_t Naive_NurbsSurface_New(
    const int /* n_poles_u */, const int /* n_poles_v */,
    const Naive_Point3d_t * /* poles */, const int /* n_weights_u */,
    const int /* n_weights_v */, const double * /* weights */,
    const int /* n_knots_u */, const double * /* knots_u */,
    const int /* n_knots_v */, const double * /* knots_v */,
    const int /* n_mults_u */, const int * /* mults_u */,
    const int /* n_mults_v */, const int * /* mults_v */,
    const int /* degree_u */, const int /* degree_v */,
    Naive_Handle_t *const /* nurbs_surface */);

Naive_API Naive_Code_t
Naive_NurbsSurface_Degree(const Naive_Handle_t /* handle */,
                          int *const /* degree_u */, int *const /* degree_v */);

Naive_API Naive_Code_t Naive_NurbsSurface_Evaluate(
    const Naive_Handle_t /* handle */, const double /* u */,
    const double /* v */, int /* n_derivative */, int *const /* n_result */,
    Naive_Vector3d_t *const /* result */);

/* Naive_Poly */

Naive_API Naive_Code_t Naive_Poly_New(const int /* n_vertices */,
                                      const Naive_Point3d_t * /* vertices */,
                                      const int /* n_triangles */,
                                      const Naive_Triangle_t * /* triangles */,
                                      Naive_Handle_t *const /* poly */);

Naive_API Naive_Code_t Naive_Poly_IsValid(
    const Naive_Handle_t /* handle */, Naive_Logical_t *const /* is_valid */);

Naive_API Naive_Code_t Naive_Poly_Clone(const Naive_Handle_t /* handle */,
                                        Naive_Handle_t *const /* clone */);

Naive_API Naive_Code_t Naive_Poly_Vertices(
    const Naive_Handle_t /* handle */, int *const /* n_vertices */,
    Naive_Point3d_t *const /* vertices */);

Naive_API Naive_Code_t Naive_Poly_Triangles(
    const Naive_Handle_t /* handle */, int *const /* n_triangles */,
    Naive_Triangle_t *const /* triangles */);

/* Naive_BndShape_ConvexHull2D */

Naive_API Naive_Code_t Naive_BndShape_ConvexHull2D_New(
    int /* n_points */, const Naive_Point2d_t * /* points */,
    Naive_ConvexHull2D_Algorithm /* algo */,
    Naive_Handle_t *const /* covex_hull_2d */);

Naive_API Naive_Code_t Naive_BndShape_ConvexHull2D_SetAlgorithm(
    Naive_Handle_t /* handle */, Naive_ConvexHull2D_Algorithm /* algo */);

Naive_API Naive_Code_t
    Naive_BndShape_ConvexHull2D_Perform(Naive_Handle_t /* handle */);

Naive_API Naive_Code_t Naive_BndShape_ConvexHull2D_Add(
    Naive_Handle_t /* handle */, Naive_Point2d_t /* point */,
    Naive_Logical_t /* to_perform */);

Naive_API Naive_Code_t Naive_BndShape_ConvexHull2D_Result(
    const Naive_Handle_t /* handle */, int *const /* n_convex_points */,
    int *const /* convex_indices */,
    Naive_Point2d_t *const /* convex_points */);

/* Naive_BndShape_EnclosingDisc */

Naive_API Naive_Code_t
Naive_BndShape_EnclosingDisc_New(Naive_Handle_t *const /* enclosing_disc */);

Naive_API Naive_Code_t Naive_BndShape_EnclosingDisc_Rebuild(
    Naive_Handle_t /* handle */, int /* n_points */,
    const Naive_Point2d_t * /* points */);

Naive_API Naive_Code_t Naive_BndShape_EnclosingDisc_Circle(
    const Naive_Handle_t /* handle */, Naive_Point2d_t *const /* origin */,
    double *const /* radius */);

/* Naive_Intersect_Intersection */

Naive_API Naive_Code_t Naive_Intersect_Intersection_LinePlane(
    const Naive_Handle_t /* line */, const Naive_Handle_t /* plane */,
    double *const /* t_line */);

/* Naive_Tessellation_Sphere */

Naive_API Naive_Code_t Naive_Tessellation_TetraSphere(
    const Naive_Point3d_t * /* center */, const double /* radius */,
    const int /* level */, Naive_Handle_t *const /* poly */);

#undef Naive_API

#endif
