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

Naive_API Naive_Code_t Naive_Body_ask_edges(Naive_Body_t body,
                                            int *const n_edges,
                                            Naive_Edge_t **const edges);

Naive_API Naive_Code_t Naive_Body_ask_faces(Naive_Body_t body,
                                            int *const n_faces,
                                            Naive_Face_t **const faces);

Naive_API Naive_Code_t Naive_Body_ask_fins(Naive_Body_t body, int *const n_fins,
                                           Naive_Fin_t **const fins);

Naive_API Naive_Code_t
Naive_Body_ask_location(Naive_Body_t body, Naive_Transform3d_t *const location);

Naive_API Naive_Code_t Naive_Body_ask_loops(Naive_Body_t body,
                                            int *const n_loops,
                                            Naive_Loop_t **const loops);

Naive_API Naive_Code_t Naive_Body_ask_orient(
    Naive_Body_t body, Naive_Orientation_t *const orientation);

Naive_API Naive_Code_t Naive_Body_ask_shells(Naive_Body_t body,
                                             int *const n_shells,
                                             Naive_Shell_t **const shells);

Naive_API Naive_Code_t Naive_Body_ask_vertices(Naive_Body_t body,
                                               int *const n_vertices,
                                               Naive_Vertex_t **const vertices);

Naive_API Naive_Code_t
Naive_Body_boolean(Naive_Body_t target, int n_tools, const Naive_Body_t *tools,
                   const Naive_Body_boolean_o_t *options);

Naive_API Naive_Code_t Naive_Body_create_solid_block(
    double x, double y, double z, const Naive_Ax2_sf_t *basis_set,
    Naive_Body_t *const body);

/* Naive_Class */

Naive_API Naive_Code_t Naive_Class_ask_superclass(
    Naive_Class_t class_, Naive_Class_t *const superclass);

Naive_API Naive_Code_t
Naive_Class_is_subclass(Naive_Class_t may_be_subclass, Naive_Class_t class_,
                        Naive_Logical_t *const is_subclass);

/* Naive_Curve */

Naive_API Naive_Code_t Naive_Curve_ask_bound(Naive_Curve_t curve,
                                             Naive_Interval_t *const bound);

Naive_API Naive_Code_t Naive_Curve_eval(Naive_Curve_t curve, double t,
                                        int n_deriv, Naive_Vec3d_t p[]);

Naive_API Naive_Code_t Naive_Curve_eval_curvature(
    Naive_Curve_t curve, double t, Naive_Vec3d_t *const curvature);

Naive_API Naive_Code_t Naive_Curve_make_wire_body(
    int n_curves, const Naive_Curve_t curves[], const Naive_Interval_t bounds[],
    const Naive_Curve_make_wire_body_o_t *options, Naive_Body_t *const body,
    int *const n_new_edges, Naive_Edge_t **const new_edges,
    int **const edge_index);

/* Naive_Geom2dAPI */

/**
 * @brief This function calculates the convex hull of a set of 2d points.
 *
 * @param n_points [I] Number of points.
 * @param points [I] Points.
 * @param algo [I] Algorithm.
 * @param n_convex_points [O] Number of vertex in the convex hull.
 * @param convex_indices [O] Index of vertex in the convex hull.
 * @param convex_points [O] Convex vertex.
 * @return Code.
 */
Naive_API Naive_Code_t Naive_Geom2dAPI_convex_hull(
    int n_points, const Naive_Pnt2d_t *points, Naive_Algorithm_t algo,
    int *const n_convex_points, int **const convex_indices,
    Naive_Pnt2d_t **const convex_points);

/**
 * @brief This function calculates the enclosing disc of a set of 2d 2d points.
 *
 * @param n_points [I] Number of points.
 * @param points [I] Points.
 * @param origin [O] The origin of the disc.
 * @param radius [O] The radius of the disc.
 * @return Code.
 */
Naive_API Naive_Code_t Naive_Geom2dAPI_enclosing_disc(
    int n_points, const Naive_Pnt2d_t *points, Naive_Pnt2d_t *const origin,
    double *const radius);

/* Naive_Geometry */

Naive_API Naive_Code_t Naive_Geometry_clone(Naive_Geometry_t geometry,
                                            Naive_Geometry_t *const clone);

Naive_API Naive_Code_t Naive_Geometry_is_valid(Naive_Geometry_t geometry,
                                               Naive_Logical_t *const is_valid);

/* Naive_Line */

Naive_API Naive_Code_t Naive_Line_create(const Naive_Line_sf_t *line_sf,
                                         Naive_Line_t *const line);

/* Naive_Memory */

Naive_API Naive_Code_t Naive_Memory_alloc(size_t nbytes, void **const pointer);

Naive_API Naive_Code_t Naive_Memory_free(void *pointer);

/* Naive_NurbsCurve */

/**
 * @brief This function modifies the given 'nurbs_curve' by inserting knots
 * with the quantity of 'mult' at the given split parameter.
 *
 * @param nurbs_curve [I] NURBS curve.
 * @param t [I] Split parameter.
 * @param mult [I] Multiplicity.
 * @return Code.
 */
Naive_API Naive_Code_t Naive_NurbsCurve_add_knot(Naive_NurbsCurve_t nurbs_curve,
                                                 double t, int mult);

/**
 * @brief This function returns the standard form for a NURBS curve.
 *
 * @param nurbs_curve [I] NURBS curve.
 * @param nurbs_curve_sf [O] NURBS curve standard form.
 * @return Code.
 */
Naive_API Naive_Code_t
Naive_NurbsCurve_ask(Naive_NurbsCurve_t nurbs_curve,
                     Naive_NurbsCurve_sf_t *const nurbs_curve_sf);

/**
 * @brief This function returns the uniques knots and the multiplicities of a
 * given NURBS curve.
 *
 * @param nurbs_curve [I] NURBS curve to query.
 * @param n_knots [O] Number of knots.
 * @param knots [O] Knot values.
 * @param multiplicities [O] Corresponding multiplicities.
 * @return Code.
 */
Naive_API Naive_Code_t
Naive_NurbsCurve_ask_knots(Naive_NurbsCurve_t nurbs_curve, int *const n_knots,
                           double **const knots, int **const multiplicities);

/**
 * @brief This function creates a NURBS curve from the standard form.
 *
 * @param nurbs_curve_sf [I] NURBS curve standard form.
 * @param nurbs_curve [O] NURBS curve.
 * @return Code.
 */
Naive_API Naive_Code_t
Naive_NurbsCurve_create(const Naive_NurbsCurve_sf_t *nurbs_curve_sf,
                        Naive_NurbsCurve_t *const nurbs_curve);

/**
 * @brief This function modifies the given 'bcurve' by raising its degree by
 * 'increment'.
 *
 * @param nurbs_curve [I] NURBS curve.
 * @param degree [I] How much to raise by.
 * @return Code.
 */
Naive_API Naive_Code_t
Naive_NurbsCurve_raise_degree(Naive_NurbsCurve_t nurbs_curve, int increment);

/**
 * @brief This function reduces the multiplicity of the knot of index 'index' to
 * 'mult'.
 *
 * @param nurbs_curve [I] NURBS curve.
 * @param index [I] Index of the knot.
 * @param mult [I] Multiplicity to reduce to.
 * @return Code.
 */
Naive_API Naive_Code_t Naive_NurbsCurve_remove_knot(
    Naive_NurbsCurve_t nurbs_curve, int index, int mult);

/* Naive_NurbsSurface */

/**
 * @brief This function returns the standard form for a NURBS surface.
 *
 * @param nurbs_surface [I] NURBS surface.
 * @param nurbs_surface_sf [O] NURBS surface standard form.
 * @return Code.
 */
Naive_API Naive_Code_t
Naive_NurbsSurface_ask(Naive_NurbsSurface_t nurbs_surface,
                       Naive_NurbsSurface_sf_t *const nurbs_surface_sf);

/**
 * @brief This function creates a NURBS surface from the standard form.
 *
 * @param nurbs_surface_sf [I] NURBS surface standard form.
 * @param nurbs_surface [O] NURBS surface.
 * @return Code.
 */
Naive_API Naive_Code_t
Naive_NurbsSurface_create(const Naive_NurbsSurface_sf_t *nurbs_surface_sf,
                          Naive_NurbsSurface_t *const nurbs_surface);

/* Naive_Object */

/**
 * @brief This function returns the given object's concrete class.
 *
 * @param object [I] Object.
 * @param class_ [O] Class of object.
 * @return Code.
 */
Naive_API Naive_Code_t Naive_Object_ask_class(Naive_Object_t object,
                                              Naive_Class_t *const class_);

/**
 * @brief This function deletes the given object.
 *
 * @param object [I] Object.
 * @return Code.
 */
Naive_API Naive_Code_t Naive_Object_delete(Naive_Object_t object);

/* Naive_Plane */

Naive_API Naive_Code_t Naive_Plane_ask(Naive_Plane_t plane,
                                       Naive_Plane_sf_t *const plane_sf);

Naive_API Naive_Code_t Naive_Plane_create(const Naive_Plane_sf_t *plane_sf,
                                          Naive_Plane_t *const plane);

Naive_API Naive_Code_t Naive_Plane_distance(Naive_Plane_t plane,
                                            const Naive_Pnt3d_t *point,
                                            double *const distance);

/* Naive_Surface */

Naive_API Naive_Code_t Naive_Surface_eval(Naive_Surface_t surface, double u,
                                          double v, int n_u_deriv,
                                          int n_v_deriv, Naive_Vec3d_t p[]);

/* Naive_Tessellation */

/**
 * @brief This function creates a triangulated sphere with tetrahedral pattern.
 *
 * @param center [I] Center of the sphere.
 * @param radius [I] Radius of the sphere.
 * @param level [I] Tessellation level.
 * @param triangulation [O] The tetrsphere.
 * @return Code.
 */
Naive_API Naive_Code_t Naive_Tessellation_create_tetrasphere(
    const Naive_Pnt3d_t *center, double radius, int level,
    Naive_Triangulation_t *const triangulation);

/* Naive_Triangulation */

Naive_API Naive_Code_t Naive_Triangulation_ask_triangles(
    Naive_Triangulation_t triangulation, int *const n_triangles,
    Naive_Triangle_t **const triangles);

Naive_API Naive_Code_t Naive_Triangulation_ask_vertices(
    Naive_Triangulation_t triangulation, int *const n_vertices,
    Naive_Pnt3d_t **const vertices);

Naive_API Naive_Code_t Naive_Triangulation_create(
    int n_vertices, const Naive_Pnt3d_t *vertices, int n_triangles,
    const Naive_Triangle_t *triangles, int i_offset,
    Naive_Triangulation_t *const triangulation);

/* Naive_Vertex */

/**
 * @brief This function attaches points to vertices.
 *
 * @param n_vertices [I] Number of vertices.
 * @param vertices [I] Vertices to have points attached.
 * @param points [I] Points to be attached to vertices.
 * @return Code.
 */
Naive_API Naive_Code_t
Naive_Vertex_attach_points(int n_vertices, const Naive_Vertex_t vertices[],
                           const Naive_Pnt3d_t points[]);

#undef Naive_API

#endif
