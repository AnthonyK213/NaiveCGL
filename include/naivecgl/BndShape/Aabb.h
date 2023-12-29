#ifndef _NaiveCGL_BndShape_Aabb_HeaderFile
#define _NaiveCGL_BndShape_Aabb_HeaderFile

#include <naivecgl/Common/geometry.h>

Naive_Namespace_Begin(bndshape);

class Aabb final {
public:
  Aabb();
  
  Aabb(const Naive_Point3d &theMin, const Naive_Point3d &theMax);
};

Naive_Namespace_End(bndshape);

#endif
