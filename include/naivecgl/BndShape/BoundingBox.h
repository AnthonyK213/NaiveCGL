#ifndef _NaiveCGL_BndShape_BoundingBox_HeaderFile
#define _NaiveCGL_BndShape_BoundingBox_HeaderFile

#include "../Geometry/Box.h"
#include "../Geometry/OBB.h"

Naive_NAMESPACE_BEGIN(bndshape);

class BoundingBox final {
public:
  Naive_EXPORT static Naive_Code
  BoxFromPoints(const Naive_Pnt3dList1 &thePoints, Naive_Box &theBox);

  Naive_EXPORT static Naive_Code
  OBBFromPoints(const Naive_Pnt3dList1 &thePoints, Naive_OBB &theOBB);
};

Naive_NAMESPACE_END(bndshape);

#endif
