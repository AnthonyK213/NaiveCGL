#ifndef _NaiveCGL_BndShape_Obb_HeaderFile
#define _NaiveCGL_BndShape_Obb_HeaderFile

#include <naivecgl/Common/geometry.h>

Naive_Namespace_Begin(bndshape);

class Obb final {
public:
private:
  Naive_Plane myPlane;
  Naive_Interval myX;
  Naive_Interval myY;
  Naive_Interval myZ;
};

Naive_Namespace_End(bndshape);

#endif
