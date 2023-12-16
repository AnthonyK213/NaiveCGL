#ifndef _NaiveCGL_Interface_NaiveCGL_c_Header
#define _NaiveCGL_Interface_NaiveCGL_c_Header

#include "NaiveCGL_c_types.h"

#ifndef __cplusplus
#define Naive_CAPI
#else
#include <naivecgl/BndShape/ConvexHull.h>
#include <naivecgl/Tessellation/Sphere.h>
#ifdef _WIN32
#define Naive_CAPI extern "C" __declspec(dllexport)
#else
#define Naive_CAPI extern "C"
#endif
#endif

/// Naive_Poly {{{

Naive_CAPI int32_t Naive_Poly_NbVertices(const Naive_Poly *handle);

Naive_CAPI void Naive_Poly_Vertices(const Naive_Poly *handle,
                                    Naive_Point3d_T *vertices);

Naive_CAPI int32_t Naive_Poly_NbTriangles(const Naive_Poly *handle);

Naive_CAPI void Naive_Poly_Triangles(const Naive_Poly *handle,
                                     Naive_Triangle_T *triangles);

Naive_CAPI void Naive_Poly_Release(Naive_Poly *handle);

/// }}}

/// BndShape {{{

Naive_CAPI Naive_Code Naive_BndShape_ConvexHull2D(const Naive_Point2d_T *points,
                                                  int32_t *count,
                                                  int32_t **convexIndices);

/// }}}

/// Tessellation {{{

Naive_CAPI Naive_Poly *
Naive_Tessellation_Tetrasphere(const Naive_Point3d_T *center, double radius,
                               int32_t level);

/// }}}

/// Release {{{

Naive_CAPI void Naive_Release_Int32Array(int32_t *array);

Naive_CAPI void Naive_Release_DoubleArray(double *array);

/// }}}

#undef Naive_CAPI

#endif

// vim: set foldmarker={{{,}}} foldmethod=marker foldlevel=0:
