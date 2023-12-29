#ifndef _NaiveCGL_BndShape_Aabb_HeaderFile
#define _NaiveCGL_BndShape_Aabb_HeaderFile

#include <naivecgl/Common/geometry.h>

Naive_Namespace_Begin(bndshape);

class Aabb final {
public:
  Naive_Export Aabb();

  Naive_Export Aabb(const Naive_Point3d &theMin, const Naive_Point3d &theMax);

private:
  Naive_Real myXMin;
  Naive_Real myYMin;
  Naive_Real myZMin;
  Naive_Real myXMax;
  Naive_Real myYMax;
  Naive_Real myZMax;
};

Naive_Namespace_End(bndshape);

#endif
