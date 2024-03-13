#include <naivecgl/Interface/NaiveCGL_c.h>
#include <naivecgl/Math/Constants.h>

#define Naive_HANDLE_CAST(T, H, N) T *N = static_cast<T *>(H);

/// Naive_Poly {{{

Naive_Handle Naive_Poly_New(const int32_t nbVertices,
                            const Naive_Point3d_T *theVertices,
                            const int32_t nbTriangles,
                            const Naive_Triangle_T *theTriangles) {
  if (nbVertices < 0 || !theVertices || nbTriangles < 0 || !theTriangles)
    return nullptr;

  Naive_Point3d_List aVerts(nbVertices);
  for (int i = 0; i < nbVertices; ++i) {
    aVerts[i] = theVertices[i];
  }

  std::vector<Naive_Triangle> aTris(nbTriangles);
  for (int i = 0; i < nbTriangles; ++i) {
    aTris[i].x() = theTriangles[i].n0;
    aTris[i].y() = theTriangles[i].n1;
    aTris[i].z() = theTriangles[i].n2;
  }

  return new Naive_Poly(std::move(aVerts), std::move(aTris));
}

int32_t Naive_Poly_NbVertices(const Naive_Handle theHandle) {
  if (!theHandle)
    return 0;

  Naive_HANDLE_CAST(const Naive_Poly, theHandle, H);
  return static_cast<int32_t>(H->Vertices().size());
}

void Naive_Poly_Vertices(const Naive_Handle theHandle,
                         Naive_Point3d_T *theVertices) {
  if (!theHandle || !theVertices)
    return;

  Naive_HANDLE_CAST(const Naive_Poly, theHandle, H);
  Naive_Size nbVertices = H->Vertices().size();

  for (Naive_Size i = 0; i < nbVertices; ++i) {
    const Naive_Point3d &aVertex = H->Vertices()[i];
    aVertex.Dump(theVertices[i]);
  }
}

int32_t Naive_Poly_NbTriangles(const Naive_Handle theHandle) {
  if (!theHandle)
    return 0;

  Naive_HANDLE_CAST(const Naive_Poly, theHandle, H);
  return static_cast<int32_t>(H->Triangles().size());
}

void Naive_Poly_Triangles(const Naive_Handle theHandle,
                          Naive_Triangle_T *theTriangles) {
  if (!theHandle || !theTriangles)
    return;

  Naive_HANDLE_CAST(const Naive_Poly, theHandle, H);
  Naive_Size nbTriangles = H->Triangles().size();

  for (Naive_Size i = 0; i < nbTriangles; ++i) {
    const Naive_Triangle &aTriangle = H->Triangles()[i];
    theTriangles[i].n0 = aTriangle(0);
    theTriangles[i].n1 = aTriangle(1);
    theTriangles[i].n2 = aTriangle(2);
  }
}

void Naive_Poly_Release(Naive_Handle theHandle) {
  Naive_HANDLE_CAST(Naive_Poly, theHandle, H);
  delete H;
}

/// }}}

/// BndShape {{{

Naive_Handle
Naive_BndShape_ConvexHull2D_New(const Naive_Point2d_T *thePoints,
                                int32_t nbPoints,
                                Naive_ConvexHull2D_Algorithm theAlgo) {
  if (!thePoints || nbPoints < 0)
    return nullptr;

  Naive_Point2d_List aPoints(nbPoints);

  for (Naive_Integer i = 0; i < nbPoints; ++i) {
    aPoints[i](0) = thePoints[i].x;
    aPoints[i](1) = thePoints[i].y;
  }

  return new naivecgl::bndshape::ConvexHull2D{std::move(aPoints), theAlgo};
}

void Naive_BndShape_ConvexHull2D_SetAlgorithm(
    Naive_Handle theHandle, Naive_ConvexHull2D_Algorithm theAlgo) {
  if (!theHandle)
    return;

  Naive_HANDLE_CAST(naivecgl::bndshape::ConvexHull2D, theHandle, theCH2D);
  theCH2D->SetAlgorithm(theAlgo);
}

void Naive_BndShape_ConvexHull2D_Perform(Naive_Handle theHandle) {
  if (!theHandle)
    return;

  Naive_HANDLE_CAST(naivecgl::bndshape::ConvexHull2D, theHandle, theCH2D);
  theCH2D->Perform();
}

void Naive_BndShape_ConvexHull2D_Add(Naive_Handle theHandle,
                                     Naive_Point2d_T thePoint,
                                     bool thePerform) {
  if (!theHandle)
    return;

  Naive_HANDLE_CAST(naivecgl::bndshape::ConvexHull2D, theHandle, theCH2D);
  theCH2D->Add({thePoint.x, thePoint.y}, thePerform);
}

Naive_ConvexHull2D_Status
Naive_BndShape_ConvexHull2D_Status(const Naive_Handle theHandle) {
  if (!theHandle)
    return Naive_ConvexHull2D_Failed;

  Naive_HANDLE_CAST(const naivecgl::bndshape::ConvexHull2D, theHandle, theCH2D);
  return theCH2D->Status();
}

int32_t
Naive_BndShape_ConvexHull2D_NbConvexPoints(const Naive_Handle theHandle) {
  if (!theHandle)
    return 0;

  Naive_HANDLE_CAST(const naivecgl::bndshape::ConvexHull2D, theHandle, theCH2D);
  return theCH2D->NbConvexPoints();
}

Naive_Code
Naive_BndShape_ConvexHull2D_ConvexIndices(const Naive_Handle theHandle,
                                          int32_t *theConvexIndices) {
  if (!theHandle || !theConvexIndices)
    return Naive_Err;

  Naive_HANDLE_CAST(const naivecgl::bndshape::ConvexHull2D, theHandle, theCH2D);
  Naive_Integer_List anIndices = theCH2D->ConvexIndices();
  std::copy(anIndices.cbegin(), anIndices.cend(), theConvexIndices);

  return Naive_Ok;
}

Naive_Code
Naive_BndShape_ConvexHull2D_ConvexPoints(const Naive_Handle theHandle,
                                         Naive_Point2d_T *theConvexPoints) {
  if (!theHandle || !theConvexPoints)
    return Naive_Err;

  Naive_HANDLE_CAST(const naivecgl::bndshape::ConvexHull2D, theHandle, theCH2D);
  Naive_Point2d_List aPoints = theCH2D->ConvexPoints();

  for (Naive_Integer i = 0; i < aPoints.size(); ++i) {
    theConvexPoints[i].x = aPoints[i].x();
    theConvexPoints[i].y = aPoints[i].y();
  }

  return Naive_Ok;
}

void Naive_BndShape_ConvexHull2D_Release(Naive_Handle theHandle) {
  Naive_HANDLE_CAST(const naivecgl::bndshape::ConvexHull2D, theHandle, theCH2D);
  delete theCH2D;
}

/// }}}

/// Tessellation {{{

Naive_Handle Naive_Tessellation_TetraSphere(const Naive_Point3d_T *theCenter,
                                            double theRadius,
                                            int32_t theLevel) {
  if (!theCenter || theRadius <= naivecgl::math::ZeroTolerance || theLevel < 0)
    return nullptr;

  Naive_Point3d aCenter{*theCenter};
  auto poly = naivecgl::tessellation::TetraSphere(aCenter, theRadius, theLevel);

  if (poly.get() == nullptr)
    return nullptr;

  return new Naive_Poly(std::move(*poly));
}

/// }}}

/// Release {{{

void Naive_Release_Int32Array(int32_t *theArray) { delete[] theArray; }

void Naive_Release_DoubleArray(double *theArray) { delete[] theArray; }

/// }}}

// vim: set foldmarker={{{,}}} foldmethod=marker foldlevel=0:
