#ifndef _NaiveCGL_Interface_NaiveCGL_c_HeaderFile
#define _NaiveCGL_Interface_NaiveCGL_c_HeaderFile

#include "NaiveCGL_c_types.h"

#ifndef __cplusplus
#define Naive_CAPI
#else
#include <naivecgl/BndShape/ConvexHull2D.h>
#include <naivecgl/BndShape/ConvexHull3D.h>
#include <naivecgl/Tessellation/Sphere.h>
#ifdef _WIN32
#define Naive_CAPI extern "C" __declspec(dllexport)
#else
#define Naive_CAPI extern "C"
#endif
#endif

/// Naive_Poly {{{

Naive_CAPI int32_t Naive_Poly_NbVertices(const Naive_Poly *theHandle);

Naive_CAPI void Naive_Poly_Vertices(const Naive_Poly *theHandle,
                                    Naive_Point3d_T *theVertices);

Naive_CAPI int32_t Naive_Poly_NbTriangles(const Naive_Poly *theHandle);

Naive_CAPI void Naive_Poly_Triangles(const Naive_Poly *theHandle,
                                     Naive_Triangle_T *theTriangles);

Naive_CAPI void Naive_Poly_Release(Naive_Poly *theHandle);

/// }}}

/// BndShape {{{

Naive_CAPI Naive_Handle Naive_BndShape_ConvexHull2D_New(
    const Naive_Point2d_T *thePoints, int32_t nbPoints,
    Naive_ConvexHull2D_Algorithm theAlgo);

Naive_CAPI void
Naive_BndShape_ConvexHull2D_SetAlgorithm(Naive_Handle theHandle,
                                         Naive_ConvexHull2D_Algorithm theAlgo);

Naive_CAPI void Naive_BndShape_ConvexHull2D_Perform(Naive_Handle theHandle);

Naive_CAPI void Naive_BndShape_ConvexHull2D_Add(Naive_Handle theHandle,
                                                Naive_Point2d_T thePoint,
                                                bool thePerform);

Naive_CAPI Naive_ConvexHull2D_Status
Naive_BndShape_ConvexHull2D_Status(const Naive_Handle theHandle);

Naive_CAPI int32_t
Naive_BndShape_ConvexHull2D_NbConvexPoints(const Naive_Handle theHandle);

Naive_CAPI Naive_Code Naive_BndShape_ConvexHull2D_ConvexIndices(
    const Naive_Handle theHandle, int32_t *theConvexIndices);

Naive_CAPI Naive_Code Naive_BndShape_ConvexHull2D_ConvexPoints(
    const Naive_Handle theHandle, Naive_Point2d_T *theConvexIndices);

Naive_CAPI void Naive_BndShape_ConvexHull2D_Release(Naive_Handle theHandle);

/// }}}

/// Tessellation {{{

Naive_CAPI Naive_Poly *
Naive_Tessellation_TetraSphere(const Naive_Point3d_T *theCenter,
                               double theRadius, int32_t theLevel);

/// }}}

/// Release {{{

Naive_CAPI void Naive_Release_Int32Array(int32_t *theArray);

Naive_CAPI void Naive_Release_DoubleArray(double *theArray);

/// }}}

#undef Naive_CAPI

#endif

// vim: set foldmarker={{{,}}} foldmethod=marker foldlevel=0:
