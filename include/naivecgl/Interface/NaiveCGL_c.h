#ifndef _NaiveCGL_Interface_NaiveCGL_c_HeaderFile
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

/// Math_Constant {{{

Naive_CAPI double Naive_Math_Constant_PI(void);

Naive_CAPI double Naive_Math_Constant_Epsilon(void);

Naive_CAPI double Naive_Math_Constant_MinReal(void);

Naive_CAPI double Naive_Math_Constant_MaxReal(void);

Naive_CAPI double Naive_Math_Constant_UnsetReal(void);

// }}}

/// Math_Util {{{

Naive_CAPI bool Naive_Math_Util_IsValidReal(const double theR);

/// }}}

/// Naive_Transient {{{

Naive_CAPI Naive_Code_t Naive_Transient_Release(Naive_H theHandle);

/// }}}

/// Naive_Geometry {{{

Naive_CAPI Naive_Code_t Naive_Geometry_IsValid(const Naive_H theHandle,
                                               bool *const theIsValid);

Naive_CAPI Naive_Code_t Naive_Geometry_Clone(const Naive_H theHandle,
                                             Naive_H *const theClone);

/// }}}

/// Naive_Plane {{{

Naive_CAPI Naive_Code_t Naive_Plane_New(const Naive_Plane_t *thePlaneT,
                                        Naive_H *const thePlane);

Naive_CAPI Naive_Code_t Naive_Plane_Location(
    const Naive_H theHandle, Naive_Point3d_t *const theLocation);

Naive_CAPI Naive_Code_t Naive_Plane_XAxis(const Naive_H theHandle,
                                          Naive_Point3d_t *const theXAxis);

Naive_CAPI Naive_Code_t Naive_Plane_YAxis(const Naive_H theHandle,
                                          Naive_Point3d_t *const theYAxis);

Naive_CAPI Naive_Code_t Naive_Plane_Axis(const Naive_H theHandle,
                                         Naive_Point3d_t *const theAxis);

Naive_CAPI Naive_Code_t Naive_Plane_Distance(const Naive_H theHandle,
                                             const Naive_Point3d_t *thePoint,
                                             double *const theDistance);

/// }}}

/// Naive_Line {{{

Naive_CAPI Naive_Code_t Naive_Line_New(const Naive_Line_t *theLineT,
                                       Naive_H *const theLine);

/// }}}

/// Naive_NurbsCurve {{{

Naive_CAPI Naive_Code_t Naive_NurbsCurve_New(
    const int32_t nbPoles, const Naive_Point3d_t *thePoles,
    const int32_t nbWeights, const double *theWeights, const int32_t nbKnots,
    const double *theKnots, const int32_t nbMults, const int32_t *theMults,
    const int32_t theDegree, Naive_H *const theNurbsCurve);

Naive_CAPI int32_t Naive_NurbsCurve_Degree(const Naive_H theHandle);

Naive_CAPI int32_t Naive_NurbsCurve_NbPoles(const Naive_H theHandle);

Naive_CAPI bool Naive_NurbsCurve_Pole(const Naive_H theHandle,
                                      const int32_t theI,
                                      Naive_Point3d_t *const thePole);

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
                                         Naive_Point3d_t *const theP);

Naive_CAPI bool Naive_NurbsCurve_TangentAt(const Naive_H theHandle,
                                           const double theT,
                                           Naive_Vector3d_t *const theV);

Naive_CAPI bool Naive_NurbsCurve_DerivativeAt(const Naive_H theHandle,
                                              const double theT, int32_t theN,
                                              int32_t *const nbD,
                                              Naive_Vector3d_t *const theD);

Naive_CAPI bool Naive_NurbsCurve_CurvatureAt(const Naive_H theHandle,
                                             const double theT,
                                             Naive_Vector3d_t *const theV);

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

/// }}}

/// Naive_NurbsSurface {{{

Naive_CAPI Naive_Code_t Naive_NurbsSurface_New(
    const int32_t nbUPoles, const int32_t nbVPoles,
    const Naive_Point3d_t *thePoles, const int32_t nbUWeights,
    const int32_t nbVWeights, const double *theWeights, const int32_t nbUKnots,
    const double *theUKnots, const int32_t nbVKnots, const double *theVKnots,
    const int32_t nbUMults, const int32_t *theUMults, const int32_t nbVMults,
    const int32_t *theVMults, const int32_t theUDegree,
    const int32_t theVDegree, Naive_H *const theNurbsSurface);

Naive_CAPI int32_t Naive_NurbsSurface_UDegree(const Naive_H theHandle);

Naive_CAPI int32_t Naive_NurbsSurface_VDegree(const Naive_H theHandle);

Naive_CAPI Naive_Code_t Naive_NurbsSurface_PointAt(const Naive_H theHandle,
                                                   const double theU,
                                                   const double theV,
                                                   Naive_Point3d_t *const theP);

Naive_CAPI Naive_Code_t Naive_NurbsSurface_Evaluate(
    const Naive_H theHandle, const double theU, const double theV, int32_t theN,
    int32_t *const nbD, Naive_Vector3d_t *const theD);

/// }}}

/// Naive_Poly {{{

Naive_CAPI Naive_Code_t Naive_Poly_New(const int32_t nbVertices,
                                       const Naive_Point3d_t *theVertices,
                                       const int32_t nbTriangles,
                                       const Naive_Triangle_t *theTriangles,
                                       Naive_H *const thePoly);

Naive_CAPI Naive_Code_t Naive_Poly_Clone(const Naive_H theHandle,
                                         Naive_H *const theClone);

Naive_CAPI int32_t Naive_Poly_NbVertices(const Naive_H theHandle);

Naive_CAPI void Naive_Poly_Vertices(const Naive_H theHandle,
                                    Naive_Point3d_t *const theVertices);

Naive_CAPI int32_t Naive_Poly_NbTriangles(const Naive_H theHandle);

Naive_CAPI void Naive_Poly_Triangles(const Naive_H theHandle,
                                     Naive_Triangle_t *const theTriangles);

/// }}}

/// BndShape_ConvexHull2D {{{

Naive_CAPI Naive_Code_t Naive_BndShape_ConvexHull2D_New(
    int32_t nbPoints, const Naive_Point2d_t *thePoints,
    Naive_ConvexHull2D_Algorithm theAlgo, Naive_H *const theConvexHull2D);

Naive_CAPI void
Naive_BndShape_ConvexHull2D_SetAlgorithm(Naive_H theHandle,
                                         Naive_ConvexHull2D_Algorithm theAlgo);

Naive_CAPI void Naive_BndShape_ConvexHull2D_Perform(Naive_H theHandle);

Naive_CAPI void Naive_BndShape_ConvexHull2D_Add(Naive_H theHandle,
                                                Naive_Point2d_t thePoint,
                                                bool thePerform);

Naive_CAPI Naive_Code_t
Naive_BndShape_ConvexHull2D_Status(const Naive_H theHandle);

Naive_CAPI int32_t
Naive_BndShape_ConvexHull2D_NbConvexPoints(const Naive_H theHandle);

Naive_CAPI Naive_Code_t Naive_BndShape_ConvexHull2D_ConvexIndices(
    const Naive_H theHandle, int32_t *const theConvexIndices);

Naive_CAPI Naive_Code_t Naive_BndShape_ConvexHull2D_ConvexPoints(
    const Naive_H theHandle, Naive_Point2d_t *const theConvexPoints);

/// }}}

/// BndShape_EnclosingDisc {{{

Naive_CAPI Naive_Code_t
Naive_BndShape_EnclosingDisc_New(Naive_H *const theEnclosingDisc);

Naive_CAPI void
Naive_BndShape_EnclosingDisc_Rebuild(Naive_H theHandle, int32_t nbPoints,
                                     const Naive_Point2d_t *thePoints);

Naive_CAPI bool
Naive_BndShape_EnclosingDisc_Circle(const Naive_H theHandle,
                                    Naive_Point2d_t *const theOrigin,
                                    double *const theR);

/// }}}

/// Intersect_Intersection {{{

Naive_CAPI Naive_Code_t Naive_Intersect_Intersection_LinePlane(
    const Naive_H theLine, const Naive_H thePlane, double *const theT);

/// }}}

/// Tessellation {{{

/// @brief Generate a tetrasphere.
/// @param theCenter Center of the sphere.
/// @param theRadius Radius of the sphere.
/// @param theLevel The tessellation level.
/// @return Handle of |Naive_Poly|.
Naive_CAPI Naive_H Naive_Tessellation_TetraSphere(
    const Naive_Point3d_t *theCenter, double theRadius, int32_t theLevel);

/// }}}

#undef Naive_CAPI

#endif

// vim: set foldmarker={{{,}}} foldmethod=marker foldlevel=0:
