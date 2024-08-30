#pragma once

#include <gtest/gtest.h>
#include <naivecgl/Interface/NaiveCGL_c.h>

TEST(NaiveCGLTest_Interface, Plane) {
  Naive_Plane_sf_t plane_sf;
  plane_sf.basis_set.location.x = 0.;
  plane_sf.basis_set.location.y = 0.;
  plane_sf.basis_set.location.z = 0.;
  plane_sf.basis_set.ref_direction.x = 1.;
  plane_sf.basis_set.ref_direction.y = 0.;
  plane_sf.basis_set.ref_direction.z = 0.;
  plane_sf.basis_set.axis.x = 0.;
  plane_sf.basis_set.axis.y = 0.;
  plane_sf.basis_set.axis.z = 1.;

  Naive_Plane_t plane = Naive_Object_null;
  ASSERT_EQ(Naive_Code_ok, Naive_Plane_create(&plane_sf, &plane));

  Naive_Plane_t plane_clone = Naive_Object_null;
  ASSERT_EQ(Naive_Code_ok, Naive_Geometry_clone(plane, &plane_clone));

  Naive_Logical_t is_valid;
  ASSERT_EQ(Naive_Code_ok, Naive_Geometry_is_valid(plane_clone, &is_valid));
  ASSERT_EQ(Naive_Logical_true, is_valid);

  Naive_Plane_sf_t plane_sf_2;
  ASSERT_EQ(Naive_Code_ok, Naive_Plane_ask(plane_clone, &plane_sf_2));
  ASSERT_DOUBLE_EQ(1., plane_sf_2.basis_set.axis.z);

  ASSERT_EQ(Naive_Code_invalid_tag, Naive_Plane_ask(0, &plane_sf_2));

  Naive_Class_t plane_class;
  ASSERT_EQ(Naive_Code_ok, Naive_Object_ask_class(plane, &plane_class));
  ASSERT_EQ(Naive_Class_plane, plane_class);

  Naive_Logical_t is_subclass;
  ASSERT_EQ(Naive_Code_ok, Naive_Class_is_subclass(
                               plane_class, Naive_Class_surface, &is_subclass));
  ASSERT_EQ(Naive_Logical_true, is_subclass);
  ASSERT_EQ(Naive_Code_ok,
            Naive_Class_is_subclass(plane_class, Naive_Class_nurbs_surface,
                                    &is_subclass));
  ASSERT_EQ(Naive_Logical_false, is_subclass);

  ASSERT_EQ(Naive_Code_ok, Naive_Object_delete(plane));
  ASSERT_EQ(Naive_Code_ok, Naive_Object_delete(plane_clone));
  ASSERT_EQ(Naive_Code_invalid_tag, Naive_Object_delete(plane_clone));
}

TEST(NaiveCGLTest_Interface, ConvexHull) {
  ::std::vector<Naive_Pnt2d_t> points{
      {0, 2}, {1, 3}, {2, 2}, {2, 0}, {3, 1}, {3, 4}, {4, 2}, {4, 3},
  };

  int n, *ci;
  Naive_Pnt2d_t *cp;
  ASSERT_EQ(Naive_Code_ok, Naive_Geom2dAPI_convex_hull(
                               points.size(), points.data(),
                               Naive_Algorithm_quick_hull_c, &n, &ci, &cp));

  ASSERT_EQ(7, n);
  ASSERT_EQ(4, ci[2]);

  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(ci));
  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(cp));
}

TEST(NaiveCGLTest_Interface, EnclosingDisc) {
  ::std::vector<Naive_Pnt2d_t> aPnts = {
      {0, 2}, {1, 3}, {2, 2}, {2, 0}, {3, 1}, {3, 4}, {4, 2}, {4, 3},
  };

  Naive_Pnt2d_t o;
  double r;
  ASSERT_EQ(Naive_Code_ok,
            Naive_Geom2dAPI_enclosing_disc(aPnts.size(), aPnts.data(), &o, &r));
}

TEST(NaiveCGLTest_Interface, Curve2d) {
  double s = sqrt(0.5);
  double s10 = s * 10.0;

  /* NURBS circle. */

  ::std::vector<double> vertex{10.0, 0.0,  1.0,  s10,  s10, s,     0.0,
                               10.0, 1.0,  -s10, s10,  s,   -10.0, 0.0,
                               1.0,  -s10, -s10, s,    0.0, -10.0, 1.0,
                               s10,  -s10, s,    10.0, 0.0, 1.0};
  ::std::vector<double> knot{0.0, 0.25, 0.5, 0.75, 1.0};
  ::std::vector<int> knot_mult{3, 2, 2, 2, 3};

  Naive_NurbsCurve_sf_t nurbs_curve_sf;
  nurbs_curve_sf.degree = 2;
  nurbs_curve_sf.vertex_dim = 3;
  nurbs_curve_sf.is_rational = Naive_Logical_true;
  nurbs_curve_sf.n_vertices = vertex.size();
  nurbs_curve_sf.vertex = vertex.data();
  nurbs_curve_sf.n_knots = knot.size();
  nurbs_curve_sf.knot_mult = knot_mult.data();
  nurbs_curve_sf.knot = knot.data();

  Naive_NurbsCurve_t nurbs_curve = Naive_Object_null;
  ASSERT_EQ(Naive_Code_ok,
            Naive_NurbsCurve_create(&nurbs_curve_sf, &nurbs_curve));

  Naive_Class_t curve_class = Naive_Class_null;
  ASSERT_EQ(Naive_Code_ok, Naive_Object_ask_class(nurbs_curve, &curve_class));
  ASSERT_EQ(Naive_Class_nurbs_curve2d, curve_class);

  Naive_NurbsCurve_sf_t ask_result;
  ASSERT_EQ(Naive_Code_ok, Naive_NurbsCurve_ask(nurbs_curve, &ask_result));
  ASSERT_EQ(nurbs_curve_sf.degree, ask_result.degree);
  ASSERT_EQ(nurbs_curve_sf.vertex_dim, ask_result.vertex_dim);
  ASSERT_EQ(nurbs_curve_sf.is_rational, ask_result.is_rational);
  ASSERT_EQ(nurbs_curve_sf.n_vertices, ask_result.n_vertices);
  ASSERT_EQ(nurbs_curve_sf.n_knots, ask_result.n_knots);

  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(ask_result.vertex));
  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(ask_result.knot_mult));
  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(ask_result.knot));

  Naive_Vec3d_t evals[1];
  ASSERT_EQ(Naive_Code_ok, Naive_Curve_eval(nurbs_curve, 0.125, 0, evals));
  ASSERT_FLOAT_EQ(s10, evals[0].x);
  ASSERT_FLOAT_EQ(s10, evals[0].y);
  ASSERT_FLOAT_EQ(0.0, evals[0].z);

  Naive_Vec3d_t curvature;
  ASSERT_EQ(Naive_Code_ok,
            Naive_Curve_eval_curvature(nurbs_curve, 0.6, &curvature));
  double k = sqrt(curvature.x * curvature.x + curvature.y * curvature.y);
  ASSERT_FLOAT_EQ(0.1, k);
}

TEST(NaiveCGLTest_Interface, Curve) {
  ::std::vector<double> vertex{
      -10. * 1.5, 34. * 1.5, 6. * 1.5,  1.5,       -9. * 2.0, 15. * 2.0,
      -6. * 2.0,  2.0,       -6. * 0.5, 20. * 0.5, 1. * 0.5,  0.5,
      0. * 1.1,   26. * 1.1, 2. * 1.1,  1.1,       4. * 0.1,  17. * 0.1,
      -3. * 0.1,  0.1,       10.,       21.,       10.,       1.0,
  };
  ::std::vector<double> knot{0., 1., 2., 3.};
  ::std::vector<int> knot_mult{4, 1, 1, 4};

  Naive_NurbsCurve_sf_t nurbs_curve_sf;
  nurbs_curve_sf.degree = 3;
  nurbs_curve_sf.vertex_dim = 4;
  nurbs_curve_sf.is_rational = Naive_Logical_true;
  nurbs_curve_sf.n_vertices = vertex.size();
  nurbs_curve_sf.vertex = vertex.data();
  nurbs_curve_sf.n_knots = knot.size();
  nurbs_curve_sf.knot_mult = knot_mult.data();
  nurbs_curve_sf.knot = knot.data();

  Naive_NurbsCurve_t nurbs_curve = Naive_Object_null;
  ASSERT_EQ(Naive_Code_ok,
            Naive_NurbsCurve_create(&nurbs_curve_sf, &nurbs_curve));

  Naive_Class_t curve_class = Naive_Class_null;
  ASSERT_EQ(Naive_Code_ok, Naive_Object_ask_class(nurbs_curve, &curve_class));
  ASSERT_EQ(Naive_Class_nurbs_curve, curve_class);

  Naive_NurbsCurve_sf_t ask_result;
  ASSERT_EQ(Naive_Code_ok, Naive_NurbsCurve_ask(nurbs_curve, &ask_result));
  ASSERT_EQ(nurbs_curve_sf.degree, ask_result.degree);
  ASSERT_EQ(nurbs_curve_sf.vertex_dim, ask_result.vertex_dim);
  ASSERT_EQ(nurbs_curve_sf.is_rational, ask_result.is_rational);
  ASSERT_EQ(nurbs_curve_sf.n_vertices, ask_result.n_vertices);
  ASSERT_EQ(nurbs_curve_sf.n_knots, ask_result.n_knots);

  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(ask_result.vertex));
  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(ask_result.knot_mult));
  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(ask_result.knot));

  ASSERT_EQ(Naive_Code_ok, Naive_NurbsCurve_add_knot(nurbs_curve, 0.7, 2));
}

TEST(NaiveCGLTest_Interface, Surface) {
  ::std::vector<double> vertex = {
      15 * 0.3, -10 * 0.3, 3 * 0.3,  0.3, 15 * 1.4, 0 * 1.4,   9 * 1.4,  1.4,
      15 * 2.9, 10 * 2.9,  2 * 2.9,  2.9, 25 * 1.2, -10 * 1.2, 1 * 1.2,  1.2,
      25 * 1.2, 0 * 1.2,   0 * 1.2,  1.2, 25 * 1.2, 10 * 1.2,  -6 * 1.2, 1.2,
      35 * 0.8, -10 * 0.8, -4 * 0.8, 0.8, 35 * 1.1, 0 * 1.1,   1 * 1.1,  1.1,
      35 * 1.8, 10 * 1.8,  5 * 1.8,  1.8};
  ::std::vector<int> u_knot_mult{3, 3};
  ::std::vector<int> v_knot_mult{3, 3};
  ::std::vector<double> u_knot{0., 1.};
  ::std::vector<double> v_knot{0., 1.};

  Naive_NurbsSurface_sf_t nurbs_surface_sf;
  nurbs_surface_sf.u_degree = 2;
  nurbs_surface_sf.v_degree = 2;
  nurbs_surface_sf.vertex_dim = 4;
  nurbs_surface_sf.is_rational = Naive_Logical_true;
  nurbs_surface_sf.n_u_vertices = 12;
  nurbs_surface_sf.n_v_vertices = 12;
  nurbs_surface_sf.vertex = vertex.data();
  nurbs_surface_sf.n_u_knots = u_knot.size();
  nurbs_surface_sf.n_v_knots = v_knot.size();
  nurbs_surface_sf.u_knot_mult = u_knot_mult.data();
  nurbs_surface_sf.v_knot_mult = v_knot_mult.data();
  nurbs_surface_sf.u_knot = u_knot.data();
  nurbs_surface_sf.v_knot = v_knot.data();

  Naive_NurbsSurface_t nurbs_surface = Naive_Object_null;
  ASSERT_EQ(Naive_Code_ok,
            Naive_NurbsSurface_create(&nurbs_surface_sf, &nurbs_surface));

  Naive_Class_t surface_class = Naive_Class_null;
  ASSERT_EQ(Naive_Code_ok,
            Naive_Object_ask_class(nurbs_surface, &surface_class));
  ASSERT_EQ(Naive_Class_nurbs_surface, surface_class);

  Naive_NurbsSurface_sf_t ask_result;
  ASSERT_EQ(Naive_Code_ok, Naive_NurbsSurface_ask(nurbs_surface, &ask_result));
  ASSERT_EQ(nurbs_surface_sf.u_degree, ask_result.u_degree);
  ASSERT_EQ(nurbs_surface_sf.v_degree, ask_result.v_degree);
  ASSERT_EQ(nurbs_surface_sf.vertex_dim, ask_result.vertex_dim);
  ASSERT_EQ(nurbs_surface_sf.is_rational, ask_result.is_rational);
  // ASSERT_EQ(nurbs_surface_sf.n_u_vertices, ask_result.n_u_vertices);
  // ASSERT_EQ(nurbs_surface_sf.n_v_vertices, ask_result.n_v_vertices);
  // ASSERT_EQ(nurbs_surface_sf.n_u_knots, ask_result.n_u_knots);
  // ASSERT_EQ(nurbs_surface_sf.n_v_knots, ask_result.n_v_knots);

  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(ask_result.vertex));
  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(ask_result.u_knot_mult));
  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(ask_result.v_knot_mult));
  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(ask_result.u_knot));
  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(ask_result.v_knot));
}
