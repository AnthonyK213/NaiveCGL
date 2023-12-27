#ifndef _NaiveCGL_BndShape_ConvexHull_HeaderFile
#define _NaiveCGL_BndShape_ConvexHull_HeaderFile

#include <naivecgl/Common/geometry.h>

Naive_Namespace_Begin(bndshape);

Naive_Export Naive_Code convexHull2D(const Naive_List<Naive_Point2d> &points,
                                     Naive_List<Naive_Integer> &convexIndices);

Naive_Export Naive_H_Mesh convexHull3D(const Naive_List<Naive_Point3d> &points);

Naive_Namespace_End(bndshape);

#endif
