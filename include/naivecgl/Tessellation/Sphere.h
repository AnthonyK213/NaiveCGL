#ifndef _NaiveCGL_Tessellation_Sphere_HeaderFile
#define _NaiveCGL_Tessellation_Sphere_HeaderFile

#include <naivecgl/Common/geometry.h>

Naive_Namespace_Begin(tessellation);

/// @brief
/// @param center
/// @param radius
/// @param poly
Naive_Export void uvsphere(const Naive_Point3d &center,
                           const Naive_Real radius, Naive_Poly &poly);

/// @brief
/// @param center
/// @param radius
/// @param level
/// @return
Naive_Export Naive_H_Poly tetrasphere(const Naive_Point3d &center,
                                      const Naive_Real radius,
                                      const Naive_Integer level = 6);

/// @brief
/// @param center
/// @param radius
/// @param level
/// @return
Naive_Export Naive_H_Poly octasphere(const Naive_Point3d &center,
                                     const Naive_Real radius,
                                     const Naive_Integer level = 6);

/// @brief
/// @param center
/// @param radius
/// @param level
/// @return
Naive_Export Naive_H_Poly icoshpere(const Naive_Point3d &center,
                                    const Naive_Real radius,
                                    const Naive_Integer level = 6);

Naive_Namespace_End(tessellation);

#endif
