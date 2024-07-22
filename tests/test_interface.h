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
  ASSERT_EQ(Naive_Code_ok, Naive_Plane_new(&plane_sf, &plane));

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
  ::std::vector<Naive_Point2d_t> points{
      {0, 2}, {1, 3}, {2, 2}, {2, 0}, {3, 1}, {3, 4}, {4, 2}, {4, 3},
  };

  int n, *ci;
  Naive_Point2d_t *cp;
  ASSERT_EQ(Naive_Code_ok, Naive_Geom2dAPI_convex_hull(
                               points.size(), points.data(),
                               Naive_Algorithm_quick_hull_c, &n, &ci, &cp));

  ASSERT_EQ(7, n);
  ASSERT_EQ(4, ci[2]);

  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(ci));
  ASSERT_EQ(Naive_Code_ok, Naive_Memory_free(cp));
}

TEST(NaiveCGLTest_Interface, EnclosingDisc) {
  ::std::vector<Naive_Point2d_t> aPnts = {
      {0, 2}, {1, 3}, {2, 2}, {2, 0}, {3, 1}, {3, 4}, {4, 2}, {4, 3},
  };

  Naive_Point2d_t o;
  double r;
  ASSERT_EQ(Naive_Code_ok,
            Naive_Geom2dAPI_enclosing_disc(aPnts.size(), aPnts.data(), &o, &r));
}
