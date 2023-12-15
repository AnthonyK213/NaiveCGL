#include <naivecgl/Interface/NaiveCGL_c.h>

/// BndShape {{{

Naive_Code Naive_BndShape_ConvexHull2D(const double *points, int32_t *count,
                                       int32_t **convexIndices) {
  if (!points || !count || *count < 0 || !convexIndices)
    return Naive_Fail;

  int32_t nbPoints = *count;
  Naive_List<Naive_Point2d> aPoints(nbPoints);

  for (int i = 0; i < nbPoints; ++i) {
    aPoints[i](0) = points[i * 2];
    aPoints[i](1) = points[i * 2 + 1];
  }

  Naive_List<Naive_Integer> aConvexIndices{};
  Naive_Code aCode = naivecgl::bndshape::convexHull2D(aPoints, aConvexIndices);

  if (aCode == Naive_Ok) {
    int32_t *result = new int32_t[aConvexIndices.size()];
    std::copy(aConvexIndices.cbegin(), aConvexIndices.cend(), result);
    *count = static_cast<int32_t>(aConvexIndices.size());
    *convexIndices = result;
  }

  return aCode;
}

/// }}}

/// Tessellation {{{

/// }}}

/// Release {{{

void Naive_Release_OpaqueArray(void *array) { delete[] array; }

/// }}}

// vim: set foldmarker={{{,}}} foldmethod=marker foldlevel=0:
