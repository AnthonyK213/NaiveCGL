#ifndef _NaiveCGL_Geometry_Rectangle_HeaderFile
#define _NaiveCGL_Geometry_Rectangle_HeaderFile

#include "../Math/Intv.h"
#include "../Math/Pln.h"

Naive_NAMESPACE_BEGIN(geometry);

class Rectangle final {
public:
private:
  Naive_Pln myPln;
  Naive_Interval myX;
  Naive_Interval myY;
};

Naive_NAMESPACE_END(geometry);

using Naive_Rectangle = ::naivecgl::geometry::Rectangle;

#endif
