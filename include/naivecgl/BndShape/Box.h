#ifndef _NaiveCGL_BndShape_Box_HeaderFile
#define _NaiveCGL_BndShape_Box_HeaderFile

#include <naivecgl/Geometry/Point3d.h>
#include <naivecgl/Geometry/Vector3d.h>

Naive_NAMESPACE_BEGIN(bndshape);

class Box final {
public:
  Naive_EXPORT Box();

  Naive_EXPORT Box(const Naive_Point3d &theMin, const Naive_Point3d &theMax);

private:
  Naive_Real myXMin;
  Naive_Real myYMin;
  Naive_Real myZMin;
  Naive_Real myXMax;
  Naive_Real myYMax;
  Naive_Real myZMax;
};

Naive_NAMESPACE_END(bndshape);

#endif
