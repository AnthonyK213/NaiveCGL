#pragma once

#include <gtest/gtest.h>
#include <naivecgl/Interface/NaiveCGL_c.h>

TEST(NaiveCGLTest_Interface, Plane) {
  Naive_Code_t code = Naive_Code_ok;

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
  code = Naive_Plane_new(&plane_sf, &plane);
  ASSERT_EQ(Naive_Code_ok, code);

  Naive_Plane_t plane_clone;
  code = Naive_Geometry_clone(plane, &plane_clone);
  ASSERT_EQ(Naive_Code_ok, code);

  Naive_Logical_t is_valid;
  code = Naive_Geometry_is_valid(plane_clone, &is_valid);
  ASSERT_EQ(Naive_Code_ok, code);
  ASSERT_TRUE(is_valid);

  Naive_Plane_sf_t plane_sf_2;
  code = Naive_Plane_ask(plane_clone, &plane_sf_2);
  ASSERT_EQ(Naive_Code_ok, code);
  ASSERT_DOUBLE_EQ(1., plane_sf_2.basis_set.axis.z);

  ASSERT_EQ(Naive_Code_invalid_handle, Naive_Plane_ask(nullptr, &plane_sf_2));

  ASSERT_EQ(Naive_Code_ok, Naive_Object_free(plane));
  ASSERT_EQ(Naive_Code_ok, Naive_Object_free(plane_clone));
}
