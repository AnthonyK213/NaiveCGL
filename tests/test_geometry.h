#pragma once

#include <gtest/gtest.h>
#include <naivecgl/Geometry/Mesh.h>
#include <naivecgl/Geometry/Triangulation.h>

TEST(NaiveCGLTest_Geometry, Create_Mesh_From_Triangulation) {
  Naive_List1<Naive_Pnt3d> vertices = {
      {0., 0., 1.},  {-1., -1., 0.}, {-1., 1., 0.},
      {1., -1., 0.}, {1., 1., 0.},   {0., 0., -1.},
  };

  Naive_List1<Naive_Triangle> triangles = {
      {0, 2, 1}, {0, 4, 2}, {0, 3, 4}, {0, 1, 3},
      {5, 1, 2}, {5, 2, 4}, {5, 4, 3}, {5, 3, 1},
  };

  Handle_Naive_Poly aPoly =
      new Naive_Poly(::std::move(vertices), ::std::move(triangles));

  ASSERT_TRUE(aPoly->IsValid());

  Handle_Naive_Mesh aMesh = new Naive_Mesh(aPoly);

  aMesh->RemoveVertex(5);
  aMesh->RemoveVertex(1);

  Naive_Integer id = aMesh->AddVertex({0., 0., -1.});
  aMesh->AddFace(id, 2, 4);
  aMesh->RemoveFace(2);

  Handle_Naive_Poly aPoly2 = aMesh->GetTriangulation(Naive_True);
}
