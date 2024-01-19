#ifndef _NaiveCGL_BndShape_ConvexHull_HeaderFile
#define _NaiveCGL_BndShape_ConvexHull_HeaderFile

#include <naivecgl/Common/geometry.h>

Naive_NAMESPACE_BEGIN(bndshape);

Naive_EXPORT Naive_Code
ConvexHull2D(const Naive_List<Naive_Point2d> &thePoints,
             Naive_List<Naive_Integer> &theConvexIndices);

Naive_EXPORT Naive_H_Mesh
ConvexHull3D(const Naive_List<Naive_Point3d> &thePoints);

Naive_NAMESPACE_END(bndshape);

#endif
