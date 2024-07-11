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

  Naive_Plane_t plane;
  ASSERT_EQ(Naive_Code_ok, Naive_Plane_new(&plane_sf, &plane));

  Naive_Plane_t plane_clone;
  ASSERT_EQ(Naive_Code_ok, Naive_Geometry_clone(plane, &plane_clone));

  Naive_Logical_t is_valid;
  ASSERT_EQ(Naive_Code_ok, Naive_Geometry_is_valid(plane_clone, &is_valid));
  ASSERT_EQ(Naive_Logical_true, is_valid);

  Naive_Plane_sf_t plane_sf_2;
  ASSERT_EQ(Naive_Code_ok, Naive_Plane_ask(plane_clone, &plane_sf_2));
  ASSERT_DOUBLE_EQ(1., plane_sf_2.basis_set.axis.z);

  ASSERT_EQ(Naive_Code_invalid_tag, Naive_Plane_ask(0, &plane_sf_2));

  ASSERT_EQ(Naive_Code_ok, Naive_Object_delete(plane));
  ASSERT_EQ(Naive_Code_ok, Naive_Object_delete(plane_clone));
  ASSERT_EQ(Naive_Code_invalid_tag, Naive_Object_delete(plane_clone));
}

TEST(NaiveCGLTest_Interface, EnclosingDisc) {
  std::vector<Naive_Point2d_t> aPnts = {
      {0, 2}, {1, 3}, {2, 2}, {2, 0}, {3, 1}, {3, 4}, {4, 2}, {4, 3},
  };

  Naive_Point2d_t o;
  double r;
  ASSERT_EQ(Naive_Code_ok,
            Naive_Geom2dAPI_enclosing_disc(aPnts.size(), aPnts.data(), &o, &r));
}
