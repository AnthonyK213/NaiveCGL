#pragma once

#include <gtest/gtest.h>
#include <naivecgl/Tessellation/Sphere.h>

TEST(NaiveCGLTest_Tessellation, Create_Octasphere) {
  Handle_Naive_Poly sphere =
      ::naivecgl::tessellation::OctaSphere({3, 4, 5}, 10);

  ASSERT_EQ(36, sphere->Vertices().size());
  ASSERT_EQ(49, sphere->Triangles().size());

  ASSERT_EQ(36, sphere->Vertices().capacity());
  ASSERT_EQ(49, sphere->Triangles().capacity());
}
