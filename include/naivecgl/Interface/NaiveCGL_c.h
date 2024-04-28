﻿#ifndef _NaiveCGL_Interface_NaiveCGL_c_HeaderFile
#define _NaiveCGL_Interface_NaiveCGL_c_HeaderFile

#include "NaiveCGL_c_types.h"

#ifndef __cplusplus
#define Naive_CAPI
#else
#ifdef _WIN32
#define Naive_CAPI extern "C" __declspec(dllexport)
#else
#define Naive_CAPI extern "C"
#endif
#endif

/// Math_Util {{{

Naive_CAPI bool Naive_Math_Util_IsValidReal(const double theR);

/// }}}

/// Naive_NurbsCurve {{{

Naive_CAPI Naive_H Naive_NurbsCurve_New(
    const int32_t nbPoles, const Naive_Point3d_T *thePoles,
    const int32_t nbWeights, const double *theWeights, const int32_t nbKnots,
    const double *theKnots, const int32_t nbMults, const int32_t *theMults,
    const int32_t theDegree);

Naive_CAPI bool Naive_NurbsCurve_IsValid(const Naive_H theHandle);

Naive_CAPI int32_t Naive_NurbsCurve_Degree(const Naive_H theHandle);

Naive_CAPI int32_t Naive_NurbsCurve_NbPoles(const Naive_H theHandle);

Naive_CAPI bool Naive_NurbsCurve_Pole(const Naive_H theHandle,
                                      const int32_t theI,
                                      Naive_Point3d_T *thePole);

Naive_CAPI double Naive_NurbsCurve_Weight(const Naive_H theHandle,
                                          const int32_t theI);

Naive_CAPI int32_t Naive_NurbsCurve_NbKnots(const Naive_H theHandle);

Naive_CAPI double Naive_NurbsCurve_Knot(const Naive_H theHandle,
                                        const int32_t theI);

Naive_CAPI int32_t Naive_NurbsCurve_Multiplicity(const Naive_H theHandle,
                                                 const int32_t theI);

Naive_CAPI double Naive_NurbsCurve_FirstParameter(const Naive_H theHandle);

Naive_CAPI double Naive_NurbsCurve_LastParameter(const Naive_H theHandle);

Naive_CAPI bool Naive_NurbsCurve_PointAt(const Naive_H theHandle,
                                         const double theT,
                                         Naive_Point3d_T *theP);

Naive_CAPI bool Naive_NurbsCurve_TangentAt(const Naive_H theHandle,
                                           const double theT,
                                           Naive_Vector3d_T *theV);

Naive_CAPI bool Naive_NurbsCurve_DerivativeAt(const Naive_H theHandle,
                                              const double theT, int32_t theN,
                                              int32_t *nbD,
                                              Naive_Vector3d_T *theD);

Naive_CAPI bool Naive_NurbsCurve_IncreaseDegree(Naive_H theHandle,
                                                const int32_t theDegree);

Naive_CAPI bool Naive_NurbsCurve_IncreaseMultiplicity(Naive_H theHandle,
                                                      const int32_t theI,
                                                      const int32_t theM);

Naive_CAPI bool Naive_NurbsCurve_InsertKnot(Naive_H theHandle,
                                            const double theT,
                                            const int32_t theM);

/// @brief Reduces the multiplicity of the knot of index |I| to |M|.
/// @param theHandle The handle of the NURBS curve.
/// @param theI The knot index.
/// @param theM The multiplicity to reduce to.
/// @return If reduced successfully, true; otherwise, false.
Naive_CAPI bool Naive_NurbsCurve_RemoveKnot(Naive_H theHandle,
                                            const int32_t theI,
                                            const int32_t theM);

Naive_CAPI void Naive_NurbsCurve_Release(Naive_H theHandle);

/// }}}

/// Naive_NurbsSurface {{{

Naive_CAPI Naive_H Naive_NurbsSurface_New(
    const int32_t nbUPoles, const int32_t nbVPoles,
    const Naive_Point3d_T *thePoles, const int32_t nbUWeights,
    const int32_t nbVWeights, const double *theWeights, const int32_t nbUKnots,
    const double *theUKnots, const int32_t nbVKnots, const double *theVKnots,
    const int32_t nbUMults, const int32_t *theUMults, const int32_t nbVMults,
    const int32_t *theVMults, const int32_t theUDegree,
    const int32_t theVDegree);

Naive_CAPI bool Naive_NurbsSurface_IsValid(const Naive_H theHandle);

Naive_CAPI int32_t Naive_NurbsSurface_UDegree(const Naive_H theHandle);

Naive_CAPI int32_t Naive_NurbsSurface_VDegree(const Naive_H theHandle);

Naive_CAPI bool Naive_NurbsSurface_PointAt(const Naive_H theHandle,
                                           const double theU, const double theV,
                                           Naive_Point3d_T *theP);

Naive_CAPI bool Naive_NurbsSurface_Evaluate(const Naive_H theHandle,
                                            const double theU,
                                            const double theV, int32_t theN,
                                            int32_t *nbD,
                                            Naive_Vector3d_T *theD);

Naive_CAPI void Naive_NurbsSurface_Release(Naive_H theHandle);

/// }}}

/// Naive_Poly {{{

Naive_CAPI Naive_H Naive_Poly_New(const int32_t nbVertices,
                                  const Naive_Point3d_T *theVertices,
                                  const int32_t nbTriangles,
                                  const Naive_Triangle_T *theTriangles);

Naive_CAPI int32_t Naive_Poly_NbVertices(const Naive_H theHandle);

Naive_CAPI void Naive_Poly_Vertices(const Naive_H theHandle,
                                    Naive_Point3d_T *theVertices);

Naive_CAPI int32_t Naive_Poly_NbTriangles(const Naive_H theHandle);

Naive_CAPI void Naive_Poly_Triangles(const Naive_H theHandle,
                                     Naive_Triangle_T *theTriangles);

Naive_CAPI void Naive_Poly_Release(Naive_H theHandle);

/// }}}

/// BndShape {{{

Naive_CAPI Naive_H Naive_BndShape_ConvexHull2D_New(
    int32_t nbPoints, const Naive_Point2d_T *thePoints,
    Naive_ConvexHull2D_Algorithm theAlgo);

Naive_CAPI void
Naive_BndShape_ConvexHull2D_SetAlgorithm(Naive_H theHandle,
                                         Naive_ConvexHull2D_Algorithm theAlgo);

Naive_CAPI void Naive_BndShape_ConvexHull2D_Perform(Naive_H theHandle);

Naive_CAPI void Naive_BndShape_ConvexHull2D_Add(Naive_H theHandle,
                                                Naive_Point2d_T thePoint,
                                                bool thePerform);

Naive_CAPI Naive_Code
Naive_BndShape_ConvexHull2D_Status(const Naive_H theHandle);

Naive_CAPI int32_t
Naive_BndShape_ConvexHull2D_NbConvexPoints(const Naive_H theHandle);

Naive_CAPI Naive_Code Naive_BndShape_ConvexHull2D_ConvexIndices(
    const Naive_H theHandle, int32_t *theConvexIndices);

Naive_CAPI Naive_Code Naive_BndShape_ConvexHull2D_ConvexPoints(
    const Naive_H theHandle, Naive_Point2d_T *theConvexPoints);

Naive_CAPI void Naive_BndShape_ConvexHull2D_Release(Naive_H theHandle);

Naive_CAPI Naive_H Naive_BndShape_EnclosingDisc_New(void);

Naive_CAPI void
Naive_BndShape_EnclosingDisc_Rebuild(Naive_H theHandle, int32_t nbPoints,
                                     const Naive_Point2d_T *thePoints);

Naive_CAPI bool Naive_BndShape_EnclosingDisc_Circle(const Naive_H theHandle,
                                                    Naive_Point2d_T *theOrigin,
                                                    double *theR);

Naive_CAPI void Naive_BndShape_EnclosingDisc_Release(Naive_H theHandle);

/// }}}

/// Tessellation {{{

Naive_CAPI Naive_H Naive_Tessellation_TetraSphere(
    const Naive_Point3d_T *theCenter, double theRadius, int32_t theLevel);

/// }}}

#undef Naive_CAPI

#endif

// vim: set foldmarker={{{,}}} foldmethod=marker foldlevel=0:
