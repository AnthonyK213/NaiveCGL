#ifndef _NaiveCGL_Geometry_Rectangle_HeaderFile
#define _NaiveCGL_Geometry_Rectangle_HeaderFile

#include "def.h"

Naive_NAMESPACE_BEGIN(geometry);

class Rectangle final {
public:
private:
  Plane myPlane;
  Interval myX;
  Interval myY;
};

Naive_NAMESPACE_END(geometry);

#endif
