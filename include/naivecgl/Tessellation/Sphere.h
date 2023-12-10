#ifndef _NaiveCGL_Tessellation_Sphere_Header
#define _NaiveCGL_Tessellation_Sphere_Header

#include <naivecgl/Common/mesh.h>

namespace naivecgl {
namespace tessellation {

/// @brief
/// @param center
/// @param radius
/// @param poly
Naive_Export void uvsphere(const Naive_Vector3d &center,
                           const Naive_Real radius, Naive_Poly3D &poly);

/// @brief
/// @param center
/// @param radius
/// @param poly
Naive_Export Naive_H_Poly3D octasphere(const Naive_Vector3d &center,
                                       const Naive_Real radius,
                                       const Naive_Integer level = 2);

/// @brief
/// @param center
/// @param radius
/// @param poly
Naive_Export void icoshpere(const Naive_Vector3d &center,
                            const Naive_Real radius, Naive_Poly3D &poly);

} // namespace tessellation
} // namespace naivecgl

#endif
