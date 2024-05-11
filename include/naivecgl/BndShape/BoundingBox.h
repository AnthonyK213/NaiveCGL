#ifndef _NaiveCGL_BndShape_BoundingBox_HeaderFile
#define _NaiveCGL_BndShape_BoundingBox_HeaderFile

#include <naivecgl/Geometry/Box.h>
#include <naivecgl/Geometry/OBB.h>

Naive_NAMESPACE_BEGIN(bndshape);

class BoundingBox final {
public:
  Naive_EXPORT static Naive_Code
  BoxFromPoints(const Naive_Point3dList &thePoints, Naive_Box &theBox);

  Naive_EXPORT static Naive_Code
  OBBFromPoints(const Naive_Point3dList &thePoints, Naive_OBB &theOBB);
};

Naive_NAMESPACE_END(bndshape);

#endif
