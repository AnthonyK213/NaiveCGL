#include <naivecgl/BndShape/ConvexHull2D.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t
Naive_BndShape_ConvexHull2D_new(int n_points, const Naive_Point2d_t *points,
                                Naive_Algorithm_t algo,
                                Naive_ConvexHull2D_t *const convex_hull_2d) {
  if (!points || !convex_hull_2d)
    return Naive_Code_null_arg_address;

  if (n_points < 0)
    return Naive_Code_err;

  Naive_Pnt2dList1 aPoints(n_points);
  for (Naive_Integer i = 0; i < n_points; ++i) {
    aPoints[i] = points[i];
  }

  Naive_Handle<::naivecgl::bndshape::ConvexHull2D> aCH2D =
      new ::naivecgl::bndshape::ConvexHull2D(
          ::std::move(aPoints), static_cast<Naive_Algorithm>(algo));
  aCH2D->IncrementRefCounter();
  *convex_hull_2d = aCH2D.get();
  return Naive_Code_ok;
}

Naive_Code_t
Naive_BndShape_ConvexHull2D_set_algorithm(Naive_ConvexHull2D_t convex_hull_2d,
                                          Naive_Algorithm_t algo) {
  Naive_H_CAST_AND_CHECK(::naivecgl::bndshape::ConvexHull2D, convex_hull_2d, H);
  H->SetAlgorithm(static_cast<Naive_Algorithm>(algo));
  return H->Status();
}

Naive_Code_t
Naive_BndShape_ConvexHull2D_perform(Naive_ConvexHull2D_t convex_hull_2d) {
  Naive_H_CAST_AND_CHECK(::naivecgl::bndshape::ConvexHull2D, convex_hull_2d, H);
  H->Perform();
  return H->Status();
}

Naive_Code_t
Naive_BndShape_ConvexHull2D_add_point(Naive_ConvexHull2D_t convex_hull_2d,
                                      Naive_Point2d_t point,
                                      Naive_Logical_t to_perform) {
  Naive_H_CAST_AND_CHECK(::naivecgl::bndshape::ConvexHull2D, convex_hull_2d, H);
  H->Add(point, to_perform);
  return H->Status();
}

Naive_Code_t Naive_BndShape_ConvexHull2D_ask_result(
    const Naive_ConvexHull2D_t convex_hull_2d, int *const n_convex_points,
    int *const convex_indices, Naive_Point2d_t *const convex_points) {
  if (!n_convex_points)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const ::naivecgl::bndshape::ConvexHull2D,
                         convex_hull_2d, H);
  if (H->Status() != Naive_Code_ok)
    return H->Status();

  *n_convex_points = H->NbConvexPoints();

  if (convex_indices) {
    Naive_IntegerList1 anIndices = H->ConvexIndices();
    ::std::copy(anIndices.cbegin(), anIndices.cend(), convex_indices);
  }

  if (convex_points) {
    Naive_Pnt2dList1 aPoints = H->ConvexPoints();
    for (Naive_Integer i = 0; i < aPoints.size(); ++i) {
      aPoints[i].Dump(convex_points[i]);
    }
  }

  return Naive_Code_ok;
}
