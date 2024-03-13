#ifndef _NaiveCGL_Geometry_Circle_HeaderFile
#define _NaiveCGL_Geometry_Circle_HeaderFile

#include "Plane.h"

Naive_NAMESPACE_BEGIN(geometry);

class Circle final {
public:
  Naive_EXPORT Circle() {}

  Naive_EXPORT Circle(const Naive_Circle_T &theCircle);

  Naive_EXPORT Circle(const Plane &thePlane, const Naive_Real theRadius);

private:
  Plane myPlane;
  Naive_Real myRadius;
};

Naive_NAMESPACE_END(geometry);

using Naive_Circle = naivecgl::geometry::Circle;

#endif
