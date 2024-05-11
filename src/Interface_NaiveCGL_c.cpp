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

#define Naive_H_CLONE(T, H)                                                    \
  Naive_H_CAST(const T, H, __h__);                                             \
  return __h__ ? new T(*__h__) : nullptr;

#define Naive_H_CLONE_TRANSIENT(T, H)                                          \
  Naive_H_CAST(const T, H, __h__);                                             \
  if (__h__) {                                                                 \
    ::naivecgl::common::handle<T> aClone = new T(*__h__);                      \
    aClone->IncrementRefCounter();                                             \
    return aClone.get();                                                       \
  }                                                                            \
  return nullptr;

#define Naive_H_RELEASE(T, H)                                                  \
  Naive_H_CAST(T, H, __h__);                                                   \
  delete __h__;

#define Naive_H_RELEASE_TRANSIENT(T, H)                                        \
  Naive_H_CAST(T, H, __h__);                                                   \
  if (__h__ && __h__->DecrementRefCounter() == 0) {                            \
    __h__->Delete();                                                           \
  }

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

/// Naive_Plane {{{

Naive_H Naive_Plane_New(void) { return new Naive_Plane; }

Naive_H Naive_Plane_FromOXY(const Naive_Point3d_T *thePoint,
                            const Naive_Vector3d_T *theXAxis,
                            const Naive_Vector3d_T *theYAxis) {
  if (!thePoint || !theXAxis || !theYAxis)
    return nullptr;

  Naive_Point3d aPoint{*thePoint};
  Naive_Vector3d aXAxis{*theXAxis};
  Naive_Vector3d aYAxis{*theYAxis};
  return new Naive_Plane(aPoint, aXAxis, aYAxis);
}

Naive_H Naive_Plane_FromON(const Naive_Point3d_T *thePoint,
                           const Naive_Vector3d_T *theNormal) {
  if (!thePoint || !theNormal)
    return nullptr;

  Naive_Point3d aPoint{*thePoint};
  Naive_Vector3d aNormal{*theNormal};
  return new Naive_Plane(aPoint, aNormal);
}

Naive_H Naive_Plane_Clone(const Naive_H theHandle) {
  Naive_H_CLONE(Naive_Plane, theHandle);
}

bool Naive_Plane_IsValid(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_Plane, theHandle, H);
  return H ? H->IsValid() : false;
}

bool Naive_Plane_Location(const Naive_H theHandle,
                          Naive_Point3d_T *theLocation) {
  Naive_H_CAST(const Naive_Plane, theHandle, H);
  return (H && theLocation) ? H->Location().Dump(*theLocation) : false;
}

bool Naive_Plane_XAxis(const Naive_H theHandle, Naive_Point3d_T *theXAxis) {
  Naive_H_CAST(const Naive_Plane, theHandle, H);
  return (H && theXAxis) ? H->XAxis().Dump(*theXAxis) : false;
}

bool Naive_Plane_YAxis(const Naive_H theHandle, Naive_Point3d_T *theYAxis) {
  Naive_H_CAST(const Naive_Plane, theHandle, H);
  return (H && theYAxis) ? H->YAxis().Dump(*theYAxis) : false;
}

bool Naive_Plane_Axis(const Naive_H theHandle, Naive_Point3d_T *theAxis) {
  Naive_H_CAST(const Naive_Plane, theHandle, H);
  return (H && theAxis) ? H->Axis().Dump(*theAxis) : false;
}

double Naive_Plane_Distance(const Naive_H theHandle,
                            const Naive_Point3d_T *thePoint) {
  Naive_H_CAST(const Naive_Plane, theHandle, H);
  return (H && thePoint) ? H->Distance(*thePoint)
                         : ::naivecgl::math::Constant::UnsetReal();
}

void Naive_Plane_Release(const Naive_H theHandle) {
  Naive_H_RELEASE(const Naive_Plane, theHandle);
}

/// }}}

/// Naive_Line {{{

Naive_H Naive_Line_New(void) {
  Handle_Naive_Line aLine = new Naive_Line;
  aLine->IncrementRefCounter();
  return aLine.get();
}

Naive_H Naive_Line_FromEnds(const Naive_Point3d_T *theFrom,
                            const Naive_Point3d_T *theTo) {
  if (!theFrom || !theTo)
    return nullptr;

  Naive_Point3d aFrom = *theFrom;
  Naive_Point3d aTo = *theTo;
  Handle_Naive_Line aLine = new Naive_Line(aFrom, aTo);
  aLine->IncrementRefCounter();
  return aLine.get();
}

Naive_H Naive_Line_Clone(const Naive_H theHandle) {
  Naive_H_CLONE_TRANSIENT(Naive_Line, theHandle);
}

bool Naive_Line_IsValid(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_Line, theHandle, H);
  return H ? H->IsValid() : false;
}

void Naive_Line_Release(Naive_H theHandle) {
  Naive_H_RELEASE_TRANSIENT(Naive_Line, theHandle);
}

/// }}}

/// Naive_NurbsCurve {{{

Naive_H Naive_NurbsCurve_New(const int32_t nbPoles,
                             const Naive_Point3d_T *thePoles,
                             const int32_t nbWeights, const double *theWeights,
                             const int32_t nbKnots, const double *theKnots,
                             const int32_t nbMults, const int32_t *theMults,
                             const int32_t theDegree) {
  if (nbPoles < 2 || nbWeights < 2 || nbKnots < 2 || nbMults < 2 ||
      theDegree < 1)
    return nullptr;

  if (!thePoles || !theWeights || !theKnots || !theMults)
    return nullptr;

  Naive_Point3dList aPoles(thePoles, thePoles + nbPoles);
  Naive_RealList aWeights(theWeights, theWeights + nbWeights);
  Naive_RealList aKnots(theKnots, theKnots + nbKnots);
  Naive_IntegerList aMults(theMults, theMults + nbMults);
  Handle_Naive_NurbsCurve aCrv =
      new Naive_NurbsCurve(aPoles, aWeights, aKnots, aMults, theDegree);
  aCrv->IncrementRefCounter();
  return aCrv.get();
}

Naive_H Naive_NurbsCurve_Clone(const Naive_H theHandle) {
  Naive_H_CLONE_TRANSIENT(Naive_NurbsCurve, theHandle);
}

bool Naive_NurbsCurve_IsValid(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return H ? H->IsValid() : false;
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
                           Naive_Point3d_T *thePole) {
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
                              Naive_Point3d_T *theP) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return (H && theP) ? H->PointAt(theT).Dump(*theP) : false;
}

bool Naive_NurbsCurve_TangentAt(const Naive_H theHandle, const double theT,
                                Naive_Vector3d_T *theV) {
  Naive_H_CAST(const Naive_NurbsCurve, theHandle, H);
  return (H && theV) ? H->TangentAt(theT).Dump(*theV) : false;
}

bool Naive_NurbsCurve_DerivativeAt(const Naive_H theHandle, const double theT,
                                   int32_t theN, int32_t *nbD,
                                   Naive_Vector3d_T *theD) {
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
                                  Naive_Vector3d_T *theV) {
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

void Naive_NurbsCurve_Release(Naive_H theHandle) {
  Naive_H_RELEASE_TRANSIENT(Naive_NurbsCurve, theHandle);
}

/// }}}

/// Naive_NurbsSurface {{{

Naive_H Naive_NurbsSurface_New(
    const int32_t nbUPoles, const int32_t nbVPoles,
    const Naive_Point3d_T *thePoles, const int32_t nbUWeights,
    const int32_t nbVWeights, const double *theWeights, const int32_t nbUKnots,
    const double *theUKnots, const int32_t nbVKnots, const double *theVKnots,
    const int32_t nbUMults, const int32_t *theUMults, const int32_t nbVMults,
    const int32_t *theVMults, const int32_t theUDegree,
    const int32_t theVDegree) {
  if (nbUPoles < 2 || nbVPoles < 2 || nbUWeights < 2 || nbVWeights < 2 ||
      nbUKnots < 2 || nbVKnots < 2 || nbUMults < 2 || nbVMults < 2 ||
      theUDegree < 1 || theVDegree < 1)
    return nullptr;

  if (!thePoles || !theWeights || !theUKnots || !theVKnots || !theUMults ||
      !theVMults)
    return nullptr;

  Naive_Point3dList2 aPoles{};
  aPoles.reserve(nbUPoles);
  const Naive_Point3d_T *aPHead = thePoles;
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
  return aSrf.get();
}

Naive_H Naive_NurbsSurface_Clone(const Naive_H theHandle) {
  Naive_H_CLONE_TRANSIENT(Naive_NurbsSurface, theHandle);
}

bool Naive_NurbsSurface_IsValid(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_NurbsSurface, theHandle, H);
  return H ? H->IsValid() : false;
}

int32_t Naive_NurbsSurface_UDegree(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_NurbsSurface, theHandle, H);
  return H ? H->UDegree() : 0;
}

int32_t Naive_NurbsSurface_VDegree(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_NurbsSurface, theHandle, H);
  return H ? H->VDegree() : 0;
}

bool Naive_NurbsSurface_PointAt(const Naive_H theHandle, const double theU,
                                const double theV, Naive_Point3d_T *theP) {
  Naive_H_CAST(const Naive_NurbsSurface, theHandle, H);
  return (H && theP) ? H->PointAt(theU, theV).Dump(*theP) : false;
}

bool Naive_NurbsSurface_Evaluate(const Naive_H theHandle, const double theU,
                                 const double theV, int32_t theN, int32_t *nbD,
                                 Naive_Vector3d_T *theD) {
  if (!theHandle || theN < 0 || !nbD)
    return false;

  *nbD = (theN + 1) * (theN + 2) >> 1;

  if (theD) {
    Naive_H_CAST(const Naive_NurbsSurface, theHandle, H);
    Naive_Vector3dList aD{};
    if (!H->Evaluate(theU, theV, theN, aD))
      return false;

    for (Naive_Integer i = 0; i < *nbD; ++i) {
      aD[i].Dump(theD[i]);
    }
  }

  return true;
}

void Naive_NurbsSurface_Release(Naive_H theHandle) {
  Naive_H_RELEASE_TRANSIENT(Naive_NurbsSurface, theHandle);
}

/// }}}

/// Naive_Poly {{{

Naive_H Naive_Poly_New(const int32_t nbVertices,
                       const Naive_Point3d_T *theVertices,
                       const int32_t nbTriangles,
                       const Naive_Triangle_T *theTriangles) {
  if (nbVertices < 0 || !theVertices || nbTriangles < 0 || !theTriangles)
    return nullptr;

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
  return aPoly.get();
}

Naive_H Naive_Poly_Clone(const Naive_H theHandle) {
  Naive_H_CLONE_TRANSIENT(Naive_Poly, theHandle);
}

int32_t Naive_Poly_NbVertices(const Naive_H theHandle) {
  Naive_H_CAST(const Naive_Poly, theHandle, H);
  return H ? static_cast<int32_t>(H->Vertices().size()) : 0;
}

void Naive_Poly_Vertices(const Naive_H theHandle,
                         Naive_Point3d_T *theVertices) {
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
                          Naive_Triangle_T *theTriangles) {
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

void Naive_Poly_Release(Naive_H theHandle) {
  Naive_H_RELEASE_TRANSIENT(Naive_Poly, theHandle);
}

/// }}}

/// BndShape_ConvexHull2D {{{

Naive_H Naive_BndShape_ConvexHull2D_New(int32_t nbPoints,
                                        const Naive_Point2d_T *thePoints,
                                        Naive_ConvexHull2D_Algorithm theAlgo) {
  if (!thePoints || nbPoints < 0)
    return nullptr;

  Naive_Point2dList aPoints(nbPoints);

  for (Naive_Integer i = 0; i < nbPoints; ++i) {
    aPoints[i] = thePoints[i];
  }

  return new ::naivecgl::bndshape::ConvexHull2D(::std::move(aPoints), theAlgo);
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
                                     Naive_Point2d_T thePoint,
                                     bool thePerform) {
  Naive_H_CAST(::naivecgl::bndshape::ConvexHull2D, theHandle, H);
  if (H)
    H->Add({thePoint.x, thePoint.y}, thePerform);
}

Naive_Code Naive_BndShape_ConvexHull2D_Status(const Naive_H theHandle) {
  Naive_H_CAST(const ::naivecgl::bndshape::ConvexHull2D, theHandle, H);
  return H ? H->Status() : Naive_NullException;
}

int32_t Naive_BndShape_ConvexHull2D_NbConvexPoints(const Naive_H theHandle) {
  Naive_H_CAST(const ::naivecgl::bndshape::ConvexHull2D, theHandle, H);
  return H ? H->NbConvexPoints() : 0;
}

Naive_Code
Naive_BndShape_ConvexHull2D_ConvexIndices(const Naive_H theHandle,
                                          int32_t *theConvexIndices) {
  Naive_H_CAST(const ::naivecgl::bndshape::ConvexHull2D, theHandle, H);
  if (!H || !theConvexIndices)
    return Naive_NullException;

  Naive_IntegerList anIndices = H->ConvexIndices();
  ::std::copy(anIndices.cbegin(), anIndices.cend(), theConvexIndices);
  return Naive_Ok;
}

Naive_Code
Naive_BndShape_ConvexHull2D_ConvexPoints(const Naive_H theHandle,
                                         Naive_Point2d_T *theConvexPoints) {
  Naive_H_CAST(const ::naivecgl::bndshape::ConvexHull2D, theHandle, H);
  if (!H || !theConvexPoints)
    return Naive_NullException;

  Naive_Point2dList aPoints = H->ConvexPoints();
  for (Naive_Integer i = 0; i < aPoints.size(); ++i) {
    aPoints[i].Dump(theConvexPoints[i]);
  }

  return Naive_Ok;
}

void Naive_BndShape_ConvexHull2D_Release(const Naive_H theHandle) {
  Naive_H_RELEASE(const ::naivecgl::bndshape::ConvexHull2D, theHandle);
}

/// }}}

/// BndShape_EnclosingDisc {{{

Naive_H Naive_BndShape_EnclosingDisc_New(void) {
  return new ::naivecgl::bndshape::EnclosingDisc();
}

void Naive_BndShape_EnclosingDisc_Rebuild(Naive_H theHandle, int32_t nbPoints,
                                          const Naive_Point2d_T *thePoints) {
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
                                         Naive_Point2d_T *theOrigin,
                                         double *theR) {
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

void Naive_BndShape_EnclosingDisc_Release(const Naive_H theHandle) {
  Naive_H_RELEASE(const ::naivecgl::bndshape::EnclosingDisc, theHandle);
}

/// }}}

/// Intersect_Intersection {{{

bool Naive_Intersect_Intersection_LinePlane(const Naive_H theLine,
                                            const Naive_H thePlane,
                                            double *theT) {
  Naive_H_CAST(const Naive_Line, theLine, HL);
  Naive_H_CAST(const Naive_Plane, thePlane, HP);
  if (!HL || !HP || !theT)
    return false;
  return ::naivecgl::intersect::Intersection::LinePlane(*HL, *HP, *theT);
}

/// }}}

/// Tessellation {{{

Naive_H Naive_Tessellation_TetraSphere(const Naive_Point3d_T *theCenter,
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
