#include <naivecgl/Geom2dAPI/ConvexHull.h>
#include <naivecgl/Geom2dAPI/EnclosingDisc.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Geom2dAPI_convex_hull(int n_points,
                                         const Naive_Pnt2d_t *points,
                                         Naive_Algorithm_t algo,
                                         int *const n_convex_points,
                                         int **const convex_indices,
                                         Naive_Pnt2d_t **const convex_points) {
  if (!points || !n_convex_points)
    return Naive_Code_null_arg_address;

  if (n_points < 0)
    return Naive_Code_insufficient_points;

  Naive_Pnt2dList1 aPoints(points, points + n_points);
  ::naivecgl::geom2dapi::ConvexHull CH{::std::move(aPoints),
                                       static_cast<Naive_Algorithm>(algo)};

  CH.Perform();

  Naive_CHECK_CODE(CH.Status());

  *n_convex_points = CH.NbConvexPoints();

  if (convex_indices) {
    Naive_IntegerList1 anIndices = CH.ConvexIndices();
    Naive_ALLOC_ARRAY(int, anIndices.size(), convex_indices);
    ::std::copy(anIndices.cbegin(), anIndices.cend(), *convex_indices);
  }

  if (convex_points) {
    Naive_Pnt2dList1 aPoints = CH.ConvexPoints();
    Naive_ALLOC_ARRAY(Naive_Pnt2d_t, aPoints.size(), convex_points);
    for (Naive_Integer i = 0; i < aPoints.size(); ++i) {
      aPoints[i].Dump((*convex_points)[i]);
    }
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_Geom2dAPI_enclosing_disc(int n_points,
                                            const Naive_Pnt2d_t *points,
                                            Naive_Pnt2d_t *const origin,
                                            double *const radius) {
  if (!points || !origin || !radius)
    return Naive_Code_null_arg_address;

  if (n_points < 0)
    return Naive_Code_insufficient_points;

  Naive_Pnt2dList1 aPoints(points, points + n_points);

  ::naivecgl::geom2dapi::EnclosingDisc ED{};
  ED.ReBuild(aPoints);

  Naive_Pnt2d O;
  if (!ED.Result(O, *radius))
    return Naive_Code_err;

  O.Dump(*origin);

  return Naive_Code_ok;
}
