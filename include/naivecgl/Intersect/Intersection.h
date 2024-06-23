#ifndef _NaiveCGL_Intersect_Intersection_HeaderFile
#define _NaiveCGL_Intersect_Intersection_HeaderFile

#include "../Geometry/Line.h"
#include "../Geometry/Plane.h"

Naive_NAMESPACE_BEGIN(intersect);

class Intersection {
public:
  Naive_EXPORT static Naive_Code LinePlane(const Handle_Naive_Line &theLine,
                                           const Handle_Naive_Plane &thePlane,
                                           Naive_Real &theT);
};

Naive_NAMESPACE_END(intersect);

using Naive_Intersection = ::naivecgl::intersect::Intersection;

#endif
