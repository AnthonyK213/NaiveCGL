#ifndef _NaiveCGL_Tessellation_Sphere_HeaderFile
#define _NaiveCGL_Tessellation_Sphere_HeaderFile

#include <naivecgl/Common/geometry.h>

Naive_Namespace_Begin(tessellation);

Naive_Export void UVSphere(const Naive_Point3d &theCenter,
                           const Naive_Real theRadius, Naive_Poly &thePoly);

Naive_Export Naive_H_Poly TetraSphere(const Naive_Point3d &theCenter,
                                      const Naive_Real theRadius,
                                      const Naive_Integer theLevel = 6);

Naive_Export Naive_H_Poly OctaSphere(const Naive_Point3d &theCenter,
                                     const Naive_Real theRadius,
                                     const Naive_Integer theLevel = 6);

Naive_Export Naive_H_Poly IcoShpere(const Naive_Point3d &theCenter,
                                    const Naive_Real theRadius,
                                    const Naive_Integer theLevel = 6);

Naive_Namespace_End(tessellation);

#endif
