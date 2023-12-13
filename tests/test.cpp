#include <naivecgl/Tessellation/Sphere.h>

#include <gtest/gtest.h>

TEST(HalfEdgeMesh, CreateHalfEdgeMeshFromTriangleSoup) {
  Naive_List<Naive_Vector3d> vertices = {
      {0., 0., 1.},  {-1., -1., 0.}, {-1., 1., 0.},
      {1., -1., 0.}, {1., 1., 0.},   {0., 0., -1.},
  };

  Naive_List<Naive_Triangle> triangles = {
      {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4, 1},
      {5, 1, 2}, {5, 2, 3}, {5, 3, 4}, {5, 4, 1},
  };

  Naive_Poly soup(std::move(vertices), std::move(triangles));

  ASSERT_TRUE(soup.isValid());

  Naive_Mesh mesh(soup);
}

TEST(Sphere, CreateOctasphere) {
  Naive_H_Poly sphere = naivecgl::tessellation::octasphere({3, 4, 5}, 10);

  ASSERT_EQ(36, sphere->vertices().size());
  ASSERT_EQ(49, sphere->triangles().size());

  ASSERT_EQ(36, sphere->vertices().capacity());
  ASSERT_EQ(49, sphere->triangles().capacity());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
