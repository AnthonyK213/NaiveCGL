#include <naivecgl/BndShape/ConvexHull2D.h>
#include <naivecgl/BndShape/ConvexHull3D.h>
#include <naivecgl/BndShape/EnclosingDisc.h>
#include <naivecgl/Geometry/Line.h>
#include <naivecgl/Geometry/NurbsCurve.h>
#include <naivecgl/Geometry/NurbsSurface.h>
#include <naivecgl/Geometry/Plane.h>
#include <naivecgl/Interface/NaiveCGL_c.h>
#include <naivecgl/Intersect/Intersection.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Tessellation/Sphere.h>

#define Naive_H_CAST(T, H, N) T *N = reinterpret_cast<T *>(H);

/// Math_Constant {{{

double Naive_Math_Constant_PI(void) { return ::naivecgl::math::Constant::PI(); }

double Naive_Math_Constant_Epsilon(void) {
  return ::naivecgl::math::Constant::Epsilon();
}

double Naive_Math_Constant_MinReal(void) {
  return ::naivecgl::math::Constant::MinReal();
}

double Naive_Math_Constant_MaxReal(void) {
  return ::naivecgl::math::Constant::MaxReal();
}

double Naive_Math_Constant_UnsetReal(void) {
  return ::naivecgl::math::Constant::UnsetReal();
}

// }}}

/// Math_Util {{{

bool Naive_Math_Util_IsValidReal(const double theR) {
  return ::naivecgl::math::Util::IsValidReal(theR);
}

/// }}}

/// Naive_Transient {{{

Naive_Code_t Naive_Transient_Release(Naive_H theHandle) {
  Naive_H_CAST(Naive_Transient, theHandle, H);
  if (H && H->DecrementRefCounter() == 0)
    H->Delete();
  return Naive_Ok;
}

/// }}}

/// Naive_Geometry {{{

Naive_Code_t Naive_Geometry_IsValid(const Naive_H theHandle,
                                    bool *const theIsValid) {
  if (!theIsValid)
    return Naive_NullException;

  Naive_H_CAST(const Naive_Geometry, theHandle, H);
  if (!H)
    return Naive_InvalidHandle;
  *theIsValid = H->IsValid();
  return Naive_Ok;
}

Naive_Code_t Naive_Geometry_Clone(const Naive_H theHandle,
                                  Naive_H *const theClone) {
  if (!theClone)
    return Naive_NullException;

  Naive_H_CAST(const Naive_Geometry, theHandle, H);
  if (!H)
    return Naive_InvalidHandle;
  Handle_Naive_Geometry aClone = H->Clone();
  aClone->IncrementRefCounter();
  *theClone = aClone.get();
  return Naive_Ok;
}

/// }}}

/// Naive_Plane {{{

Naive_Code_t Naive_Plane_New(const Naive_Plane_t *thePlaneT,
                             Naive_H *const thePlane) {
  if (!thePlaneT || !thePlane)
    return Naive_NullException;

  Handle_Naive_Plane aPlane = new Naive_Plane(*thePlaneT);
  aPlane->IncrementRefCounter();
  *thePlane = aPlane.get();
  return Naive_Ok;
}

Naive_Code_t Naive_Plane_Location(const Naive_H theHandle,
                                  Naive_Point3d_t *const theLocation) {
  if (!theLocation)
    return Naive_NullException;

  Naive_H_CAST(const Naive_Plane, theHandle, H);
  if (!H)
    return Naive_InvalidHandle;
  if (!H->Location().Dump(*theLocation))
    return Naive_InvalidValue;
  return Naive_Ok;
}

Naive_Code_t Naive_Plane_XAxis(const Naive_H theHandle,
                               Naive_Point3d_t *const theXAxis) {
  if (!theXAxis)
    return Naive_NullException;

  Naive_H_CAST(const Naive_Plane, theHandle, H);
  if (!H)
    return Naive_InvalidHandle;
  if (!H->XAxis().Dump(*theXAxis))
    return Naive_InvalidValue;
  return Naive_Ok;
}

Naive_Code_t Naive_Plane_YAxis(const Naive_H theHandle,
                               Naive_Point3d_t *const theYAxis) {
  if (!theYAxis)
    return Naive_NullException;

  Naive_H_CAST(const Naive_Plane, theHandle, H);
  if (!H)
    return Naive_InvalidHandle;
  if (!H->YAxis().Dump(*theYAxis))
    return Naive_InvalidValue;
  return Naive_Ok;
}

Naive_Code_t Naive_Plane_Axis(const Naive_H theHandle,
                              Naive_Point3d_t *const theAxis) {
  if (!theAxis)
    return Naive_NullException;

  Naive_H_CAST(const Naive_Plane, theHandle, H);
  if (!H)
    return Naive_InvalidHandle;
  if (!H->Axis().Dump(*theAxis))
    return Naive_InvalidValue;
  return Naive_Ok;
}

Naive_Code_t Naive_Plane_Distance(const Naive_H theHandle,
                                  const Naive_Point3d_t *thePoint,
                                  double *const theDistance) {
  if (!thePoint)
    return Naive_NullException;

  Naive_H_CAST(const Naive_Plane, theHandle, H);
  if (!H)
    return Naive_InvalidHandle;
  double aDistance = H->Distance(*thePoint);
  if (!::naivecgl::math::Util::IsValidReal(aDistance))
    return Naive_InvalidValue;
  *theDistance = aDistance;
  return Naive_Ok;
}

/// }}}

/// Naive_Line {{{

Naive_Code_t Naive_Line_New(const Naive_Line_t *theLineT,
                            Naive_H *const theLine) {
  if (!theLineT || !theLine)
    return Naive_NullException;

  Handle_Naive_Line aLine = new Naive_Line(*theLineT);
  aLine->IncrementRefCounter();
  *theLine = aLine.get();
  return Naive_Ok;
}

/// }}}

/// Naive_NurbsCurve {{{

Naive_Code_t
Naive_NurbsCurve_New(const int32_t nbPoles, const Naive_Point3d_t *thePoles,
                     const int32_t nbWeights, const double *theWeights,
                     const int32_t nbKnots, const double *theKnots,
                     const int32_t nbMults, const int32_t *theMults,
                     const int32_t theDegree, Naive_H *const theNurbsCurve) {
  if (!thePoles || !theWeights || !theKnots || !theMults || !theNurbsCurve)
    return Naive_NullException;

  if (nbPoles < 2 || nbWeights < 2 || nbKnots < 2 || nbMults < 2 ||
      theDegree < 1)
    return Naive_Err;

  Naive_Point3dList aPoles(thePoles, thePoles + nbPoles);
  Naive_RealList aWeights(theWeights, theWeights + nbWeights);
  Naive_RealList aKnots(theKnots, theKnots + nbKnots);
  Naive_IntegerList aMults(theMults, theMults + nbMults);
  Handle_Naive_NurbsCurve aCrv =
      new Naive_NurbsCurve(aPoles, aWeights, aKnots, aMults, theDegree);
  aCrv->IncrementRefCounter();
  *theNurbsCurve = aCrv.get();
  return Naive_Ok;
}

int32_t Naive_NurbsCurve_Degree(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return H ? H->Degree() : 0;
}

int32_t Naive_NurbsCurve_NbPoles(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return H ? H->NbPoles() : 0;
}

bool Naive_NurbsCurve_Pole(const Naive_H theHandle, const int32_t theI,
                           Naive_Point3d_t *const thePole) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return (H && thePole) ? H->Pole(theI).Dump(*thePole) : false;
}

double Naive_NurbsCurve_Weight(const Naive_H theHandle, const int32_t theI) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return H ? H->Weight(theI) : ::naivecgl::math::Constant::UnsetReal();
}

int32_t Naive_NurbsCurve_NbKnots(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return H ? H->NbKnots() : 0;
}

double Naive_NurbsCurve_Knot(const Naive_H theHandle, const int32_t theI) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return H ? H->Knot(theI) : ::naivecgl::math::Constant::UnsetReal();
}

int32_t Naive_NurbsCurve_Multiplicity(const Naive_H theHandle,
                                      const int32_t theI) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return H ? H->Multiplicity(theI) : 0;
}

double Naive_NurbsCurve_FirstParameter(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return H ? H->FirstParameter() : ::naivecgl::math::Constant::UnsetReal();
}

double Naive_NurbsCurve_LastParameter(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return H ? H->LastParameter() : ::naivecgl::math::Constant::UnsetReal();
}

bool Naive_NurbsCurve_PointAt(const Naive_H theHandle, const double theT,
                              Naive_Point3d_t *const theP) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return (H && theP) ? H->PointAt(theT).Dump(*theP) : false;
}

bool Naive_NurbsCurve_TangentAt(const Naive_H theHandle, const double theT,
                                Naive_Vector3d_t *const theV) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return (H && theV) ? H->TangentAt(theT).Dump(*theV) : false;
}

bool Naive_NurbsCurve_DerivativeAt(const Naive_H theHandle, const double theT,
                                   int32_t theN, int32_t *const nbD,
                                   Naive_Vector3d_t *const theD) {
  if (!theHandle || theN < 0 || !nbD)
    return false;

  *nbD = theN + 1;

  if (theD) {
    Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
    Naive_Vector3dList aD{};
    if (!H->DerivativeAt(theT, theN, aD))
      return false;

    for (Naive_Integer i = 0; i < *nbD; ++i) {
      aD[i].Dump(theD[i]);
    }
  }

  return true;
}

bool Naive_NurbsCurve_CurvatureAt(const Naive_H theHandle, const double theT,
                                  Naive_Vector3d_t *const theV) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return (H && theV) ? H->CurvatureAt(theT).Dump(*theV) : false;
}

bool Naive_NurbsCurve_IncreaseDegree(Naive_H theHandle,
                                     const int32_t theDegree) {
  Naive_H_CAST(Naive_NurbsCurve, theHandle, H);
  return H ? H->IncreaseDegree(theDegree) : false;
}

bool Naive_NurbsCurve_IncreaseMultiplicity(Naive_H theHandle,
                                           const int32_t theI,
                                           const int32_t theM) {
  Naive_H_CAST(Naive_NurbsCurve, theHandle, H);
  return H ? H->IncreaseMultiplicity(theI, theM) : false;
}

bool Naive_NurbsCurve_InsertKnot(Naive_H theHandle, const double theT,
                                 const int32_t theM) {
  Naive_H_CAST(Naive_NurbsCurve, theHandle, H);
  return H ? H->InsertKnot(theT, theM) : false;
}

bool Naive_NurbsCurve_RemoveKnot(Naive_H theHandle, const int32_t theI,
                                 const int32_t theM) {
  Naive_H_CAST(Naive_NurbsCurve, theHandle, H);
  return H ? H->RemoveKnot(theI, theM) : false;
}

/// }}}

/// Naive_NurbsSurface {{{

Naive_Code_t Naive_NurbsSurface_New(
    const int32_t nbUPoles, const int32_t nbVPoles,
    const Naive_Point3d_t *thePoles, const int32_t nbUWeights,
    const int32_t nbVWeights, const double *theWeights, const int32_t nbUKnots,
    const double *theUKnots, const int32_t nbVKnots, const double *theVKnots,
    const int32_t nbUMults, const int32_t *theUMults, const int32_t nbVMults,
    const int32_t *theVMults, const int32_t theUDegree,
    const int32_t theVDegree, Naive_H *const theNurbsSurface) {
  if (!thePoles || !theWeights || !theUKnots || !theVKnots || !theUMults ||
      !theVMults || !theNurbsSurface)
    return Naive_NullException;

  if (nbUPoles < 2 || nbVPoles < 2 || nbUWeights < 2 || nbVWeights < 2 ||
      nbUKnots < 2 || nbVKnots < 2 || nbUMults < 2 || nbVMults < 2 ||
      theUDegree < 1 || theVDegree < 1)
    return Naive_Err;

  Naive_Point3dList2 aPoles{};
  aPoles.reserve(nbUPoles);
  const Naive_Point3d_t *aPHead = thePoles;
  for (Naive_Integer i = 0; i < nbUPoles; ++i, aPHead += nbVPoles) {
    Naive_Point3dList aVP(aPHead, aPHead + nbVPoles);
    aPoles.push_back(::std::move(aVP));
  }
  Naive_RealList2 aWeights{};
  aWeights.reserve(nbUWeights);
  const Naive_Real *aWHead = theWeights;
  for (Naive_Integer i = 0; i < nbUWeights; ++i, aWHead += nbVWeights) {
    Naive_RealList aVW(aWHead, aWHead + nbVWeights);
    aWeights.push_back(::std::move(aVW));
  }
  Naive_RealList aUKnots(theUKnots, theUKnots + nbUKnots);
  Naive_RealList aVKnots(theVKnots, theVKnots + nbVKnots);
  Naive_IntegerList aUMults(theUMults, theUMults + nbUMults);
  Naive_IntegerList aVMults(theVMults, theVMults + nbVMults);
  Handle_Naive_NurbsSurface aSrf =
      new Naive_NurbsSurface(aPoles, aWeights, aUKnots, aVKnots, aUMults,
                             aVMults, theUDegree, theVDegree);
  aSrf->IncrementRefCounter();
  *theNurbsSurface = aSrf.get();
  return Naive_Ok;
}

int32_t Naive_NurbsSurface_UDegree(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_NurbsSurface, theHandle, H);
  return H ? H->UDegree() : 0;
}

int32_t Naive_NurbsSurface_VDegree(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_NurbsSurface, theHandle, H);
  return H ? H->VDegree() : 0;
}

Naive_Code_t Naive_NurbsSurface_PointAt(const Naive_H theHandle,
                                        const double theU, const double theV,
                                        Naive_Point3d_t *const theP) {
  if (!theP)
    return Naive_NullException;

  Naive_H_CAST(const Naive_NurbsSurface, theHandle, H);
  if (!H)
    return Naive_InvalidHandle;

  if (!H->PointAt(theU, theV).Dump(*theP))
    return Naive_InvalidValue;

  return Naive_Ok;
}

Naive_Code_t Naive_NurbsSurface_Evaluate(const Naive_H theHandle,
                                         const double theU, const double theV,
                                         int32_t theN, int32_t *const nbD,
                                         Naive_Vector3d_t *const theD) {
  if (!nbD)
    return Naive_NullException;

  if (theN < 0)
    return Naive_InvalidValue;

  *nbD = (theN + 1) * (theN + 2) >> 1;

  if (theD) {
    Naive_H_CAST(const Naive_NurbsSurface, theHandle, H);
    if (!H)
      return Naive_InvalidHandle;

    Naive_Vector3dList aD{};
    if (!H->Evaluate(theU, theV, theN, aD))
      return Naive_Err;

    for (Naive_Integer i = 0; i < *nbD; ++i) {
      aD[i].Dump(theD[i]);
    }
  }

  return Naive_Ok;
}

/// }}}

/// Naive_Poly {{{

Naive_Code_t Naive_Poly_New(const int32_t nbVertices,
                            const Naive_Point3d_t *theVertices,
                            const int32_t nbTriangles,
                            const Naive_Triangle_t *theTriangles,
                            Naive_H *const thePoly) {
  if (!theVertices || !theTriangles || !thePoly)
    return Naive_NullException;

  if (nbVertices < 0 || nbTriangles < 0)
    return Naive_Err;

  Naive_Point3dList aVerts(nbVertices);
  for (int i = 0; i < nbVertices; ++i) {
    aVerts[i] = theVertices[i];
  }

  Naive_List<Naive_Triangle> aTris(nbTriangles);
  for (int i = 0; i < nbTriangles; ++i) {
    aTris[i].x() = theTriangles[i].n0;
    aTris[i].y() = theTriangles[i].n1;
    aTris[i].z() = theTriangles[i].n2;
  }

  Handle_Naive_Poly aPoly =
      new Naive_Poly(::std::move(aVerts), ::std::move(aTris));
  aPoly->IncrementRefCounter();
  *thePoly = aPoly.get();
  return Naive_Ok;
}

Naive_Code_t Naive_Poly_Clone(const Naive_H theHandle,
                              Naive_H *const theClone) {
  if (!theClone)
    return Naive_NullException;

  Naive_H_CAST(const Naive_Poly, theHandle, H);
  if (!H)
    return Naive_InvalidHandle;

  Handle_Naive_Poly aClone = new Naive_Poly(*H);
  aClone->IncrementRefCounter();
  *theClone = aClone.get();
  return Naive_Ok;
}

int32_t Naive_Poly_NbVertices(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_Poly, theHandle, H);
  return H ? static_cast<int32_t>(H->Vertices().size()) : 0;
}

void Naive_Poly_Vertices(const Naive_H theHandle,
                         Naive_Point3d_t *const theVertices) {
  Naive_H_CAST(const Naive_Poly, theHandle, H);
  if (H && theVertices) {
    Naive_Size nbVertices = H->Vertices().size();
    for (Naive_Size i = 0; i < nbVertices; ++i) {
      const Naive_Point3d &aVertex = H->Vertices()[i];
      aVertex.Dump(theVertices[i]);
    }
  }
}

int32_t Naive_Poly_NbTriangles(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_Poly, theHandle, H);
  return H ? static_cast<int32_t>(H->Triangles().size()) : 0;
}

void Naive_Poly_Triangles(const Naive_H theHandle,
                          Naive_Triangle_t *const theTriangles) {
  Naive_H_CAST(const Naive_Poly, theHandle, H);
  if (H && theTriangles) {
    Naive_Size nbTriangles = H->Triangles().size();
    for (Naive_Size i = 0; i < nbTriangles; ++i) {
      const Naive_Triangle &aTriangle = H->Triangles()[i];
      theTriangles[i].n0 = aTriangle(0);
      theTriangles[i].n1 = aTriangle(1);
      theTriangles[i].n2 = aTriangle(2);
    }
  }
}

/// }}}

/// BndShape_ConvexHull2D {{{

Naive_Code_t Naive_BndShape_ConvexHull2D_New(
    int32_t nbPoints, const Naive_Point2d_t *thePoints,
    Naive_ConvexHull2D_Algorithm theAlgo, Naive_H *const theConvexHull2D) {
  if (!thePoints || !theConvexHull2D)
    return Naive_NullException;

  if (nbPoints < 0)
    return Naive_Err;

  Naive_Point2dList aPoints(nbPoints);

  for (Naive_Integer i = 0; i < nbPoints; ++i) {
    aPoints[i] = thePoints[i];
  }

  Naive_Handle<::naivecgl::bndshape::ConvexHull2D> aCH2D =
      new ::naivecgl::bndshape::ConvexHull2D(::std::move(aPoints), theAlgo);
  aCH2D->IncrementRefCounter();
  *theConvexHull2D = aCH2D.get();
  return Naive_Ok;
}

void Naive_BndShape_ConvexHull2D_SetAlgorithm(
    Naive_H theHandle, Naive_ConvexHull2D_Algorithm theAlgo) {
  Naive_H_CAST(::naivecgl::bndshape::ConvexHull2D, theHandle, H);
  if (H)
    H->SetAlgorithm(theAlgo);
}

void Naive_BndShape_ConvexHull2D_Perform(Naive_H theHandle) {
  Naive_H_CAST(::naivecgl::bndshape::ConvexHull2D, theHandle, H);
  if (H)
    H->Perform();
}

void Naive_BndShape_ConvexHull2D_Add(Naive_H theHandle,
                                     Naive_Point2d_t thePoint,
                                     bool thePerform) {
  Naive_H_CAST(::naivecgl::bndshape::ConvexHull2D, theHandle, H);
  if (H)
    H->Add({thePoint.x, thePoint.y}, thePerform);
}

Naive_Code_t Naive_BndShape_ConvexHull2D_Status(const Naive_H theHandle) {
  Naive_H_CAST(const ::naivecgl::bndshape::ConvexHull2D, theHandle, H);
  return H ? H->Status() : Naive_InvalidHandle;
}

int32_t Naive_BndShape_ConvexHull2D_NbConvexPoints(const Naive_H theHandle) {
  Naive_H_CAST(const ::naivecgl::bndshape::ConvexHull2D, theHandle, H);
  return H ? H->NbConvexPoints() : 0;
}

Naive_Code_t
Naive_BndShape_ConvexHull2D_ConvexIndices(const Naive_H theHandle,
                                          int32_t *const theConvexIndices) {
  if (!theConvexIndices)
    return Naive_NullException;

  Naive_H_CAST(const ::naivecgl::bndshape::ConvexHull2D, theHandle, H);
  if (!H)
    return Naive_InvalidHandle;

  Naive_IntegerList anIndices = H->ConvexIndices();
  ::std::copy(anIndices.cbegin(), anIndices.cend(), theConvexIndices);
  return Naive_Ok;
}

Naive_Code_t Naive_BndShape_ConvexHull2D_ConvexPoints(
    const Naive_H theHandle, Naive_Point2d_t *const theConvexPoints) {
  if (!theConvexPoints)
    return Naive_NullException;

  Naive_H_CAST(const ::naivecgl::bndshape::ConvexHull2D, theHandle, H);
  if (!H)
    return Naive_InvalidHandle;

  Naive_Point2dList aPoints = H->ConvexPoints();
  for (Naive_Integer i = 0; i < aPoints.size(); ++i) {
    aPoints[i].Dump(theConvexPoints[i]);
  }

  return Naive_Ok;
}

/// }}}

/// BndShape_EnclosingDisc {{{

Naive_Code_t Naive_BndShape_EnclosingDisc_New(Naive_H *const theEnclosingDisc) {
  if (!theEnclosingDisc)
    return Naive_NullException;

  Naive_Handle<::naivecgl::bndshape::EnclosingDisc> aED =
      new ::naivecgl::bndshape::EnclosingDisc();
  aED->IncrementRefCounter();
  *theEnclosingDisc = aED.get();
  return Naive_Ok;
}

void Naive_BndShape_EnclosingDisc_Rebuild(Naive_H theHandle, int32_t nbPoints,
                                          const Naive_Point2d_t *thePoints) {
  Naive_H_CAST(::naivecgl::bndshape::EnclosingDisc, theHandle, H);
  if (!H || nbPoints < 0 || !thePoints)
    return;

  Naive_Point2dList aPoints(nbPoints);
  for (int i = 0; i < nbPoints; ++i) {
    aPoints[i] = thePoints[i];
  }

  H->ReBuild(aPoints);
}

bool Naive_BndShape_EnclosingDisc_Circle(const Naive_H theHandle,
                                         Naive_Point2d_t *const theOrigin,
                                         double *const theR) {
  Naive_H_CAST(const ::naivecgl::bndshape::EnclosingDisc, theHandle, H);
  if (!H || !theOrigin || !theR)
    return false;

  Naive_Point2d anOrigin;
  Naive_Real aR;
  if (!H->Circle(anOrigin, aR))
    return false;

  anOrigin.Dump(*theOrigin);
  *theR = aR;

  return true;
}

/// }}}

/// Intersect_Intersection {{{

Naive_Code_t Naive_Intersect_Intersection_LinePlane(const Naive_H theLine,
                                                    const Naive_H thePlane,
                                                    double *const theT) {
  if (!theT)
    return Naive_NullException;

  Naive_H_CAST(const Naive_Line, theLine, HL);
  Naive_H_CAST(const Naive_Plane, thePlane, HP);
  if (!HL || !HP)
    return Naive_InvalidHandle;

  return ::naivecgl::intersect::Intersection::LinePlane(*HL, *HP, *theT);
}

/// }}}

/// Tessellation {{{

Naive_H Naive_Tessellation_TetraSphere(const Naive_Point3d_t *theCenter,
                                       double theRadius, int32_t theLevel) {
  if (!theCenter || theRadius <= ::naivecgl::math::Constant::ZeroTolerance() ||
      theLevel < 0)
    return nullptr;

  Naive_Point3d aCenter{*theCenter};
  auto aPoly =
      ::naivecgl::tessellation::TetraSphere(aCenter, theRadius, theLevel);
  if (!aPoly)
    return nullptr;

  aPoly->IncrementRefCounter();
  return aPoly.get();
}

/// }}}

// vim: set foldmarker={{{,}}} foldmethod=marker foldlevel=0:
