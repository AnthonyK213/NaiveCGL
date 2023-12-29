#include <naivecgl/Interface/NaiveCGL_c.h>
#include <naivecgl/Math/Constants.h>

/// Naive_Poly {{{

int32_t Naive_Poly_NbVertices(const Naive_Poly *theHandle) {
  if (!theHandle)
    return 0;

  return static_cast<int32_t>(theHandle->Vertices().size());
}

void Naive_Poly_Vertices(const Naive_Poly *theHandle,
                         Naive_Point3d_T *theVertices) {
  if (!theHandle || !theVertices)
    return;

  size_t nbVertices = theHandle->Vertices().size();

  for (size_t i = 0; i < nbVertices; ++i) {
    const Naive_Point3d &aVertex = theHandle->Vertices()[i];
    theVertices[i].x = aVertex(0);
    theVertices[i].y = aVertex(1);
    theVertices[i].z = aVertex(2);
  }
}

int32_t Naive_Poly_NbTriangles(const Naive_Poly *theHandle) {
  if (!theHandle)
    return 0;

  return static_cast<int32_t>(theHandle->Triangles().size());
}

void Naive_Poly_Triangles(const Naive_Poly *theHandle,
                          Naive_Triangle_T *theTriangles) {
  if (!theHandle || !theTriangles)
    return;

  size_t nbTriangles = theHandle->Triangles().size();

  for (size_t i = 0; i < nbTriangles; ++i) {
    const Naive_Triangle &aTriangle = theHandle->Triangles()[i];
    theTriangles[i].n0 = aTriangle(0);
    theTriangles[i].n1 = aTriangle(1);
    theTriangles[i].n2 = aTriangle(2);
  }
}

void Naive_Poly_Release(Naive_Poly *theHandle) { delete theHandle; }

/// }}}

/// BndShape {{{

Naive_Code Naive_BndShape_ConvexHull2D(const Naive_Point2d_T *thePoints,
                                       int32_t *theCount,
                                       int32_t **theConvexIndices) {
  if (!thePoints || !theCount || *theCount < 0 || !theConvexIndices)
    return Naive_Fail;

  int32_t nbPoints = *theCount;
  Naive_List<Naive_Point2d> aPoints(nbPoints);

  for (int32_t i = 0; i < nbPoints; ++i) {
    aPoints[i](0) = thePoints[i].x;
    aPoints[i](1) = thePoints[i].y;
  }

  Naive_List<Naive_Integer> aConvexIndices{};
  Naive_Code aCode = naivecgl::bndshape::ConvexHull2D(aPoints, aConvexIndices);

  if (aCode == Naive_Ok) {
    int32_t *result = new int32_t[aConvexIndices.size()];
    std::copy(aConvexIndices.cbegin(), aConvexIndices.cend(), result);
    *theCount = static_cast<int32_t>(aConvexIndices.size());
    *theConvexIndices = result;
  }

  return aCode;
}

/// }}}

/// Tessellation {{{

Naive_Poly *Naive_Tessellation_TetraSphere(const Naive_Point3d_T *theCenter,
                                           double theRadius, int32_t theLevel) {
  if (!theCenter || theRadius <= naivecgl::math::ZeroTolerance || theLevel < 0)
    return nullptr;

  Naive_Point3d aCenter{theCenter->x, theCenter->y, theCenter->z};

  auto poly = naivecgl::tessellation::TetraSphere(aCenter, theRadius, theLevel);

  if (poly.get() == nullptr)
    return nullptr;

  Naive_Poly *result = new Naive_Poly(std::move(*poly.get()));

  return result;
}

/// }}}

/// Release {{{

void Naive_Release_Int32Array(int32_t *theArray) { delete[] theArray; }

void Naive_Release_DoubleArray(double *theArray) { delete[] theArray; }

/// }}}

// vim: set foldmarker={{{,}}} foldmethod=marker foldlevel=0:
