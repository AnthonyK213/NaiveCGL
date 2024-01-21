#include <naivecgl/BndShape/ConvexHull2D.h>
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

  ASSERT_TRUE(soup.IsValid());

  Naive_Mesh mesh(soup);
}

TEST(Sphere, CreateOctasphere) {
  Naive_H_Poly sphere = naivecgl::tessellation::OctaSphere({3, 4, 5}, 10);

  ASSERT_EQ(36, sphere->Vertices().size());
  ASSERT_EQ(49, sphere->Triangles().size());

  ASSERT_EQ(36, sphere->Vertices().capacity());
  ASSERT_EQ(49, sphere->Triangles().capacity());
}

TEST(ConvexHull2D, GetHull) {
  Naive_List<Naive_Point2d> points{
      {0, 2}, {1, 3}, {2, 2}, {2, 0}, {3, 1}, {3, 4}, {4, 2}, {4, 3},
  };

  Naive_List<Naive_Integer> result{};
  // Naive_ConvexHull2D_Status code =
  //     naivecgl::bndshape::ConvexHull2D(points, result);

  // ASSERT_EQ(Naive_ConvexHull2D_Done, code);

  // Naive_List<Naive_Integer> answer{0, 3, 4, 6, 7, 5, 1};

  // ASSERT_EQ(answer, result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
