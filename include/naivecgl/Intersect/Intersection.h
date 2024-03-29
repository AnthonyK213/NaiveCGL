#ifndef _NaiveCGL_Intersect_Intersection_HeaderFile
#define _NaiveCGL_Intersect_Intersection_HeaderFile

#include <naivecgl/Geometry/Line.h>
#include <naivecgl/Geometry/Plane.h>

Naive_NAMESPACE_BEGIN(intersect);

class Intersection {
public:
  static Naive_Bool LinePlane(const Naive_Line &theLine,
                              const Naive_Plane &thePlane, Naive_Real &theT);
};

Naive_NAMESPACE_END(intersect);

using Naive_Intersection = naivecgl::intersect::Intersection;

#endif
