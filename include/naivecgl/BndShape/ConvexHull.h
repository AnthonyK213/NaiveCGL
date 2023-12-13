#ifndef _NaiveCGL_BndShape_ConvexHull_Header
#define _NaiveCGL_BndShape_ConvexHull_Header

#include <naivecgl/Common/geometry.h>

Naive_Namespace_Begin(bndshape);

Naive_Export Naive_List<Naive_Integer>
convexHull2D(const Naive_List<Naive_Point2d> &points);

Naive_Export Naive_H_Mesh convexHull3D(const Naive_List<Naive_Point3d> &points);

Naive_Namespace_End(bndshape);

#endif
