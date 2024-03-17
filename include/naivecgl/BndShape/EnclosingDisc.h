#ifndef _NaiveCGL_BndShape_EnclosingDisc_HeaderFile
#define _NaiveCGL_BndShape_EnclosingDisc_HeaderFile

#include <naivecgl/Geometry/Point2d.h>
#include <naivecgl/Geometry/Vector3d.h>

Naive_NAMESPACE_BEGIN(bndshape);

class EnclosingDisc final {
public:
  Naive_EXPORT EnclosingDisc() {}

  Naive_EXPORT void ReBuild(const Naive_Point2dList &thePoints);

  Naive_EXPORT Naive_Bool Circle(Naive_Point2d &theOrigin, Naive_Real &theR);

  Naive_EXPORT const Naive_Point2dList &Points() const { return myPoints; }

private:
  Naive_Point2dList myPoints;
  Naive_Point2d myOrigin;
  Naive_Real myR;
};

Naive_NAMESPACE_END(bndshape);

#endif
