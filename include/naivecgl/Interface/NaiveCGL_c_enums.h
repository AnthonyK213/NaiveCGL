#ifndef _NAIVECGL_C_ENUMS_H
#define _NAIVECGL_C_ENUMS_H

/* Naive_Algorithm */

typedef enum {
  Naive_Algorithm_quick_hull_c = 0,
  Naive_Algorithm_incremental_c,
  Naive_Algorithm_graham_scan_c,
  Naive_Algorithm_divide_and_conquer_c,
} Naive_Algorithm;

/* Naive_Class */

typedef enum {
  Naive_Class_null = 0,
  Naive_Class_class,
  Naive_Class_object,
  Naive_Class_geometry2d,
  Naive_Class_point2d,
  Naive_Class_cartesian_point2d,
  Naive_Class_vector2d,
  Naive_Class_curve2d,
  Naive_Class_bounded_curve2d,
  Naive_Class_nurbs_curve2d,
  Naive_Class_trimmed_curve2d,
  Naive_Class_conic2d,
  Naive_Class_circle2d,
  Naive_Class_ellipse2d,
  Naive_Class_hyperbola2d,
  Naive_Class_parabola2d,
  Naive_Class_line2d,
  Naive_Class_offset_curve2d,
  Naive_Class_geometry,
  Naive_Class_point3d,
  Naive_Class_cartesian_point3d,
  Naive_Class_vector3d,
  Naive_Class_transform3d,
  Naive_Class_curve,
  Naive_Class_bounded_curve,
  Naive_Class_nurbs_curve,
  Naive_Class_trimmed_curve,
  Naive_Class_conic,
  Naive_Class_circle,
  Naive_Class_ellipse,
  Naive_Class_hyperbola,
  Naive_Class_parabola,
  Naive_Class_line,
  Naive_Class_offset_curve,
  Naive_Class_surface,
  Naive_Class_bounded_surface,
  Naive_Class_nurbs_surface,
  Naive_Class_rectangular_trimmed_surface,
  Naive_Class_elementary_surface,
  Naive_Class_conical_surface,
  Naive_Class_cylindrical_surface,
  Naive_Class_spherical_surface,
  Naive_Class_toroidal_surface,
  Naive_Class_plane,
  Naive_Class_offset_surface,
  Naive_Class_mesh,
  Naive_Class_triangulation,
  Naive_Class_point_rep,
  Naive_Class_point_on_curve,
  Naive_Class_point_on_surface,
  Naive_Class_curve_rep,
  Naive_Class_curve_on_surface,
  Naive_Class_topol,
  Naive_Class_body,
  Naive_Class_region,
  Naive_Class_shell,
  Naive_Class_face,
  Naive_Class_loop,
  Naive_Class_fin,
  Naive_Class_edge,
  Naive_Class_vertex,
} Naive_Class;

/* Naive_Code */

typedef enum {
  Naive_Code_ok = 0,
  Naive_Code_err,
  Naive_Code_not_implemented,
  Naive_Code_initialized,
  Naive_Code_null_arg_address,
  Naive_Code_invalid_value,
  Naive_Code_invalid_object,
  Naive_Code_invalid_tag,
  Naive_Code_still_referenced,
  Naive_Code_no_intersection,
  Naive_Code_points_are_collinear,
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
  Naive_Code_bad_dimension,
  Naive_Code_bad_knots,
  Naive_Code_poles_weights_not_match,
  Naive_Code_knots_mults_not_match,
  Naive_Code_invalid_mults,
  Naive_Code_geom_not_needed,
  Naive_Code_fin_not_in_loop,
  Naive_Code_fins_not_distinct,
  Naive_Code_edge_not_manifold,
  Naive_Code_vertex_not_manifold,
  Naive_Code_no_common_vertex,
} Naive_Code;

/* Naive_Loop_type */

typedef enum {
  Naive_Loop_type_vertex_c = 0,
  Naive_Loop_type_outer_c,
  Naive_Loop_type_inner_c,
} Naive_Loop_type;

/* Naive_NurbsCurve_form */

typedef enum {
  Naive_NurbsCurve_form_unset_c = 0,
  Naive_NurbsCurve_form_arbitrary_c,
  Naive_NurbsCurve_form_polyline_c,
  Naive_NurbsCurve_form_circular_c,
  Naive_NurbsCurve_form_elliptic_c,
  Naive_NurbsCurve_form_parabolic_c,
  Naive_NurbsCurve_form_hyperbolic_c,
} Naive_NurbsCurve_form;

/* Naive_NurbsSurface_form */

typedef enum {
  Naive_NurbsSurface_form_unset_c = 0,
  Naive_NurbsSurface_form_arbitrary_c,
  Naive_NurbsSurface_form_planar_c,
  Naive_NurbsSurface_form_cylindrical_c,
  Naive_NurbsSurface_form_conical_c,
  Naive_NurbsSurface_form_spherical_c,
  Naive_NurbsSurface_form_toroidal_c,
  Naive_NurbsSurface_form_revolved_c,
  Naive_NurbsSurface_form_ruled_c,
  Naive_NurbsSurface_form_gen_cone_c,
  Naive_NurbsSurface_form_quadric_c,
  Naive_NurbsSurface_form_swept_c,
} Naive_NurbsSurface_form;

/* Naive_Orientation */

typedef enum {
  Naive_Orientation_forward_c = 0,
  Naive_Orientation_reversed_c,
  Naive_Orientation_internal_c,
  Naive_Orientation_external_c,
} Naive_Orientation;

/* Naive_boolean_function */

typedef enum {
  Naive_boolean_intersect_c = 0,
  Naive_boolean_subtract_c,
  Naive_boolean_unite_c,
} Naive_boolean_function;

#endif
