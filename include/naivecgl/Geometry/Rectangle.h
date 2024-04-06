#ifndef _NaiveCGL_Geometry_Rectangle_HeaderFile
#define _NaiveCGL_Geometry_Rectangle_HeaderFile

#include "Interval.h"
#include "Plane.h"

Naive_NAMESPACE_BEGIN(geometry);

class Rectangle final {
public:
private:
  Plane myPlane;
  Interval myX;
  Interval myY;
};

Naive_NAMESPACE_END(geometry);

using Naive_Rectangle = ::naivecgl::geometry::Rectangle;

#endif
