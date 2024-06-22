#pragma once

#include <gtest/gtest.h>
#include <naivecgl/Geometry/HalfEdgeMesh.h>

TEST(NaiveCGLTest_Geometry, Create_HalfEdgeMesh_From_TriangleSoup) {
  Naive_List<Naive_Point3d> vertices = {
      {0., 0., 1.},  {-1., -1., 0.}, {-1., 1., 0.},
      {1., -1., 0.}, {1., 1., 0.},   {0., 0., -1.},
  };

  Naive_List<Naive_Triangle> triangles = {
      {0, 2, 1}, {0, 4, 2}, {0, 3, 4}, {0, 1, 3},
      {5, 1, 2}, {5, 2, 4}, {5, 4, 3}, {5, 3, 1},
  };

  Naive_Poly soup(::std::move(vertices), ::std::move(triangles));

  ASSERT_TRUE(soup.IsValid());

  Handle_Naive_Mesh mesh = new Naive_Mesh(soup);

  mesh->RemoveVertex(5);
  mesh->RemoveVertex(1);

  Naive_Integer id = mesh->AddVertex({0., 0., -1.});
  mesh->AddFace(id, 2, 4);
  mesh->RemoveFace(2);

  Handle_Naive_Poly poly = mesh->Soup(Naive_True);
}
