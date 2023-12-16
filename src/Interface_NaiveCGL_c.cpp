#include <naivecgl/Interface/NaiveCGL_c.h>
#include <naivecgl/Math/Constants.h>

/// Naive_Poly {{{

int32_t Naive_Poly_NbVertices(const Naive_Poly *handle) {
  if (!handle)
    return 0;

  return static_cast<int32_t>(handle->vertices().size());
}

void Naive_Poly_Vertices(const Naive_Poly *handle, Naive_Point3d_T *vertices) {
  if (!handle || !vertices)
    return;

  size_t nbVertices = handle->vertices().size();

  for (size_t i = 0; i < nbVertices; ++i) {
    const Naive_Point3d &vertex = handle->vertices()[i];
    vertices[i].x = vertex(0);
    vertices[i].y = vertex(1);
    vertices[i].z = vertex(2);
  }
}

int32_t Naive_Poly_NbTriangles(const Naive_Poly *handle) {
  if (!handle)
    return 0;

  return static_cast<int32_t>(handle->triangles().size());
}

void Naive_Poly_Triangles(const Naive_Poly *handle,
                          Naive_Triangle_T *triangles) {
  if (!handle || !triangles)
    return;

  size_t nbTriangles = handle->triangles().size();

  for (size_t i = 0; i < nbTriangles; ++i) {
    const Naive_Triangle &triangle = handle->triangles()[i];
    triangles[i].n0 = triangle(0);
    triangles[i].n1 = triangle(1);
    triangles[i].n2 = triangle(2);
  }
}

void Naive_Poly_Release(Naive_Poly *handle) { delete handle; }

/// }}}

/// BndShape {{{

Naive_Code Naive_BndShape_ConvexHull2D(const Naive_Point2d_T *points,
                                       int32_t *count,
                                       int32_t **convexIndices) {
  if (!points || !count || *count < 0 || !convexIndices)
    return Naive_Fail;

  int32_t nbPoints = *count;
  Naive_List<Naive_Point2d> aPoints(nbPoints);

  for (int32_t i = 0; i < nbPoints; ++i) {
    aPoints[i](0) = points[i].x;
    aPoints[i](1) = points[i].y;
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

Naive_Poly *Naive_Tessellation_Tetrasphere(const Naive_Point3d_T *center,
                                           double radius, int32_t level) {
  if (!center || radius <= naivecgl::math::ZeroTolerance || level < 0)
    return nullptr;

  Naive_Point3d aCenter{center->x, center->y, center->z};

  auto poly = naivecgl::tessellation::tetrasphere(aCenter, radius, level);

  if (poly.get() == nullptr)
    return nullptr;

  Naive_Poly *result = new Naive_Poly(std::move(*poly.get()));

  return result;
}

/// }}}

/// Release {{{

void Naive_Release_Int32Array(int32_t *array) { delete[] array; }

void Naive_Release_DoubleArray(double *array) { delete[] array; }

/// }}}

// vim: set foldmarker={{{,}}} foldmethod=marker foldlevel=0:
