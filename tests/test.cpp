#include <naivecgl/Tessellation/Sphere.h>

#include <gtest/gtest.h>

TEST(HalfEdgeMesh, CreateHalfEdgeMeshFromTriangleSoup) {
  std::vector<Naive_Vector3d> vertices = {
      {0., 0., 1.},  {-1., -1., 0.}, {-1., 1., 0.},
      {1., -1., 0.}, {1., 1., 0.},   {0., 0., -1.},
  };

  std::vector<Naive_Vector3i> triangles = {
      {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4, 1},
      {5, 1, 2}, {5, 2, 3}, {5, 3, 4}, {5, 4, 1},
  };

  Naive_Poly3D soup(std::move(vertices), std::move(triangles));

  ASSERT_TRUE(soup.isValid());

  Naive_Mesh3D mesh(soup);
}

TEST(Sphere, CreateOctasphere) {
  Naive_H_Poly3D sphere = naivecgl::tessellation::octasphere({3, 4, 5}, 10);

  ASSERT_EQ(15, sphere->vertices().size());
  ASSERT_EQ(16, sphere->triangles().size());

  ASSERT_EQ(15, sphere->vertices().capacity());
  ASSERT_EQ(16, sphere->triangles().capacity());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
