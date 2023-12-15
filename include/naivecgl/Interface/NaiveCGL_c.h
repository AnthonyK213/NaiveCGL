#ifndef _NaiveCGL_Interface_NaiveCGL_c_Header
#define _NaiveCGL_Interface_NaiveCGL_c_Header

#ifndef __cplusplus
#define Naive_CAPI
#else
#ifdef _WIN32
#include <naivecgl/BndShape/ConvexHull.h>
#include <naivecgl/Tessellation/Sphere.h>
#define Naive_CAPI extern "C" __declspec(dllexport)
#else
#define Naive_CAPI extern "C"
#endif
#endif

#include "NaiveCGL_c_types.h"

/// BndShape {{{

Naive_CAPI Naive_Code Naive_BndShape_ConvexHull2D(const double *points,
                                                  int32_t *count,
                                                  int32_t **convexIndices);

/// }}}

/// Tessellation {{{

/// }}}

/// Release {{{

Naive_CAPI void Naive_Release_OpaqueArray(void *array);

/// }}}

#undef Naive_CAI

#endif

// vim: set foldmarker={{{,}}} foldmethod=marker foldlevel=0:
