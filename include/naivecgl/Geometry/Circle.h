#ifndef _NaiveCGL_Geometry_Circle_HeaderFile
#define _NaiveCGL_Geometry_Circle_HeaderFile

#include "Plane.h"

Naive_Namespace_Begin(geometry);

class Circle final {
public:
  Naive_Export Circle();

  Naive_Export Circle(const Plane &thePlane, const Naive_Real theRadius);

private:
  Plane myPlane;
  Naive_Real myRadius;
};

Naive_Namespace_End(geometry);

#endif
