#include <Shape/HalfEdgeMesh.hpp>
#include <Shape/TriangleSoup.hpp>

#include <gtest/gtest.h>

using Soup = naivecgl::shape::TriangleSoup<double, int>;
using Mesh = naivecgl::shape::HalfEdgeMesh<double, int>;

TEST(HalfEdgeMesh, CreateHalfEdgeMeshFromTriangleSoup) {
  std::vector<Eigen::Vector3d> vertices = {
      {0., 0., 1.},  {-1., -1., 0.}, {-1., 1., 0.},
      {1., -1., 0.}, {1., 1., 0.},   {0., 0., -1.},
  };

  std::vector<Eigen::Vector3i> triangles = {
      {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4, 1},
      {5, 1, 2}, {5, 2, 3}, {5, 3, 4}, {5, 4, 1},
  };

  Soup soup(std::move(vertices), std::move(triangles));

  ASSERT_TRUE(soup.isValid());

  Mesh mesh(soup);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
