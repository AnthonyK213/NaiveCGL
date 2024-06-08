#include <naivecgl/BndShape/ConvexHull2D.h>
#include <naivecgl/BndShape/EnclosingDisc.h>
#include <naivecgl/Geometry/HalfEdgeMesh.h>
#include <naivecgl/Math/Polynomial.h>
#include <naivecgl/Tessellation/Sphere.h>

#include <naivecgl/Interface/NaiveCGL_c.h>

#include <gtest/gtest.h>

TEST(NaiveCGL_HalfEdgeMesh, CreateHalfEdgeMeshFromTriangleSoup) {
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

TEST(NaiveCGL_Sphere, CreateOctasphere) {
  Handle_Naive_Poly sphere =
      ::naivecgl::tessellation::OctaSphere({3, 4, 5}, 10);

  ASSERT_EQ(36, sphere->Vertices().size());
  ASSERT_EQ(49, sphere->Triangles().size());

  ASSERT_EQ(36, sphere->Vertices().capacity());
  ASSERT_EQ(49, sphere->Triangles().capacity());
}

TEST(NaiveCGL_ConvexHull2D, GetHull) {
  Naive_Point2dList points{
      {0, 2}, {1, 3}, {2, 2}, {2, 0}, {3, 1}, {3, 4}, {4, 2}, {4, 3},
  };

  ::naivecgl::bndshape::ConvexHull2D aCH2d{points};
  aCH2d.Perform();

  Naive_Code code = aCH2d.Status();
  ASSERT_EQ(Naive_Code_ok, code);

  Naive_IntegerList answer{0, 3, 4, 6, 7, 5, 1};
  ASSERT_EQ(answer, aCH2d.ConvexIndices());
}

TEST(NaiveCGL_EnclosingDisc, GetDisc) {
  Naive_Point2dList points{
      {0, 2}, {1, 3}, {2, 2}, {2, 0}, {3, 1}, {3, 4}, {4, 2}, {4, 3},
  };

  ::naivecgl::bndshape::EnclosingDisc aDisc{};
  aDisc.ReBuild(points);

  Naive_Point2d anOrigin{};
  Naive_Real aR{};

  ASSERT_TRUE(aDisc.Circle(anOrigin, aR));
}

TEST(NaiveCGL_Math, Polynomial) {
  naivecgl::math::Polynomial aP({3, 1, 4, 1, 5, 9});
  ASSERT_EQ(5, aP.Degree());
  ASSERT_DOUBLE_EQ(397, aP.Evaluate(2));
  auto aP_3 = aP.Derivative(3);
  ASSERT_TRUE(aP_3.IsEqual(naivecgl::math::Polynomial({6, 120, 540})));

  naivecgl::math::Polynomial aP1({2, 1});
  auto aP2 = aP.Multiplied(aP1);
  ASSERT_TRUE(aP2.IsEqual(naivecgl::math::Polynomial({6, 5, 9, 6, 11, 23, 9})));
}

TEST(NaiveCGL_CAPI, Geometry) {
  Naive_Code_t code = Naive_Code_ok;

  Naive_Plane_t plane_sf;
  plane_sf.basis_set.location.x = 0.;
  plane_sf.basis_set.location.y = 0.;
  plane_sf.basis_set.location.z = 0.;
  plane_sf.basis_set.ref_direction.x = 1.;
  plane_sf.basis_set.ref_direction.y = 0.;
  plane_sf.basis_set.ref_direction.z = 0.;
  plane_sf.basis_set.axis.x = 0.;
  plane_sf.basis_set.axis.y = 0.;
  plane_sf.basis_set.axis.z = 1.;

  Naive_Handle_t plane;
  code = Naive_Plane_new(&plane_sf, &plane);
  ASSERT_EQ(Naive_Code_ok, code);

  Naive_Handle_t plane_clone;
  code = Naive_Geometry_clone(plane, &plane_clone);
  ASSERT_EQ(Naive_Code_ok, code);

  Naive_Logical_t is_valid;
  code = Naive_Geometry_is_valid(plane_clone, &is_valid);
  ASSERT_EQ(Naive_Code_ok, code);
  ASSERT_TRUE(is_valid);

  Naive_Plane_t plane_sf_2;
  code = Naive_Plane_ask(plane_clone, &plane_sf_2);
  ASSERT_EQ(Naive_Code_ok, code);
  ASSERT_DOUBLE_EQ(1., plane_sf_2.basis_set.axis.z);

  ASSERT_EQ(Naive_Code_invalid_handle, Naive_Plane_ask(nullptr, &plane_sf_2));

  ASSERT_EQ(Naive_Code_ok, Naive_Transient_release(plane));
  ASSERT_EQ(Naive_Code_ok, Naive_Transient_release(plane_clone));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
